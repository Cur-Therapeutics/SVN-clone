/********************************************************************
 *
 *   faulthandler.c
 *
 *   Description:    Faulthandling
 *
 *   Copyright NextPhase Medical, Inc. 2026 -- All rights reserved.
 *
 *--------------------------------------------------------------------
 *
 *   Revision History:
 *
 *   Rev.    | Date      | Name              | Description
 *   1       | 11/08/18  | Brian Compter     | Created
 *
 ********************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "main.h"
#include "faulthandler.h"
#include "diagnostics.h"
#include "health.h"

/**
 * System error bit field. ((uint64_t) 1 << eFAULT_TYPE);
 */
uint64_t gSystemErrors = 0;
uint32_t gErrorCount = 0;

/**
 * Internal functions
 */
void FatalErrorLoop(void);

/**
 * @brief Handle system faults
 * @param errType The error type
 * @return None
 */
void FaultHandler(eFAULT_TYPE errType)
{
	// Handle bad error type
	if (errType >= ERR_COUNT)
		errType = ERR_UNKNOWN;

	// Latch error bit
	gSystemErrors |= ((uint64_t)1 << errType);

	// Count faults
	gErrorCount++;

	/**
	 * Fault Type handling
	 */
	switch (errType)
	{
	case ERR_NONE:
		break;


	case ERR_HAL:
	case ERR_HYPERBUS_RAM:
	case ERR_STK_DRIFT:
		/* Fatal Error - Cannot proceed! */
		FatalErrorLoop();
		break;


	case ERR_ADC:
	case ERR_DIAG_UNKNOWN:

		break;

	case ERR_FLASH_ERASE:
	case ERR_FLASH_READ:
	case ERR_FLASH_WRITE:
	case ERR_FLASH_WRITE_ENABLE:
	case ERR_FLASH_SET_CONFIG:
	case ERR_FLASH_READY:
	case ERR_FLASH_TIMEOUT:
		HealthSubsystemBad(eSystemFlash);
		break;


	case ERR_LCD:
	case ERR_STATE_UNKNOWN:
	case ERR_FAULT_CLEAR:
	case ERR_CLK:
	case ERR_AD7124:
		break;

	case ERR_UNKNOWN:
		break;

	default:
		break;

	}  // end switch
}  // end faulthandler

/**
 * @brief Get the current error state
 * @return the current error state
 * ((uint64_t) 1 << eFAULT_TYPE);
 */
uint64_t GetErrorState()
{
	return gSystemErrors;
}

/**
 * @brief Clear all faults in the system
 * @return None
 */
void ClearFaults()
{
	gSystemErrors = 0;
}

/**
 * @brief In the event of a fatal error, the device cannot operate. This loop never exits. Handle diagnostics
 * @return None, does not return!
 */
void FatalErrorLoop()
{
	// Stay in this loop forever, handle diags only
	while (1)
	{
		DIAG_Drive();
		uint32_t sysTick = HAL_GetTick();
		while (sysTick == HAL_GetTick()){sysTick = HAL_GetTick();}
	}
}

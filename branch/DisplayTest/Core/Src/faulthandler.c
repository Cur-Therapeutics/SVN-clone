/********************************************************************
 *
 *   faulthandler.c
 *
 *   Description:    Faulthandling
 *
 *   Copyright NextPhase Medical, Inc. 2018 -- All rights reserved.
 *
 *--------------------------------------------------------------------
 *
 *   Functions:
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

/**
 * System error bit field. ((uint64_t) 1 << eFAULT_TYPE);
 */
uint64_t gSystemErrors = 0;

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

	/**
	 * Fault Type handling
	 */
	switch (errType)
	{
	case ERR_NONE:
		break;

	case ERR_HAL:
	case ERR_ADC:
	case ERR_DIAG_UNKNOWN:
	case ERR_FLASH_ERASE:
	case ERR_FLASH_READ:
	case ERR_FLASH_WRITE:
	case ERR_FLASH_WRITE_ENABLE:
	case ERR_FLASH_SET_CONFIG:
	case ERR_FLASH_READY:
	case ERR_FLASH_TIMEOUT:
	case ERR_LCD_1:
	case ERR_LCD_2:
	case ERR_STK_DRIFT:
	case ERR_STATE_UNKNOWN:
	case ERR_FAULT_CLEAR:
	case ERR_CLK:
	case ERR_I2C:
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


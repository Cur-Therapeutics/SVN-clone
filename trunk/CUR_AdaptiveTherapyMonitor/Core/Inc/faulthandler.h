/********************************************************************
 *
 *   faulthandler.h
 *
 *   Description:    Handles faults
 *
 *   Copyright NextPhase Medical, Inc. 2023 -- All rights reserved.
 *
 *--------------------------------------------------------------------
 *
 *   Revision History:
 *
 *   Rev.    | Date      | Name              | Description
 *   1       | 11/08/18  | Brian Compter     | Created
 *
 ********************************************************************/

#ifndef INC_FAULTHANDLER_H_
#define INC_FAULTHANDLER_H_

#include "main.h"

/**
 * Error types
 */
typedef enum {
	ERR_NONE,
	ERR_HAL,
	ERR_ADC,
	ERR_DIAG_UNKNOWN,
	ERR_FLASH_INIT,
	ERR_FLASH_ERASE,
	ERR_FLASH_READ,
	ERR_FLASH_WRITE,
	ERR_FLASH_WRITE_ENABLE,
	ERR_FLASH_SET_CONFIG,
	ERR_FLASH_READY,
	ERR_FLASH_TIMEOUT,
	ERR_STK_DRIFT,
	ERR_STATE_UNKNOWN,
	ERR_FAULT_CLEAR,
	ERR_CLK,
	ERR_AD7124,
	ERR_LCD,
	ERR_LCD_BLEND,
	ERR_LCD_WRITE,
	ERR_LCD_ADDRESS,
	ERR_ACCEL_COMMS,
	ERR_HYPERBUS_RAM,
	ERR_I2C_TOUCH,
	ERR_TOUCH_CAL,
	ERR_TOUCH_COMMS,
	ERR_UNKNOWN,
	ERR_COUNT
} eFAULT_TYPE;


void FaultHandler(eFAULT_TYPE errType);
uint64_t GetErrorState(void);   // gSystemErrors
void ClearFaults(void);         // gSystemErrors
uint8_t IsFatalFault(void);

#endif /* INC_FAULTHANDLER_H_ */

/********************************************************************
*
*   i2c.h
*
*   Description:    Negotiates access to the I2C bus for the Battery
*   				and Touch drivers
*
*   Copyright PPMD, Inc. 2019 -- All rights reserved.
*
*--------------------------------------------------------------------
*
*   Revision History:
*
*   Rev.    | Date      | Name              | Description
*   1       | 09/06/19  | Brian Compter     | Created.
*
********************************************************************/


#ifndef I2C_H
#define I2C_H

#include "main.h"

/**
 * Reference to our I2C comms handle
 */
extern I2C_HandleTypeDef hi2c3;

/**
 * I2C State
 */
typedef enum
{
	eI2C_IDLE,		// Available for new requests
	eI2C_BUSY,		// Request is being handled
	eI2C_READY,		// Operation is complete and data is ready to be read if available
	eI2C_ERROR
}eI2C_STATE;

/**
 * I2C Operation Result
 */
typedef enum
{
	eI2C_SUCCESS,
	eI2C_FAILED,
}eI2C_RESULT;

/**
 * I2C Operation types
 */
typedef enum
{
	eI2C_NONE,
	eI2C_READ,
	eI2C_WRITE,
	eI2C_READAFTERWRITE,
}eI2C_OPERATION_TYPE;

/**
 * Functions
 */
void I2C_Init();
eI2C_STATE I2C_GetState();
eI2C_STATE I2C_TryLock();
void I2C_Unlock();
eI2C_RESULT I2C_Read(uint16_t address, uint8_t * buffer, uint16_t count);
eI2C_RESULT I2C_Write(uint16_t address, uint8_t * buffer, uint16_t count);
eI2C_RESULT I2C_ReadAfterWrite(uint16_t address, uint8_t * txbuffer, uint16_t txcount, uint8_t * rxbuffer, uint16_t rxcount);

#endif

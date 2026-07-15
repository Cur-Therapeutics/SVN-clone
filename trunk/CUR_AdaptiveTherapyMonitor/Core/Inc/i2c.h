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
 * The structure of an I2C port
 */
typedef struct
{
	I2C_HandleTypeDef * i2c;
	eI2C_STATE 			state;
	eI2C_OPERATION_TYPE opType;
	uint16_t 			savedAddress;
	uint8_t * 			savedRxBuffer;
	uint16_t 			savedRxCount;
} sI2CPort;

/**
 * Functions
 */
void I2C_Init();
eI2C_STATE I2C_GetState(sI2CPort * port);
eI2C_RESULT I2C_Read(sI2CPort * port, uint16_t address, uint8_t * buffer, uint16_t count);
eI2C_RESULT I2C_Write(sI2CPort * port, uint16_t address, uint8_t * buffer, uint16_t count);
eI2C_RESULT I2C_ReadAfterWrite(sI2CPort * port, uint16_t address, uint8_t * txbuffer, uint16_t txcount, uint8_t * rxbuffer, uint16_t rxcount);

eI2C_RESULT I2C_Read_IT(sI2CPort * port, uint16_t address, uint8_t * buffer, uint16_t count);
eI2C_RESULT I2C_Write_IT(sI2CPort * port, uint16_t address, uint8_t * buffer, uint16_t count);

/**
 * Externs
 */
extern I2C_HandleTypeDef hi2c1;
extern I2C_HandleTypeDef hi2c3;
extern sI2CPort sI2CBarometric;
extern sI2CPort sI2CTouch;

#endif

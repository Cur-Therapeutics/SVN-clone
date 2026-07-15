/********************************************************************
*
*   i2c.c
*
*   Description:    Negotiates access to the I2C1 bus
*
*   Copyright PPMD, Inc. 2026 -- All rights reserved.
*
*--------------------------------------------------------------------
*
*   Revision History:
*
*   Rev.    | Date      | Name              | Description
*   1       | 09/06/19  | Brian Compter     | Created.
*
********************************************************************/

#include "i2c.h"
#include "health.h"
#include "barometric.h"

/**
 * I2C Ports
 */
sI2CPort sI2CBarometric = {&hi2c1, eI2C_IDLE, eI2C_NONE, 0, 0, 0};
sI2CPort sI2CTouch = {&hi2c3, eI2C_IDLE, eI2C_NONE, 0, 0, 0};

/**
 * Tracks the state of the bus
 */
eI2C_STATE mState = eI2C_IDLE;

/**
 * Current operation type
 */
eI2C_OPERATION_TYPE mOperationType = eI2C_NONE;

/**
 * Saved parameters to facilitate Read after Write operations
 */
uint16_t mSavedAddress;
uint8_t * mSavedRxbuffer;
uint16_t mSavedRxcount;

/**
 * @brief Initialize the I2C for use, checks subsystem state
 * @return None
 */
void I2C_Init()
{
	if (hi2c3.State != HAL_I2C_STATE_RESET)
		HealthSubsystemGood(eSystemI2C);
	else
		HealthSubsystemBad(eSystemI2C);
}

/**
  * @brief  Get the current state of the I2C controller
  * @retval The I2C state
  */
eI2C_STATE I2C_GetState(sI2CPort * port)
{
	return port->state;
}

/**
  * @brief  Read bytes from the I2C
  * @param port The i2c port
  * @param  address to read from
  * @param  buffer of data to read
  * @param  count The number of bytes to read
  * @retval status of the operation, eI2C_SUCCESS or error code
  */
eI2C_RESULT I2C_Read(sI2CPort * port, uint16_t address, uint8_t * buffer, uint16_t count)
{
	// Kick off read request
	port->opType = eI2C_READ;

	return HAL_I2C_Master_Receive(port->i2c, address, buffer, count, 50);
}

/**
  * @brief  Write bytes to the I2C
  * @param port The i2c port
  * @param  address to write to
  * @param  buffer of data to write
  * @param  count The number of bytes to write
  * @retval status of the operation, eI2C_SUCCESS or error code
  */
eI2C_RESULT I2C_Write(sI2CPort * port, uint16_t address, uint8_t * buffer, uint16_t count)
{
	// Kick off write request
	port->opType = eI2C_WRITE;
	return HAL_I2C_Master_Transmit(port->i2c, address, buffer, count, 50);
}

/**
  * @brief  Read bytes from the I2C
  * @param port The i2c port
  * @param  address to read from
  * @param  buffer of data to read
  * @param  count The number of bytes to read
  * @retval status of the operation, eI2C_SUCCESS or error code
 */
eI2C_RESULT I2C_Read_IT(sI2CPort * port, uint16_t address, uint8_t * buffer, uint16_t count)
{
	// Kick off read request
	port->opType = eI2C_READ;
	return HAL_I2C_Master_Receive_IT(port->i2c, address, buffer, count);
}

/**
  * @brief  Write bytes to the I2C
  * @param port The i2c port
  * @param  address to write to
  * @param  buffer of data to write
  * @param  count The number of bytes to write
  * @retval status of the operation, eI2C_SUCCESS or error code
  */
eI2C_RESULT I2C_Write_IT(sI2CPort * port, uint16_t address, uint8_t * buffer, uint16_t count)
{
	// Kick off write request
	port->opType = eI2C_WRITE;
	return HAL_I2C_Master_Transmit_IT(port->i2c, address, buffer, count);
}

/**
  * @brief  Read bytes after a write operation on the I2C
  * @param port The I2C port to use
  * @param  address to write to
  * @param  buffer of data to write
  * @param  count The number of bytes to write
  * @param  buffer of data to read
  * @param  count The number of bytes to read
  * @retval status of the operation, eI2C_SUCCESS or error code
  */
eI2C_RESULT I2C_ReadAfterWrite(sI2CPort * port, uint16_t address, uint8_t * txBuffer, uint16_t txCount, uint8_t * rxBuffer, uint16_t rxCount)
{
	port->opType		= eI2C_READAFTERWRITE;
	port->savedAddress 	= address;
	port->savedRxBuffer = rxBuffer;
	port->savedRxCount 	= rxCount;
	return I2C_Write(port, address, txBuffer, txCount);
}

/**
  * @brief  Master Tx Transfer completed callback.
  * @note	Replaces weak definition in HAL
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *                the configuration information for the specified I2C.
  * @retval None
  */
void HAL_I2C_MasterTxCpltCallback(I2C_HandleTypeDef *hi2c)
{
	// Ignore I2C ports we don't manage
	if (hi2c == &hi2c3)
	{
		// If we are doing a read after write, we need to kick off the read portion
		if (mOperationType == eI2C_READAFTERWRITE)
		{
			// Write complete, kick off the read portion of the request
			HAL_I2C_Master_Receive_IT(&hi2c3, mSavedAddress, mSavedRxbuffer, mSavedRxcount);
		}
		else
		{
			// Set state to ready and operation none
			mState 			= eI2C_READY;
			mOperationType 	= eI2C_NONE;
		}
	}
	else if (hi2c == &hi2c1)
	{
		BarometricTxCallback(&mBarometricSensor);
	}
}

/**
  * @brief  Master Rx Transfer completed callback.
  * @note	Replaces weak definition in HAL
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *                the configuration information for the specified I2C.
  * @retval None
  */
void HAL_I2C_MasterRxCpltCallback(I2C_HandleTypeDef *hi2c)
{
	// Ignore I2C ports we don't manage
	if (hi2c == &hi2c3)
	{
		// Set state to ready and operation none
		mState 			= eI2C_READY;
		mOperationType 	= eI2C_NONE;
	}
	else if (hi2c == &hi2c1)
	{
		BarometricRxCallback(&mBarometricSensor);
	}
}

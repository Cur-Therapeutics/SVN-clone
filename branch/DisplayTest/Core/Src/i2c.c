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
  * @brief  Get the current state of the I2C controller
  * @retval The I2C state
  */
eI2C_STATE I2C_GetState()
{
	return mState;
}

/**
  * @brief  Attempt to gain access to the I2C resource for communications
  * 		If the controller is idle, the resource is locked by the caller
  * @retval eI2C_Idle on success, eI2C_Busy on failure
  */
eI2C_STATE I2C_TryLock()
{
	// Check state
	if (mState != eI2C_IDLE)
	{
		// Lock failed
		return eI2C_BUSY;
	}
	else
	{
		// Lock the resource and return IDLE
		mState = eI2C_BUSY;
		return eI2C_IDLE;
	}
}

/**
  * @brief  Release I2C port for use by other components
  * @retval None
  */
void I2C_Unlock()
{
	mState = eI2C_IDLE;
}

/**
  * @brief  Read bytes from the I2C
  * @param  address to write to
  * @param  buffer of data to read
  * @param  count The number of bytes to read
  * @retval status of the operation, eI2C_SUCCESS or error code
  */
eI2C_RESULT I2C_Read(uint16_t address, uint8_t * buffer, uint16_t count)
{
	// Kick off read request
	mOperationType = eI2C_READ;
	return HAL_I2C_Master_Receive_IT(&hi2c1, address, buffer, count);
}

/**
  * @brief  Write bytes to the I2C
  * @param  address to write to
  * @param  buffer of data to write
  * @param  count The number of bytes to write
  * @retval status of the operation, eI2C_SUCCESS or error code
  */
eI2C_RESULT I2C_Write(uint16_t address, uint8_t * buffer, uint16_t count)
{
	// Kick off write request
	mOperationType = eI2C_WRITE;
	return HAL_I2C_Master_Transmit_IT(&hi2c1, address, buffer, count);
}

/**
  * @brief  Read bytes after a write operation on the I2C
  * @param  address to write to
  * @param  buffer of data to write
  * @param  count The number of bytes to write
  * @param  buffer of data to read
  * @param  count The number of bytes to read
  * @retval status of the operation, eI2C_SUCCESS or error code
  */
eI2C_RESULT I2C_ReadAfterWrite(uint16_t address, uint8_t * txBuffer, uint16_t txCount, uint8_t * rxBuffer, uint16_t rxCount)
{
	mOperationType	= eI2C_READAFTERWRITE;
	mSavedAddress 	= address;
	mSavedRxbuffer 	= rxBuffer;
	mSavedRxcount 	= rxCount;
	return I2C_Write(address, txBuffer, txCount);
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
	if (hi2c != &hi2c1)
		return;

	// If we are doing a read after write, we need to kick off the read portion
	if (mOperationType == eI2C_READAFTERWRITE)
	{
		// Write complete, kick off the read portion of the request
		HAL_I2C_Master_Receive_IT(&hi2c1, mSavedAddress, mSavedRxbuffer, mSavedRxcount);
	}
	else
	{
		// Set state to ready and operation none
		mState 			= eI2C_READY;
		mOperationType 	= eI2C_NONE;
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
	if (hi2c != &hi2c1)
		return;

	// Set state to ready and operation none
	mState 			= eI2C_READY;
	mOperationType 	= eI2C_NONE;
}

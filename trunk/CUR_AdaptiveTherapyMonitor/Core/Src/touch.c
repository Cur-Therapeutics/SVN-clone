/********************************************************************
*
*   touch.c
*
*   Description:    Controls a TS2007 Touch Screen Controller
*
*   Copyright PPMD, Inc. 2026 -- All rights reserved.
*
*--------------------------------------------------------------------
*
*   Revision History:
*
*   Rev.    | Date      | Name              | Description
*   1       | 09/05/19  | Brian Compter     | Created.
*
********************************************************************/

#include "main.h"
#include "touch.h"
#include "health.h"
#include "i2c.h"
#include "lcd.h"
#include "display.h"
#include "faulthandler.h"

/**
 * Touch state
 */
eTouchState mTouchState = eTOUCH_IDLE;

/**
 * The touch screen calibration
 */
sTouchCalibration mTouchCal;

/**
 * Signals a touch event and is automatically cleared when read!
 */
uint8_t mTouchEvent = 0;

/**
 * Last touch coordinates
 */
uint16_t mLastXTouch	= 0;
uint16_t mLastYTouch 	= 0;
uint16_t mLastXTouchRaw = 0;	// Raw data is in adc counts
uint16_t mLastYTouchRaw = 0;	// ...

/**
 * Debounce variables
 */
uint8_t mDebounceTimer = 0;
#define TOUCH_DEBOUNCE	50

/**
 * Debug cooldown
 */
uint8_t mDebugCooldown = 0;
#define TOUCH_COOLDOWN	50

/**
 * Touch targets
 */
/* TBD */

/**
  * @brief  Initialize the touch chip for operation
  * @retval None
  */
void TOUCH_Init()
{
	HealthSubsystemGood(eSystemTouch);

	// Verify touch comms, any generated faults will set touch health
	TOUCH_Read(TOUCH_MEASURE_X);

	// Initialize member variables
	mLastXTouch = 0;
	mLastYTouch = 0;

	// Fetch and validate calibration from flash slot 16
	/*FLA_Read(TOUCH_CAL_FLASH_ADDR, (uint8_t *)&mTouchCal, sizeof(mTouchCal));
	if (mTouchCal.xMax > 5000 || mTouchCal.yMax > 5000 || mTouchCal.xMin == 0xFFFF || mTouchCal.yMin == 0xFFFF)
	{
		// Setup defaults
		mTouchCal.xMax = 3800;
		mTouchCal.xMin = 275;
		mTouchCal.yMax = 3800;
		mTouchCal.yMin = 275;
	}*/
}

/**
  * @brief  Drive the touch interface and handle touches and debouncing
  * @retval None
  */
void TOUCH_Drive()
{
	GPIO_PinState touchDetected = HAL_GPIO_ReadPin(TOUCH_INT_GPIO_Port, TOUCH_INT_Pin);

	// Detect activity
	if (touchDetected == GPIO_PIN_RESET)
	{
		//Activity_Kick();
	}

	switch (mTouchState)
	{
		case eTOUCH_IDLE:
			HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, 0);
			if (touchDetected == GPIO_PIN_RESET)
			{
				mTouchState = eTOUCH_DOWN;	// Update state
				mDebounceTimer = 0;			// Clear debounce

				// Read and store x/y coordinates
				mLastXTouch = TOUCH_X();
				mLastYTouch = TOUCH_Y();

				mTouchEvent = 1;			// Signal event
			}

			break;
		case eTOUCH_DOWN:
			HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, 1);
			if (touchDetected == GPIO_PIN_RESET)
			{
				mDebounceTimer = 0;			// Clear debounce
			}
			else
			{
				if (mDebounceTimer++ > TOUCH_DEBOUNCE)
				{
					mTouchState = eTOUCH_IDLE;	// Update state
					mDebounceTimer = 0;			// Clear debounce
				}
			}
			break;

		case eTOUCH_DEBUG:

			if (touchDetected == GPIO_PIN_RESET)
			{
				if (mDebugCooldown != 0)
				{
					mDebugCooldown--;
					break;
				}
				mDebugCooldown = TOUCH_COOLDOWN;

				// Read and store x/y coordinates
				mLastXTouch = TOUCH_X();
				mLastYTouch = TOUCH_Y();

				// Draw to frame buffer DEBUG
				LCD_Draw(mLastXTouch, mLastYTouch, colorRed);
			}

			break;
	}
}

/**
  * @brief  Determines if a touch event matches a touch target
  * @param	target The touch target to check
  * @param	The touch x coordinate
  * @param	The touch y coordinate
  * @retval True if the supplied touch coordinates match the touch target
  */
uint8_t TOUCH_TargetActive(sTouchTarget target, uint16_t x, uint16_t y)
{
	if (x < target.x + target.width)
	{
		if (x > target.x)
		{
			if (y < target.y + target.height)
			{
				if (y > target.y)
				{
					return 1;
				}
			}
		}
	}

	return 0;
}

/**
  * @brief  Detects touch events
  * @note	This flag self clears when read.
  * @retval True if a touch event has occurred
  */
uint8_t TOUCH_Event()
{
	if (mTouchEvent == 0)
		return 0;

	mTouchEvent = 0;	// Clear flag after reading
	return 1;
}

/**
  * @brief  Get the last x touch
  * @retval The last X touch coordinate
  */
uint16_t TOUCH_LastX()
{
	return mLastXTouch;
}

/**
  * @brief  Get the last y touch
  * @retval The last Y touch coordinate
  */
uint16_t TOUCH_LastY()
{
	return mLastYTouch;
}

/**
  * @brief  Get the last x touch in adc counts
  * @retval The last X touch coordinate
  */
uint16_t TOUCH_LastXRaw()
{
	return mLastXTouchRaw;
}

/**
  * @brief  Get the last y touch in adc counts
  * @retval The last Y touch coordinate
  */
uint16_t TOUCH_LastYRaw()
{
	return mLastYTouchRaw;
}

/**
  * @brief  Enter an IDLE state
  * @retval None
  */
void TOUCH_Idle()
{
	eI2C_STATE i2cState = I2C_TryLock();
	if (i2cState != eI2C_IDLE)
	{
		return;
	}

	// Send idle command
	uint8_t cmd = TOUCH_SETUP_IDLE;
	I2C_Write(TOUCH_SLAVE_ADDRESS, &cmd, 1);

	I2C_Unlock();
}

/**
  * @brief  Initiate a conversion and read the result
  * @param	The command to send
  * @retval The touch position
  */
uint16_t TOUCH_Read(uint8_t cmd)
{
	eI2C_STATE i2cState = I2C_TryLock();
	if (i2cState != eI2C_IDLE)
	{
		FaultHandler(ERR_I2C_TOUCH);
		HealthSubsystemBad(eSystemTouch);
		return 0;
	}

	// Start conversion
	uint8_t retval = HAL_OK;
	retval |= HAL_I2C_Master_Transmit(&hi2c3, TOUCH_SLAVE_ADDRESS, &cmd, 1, TOUCH_TIMEOUT);
	if (retval != HAL_OK)
	{
		FaultHandler(ERR_TOUCH_COMMS);
		HealthSubsystemBad(eSystemTouch);
		I2C_Unlock();
		return 0;
	}

	for (int i  = 0; i < TOUCH_READ_DELAY; i++) {}

	// Read the data
	uint16_t result;
	uint8_t readData[2];
	retval |= HAL_I2C_Master_Receive(&hi2c3, TOUCH_SLAVE_ADDRESS + 1, (uint8_t*)readData, 2, TOUCH_TIMEOUT);
	if (retval != HAL_OK)
	{
		FaultHandler(ERR_TOUCH_COMMS);
		HealthSubsystemBad(eSystemTouch);
		I2C_Unlock();
		return 0;
	}

	result = readData[0] << 4;
	result |= readData[1] >> 4;

	I2C_Unlock();
	return result;
}

/**
  * @brief  Read the current X position
  * @retval The touch position
  */
uint16_t TOUCH_X()
{
	mLastXTouchRaw = TOUCH_Read(TOUCH_MEASURE_Y);
	float xPosition = mLastXTouchRaw;

	// Check divisor
	if (mTouchCal.xMax-mTouchCal.xMin == 0)
	{
		FaultHandler(ERR_TOUCH_CAL);
		return 0;
	}

	// Translate to the screen size
	float scale = ((float)DISPLAY_HEIGHT) / ((float)(mTouchCal.xMax-mTouchCal.xMin));
	xPosition = (xPosition - mTouchCal.xMin) * scale;

	xPosition = DISPLAY_HEIGHT - xPosition;	// Flip coordinates
	if (xPosition > DISPLAY_HEIGHT)
		xPosition = 0;

	return (uint16_t)xPosition;
}

/**
  * @brief  Read the current Y position
  * @retval The touch position
  */
uint16_t TOUCH_Y()
{
	mLastYTouchRaw = TOUCH_Read(TOUCH_MEASURE_X);
	float yPosition = mLastYTouchRaw;

	// Check divisor
	if (mTouchCal.yMax-mTouchCal.yMin == 0)
	{
		FaultHandler(ERR_TOUCH_CAL);
		return 0;
	}

	// Translate to the screen size
	float scale = ((float)DISPLAY_WIDTH) / ((float)(mTouchCal.yMax-mTouchCal.yMin));
	yPosition = (yPosition - mTouchCal.yMin) * scale;

	yPosition = DISPLAY_WIDTH - yPosition;	// Flip coordinates
	if (yPosition > DISPLAY_WIDTH)
		yPosition = 0;

	return (uint16_t)yPosition;
}

/**
  * @brief  Get the current touch operating mode
  * @retval The current mode
  */
uint8_t TOUCH_GetMode()
{
	return mTouchState;
}

/**
  * @brief  Set the touch mode of operation
  * @param mode The mode to set to.  Currently the only valid modes are normal and debug
  * @retval none
  */
void TOUCH_SetMode(uint8_t mode)
{
	mTouchState = mode;
}

/**
  * @brief  Get the current touch calibration
  * @retval The touch calibration
  */
sTouchCalibration TOUCH_GetCal()
{
	return mTouchCal;
}

/**
  * @brief  Set and store a new touch calibration
  * @param The calibration to set
  * @retval none
  */
void TOUCH_SetCal(sTouchCalibration cal)
{
	mTouchCal = cal;

	// Store calibration
	//FLA_EraseSegment(TOUCH_CAL_FLASH_ADDR);
	//FLA_Write(TOUCH_CAL_FLASH_ADDR, (uint8_t*)&mTouchCal, sizeof(mTouchCal));
}

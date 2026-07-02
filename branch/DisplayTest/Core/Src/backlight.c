/********************************************************************
*
*   backlight.c
*
*   Description:    Manages the backlight through a PWM timer
*
*   Copyright NextPhase Medical, Inc. 2026 -- All rights reserved.
*
*--------------------------------------------------------------------
*
*   Revision History:
*
*   Rev.    | Date      | Name              | Description
*   1       | 12/27/23  | Brian Compter     | Created.
*
********************************************************************/

#include "main.h"
#include "backlight.h"

/**
 * Backlight settings
 */
uint16_t mBacklightValue;
uint16_t mBacklightTarget;

/**
 * Backlight timer
 */
uint16_t mBacklightTimer = BACKLIGHT_TIMER;

/**
 * Reference to our PWM timer resource
 */
extern TIM_HandleTypeDef htim8;

/**
 * @brief Initialize the backlight
 */
void BacklightInit()
{
	mBacklightValue = BACKLIGHT_DIM;
	mBacklightTarget = BACKLIGHT_FULL;
	BacklightSet(mBacklightValue);
	BacklightOn();
}

/**
 * @brief Fade backlight transitions
 * @return None
 */
void BacklightDrive()
{
	// Timer
	if (mBacklightTimer++ < BACKLIGHT_TIMER)
		return;
	mBacklightTimer = 0;

	//  Nothing to do if we are at our target
	if (mBacklightValue == mBacklightTarget)
		return;

	// Update the value, move towards the target
	if (mBacklightValue < mBacklightTarget)
	{
		if (mBacklightTarget - mBacklightValue > BACKLIGHT_SPEED)
			mBacklightValue += BACKLIGHT_SPEED;
		else
			mBacklightValue = mBacklightTarget;
	}
	else
	{
		if (mBacklightValue - mBacklightTarget > BACKLIGHT_SPEED)
			mBacklightValue -= BACKLIGHT_SPEED;
		else
			mBacklightValue = mBacklightTarget;
	}

	BacklightSet(mBacklightValue);
}

/**
 * @brief Turn the backlight on
 * @return None
 */
void BacklightOn()
{
	HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_1);
}

/**
 * @brief Turn the backlight off
 * @return None
 */
void BacklightOff()
{
	HAL_TIM_PWM_Stop(&htim8, TIM_CHANNEL_1);
}

/**
 * @brief Set the backlight value
 * @param val The backlight value
 * @return None
 */
void BacklightSet(uint16_t val)
{
	if (val  > BACKLIGHT_FULL)
		val = BACKLIGHT_FULL;

	TIM_OC_InitTypeDef sConfigOC = {0};
	HAL_TIM_PWM_Stop(&htim8, TIM_CHANNEL_1);
	sConfigOC.OCMode = TIM_OCMODE_PWM1;
	sConfigOC.Pulse = val;
	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
	sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
	if (HAL_TIM_PWM_ConfigChannel(&htim8, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
	{
		// Set fault, todo
		return;
	}
	HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_1);
}

/**
 * @brief Set the backlight value target
 * @param val The backlight value
 * @return None
 */
void BacklightTarget(uint16_t val)
{
	if (val  > BACKLIGHT_FULL)
		val = BACKLIGHT_FULL;
	mBacklightTarget = val;
}

/**
 * @brief Check if backlight is at target
 * @return None
 */
uint8_t BacklightAtTarget(void)
{
	return (mBacklightValue == mBacklightTarget);
}

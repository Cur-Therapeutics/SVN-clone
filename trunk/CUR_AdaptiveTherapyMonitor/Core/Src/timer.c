/********************************************************************
 *
 *   timer.c
 *
 *   Description:    Handles timer functions
 *
 *   Copyright Arterex Medical, Inc. 2026 -- All rights reserved.
 *
 *--------------------------------------------------------------------
 *
 *   Revision History:
 *
 *   Rev.    | Date      | Name              | Description
 *   1       | 07/10/26  | Brian Compter     | Created.
 *
 ********************************************************************/

#include "main.h"
#include "timer.h"
#include "gpio.h"
#include "datalog.h"

/**
 * @brief TIM Callback function
 * @param htim Pointer to the timer handle
 * @return None
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim != &htim2)
		return;

	// Save data to log
	DataLogSaveSample();

	// LED Debug
	GpioToggle(&sGpioLedGp2);
}


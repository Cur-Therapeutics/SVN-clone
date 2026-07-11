/********************************************************************
 *
 *   main_cur.c
 *
 *   Description:    Main entry point for the application
 *
 *   Copyright NextPhase Medical, Inc. 2026 -- All rights reserved.
 *
 *--------------------------------------------------------------------
 *
 *   Revision History:
 *
 *   Rev.    | Date      | Name              | Description
 *   1       | 05/28/26  | Brian Compter     | Created.
 *
 ********************************************************************/

#include "faulthandler.h"
#include "diagnostics.h"
#include "gpio.h"
#include "hyperbusram.h"
#include "string.h"
#include "backlight.h"
#include "lcd.h"
#include "health.h"
#include "stack_check.h"
#include "ospiflash.h"
#include "ad7124.h"
#include "main.h"
#include "statemachine.h"
#include "display.h"

/**
 * System tick
 */
uint32_t gSystemTick = 0;

/**
 * Track skipped ticks
 */
uint32_t gSkippedTicks = 0;

/**
 * Used for measuring idle time
 */
uint32_t gIdleTicks 		= 0;
uint32_t gLastIdleTicks 	= 0;
uint32_t gMinIdleTicks 		= !0;
uint32_t gMaxIdleTicks 		= 0;

/**
 * LED Toggle
 */
uint16_t mSecondTimer		= 0;

/**
 * @brief Main entry point of our application
 * @note This function DOES NOT RETURN
 */
void main_cur()
{
	// Subsystem initialization
	HealthInit();
	//HyperbusInit();
	//FlashInit();
	DIAG_Init();
	//BacklightInit();
	//SpiInit();
	//AD7124_Init();
	//StateInit();

	//sColor c = {255, 0, 255};
	//LCD_FillWindow(LCD_GetDisplayIndex(), c);

	// Begin loop on start of system tick
	gSystemTick = HAL_GetTick();
	while (gSystemTick == HAL_GetTick()) { /*  */ }

	while (1)
	{
		StackCheck();
		gSystemTick = HAL_GetTick();

		DIAG_Drive();
		//BacklightDrive();
		//AD7124_Drive();
		//RTC_Drive();
		//LCD_Drive();
		//StateDrive();
		//DisplayDrive(GetCurrentState());

		// Wait for next tick
		WaitForNextTick(HAL_GetTick());

	}  // end while


}  // end main_cur

/**
 * @brief Wait for the next tick
 * @param timeNow The current system tick
 * @return None
 */
void WaitForNextTick(uint32_t timeNow)
{
	if (timeNow != HAL_GetTick())
	{
		// We missed a tick!
		gSkippedTicks += HAL_GetTick() - timeNow;
		gIdleTicks = 0;
		gLastIdleTicks = 0;
	}
	else
	{
		// Wait for the next tick, track idle time
		gIdleTicks = 0;
		while(timeNow == HAL_GetTick())
		{
			gIdleTicks++;
		}
		gLastIdleTicks = gIdleTicks;

		// Update min/max idle ticks
		if (gLastIdleTicks > gMaxIdleTicks)
			gMaxIdleTicks = gLastIdleTicks;
		else if (gLastIdleTicks < gMinIdleTicks)
			gMinIdleTicks = gLastIdleTicks;
	}

	// Toggle led if we have crossed over a second
	if (mSecondTimer++ > TICKS_PER_SECOND)
	{
		mSecondTimer = 0;
		GpioToggle(&sGpioLedGreen);
	}
}

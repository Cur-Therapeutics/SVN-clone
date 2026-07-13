/********************************************************************
*
*   display.c
*
*   Description:    Control the presentation on the screen
*
*   Copyright NextPhase Medical, Inc. 2026 -- All rights reserved.
*
*--------------------------------------------------------------------
*
*   Revision History:
*
*   Rev.    | Date      | Name              | Description
*   1       | 06/13/26  | Brian Compter     | Created.
*
********************************************************************/

#include "main.h"
#include "display.h"
#include "object.h"
#include "pressure.h"
#include "ospiflash.h"
#include "lcd.h"

/**
 * Display Object Queue
 */

/**
 * Display objects
 */
sDisplayObject objCurLogo 				= { {0 ,0 , eDISPLAY_WindowAssets01},{0,0,eDISPLAY_FrameBuffer0},{0,0,eDISPLAY_FrameBuffer0},{202, 204}, 0,5,ePATTERN_None};
sDisplayObject objAlert 				= { {202 ,0 , eDISPLAY_WindowAssets01},{0,0,eDISPLAY_FrameBuffer0},{0,0,eDISPLAY_FrameBuffer0},{86, 86}, 0,1,ePATTERN_None};
sDisplayObject objElapsed 				= { {202 ,86 , eDISPLAY_WindowAssets01},{0,0,eDISPLAY_FrameBuffer0},{0,0,eDISPLAY_FrameBuffer0},{79, 14}, 0,1,ePATTERN_None};
sDisplayObject objBaselinePressure 		= { {0 ,205 , eDISPLAY_WindowAssets01},{0,0,eDISPLAY_FrameBuffer0},{0,0,eDISPLAY_FrameBuffer0},{186, 34}, 0,1,ePATTERN_None};
sDisplayObject objReadyToConnect 		= { {0 ,0 , eDISPLAY_WindowAssets02},{0,0,eDISPLAY_FrameBuffer0},{0,0,eDISPLAY_FrameBuffer0},{172, 72}, 0,1,ePATTERN_None};
sDisplayObject objBatteryLow 			= { {0 ,72 , eDISPLAY_WindowAssets02},{0,0,eDISPLAY_FrameBuffer0},{0,0,eDISPLAY_FrameBuffer0},{167, 28}, 0,2,ePATTERN_Vertical};
sDisplayObject objSelfTest 				= { {0 ,129 , eDISPLAY_WindowAssets02},{0,0,eDISPLAY_FrameBuffer0},{0,0,eDISPLAY_FrameBuffer0},{157, 36}, 0,1,ePATTERN_None};
sDisplayObject objConnection 			= { {0 ,165 , eDISPLAY_WindowAssets02},{0,0,eDISPLAY_FrameBuffer0},{0,0,eDISPLAY_FrameBuffer0},{201, 34}, 0,1,ePATTERN_None};
sDisplayObject objSelectPressureUnits 	= { {0 ,199 , eDISPLAY_WindowAssets02},{0,0,eDISPLAY_FrameBuffer0},{0,0,eDISPLAY_FrameBuffer0},{222, 16}, 0,1,ePATTERN_None};
sDisplayObject objFailed 				= { {172 ,0 , eDISPLAY_WindowAssets02},{0,0,eDISPLAY_FrameBuffer0},{0,0,eDISPLAY_FrameBuffer0},{102, 37}, 0,1,ePATTERN_None};
sDisplayObject objBad 					= { {172 ,37 , eDISPLAY_WindowAssets02},{0,0,eDISPLAY_FrameBuffer0},{0,0,eDISPLAY_FrameBuffer0},{70, 35}, 0,1,ePATTERN_None};
sDisplayObject objUnitsLarge 			= { {168 ,79 , eDISPLAY_WindowAssets02},{0,0,eDISPLAY_FrameBuffer0},{0,0,eDISPLAY_FrameBuffer0},{81, 27}, 0,3,ePATTERN_Vertical};
sDisplayObject objUnitsSmall 			= { {249 ,37 , eDISPLAY_WindowAssets02},{0,0,eDISPLAY_FrameBuffer0},{0,0,eDISPLAY_FrameBuffer0},{57, 14}, 0,3,ePATTERN_Vertical};
sDisplayObject objMmHgBlock 			= { {0 ,0 , eDISPLAY_WindowAssets03},{0,0,eDISPLAY_FrameBuffer0},{0,0,eDISPLAY_FrameBuffer0},{107, 104}, 0,2,ePATTERN_Vertical};
sDisplayObject objKpaBlock 				= { {107 ,0 , eDISPLAY_WindowAssets03},{0,0,eDISPLAY_FrameBuffer0},{0,0,eDISPLAY_FrameBuffer0},{106, 104}, 0,2,ePATTERN_Vertical};
sDisplayObject objPsiBlock 				= { {213 ,0 , eDISPLAY_WindowAssets03},{0,0,eDISPLAY_FrameBuffer0},{0,0,eDISPLAY_FrameBuffer0},{107, 104}, 0,2,ePATTERN_Vertical};
sDisplayObject objStartFinishBar 		= { {0 ,0 , eDISPLAY_WindowAssets04},{0,0,eDISPLAY_FrameBuffer0},{0,0,eDISPLAY_FrameBuffer0},{320, 53}, 0,4,ePATTERN_Vertical};
sDisplayObject objSmallNumbers 			= { {0 ,212 , eDISPLAY_WindowAssets04},{0,0,eDISPLAY_FrameBuffer0},{0,0,eDISPLAY_FrameBuffer0},{11, 14}, 0,10,ePATTERN_Horizontal};
sDisplayObject objSmallNumberColon 		= { {113 ,212 , eDISPLAY_WindowAssets04},{0,0,eDISPLAY_FrameBuffer0},{0,0,eDISPLAY_FrameBuffer0},{5, 14}, 0,1,ePATTERN_None};
sDisplayObject objNumLargeZero 			= { {0 ,0 , eDISPLAY_WindowAssets05},{0,0,eDISPLAY_FrameBuffer0},{0,0,eDISPLAY_FrameBuffer0},{66, 106}, 0,1,ePATTERN_None};
sDisplayObject objNumLargeOne 			= { {66 ,0 , eDISPLAY_WindowAssets05},{0,0,eDISPLAY_FrameBuffer0},{0,0,eDISPLAY_FrameBuffer0},{66, 106}, 0,1,ePATTERN_None};
sDisplayObject objNumLargeTwo 			= { {132 ,0 , eDISPLAY_WindowAssets05},{0,0,eDISPLAY_FrameBuffer0},{0,0,eDISPLAY_FrameBuffer0},{66, 106}, 0,1,ePATTERN_None};
sDisplayObject objNumLargeThree 		= { {198 ,0 , eDISPLAY_WindowAssets05},{0,0,eDISPLAY_FrameBuffer0},{0,0,eDISPLAY_FrameBuffer0},{66, 106}, 0,1,ePATTERN_None};
sDisplayObject objNumLargeFour 			= { {0 ,106 , eDISPLAY_WindowAssets05},{0,0,eDISPLAY_FrameBuffer0},{0,0,eDISPLAY_FrameBuffer0},{66, 106}, 0,1,ePATTERN_None};
sDisplayObject objNumLargeFive 			= { {66 ,106 , eDISPLAY_WindowAssets05},{0,0,eDISPLAY_FrameBuffer0},{0,0,eDISPLAY_FrameBuffer0},{66, 106}, 0,1,ePATTERN_None};
sDisplayObject objNumLargeSix 			= { {132 ,106 , eDISPLAY_WindowAssets05},{0,0,eDISPLAY_FrameBuffer0},{0,0,eDISPLAY_FrameBuffer0},{66, 106}, 0,1,ePATTERN_None};
sDisplayObject objNumLargeSeven 		= { {198 ,106 , eDISPLAY_WindowAssets05},{0,0,eDISPLAY_FrameBuffer0},{0,0,eDISPLAY_FrameBuffer0},{66, 106}, 0,1,ePATTERN_None};
sDisplayObject objNumLargeEight 		= { {0 ,0 , eDISPLAY_WindowAssets06},{0,0,eDISPLAY_FrameBuffer0},{0,0,eDISPLAY_FrameBuffer0},{66, 106}, 0,1,ePATTERN_None};
sDisplayObject objNumLargeNine 			= { {0 ,106 , eDISPLAY_WindowAssets06},{0,0,eDISPLAY_FrameBuffer0},{0,0,eDISPLAY_FrameBuffer0},{66, 106}, 0,1,ePATTERN_None};
sDisplayObject objMeasuringComplete 	= { {66 ,0 , eDISPLAY_WindowAssets06},{0,0,eDISPLAY_FrameBuffer0},{0,0,eDISPLAY_FrameBuffer0},{207, 81}, 0,1,ePATTERN_None};
sDisplayObject objPressureDataSaved 	= { {66 ,81 , eDISPLAY_WindowAssets06},{0,0,eDISPLAY_FrameBuffer0},{0,0,eDISPLAY_FrameBuffer0},{150, 36}, 0,1,ePATTERN_None};

/**
 * Overlay state for double buffering
 */
uint8_t mBufferState = BUFFER_WINDOW_A;

/**
 * Internal functions
 */
void _DisplayRenderBaselinePressure(uint32_t press);
void _DisplayRenderPressure(uint32_t press);

/**
 * @brief Prepare the display for use, load flash images to RAM
 * @return None
 */
void DisplayInit()
{
	// Fill with white
	LCD_FillWindow(mBufferState, colorWhite);

	// Load assets from flash to RAM
	DisplayLoadFromFlash(0, eDISPLAY_WindowAssets01);
	DisplayLoadFromFlash(1, eDISPLAY_WindowAssets02);
	DisplayLoadFromFlash(2, eDISPLAY_WindowAssets03);
	DisplayLoadFromFlash(3, eDISPLAY_WindowAssets04);
	DisplayLoadFromFlash(4, eDISPLAY_WindowAssets05);
	DisplayLoadFromFlash(5, eDISPLAY_WindowAssets06);
	DisplayLoadFromFlash(6, eDISPLAY_WindowAssets07);
}

/**
 * @brief Perform display behaviors
 * @param currentState
 * @return None
 */
void DisplayDrive(eSystemStates currentState)
{

}

/**
 * @brief Update the display based on the current state
 * @return None
 */
void DisplayUpdate()
{
	// Get the current state, skip
	eSystemStates state = GetCurrentState();
	if (state == eSTATE_TEST)
		return;

	// Flip our buffer and clear it
	mBufferState ^= 1;

	// Render display
	switch (state)
	{
		case eSTATE_POST:
			LCD_FillWindow(mBufferState, colorWhite);
			break;

		case eSTATE_SPLASH:
			LCD_FillWindow(mBufferState, colorWhite);
			ObjectDraw(objCurLogo, 0, 0, 0);
			break;

		case eSTATE_READY_TO_CONNECT:
			LCD_FillWindow(mBufferState, colorBlue);
			ObjectDraw(objBaselinePressure, 0, 0, 0);

			// Baseline pressure
			_DisplayRenderBaselinePressure(GetBaselinePressure());

			break;

		case eSTATE_SELECT_UNITS:
			LCD_FillWindow(mBufferState, colorBlue);
			ObjectDraw(objSelectPressureUnits, 0, 0, 0);

			objMmHgBlock.state = eUnitBlockState_Default;
			ObjectDraw(objMmHgBlock, 0, 0, 0);

			objKpaBlock.state = eUnitBlockState_Default;
			ObjectDraw(objKpaBlock, 0, 0, 0);

			objPsiBlock.state = eUnitBlockState_Default;
			ObjectDraw(objPsiBlock, 0, 0, 0);

			objStartFinishBar.state = eObjStartFinishBarState_StartMeasureingInActive;
			ObjectDraw(objStartFinishBar, 0, 0, 0);

			break;

		case eSTATE_MEASURING:
			LCD_FillWindow(mBufferState, colorBlue);


			break;

		case eSTATE_COMPLETE:
			LCD_FillWindow(mBufferState, colorBlue);
			ObjectDraw(objMeasuringComplete, 0, 0, 0);
			break;

		case eSTATE_TEST:
			LCD_FillWindow(mBufferState, colorBlack);
			break;

		case eSTATE_ERROR:
			LCD_FillWindow(mBufferState, colorRed);
			ObjectDraw(objAlert, 0, 0, 0);
			break;
	}

	// Swap buffers
	LCD_SetDisplayWindow(mBufferState);
}

/**
 *
 */
void DisplayQueueObject(sObjectQueueItem item)
{

}

/**
 * @brief Load image data from flash to our RAM framebuffer
 * @param flashSlot The slot in flash to
 * @param window The framebuffer window index to load into
 *
 * @note Please review data section of the SDD for specific details on how addresses are calculated from slot and window
 *
 * @return None
 */
void DisplayLoadFromFlash(uint32_t flashSlot, eDisplayWindow window)
{
	uint32_t flashAddr = ( flashSlot * ( 2 * FLASH_SECTOR_SIZE) ) + FLASH_IMAGE_START_ADDRESS;
	uint32_t displayAddr = gDisplays[window];
	FlashRead(flashAddr, (uint8_t*)displayAddr, FRAMEBUFFER_SIZE);
}

/**
 * @brief Display the baseline pressure
 * @param press The pressure to display
 * @return None
 */
void _DisplayRenderBaselinePressure(uint32_t press)
{
	// Thousands
	if (press > 999)
	{
		uint32_t thousands = (press / 1000);
		objSmallNumbers.state = thousands;
		if (thousands > 0) ObjectDraw(objSmallNumbers, 0, 0, 0);
		press -= (thousands);
	}

	// Hundreds
	if (press > 99)
	{
		uint32_t hundreds = (press / 100);
		objSmallNumbers.state = hundreds;
		ObjectDraw(objSmallNumbers, 0, objSmallNumbers.shape.width, 0);
		press -= (hundreds);
	}

	// Tens
	if (press > 9)
	{
		uint32_t tens = (press / 10);
		objSmallNumbers.state = tens;
		ObjectDraw(objSmallNumbers, 0, objSmallNumbers.shape.width*2, 0);
		press -= (tens);
	}

	// Ones
	objSmallNumbers.state = press;
	ObjectDraw(objSmallNumbers, 0, objSmallNumbers.shape.width*3, 0);
}

/**
 * @brief Display the main pressure
 * @param press The pressure to display
 * @return None
 */
void _DisplayRenderPressure(uint32_t press)
{
	/*
objNumLargeZero
objNumLargeOne
objNumLargeTwo
objNumLargeThree
objNumLargeFour
objNumLargeFive
objNumLargeSix
objNumLargeSeven
objNumLargeEight
objNumLargeNine
	*/

	// Thousands
	if (press > 999)
	{
		uint32_t thousands = (press / 1000);
		objSmallNumbers.state = thousands;
		if (thousands > 0) ObjectDraw(objSmallNumbers, 0, 0, 0);
		press -= (thousands);
	}

	// Hundreds
	if (press > 99)
	{
		uint32_t hundreds = (press / 100);
		objSmallNumbers.state = hundreds;
		ObjectDraw(objSmallNumbers, 0, objSmallNumbers.shape.width, 0);
		press -= (hundreds);
	}

	// Tens
	if (press > 9)
	{
		uint32_t tens = (press / 10);
		objSmallNumbers.state = tens;
		ObjectDraw(objSmallNumbers, 0, objSmallNumbers.shape.width*2, 0);
		press -= (tens);
	}

	// Ones
	objSmallNumbers.state = press;
	ObjectDraw(objSmallNumbers, 0, objSmallNumbers.shape.width*3, 0);
}

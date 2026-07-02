/********************************************************************
*
*   display.h
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
#ifndef INC_DISPLAY_H_
#define INC_DISPLAY_H_

#include "statemachine.h"
#include "object.h"

/**
 * Window indexes used for double buffering / overlay
 */
#define BUFFER_WINDOW_A	0
#define BUFFER_WINDOW_B	1
#define BUFFER_OVERLAY	2

/**
 * Display windows
 */
typedef enum
{
	eDISPLAY_FrameBuffer0,		// 0
	eDISPLAY_FrameBuffer1,		// 1
	eDISPLAY_Overlay,			// 2
	eDISPLAY_WindowAssets01,	// 3
	eDISPLAY_WindowAssets02,	// 4
	eDISPLAY_WindowAssets03,	// 5
	eDISPLAY_WindowAssets04,	// 6
	eDISPLAY_WindowAssets05,	// 7
	eDISPLAY_WindowAssets06,	// 8
	eDISPLAY_WindowAssets07,	// 9
	eDISPLAY_WindowAssets08,	// 10
	eDISPLAY_WindowAssets09,	// 11
	eDISPLAY_WindowAssets10,	// 12
	eDISPLAY_WindowAssets11,	// 13
	eDISPLAY_WindowAssets12,	// 14
	eDISPLAY_WindowAssets13,	// 15
	eDISPLAY_WindowAssets14,	// 16
	eDISPLAY_WindowAssets15,	// 17
} eDisplayWindow;

/**
 * Finished, start measuring states
 */
typedef enum
{
	eObjStartFinishBarState_FinishedChecked,
	eObjStartFinishBarState_FinishedUnChecked,
	eObjStartFinishBarState_StartMeasureingActive,
	eObjStartFinishBarState_StartMeasureingInActive,
} eObjStartFinishBarState;

/**
 * Unit block
 */
typedef enum
{
	eUnitBlockState_Default,
	eUnitBlockState_Selected
} eUnitBlockState;


/**
 * Functions
 */
void DisplayInit(void);
void DisplayDrive(eSystemStates currentState);
void DisplayUpdate(void);

void DisplayLoadFromFlash(void);

void DisplayQueueObject(sObjectQueueItem item);

#endif /* INC_DISPLAY_H_ */

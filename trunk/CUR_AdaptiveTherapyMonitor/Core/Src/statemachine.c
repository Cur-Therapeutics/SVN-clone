/********************************************************************
*
*   statemachine.c
*
*   Description:    The system state machine controller
*
*   Copyright NextPhase Medical, Inc. 2026 -- All rights reserved.
*
*--------------------------------------------------------------------
*
*   Revision History:
*
*   Rev.    | Date      | Name              | Description
*   1       | 06/13/26  | Brian Compter     | Created
*
********************************************************************/

#include "main.h"
#include "statemachine.h"
#include "display.h"
#include "touch.h"

/**
 * Our system state
 */
eSystemStates mSystemState = eSTATE_POST;
eSystemStates mSystemPreviousState = eSTATE_POST;

/**
 * Stay on the splash screen for 3 seconds
 */
uint16_t mSplashTimer = 0;

/**
 * @brief Initialize the statemachine for use
 * @return None
 */
void StateInit()
{
	mSystemState = eSTATE_POST;
}

/**
 * @brief Perform state machine behavior
 * @return None
 */
void StateDrive()
{
	switch (mSystemState)
	{
		case eSTATE_POST:
			ChangeState(eSTATE_SPLASH);
			break;

		case eSTATE_SPLASH:
			if (mSplashTimer++ > 3000)
				ChangeState(eSTATE_SELECT_UNITS);
			break;

		case eSTATE_READY_TO_CONNECT:
			break;

		case eSTATE_SELECT_UNITS:

			// Advance on touch
			if (TOUCH_Event() && TOUCH_TargetActive(sTargetBottomButton))
			{
				ChangeState(eSTATE_MEASURING);
			}
			break;

		case eSTATE_MEASURING:

			// Advance on touch
			if (TOUCH_Event() && TOUCH_TargetActive(sTargetFinishedButton))
			{
				ChangeState(eSTATE_COMPLETE_SELECTED);
			}

			break;

		case eSTATE_COMPLETE_SELECTED:

			// Advance on touch, save data
			if (TOUCH_Event())
			{
				if (TOUCH_TargetActive(sTargetFinishedGoButton)) ChangeState(eSTATE_COMPLETE);
				if (TOUCH_TargetActive(sTargetNoButton)) ChangeState(eSTATE_MEASURING);
			}
			break;

		case eSTATE_COMPLETE:

			// Back on touch
			if (TOUCH_Event() && TOUCH_TargetActive(sTargetBottomButton))
			{
				ChangeState(eSTATE_SELECT_UNITS);
			}
			break;

		case eSTATE_TEST:
			break;

		case eSTATE_ERROR:
			break;
	}
}

/**
 * @brief Get the current state
 * @return The current state
 */
eSystemStates GetCurrentState()
{
	return mSystemState;
}

/**
 * @brief Change the state machine state
 * @param newState The desired state
 * @return None
 */
void ChangeState(eSystemStates newState)
{
	mSystemPreviousState = mSystemState;
	mSystemState = newState;

	DisplayUpdate();
}

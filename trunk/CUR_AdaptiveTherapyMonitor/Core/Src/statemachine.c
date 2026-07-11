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

/**
 * Our system state
 */
eSystemStates mSystemState = eSTATE_POST;

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
			break;

		case eSTATE_SPLASH:
			break;

		case eSTATE_READY_TO_CONNECT:
			break;

		case eSTATE_SELECT_UNITS:
			break;

		case eSTATE_MEASURING:
			break;

		case eSTATE_COMPLETE:
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


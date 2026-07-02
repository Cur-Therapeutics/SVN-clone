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
 *
 */
void StateInit()
{

}

/**
 *
 */
void StateDrive()
{

}

/**
 * @brief Get the current state
 * @return The current state
 */
eSystemStates GetCurrentState()
{
	return mSystemState;
}


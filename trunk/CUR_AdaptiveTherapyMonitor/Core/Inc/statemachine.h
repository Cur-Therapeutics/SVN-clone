/********************************************************************
*
*   statemachine.h
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

#ifndef INC_STATEMACHINE_H_
#define INC_STATEMACHINE_H_

/**
 * Our system states
 */
typedef enum
{
	eSTATE_POST,
	eSTATE_SPLASH,
	eSTATE_READY_TO_CONNECT,
	eSTATE_SELECT_UNITS,
	eSTATE_MEASURING,
	eSTATE_COMPLETE_SELECTED,
	eSTATE_COMPLETE,
	eSTATE_TEST,
	eSTATE_ERROR
} eSystemStates;

/**
 * Functions
 */
eSystemStates GetCurrentState(void);
void StateInit(void);
void StateDrive(void);
void ChangeState(eSystemStates newState);

#endif /* INC_STATEMACHINE_H_ */

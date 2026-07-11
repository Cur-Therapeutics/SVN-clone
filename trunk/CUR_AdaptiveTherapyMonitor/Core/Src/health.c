/********************************************************************
*
*   health.c
*
*   Description:    Tracks the status of subsystems
*
*   Copyright NextPhase Medical, Inc. 2026 -- All rights reserved.
*
*--------------------------------------------------------------------
*
*   Revision History:
*
*   Rev.    | Date      | Name              | Description
*   1       | 08/19/19  | Brian Compter     | Created.
*
********************************************************************/
#include "main.h"
#include "health.h"
#include "gpio.h"

/**
 * Status register for tracking subsystem status
 * This variable should only be updated through the HealthUpdate function
 * except for initialization
 */
uint32_t gHealthStatus;

/**
  * @brief  Set system start time for error logging
  * @retval None
  */
void HealthInit()
{
	// Set system health based on subsystem health
	gHealthStatus = 0;
	HealthSubsystemGood(eSystemArm);
	HealthSubsystemGood(eSystemStack);
}

/**
  * @brief  Check vital subsystem health
  * @retval None
  */
void HealthDrive()
{
	/* Intentionally left blank */
}

/**
  * @brief  Update health status for a subsystem defined in health.h
  * @retval None
  */
void HealthUpdate(eSubsystems sys, eHealth state)
{
	uint32_t bit = 1 << sys;
    if (state == eHealthGood)
        gHealthStatus |= (bit);
    else
        gHealthStatus &= ~(bit);
}

/**
 * @brief Get the status of the system health
 * @return The current health status
 */
uint32_t HealthGetStatus()
{
	return gHealthStatus;
}

/**
 * @brief Update a sub system to good health
 * @param sys The subsystem to update
 * @return None
 */
void HealthSubsystemGood(eSubsystems sys)
{
	uint32_t bit = 1 << sys;
	gHealthStatus |= (bit);
}

/**
 * @brief Update a sub system to bad health
 * @param sys The subsystem to update
 * @return None
 */
void HealthSubsystemBad(eSubsystems sys)
{
	uint32_t bit = 1 << sys;
	gHealthStatus &= ~(bit);
}


/********************************************************************
*
*   health.c
*
*   Description:    Tracks the status of subsystems
*
*   Copyright NextPhase Medical, Inc. 2022 -- All rights reserved.
*
*--------------------------------------------------------------------
*
*   Functions:
*
*--------------------------------------------------------------------
*
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
	HealthUpdate(HEALTH_SYS, HEALTH_GOOD);
}

/**
  * @brief  Check vital subsystem health
  * @retval None
  */
void HealthDrive()
{

}

/**
  * @brief  Update health status for a subsystem defined in health.h
  * @retval None
  */
void HealthUpdate(uint32_t bit, uint8_t state)
{
    if (state)
    {
        gHealthStatus |= (bit);
    }
    else
    {
        gHealthStatus &= ~(bit);
    }
}

/**
 * @brief Get the status of the system health
 * @return The current health status
 */
uint32_t HealthGetStatus()
{
	return gHealthStatus;
}

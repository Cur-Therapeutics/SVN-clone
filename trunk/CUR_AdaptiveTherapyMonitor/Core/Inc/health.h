/********************************************************************
*
*   health.h
*
*   Description:    Tracks the status of subsystems
*
*   Copyright NextPhase Medical, Inc. 2018 -- All rights reserved.
*
*--------------------------------------------------------------------
*
*   Revision History:
*
*   Rev.    | Date      | Name              | Description
*   1       | 11/08/18  | Brian Compter     | Created
*
********************************************************************/

#ifndef HEALTH_H
#define HEALTH_H

/**
 * Health states
 */
typedef enum
{
	eHealthBad,
	eHealthGood,
} eHealth;

/**
 * Subsystems
 */
typedef enum
{
	eSystemArm,
	eSystemFlash,
	eSystemRam,
	eSystemAdc,
	eSystem7124,
	eSystemUart,
	eSystemTouch,
	eSystemRtc,
	eSystemLcd,
	eSystemStack,
	eSystemAccel,
	eSystemSpi,
	eSystemI2C,
	eSystemCath,
} eSubsystems;

void HealthInit(void);
void HealthDrive(void);
void HealthUpdate(eSubsystems sys, eHealth state);
void HealthSubsystemBad(eSubsystems sys);
void HealthSubsystemGood(eSubsystems sys);
uint32_t HealthGetStatus(void);

#endif

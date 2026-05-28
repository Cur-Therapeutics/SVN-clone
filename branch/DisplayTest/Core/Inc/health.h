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
*   Functions:  HealthUpdate()
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

#define HEALTH_GOOD     1
#define HEALTH_BAD      0

/**
 * Subsystem health bits
 */
#define HEALTH_SYS      0x0001
#define HEALTH_ADC		0x0002
#define HEALTH_SD       0x0004
#define HEALTH_RTC      0x0008
#define HEALTH_FLA      0x0010
#define HEALTH_BAT      0x0020
#define HEALTH_LCD      0x0040
#define HEALTH_URT      0x0100
#define HEALTH_STK		0x0200
#define HEALTH_ACC		0x0400
#define HEALTH_SPI		0x0800
#define HEALTH_OSPI		0x1000
#define HEALTH_ENC		0x2000
#define HEALTH_TVL		0x4000


void HealthInit(void);
void HealthDrive(void);
void HealthUpdate(uint32_t bit, uint8_t state);
uint32_t HealthGetStatus(void);

extern uint32_t gHealthStatus;
extern uint32_t gFaultStatus;

#endif

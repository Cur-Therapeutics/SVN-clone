/********************************************************************
*
*   touch.h
*
*   Description:    Controls a TS2007 Touch Screen Controller
*
*   Copyright PPMD, Inc. 2019 -- All rights reserved.
*
*--------------------------------------------------------------------
*
*   Revision History:
*
*   Rev.    | Date      | Name              | Description
*   1       | 09/05/19  | Brian Compter     | Created.
*
********************************************************************/

#ifndef TOUCH_H
#define TOUCH_H

#include "main.h"

/**
 * Touch controller slave address
 */
#define TOUCH_SLAVE_ADDRESS	0x90

/**
 * Timeout for polled operations
 */
#define TOUCH_TIMEOUT		1000

/**
 * Touch commands
 */
#define TOUCH_SETUP_IDLE	0xB0
#define TOUCH_MEASURE_X		0xC0
#define TOUCH_MEASURE_Y		0xD0

/**
 * Calibration address in flash
 */
//#define TOUCH_CAL_FLASH_ADDR	(eFLASH_Slot_18*FLASH_SLOT_SIZE)

/**
 * Touch read delay
 */
#define TOUCH_READ_DELAY		500

/**
 * Touch states
 */
typedef enum
{
	eTOUCH_IDLE,
	eTOUCH_DOWN,
	eTOUCH_DEBUG,
} eTouchState;

/**
 * Touch screen calibration values
 */
typedef struct __attribute__((packed, aligned(1)))
{
	uint16_t xMin;
	uint16_t xMax;
	uint16_t yMin;
	uint16_t yMax;
} sTouchCalibration;

/**
 * Touch target
 */
typedef struct
{
	uint16_t x;
	uint16_t y;
	uint16_t width;
	uint16_t height;
} sTouchTarget;

void TOUCH_Init();
void TOUCH_Idle();
uint16_t TOUCH_X();
uint16_t TOUCH_Y();
uint16_t TOUCH_Read(uint8_t cmd);
void TOUCH_Drive();
uint8_t TOUCH_GetMode();
void TOUCH_SetMode(uint8_t mode);
sTouchCalibration TOUCH_GetCal();
void TOUCH_SetCal(sTouchCalibration);

uint8_t TOUCH_Event();
uint16_t TOUCH_LastX();
uint16_t TOUCH_LastY();
uint16_t TOUCH_LastXRaw();
uint16_t TOUCH_LastYRaw();
uint8_t TOUCH_TargetActive(sTouchTarget target);

/**
 * Externs
 */
extern sTouchTarget sTargetBottomButton;
extern sTouchTarget sTargetFinishedButton;
extern sTouchTarget sTargetFinishedGoButton;
extern sTouchTarget sTargetNoButton;

#endif

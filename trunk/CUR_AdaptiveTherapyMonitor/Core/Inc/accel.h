/********************************************************************
*
*   accel.h
*
*   Description:    Manages the Accelerometer, AIS2IH
*
*   Copyright NextPhase Medical, Inc. 2026 -- All rights reserved.
*
*--------------------------------------------------------------------
*
*   Revision History:
*
*   Rev.    | Date      | Name              | Description
*   1       | 06/17/26  | Brian Compter     | Created.
*
********************************************************************/

#ifndef INC_ACCEL_H_
#define INC_ACCEL_H_

/**
 * Registers
 */
#define ACCEL_REG_WHO_AM_I 		0x0F
#define ACCEL_CTRL_1			0x20
#define ACCEL_CTRL_2			0x21
#define ACCEL_CTRL_3			0x22
#define ACCEL_REG_OUT_X_L		0x28
#define ACCEL_REG_OUT_X_H		0x29
#define ACCEL_REG_OUT_Y_L		0x2A
#define ACCEL_REG_OUT_Y_H		0x2B
#define ACCEL_REG_OUT_Z_L		0x2C
#define ACCEL_REG_OUT_Z_H		0x2D

/**
 * Access Type, Bit 7 is Read or NOT Write
 */
#define ACCEL_READ				0x80


/**
 * Control 1 Register values
 * This register is divided into three sections, resolution, mode, and datarate
 */
#define ACCEL_CTRL_1_RES_12BIT			0x00
#define ACCEL_CTRL_1_RES_14BIT			0x01

#define ACCEL_CTRL_1_MODE_LOW_POWER		0x00	// 12/14 bit resolution
#define ACCEL_CTRL_1_MODE_HIGH_POWER	0x04	// 14 bit resolution
#define ACCEL_CTRL_1_MODE_SINGLE		0x08

#define ACCEL_CTRL_1_DATARATE_POWERDOWN	0x00
#define ACCEL_CTRL_1_DATARATE_1Hz		0x10
#define ACCEL_CTRL_1_DATARATE_12Hz		0x20
#define ACCEL_CTRL_1_DATARATE_25Hz		0x30
#define ACCEL_CTRL_1_DATARATE_50Hz		0x40
#define ACCEL_CTRL_1_DATARATE_100Hz		0x50
#define ACCEL_CTRL_1_DATARATE_200Hz		0x60
#define ACCEL_CTRL_1_DATARATE_400Hz		0x70
#define ACCEL_CTRL_1_DATARATE_800Hz		0x80
#define ACCEL_CTRL_1_DATARATE_1600Hz	0x90

/**
 * Register values
 */
#define ACCEL_WHO_AM_I 	0x44

/**
 * Accel timer
 */
#define ACCEL_TIMER (1000)

/**
 * Functions
 */
void AccelInit(void);
void AccelDrive(void);

uint32_t AccelReadX(void);
uint32_t AccelReadY(void);
uint32_t AccelReadZ(void);

#endif /* INC_ACCEL_H_ */

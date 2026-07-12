/********************************************************************
*
*   accel.c
*
*   Description:    Manages the Accelerometer
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

#include "main.h"
#include "accel.h"
#include "spi.h"
#include "health.h"
#include "faulthandler.h"

/**
 * Acceleration values
 */
uint16_t mAccelX;
uint16_t mAccelY;
uint16_t mAccelZ;

/**
 * Accel timer used to periodically grab accel values
 */
uint16_t mAccelTimer = 0;

/**
 * Local functions
 */
void _AccelReadRegister(uint8_t reg, uint8_t * outValue);
void _AccelWriteRegister(uint8_t reg, uint8_t value);

/**
 * @brief Initialize the accelerometer for first use
 * @return None
 */
void AccelInit()
{
	// Read id register
	uint8_t who = 0;
	uint8_t ctrl1, ctrl2;
	_AccelReadRegister(ACCEL_REG_WHO_AM_I, &who);	// Double tap to setup the SPI clock on the right edge
	_AccelReadRegister(ACCEL_REG_WHO_AM_I, &who);
	_AccelReadRegister(ACCEL_CTRL_1, &ctrl1);
	_AccelReadRegister(ACCEL_CTRL_2, &ctrl2);

	// Check id against known good value
	if (who != ACCEL_WHO_AM_I)
		HealthSubsystemBad(eSystemAccel);
	else
		HealthSubsystemGood(eSystemAccel);

	// Start conversions by configuring control registers
	_AccelWriteRegister(ACCEL_CTRL_1,
			ACCEL_CTRL_1_RES_14BIT | ACCEL_CTRL_1_MODE_HIGH_POWER | ACCEL_CTRL_1_DATARATE_12Hz);
	_AccelReadRegister(ACCEL_CTRL_1, &ctrl1);
	if (ctrl1 != (ACCEL_CTRL_1_RES_14BIT | ACCEL_CTRL_1_MODE_HIGH_POWER | ACCEL_CTRL_1_DATARATE_12Hz) )
	{
		HealthSubsystemBad(eSystemAccel);
	}
}

/**
 * @brief Process Accelerometer behavior and events
 * @return None
 */
void AccelDrive()
{
	// Periodically read accel values
	if (mAccelTimer++ < ACCEL_TIMER)
		return;

	mAccelTimer = 0;

	uint16_t mAccelXtemp = 0;
	uint16_t mAccelYtemp = 0;
	uint16_t mAccelZtemp = 0;
	uint8_t regValue = 0;

	_AccelReadRegister(ACCEL_REG_OUT_X_H, &regValue);
	mAccelXtemp = regValue << 8;
	_AccelReadRegister(ACCEL_REG_OUT_X_L, &regValue);
	mAccelXtemp |= regValue;

	_AccelReadRegister(ACCEL_REG_OUT_Y_H, &regValue);
	mAccelYtemp = regValue << 8;
	_AccelReadRegister(ACCEL_REG_OUT_Y_L, &regValue);
	mAccelYtemp |= regValue;

	_AccelReadRegister(ACCEL_REG_OUT_Z_H, &regValue);
	mAccelZtemp = regValue << 8;
	_AccelReadRegister(ACCEL_REG_OUT_Z_L, &regValue);
	mAccelZtemp |= regValue;

	mAccelX = mAccelXtemp;
	mAccelY = mAccelYtemp;
	mAccelZ = mAccelZtemp;
}

/**
 * @brief Get the last X result
 * @return The last read X value
 */
uint32_t AccelReadX()
{
	return mAccelX;
}

/**
 * @brief Get the last Y result
 * @return The last read Y value
 */
uint32_t AccelReadY()
{
	return mAccelY;
}

/**
 * @brief Get the last Z result
 * @return The last read Z value
 */
uint32_t AccelReadZ()
{
	return mAccelZ;
}

/**
 * @brief Read a register from the accelerometer
 * @param reg The register to read
 * @param outValue Pointer to the place to put the read value
 * @return None
 */
void _AccelReadRegister(uint8_t reg, uint8_t * outValue)
{
	reg |= ACCEL_READ;		// Set the read bit
	uint8_t writeBuf [] = {reg, 0xFF};
	uint8_t readBuf [] = {0,0};

	SpiSelect(&sSpiAccel);
	SpiWriteRead(&sSpiAccel, writeBuf, readBuf, 2);
	SpiDeSelect(&sSpiAccel);

	*outValue = readBuf[1];
}

/**
 * @brief Write to a register in the accelerometer
 * @param reg The register to write
 * @param value The value to write
 * @return None
 */
void _AccelWriteRegister(uint8_t reg, uint8_t value)
{
	uint8_t writeBuf [] = {reg, value};
	SpiSelect(&sSpiAccel);
	SpiWrite(&sSpiAccel, writeBuf, 2);
	SpiDeSelect(&sSpiAccel);
}

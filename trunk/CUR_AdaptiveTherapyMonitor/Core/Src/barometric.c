/********************************************************************
*
*   barometric.c
*
*   Description:    Pressure sensor interface, MS5607-02BA03
*
*   Copyright NextPhase Medical, Inc. 2026 -- All rights reserved.
*
*--------------------------------------------------------------------
*
*   Revision History:
*
*   Rev.    | Date      | Name              | Description
*   1       | 05/21/25  | Brian Compter     | Created.
*
********************************************************************/

#include "main.h"
#include "barometric.h"
#include "i2c.h"
#include "gpio.h"
#include "string.h"
#include "statemachine.h"
#include "diagnostics.h"

// Error counter
uint32_t i2CErrorCnt = 0;
uint32_t i2cOverflow = 0;
uint32_t i2cTxDefault = 0;
uint32_t i2cRxDefault = 0;
uint32_t i2cTimeout = 0;

/**
 * Pressure sensors
 */
sPressureSensor mBarometricSensor;

/**
 * Filters
 */
#define FILTER_PRESS_SIZE	10
float filterValues [FILTER_PRESS_SIZE];
float filterSum = 0;
uint16_t filterHead = 0;
uint8_t firstSample = 1;

/**
 * Internal functions
 */
void PressureReadPromAddress(sPressureSensor * sensor, uint8_t addr);
void _PressureDriveHandler(sPressureSensor * sensor);

void __InitPressFilter(void);
float __FilterPressAdd(float newValue, float values [], uint16_t * head, float * sum);

/**
 * @brief Initialize the pressure sensors for use
 * @return None
 */
void BarometricInit()
{
	// Setup all pressure sensors to the correct ID and I2C port
	mBarometricSensor.id = 1;
	mBarometricSensor.i2c = &sI2CBarometric;
	mBarometricSensor.state = ePRESS_STATE_IDLE;

	// Send reset to all pressure sensors
	BarometricReset(&mBarometricSensor);

	// Request PROM data from each sensor
	BarometricReadProm(&mBarometricSensor);

	// Setup filters
	__InitPressFilter();
}

/**
 * @brief Perform periodic processing of the pressure sensor
 * @return None
 */
void BarometricDrive()
{
	// Process all pressure state based actions
	_PressureDriveHandler(&mBarometricSensor);
}

/**
 * @brief Handle drive functions
 * @param sensor The pressure sensor
 * @return None
 */
void _PressureDriveHandler(sPressureSensor * sensor)
{
	// Increment timer for next record
	sensor->timer++;

	uint8_t result;

	uint32_t rawPressure = 0;
	uint32_t rawTemperature = 0;

	switch (sensor->state)
	{
		case ePRESS_STATE_IDLE:

			// Hold until next sample
			if (sensor->timer < PRESSURE_SAMPLE_PERIOD)
				return;

			sensor->timer = 0;
			sensor->timeOut = 0;

			BarometricRead(sensor);
			break;

		case ePRESS_STATE_CONVERT_D1:
		case ePRESS_STATE_CONVERT_D2:
		case ePRESS_STATE_READ_D1:
		case ePRESS_STATE_READ_D2:
		case ePRESS_STATE_DATA_D1:
		case ePRESS_STATE_DATA_D2:

			// Handle timeouts
			if (sensor->timeOut++ > PRESSURE_TIMEOUT_TIME)
			{
				sensor->state = ePRESS_STATE_IDLE;
				i2cTimeout++;
			}
			break;

		case ePRESS_STATE_WAIT_D1:
			if (sensor->waitD12++ > PRESSURE_WAIT_TIME)
			{
				// Advance state
				sensor->state = ePRESS_STATE_READ_D1;
				sensor->waitD12 = 0;

				// Kick off Read cmd
				sensor->cmd = PRESSURE_ADC_RESULT;
				result = I2C_Write_IT(sensor->i2c, PRESSURE_ADDRESS, &sensor->cmd, 1);
				if ( result != eI2C_SUCCESS)
				{
					i2CErrorCnt++;
					return;
				}
			}
			break;

		case ePRESS_STATE_WAIT_D2:
			if (sensor->waitD12++ > PRESSURE_WAIT_TIME)
			{
				// Advance state
				sensor->state = ePRESS_STATE_READ_D2;
				sensor->waitD12 = 0;

				// Kick off Read cmd
				sensor->cmd = PRESSURE_ADC_RESULT;
				result = I2C_Write_IT(sensor->i2c, PRESSURE_ADDRESS, &sensor->cmd, 1);
				if ( result != eI2C_SUCCESS)
				{
					i2CErrorCnt++;
					return;
				}
			}
			break;

		case ePRESS_STATE_DATA_READY:

			// Pressure, reverse bytes
			uint8_t * pData = (uint8_t*)&sensor->d1Result;
			uint8_t * pPress = (uint8_t*)&rawPressure;
			pPress[0] = pData[2];
			pPress[1] = pData[1];
			pPress[2] = pData[0];

			// Temperature, reverse bytes
			pData = (uint8_t*)&sensor->d2Result;
			uint8_t * pTemp = (uint8_t*)&rawTemperature;
			pTemp[0] = pData[2];
			pTemp[1] = pData[1];
			pTemp[2] = pData[0];

			// Perform calculations to convert to pressure and temperature
			/* These calculations are detailed in the MS5607-02BA03 Datasheet */
			int32_t dT = rawTemperature - (sensor->prom.tref * 256);
			int32_t temp = ((int32_t)2000) + (int64_t)dT * (int64_t)sensor->prom.tempSens / ((int64_t)8388608);

			int64_t off = (int64_t)sensor->prom.offset * (131072) + ((int64_t)sensor->prom.tcoeffOffset*(int64_t)dT) / (64);
			int64_t sens = (int64_t)sensor->prom.sensitivity * (65536) + ((int64_t)sensor->prom.tcoeffSens * (int64_t)dT) / (128);
			int32_t p = ( rawPressure * sens / (2097152) - off ) / (32768);

			// Pressure is in deka-milli-bar; convert to mbar
			sensor->lastPressure = (float)p / 100.0f;

			// Convert to mmHg
			sensor->lastPressure *= 0.750062f;

			// Convert to PSI if the GUI requested it
			if (gPressureUnit == 1) 
			{
				sensor->lastPressure /= 51.7149f;
			}

			// Filter
			sensor->lastPressureFilt = __FilterPressAdd(sensor->lastPressure, filterValues, &filterHead, &filterSum);

			// Temperature is in hecto-Celsius; convert to Celsius
			sensor->lastTemperature = (float)temp / 100.0f;

			sensor->state = ePRESS_STATE_IDLE;
			break;

		case ePRESS_STATE_TIMEDOUT_WAIT:
			if (sensor->timer < 10)
				return;

			sensor->state = ePRESS_STATE_IDLE;

			break;
	}
}

/**
 * @brief Send a reset command to a pressure sensor
 * @param sensor The pressure sensor to reset
 * @return None
 */
void BarometricReset(sPressureSensor * sensor)
{
	sensor->cmd = PRESSURE_RESET;
	eI2C_RESULT rst = I2C_Write(sensor->i2c, PRESSURE_ADDRESS, &sensor->cmd, 1);
	if ( rst != eI2C_SUCCESS)
	{
		i2CErrorCnt++;
	}
	HAL_Delay(50);	// Need to wait for reset to complete, hold here...
}

/**
 * @brief Read the PROM data from a pressure sensor
 * @param sensor The pressure sensor
 * @return None
 */
void BarometricReadProm(sPressureSensor * sensor)
{
	int i;
	for (i = 0; i <= 0xC; i += 2)
	{
		PressureReadPromAddress(sensor, i);
	}
}

/**
 * @brief Read the PROM data from a pressure sensor
 * @param sensor The pressure sensor
 * @param addr The PROM address offset to read
 * @return None
 */
void PressureReadPromAddress(sPressureSensor * sensor, uint8_t addr)
{
	uint8_t cmd = PRESSURE_READ_PROM_BASE + addr;
	eI2C_RESULT rst = I2C_Write(sensor->i2c, PRESSURE_ADDRESS, &cmd, 1);
	if ( rst != eI2C_SUCCESS)
	{
		i2CErrorCnt++;
		return;
	}
	uint8_t * dest = (uint8_t*)&(sensor->prom);
	dest += addr;
	rst = I2C_Read(sensor->i2c, PRESSURE_ADDRESS, dest, 2);
	if ( rst != eI2C_SUCCESS)
	{
		i2CErrorCnt++;
	}

	// Swap bytes
	uint8_t tmp = dest[0];
	dest[0] = dest[1];
	dest[1] = tmp;
}

/**
 * @brief Sample and calculate the pressure. The result is stored to be retrieved by PressureGetLast
 * @param sensor The pressure sensor
 * @return None
 */
void BarometricRead(sPressureSensor * sensor)
{
	// Must be in an IDLE state to begin conversion
	if (sensor->state != ePRESS_STATE_IDLE)
	{
		i2cOverflow++;
		return;
	}

	// Advance state
	sensor->state = ePRESS_STATE_CONVERT_D1;

	// Kick off D1 conversion
	sensor->cmd = PRESSURE_D1_CONVERT_BASE + OSR_256;
	eI2C_RESULT rst = I2C_Write_IT(sensor->i2c, PRESSURE_ADDRESS, &sensor->cmd, 1);
	if ( rst != eI2C_SUCCESS)
	{
		i2CErrorCnt++;
		return;
	}
	sensor->waitD12 = 0;	// Enforce conversion time
}

/**
 * @brief Get the last stored pressure reading
 * @param sensor The pressure sensor
 * @return The sensor pressure in mmHg
 */
float BarometricGetLast(sPressureSensor * sensor)
{
	return sensor->lastPressure;
}

/**
 * @brief Get the last filtered pressure reading
 * @param sensor The pressure sensor
 * @return The sensor pressure in mmHg
 */
float BarometricGetLastFilt(sPressureSensor * sensor)
{
	return sensor->lastPressureFilt;
}

/**
 * @brief Get the last stored temperature reading
 * @param sensor The pressure sensor
 * @return The sensor temperature in degrees C
 */
float BarometricGetLastTemp(sPressureSensor * sensor)
{
	return sensor->lastTemperature;
}

/**
 * @brief Copy data from one PROM struct to another
 * @param dst The destination
 * @param src The source
 * @return None
 */
void BarometricCopyProm(sPressureProm * dst, sPressureProm * src)
{
	dst->offset = src->offset;
	dst->prog = src->prog;
	dst->sensitivity = src->sensitivity;
	dst->tcoeffOffset = src->tcoeffOffset;
	dst->tcoeffSens = src->tcoeffSens;
	dst->tempSens = src->tempSens;
	dst->tref = src->tref;
}

/**
 * @brief Transmit callback
 * @param port The I2C port
 * @return None
 */
void BarometricTxCallback(sPressureSensor * sensor)
{
	uint8_t result;
	switch (sensor->state)
	{
		case ePRESS_STATE_CONVERT_D1:
			sensor->state = ePRESS_STATE_WAIT_D1;
			break;

		case ePRESS_STATE_READ_D1:
			sensor->state = ePRESS_STATE_DATA_D1;
			result = I2C_Read_IT(sensor->i2c, PRESSURE_ADDRESS, (uint8_t*)&sensor->tmpData, 3);
			if ( result != eI2C_SUCCESS)
			{
				i2CErrorCnt++;
				return;
			}
			break;

		case ePRESS_STATE_CONVERT_D2:
			sensor->state = ePRESS_STATE_WAIT_D2;
			break;

		case ePRESS_STATE_READ_D2:
			sensor->state = ePRESS_STATE_DATA_D2;
			result = I2C_Read_IT(sensor->i2c, PRESSURE_ADDRESS, (uint8_t*)&sensor->tmpData, 3);
			if ( result != eI2C_SUCCESS)
			{
				i2CErrorCnt++;
				return;
			}
			break;

		case ePRESS_STATE_DATA_READY:
			break;

		default:
			i2cTxDefault++;
			break;
	}
}

/**
 * @brief Receive callback
 * @param port The I2C port
 * @return None
 */
void BarometricRxCallback(sPressureSensor * sensor)
{
	switch (sensor->state)
	{
		case ePRESS_STATE_DATA_D1:
			// Move data from tmp to D1 result
			sensor->d1Result = sensor->tmpData;

			// Advance state
			sensor->state = ePRESS_STATE_CONVERT_D2;

			// Initiate D2 conversion
			sensor->cmd = PRESSURE_D2_CONVERT_BASE + OSR_256;
			eI2C_RESULT rst = I2C_Write_IT(sensor->i2c, PRESSURE_ADDRESS, &sensor->cmd, 1);
			if ( rst != eI2C_SUCCESS)
			{
				i2CErrorCnt++;
				return;
			}
			sensor->waitD12 = 0;	// Enforce conversion time
			break;

		case ePRESS_STATE_DATA_D2:
			// Move data from tmp to D1 result
			sensor->d2Result = sensor->tmpData;

			// Advance state, Data Ready!
			sensor->state = ePRESS_STATE_DATA_READY;
			break;

		default:
			i2cRxDefault++;
			break;
	}
}

/**
 * @brief Calculate and verify the CRC value for a pressure sensor PROM
 * @param sensor The sensor
 * @return The four bit CRC calculation
 */
uint8_t crc4(sPressureSensor * sensor)
{
	int cnt;
	unsigned int n_rem = 0;
	uint8_t n_bit;
	UNUSED(cnt);
	UNUSED(n_bit);

/* todo */

	n_rem = ((n_rem >> 12) & 0x000F);
	return (n_rem ^ 0x00);
}

/**
 * @brief Initialize filters
 * @return None
 */
void __InitPressFilter(void)
{
	memset(filterValues, 0, FILTER_PRESS_SIZE*sizeof(filterValues[0]));

	filterSum = 0;
	filterHead = 0;
	firstSample = 1;
}

/**
 * @brief Add a value to a filter
 * @param values Filter values
 * @param sum filter sum
 * @return The filtered value
 */
float __FilterPressAdd(float newValue, float values [], uint16_t * head, float * sum)
{
	// Pre-load on first sample
	if (firstSample == 1)
	{
		for (int i = 0; i < FILTER_PRESS_SIZE; i++)
		{
			values[i] = newValue;
			*sum += newValue;
		}
		firstSample = 0;
	}

	// Replace
	*sum -= values[*head];
	values[*head] = newValue;
	*sum += newValue;

	// Increment head
	((*head)++);
	if (*head >= FILTER_PRESS_SIZE)
		*head = 0;

	return *sum / FILTER_PRESS_SIZE;
}

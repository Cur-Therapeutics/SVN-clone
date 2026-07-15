/********************************************************************
*
*   barometric.h
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
#ifndef INC_BAROMETRIC_H_
#define INC_BAROMETRIC_H_

#include "i2c.h"

/**
 * I2C address (bit shifted up once to agree with STM32 I2C paradigms)
 */
#define PRESSURE_ADDRESS	(0xEE)

/**
 * Constant to convert bar to psi
 */
#define BAR_TO_PSI			(14.5038f)

/**
 * One ATM in cm-H2O
 */
#define ONE_ATM_TO_CM_H2O	(1033.23f)

/**
 * Wait time for conversion
 */
#define PRESSURE_WAIT_TIME	(1)

/**
 * Timeout
 */
#define PRESSURE_TIMEOUT_TIME	(30)

/**
 * Sample Period, ms
 */
#define PRESSURE_SAMPLE_PERIOD	(50)

/**
 * PROM contents
 * 7 addresses, 2 bytes per address
 */
typedef struct
{
	uint16_t prog;
	uint16_t sensitivity;
	uint16_t offset;
	uint16_t tcoeffSens;
	uint16_t tcoeffOffset;
	uint16_t tref;
	uint16_t tempSens;
} sPressureProm;

/**
 * Pressure commands
 */
typedef enum {
	PRESSURE_ADC_RESULT = 0x00,
	PRESSURE_RESET = 0x1E,
	PRESSURE_D1_CONVERT_BASE = 0x40,	// Pressure
	PRESSURE_D2_CONVERT_BASE = 0x50,	// Temperature
	PRESSURE_READ_PROM_BASE = 0xA0,
} ePressCmd;

/**
 * Sampling OSR modifiers to D1 and D2 commands
 * This modifier is added to the base to set the oversampling rate
 */
typedef enum {				// ADC Conversion Times
	OSR_256 = 0x00,			// 0.54 ms
	OSR_512 = 0x02,			// 1.06 ms
	OSR_1024 = 0x04,		// 2.08 ms
	OSR_2048 = 0x06,		// 4.13 ms
	OSR_4096 = 0x08,		// 8.22 ms
	OSR_8192 = 0x0A			// 16.44 ms
} eOsrModifier;

/**
 * Pressure read state
 */
typedef enum {
	ePRESS_STATE_IDLE,
	ePRESS_STATE_CONVERT_D1,
	ePRESS_STATE_WAIT_D1,
	ePRESS_STATE_READ_D1,
	ePRESS_STATE_DATA_D1,
	ePRESS_STATE_CONVERT_D2,
	ePRESS_STATE_WAIT_D2,
	ePRESS_STATE_READ_D2,
	ePRESS_STATE_DATA_D2,
	ePRESS_STATE_DATA_READY,
	ePRESS_STATE_TIMEDOUT_WAIT,
} ePressureReadState;

/**
 * Pressure sensor instance
 */
typedef struct {
	uint8_t id;
	float lastPressure;
	float lastPressureFilt;
	float lastTemperature;
	sPressureProm prom;
	sI2CPort * i2c;
	uint32_t state;
	uint32_t d1Result;
	uint32_t d2Result;
	uint32_t tmpData;
	uint16_t timer;
	uint8_t waitD12;
	uint8_t timeOut;
	uint8_t cmd;
} sPressureSensor;

/**
 * Functions
 */
void BarometricInit();
void BarometricDrive();
void BarometricReset(sPressureSensor * sensor);
void BarometricReadProm(sPressureSensor * sensor);
void BarometricRead(sPressureSensor * sensor);
void BarometricReadOld(sPressureSensor * sensor);
void BarometricCopyProm(sPressureProm * dst, sPressureProm * src);

float BarometricGetLast(sPressureSensor * sensor);
float BarometricGetLastFilt(sPressureSensor * sensor);
float BarometricGetLastTemp(sPressureSensor * sensor);

void BarometricTxCallback(sPressureSensor * sensor);
void BarometricRxCallback(sPressureSensor * sensor);

/**
 * Externals
 */
extern sPressureSensor mBarometricSensor;
extern uint32_t i2CErrorCnt;
extern uint32_t i2cOverflow;
extern uint32_t i2cTxDefault;
extern uint32_t i2cRxDefault;
extern uint32_t i2cTimeout;

extern TIM_HandleTypeDef htim1;

#endif /* INC_BAROMETRIC_H_ */

/********************************************************************
*
*   pressure.c
*
*   Description:    Pressure sensor accessor
*
*--------------------------------------------------------------------
*
*   Revision History:
*
*   Rev.    | Date      | Name              | Description
*   2       | 07/31/26  | WJ                | Fixed.
*
********************************************************************/

#include "main.h"
#include "pressure.h"
#include "ad7124.h"
#include "barometric.h" // Added to access BarometricGetLastFilt and mBarometricSensor

// Store the zeroing offset
static float user_pressure_offset_mmHg = 0.0f;

/**
 * @brief Get the baseline pressure from the barometric sensor
 * @return The ambient pressure in mmHg
 */
float GetBaselinePressure()
{
	return BarometricGetLastFilt(&mBarometricSensor);
}

/**
 * @brief Zeros out the pressure reading to the current ambient conditions.
 * Call this prior to starting a measurement.
 */
void Pressure_Zero(void)
{
	// Temporarily clear offset to get the true gauge pressure
	user_pressure_offset_mmHg = 0.0f;
	
	// Read the absolute pressure from the ADC
	float absolute_pressure = AD7124_GetLastEng(&ad7124);
	
	// Read the current barometric pressure
	float barometric_pressure = GetBaselinePressure();
	
	// Set the offset to the current uncompensated gauge pressure
	user_pressure_offset_mmHg = absolute_pressure - barometric_pressure;
}

/**
 * @brief Get the current pressure reading
 * @param units The desired units
 * @return The pressure in the requested units
 */
float GetPressure(ePressureUnits units)
{
	// 1. Get the absolute pressure from the ADC
	float absolute_pressure = AD7124_GetLastEng(&ad7124);
	
	// 2. Get the ambient barometric pressure
	float barometric_pressure = GetBaselinePressure();
	
	// 3. Calculate true gauge pressure (Absolute - Barometric - Offset)
	float pressure = absolute_pressure - barometric_pressure - user_pressure_offset_mmHg;

	// 4. Convert to the requested units
	switch (units)
	{
		case ePressureUnits_mmHg:
			/* Intentionally left blank, no conversion */
			break;

		case ePressureUnits_psi:
			pressure *= CONVERT_MMHG_TO_PSI;
			break;

		case ePressureUnits_kPa:
			pressure *= CONVERT_MMHG_TO_KPA;
			break;

	}
	return pressure;
}

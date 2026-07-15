/********************************************************************
*
*   pressure.c
*
*   Description:    Pressure sensor accessor
*
*   Copyright PPMD, Inc. 2026 -- All rights reserved.
*
*--------------------------------------------------------------------
*
*   Revision History:
*
*   Rev.    | Date      | Name              | Description
*   1       | 06/15/26  | Brian Compter     | Created.
*
********************************************************************/

#include "main.h"
#include "pressure.h"
#include "ad7124.h"

/**
 * @brief Get the baseline pressure from the barometric sensor
 * @return The ambient pressure in mmHg
 */
uint32_t GetBaselinePressure()
{
	return 0;
}

/**
 * @brief Get the current pressure reading
 * @param units The desired units
 * @return The pressure in the requested units
 */
uint32_t GetPressure(ePressureUnits units)
{
	float pressure = AD7124_GetLastEng(&ad7124);
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

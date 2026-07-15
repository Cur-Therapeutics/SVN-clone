/********************************************************************
*
*   pressure.h
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
#ifndef INC_PRESSURE_H_
#define INC_PRESSURE_H_

/**
 * Conversion values
 */
#define CONVERT_MMHG_TO_PSI (0.0193368f)
#define CONVERT_MMHG_TO_KPA (0.133322f)

/**
 * Pressure units
 */
typedef enum
{
	ePressureUnits_mmHg,
	ePressureUnits_kPa,
	ePressureUnits_psi
} ePressureUnits;

uint32_t GetBaselinePressure(void);
uint32_t GetPressure(ePressureUnits units);

#endif /* INC_PRESSURE_H_ */

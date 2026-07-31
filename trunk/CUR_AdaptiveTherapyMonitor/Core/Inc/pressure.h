/********************************************************************
*
*   pressure.h
*
*   Description:    Pressure sensor accessor
*
*--------------------------------------------------------------------
*
*   Revision History:
*
*   Rev.    | Date      | Name              | Description
*   2       | 07/31/26  | Whitney Jackson     | Fixed.
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

// Added Zeroing Function Prototype
void Pressure_Zero(void);

float GetBaselinePressure(void);
float GetPressure(ePressureUnits units);

#endif /* INC_PRESSURE_H_ */

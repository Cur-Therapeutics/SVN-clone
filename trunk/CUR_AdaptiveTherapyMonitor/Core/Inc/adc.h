/********************************************************************
*
*   adc.h
*
*   Description:    Manages the internal adc
*
*   Copyright NextPhase Medical, Inc. 2023 -- All rights reserved.
*
*--------------------------------------------------------------------
*
*   Revision History:
*
*   Rev.    | Date      | Name              | Description
*   1       | 12/04/23  | Brian Compter     | Created.
*
********************************************************************/

#ifndef INC_ADC_H_
#define INC_ADC_H_

/**
 * Battery counts to voltage scale
 */
#define ADC_BAT_COUNTS_TO_VOLTS	(0.000153f)

/**
 * Battery volts to engineering voltage
 * This converts the observed volts to the actual volts by compensating for the voltage divider
 * (1.0f/0.3651f), 49.9KOhm over 28.7KOhm
 */
#define ADC_BAT_VOLTS_TO_ENG	(2.738976f)

/**
 * ADC channels
 */
typedef enum
{
	eAdcChannelBattery,
} eAdcChannel;

/**
 * ADC State
 */
typedef enum
{
	eAdcStateIdle,
	eAdcStateCh1,
} eAdcState;

/**
 * Functions
 */
void AdcInit(void);
void AdcDrive(void);
uint16_t AdcGetBatteryCounts(void);
float AdcGetBatteryVolts(void);
uint8_t AdcIsSampleInProgress(void);

/**
 * External
 */
extern ADC_HandleTypeDef hadc1;

#endif /* INC_ADC_H_ */

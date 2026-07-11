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
uint16_t AdcGetBatteryVolts(void);
uint8_t AdcIsSampleInProgress(void);

/**
 * External
 */
extern ADC_HandleTypeDef hadc1;

#endif /* INC_ADC_H_ */

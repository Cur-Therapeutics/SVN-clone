/********************************************************************
*
*   adc.c
*
*   Description:    Manages the internal ADC
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

#include "main.h"
#include "adc.h"
#include "faulthandler.h"
#include "health.h"

/**
 * Internal functions
 */
void __AdcChangeChannel(int channel);

/**
 * Local variables
 */
const int mNumChannels = 1;
volatile uint16_t mAdcResults[1];
int mAdcErrorCnt = 0;
int adcTimer = 0;

/**
 * ADC state
 */
eAdcState mAdcState = eAdcStateIdle;

/**
 * Sample in progress flag
 */
uint8_t mSampleInProgress = 0;

/**
 * @brief Initialize the internal ADC for use
 * @return None
 */
void AdcInit()
{
	/* Perform ADC calibration */
	if (HAL_ADCEx_Calibration_Start(&hadc1, ADC_CALIB_OFFSET, ADC_SINGLE_ENDED) != HAL_OK)
	{
		/* Calibration Error */
		FaultHandler(ERR_ADC);
	}
	HealthSubsystemGood(eSystemAdc);
}

/**
 * @brief Perform ADC drive
 * @return None
 */
void AdcDrive()
{
	// Start a conversion if required
	if (mSampleInProgress == 0 && adcTimer-- <= 0)
	{
		adcTimer = 1000;
		mSampleInProgress = 1;
		mAdcState = eAdcStateCh1;

		if (HAL_ADC_Start_IT(&hadc1) != HAL_OK)
		{
			FaultHandler(ERR_ADC);
		}

		mSampleInProgress = 0;
	}
}

/**
 * @brief Get battery counts
 * @return Battery voltage in counts
 */
uint16_t AdcGetBatteryCounts()
{
	return mAdcResults[eAdcChannelBattery];
}

/**
 * @brief Get battery voltage
 * @return Battery voltage in volts
 */
float AdcGetBatteryVolts()
{
	return (float)mAdcResults[eAdcChannelBattery] * ADC_BAT_COUNTS_TO_VOLTS * ADC_BAT_VOLTS_TO_ENG;
}

/**
 * @brief ADC Conversion complete callback
 * @param hadc ADC handle pointer
 * @return None
 */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
	switch (mAdcState)
	{
		case eAdcStateCh1:
			mAdcResults[eAdcChannelBattery] = HAL_ADC_GetValue(hadc);
			HAL_ADC_Stop_IT(hadc);
			mAdcState = eAdcStateIdle;
			break;

		default:
			break;
	}
}

/**
 * @brief Is a sample in progress
 * @return True is a sample is in progress
 */
uint8_t AdcIsSampleInProgress()
{
	return mSampleInProgress;
}

/**
 * @brief Change ADC channel
 * @param channel The desired channel
 * @return None
 */
void __AdcChangeChannel(int channel)
{
	/**
	 * Configure Regular Channel
	 */
	ADC_ChannelConfTypeDef sConfig = {0};
	if (channel == 1)
		sConfig.Channel = ADC_CHANNEL_1;
	else if (channel == 2)
		sConfig.Channel = ADC_CHANNEL_2;
	else
		sConfig.Channel = ADC_CHANNEL_3;
	sConfig.Rank = ADC_REGULAR_RANK_1;
	sConfig.SamplingTime = ADC_SAMPLETIME_5CYCLE;
	sConfig.SingleDiff = ADC_SINGLE_ENDED;
	sConfig.OffsetNumber = ADC_OFFSET_NONE;
	sConfig.Offset = 0;
	if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
	{
		FaultHandler(ERR_ADC);
	}
}

/********************************************************************
 *
 *   ad7124.c
 *
 *   Description:    Manages the AD7124-4 ADC
 *
 *   Copyright NextPhase Medical, Inc. 2023 -- All rights reserved.
 *
 *--------------------------------------------------------------------
 *
 *   Revision History:
 *
 *   Rev.    | Date      | Name              | Description
 *   1       | 01/02/24  | Brian Compter     | Created.
 *
 ********************************************************************/

#include <string.h>
#include "main.h"
#include "diagnostics.h"
#include "ad7124.h"
#include "gpio.h"
#include "spi.h"
#include "string.h"
#include "faulthandler.h"
#include "health.h"

/**
 * AD7124 Device Instance
 */
sAd7124 ad7124 = {eAD7124_Bridge, &sSpiAdc1};

/**
 * Current state
 */
eAD7124_States mAD7124State = eAD7124_States_WAIT;

/**
 * Device registers
 */
sAD7124Register mRegisters [] =
{
		{AD7124_STATUS, 0, 1, AD7124READ},
		{AD7124_ADC_CTRL, 0, 2, AD7124READWRITE},
		{AD7124_DATA, 0, 3, AD7124READ},
		{AD7124_IO_CTRL_1, 0, 3, AD7124READWRITE},
		{AD7124_IO_CTRL_2, 0, 2, AD7124READWRITE},
		{AD7124_ID, 0, 1, AD7124READ},
		{AD7124_ERROR, 0, 3, AD7124READ},
		{AD7124_ERROR_EN, 0, 3, AD7124WRITE},
		{AD7124_MCLK_COUNT, 0, 1, AD7124WRITE},

		{AD7124_CH_00, 0, 2, AD7124READWRITE},
		{AD7124_CH_01, 0, 2, AD7124READWRITE},
		{AD7124_CH_02, 0, 2, AD7124READWRITE},
		{AD7124_CH_03, 0, 2, AD7124READWRITE},
		{AD7124_CH_04, 0, 2, AD7124READWRITE},
		{AD7124_CH_05, 0, 2, AD7124READWRITE},
		{AD7124_CH_06, 0, 2, AD7124READWRITE},
		{AD7124_CH_07, 0, 2, AD7124READWRITE},
		{AD7124_CH_08, 0, 2, AD7124READWRITE},
		{AD7124_CH_09, 0, 2, AD7124READWRITE},
		{AD7124_CH_10, 0, 2, AD7124READWRITE},
		{AD7124_CH_11, 0, 2, AD7124READWRITE},
		{AD7124_CH_12, 0, 2, AD7124READWRITE},
		{AD7124_CH_13, 0, 2, AD7124READWRITE},
		{AD7124_CH_14, 0, 2, AD7124READWRITE},
		{AD7124_CH_15, 0, 2, AD7124READWRITE},

		{AD7124_CONFIG_00, 0, 2, AD7124READWRITE},
		{AD7124_CONFIG_01, 0, 2, AD7124READWRITE},
		{AD7124_CONFIG_02, 0, 2, AD7124READWRITE},
		{AD7124_CONFIG_03, 0, 2, AD7124READWRITE},
		{AD7124_CONFIG_04, 0, 2, AD7124READWRITE},
		{AD7124_CONFIG_05, 0, 2, AD7124READWRITE},
		{AD7124_CONFIG_06, 0, 2, AD7124READWRITE},
		{AD7124_CONFIG_07, 0, 2, AD7124READWRITE},

		{AD7124_FILTER_00, 0, 3, AD7124READWRITE},
		{AD7124_FILTER_01, 0, 3, AD7124READWRITE},
		{AD7124_FILTER_02, 0, 3, AD7124READWRITE},
		{AD7124_FILTER_03, 0, 3, AD7124READWRITE},
		{AD7124_FILTER_04, 0, 3, AD7124READWRITE},
		{AD7124_FILTER_05, 0, 3, AD7124READWRITE},
		{AD7124_FILTER_06, 0, 3, AD7124READWRITE},
		{AD7124_FILTER_07, 0, 3, AD7124READWRITE},

		{AD7124_OFFSET_00, 0, 3, AD7124READWRITE},
		{AD7124_OFFSET_01, 0, 3, AD7124READWRITE},
		{AD7124_OFFSET_02, 0, 3, AD7124READWRITE},
		{AD7124_OFFSET_03, 0, 3, AD7124READWRITE},
		{AD7124_OFFSET_04, 0, 3, AD7124READWRITE},
		{AD7124_OFFSET_05, 0, 3, AD7124READWRITE},
		{AD7124_OFFSET_06, 0, 3, AD7124READWRITE},
		{AD7124_OFFSET_07, 0, 3, AD7124READWRITE},

		{AD7124_GAIN_00, 0, 3, AD7124READWRITE},
		{AD7124_GAIN_01, 0, 3, AD7124READWRITE},
		{AD7124_GAIN_02, 0, 3, AD7124READWRITE},
		{AD7124_GAIN_03, 0, 3, AD7124READWRITE},
		{AD7124_GAIN_04, 0, 3, AD7124READWRITE},
		{AD7124_GAIN_05, 0, 3, AD7124READWRITE},
		{AD7124_GAIN_06, 0, 3, AD7124READWRITE},
		{AD7124_GAIN_07, 0, 3, AD7124READWRITE},
};

/**
 * Acquisition timer
 */
uint16_t mTimer = 0;

/**
 * Internal functions
 */
uint32_t AD7124_ReadRegister(sAd7124 * ad7124, sAD7124Register reg);
void AD7124_WriteRegister(sAd7124 * ad7124, sAD7124Register reg, uint32_t val);
uint32_t AD7124_InitInternal(sAd7124 * ad7124);
void AD7124_DriveBridge(sAd7124 * ad7124);

/**
 * @brief Initialize our three AD7124s for use
 * @return None
 */
void AD7124_Init()
{
	// Setup max channels per configuration
	ad7124.maxChannel = AD7124_MAX_CH;

	// Perform setup on each ADC
	if (AD7124_InitInternal(&ad7124) == HAL_OK)
		HealthSubsystemGood(eSystem7124);
}

/**
 * @brief
 * @param ad7124 The AD7124 to configure
 * @return HAL_OK on success, HAL_ERROR otherwise
 */
uint32_t AD7124_InitInternal(sAd7124 * ad7124)
{
	// Check ID for communications check
	uint32_t readback = AD7124_Read(ad7124, AD7124_ID);
	readback = AD7124_Read(ad7124, AD7124_ID);
	if (readback != AD7124_DEVICE_ID && readback != AD7124_DEVICE_ID2)
	{
		FaultHandler(ERR_AD7124);
		return HAL_ERROR;
	}

	// Local variables
	uint16_t setup;
	uint32_t filter;

	ad7124->channelConfig = AD7124_CHANNEL_AIN_POS_02 | AD7124_CHANNEL_AIN_NEG_03 | AD7124_CHANNEL_SETUP_00 | AD7124_CHANNEL_ENABLE;
	AD7124_Write(ad7124, AD7124_CH_01, ad7124->channelConfig);

	setup = AD7124_CONFIG_BIPOLOR | AD7124_CONFIG_REFSEL_1 | AD7124_CONFIG_GAIN_128 |
			AD7124_CONFIG_AINP_BUF_EN | AD7124_CONFIG_AINN_BUF_EN |
			AD7124_CONFIG_REFP_BUF_EN | AD7124_CONFIG_REFN_BUF_EN;
	AD7124_Write(ad7124, AD7124_CONFIG_00, setup);

	// Filter setting to FS 5, Sinc4
	filter = AD7124_FILTER_SINC4_FAST + (1);
	AD7124_Write(ad7124, AD7124_FILTER_00, filter);

	return HAL_OK;
}

/**
 * @brief Perform periodic operations on the ADCs
 * @return None
 */
void AD7124_Drive()
{
	mTimer++;	// Increment our timer no matter what to keep the acquisition sequence on time
	switch (mAD7124State)
	{
		case eAD7124_States_WAIT:

			if (mTimer < AD7124_SAMPLE_PERIOD)
				return;

			mAD7124State = eAD7124_States_ACQUIRE;
			mTimer = 0;

			AD7124_TriggerAcq(&ad7124);
			break;

		case eAD7124_States_ACQUIRE:
			AD7124_DriveBridge(&ad7124);

			// If all acquisition is complete, return to wait state
			if (AD7124_IsAcqDone(&ad7124))
			{
				mAD7124State = eAD7124_States_WAIT;
			}
			break;

		default:
			/* Should not get here, fault? todo */
			break;
	}
}

/**
 * @brief Sample and process data from our bag weight sensors
 * @param ad7124 The AD7124 to drive
 * @return None
 */
void AD7124_DriveBridge(sAd7124 * ad7124)
{
	// Check status register
	uint32_t status = AD7124_Read(ad7124, AD7124_STATUS);
	if ((status & AD7124_STATUS_NRDY) != AD7124_STATUS_NRDY)
	{
		// Grab Data, determine channel and convert
		uint32_t counts = AD7124_Read(ad7124, AD7124_DATA);
		status = AD7124_Read(ad7124, AD7124_STATUS);
		uint16_t channel = status & AD7124_STATUS_CH_ACTIVE_MASK;

		ad7124->lastCounts = counts;
		ad7124->lastVoltage = (ad7124->lastCounts);
		ad7124->lastEng = ad7124->lastVoltage;

		ad7124->lastChannel = channel;
	}
}

/**
 * @brief Read a register
 * @param reg The register
 * @return The register value
 */
uint32_t AD7124_Read(sAd7124 * ad7124, uint32_t reg)
{
	return AD7124_ReadRegister(ad7124, mRegisters[reg]);
}

/**
 * @brief Write to a register
 * @param reg The register
 * @param val The value to set the register to
 * @return None
 */
void AD7124_Write(sAd7124 * ad7124, uint32_t reg, uint32_t val)
{
	AD7124_WriteRegister(ad7124, mRegisters[reg], val);
}

/**
 * @brief Read a register from the ADC
 * @param reg The register
 * @return The register value
 */
uint32_t AD7124_ReadRegister(sAd7124 * ad7124, sAD7124Register reg)
{
	uint32_t retval = 0;
	uint8_t data [] = {0,0,0,0};
	uint8_t cmd = reg.regNum | AD7124_COMMS_READ;

	SpiSelect(ad7124->spiPort);

	SpiWrite(ad7124->spiPort, (uint8_t*)&cmd, 1);
	SpiRead(ad7124->spiPort, data, reg.len);
	SpiDeSelect(ad7124->spiPort);

	// Reverse bytes of reply
	if (reg.len == 2)
	{
		uint8_t temp = data[0];
		data[0] = data[1];
		data[1] = temp;
	}
	if (reg.len == 3)
	{
		uint8_t temp = data[0];
		data[0] = data[2];
		data[2] = temp;
	}

	memcpy(&retval, data, 4);
	return retval;
}

/**
 * @brief Write to a ADC register
 * @param reg The register to write to
 * @param val The value to write
 * @return None
 */
void AD7124_WriteRegister(sAd7124 * ad7124, sAD7124Register reg, uint32_t val)
{
	uint8_t data [] = {reg.regNum, 0, 0, 0, 0};
	memcpy((uint8_t*)&data[1], (uint8_t*)&val, sizeof(uint32_t));

	// Reverse bytes
	if (reg.len == 2)
	{
		uint8_t temp = data[1];
		data[1] = data[2];
		data[2] = temp;
	}
	if (reg.len == 3)
	{
		uint8_t temp = data[1];
		data[1] = data[3];
		data[3] = temp;
	}

	SpiSelect(ad7124->spiPort);
	SpiWrite(ad7124->spiPort, data, reg.len+1);
	SpiDeSelect(ad7124->spiPort);
}

/**
 * @brief Get the last data in counts
 * @param ad7124 The ADC to read
 * @return the last ADC counts value
 */
uint32_t AD7124_GetLastCount(sAd7124 * ad7124)
{
	return ad7124->lastCounts;
}

/**
 * @brief Get the last voltage value read from the ADC
 * @param ad7124 The ADC to read
 * @return the last force in voltage
 */
float AD7124_GetLastVolts(sAd7124 * ad7124)
{
	return ad7124->lastVoltage;
}

/**
 * @brief Get the last engineering units read from the ADC
 * @param ad7124 The ADC to read
 * @return The last engineering unit output data
 */
float AD7124_GetLastEng(sAd7124 * ad7124)
{
	return ad7124->lastEng;
}

/**
 * @brief Reset SPI communications with the ADC by sending a string of 0xFF data
 * @return None
 */
void AD7124_Reset(sAd7124 * ad7124)
{
	uint8_t data [] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
	SpiSelect(ad7124->spiPort);
	SpiWrite(ad7124->spiPort, data, 8);
	SpiDeSelect(ad7124->spiPort);
}

/**
 * @brief Fill a sAdcStatus struct with the latest status data from the ADC
 * @return None, the returned data is passed back by reference
 */
void AD7124_GetStatus(sAd7124 * ad7124, sAd7124Status * status)
{
	status->status 		= AD7124_Read(ad7124, AD7124_STATUS);
	status->id 			= AD7124_Read(ad7124, AD7124_ID);
	status->channel 	= AD7124_Read(ad7124, AD7124_CH_00);
	status->offset 		= AD7124_Read(ad7124, AD7124_OFFSET_00);
	status->filter 		= AD7124_Read(ad7124, AD7124_FILTER_00);
	status->config 		= AD7124_Read(ad7124, AD7124_CONFIG_00);
	status->control 	= AD7124_Read(ad7124, AD7124_ADC_CTRL);
	status->io1 		= AD7124_Read(ad7124, AD7124_IO_CTRL_1);
	status->io2 		= AD7124_Read(ad7124, AD7124_IO_CTRL_2);
	status->error 		= AD7124_Read(ad7124, AD7124_ERROR);
	status->error_en 	= AD7124_Read(ad7124, AD7124_ERROR_EN);
	status->gain 		= AD7124_Read(ad7124, AD7124_GAIN_00);
}

/**
 * @brief Is data acquisition done for this chip?
 * @param ad7124 The ADC to check
 * @return 1 if done, 0 if its still working
 */
uint8_t AD7124_IsAcqDone(sAd7124 * ad7124)
{
	return ad7124->lastChannel == ad7124->maxChannel;
}

/**
 * @brief Trigger a new conversion
 * @param ad7124 The ADC to trigger
 * @return None
 */
uint8_t AD7124_TriggerAcq(sAd7124 * ad7124)
{
	ad7124->lastChannel = 0;
	uint16_t config = AD7124_CTRL_MODE_SNGL | AD7124_CTRL_PWR_MODE_FULL;
	AD7124_Write(ad7124, AD7124_ADC_CTRL, config);
	return HAL_OK;
}

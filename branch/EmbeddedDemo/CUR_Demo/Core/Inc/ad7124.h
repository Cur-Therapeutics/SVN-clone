/********************************************************************
*
*   ad7124.h
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
#ifndef INC_AD7124_H_
#define INC_AD7124_H_

#include "spi.h"

/**
 * Acquisition states
 * Control the sequence of acquisitions on the three AD7124 chips
 */
typedef enum
{
	eAD7124_States_WAIT,
	eAD7124_States_ACQUIRE,
} eAD7124_States;

/**
 * Chips in use
 */
typedef enum
{
	eAD7124_PRESSURE,
} eAd7124Ids;

/**
 * Channel counts
 */
#define AD7124_MAX_CH		(1)	// Zero based index

/**
 * Number of possible channels in each AD7124
 */
#define AD7124_CHANNEL_COUNT (1)

/**
 * AD7124 instance
 */
typedef struct
{
	uint8_t id;
	sSpi * spiPort;

	// Channel configuration
	uint16_t channelConfig[AD7124_CHANNEL_COUNT];

	// Stored data
	uint32_t lastCounts [AD7124_CHANNEL_COUNT];
	float lastVoltage [AD7124_CHANNEL_COUNT];
	float lastEng [AD7124_CHANNEL_COUNT];
	uint16_t lastChannel;
	uint16_t maxChannel;
} sAd7124;

/**
 * AD7124 Register contents
 */
typedef struct
{
	uint8_t regNum;
	uint32_t value;
	uint8_t len;
	uint8_t mode;
} sAD7124Register;

/**
 * Register mode
 */
typedef enum
{
	AD7124READ,
	AD7124WRITE,
	AD7124READWRITE,
} eAD7124RegMode;

/**
 * Register numbers
 */
typedef enum
{
	AD7124_STATUS,
	AD7124_ADC_CTRL,
	AD7124_DATA,
	AD7124_IO_CTRL_1,
	AD7124_IO_CTRL_2,
	AD7124_ID,
	AD7124_ERROR,
	AD7124_ERROR_EN,
	AD7124_MCLK_COUNT,
	AD7124_CH_00,
	AD7124_CH_01,
	AD7124_CH_02,
	AD7124_CH_03,
	AD7124_CH_04,
	AD7124_CH_05,
	AD7124_CH_06,
	AD7124_CH_07,
	AD7124_CH_08,
	AD7124_CH_09,
	AD7124_CH_10,
	AD7124_CH_11,
	AD7124_CH_12,
	AD7124_CH_13,
	AD7124_CH_14,
	AD7124_CH_15,
	AD7124_CONFIG_00,
	AD7124_CONFIG_01,
	AD7124_CONFIG_02,
	AD7124_CONFIG_03,
	AD7124_CONFIG_04,
	AD7124_CONFIG_05,
	AD7124_CONFIG_06,
	AD7124_CONFIG_07,
	AD7124_FILTER_00,
	AD7124_FILTER_01,
	AD7124_FILTER_02,
	AD7124_FILTER_03,
	AD7124_FILTER_04,
	AD7124_FILTER_05,
	AD7124_FILTER_06,
	AD7124_FILTER_07,
	AD7124_OFFSET_00,
	AD7124_OFFSET_01,
	AD7124_OFFSET_02,
	AD7124_OFFSET_03,
	AD7124_OFFSET_04,
	AD7124_OFFSET_05,
	AD7124_OFFSET_06,
	AD7124_OFFSET_07,
	AD7124_GAIN_00,
	AD7124_GAIN_01,
	AD7124_GAIN_02,
	AD7124_GAIN_03,
	AD7124_GAIN_04,
	AD7124_GAIN_05,
	AD7124_GAIN_06,
	AD7124_GAIN_07,
} eAD7124RegisterNums;

/**
 * Communications register
 */
#define AD7124_COMMS_READ	0x40
#define AD7124_COMMS_WEN	0x80

/**
 * Status Register Values
 */
#define AD7124_STATUS_NRDY				0x80
#define AD7124_STATUS_CH_ACTIVE_MASK	(0x000F)

/**
 * Device ID, stored in the ID register 0x05
 * Two possible values depending on the version of the chip purchased
 */
#define AD7124_DEVICE_ID	0x04
#define AD7124_DEVICE_ID2	0x07
#define AD7124_DEVICE_ID3	0x14

/**
 * ADC Ctrl Register Values
 */
#define AD7124_CTRL_PWR_MODE_FULL	0x80
#define AD7124_CTRL_PWR_MODE_MID	0x40
#define AD7124_CTRL_PWR_MODE_LO		0x00

#define AD7124_CTRL_MODE_CONT		0x00
#define AD7124_CTRL_MODE_SNGL		0x04
#define AD7124_CTRL_REF_ENABLE		0x100

#define AD7124_CTRL_DATA_STATUS		0x400

/**
 * Channel register values
 * These select the analog inputs (positive and negative) as well as the setup to connect to
 * Channels can be enabled or disabled
 */
#define AD7124_CHANNEL_ENABLE		(0x8000)

#define AD7124_CHANNEL_AIN_POS_00	(0x0000)
#define AD7124_CHANNEL_AIN_POS_01	(0x0020)
#define AD7124_CHANNEL_AIN_POS_02	(0x0040)
#define AD7124_CHANNEL_AIN_POS_03	(0x0060)
#define AD7124_CHANNEL_AIN_POS_04	(0x0080)
#define AD7124_CHANNEL_AIN_POS_05	(0x00A0)
#define AD7124_CHANNEL_AIN_POS_06	(0x00C0)
#define AD7124_CHANNEL_AIN_POS_07	(0x00E0)

#define AD7124_CHANNEL_AIN_NEG_00	(0x0000)
#define AD7124_CHANNEL_AIN_NEG_01	(0x0001)
#define AD7124_CHANNEL_AIN_NEG_02	(0x0002)
#define AD7124_CHANNEL_AIN_NEG_03	(0x0003)
#define AD7124_CHANNEL_AIN_NEG_04	(0x0004)
#define AD7124_CHANNEL_AIN_NEG_05	(0x0005)
#define AD7124_CHANNEL_AIN_NEG_06	(0x0006)
#define AD7124_CHANNEL_AIN_NEG_07	(0x0007)

// A setup refers to a set of four registers; analog config, filter, offset, and gain
// Eight different setups are available to be selected, or use one for all channels if you'd like
#define AD7124_CHANNEL_SETUP_00		(0x0000)
#define AD7124_CHANNEL_SETUP_01		(0x1000)
#define AD7124_CHANNEL_SETUP_02		(0x2000)
#define AD7124_CHANNEL_SETUP_03		(0x3000)
#define AD7124_CHANNEL_SETUP_04		(0x4000)
#define AD7124_CHANNEL_SETUP_05		(0x5000)
#define AD7124_CHANNEL_SETUP_06		(0x6000)
#define AD7124_CHANNEL_SETUP_07		(0x7000)

/**
 * ADC Configuration register values
 * Controls channel configuration, buffer selection, reference select, and gain select
 */
#define AD7124_CONFIG_UNIPOLAR		(0x0000)
#define AD7124_CONFIG_BIPOLOR		(0x0800)

#define AD7124_CONFIG_REFSEL_1		(0x0000)
#define AD7124_CONFIG_REFSEL_2		(0x0008)
#define AD7124_CONFIG_REFSEL_INT	(0x0010)
#define AD7124_CONFIG_REFSEL_AVDD	(0x0018)

#define AD7124_CONFIG_GAIN_1		(0x0000)	// +/- 2.5 V
#define AD7124_CONFIG_GAIN_2		(0x0001)	// +/- 1.25 V
#define AD7124_CONFIG_GAIN_4		(0x0002)	// +/- 625 mV
#define AD7124_CONFIG_GAIN_8		(0x0003)	// +/- 312.5 mV
#define AD7124_CONFIG_GAIN_16		(0x0004)	// +/- 156.25 mV
#define AD7124_CONFIG_GAIN_32		(0x0005)	// +/- 78.125 mV
#define AD7124_CONFIG_GAIN_64		(0x0006)	// +/- 39.06 mV
#define AD7124_CONFIG_GAIN_128		(0x0007)	// +/- 19.53 mV

#define AD7124_CONFIG_AINP_BUF_EN	(0x40)
#define AD7124_CONFIG_AINN_BUF_EN	(0x20)

#define AD7124_CONFIG_REFP_BUF_EN	(0x100)
#define AD7124_CONFIG_REFN_BUF_EN	(0x80)

/**
 * IO Control 1 Register Values
 */
#define AD7124_IOCTRL1_IOUT0_IEXC_OFF		(0x0000)
#define AD7124_IOCTRL1_IOUT0_50UA			(0x0800)
#define AD7124_IOCTRL1_IOUT0_100UA			(0x1000)
#define AD7124_IOCTRL1_IOUT0_250UA			(0x1800)
#define AD7124_IOCTRL1_IOUT0_500UA			(0x2000)
#define AD7124_IOCTRL1_IOUT0_750UA			(0x2800)
#define AD7124_IOCTRL1_IOUT0_1000UA			(0x3000)
#define AD7124_IOCTRL1_IOUT0_01UA			(0x3800)

#define AD7124_IOCTRL1_IOUT1_IEXC_OFF		(0x0000)
#define AD7124_IOCTRL1_IOUT1_50UA			(0x0100)
#define AD7124_IOCTRL1_IOUT1_100UA			(0x0200)
#define AD7124_IOCTRL1_IOUT1_250UA			(0x0300)
#define AD7124_IOCTRL1_IOUT1_500UA			(0x0400)
#define AD7124_IOCTRL1_IOUT1_750UA			(0x0500)
#define AD7124_IOCTRL1_IOUT1_1000UA			(0x0600)
#define AD7124_IOCTRL1_IOUT1_01UA			(0x0700)

#define AD7124_IOCTRL1_IOUT0_CH0			(0x0000)
#define AD7124_IOCTRL1_IOUT0_CH1			(0x0001)
#define AD7124_IOCTRL1_IOUT0_CH2			(0x0004)
#define AD7124_IOCTRL1_IOUT0_CH3			(0x0005)
#define AD7124_IOCTRL1_IOUT0_CH4			(0x000A)
#define AD7124_IOCTRL1_IOUT0_CH5			(0x000B)
#define AD7124_IOCTRL1_IOUT0_CH6			(0x000E)
#define AD7124_IOCTRL1_IOUT0_CH7			(0x000F)

#define AD7124_IOCTRL1_IOUT1_CH0			(0x0000)
#define AD7124_IOCTRL1_IOUT1_CH1			(0x0010)
#define AD7124_IOCTRL1_IOUT1_CH2			(0x0040)
#define AD7124_IOCTRL1_IOUT1_CH3			(0x0050)
#define AD7124_IOCTRL1_IOUT1_CH4			(0x00A0)
#define AD7124_IOCTRL1_IOUT1_CH5			(0x00B0)
#define AD7124_IOCTRL1_IOUT1_CH6			(0x00E0)
#define AD7124_IOCTRL1_IOUT1_CH7			(0x00F0)

/**
 * Filter Register Values
 * 3 Bytes long
 */
#define AD7124_FILTER_SINC4					(0x000000)
#define AD7124_FILTER_SINC3					(0x400000)
#define AD7124_FILTER_SINC4_FAST			(0x800000)
#define AD7124_FILTER_SINC3_FAST			(0xA00000)
#define AD7124_FILTER_POST					(0xE00000)

/**
 * Conversion values
 */
#define AD7124_CONV_SCALE_V			((2.49f/16777216.0f)*2.0f*2.0f)
#define AD7124_CONV_OFFSET_V		(8388608.0f)
#define AD7124_CONV_VREF_OFFSET		(0.249f)

#define AD7124_CONV_SCALE_BRIDGE	(0.0000022183964f)
#define AD7124_CONV_V_TO_PSI		(5.0f)

/**
 * Functions
 */
void AD7124_Init();
void AD7124_Drive();

uint32_t AD7124_GetLastCount(sAd7124 * ad7124, int idx);
float AD7124_GetLastVolts(sAd7124 * ad7124, int idx);
float AD7124_GetLastEng(sAd7124 * ad7124, int idx);
uint32_t AD7124_Read(sAd7124 * ad7124, uint32_t reg);
void AD7124_Write(sAd7124 * ad7124, uint32_t reg, uint32_t val);
void AD7124_Reset(sAd7124 * ad7124);
void AD7124_GetStatus(sAd7124 * ad7124, sAd7124Status * status);

uint8_t AD7124_IsAcqDone(sAd7124 * ad7124);
uint8_t AD7124_TriggerAcq(sAd7124 * ad7124);

extern sAd7124 * ad7124Array [];

#endif /* INC_AD7124_H_ */

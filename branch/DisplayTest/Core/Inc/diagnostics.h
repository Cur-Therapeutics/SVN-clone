/********************************************************************
*
*   diagnostics.h
*
*   Description:    Provides diagnostics communication over UART
*
*   Copyright NextPhase Medical, Inc. 2026 -- All rights reserved.
*
*--------------------------------------------------------------------
*
*   Revision History:
*
*   Rev.    | Date      | Name              | Description
*   1       | 08/14/19  | Brian Compter     | Created.
*
********************************************************************/

#ifndef DIAGNOSTICS_H
#define DIAGNOSTICS_H

#include "touch.h"
#include "rtc.h"
#include "ospiflash.h"

/**
 * From main, used in Arm Status message
 */
extern uint32_t gLastIdleTicks;
extern uint32_t gMinIdleTicks;
extern uint32_t gMaxIdleTicks;
extern uint32_t gSkippedTicks;

/**
 * The start byte is always the first byte of any communication
 */
#define START_BYTE 0x43

/**
 * Receive buffer size and count
 * The ARM will keep a queue of RX_BUFFER_COUNT commands each up to RX_BUFFER_SIZE bytes long
 */
//#define RX_BUFFER_SIZE 	1024
#define RX_BUFFER_SIZE 	600
#define RX_BUFFER_COUNT 16

/**
 * RX state used to control reception progress
 */
#define RX_STATE_HEADER		0
#define RX_STATE_PAYLOAD 	1

/**
 * Operation types
 */
#define READ		0
#define WRITE		1
#define ERASE		2
#define MASS_ERASE	3

/**
 * Diag Commands
 * This enum MUST match the one found in the MeiraGtx C# code
 */
typedef enum
{
		eDIAG_NOP,
		eDIAG_HELLO,
		eDIAG_STATUS,
		eDIAG_LCD_DATA,
		eDIAG_LCD_DATA_ACK,
		eDIAG_LCD_SET_DISPLAY,
		eDIAG_LCD_BKLIGHT_ON,
		eDIAG_LCD_BKLIGHT_OFF,
		eDIAG_LCD_BKLIGHT_SET,
		eDIAG_TOUCH_INIT,
		eDIAG_TOUCH_READ,
		eDIAG_TOUCH_MODE,
		eDIAG_TOUCH_CAL,
		eDIAG_RTC_STATUS,
		eDIAG_RTC_WRITE,
		eDIAG_FLASH_STATUS,
		eDIAG_FLASH_ID,
		eDIAG_FLASH_READ,
		eDIAG_FLASH_WRITE,
		eDIAG_FLASH_ACK,
		eDIAG_FLASH_ERASE,
		eDIAG_FLASH_MASS_ERASE,
		eDIAG_FLASH_BURN,
		eDIAG_FLASH_RESET,
		eDIAG_FLASH_CLEAR_PROG,
		eDIAG_AD7124_GET_STATUS,
		eDIAG_AD7124_REG_WRITE,
		eDIAG_AD7124_REG_READ,
		eDIAG_AD7124_INIT,
		eDIAG_AD7124_RESET,
		eDIAG_AD7124_READ_DATA,
		eDIAG_ACCEL_READ,
	eDIAG_Count
} eDIAG_Commands;

/**
 * Command Header
 * Precedes all communications to and from the ARM
 */
typedef struct __attribute__((packed, aligned(1)))
{
	uint8_t startByte;
	uint8_t seqId;
	uint8_t command;
	uint16_t size;
	uint8_t checksum;
} sDIAG_Header;

/**
 * RTC status and write
 */
typedef struct __attribute__((packed, aligned(1)))
{
	uint32_t status;
	RTC_DateTime dateTime;
}sDIAG_Rtc_Status;

/**
 * Set the state machine state
 */
typedef struct __attribute__((packed, aligned(1)))
{
	uint32_t state;
} sDIAG_SetState;

/**
 * Hello message used to confirm communications
 */
typedef struct __attribute__((packed, aligned(1)))
{
	uint8_t hello;
} sDIAG_Hello;

/**
 * Status Message
 * Includes version, status bit field, and system tick
 */
typedef struct __attribute__((packed, aligned(1)))
{
	uint8_t versionMajor;
	uint8_t versionMinor;
	uint8_t versionBuild;
	uint8_t reserved;
	uint32_t sysTicks;
	uint32_t idleTicks;
	uint32_t skippedTicks;
	uint32_t minIdle;
	uint32_t maxIdle;
	uint32_t state;
	uint32_t health;
	uint64_t errors;
}sDIAG_Status;

/**
 * LCD Data
 */
typedef struct __attribute__((packed, aligned(1)))
{
	uint32_t address;
	uint32_t count;
	uint8_t data [512];
}sDIAG_LCD_Data;

/**
 * LCD Data Ack
 */
typedef struct __attribute__((packed, aligned(1)))
{
	uint32_t address;
	uint32_t ack;
}sDIAG_LCD_Data_Ack;

/**
 * Set Display Window
 */
typedef struct __attribute__((packed, aligned(1)))
{
	uint8_t window;
} sDIAG_LCD_Window;

/**
 * Set Backlight
 */
typedef struct __attribute__((packed, aligned(1)))
{
	uint16_t value;
} sDIAG_LCD_Backlight;

/**
 * ADC Status
 */
typedef struct __attribute__((packed, aligned(1)))
{
	uint8_t status;
	uint16_t control;
	uint32_t io1;
	uint32_t io2;
	uint8_t id;
	uint32_t error;
	uint32_t error_en;
	uint16_t channel;
	uint16_t config;
	uint16_t filter;
	uint32_t offset;
} sAdcStatus;

/**
 * Touch read
 */
typedef struct __attribute__((packed, aligned(1)))
{
	uint16_t xPos;
	uint16_t yPos;
	uint8_t  mode;
	uint16_t xPosRaw;
	uint16_t yPosRaw;
}sDIAG_Touch_Read;

/**
 * Touch mode
 */
typedef struct __attribute__((packed, aligned(1)))
{
	uint8_t mode;
}sDIAG_Touch_Mode;

/**
 * Touch calibration
 */
typedef struct __attribute__((packed, aligned(1)))
{
	uint8_t 			opType;
	sTouchCalibration 	calValues;
}sDIAG_Touch_Cal;

/**
 * Flash Id
 */
typedef struct __attribute__((packed, aligned(1)))
{
	uint8_t manufactureId;
	uint8_t memInterface;
	uint8_t density;
	uint8_t idLen;
	uint8_t config;
	uint8_t family;
	uint64_t uniqueId;
} sDIAG_Flash_Id;

/**
 * Flash Status
 */
typedef struct __attribute__((packed, aligned(1)))
{
	uint8_t statusReg1;
	uint8_t statusReg2;

	uint8_t configReg1;
	uint8_t configReg2;
	uint8_t configReg3;
	uint8_t configReg4;
	uint8_t configReg5;

	sFlashIds ids;

} sDIAG_Flash_Status;

/**
 * Flash read / erase / mass erase
 */
typedef struct __attribute__((packed, aligned(1)))
{
	uint32_t address;
	uint32_t count;
} sDIAG_Flash_Address;

/**
 * Flash Data
 */
typedef struct __attribute__((packed, aligned(1)))
{
	uint32_t address;
	uint32_t count;
	uint8_t data [512];
}sDIAG_Flash_Data;

/**
 * Flash Ack
 */
typedef struct __attribute__((packed, aligned(1)))
{
	uint32_t address;
	uint8_t result;
}sDIAG_Flash_Ack;

/**
 * AD7124 Register Read
 */
typedef struct __attribute__((packed, aligned(1)))
{
	uint8_t chipId;
	uint32_t reg;
	uint32_t data;
} sAd7124RegRead;

/**
 * AD7124 Register Write
 */
typedef struct __attribute__((packed, aligned(1)))
{
	uint8_t chipId;
	uint32_t reg;
	uint32_t val;
} sAd7124RegWrite;

/**
 * AD7124 Read
 */
typedef struct __attribute__((packed, aligned(1)))
{
	uint8_t 	chipId;
	uint32_t 	counts;
	float 		engValue;
	float       mLastVoltage;
	float       mFilterAvg;
} sAd7124Read;

/**
 * AD7124 Status
 */
typedef struct __attribute__((packed, aligned(1)))
{
	uint8_t chipId;
	uint8_t status;
	uint16_t control;
	uint32_t io1;
	uint32_t io2;
	uint8_t id;
	uint32_t error;
	uint32_t error_en;
	uint16_t channel;
	uint16_t config;
	uint32_t filter;
	uint32_t offset;
	uint32_t gain;
} sAd7124Status;

/**
 * Accel Read
 */
typedef struct __attribute__((packed, aligned(1)))
{
	uint32_t 	x;
	uint32_t 	y;
	uint32_t 	z;
} sAccelRead;

/**
 * Command Message
 */
typedef struct
{
	sDIAG_Header head;
	union __attribute__((packed, aligned(2)))
	{
		sDIAG_Hello				hello;
		sDIAG_Status 			armStatus;
		sAdcStatus				adcStatus;
		sDIAG_LCD_Data			lcdData;
		sDIAG_LCD_Data_Ack		lcdDataAck;
		sDIAG_LCD_Window		lcdSetWindow;
		sDIAG_LCD_Backlight		lcdSetBacklight;
		sDIAG_Touch_Read		touchRead;
		sDIAG_Touch_Mode		touchMode;
		sDIAG_Touch_Cal			touchCal;
		sDIAG_Rtc_Status		rtcStatus;
		sDIAG_Flash_Id			flashId;
		sDIAG_Flash_Status		flashStatus;
		sDIAG_Flash_Data		flashData;
		sDIAG_Flash_Ack			flashAck;
		sDIAG_Flash_Address		flashAddress;
		sAd7124RegRead			ad7124RegRead;
		sAd7124RegWrite			ad7124RegWrite;
		sAd7124Read				ad7124Read;
		sAd7124Status			ad7124Status;
		sAccelRead				accelRead;
	};
} sDIAG_Command;

/**
 * Diagnostic functions
 */
void DIAG_Init();
void DIAG_Drive();
void DIAG_Process(uint8_t * data);
void DIAG_Send(sDIAG_Command * rx, sDIAG_Command * tx);
int DIAG_SendEx(sDIAG_Command * rx, sDIAG_Command * tx, int bufferSize);

#endif

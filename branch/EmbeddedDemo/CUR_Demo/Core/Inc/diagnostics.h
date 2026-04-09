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
*   1       | 03/13/26  | Brian Compter     | Created.
*
********************************************************************/

#ifndef DIAGNOSTICS_H
#define DIAGNOSTICS_H

#include "main.h"


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
#define START_BYTE 0x46

/**
 * Receive buffer size and count
 * The ARM will keep a queue of RX_BUFFER_COUNT commands each up to RX_BUFFER_SIZE bytes long
 */
#define RX_BUFFER_SIZE 	600
#define RX_BUFFER_COUNT 16

/**
 * RX state used to control reception progress
 */
#define RX_STATE_HEADER		0
#define RX_STATE_PAYLOAD 	1


/**
 * Diag Commands
 * This enum MUST match the one found in the diagnostics C# code
 */
typedef enum
{
	eDIAG_NOP,
	eDIAG_HELLO,
	eDIAG_STATUS,
	eDIAG_DATA,
	eDIAG_AD7124_GET_STATUS,
	eDIAG_AD7124_REG_WRITE,
	eDIAG_AD7124_REG_READ,
	eDIAG_AD7124_INIT,
	eDIAG_AD7124_RESET,
	eDIAG_AD7124_READ_DATA,
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
 * Hello message used to confirm communications
 */
typedef struct __attribute__((packed, aligned(1)))
{
	uint32_t sysTicks;
	uint8_t data [32];
} sDIAG_Hello;

/**
 * Status Message
 * Includes version, status bit field, and system ticks
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
}sDIAG_Status;

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
 * Command Message
 */
typedef struct
{
	sDIAG_Header head;
	union
	{
		sDIAG_Hello				hello;
		sDIAG_Status 			armStatus;
		//sDIAG_Data				data;
		sAd7124RegRead			adc7124RegRead;
		sAd7124RegWrite			adc7124RegWrite;
		sAd7124Read				adc7124Read;
		sAd7124Status			adc7124Status;
	};
} sDIAG_Command;

/**
 * Diagnostic functions
 */
void DIAG_Init(void);
void DIAG_Drive(void);
void DIAG_Process(uint8_t * data);
void DIAG_Send(sDIAG_Command * rx, sDIAG_Command * tx);
void DiagInterrupt(UART_HandleTypeDef * huart);

extern UART_HandleTypeDef huart1;		// Diagnostics

#endif

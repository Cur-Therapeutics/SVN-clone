/********************************************************************
 *
 *   diagnostics.c
 *
 *   Description:    Provides diagnostics communication over UART
 *
 *   Copyright NextPhase Medical, Inc. 2019 -- All rights reserved.
 *
 *--------------------------------------------------------------------
 *
 *   Revision History:
 *
 *   Rev.    | Date      | Name              | Description
 *   1       | 08/14/19  | Brian Compter     | Created.
 *
 ********************************************************************/

#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "main.h"
#include "diagnostics.h"
#include "faulthandler.h"
#include "health.h"
#include "version.h"
#include "string.h"
#include "lcd.h"
#include "backlight.h"

/**
 * Reference to the uart instance
 */
extern UART_HandleTypeDef huart4;		// Diagnostics

/**
 * Tracks the current Rx state
 */
uint8_t gRxState = RX_STATE_HEADER;

/**
 * Rx Buffer to hold received data
 */
uint8_t gRxBuffer [RX_BUFFER_COUNT][RX_BUFFER_SIZE];

#define DATABYTE0 sizeof(sDIAG_Header)

/**
 * Head and tail indexes to mark our position in the gRxBuffer queue
 */
uint8_t gRxHead = 0;
uint8_t gRxTail = 0;

/**
 * Used to detect communication timeouts caused by synchronization issues
 */
uint8_t gComTimer = 0;
#define DIAG_TIMEOUT 128

/**
 * Diagnostics counters
 * Counts the number of different error types
 */
uint32_t gDiagBadStartByteCount = 0;
uint32_t gDiagOverflowCount 	= 0;
uint32_t gDiagBadChecksumCount 	= 0;
uint32_t gDiagInvalidCmdCount 	= 0;
uint32_t gDiagInvalidSizeCount 	= 0;
uint32_t gDiagTimeoutCount 		= 0;
uint32_t gDiagBadTx				= 0;

/**
 * Command message used to reply to the diagnostics application
 */
sDIAG_Command gDiagReply;

/**
 * Internal functions
 */
void _DiagInterrupt(UART_HandleTypeDef * huart);

/**
 * @brief  Initialize the diagnostics Rx process
 * @retval None
 */
void DIAG_Init()
{
	// Initialize command reply
	gDiagReply.head.startByte = START_BYTE;

	// Check state
	HAL_UART_StateTypeDef state = HAL_UART_GetState(&huart4);
	if (state == HAL_UART_STATE_READY)
	{
		HealthUpdate(HEALTH_URT, HEALTH_GOOD);
	}

	// Begin receiving command header
	HAL_UART_Receive_IT(&huart4, gRxBuffer[gRxHead], sizeof(sDIAG_Header));
}

/**
 * @brief  Process received diagnostics commands in the gRxBuffer queue
 * 		Maintain communications synchronization
 * @param  None
 * @retval None
 */
void DIAG_Drive()
{
	// Update subsystem health
	HAL_UART_StateTypeDef state = HAL_UART_GetState(&huart4);
	if (state == HAL_UART_STATE_ERROR || state == HAL_UART_STATE_RESET)
	{
		HealthUpdate(HEALTH_URT, HEALTH_BAD);
	}

	// Handle communications timeouts
	if (huart4.RxXferCount != huart4.RxXferSize && ++gComTimer > DIAG_TIMEOUT)
	{
		gDiagTimeoutCount++;

		// Cancel existing Rx interrupt
		HAL_UART_AbortReceive_IT(&huart4);

		// Begin receiving a new command header
		HAL_StatusTypeDef result = HAL_UART_Receive_IT(&huart4, gRxBuffer[gRxHead], sizeof(sDIAG_Header));

		// If we failed to restart receiving don't reset our comm timer so we will try again on the next pass
		if (result == HAL_OK)
			gComTimer = 0;

		return;
	}

	// Handle communications lockups
	if (gRxState == RX_STATE_HEADER && ((state & HAL_UART_STATE_BUSY_RX) != HAL_UART_STATE_BUSY_RX))
	{
		gComTimer = DIAG_TIMEOUT;	// Trigger a timeout event
		huart4.RxXferCount = 1;
	}

	// Skip processing if the transmitter is busy
	if ( (state & HAL_UART_STATE_BUSY_TX) == HAL_UART_STATE_BUSY_TX )
		return;

	// Process received commands if the transmitter is ready
	if (gRxHead != gRxTail)
	{
		// Process current tail message
		DIAG_Process(gRxBuffer[gRxTail]);

		// Zero out processed command to avoid possible confusion later
		memset(gRxBuffer[gRxTail], 0, RX_BUFFER_SIZE);

		// Increment the tail
		gRxTail++;
		gRxTail &= (RX_BUFFER_COUNT-1);	// Rollover
	}
}

/**
 * @brief  Verify and process a command
 * @param  data The raw data to process
 * @retval None
 */
void DIAG_Process(uint8_t * data)
{
	// Cast to diagnostics command
	sDIAG_Command * cmd = (sDIAG_Command*)data;

	// Check for valid command type
	if (cmd->head.command >= eDIAG_Count)
	{
		gDiagInvalidCmdCount++;
		return;
	}

	// Checksum verification
	uint8_t checksumVerify = cmd->head.startByte + cmd->head.seqId + cmd->head.command + (cmd->head.size&0xFF) + (cmd->head.size>>8);
	for (int i = sizeof(cmd->head); i < cmd->head.size; i++)
	{
		checksumVerify += data[i];
	}
	if (checksumVerify != cmd->head.checksum)
	{
		gDiagBadChecksumCount++;
		return;
	}

	// Handle command type
	switch(cmd->head.command)
	{
	case eDIAG_NOP:
		/* INTENTIONALLY LEFT BLANK */
		break;

	case eDIAG_HELLO:
		gDiagReply.hello.hello = 0;
		DIAG_Send(cmd, &gDiagReply);
		break;

	case eDIAG_STATUS:
		gDiagReply.armStatus.versionMajor 	= BUILD_MAJOR;
		gDiagReply.armStatus.versionMinor 	= BUILD_MINOR;
		gDiagReply.armStatus.versionBuild 	= BUILD_COMPILE;
		gDiagReply.armStatus.sysTicks 		= HAL_GetTick();
		gDiagReply.armStatus.idleTicks		= gLastIdleTicks;
		gDiagReply.armStatus.skippedTicks	= gSkippedTicks;
		gDiagReply.armStatus.minIdle		= gMinIdleTicks;
		gDiagReply.armStatus.maxIdle		= gMaxIdleTicks;
		DIAG_Send(cmd, &gDiagReply);
		break;

	case eDIAG_LCD_DATA:
		// Copy data to the specified window
		memcpy( (uint8_t*)(WINDOW_0 + cmd->lcdData.address), cmd->lcdData.data, cmd->lcdData.count);

		// Ack/Nak the message
		cmd->head.command = eDIAG_LCD_DATA_ACK;
		gDiagReply.lcdDataAck.address = cmd->lcdData.address;
		gDiagReply.lcdDataAck.ack = 1;
		DIAG_Send(cmd, &gDiagReply);
		break;

	case eDIAG_LCD_SET_DISPLAY:
		LCD_SetDisplayWindow(cmd->lcdSetWindow.window);
		break;

	case eDIAG_LCD_BKLIGHT_ON:
		BacklightOn();
		break;

	case eDIAG_LCD_BKLIGHT_OFF:
		BacklightOff();
		break;

	case eDIAG_LCD_BKLIGHT_SET:
		BacklightSet(cmd->lcdSetBacklight.value);
		break;

	default:
		gDiagInvalidCmdCount++;
		break;

	}  // end select
}  // end DIAG_Process

/**
 * @brief  Rx Transfer completed callback.
 * @param  huart UART handle.
 * @retval None
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef * huart)
{
	// Check source of callback
	if (huart == &huart4)
	{
		_DiagInterrupt(huart);
	}
}  // end HAL_UART_RxCpltCallback

/**
 * @brief The RX received interrupt for the UART
 * @param huart The handle of the uart port
 * @return None
 */
void _DiagInterrupt(UART_HandleTypeDef * huart)
{
	/**
	 * Clear our timeout counter
	 */
	gComTimer = 0;

	/**
	 * Data received, are we handling the header or the payload?
	 */
	switch (gRxState)
	{
	case RX_STATE_HEADER:
		// Check for start byte
		if (((sDIAG_Header*)gRxBuffer[gRxHead])->startByte == (uint8_t)START_BYTE)
		{
			// Error check for invalid size
			if (((sDIAG_Header*)gRxBuffer[gRxHead])->size > RX_BUFFER_SIZE)
			{
				gDiagInvalidSizeCount++;
				gRxState = 0;
				HAL_UART_Receive_IT(huart, gRxBuffer[gRxHead], sizeof(sDIAG_Header));
				return;
			}

			// Check for header only commands, or continue to Rx the payload
			if (((sDIAG_Header*)gRxBuffer[gRxHead])->size == sizeof(sDIAG_Header))
			{
				// Command received (header only command)
				gRxHead++;
				gRxHead &= (RX_BUFFER_COUNT-1);	// Rollover

				// Detect overflow
				if (gRxHead == gRxTail)
				{
					gDiagOverflowCount++;
					HAL_UART_Receive_IT(huart, gRxBuffer[gRxHead], sizeof(sDIAG_Header));
				}

				// Prepare for next command
				HAL_UART_Receive_IT(huart, gRxBuffer[gRxHead], sizeof(sDIAG_Header));
			}
			else
			{
				// Rx the payload
				gRxState++;
				HAL_UART_Receive_IT(huart, &gRxBuffer[gRxHead][sizeof(sDIAG_Header)], ((sDIAG_Header*)gRxBuffer[gRxHead])->size - sizeof(sDIAG_Header));
			}
		}
		else
		{
			// Bad start byte
			gDiagBadStartByteCount++;
			HAL_UART_Receive_IT(huart, gRxBuffer[gRxHead], sizeof(sDIAG_Header));
		}
		break;

	case RX_STATE_PAYLOAD:
		// Command received!
		gRxHead++;
		gRxHead &= (RX_BUFFER_COUNT-1);	// Rollover

		// Begin next reception
		gRxState = 0;
		HAL_UART_Receive_IT(huart, gRxBuffer[gRxHead], sizeof(sDIAG_Header));
		break;

	default:
		// We should never get here!
		//FaultHandler(ERR_DIAG_UNKNOWN);
		break;

	}  // end switch
}

/**
 * @brief  Send a command to the diagnostics application
 * @param  rx The command we are replying to (used to populate reply fields)
 * @param  tx The command we are sending
 * @param  bufferSize Size of the data packet
 * @retval true/false
 */
int DIAG_SendEx(sDIAG_Command * rx, sDIAG_Command * tx, int bufferSize)
{
	// Copy header values from the received message
	tx->head.command = rx->head.command;
	tx->head.seqId = rx->head.seqId;

	// Set size based on command type
	tx->head.size = sizeof(sDIAG_Header) + bufferSize;

	// Calculate checksum
	uint8_t * data = (uint8_t*)tx;
	tx->head.checksum = tx->head.startByte + tx->head.seqId + tx->head.command + (tx->head.size&0xFF) + (tx->head.size>>8);
	for (int i = sizeof(sDIAG_Header); i < tx->head.size; i++)
	{
		tx->head.checksum += data[i];
	}

	// Send the data
	HAL_StatusTypeDef result = HAL_UART_Transmit_IT(&huart4, (uint8_t *)tx, tx->head.size);
	if (result != HAL_OK)
	{
		gDiagBadTx++;
	}

	return result == HAL_OK;
}

/**
 * @brief  Send a command to the diagnostics application
 * @param  rx The command we are replying to (used to populate reply fields)
 * @param  tx The command we are sending
 * @retval None
 */
void DIAG_Send(sDIAG_Command * rx, sDIAG_Command * tx)
{
	// Copy header values from the received message
	tx->head.command = rx->head.command;
	tx->head.seqId = rx->head.seqId;

	// Set size based on command type
	tx->head.size = sizeof(sDIAG_Header);
	switch (tx->head.command)
	{
		case eDIAG_HELLO:
			tx->head.size += sizeof(sDIAG_Hello);
			break;

		case eDIAG_STATUS:
			tx->head.size += sizeof(sDIAG_Status);
			break;
		default:
			// We should never get here!
			FaultHandler(ERR_DIAG_UNKNOWN);
			break;
	}

	// Calculate checksum
	uint8_t * data = (uint8_t*)tx;
	tx->head.checksum = tx->head.startByte + tx->head.seqId + tx->head.command + (tx->head.size&0xFF) + (tx->head.size>>8);
	for (int i = sizeof(tx->head); i < tx->head.size; i++)
	{
		tx->head.checksum += data[i];
	}

	// Send the data
	HAL_StatusTypeDef result = HAL_UART_Transmit_IT(&huart4, (uint8_t *)tx, tx->head.size);
	if (result != HAL_OK)
	{
		gDiagBadTx++;
	}
}

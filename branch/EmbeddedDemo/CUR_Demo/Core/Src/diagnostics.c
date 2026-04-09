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

#include "diagnostics.h"
#include "main.h"
#include <string.h>

uint16_t mTestCounter = 0;

/**
 * Reference to the uart instance
 */
UART_HandleTypeDef * pHuartDiags = &huart1;

/**
 * Tracks the current Rx state
 */
uint8_t gRxState = RX_STATE_HEADER;

/**
 * Rx Buffer to hold received data
 */
uint8_t gRxBuffer [RX_BUFFER_COUNT][RX_BUFFER_SIZE];

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
uint8_t mSeqId = 0;

/**
 * High speed data mode
 */
uint8_t mIsHighSpeedEnabled = 0;
uint16_t mHighSpeedTimer = 0;

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
uint32_t gDiagTxBusy			= 0;

/**
 * Command message used to reply to the diagnostics application
 */
sDIAG_Command gDiagReply;
sDIAG_Command gDiagData;

/**
 * Internal functions
 */
void _DiagInterrupt(UART_HandleTypeDef * huart);
void _DiagUpdateDeviceState(uint8_t deviceId, uint32_t state);

/**
  * @brief  Initialize the diagnostics Rx process
  * @retval None
  */
void DIAG_Init()
{
	// Initialize command reply
	gDiagReply.head.startByte 			= START_BYTE;
	gDiagData.head.startByte			= START_BYTE;
	gDiagData.head.command 				= eDIAG_DATA;

	// Check state
	HAL_UART_StateTypeDef state = HAL_UART_GetState(pHuartDiags);
	if (state == HAL_UART_STATE_READY)
	{
		//HealthUpdate(HEALTH_URT, HEALTH_GOOD);
	}

	// Begin receiving command header
	HAL_UART_Receive_IT(pHuartDiags, gRxBuffer[gRxHead], sizeof(sDIAG_Header));
}

/**
  * @brief  Process received diagnostics commands in the gRxBuffer queue
  * 		Maintain communications synchronization
  * @retval None
  */
void DIAG_Drive()
{
	// Update subsystem health
	HAL_UART_StateTypeDef state = HAL_UART_GetState(pHuartDiags);
	if (state == HAL_UART_STATE_ERROR || state == HAL_UART_STATE_RESET)
	{
		//HealthUpdate(HEALTH_URT, HEALTH_BAD);
	}

	// Handle communications timeouts
	if (pHuartDiags->RxXferCount != pHuartDiags->RxXferSize && ++gComTimer > DIAG_TIMEOUT)
	{
		gDiagTimeoutCount++;

		// Cancel existing Rx interrupt
		HAL_UART_AbortReceive_IT(pHuartDiags);

		// Begin receiving a new command header
		HAL_StatusTypeDef result = HAL_UART_Receive_IT(pHuartDiags, gRxBuffer[gRxHead], sizeof(sDIAG_Header));

		// If we failed to restart receiving don't reset our comm timer so we will try again on the next pass
		if (result == HAL_OK)
			gComTimer = 0;
		return;
	}

	// Handle communications lockups
	if (gRxState == RX_STATE_HEADER && ((state & HAL_UART_STATE_BUSY_RX) != HAL_UART_STATE_BUSY_RX))
	{
		gComTimer = DIAG_TIMEOUT;	// Trigger a timeout event
		pHuartDiags->RxXferCount = 1;
	}

	// Skip processing if the transmitter is busy
	if ( (state & HAL_UART_STATE_BUSY_TX) == HAL_UART_STATE_BUSY_TX )
	{
		gDiagTxBusy++;
		mHighSpeedTimer++;
		return;
	}

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
	// Helper variables
	uint8_t retval;
	uint8_t tmpId = 0;

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
			gDiagReply.hello.sysTicks = HAL_GetTick();
			DIAG_Send(cmd, &gDiagReply);
			break;

		case eDIAG_STATUS:
			gDiagReply.armStatus.versionMajor 	= VER_MAJOR;
			gDiagReply.armStatus.versionMinor 	= VER_MINOR;
			gDiagReply.armStatus.versionBuild 	= VER_BUILD;
			gDiagReply.armStatus.sysTicks 		= HAL_GetTick();
			gDiagReply.armStatus.idleTicks		= gLastIdleTicks;
			gDiagReply.armStatus.skippedTicks	= gSkippedTicks;
			gDiagReply.armStatus.minIdle		= gMinIdleTicks;
			gDiagReply.armStatus.maxIdle		= gMaxIdleTicks;
			gDiagReply.armStatus.state			= 0;

			DIAG_Send(cmd, &gDiagReply);
			break;

		case eDIAG_DATA:

			break;

		case eDIAG_AD7124_GET_STATUS:
			/*AD7124_GetStatus(ad7124Array[cmd->adc7124Status.chipId], &gDiagReply.adc7124Status);
			gDiagReply.adc7124Read.chipId = cmd->adc7124Status.chipId;
			DIAG_Send(cmd, &gDiagReply);*/
			break;

		case eDIAG_AD7124_REG_WRITE:
			//AD7124_Write(ad7124Array[cmd->adc7124Status.chipId], cmd->adc7124RegWrite.reg, cmd->adc7124RegWrite.val);
			break;

		case eDIAG_AD7124_REG_READ:
			/*gDiagReply.adc7124RegRead.data = AD7124_Read(ad7124Array[cmd->adc7124Status.chipId], cmd->adc7124RegRead.reg);
			gDiagReply.adc7124RegRead.chipId = cmd->adc7124Status.chipId;
			gDiagReply.adc7124RegRead.reg = cmd->adc7124RegRead.reg;
			DIAG_Send(cmd, &gDiagReply);*/
			break;

		case eDIAG_AD7124_INIT:
			//AD7124_Init(ad7124Array[cmd->adc7124Status.chipId]);
			break;

		case eDIAG_AD7124_RESET:
			//AD7124_Reset(ad7124Array[cmd->adc7124Status.chipId]);
			break;

		case eDIAG_AD7124_READ_DATA:
			/*gDiagReply.adc7124Read.counts = AD7124_GetLastCount(ad7124Array[cmd->adc7124Status.chipId], 0);
			gDiagReply.adc7124Read.mLastVoltage = AD7124_GetLastVolts(ad7124Array[cmd->adc7124Status.chipId], 0);
			gDiagReply.adc7124Read.engValue = AD7124_GetLastEng(ad7124Array[cmd->adc7124Status.chipId], 0);
			gDiagReply.adc7124Read.chipId = cmd->adc7124Read.chipId;
			DIAG_Send(cmd, &gDiagReply);*/
			break;

		default:
			gDiagInvalidCmdCount++;
			break;

	}  // end select
}  // end DIAG_Process

/**
 * @brief The RX received interrupt for the UART
 * @param huart The handle of the uart port
 * @return None
 */
void DiagInterrupt(UART_HandleTypeDef * huart)
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
		case eDIAG_STATUS:
			tx->head.size += sizeof(sDIAG_Status);
			break;

		case eDIAG_HELLO:
			tx->head.size += sizeof(sDIAG_Hello);
			break;

		case eDIAG_DATA:

			break;

		case eDIAG_AD7124_GET_STATUS:
			tx->head.size += sizeof(sAd7124Status);
			break;

		case eDIAG_AD7124_REG_READ:
			tx->head.size += sizeof(sAd7124RegRead);
			break;

		case eDIAG_AD7124_READ_DATA:
			tx->head.size += sizeof(sAd7124Read);
			break;

		default:
			// We should never get here!
			//FaultHandler(ERR_DIAG_UNKNOWN);
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
	HAL_StatusTypeDef result = HAL_UART_Transmit_IT(pHuartDiags, (uint8_t *)tx, tx->head.size);
	if (result != HAL_OK)
	{
		gDiagBadTx++;
	}
}

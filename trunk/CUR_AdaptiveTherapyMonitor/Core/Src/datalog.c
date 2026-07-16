/********************************************************************
*
*   datalog.c
*
*   Description:    Handles the storage of event data
*
*   Copyright NextPhase Medical, Inc. 2026 -- All rights reserved.
*
*--------------------------------------------------------------------
*
*   Revision History:
*
*   Rev.    | Date      | Name              | Description
*   1       | 07/14/26  | Brian Compter     | Created.
*
********************************************************************/

#include "main.h"
#include "datalog.h"
#include "statemachine.h"
#include "ospiflash.h"
#include "string.h"
#include "ad7124.h"
#include "pressure.h"

/**
 * Our state
 */
eDataLogState mDataLogState = eDataLogState_INIT;

/**
 * Our event header which tracks our total samples and what flash sectors are used
 */
sEventHeader mDataLogEventHeader;

/**
 * RAM buffers
 */
//uint8_t mDataLogBufferA [DATA_LOG_BUFFER_SIZE];
//uint8_t mDataLogBufferB [DATA_LOG_BUFFER_SIZE];

uint8_t * mDataLogBuffer = (uint8_t*)START_DATA_LOG_BUFFER;

/**
 * RAM buffer index
 */
uint32_t mBufferIndex = 0;

/**
 * @brief Initialize the data log system for use
 * @return None
 */
void DataLogInit()
{
	// Initialize our event information
	mDataLogEventHeader.numSamples = 0;
	mDataLogEventHeader.sectorBegin = 0;
	mDataLogEventHeader.sectorEnd = 0;

#ifdef NOTNOW
	// Read event header from sector 0
	FlashRead(START_DATA_LOG_EVENT_HEADER, (uint8_t*)&mDataLogEventHeader, sizeof(mDataLogEventHeader));
	if (mDataLogEventHeader.numSamples == 0xFFFFFFFF)
	{
		// Initialize our event information
		mDataLogEventHeader.numSamples = 0;
		mDataLogEventHeader.sectorBegin = 0;
		mDataLogEventHeader.sectorEnd = 0;

		OctalSpiFlashErase4KSector(START_DATA_LOG_EVENT_HEADER);
		FlashWrite(START_DATA_LOG_EVENT_HEADER, (uint8_t*)&mDataLogEventHeader, sizeof(mDataLogEventHeader));
	}

	// Determine where we need to start next event storage
	// ...
#endif
}

/**
 * @brief Perform periodic operations such as state transitions and flash writes / erases
 * @return None
 */
void DataLogDrive()
{
	// Handle state transitions based on the overall state machine
	switch (mDataLogState)
	{
		case eDataLogState_INIT:
			mDataLogState = eDataLogState_READY;
			break;

		case eDataLogState_READY:

			// Transition to first buffer when we begin measuring
			if (GetCurrentState() == eSTATE_MEASURING)
			{
				mDataLogEventHeader.numSamples = 0;
				mBufferIndex = 0;
				mDataLogState = eDataLogState_LOGGING_FIRST_BUFFER;
			}
			break;

		case eDataLogState_LOGGING_FIRST_BUFFER:
		case eDataLogState_LOGGING_BUFFERA:
		case eDataLogState_LOGGING_BUFFERB:

			// Transition back to ready if we complete measuring
			if (GetCurrentState() == eSTATE_COMPLETE)
			{
				mDataLogState = eDataLogState_READY;
			}
			break;
	}
}

/**
 * @brief Save a data sample to memory
 * @param data The sample to save
 * @return None
 */
void DataLogSaveSample()
{
	// Check state machine, only log if we are measuring data
	if (mDataLogState < eDataLogState_LOGGING_FIRST_BUFFER || mDataLogState > eDataLogState_LOGGING_BUFFERB)
		return;

	// Gather sample
	sDataSample sample = { HAL_GetTick(), ad7124.lastCounts, ad7124.lastEng, GetBaselinePressure()};

	// Store data sample
	memcpy(&mDataLogBuffer[mBufferIndex], (uint8_t*)&sample, sizeof(sDataSample));
	mBufferIndex += sizeof(sDataSample);

	// Increment samples
	mDataLogEventHeader.numSamples++;

#ifdef NOTNOW
	// Check state machine, only log if we are measuring data
	if (mDataLogState < eDataLogState_LOGGING_FIRST_BUFFER || mDataLogState > eDataLogState_LOGGING_BUFFERB)
		return;

	// Increment samples
	mDataLogEventHeader.numSamples++;

	switch (mDataLogState)
	{
		case eDataLogState_LOGGING_FIRST_BUFFER:
		case eDataLogState_LOGGING_BUFFERA:
			// Store in buffer A at mBufferIndex
			memcpy(&mDataLogBufferA[mBufferIndex], (uint8_t*)&data, sizeof(sDataSample));
			mBufferIndex += sizeof(sDataSample);
			break;

		case eDataLogState_LOGGING_BUFFERB:
			// Store in buffer B at mBufferIndex
			memcpy(&mDataLogBufferA[mBufferIndex], (uint8_t*)&data, sizeof(sDataSample));
			mBufferIndex += sizeof(sDataSample);
			break;

		default:
			/* Intentionally left blank */
			break;
	}

	// Check for RAM buffer full
#endif
}

/**
 * @brief Get event header information
 * @return A copy of our event header information
 */
sEventHeader DataLogGetEventHeader(void)
{
	return mDataLogEventHeader;
}

/**
 * @brief Get the memory address where a sample resides
 * @param sample The sample index
 * @return The address in memory where this sample index is stored
 */
uint32_t DataLogGetAddress(uint32_t sample)
{
	uint32_t offset = sample * sizeof(sDataSample);
	return offset + START_DATA_LOG_BUFFER;
}

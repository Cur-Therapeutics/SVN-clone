/********************************************************************
*
*   datalog.h
*
*   Description:    Handles the storage and exporting of event data
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

#ifndef INC_DATALOG_H_
#define INC_DATALOG_H_

/**
 * Start of data log buffer in external RAM ???
 */
#define START_DATA_LOG_BUFFER	(0x90339000)

/**
 * Start of data log in external flash
 */
#define START_DATA_LOG_FLASH	(0x480000)

/**
 * Start of data log event header
 */
#define START_DATA_LOG_EVENT_HEADER (0x0)

/**
 * Data log size, equal to one sector, 256 KBytes
 */
#define DATA_LOG_BUFFER_SIZE	(0x40000)

/**
 * Data log count, one working buffer and one for writing to flash
 */
#define DATA_LOG_COUNT			(2)

/**
 * Datalog states
 * Indicates how data is to be handled by the drive function
 */
typedef enum
{
	eDataLogState_INIT,
	eDataLogState_READY,
	eDataLogState_LOGGING_FIRST_BUFFER,
	eDataLogState_LOGGING_BUFFERA,
	eDataLogState_LOGGING_BUFFERB,
} eDataLogState;

/**
 * Datalog Flash states
 * Indicates flash operation states
 */
typedef enum
{
	eDataLogFlashState_IDLE,
	eDataLogFlashState_ERASE_WAIT,
	eDataLogFlashState_WRITE_WAIT,
} eDataLogFlashState;

/**
 * Data sample
 */
typedef struct
{
	uint32_t sysTick;
	uint32_t counts;
	float pressure;
	float barometric;
} sDataSample;

/**
 * Event, a collection of data samples
 */
typedef struct
{
	uint32_t sectorBegin;
	uint32_t sectorEnd;
	uint32_t numSamples;
} sEventHeader;

/**
 * Functions
 */
void DataLogInit(void);
void DataLogDrive(void);
void DataLogSaveSample(void);
sEventHeader DataLogGetEventHeader(void);
uint32_t DataLogGetAddress(uint32_t sample);

#endif /* INC_DATALOG_H_ */

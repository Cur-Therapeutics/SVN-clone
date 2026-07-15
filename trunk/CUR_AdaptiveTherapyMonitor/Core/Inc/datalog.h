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

} sEvent;

/**
 * Functions
 */
void DataLogSaveSample(sDataSample data);

#endif /* INC_DATALOG_H_ */

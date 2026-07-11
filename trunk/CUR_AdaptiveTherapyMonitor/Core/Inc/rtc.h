/********************************************************************
*
*   rtc.h
*
*   Description:    Tracks real time
*
*   Copyright NextPhase Medical, Inc. 2026 -- All rights reserved.
*
*--------------------------------------------------------------------
*
*   Revision History:
*
*   Rev.    | Date      | Name              | Description
*   1       | 08/16/19  | Brian Compter     | Created.
*
********************************************************************/

#ifndef RTC_H
#define RTC_H

/**
 * Reference to our RTC instance
 */
extern RTC_HandleTypeDef hrtc;

/**
 * Stores date and time from the RTC
 */
typedef struct
{
	uint8_t hour;
	uint8_t minute;
	uint8_t second;
	uint8_t month;
	uint8_t day;
	uint8_t year;
	uint8_t TimeFormat;  // Used for user-selected Meridian. RTC_HOURFORMAT12_AM / RTC_HOURFORMAT12_PM
} RTC_DateTime;

void RTC_Drive();
void RTC_SetDateTime(RTC_DateTime dt);
RTC_DateTime RTC_GetDateTime();
uint32_t RTC_GetStatus();
void RTC_UpdateTime(int hour, int minute);
void RTC_UpdateDate(int month, int day, int year);

int IsSameRTC_DateTimes(RTC_DateTime time1, RTC_DateTime time2);

char * RTC_DateTimeAsCSV(RTC_DateTime timestamp);
uint32_t RTC_ToEpochSeconds(RTC_DateTime dt);

/* Return Now as YYMMDDHHMMSS */
#define NOWString RTC_DateTimeAsCSV(RTC_GetDateTime())
#define NOWSECONDS RTC_ToEpochSeconds(RTC_GetDateTime())

#endif

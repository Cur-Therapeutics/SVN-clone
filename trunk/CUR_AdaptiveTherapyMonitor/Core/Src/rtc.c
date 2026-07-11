/********************************************************************
*
*   rtc.c
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

#include <stdio.h>
#include <time.h>
#include "main.h"
#include "rtc.h"
#include "health.h"
#include "faulthandler.h"

/**
  * @brief  Update RTC health
  * @retval None
  */
void RTC_Drive()
{
	// Update component health
	if (HAL_RTC_GetState(&hrtc) != HAL_RTC_STATE_ERROR && HAL_RTC_GetState(&hrtc) != HAL_RTC_STATE_RESET)
	{
		HealthSubsystemGood(eSystemRtc);
	}
	else
	{
		HealthSubsystemBad(eSystemRtc);
	}
}

/**
 * @brief Format a date time as a CSV formatted string
 * @param timestamp The RTC_DateTime
 * @return A char * with the formated text, null terminated
 */
char * RTC_DateTimeAsCSV(RTC_DateTime timestamp)
{
#define bufSize 100
	static char buffer[bufSize];
	sprintf(buffer, "%02d%02d%02d %02d:%02d:%02d",
			timestamp.year,timestamp.month,timestamp.day,
			timestamp.hour, timestamp.minute, timestamp.second);

	// Ensure return value is null terminated
	buffer[bufSize - 1] = 0;

	return buffer;
}

/**
  * @brief  Set the time and date in the RTC
  * @param  The time and date to store
  * @retval None
  */
void RTC_SetDateTime(RTC_DateTime dt)
{
	RTC_TimeTypeDef time;
	RTC_DateTypeDef date;

	time.Hours 					= dt.hour;
	time.Minutes 				= dt.minute;
	time.Seconds 				= dt.second;
	time.TimeFormat             = dt.TimeFormat;
	time.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
	time.StoreOperation = RTC_STOREOPERATION_SET;

	if (HAL_RTC_SetTime(&hrtc, &time, RTC_FORMAT_BIN) != HAL_OK)
	{
		HealthSubsystemBad(eSystemRtc);
	}

	date.Date 					= dt.day;
	date.Month 					= dt.month;
	date.WeekDay 				= 1;
	date.Year 					= dt.year;
	if (HAL_RTC_SetDate(&hrtc, &date, RTC_FORMAT_BIN) != HAL_OK)
	{
		HealthSubsystemBad(eSystemRtc);
	}
}

/**
  * @brief  Get the currently stored time and date from the RTC
  * @retval Stored time and date
  */
RTC_DateTime RTC_GetDateTime()
{
	RTC_DateTime retval;
	RTC_TimeTypeDef time;
	RTC_DateTypeDef date;

	HAL_RTC_GetTime(&hrtc, &time, RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&hrtc, &date, RTC_FORMAT_BIN);

	retval.hour = time.Hours;
	retval.minute = time.Minutes;
	retval.second = time.Seconds;
	retval.TimeFormat = time.TimeFormat;

	retval.day = date.Date;
	retval.month = date.Month;
	retval.year = date.Year;

	return retval;
}

/**
  * @brief  Get RTC Status
  * @retval RTC Status byte
  */
uint32_t RTC_GetStatus()
{
	return HAL_RTC_GetState(&hrtc);
}

/**
  * @brief  Update the RTC time
  * @param hour The hour
  * @param minute The minute
  * @retval None
  */
void RTC_UpdateTime(int hour, int minute)
{
	RTC_DateTime current = RTC_GetDateTime();
	current.hour = hour;
	current.minute = minute;
	current.second = 0;
	RTC_SetDateTime(current);
}

/**
  * @brief  Update the RTC date
  * @param month The month
  * @param day	The day
  * @param year The year
  * @retval None
  */
void RTC_UpdateDate(int month, int day, int year)
{
	RTC_DateTime current = RTC_GetDateTime();
	current.month = month;
	current.day = day;
	current.year = year;
	RTC_SetDateTime(current);
}

/**
 * @brief Determine if two datetimes are the same
 * @param time1, time2, The two datetimes to compare
 * @return 1 if they are the same, 0 otherwise
 */
int IsSameRTC_DateTimes(RTC_DateTime time1, RTC_DateTime time2)
{
	int isSame =
			(time1.year == time2.year)  &&
			(time1.month == time2.month)  &&
			(time1.day == time2.day)  &&
			(time1.hour == time2.hour)  &&
			(time1.minute == time2.minute)  &&
			(time1.second == time2.second);

	return isSame;
}

/**
 * @brief Convert a RTC datetime to seconds since epoch
 * @param dt The timedate to convert
 * @return The seconds since epoch
 */
uint32_t RTC_ToEpochSeconds(RTC_DateTime dt)
{
    struct tm t;

    // Handle 12-hour format
    uint8_t hour = dt.hour;
    if (dt.TimeFormat == RTC_HOURFORMAT12_PM && hour < 12)
        hour += 12;
    if (dt.TimeFormat == RTC_HOURFORMAT12_AM && hour == 12)
        hour = 0;

    // Fill tm structure
    t.tm_year = 2000 + dt.year - 1900;  // assuming RTC year is offset from 2000
    t.tm_mon  = dt.month - 1;           // tm_mon is 0–11
    t.tm_mday = dt.day;
    t.tm_hour = hour;
    t.tm_min  = dt.minute;
    t.tm_sec  = dt.second;
    t.tm_isdst = -1;                     // let system determine DST

    time_t epoch = mktime(&t);
    return (uint32_t)epoch;
}

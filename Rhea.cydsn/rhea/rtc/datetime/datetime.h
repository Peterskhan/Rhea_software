#pragma once
#ifndef DATETIME_H_INCLUDED
#define DATETIME_H_INCLUDED
    
/*********************************************************************************
 * Copyright (c) 2020 Peter Gyulai
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
 * OR OTHER DEALINGS IN THE SOFTWARE.
**********************************************************************************/

/**
 * @file    datetime.h
 * @author  Peter Gyulai
 * @version 1.1.0
 * @date    2020.04.16
 * @brief   Datetime utilities.
 * @details
 * This file contains datetime utilities used by the Rhea RTC module.
 */
    
// Standard includes
#include <stdint.h>

    
// Conversion constants
#define RHEA_RTC_SECONDS_PER_MINUTE 60
#define RHEA_RTC_SECONDS_PER_HOUR   3600
#define RHEA_RTC_SECONDS_PER_DAY    86400
#define RHEA_RTC_SECONDS_PER_MONTH  2629744
#define RHEA_RTC_SECONDS_PER_YEAR   31556926
    
typedef struct {
    uint16_t year;
    uint8_t  month;
    uint8_t  date;
    uint8_t  weekday;
    uint8_t  hour;
    uint8_t  minute;
    uint8_t  second;
} rhea_rtc_datetime;

enum rhea_rtc_weekday {
    Sunday      = 1,
    Monday      = 2,
    Tuesday     = 3,    
    Wednesday   = 4,
    Thursday    = 5,
    Friday      = 6,
    Saturday    = 7
};

/** @brief Typedef for omitting 'enum' keyword from the typename. */
typedef enum rhea_rtc_weekday rhea_rtc_weekday;
    
/** @brief Datetime format string for standard format 'General'. */
static const char rhea_rtc_datetimeFormatGeneral[] = "YYYY/MM/dd hh:mm:ss"; 
/** @brief Datetime format string for standard format 'General US'. */
static const char rhea_rtc_datetimeFormatGeneralUS[] = "dd/MM/YYYY hh:mm:ss t";
/** @brief Datetime format string for standard format 'Full'. */
static const char rhea_rtc_datetimeFormatFull[] = "w, MMMM d, YYYY h:m:s";

/**
 * @brief Prints the formatted datetime to the specified buffer.
 * @param datetime The datetime to print.
 * @param format Datetime format string.
 * @param buffer Buffer to store the result (must be long enough).
 * @details The format may contain the following symbols:
 * - [Y,YY,YYY,YYYY]: Year digits (printing start from the last digit of the year)
 * - [M,MM,MMM,MMMM]: [month digits, month digits (with leading zeros), abbreviated month name, month name] 
 * - [w,W]: [abbreviated weekday name, weekday name]
 * - [h,hh]: [hour digits, hour digits (with leading zeros)]
 * - [t]: AM/PM designator (hours are modified accordingly)
 * - [m,mm]: [minute digits, minute digits (with leading zeros)]
 * - [s,ss]: [second digits, second digits (with leading zeros)]
 * - Arbitrary characters, that are included in the result unchanged.
 */
void rhea_rtc_formatDate(rhea_rtc_datetime datetime, const char *format, char *buffer);

/**
 * @brief Converts a datetime object to the equivalent number of seconds since epoch 1970.01.01.
 * @param datetime The datetime structure to convert.
 * @return The equivalent number of seconds.
 */
int64_t rhea_rtc_toSeconds(const rhea_rtc_datetime datetime);

/**
 * @brief Creates a datetime object from the equivalent number of seconds since epoch 1970.01.01.
 * @param seconds The amount of seconds to convert.
 * @return The equivalent datetime structure.
 */
rhea_rtc_datetime rhea_rtc_fromSeconds(int64_t seconds);

/**
 * @brief Creates a datetime object from it's string representation.
 * @param str The string representation of the datetime.
 *            The datetime format is [YYYY.MM.dd hh:mm:ss], 
 *            or alternatively [YYYY/MM/DD hh:mm:ss]. The day
              of the week is automatically generated.
 */
rhea_rtc_datetime rhea_rtc_fromString(const char *str);

/**
 * @brief Calculates and sets the weekday field of the specified datetime.
 * @param d Pointer to a datetime structure already containing date information.
 */
void rhea_rtc_setWeekday(rhea_rtc_datetime *d);

/**
 * @brief Compares two datetimes.
 * @param lhs The first datetime.
 * @param rhs The second datetime.
 * @returns Positive when 'rhs' is later than 'lhs', zero when equal 
 *          and negative if 'rhs' is sooner than 'lhs'.
 */
int64_t rhea_rtc_compareDatetime(const rhea_rtc_datetime lhs, const rhea_rtc_datetime rhs);

/**
 * @brief Adds the specified amount of time to a datetime.
 * @param lhs The initial datetime.
 * @param rhs The time interval to add.
 * @returns The datetime of 'lhs' incremented by 'rhs'.
 */
rhea_rtc_datetime rhea_rtc_addDatetime(const rhea_rtc_datetime lhs, const rhea_rtc_datetime rhs); 
    
#endif // DATETIME_H_INCLUDED

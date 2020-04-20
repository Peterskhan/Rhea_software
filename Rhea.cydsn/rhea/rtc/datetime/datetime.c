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
 * @file    datetime.c
 * @author  Peter Gyulai
 * @version 0.0.1
 * @date    2020.03.23
 * @brief   Library implementation.
 * @details
 * This file contains the datetime utility implementation.
 */

// Doxygen documentation duplication suppression
#ifndef DOXYGEN_SHOULD_SKIP_THIS

// Standard includes
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
    
// Project includes
#include "datetime.h"
    
    
static const char * const rhea_rtc_weekdayNamesLong[] = {
    "NONE", "Sunday", "Monday", "Tuesday", "Wednesday",
    "Thursday", "Friday", "Saturday"
};

static const char * const rhea_rtc_weekdayNamesShort[] = {
    "NONE", "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
};

static const char * const rhea_rtc_monthNamesLong[] = {
    "NONE", "January", "February", "March", "April", "May", "June", 
    "July", "August", "September", "October", "November", "December"
};

static const char * const rhea_rtc_monthNamesShort[] = {
    "NONE", "Jan", "Feb", "Mar", "Apr", "May", "Jun"
    "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

void rhea_rtc_formatDate(rhea_rtc_datetime datetime, const char *format, char *buffer) {

    // Logic value indicating whether AM/PM format is used or not
    uint8_t ampm_format = 0;
    
    // Index for iterating format string
    uint8_t i = 0;
    
    // Determining whether AM/PM format is used
    while(format[i] != '\0') if(format[i++] == 't') ampm_format = 1;
    
    // Resetting index
    i = 0;
    
    // Parsing format and writing buffer
    while(format[i] != '\0') {
        
        // Handling years
        if(format[i] == 'Y') {
            uint8_t yearDigits = 1;
            while(format[++i] == 'Y') yearDigits++;
            if(yearDigits == 1) datetime.year %= 10;
            if(yearDigits == 2) datetime.year %= 100;
            if(yearDigits == 3) datetime.year %= 1000;
            sprintf(buffer, "%.*u", yearDigits, datetime.year);
            buffer = buffer + yearDigits;
        }
        
        // Handling months
        else if(format[i] == 'M') {
            uint8_t monthDigits = 1;
            while(format[++i] == 'M') monthDigits++;
            if(monthDigits == 3) {
                sprintf(buffer, "%s", rhea_rtc_monthNamesShort[datetime.month]);
                buffer = buffer + strlen(rhea_rtc_monthNamesShort[datetime.month]);
            } 
            else if(monthDigits == 4) {
                sprintf(buffer, "%s", rhea_rtc_monthNamesLong[datetime.month]);
                buffer = buffer + strlen(rhea_rtc_monthNamesLong[datetime.month]);
            }
            else {
                sprintf(buffer, "%.*u", monthDigits, datetime.month);
                buffer = buffer + (datetime.month < 9 ? monthDigits : 2);
            }
        }
        
        // Handling dates
        else if(format[i] == 'd') {
            uint8_t dateDigits = 1;
            while(format[++i] == 'd') dateDigits++;
            sprintf(buffer, "%.*u", dateDigits, datetime.date);
            buffer = buffer + (datetime.date < 9 ? dateDigits : 2);
        }
        
        // Handling short weekdays
        else if(format[i] == 'w') {
            sprintf(buffer, "%s", rhea_rtc_weekdayNamesShort[datetime.weekday]);
            buffer = buffer + strlen(rhea_rtc_weekdayNamesShort[datetime.weekday]);
            i++;
        }
        
        // Handling long weekdays
        else if(format[i] == 'W') {
            sprintf(buffer, "%s", rhea_rtc_weekdayNamesLong[datetime.weekday]);
            buffer = buffer + strlen(rhea_rtc_weekdayNamesLong[datetime.weekday]);
            i++;
        }
        
        // Handling hours
        else if(format[i] == 'h') {
            uint8_t hourDigits = 1;
            while(format[++i] == 'h') hourDigits++;
            sprintf(buffer, "%.*u", hourDigits, (ampm_format && datetime.hour > 12 ? datetime.hour - 12 : datetime.hour));
            buffer = buffer + (datetime.hour < 9 || (datetime.hour > 12 && ampm_format) ? hourDigits : 2);
        }
        
        // Handling AM/PM designator
        else if(format[i] == 't') {
            sprintf(buffer, "%s", datetime.hour <= 12 ? "AM" : "PM");
            buffer = buffer + 2;
            i++;
        }
        
        // Handling minutes
        else if(format[i] == 'm') {
            uint8_t minuteDigits = 1;
            while(format[++i] == 'm') minuteDigits++;
            sprintf(buffer, "%.*u", minuteDigits, datetime.minute);
            buffer = buffer + (datetime.minute < 9 ? minuteDigits : 2);
        }
        
        // Handling seconds
        else if(format[i] == 's') {
            uint8_t secondDigits = 1;
            while(format[++i] == 's') secondDigits++;
            sprintf(buffer, "%.*u", secondDigits, datetime.second);
            buffer = buffer + (datetime.second < 9 ? secondDigits : 2);
        }
        
        // Handling other characters
        else {
            buffer[0] = format[i++];
            buffer++;
        }
    }
}

int64_t rhea_rtc_toSeconds(const rhea_rtc_datetime datetime) {
    int64_t y = datetime.year;
    uint8_t m = datetime.month;
    uint8_t d = datetime.date;
    
    // Algorithm source: https://howardhinnant.github.io/date_algorithms.html#days_from_civil
    // This algorithm calculates the number of days since epoch 1970.01.01.
    // Correction for hours, minutes and seconds are included.
    
    y -= m <= 2;
    const int era = (y >= 0 ? y : y-399) / 400;
    const unsigned yoe = (y - era * 400);      // [0, 399]
    const unsigned doy = (153*(m + (m > 2 ? -3 : 9)) + 2)/5 + d-1;  // [0, 365]
    const unsigned doe = yoe * 365 + yoe/4 - yoe/100 + doy;         // [0, 146096]
    const int64_t days_from_civil = era * 146097 + doe - 719468;
    
    return days_from_civil * RHEA_RTC_SECONDS_PER_DAY + 
           datetime.hour   * RHEA_RTC_SECONDS_PER_HOUR + 
           datetime.minute * RHEA_RTC_SECONDS_PER_MINUTE +
           datetime.second;
}

rhea_rtc_datetime rhea_rtc_fromSeconds(int64_t seconds) {
    
    // Datetime object to populate
    rhea_rtc_datetime datetime;
    
    // Calculating datetime parameters
    // Algorithm source: https://howardhinnant.github.io/date_algorithms.html#civil_from_days
    // This algorithm calculates the date from the number of days since epoch 1970.01.01.
    // Correction for hours, minutes and seconds are included.
    int64_t z = floor((double)seconds / RHEA_RTC_SECONDS_PER_DAY);
    seconds = abs(seconds - (z * RHEA_RTC_SECONDS_PER_DAY));
    datetime.hour = seconds / RHEA_RTC_SECONDS_PER_HOUR; seconds = seconds % RHEA_RTC_SECONDS_PER_HOUR;
    datetime.minute = seconds / RHEA_RTC_SECONDS_PER_MINUTE; seconds = seconds % RHEA_RTC_SECONDS_PER_MINUTE;
    datetime.second = seconds;
     
    z += 719468;
    const int era = (z >= 0 ? z : z - 146096) / 146097;
    const unsigned doe = z - era * 146097;         // [0, 146096]
    const unsigned yoe = (doe - doe/1460 + doe/36524 - doe/146096) / 365;  // [0, 399]
    const int y = yoe + era * 400;
    const unsigned doy = doe - (365*yoe + yoe/4 - yoe/100);                // [0, 365]
    const unsigned mp = (5*doy + 2)/153;                                   // [0, 11]
    const unsigned d = doy - (153*mp+2)/5 + 1;                             // [1, 31]
    const unsigned m = mp + (mp < 10 ? 3 : -9);                            // [1, 12]
    datetime.year = y + (m <= 2);
    datetime.month = m;
    datetime.date = d;
    
    // Setting weekday field
    rhea_rtc_setWeekday(&datetime);
    
    // Returning datetime
    return datetime;
}

rhea_rtc_datetime rhea_rtc_fromString(const char *str) {
    
    // Creating datetime to store the results
    rhea_rtc_datetime d;
    
    // Parsing string input
    if (sscanf(str,"%u.%u.%u %u:%u:%u", // YYYY.MM.DD hh:mm:ss
        (unsigned*)&(d.year), (unsigned*)&(d.month),  (unsigned*)&(d.date), 
        (unsigned*)&(d.hour), (unsigned*)&(d.minute), (unsigned*)&(d.second)) == 6 ||
        sscanf(str,"%u/%u/%u %u:%u:%u", // YYYY/MM/DD hh:mm:ss
        (unsigned*)&(d.year), (unsigned*)&(d.month),  (unsigned*)&(d.date), 
        (unsigned*)&(d.hour), (unsigned*)&(d.minute), (unsigned*)&(d.second)) == 6) 
    {
        // Calculating weekday
        rhea_rtc_setWeekday(&d);
    }
    
    return d;
}

void rhea_rtc_setWeekday(rhea_rtc_datetime *d) {

    // This weekday calculation algorithm is only correct between [1900; 2099],

    // Monthcode corrections: First entry is invalid (January corresponds to monthCodes[1])
    int8_t monthCodes[] = {-1, 0, 3, 3, 6, 1, 4, 6, 2, 5, 0, 3, 5};

    // Calculating correction codes
    uint8_t yearCode = ((d->year % 100) + ((d->year % 100) / 4)) % 7;
    uint8_t monthCode = monthCodes[d->month];
    uint8_t centuryCode = d->year < 2000 ? 0 : 6;
    uint8_t leapyearCode = ((d->year) / 4 == 0 && (d->month == 1 || d->month == 2)) ? 1 : 0;

    // Setting weekday (Correction result in Sunday being 0, one is added for MCP7940N's driver convention)
    d->weekday = ((yearCode + monthCode + centuryCode + d->date - leapyearCode) % 7) + 1;
}

int64_t rhea_rtc_compareDatetime(const rhea_rtc_datetime lhs, const rhea_rtc_datetime rhs) {
    return rhea_rtc_toSeconds(rhs) - rhea_rtc_toSeconds(lhs);
}

rhea_rtc_datetime rhea_rtc_addDatetime(const rhea_rtc_datetime lhs, const rhea_rtc_datetime rhs) {
    uint64_t lhsSeconds = rhea_rtc_toSeconds(lhs);
    uint64_t rhsSeconds = rhea_rtc_toSeconds(rhs);
    return rhea_rtc_fromSeconds(lhsSeconds + rhsSeconds);
}

#endif // DOXYGEN_SHOULD_SKIP_THIS

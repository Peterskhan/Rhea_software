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
 * @file    alarm.c
 * @author  Peter Gyulai
 * @version 1.0.0
 * @date    2020.04.16
 * @brief   Library implementation.
 * @details
 * This file contains the alarm utility implementation.
 */

// Doxygen documentation duplication suppression
#ifndef DOXYGEN_SHOULD_SKIP_THIS

// Standard includes
#include <string.h>

// Project includes
#include "alarm.h"
    

void rhea_rtc_formatAlarm(const rhea_rtc_alarm alarm, char *buffer) {

    // Printing formatted datetime of the alarm
    rhea_rtc_formatDate(alarm.datetime, rhea_rtc_datetimeFormatGeneral, buffer);

    // Printing alarm mode
    switch(alarm.mode) {
    case EveryMinute:   strcat(buffer, " [EveryMinute]"); break;
    case EveryHour:     strcat(buffer, " [EveryHour]  "); break;
    case EveryDay:      strcat(buffer, " [EveryDay]   "); break;
    case EveryWeek:     strcat(buffer, " [EveryWeek]  "); break;
    case EveryMonth:    strcat(buffer, " [EveryMonth] "); break;
    case EveryYear:     strcat(buffer, " [EveryYear]  "); break;
    case FutureDate:    strcat(buffer, " [FutureDate] "); break;
    };

    // Printing recurring status
    strcat(buffer, (alarm.recurring ? " [recurring]" : " [one-shot]"));
}

// Algorithm source: https://howardhinnant.github.io/date_algorithms.html#weekday_difference
unsigned rhea_rtc_weekdayDifference(unsigned x, unsigned y) {
    x -= y;
    return x <= 6 ? x : x + 7;
}

void rhea_rtc_normalizeAlarm(rhea_rtc_alarm *alarm, const rhea_rtc_datetime after) {
    
    // FutureDate alarms are not normalizable
    if(alarm->mode == FutureDate) {
        alarm->active = 0;
        return;
    }
    
    int64_t afterSeconds = rhea_rtc_toSeconds(after);
    rhea_rtc_alarm newAlarm = {after, alarm->recurring, alarm->active, alarm->mode};
    
    if(alarm->mode >= EveryMinute) newAlarm.datetime.second  = alarm->datetime.second;
    if(alarm->mode >= EveryHour)   newAlarm.datetime.minute  = alarm->datetime.minute;
    if(alarm->mode >= EveryDay)    newAlarm.datetime.hour    = alarm->datetime.hour;
    if(alarm->mode >= EveryMonth)  newAlarm.datetime.date    = alarm->datetime.date;
    if(alarm->mode >= EveryYear)   newAlarm.datetime.month   = alarm->datetime.month;
    if(alarm->mode == EveryWeek) {
        
        // Adding number of days so the day of week matches
        uint8_t inc_days = rhea_rtc_weekdayDifference(alarm->datetime.weekday, newAlarm.datetime.weekday);
        int64_t new_secs = rhea_rtc_toSeconds(newAlarm.datetime) + inc_days * RHEA_RTC_SECONDS_PER_DAY;
        newAlarm.datetime = rhea_rtc_fromSeconds(new_secs);
    }

    // Calculating new alarm timestamp
    int64_t newAlarmTimestamp = rhea_rtc_toSeconds(newAlarm.datetime);
    
    // Checking if the alarm is already normalized
    if(newAlarmTimestamp > afterSeconds) {
        
        // Recalculating day of week
        rhea_rtc_setWeekday(&newAlarm.datetime);
        
        // Applying changes
        *alarm = newAlarm;   
        return;
    }
        
    // Incrementing alarm datetime by one unit based on mode
    switch(alarm->mode) {
    case EveryMinute:   newAlarm.datetime = rhea_rtc_fromSeconds(newAlarmTimestamp + RHEA_RTC_SECONDS_PER_MINUTE);
                        break;
    case EveryHour:     newAlarm.datetime = rhea_rtc_fromSeconds(newAlarmTimestamp + RHEA_RTC_SECONDS_PER_HOUR);
                        break;
    case EveryDay:      newAlarm.datetime = rhea_rtc_fromSeconds(newAlarmTimestamp + RHEA_RTC_SECONDS_PER_DAY);
                        break;
    case EveryWeek:     newAlarm.datetime = rhea_rtc_fromSeconds(newAlarmTimestamp + RHEA_RTC_SECONDS_PER_DAY * 7);    
                        break;
    case EveryMonth:    if(newAlarm.datetime.month == 12) { newAlarm.datetime.month = 1; newAlarm.datetime.year++; }
                        else newAlarm.datetime.month++;
                        break;
    case EveryYear:     newAlarm.datetime.year++;
    };
    
    // Recalculating day of week
    rhea_rtc_setWeekday(&newAlarm.datetime);
    
    // Applying changes
    *alarm = newAlarm;
}

#endif // DOXYGEN_SHOULD_SKIP_THIS

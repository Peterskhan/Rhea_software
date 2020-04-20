#pragma once
#ifndef RHEA_RTC_ALARM_H_INCLUDED
#define RHEA_RTC_ALARM_H_INCLUDED

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
 * @file    alarm.h
 * @author  Peter Gyulai
 * @version 1.0.0
 * @date    2020.04.16
 * @brief   Alarm utilities.
 * @details
 * This file contains alarm utilities used by the Rhea RTC module.
 */

// Standard includes
#include <stdint.h>
    
// Project includes
#include "../datetime/datetime.h"
    
/** 
 * @brief Describes the possible alarm modes. 
 * @details
 * The alarm mode describes which datetime parameters are needed to match
 * the current datetime in order to trigger an alarm. Note, that the Every[X]
 * modes do NOT imply, that the alarm is restarted after being triggered.
 * An alarm is only restarted when the 'recurring' field is also set to 
 * logical true.
 */
enum rhea_rtc_alarmMode {
    EveryMinute,    /**< The alarm triggers every minute, when seconds match.                                   */
    EveryHour,      /**< The alarm triggers every hour, when minutes and seconds match.                         */
    EveryDay,       /**< The alarm triggers every day, when hours, minutes and seconds match.                   */
    EveryWeek,      /**< The alarm triggers every week, when day of week, hours, minutes and seconds match.     */
    EveryMonth,     /**< The alarm triggers every month, when date, hours, minutes and seconds match.           */
    EveryYear,      /**< The alarm triggers every year, when month, date, hours, minutes and seconds match.     */
    FutureDate      /**< The alarm triggers at a future date when all parameters (day of week excluded) match.  */
};
    
/**
 * @brief This structure describes an alarm entry.
 * @details
 * The 'datetime' field contains the necessary date and time information for the alarm.
 * Not all fields have to be filled, only those corresponding with the specified mode.
 * The 'recurring' field describes whether the alarm can be deactivated after being reset,
 * or it has to be restarted. The 'active' field is an indication whether the alarm
 * entry is active or not. The 'mode' field is a generic byte, but must be set to one
 * of the #rhea_rtc_alarmMode values (portable C does not support enum size specification).
 */
struct rhea_rtc_alarm {
    rhea_rtc_datetime   datetime;   /**< Date and time information of the alarm.                        */
    uint8_t             recurring;  /**< Describes whether the alarm is restarted after being reset.    */
    uint8_t             active;     /**< Describes whether the alarm entry is active or replacable.     */
    uint8_t             mode;       /**< Describes the mode of the alarm.                               */
};

/** @brief Typedef for omitting 'struct' keyword from the typename. */
typedef struct rhea_rtc_alarm rhea_rtc_alarm;

/**
 * @brief Prints a regular alarm structure to the specified buffer.
 * @param alarm The alarm to print into the buffer.
 * @param buffer The C-string buffer to store the results (must be large enough).
 */
void rhea_rtc_formatAlarm(const rhea_rtc_alarm alarm, char *buffer);

/**
 * @brief Normalizes an alarm by setting it's datetime to the 
 *        first valid value greater than 'after', based on mode.
 * @param alarm Pointer to the alarm to be normalized.
 * @param after Datetime to normalize the alarm after.
 */
void rhea_rtc_normalizeAlarm(rhea_rtc_alarm *alarm, const rhea_rtc_datetime after);

#endif // RHEA_RTC_ALARM_H_INCLUDED
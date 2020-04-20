#pragma once
#ifndef RHEA_RTC_H_INCLUDED
#define RHEA_RTC_H_INCLUDED

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
 * @file    rtc.h
 * @author  Peter Gyulai
 * @version 1.0.0
 * @date    2020.04.19
 * @brief   Realtime clock utilities.
 * @details
 * This file contains the realtime clock utility functions that utilize the Rhea RTC.
 */

// Standard includes
#include <stdint.h>

// Project includes
#include "datetime/datetime.h"
#include "alarm/alarm.h"
#include "rtc_config.h"

    
/** @brief Initializes the RTC module */
void rhea_rtc_Initialize();

/** @{ @name Datetime functions */
/** @brief Returns the current date and time. */
rhea_rtc_datetime rhea_rtc_Now(void);

/**
 * @brief Sets the current date and time.
 * @param now The new date and time.
 */
void rhea_rtc_SetDatetime(const rhea_rtc_datetime now);

/** @brief Returns the date and time of the last power-up. */
rhea_rtc_datetime rhea_rtc_PowerUp(void);

/** @brief Returns the date and time of the last power-fail. */
rhea_rtc_datetime rhea_rtc_PowerFail(void);
/** @} */

/** @{ @name Alarm functions */

/** @brief Typedef for a callback function to invoke when an alarm triggers. */
typedef void (*rhea_rtc_alarmCallback)(void);

/**
 * @brief Reschedules the next alarm to the hardware.
 * @details 
 * Selects the alarm from the active alarms that should trigger the soonest,
 * and sets the MCP7940N's hardware ALARM1 to this alarm. 
 */
void rhea_rtc_ScheduleAlarms(void);

/**
 * @brief Constructs and adds a new alarm to the alarm registry.
 * @param datetime A datetime structure filled with the necessary alarm parameters (based on mode).
 * @param recurring Non-zero if the alarm is recurring, zero otherwise.
 * @param mode The alarm mode (one of the #rhea_rtc_alarmMode values).
 * @param persistent Non-zero if the alarm should be persistent (with SRAM back-up), zero otherwise.
 * @param callback A #rhea_rtc_alarmCallback pointer, or NULL if not used.
 * @returns The ID of the created alarm, or -1 if the alarm could not be created.
 */
int16_t rhea_rtc_AddAlarm(rhea_rtc_datetime datetime, uint8_t recurring, uint8_t mode, uint8_t persistent,
                          rhea_rtc_alarmCallback callback);

/**
 * @brief Deletes an alarm from the alarm registry.
 * @param The ID of the alarm to be deleted.
 */
void rhea_rtc_DeleteAlarm(uint16_t id);

/**
 * @brief Handles all alarms by invoking callbacks and deleting 
 *        non-recurring alarms.
 */
void rhea_rtc_HandleAlarms(void);

#endif // RHEA_RTC_H_INCLUDED

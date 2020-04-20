#pragma once
#ifndef RHEA_RTC_IMPL_H_INCLUDED
#define RHEA_RTC_IMPL_H_INCLUDED

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
 * @file    rtc_impl.h
 * @author  Peter Gyulai
 * @version 1.0.0
 * @date    2020.04.19
 * @brief   Realtime clock implementation header.
 * @details
 * This file contains the realtime clock utility functions that need to be 
 * implemented when interfacing with a new RTC driver.
 */
    
// Project includes
#include "alarm/alarm.h"
    

// Extern variables and functions needed for implementation
extern rhea_rtc_datetime rhea_rtc_powerFailTimestamp;
extern rhea_rtc_datetime rhea_rtc_powerUpTimestamp;
extern rhea_rtc_alarm rhea_rtc_alarmRegistry[];
extern void rhea_rtc_alarmISR(void);

/**
 * @brief Initializes the RTC driver.
 * @todo  Implement this function to initialize the RTC driver.
 * @todo  Populate the rhea_rtc_powerFailTimestamp.
 * @todo  Populate the rhea_rtc_powerUpTimestamp.
 * @todo  Disable alarm interrupt sources.
 * @todo  Set up and enable the rhea_rtc_alarmISR interrupt handler.
 */
void rhea_rtc_initialize_impl(void);

/**
 * @brief   Returns the current date and time.
 * @returns The current date and time as a rhea_rtc_datetime.
 * @todo	Implement this function to query the current date and time.
 */
rhea_rtc_datetime rhea_rtc_now_impl(void);

/**
 * @brief Sets the current date and time.
 * @todo  Implement htis function to set the current date and time.
 * @param [in] newDatetime A rhea_rtc_datetime containing the new date and time.
 */
void rhea_rtc_setDatetime_impl(rhea_rtc_datetime newDatetime);

/**
 * @brief Enables the hardware alarm interrupt source.
 * @todo  Implement this function to enable alarm interrupts.
 */
void rhea_rtc_enableAlarms_impl(void);

/**
 * @brief Disables the hardware alarm interrupt source.
 * @todo  Implement this function to disable alarm interrupts.
 */
void rhea_rtc_disableAlarms_impl(void);

/**
 * @brief Sets the date and time of the hardware alarm interrupt.
 * @todo  Implement this function the set the datetime of the hardware alarm.
 * @param [in] alarmDatetime A rhea_rtc_datetime containg the date and time of the alarm.
 */
void rhea_rtc_setAlarmDatetime_impl(rhea_rtc_datetime alarmDatetime);

/**
 * @brief Loads alarms from persisent storage to the alarm registry.
 * @todo  Load a maximum of RHEA_RTC_HARDWARE_ALARM_COUNT alarms into 
 *        the front side of the rhea_rtc_alarmRegistry array.
 */
void rhea_rtc_loadAlarms_impl(void);

/**
 * @brief Stores alarms to persistent storage from the alarm registry.
 * @todo  Stores a maximum of RHEA_RTC_HARDWARE_ALARM_COUNT alarms from
 *        the front side of the rhea_rtc_alarmRegistry array.
 */
void rhea_rtc_storeAlarms_impl(void);

#endif // RHEA_RTC_IMPL_H_INCLUDED
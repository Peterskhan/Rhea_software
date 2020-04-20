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
 * @file    Rhea_RTC.c
 * @author  Peter Gyulai
 * @version 1.0.0
 * @date    2020.04.19
 * @brief   Library implementation.
 * @details
 * This file contains the function definitions used by the Rhea RTC library.
 */

 // Doxygen documentation duplication suppression
#ifndef DOXYGEN_SHOULD_SKIP_THIS
    
// Standard includes
#include <stdlib.h>

// Project includes
#include "rtc.h"
#include "rtc_impl.h"
    

// Static datetime storing the last power-fail
rhea_rtc_datetime rhea_rtc_powerFailTimestamp;

// Static datetime storing the last power-up
rhea_rtc_datetime rhea_rtc_powerUpTimestamp;

// Total size of the alarm registry
#define RHEA_RTC_ALARM_REGISTRY_SIZE (RHEA_RTC_HARDWARE_ALARM_COUNT + RHEA_RTC_SOFTWARE_ALARM_COUNT)

// Static array to store alarm callbacks
static rhea_rtc_alarmCallback rhea_rtc_alarmCallbacks[RHEA_RTC_ALARM_REGISTRY_SIZE];

// Static array to store alarms
rhea_rtc_alarm rhea_rtc_alarmRegistry[RHEA_RTC_ALARM_REGISTRY_SIZE];

// Static volatile flag indicating an alarm interrupt has occured
static volatile uint8_t rhea_rtc_alarmOccured = 0;

void rhea_rtc_Initialize(void) {

    // Invoking driver implementation
    rhea_rtc_initialize_impl();

    // Loading alarms from persistent storage
    rhea_rtc_loadAlarms_impl();
}

rhea_rtc_datetime rhea_rtc_Now(void) {

    // Returning current datetime
    return rhea_rtc_now_impl();
}

void rhea_rtc_SetDatetime(const rhea_rtc_datetime now) {

    // Setting current datetime
    rhea_rtc_setDatetime_impl(now);
}

rhea_rtc_datetime rhea_rtc_PowerUp(void) {

    // Returning timestamp
    return rhea_rtc_powerUpTimestamp;
}

rhea_rtc_datetime rhea_rtc_PowerFail(void) {
    
    // Returning datetime
    return rhea_rtc_powerFailTimestamp;
}

void rhea_rtc_ScheduleAlarms(void) {
    
    // Disabling alarm interrupts
    rhea_rtc_disableAlarms_impl();
    
    // Initial parameters
    rhea_rtc_alarm closestAlarm = rhea_rtc_alarmRegistry[0];
    uint8_t        foundActive = 0;
    
    // Performing minimum search to find the alarm to trigger the soonest
    for(uint16_t i = 1; i < RHEA_RTC_ALARM_REGISTRY_SIZE; i++) {
        if(rhea_rtc_alarmRegistry[i].active && 
           rhea_rtc_toSeconds(rhea_rtc_alarmRegistry[i].datetime) < rhea_rtc_toSeconds(closestAlarm.datetime))
        {
            closestAlarm = rhea_rtc_alarmRegistry[i];
            foundActive = 1;
        }
    }
        
    // Checking whether an active alarm is found
    if(!foundActive) return;

    // Installing alarm to hardware
    rhea_rtc_setAlarmDatetime_impl(closestAlarm.datetime);
    rhea_rtc_enableAlarms_impl();
}

int16_t rhea_rtc_AddAlarm(rhea_rtc_datetime datetime, uint8_t recurring, uint8_t mode, uint8_t persistent,
                          rhea_rtc_alarmCallback callback) 
{
    // Constructing alarm object
    rhea_rtc_alarm alarm = {datetime, recurring, 1, mode};
    
    // Determining start index based on persistency
    uint16_t start = persistent ? 0 : RHEA_RTC_HARDWARE_ALARM_COUNT;
    uint16_t end = persistent ? RHEA_RTC_HARDWARE_ALARM_COUNT : RHEA_RTC_ALARM_REGISTRY_SIZE;
    
    // Finding empty alarm slot in the registry
    for(uint16_t i = start; i < end; i++) {
        if(!rhea_rtc_alarmRegistry[i].active) {
            
            // Registering alarm
            rhea_rtc_alarmRegistry[i] = alarm;
            rhea_rtc_alarmCallbacks[i] = callback;
            
            // Saving persistent alarm to external SRAM
            if(persistent) rhea_rtc_storeAlarms_impl();
            
            // Rescheduling alarms to hardware
            rhea_rtc_ScheduleAlarms();
            
            return i;
        }
    }
    
    return -1;
}

void rhea_rtc_DeleteAlarm(uint16_t id) {
    
    // Checking alarm ID
    if(id >= RHEA_RTC_ALARM_REGISTRY_SIZE) return;
    
    // Deactivating alarm in the registry
    rhea_rtc_alarmRegistry[id].active = 0;
    rhea_rtc_alarmCallbacks[id] = NULL;
    
    // Deactivating persistent alarm in the RTC SRAM
    if(id < RHEA_RTC_HARDWARE_ALARM_COUNT) rhea_rtc_storeAlarms_impl();
    
    // Rescheduling alarms to hardware
    rhea_rtc_ScheduleAlarms();
}

void rhea_rtc_HandleAlarms(void) {
    
    // Checking interrupt indicator
    if(!rhea_rtc_alarmOccured) return;
    
    // Clearing interrupt indicator
    rhea_rtc_alarmOccured = 0;
    
    // Current timestamp
    int64_t nowSeconds = rhea_rtc_toSeconds(rhea_rtc_Now());
    
    // Checking active alarms 
    for(uint16_t i = 0; i < RHEA_RTC_ALARM_REGISTRY_SIZE; i++) {
        
        // Determining if the alarm is active and should have triggered by now
        if(rhea_rtc_alarmRegistry[i].active && 
           rhea_rtc_toSeconds(rhea_rtc_alarmRegistry[i].datetime) < nowSeconds) 
        {    
            // Activating callback
            if(rhea_rtc_alarmCallbacks[i]) {
                rhea_rtc_alarmCallbacks[i]();
            }
            
            // Deleting alarm if it's one-shot 
            if(!rhea_rtc_alarmRegistry[i].recurring) {
                rhea_rtc_DeleteAlarm(i);
            }
            // Restarting alarm if it's recurring
            else {
                rhea_rtc_normalizeAlarm(&rhea_rtc_alarmRegistry[i], rhea_rtc_Now());    
            }
        }
    }
    
    // Rescheduling alarms to hardware
    rhea_rtc_ScheduleAlarms();
}

void rhea_rtc_alarmISR(void) {
    rhea_rtc_alarmOccured = 1;   
}

#endif // DOXYGEN_SHOULD_SKIP_THIS
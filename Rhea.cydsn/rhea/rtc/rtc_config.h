#pragma once
#ifndef RHEA_RTC_CONFIG_H_INCLUDED
#define RHEA_RTC_CONFIG_H_INCLUDED

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
 * @file    rtc_config.h
 * @author  Peter Gyulai
 * @version 1.0.0
 * @date    2020.04.19
 * @brief   RTC configuration.
 * @details
 * This file contains the RTC configuration macros for the Rhea RTC library.
 */

// Defining RTC target driver
#define RHEA_RTC_TARGET_MCP7940N

// Defining RTC module string buffer size
#define RHEA_RTC_STRINGBUFFER_SIZE      (256)

// Defining the number of software stored alarms
#define RHEA_RTC_SOFTWARE_ALARM_COUNT   (24)

// Defining the number of hardware stored alarms
#define RHEA_RTC_HARDWARE_ALARM_COUNT   (8)


#endif // RHEA_RTC_CONFIG_H_INCLUDED
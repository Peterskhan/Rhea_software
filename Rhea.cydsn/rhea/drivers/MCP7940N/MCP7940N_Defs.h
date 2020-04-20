#pragma once
#ifndef MCP7940N_DEFS_H_INCLUDED
#define MCP7940N_DEFS_H_INCLUDED

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
 * @file    MCP7940N_Defs.h
 * @author  Peter Gyulai
 * @version 1.0.0
 * @date    2020.02.26
 * @brief   Macro definitions.
 * @details
 * This header file contains all the macro definitions used by the MCP7940N driver library.
 * These macros are used throughout the implementation and accessible by the end user. The
 * general convention is that all macros are preceeded by the MCP7940N_ prefix.
 */

/** @{ @name I2C Parameters */
/** @brief Defines the I2C address of the MCP7940N. */
#define MCP7940N_I2C_ADDR                    (uint8_t)(0xDE)
/** @brief Defines the starting address of registers. */
#define MCP7940N_REGISTERS_START             (uint8_t)(0x00)
/** @brief Defines the number of registers. */
#define MCP7940N_REGISTER_COUNT              (uint8_t)(0x20)
/** @} */

/** @{ @name Timekeeping Register Addresses */
/** @brief Defines the offset of the RTCSEC register. */
#define MCP7940N_RTCSEC                      (uint8_t)(0x00)
/** @brief Defines the offset of the RTCMIN register. */
#define MCP7940N_RTCMIN                      (uint8_t)(0x01)
/** @brief Defines the offset of the RTCHOUR register. */
#define MCP7940N_RTCHOUR                     (uint8_t)(0x02)
/** @brief Defines the offset of the RTCWKDAY register. */
#define MCP7940N_RTCWKDAY                    (uint8_t)(0x03)
/** @brief Defines the offset of the RTCDATE register. */
#define MCP7940N_RTCDATE                     (uint8_t)(0x04)
/** @brief Defines the offset of the RTCMTH register. */
#define MCP7940N_RTCMTH                      (uint8_t)(0x05)
/** @brief Defines the offset of the RTCYEAR register. */
#define MCP7940N_RTCYEAR                     (uint8_t)(0x06)
/** @brief Defines the offset of the CONTROL register. */
#define MCP7940N_CONTROL                     (uint8_t)(0x07)
/** @brief Defines the offset of the OSCTRIM register. */
#define MCP7940N_OSCTRIM                     (uint8_t)(0x08)
/** @} */

/** @{ @name Alarm 0. Register Addresses */
/** @brief Defines the offset of the ALM0SEC register. */
#define MCP7940N_ALM0SEC                     (uint8_t)(0x0A)
/** @brief Defines the offset of the ALM0MIN register. */
#define MCP7940N_ALM0MIN                     (uint8_t)(0x0B)
/** @brief Defines the offset of the ALM0HOUR register. */
#define MCP7940N_ALM0HOUR                    (uint8_t)(0x0C)
/** @brief Defines the offset of the ALM0WKDAY register. */
#define MCP7940N_ALM0WKDAY                   (uint8_t)(0x0D)
/** @brief Defines the offset of the ALM0DATE register. */
#define MCP7940N_ALM0DATE                    (uint8_t)(0x0E)
/** @brief Defines the offset of the ALM0MTH register. */
#define MCP7940N_ALM0MTH                     (uint8_t)(0x0F)
/** @} */

/** @{ @name Alarm 1. Register Addresses */
/** @brief Defines the offset of the ALM1SEC register. */
#define MCP7940N_ALM1SEC                     (uint8_t)(0x11)
/** @brief Defines the offset of the ALM1MIN register. */
#define MCP7940N_ALM1MIN                     (uint8_t)(0x12)
/** @brief Defines the offset of the ALM1HOUR register. */
#define MCP7940N_ALM1HOUR                    (uint8_t)(0x13)
/** @brief Defines the offset of the ALM1WKDAY register. */
#define MCP7940N_ALM1WKDAY                   (uint8_t)(0x14)
/** @brief Defines the offset of the ALM1DATE register. */
#define MCP7940N_ALM1DATE                    (uint8_t)(0x15)
/** @brief Defines the offset of the ALM1MTH register. */
#define MCP7940N_ALM1MTH                     (uint8_t)(0x16)
/** @} */

/** @{ @name Power-fail Timestamp Addresses */
/** @brief Defines the offset of the PWRDNMIN register. */
#define MCP7940N_PWRDNMIN                    (uint8_t)(0x18)
/** @brief Defines the offset of the PWRDNHOUR register. */
#define MCP7940N_PWRDNHOUR                   (uint8_t)(0x19)
/** @brief Defines the offset of the PWRDNDATE register. */
#define MCP7940N_PWRDNDATE                   (uint8_t)(0x1A)
/** @brief Defines the offset of the PWRDNMTH register. */
#define MCP7940N_PWRDNMTH                    (uint8_t)(0x1B)
/** @} */

/** @{ @name Power-up Timestamp Addresses */
/** @brief Defines the offset of the PWRUPMIN register. */
#define MCP7940N_PWRUPMIN                    (uint8_t)(0x1C)
/** @brief Defines the offset of the PWRUPHOUR register. */
#define MCP7940N_PWRUPHOUR                   (uint8_t)(0x1D)
/** @brief Defines the offset of the PWRUPDATE register. */
#define MCP7940N_PWRUPDATE                   (uint8_t)(0x1E)
/** @brief Defines the offset of the PWRUPMTH register. */
#define MCP7940N_PWRUPMTH                    (uint8_t)(0x1F)
/** @} */

/** @{ @name SRAM Parameters */
/** @brief Defines the on-chip SRAM starting address. */
#define MCP7940N_SRAM_ADDR                   (uint8_t)(0x20)
/** @brief Defines the lowest address of the on-chip SRAM. */
#define MCP7940N_SRAM_ADDRLOW                (uint8_t)(0x20)
/** @brief Defines the highest address of the on-chip SRAM. */
#define MCP7940N_SRAM_ADDRHIGH               (uint8_t)(0x5F)
/** @brief Defines the size of the on-chip SRAM in bytes. */
#define MCP7940N_SRAM_SIZE                   (uint8_t)(0x40)
/** @} */

/** @{ @name RTCSEC Register Masks */
/** @brief Defines a bitmask for RTCSEC_SECONE bits. */
#define MCP7940N_RTCSEC_SECONE               (uint8_t)(0x0F)
/** @brief Defines a bitmask for RTCSEC_SECTEN bits. */
#define MCP7940N_RTCSEC_SECTEN               (uint8_t)(0x70)
/** @brief Defines a bitmask for the RTCSEC_ST bit. */
#define MCP7940N_RTCSEC_ST                   (uint8_t)(0x80)
/** @} */

/** @{ @name RTCMIN Register Masks */
/** @brief Defines a bitmask for RTCMIN_MINONE bits. */
#define MCP7940N_RTCMIN_MINONE               (uint8_t)(0x0F)
/** @brief Defines a bitmask for RTCMIN_MINTEN bits. */
#define MCP7940N_RTCMIN_MINTEN               (uint8_t)(0x70)
/** @} */

/** @{ @name RTCHOUR Register Masks */
/** @brief Defines a bitmask for RTCHOUR_HRONE bits. */
#define MCP7940N_RTCHOUR_HRONE               (uint8_t)(0x0F)
/** @brief Defines a bitmask for RTCHOUR_HRTEN bits. */
#define MCP7940N_RTCHOUR_HRTEN               (uint8_t)(0x30)
/** @brief Defines a bitmask for the RTCHOUR_AMPM / highest RTCHOUR_HRTEN bit. */
#define MCP7940N_RTCHOUR_AMPM                (uint8_t)(0x20)
/** @brief Defines a bitmask for the RTCHOUR_1224 bit. */
#define MCP7940N_RTCHOUR_1224                (uint8_t)(0x40)
/** @} */

/** @{ @name RTCWKDAY Register Masks */
/** @brief Defines a bitmask for RTCWKDAY_WKDAY bits. */
#define MCP7940N_RTCWKDAY_WKDAY              (uint8_t)(0x07)
/** @brief Defines a bitmask for the RTCWKDAY_VBATEN bit. */
#define MCP7940N_RTCWKDAY_VBATEN             (uint8_t)(0x08)
/** @brief Defines a bitmask for the RTCWKDAY_PWRFAIL bit. */
#define MCP7940N_RTCWKDAY_PWRFAIL            (uint8_t)(0x10)
/** @brief Defines a bitmask for the RTCWKDAY_OSCRUN bit. */
#define MCP7940N_RTCWKDAY_OSCRUN             (uint8_t)(0x20)
/** @} */

/** @{ @name RTCDATE Register Masks */
/** @brief Defines a bitmask for RTCDATE_DATEONE bits. */
#define MCP7940N_RTCDATE_DATEONE             (uint8_t)(0x0F)
/** @brief Defines a bitmask for RTCDATE_DATETEN bits. */
#define MCP7940N_RTCDATE_DATETEN             (uint8_t)(0x30)
/** @} */

/** @{ @name RTCMTH Register Masks */
/** @brief Defines a bitmask for RTCMTH_MTHONE bits. */
#define MCP7940N_RTCMTH_MTHONE               (uint8_t)(0x0F)
/** @brief Defines a bitmask for RTCMTH_MTHTEN bits. */
#define MCP7940N_RTCMTH_MTHTEN               (uint8_t)(0x10)
/** @brief Defines a bitmask for the RTCMTH_LPYR bit. */
#define MCP7940N_RTCMTH_LPYR                 (uint8_t)(0x20)
/** @} */

/** @{ @name RTCYEAR Register Masks */
/** @brief Defines a bitmask for RTCYEAR_YRONE bits. */
#define MCP7940N_RTCYEAR_YRONE               (uint8_t)(0x0F)
/** @brief Defines a bitmask for RTCYEAR_YRTEN bits. */
#define MCP7940N_RTCYEAR_YRTEN               (uint8_t)(0xF0)
/** @} */

/** @{ @name CONTROL Register Masks */
/** @brief Defines a bitmask for CONTROL_SQWFS bits. */
#define MCP7940N_CONTROL_SQWFS               (uint8_t)(0x03)
/** @brief Defines a bitmask for the CONTROL_CRSTRIM bit. */
#define MCP7940N_CONTROL_CRSTRIM             (uint8_t)(0x04)
/** @brief Defines a bitmask for the CONTROL_EXTOSC bit. */
#define MCP7940N_CONTROL_EXTOSC              (uint8_t)(0x08)
/** @brief Defines a bitmask for the CONTROL_ALM0EN bit. */
#define MCP7940N_CONTROL_ALM0EN              (uint8_t)(0x10)
/** @brief Defines a bitmask for the CONTROL_ALM1EN bit. */
#define MCP7940N_CONTROL_ALM1EN              (uint8_t)(0x20)
/** @brief Defines a bitmask for the CONTROL_SQWEN bit. */
#define MCP7940N_CONTROL_SQWEN               (uint8_t)(0x40)
/** @brief Defines a bitmask for the CONTROL_OUT bit. */
#define MCP7940N_CONTROL_OUT                 (uint8_t)(0x80)
/** @} */

/** @{ @name OSCTRIM Register Masks */
/** @brief Defines a bitmask for OSCTRIM_TRIMVAL bits. */
#define MCP7940N_OSCTRIM_TRIMVAL             (uint8_t)(0x7F)
/** @brief Defines a bitmask for the OSCTRIM_SIGN bit. */
#define MCP7940N_OSCTRIM_SIGN                (uint8_t)(0x80)
/** @} */

/** @{ @name ALMxSEC Register Masks */
/** @brief Defines a bitmask for ALMxSEC_SECONE bits. */
#define MCP7940N_ALMxSEC_SECONE              (uint8_t)(0x0F)
/** @brief Defines a bitmask for ALMxSEC_SECTEN bits. */
#define MCP7940N_ALMxSEC_SECTEN              (uint8_t)(0x70)
/** @} */

/** @{ @name ALMxMIN Register Masks */
/** @brief Defines a bitmask for ALMxMIN_MINONE bits. */
#define MCP7940N_ALMxMIN_MINONE              (uint8_t)(0x0F)
/** @brief Defines a bitmask for ALMxMIN_MINTEN bits. */
#define MCP7940N_ALMxMIN_MINTEN              (uint8_t)(0x70)
/** @} */

/** @{ @name ALMxHOUR Register Masks */
/** @brief Defines a bitmask for ALMxHOUR_HRONE bits. */
#define MCP7940N_ALMxHOUR_HRONE              (uint8_t)(0x0F)
/** @brief Defines a bitmask for ALMxHOUR_HRTEN bits. */
#define MCP7940N_ALMxHOUR_HRTEN              (uint8_t)(0x30)
/** @brief Defines a bitmask for the ALMxHOUR_AMPM / highest ALMxHOUR_HRTEN bit. */
#define MCP7940N_ALMxHOUR_AMPM               (uint8_t)(0x20)
/** @brief Defines a bitmask for the ALMxHOUR_1224 bit. */
#define MCP7940N_ALMxHOUR_1224               (uint8_t)(0x40)
/** @} */

/** @{ @name ALMxWKDAY Register Masks */
/** @brief Defines a bitmask for ALMxWKDAY_WKDAY bits. */
#define MCP7940N_ALMxWKDAY_WKDAY             (uint8_t)(0x07)
/** @brief Defines a bitmask for the ALMxWKDAY_ALMxIF bit. */
#define MCP7940N_ALMxWKDAY_ALMxIF            (uint8_t)(0x08)
/** @brief Defines a bitmask for ALMxWKDAY_ALMxMSK bits. */
#define MCP7940N_ALMxWKDAY_ALMxMSK           (uint8_t)(0x70)
/** @brief Defines a bitmask for the ALMxWKDAY_ALMPOL bit. */
#define MCP7940N_ALMxWKDAY_ALMPOL            (uint8_t)(0x80)
/** @} */

/** @{ @name ALMxDATE Register Masks */
/** @brief Defines a bitmask for ALMxDATE_DATEONE bits. */
#define MCP7940N_ALMxDATE_DATEONE            (uint8_t)(0x0F)
/** @brief Defines a bitmask for ALMxDATE_DATETEN bits. */
#define MCP7940N_ALMxDATE_DATETEN            (uint8_t)(0x30)
/** @} */

/** @{ @name ALMxMTH Register Masks */
/** @brief Defines a bitmask for ALMxMTH_MTHONE bits. */
#define MCP7940N_ALMxMTH_MTHONE              (uint8_t)(0x0F)
/** @brief Defines a bitmask for ALMxMTH_MTHTEN bits. */
#define MCP7940N_ALMxMTH_MTHTEN              (uint8_t)(0x10)
/** @} */

/** @{ @name PWRDNMIN Register Masks */
/** @brief Defines a bitmask for PWRDNMIN_MINONE bits. */
#define MCP7940N_PWRDNMIN_MINONE             (uint8_t)(0x0F)
/** @brief Defines a bitmask for PWRDNMIN_MINTEN bits. */
#define MCP7940N_PWRDNMIN_MINTEN             (uint8_t)(0x70)
/** @} */

/** @{ @name PWRDNHOUR Register Masks */
/** @brief Defines a bitmask for PWRDNHOUR_HRONE bits. */
#define MCP7940N_PWRDNHOUR_HRONE             (uint8_t)(0x0F)
/** @brief Defines a bitmask for PWRDNHOUR_HRTEN bits. */
#define MCP7940N_PWRDNHOUR_HRTEN             (uint8_t)(0x30)
/** @brief Defines a bitmask for the PWRDNHOUR_AMPM / highest PWRDNHOUR_HRTEN bit. */
#define MCP7940N_PWRDNHOUR_AMPM              (uint8_t)(0x20)
/** @brief Defines a bitmask for the PWRDNHOUR_1224 bit. */
#define MCP7940N_PWRDNHOUR_1224              (uint8_t)(0x40)
/** @} */

/** @{ @name PWRDNDATE Register Masks */
/** @brief Defines a bitmask for PWRDNDATE_DATEONE bits. */
#define MCP7940N_PWRDNDATE_DATEONE           (uint8_t)(0x0F)
/** @brief Defines a bitmask for PWRDNDATE_DATETEN bits. */
#define MCP7940N_PWRDNDATE_DATETEN           (uint8_t)(0x30)
/** @} */

/** @{ @name PWRDNMTH Register Masks */
/** @brief Defines a bitmask for PWRDNMTH_MTHONE bits. */
#define MCP7940N_PWRDNMTH_MTHONE             (uint8_t)(0x0F)
/** @brief Defines a bitmask for PWRDNMTH_MTHTEN bits. */
#define MCP7940N_PWRDNMTH_MTHTEN             (uint8_t)(0x10)
/** @brief Defines a bitmask for PWRDNMTH_WKDAY bits. */
#define MCP7940N_PWRDNMTH_WKDAY              (uint8_t)(0xE0)
/** @} */

/** @{ @name PWRUPMIN Register Masks */
/** @brief Defines a bitmask for PWRUPMIN_MINONE bits. */
#define MCP7940N_PWRUPMIN_MINONE             (uint8_t)(0x0F)
/** @brief Defines a bitmask for PWRUPMIN_MINTEN bits. */
#define MCP7940N_PWRUPMIN_MINTEN             (uint8_t)(0x70)
/** @} */

/** @{ @name PWRUPHOUR Register Masks */
/** @brief Defines a bitmask for PWRUPHOUR_HRONE bits. */
#define MCP7940N_PWRUPHOUR_HRONE             (uint8_t)(0x0F)
/** @brief Defines a bitmask for PWRUPHOUR_HRTEN bits. */
#define MCP7940N_PWRUPHOUR_HRTEN             (uint8_t)(0x30)
/** @brief Defines a bitmask for the PWRUPHOUR_AMPM / highest PWRUPHOUR_HRTEN bit. */
#define MCP7940N_PWRUPHOUR_AMPM              (uint8_t)(0x20)
/** @brief Defines a bitmask for the PWRUPHOUR_1224 bit. */
#define MCP7940N_PWRUPHOUR_1224              (uint8_t)(0x40)
/** @} */

/** @{ @name PWRUPDATE Register Masks */
/** @brief Defines a bitmask for PWRUPDATE_DATEONE bits. */
#define MCP7940N_PWRUPDATE_DATEONE           (uint8_t)(0x0F)
/** @brief Defines a bitmask for PWRUPDATE_DATETEN bits. */
#define MCP7940N_PWRUPDATE_DATETEN           (uint8_t)(0x30)
/** @} */

/** @{ @name PWRUPMTH Register Masks */
/** @brief Defines a bitmask for PWRUPMTH_MTHONE bits. */
#define MCP7940N_PWRUPMTH_MTHONE             (uint8_t)(0x0F)
/** @brief Defines a bitmask for PWRUPMTH_MTHTEN bits. */
#define MCP7940N_PWRUPMTH_MTHTEN             (uint8_t)(0x10)
/** @brief Defines a bitmask for PWRUPMTH_WKDAY bits. */
#define MCP7940N_PWRUPMTH_WKDAY              (uint8_t)(0xE0)
/** @} */

/** @{ @name MFP Mode Masks */
/** 
 * @brief Defines a bitmask for clearing the SQWEN bit, resulting in alarm output mode.
 * If none of the alarms are enabled, the operation results in GPIO mode instead.
 * Use bitwise AND (&) on the CONTROL register.
 * @details Example: @code MCP7940N_GetLocalRegisters()->CONTROL &= MCP7940N_MFP_ALARM; @endcode
 */
#define MCP7940N_MFP_ALARM                   (uint8_t)(0xBF)
/** 
 * @brief Defines a bitmask for setting the SQWEN bit, resulting in squarewave output mode. 
 * Use bitwise OR (|) on the CONTROL register.
 * @details Example: @code MCP7940N_GetLocalRegisters()->CONTROL |= MCP7940N_MFP_SQUARE; @endcode
 */
#define MCP7940N_MFP_SQUARE                  (uint8_t)(0x40)
/** 
 * @brief Defines a bitmask for clearing SQWEN and ALMxEN bits, resulting in GPIO output mode. 
 * Use bitwise AND (&) on the CONTROL register.
 * @details Example: @code MCP7940N_GetLocalRegisters()->CONTROL &= MCP7940N_MFP_GPIO; @endcode
 */
#define MCP7940N_MFP_GPIO                    (uint8_t)(0x8F)
/** @} */

/** @{ @name Alarm IDs */
/** @brief Define for selecting Alarm 0. */
#define MCP7940N_ALARM0                      (uint8_t)(0x00)
/** @brief Define for selecting Alarm 1. */
#define MCP7940N_ALARM1                      (uint8_t)(0x01)
/** @} */

/** @{ @name Alarm modes */
/** @brief Define for selecting seconds alarm mode. */
#define MCP7940N_ALARM_MODE_SECONDS          (uint8_t)(0x00)
/** @brief Define for selecting minutes alarm mode. */
#define MCP7940N_ALARM_MODE_MINUTES          (uint8_t)(0x10)
/** @brief Define for selecting hours alarm mode. */
#define MCP7940N_ALARM_MODE_HOURS            (uint8_t)(0x20)
/** @brief Define for selecting weekdays alarm mode. */
#define MCP7940N_ALARM_MODE_WEEKDAYS         (uint8_t)(0x30)
/** @brief Define for selecting dates alarm mode. */
#define MCP7940N_ALARM_MODE_DATES            (uint8_t)(0x40)
/** @brief Define for selecting all alarm mode. */
#define MCP7940N_ALARM_MODE_ALL              (uint8_t)(0x70)
/** @} */

/** @{ @name Alarm polarity */
/** @brief Define for selecting active high GPIO polarity. */
#define MCP7940N_ALARM_POLARITY_HIGH         (uint8_t)(0x80)
/** @brief Define for selecting active low GPIO polarity. */
#define MCP7940N_ALARM_POLARITY_LOW          (uint8_t)(0x00)
/** @} */

/** @{ @name Alarm Enable Status */
/** @brief Define for Alarm 0. enabled status check. */
#define MCP7940N_ALARM0_ENABLED              (uint8_t)(0x10)
/** @brief Define for Alarm 1. enabled status check. */
#define MCP7940N_ALARM1_ENABLED              (uint8_t)(0x20)
/** @brief Define for Alarm disabled status check. */
#define MCP7940N_ALARM_DISABLED              (uint8_t)(0x00)
/** @} */

/** @{ @name Alarm Fire Status */
/** @brief Define indicating that an alarm has fired. */
#define MCP7940N_ALARM_FIRED                 (uint8_t)(0x08)
/** @brief Define indicating that an alarm has not fired. */
#define MCP7940N_ALARM_NOT_FIRED             (uint8_t)(0x00)
/** @} */

/** @{ @name Squarewave Frequency Modes */
/** @brief Define for selecting 1Hz squarewave output. */
#define MCP7940N_SQUAREWAVE_1HZ              (uint8_t)(0x00)
/** @brief Define for selecting 4096kHz squarewave output. */
#define MCP7940N_SQUAREWAVE_4096KHZ          (uint8_t)(0x01)
/** @brief Define for selecting 8192kHz squarewave output. */
#define MCP7940N_SQUAREWAVE_8192KHZ          (uint8_t)(0x02)
/** @brief Define for selecting 32.768kHz squarewave output. */
#define MCP7940N_SQUAREWAVE_32768KHZ         (uint8_t)(0x03)
/** @} */

/** @{ @name Weekday names */
/** @brief Define for unknown weekday. */
#define MCP7940N_WEEKDAY_NONE                (uint8_t)(0x00)
/**  @brief Define for Monday. */
#define MCP7940N_WEEKDAY_MONDAY              (uint8_t)(0x02)
/** @brief Define for Tuesday. */
#define MCP7940N_WEEKDAY_TUESDAY             (uint8_t)(0x03)
/** @brief Define for Wednesday. */
#define MCP7940N_WEEKDAY_WEDNESDAY           (uint8_t)(0x04)
/** @brief Define for Thursday. */
#define MCP7940N_WEEKDAY_THURSDAY            (uint8_t)(0x05)
/** @brief Define for Friday. */
#define MCP7940N_WEEKDAY_FRIDAY              (uint8_t)(0x06)
/** @brief Define for Saturday. */
#define MCP7940N_WEEKDAY_SATURDAY            (uint8_t)(0x07)
/** @brief Define for Sunday. */
#define MCP7940N_WEEKDAY_SUNDAY              (uint8_t)(0x01)
/** @} */

/** @{ @name External Oscillator Enable Status */
/**  @brief Define indicating that external oscillator signal mode is enabled. */
#define MCP7940N_EXTERNAL_OSC_ENABLED        (uint8_t)(0x08)
/** @brief Define indicating that external oscillator  signal mode is disabled. */
#define MCP7940N_EXTERNAL_OSC_DISABLED       (uint8_t)(0x00)
/** @} */

/** @{ @name Coarse Trimming Status */
/** @brief Define indicating that coarse trimming mode is enabled. */
#define MCP7940N_COARSE_TRIMMING_ENABLED     (uint8_t)(0x04)
/** @brief Define indicating that coarse trimming mode is disabled. */
#define MCP7940N_COARSE_TRIMMING_DISABLED    (uint8_t)(0x00)
/** @} */

/** @{ @name GPIO Status */
/** @brief Define for selecting GPIO output high. */
#define MCP7940N_GPIO_HIGH                   (uint8_t)(0x80)
/** @brief Define for selecting GPIO output low. */
#define MCP7940N_GPIO_LOW                    (uint8_t)(0x00)
/** @} */

/** @{ @name Power-fail Status */
/** @brief Define indicating that the powerfail  flag is set. */
#define MCP7940N_POWER_FAILED                (uint8_t)(0x10)
/** @brief Define indicating that the powerfail flag is not set. */
#define MCP7940N_POWER_NOT_FAILED            (uint8_t)(0x00)
/** @} */

/** @{ @name External Battery Enable Status */
/** @brief Define indicating that the backup battery is enabled. */
#define MCP7940N_BATTERY_ENABLED             (uint8_t)(0x08)
/** @brief Define indicating that the backup battery is disabled. */
#define MCP7940N_BATTERY_DISABLED            (uint8_t)(0x00)
/** @} */

/** @{ @name Oscillator Status */
/** @brief Define indicating that the oscillator is currently running. */
#define MCP7940N_OSCILLATOR_RUNNING          (uint8_t)(0x20)
/** @brief Define indicating that the oscillator is currently not running. */
#define MCP7940N_OSCILLATOR_NOT_RUNNING      (uint8_t)(0x00)
/** @} */

/** @{ @name Leapyear Status */
/** @brief Define indicating that the current year is a leapyear. */
#define MCP7940N_LEAPYEAR                    (uint8_t)(0x20)
/** @brief Define indicating that the current year is not a leapyear. */
#define MCP7940N_NOT_LEAPYEAR                (uint8_t)(0x00)
/** @} */

#endif // MCP7940N_DEFS_H_INCLUDED

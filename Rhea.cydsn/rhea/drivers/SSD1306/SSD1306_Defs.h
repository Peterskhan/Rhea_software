#pragma once
#ifndef SSD1306_DEFS_H_INCLUDED
#define SSD1306_DEFS_H_INCLUDED

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
 * @file    SSD1306_Defs.h
 * @author  Peter Gyulai
 * @version 1.0.1
 * @date    2020.03.20
 * @brief   Macro definitions.
 * @details
 * This header file contains all the macro definitions used by the SSD1306 driver library.
 * These macros are used throughout the implementation and accessible by the end user. The
 * general convention is that all macros are preceeded by the SSD1306_ prefix.
 */

 /** @{ @name Default initialization settings */
 /** @brief Defines default value for clock division and oscillator frequency. */
#define SSD1306_CLOCK_DIV_OSC_DEFAULT       (uint8_t)(0x80)
/** @brief Defines default value for multiplex ratio. */
#define SSD1306_MULTIPLEX_RATIO_DEFAULT     (uint8_t)(0x3F)
/** @brief Defines default value for display offset. */
#define SSD1306_DISPLAY_OFFSET_DEFAULT      (uint8_t)(0x00)
/** @brief Defines default value for display start line. */
#define SSD1306_DISPLAY_START_LINE_DEFAULT  (uint8_t)(0x00)
/** @brief Defines default value for COM pins settings. */
#define SSD1306_COM_PINS_DEFAULT            (uint8_t)(0x12)
/** @brief Defines default value for contrast. */
#define SSD1306_CONTRAST_DEFAULT            (uint8_t)(0xCF)
/** @brief Defines default value for precharge period. */
#define SSD1306_PRECHARGE_PERIOD_DEFAULT    (uint8_t)(0xF1)
/** @brief Defines default value for VCOM deselect settings. */
#define SSD1306_VCOM_DESELECT_DEFAULT       (uint8_t)(0x40)
/** @} */

/** @{ @name Size definitions */
#ifdef SSD1306_128X32

	/**
	 * @def SSD1306_128X32
	 * @brief Define to compile for 128x32 display mode.
	 */

#define SSD1306_BUFFER_SIZE             (uint16_t)(512)
#define SSD1306_WIDTH                   (uint8_t) (128)
#define SSD1306_HEIGHT                  (uint8_t) (32)
#elif defined(SSD1306_96X16)

	/**
	 * @def SSD1306_96X16
	 * @brief Define to compile for 96x16 display mode.
	 */

#define SSD1306_BUFFER_SIZE             (uint8_t) (192)
#define SSD1306_WIDTH                   (uint8_t) (96)
#define SSD1306_HEIGHT                  (uint8_t) (16)
#else 

	/**
	 * @def SSD1306_128X64
	 * @brief Define to compile for 128x64 display mode.
	 * @details Define SSD1306_128X32 or SSD1306_96X16 for other resolutions.
	 */

#define SSD1306_128X64 
#define SSD1306_BUFFER_SIZE             (uint16_t)(1024)
#define SSD1306_WIDTH                   (uint8_t) (128)
#define SSD1306_HEIGHT                  (uint8_t) (64)
#endif

	 /**
	  * @def SSD1306_BUFFER_SIZE
	  * @brief Defines the number of bytes needed for the display buffer.
	  *
	  * @def SSD1306_WIDTH
	  * @brief Defines the width of the display in pixels.
	  *
	  * @def SSD1306_HEIGHT
	  * @brief Defines the height of the display in pixels.
	  */

	  /** @} */

	  /** @{ @name I2C parameters */
	  /** @brief Defines the default I2C address. */
#define SSD1306_I2C_ADDR                    (uint8_t)(0x3D)
/** @brief Defines the control byte for commands. */
#define SSD1306_COMMAND                     (uint8_t)(0x00)
/** @brief Defines the control byte for data. */
#define SSD1306_DATA                        (uint8_t)(0x40)
/** @brief Defines I2C read operation. */
#define SSD1306_I2C_READ                    (uint8_t)(0x01)
/** @brief Defines I2C write operation. */
#define SSD1306_I2C_WRITE                   (uint8_t)(0x00)
/** @} */

/** @{ @name Fundamental commands */
/** @brief Defines the command byte for contrast settings. */
#define SSD1306_CONTRAST                    (uint8_t)(0x81)
/** @brief Defines the command byte for entire display mode ON. */
#define SSD1306_ENTIRE_DISPLAY_ON           (uint8_t)(0xA4)
/** @brief Defines the command byte for entire display mode OFF. */
#define SSD1306_ENTIRE_DISPLAY_RESUME       (uint8_t)(0xA5)
/** @brief Defines the command byte for normal display mode. */
#define SSD1306_DISPLAY_NORMAL              (uint8_t)(0xA6)
/** @brief Defines the command byte for inverted display mode. */
#define SSD1306_DISPLAY_INVERSE             (uint8_t)(0xA7)
/** @brief Defines the command byte for display ON. */
#define SSD1306_DISPLAY_ON                  (uint8_t)(0xAE)
/** @brief Defines the command byte for display OFF. */
#define SSD1306_DISPLAY_OFF                 (uint8_t)(0xAF)
/** @} */

// Scrolling functionality is currently not supported.
/** @{ @name Scrolling commands */
/** @} */

/** @{ @name Addressing commands */
/** @brief Defines the command byte for setting lower nibble of column start address. */
#define SSD1306_LOWER_COLUMN_ADDR_START     (uint8_t)(0x00)
/** @brief Defines the command byte for setting higher nibble of column start address. */
#define SSD1306_HIGHER_COLUMN_ADDR_START    (uint8_t)(0x10)
/** @brief Defines the command byte for setting memory addressing mode. */
#define SSD1306_MEMORY_MODE                 (uint8_t)(0x20)
/** @brief Defines the command byte for horizontal addressing mode. */
#define SSD1306_MEMORY_MODE_HORIZONTAL      (uint8_t)(0x00)
/** @brief Defines the command byte for vertical addressing mode. */
#define SSD1306_MEMORY_MODE_VERTICAL        (uint8_t)(0x01)
/** @brief Defines the command byte for page addressing mode. */
#define SSD1306_MEMORY_MODE_PAGE            (uint8_t)(0x02)
/** @brief Defines the command byte for setting column address. */
#define SSD1306_COLUMN_ADDR                 (uint8_t)(0x21)
/** @brief Defines the command byte for setting page address. */
#define SSD1306_PAGE_ADDR                   (uint8_t)(0x22)
/** @brief Defines the command byte for setting page address start. */
#define SSD1306_PAGE_ADDR_START             (uint8_t)(0xB0)
/** @} */

/** @{ @name Hardware configuration commands */
/** @brief Defines the command byte for display start line settings. */
#define SSD1306_DISPLAY_START_LINE          (uint8_t)(0x40)
/** @brief Defines the command byte for segment remapping OFF. */
#define SSD1306_SEGMENT_REMAP_OFF           (uint8_t)(0xA0)
/** @brief Defines the command byte for segment remapping ON. */
#define SSD1306_SEGMENT_REMAP_ON            (uint8_t)(0xA1)
/** @brief Defines the command byte for multiplex ratio settings. */
#define SSD1306_MULTIPLEX_RATIO             (uint8_t)(0xA8)
/** @brief Defines the command byte for incremental COM scan. */
#define SSD1306_COM_SCAN_INC                (uint8_t)(0xC0)
/** @brief Defines the command byte for decremental COM scan. */
#define SSD1306_COM_SCAN_DEC                (uint8_t)(0xC8)
/** @brief Defines the command byte for display offset settings. */
#define SSD1306_DISPLAY_OFFSET              (uint8_t)(0xD3)
/** @brief Defines the command byte for COM pins configuration. */
#define SSD1306_COM_PINS                    (uint8_t)(0xDA)
/** @brief Defines the command byte for chargepump settings. */
#define SSD1306_CHARGEPUMP                  (uint8_t)(0x8D)
/** @brief Defines the command byte for chargepump ON. */
#define SSD1306_CHARGEPUMP_ON               (uint8_t)(0x14)
/** @brief Defines the command byte for chargepump OFF. */
#define SSD1306_CHARGEPUMP_OFF              (uint8_t)(0x10)
/** @} */

/** @{ @name Timing & Driving Scheme commands */
/** @brief Defines the command byte for clock division and oscillator settings. */
#define SSD1306_CLOCK_DIV_OSC               (uint8_t)(0xD5)
/** @brief Defines the command byte for precharge period settings. */
#define SSD1306_PRECHARGE_PERIOD            (uint8_t)(0xD9)
/** @brief Defines the command byte for VCOM deselect settings. */
#define SSD1306_VCOM_DESELECT               (uint8_t)(0xDB)
/** @} */

#endif // SSD1306_DEFS_H_INCLUDED
#pragma once 
#ifndef SSD1306_H_INCLUDED
#define SSD1306_H_INCLUDED

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
 * @file    SSD1306.h
 * @author  Peter Gyulai
 * @version 1.0.1
 * @date    2020.03.20
 * @brief   Functions and datastructures.
 * @details
 * This file contains the declarations of the functions and datastructures
 * available in the SSD1306 driver library.
 */


// Standard includes
#include <stdint.h>

// Project includes
#include "SSD1306_Defs.h"


/**
 * @brief
 * Structure for passing the I2C bus controller functions,
 * that are used by the SSD1306 driver.
 * @details
 * The function pointer members must be provided for the library to
 * control trafic on the I2C bus. The library is independent from the
 * specific I2C implementation and only needs these callbacks to operate.
 * If the I2C implementation does not provide functions with these specific
 * function signatures, consider creating proxy functions to pass.
 */
typedef struct SSD1306_I2CControllerStruct {

	/**
	 * @brief Pointer to a function that generates a START condition.
	 * @param address The 7-bit I2C device address.
	 * @param read Zero for write, non-zero for read operation.
	 */
	void (*MasterSendStart)(uint8_t address, uint8_t read);

	/**
	 * @brief Pointer to a function that generates a STOP condition.
	 */
	void (*MasterSendStop)(void);

	/**
	 * @brief Pointer to a function that writes one byte to the bus.
	 * @param byte The byte to write to the I2C bus.
	 */
	void (*MasterWriteByte)(uint8_t byte);

} SSD1306_I2CControllerStruct;

/**
 * @brief Installs the I2C bus controller structure holding function pointers to the bus control methods.
 * @param controller The structure containing control function pointers.
 */
void SSD1306_SetI2CController(SSD1306_I2CControllerStruct controller);

/**
 * @brief Returns the display shadow buffer.
 * @details
 * The preferred method to access the display buffer is to use #SSD1306_WritePixel().
 * However, certain operations can be performed more effectively by directly modifying
 * the display buffer, because #SSD1306_WritePixel() performs only one-bit operations
 * on data bytes. #SSD1306_GetDisplayBuffer(void) can be used the modify the shadow
 * buffer directly for performing operations such as drawing filled rectangles or lines
 * more efficiently. Special care must be taken not to corrupt data when using this
 * function. The library maintains the display buffer using horizontal memory addressing
 * mode of the SSD1306, which means that data bytes are in this specific order:
 * - Columns of PAGE0, where each column is one byte and each page contains #SSD1306_WIDTH columns.
 * - ...
 * - Columns of PAGE[N-1], where N is the total number of pages: N = #SSD1306_HEIGHT / 8
 *
 * \image html ssd1306_horizontal_mode.png "Horizontal addressing mode of the SSD1306" width=600px
 *
 * @returns Pointer to the display buffer.
 */
uint8_t* SSD1306_GetDisplayBuffer(void);

/**
 * @brief
 * Initializes the display with default values provided in SSD1306_Defs.h, and clears
 * the display shadow buffer.
 */
void SSD1306_Init();

/**
 * @brief Resets the device settings and clears the shadow buffer & physical display.
 */
void SSD1306_Reset();

/**
 * @brief Sends a single command byte to the device.
 * @details
 * The function is used only for sending one command byte. For using multibyte
 * commands and longer command sequences use #SSD1306_WriteCommands() instead.
 * @param command The command byte to write.
 */
void SSD1306_WriteCommand(uint8_t command);

/**
 * @brief Writes multiple commands to the device.
 * @details
 * This function is more effective than #SSD1306_WriteCommand() when multiple
 * consecutive commands need to be sent to the device. The function sends the
 * stream of commands in one I2C transmission instead of multiple single command
 * transactions.
 * @param commands Array of command bytes to write.
 * @param count The number of bytes in commands.
 */
void SSD1306_WriteCommands(uint8_t commands[], uint8_t count);

/**
 * @brief
 * Writes the specified stream of data to the device.
 * @details
 * This function does not initialize memory addressing, only sends a control
 * byte indicating display data and the stream of data provided. Please use
 * the display shadow buffer and see #SSD1306_RefreshDisplay(void) for details.
 * @param data Array of data bytes to write.
 * @param count The number of bytes in data.
 */
void SSD1306_WriteData(uint8_t data[], uint16_t count);

/**
 * @brief
 * Writes the specified color to the pixel at [x,y] display coordinates.
 * @details
 * This function only updates the content of the display shadow buffer.
 * For changes to be effective, #SSD1306_RefreshDisplay(void) must be called.
 * @param x Horizontal pixel coordinate.
 * @param y Vertical pixel coordinate.
 * @param color Zero for inactive, non-zero for active pixel.
 */
void SSD1306_WritePixel(uint8_t x, uint8_t y, uint8_t color);

/**
 * @brief
 * Clears the content of the display shadow buffer, by filling it with zeros.
 * @details
 * For changes to be effective, #SSD1306_RefreshDisplay(void) must be called.
 */
void SSD1306_ClearDisplay(void);

/**
 * @brief Writes the content of the display shadow buffer to the device.
 */
void SSD1306_RefreshDisplay(void);

#endif // SSD1306_H_INCLUDED
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
 * @file    SSD1306.c
 * @author  Peter Gyulai
 * @version 1.0.1
 * @date    2020.03.20
 * @brief   Library implementation.
 * @details
 * This file contains the function definitions and static variable definitions used
 * by the SSD1306 driver library.
 */

 // Doxygen documentation duplication suppression
#ifndef DOXYGEN_SHOULD_SKIP_THIS

// Project includes
#include "SSD1306.h"


// Structure holding function pointers to I2C handlers
static SSD1306_I2CControllerStruct SSD1306_I2CController;

// Shadow buffer for display data
static uint8_t SSD1306_PixelData[SSD1306_BUFFER_SIZE];

void SSD1306_SetI2CController(SSD1306_I2CControllerStruct controller) {
	SSD1306_I2CController = controller;
}

void SSD1306_Init() {

	// Initializing command sequence
	uint8_t commands[] = {
		SSD1306_DISPLAY_OFF,
		SSD1306_CLOCK_DIV_OSC,
		SSD1306_CLOCK_DIV_OSC_DEFAULT,
		SSD1306_MULTIPLEX_RATIO,
		SSD1306_MULTIPLEX_RATIO_DEFAULT,
		SSD1306_DISPLAY_OFFSET,
		SSD1306_DISPLAY_OFFSET_DEFAULT,
		SSD1306_DISPLAY_START_LINE | SSD1306_DISPLAY_START_LINE_DEFAULT,
		SSD1306_CHARGEPUMP,
		SSD1306_CHARGEPUMP_ON,
		SSD1306_MEMORY_MODE,
		SSD1306_MEMORY_MODE_HORIZONTAL,
		SSD1306_SEGMENT_REMAP_OFF,
		SSD1306_COM_SCAN_INC,
		SSD1306_COM_PINS,
		SSD1306_COM_PINS_DEFAULT,
		SSD1306_CONTRAST,
		SSD1306_CONTRAST_DEFAULT,
		SSD1306_PRECHARGE_PERIOD,
		SSD1306_PRECHARGE_PERIOD_DEFAULT,
		SSD1306_VCOM_DESELECT,
		SSD1306_VCOM_DESELECT_DEFAULT,
		SSD1306_LOWER_COLUMN_ADDR_START,
		SSD1306_HIGHER_COLUMN_ADDR_START,
		SSD1306_ENTIRE_DISPLAY_RESUME,
		SSD1306_DISPLAY_NORMAL,
		SSD1306_DISPLAY_ON
	};

	// Sending initialization commands
	SSD1306_WriteCommands(commands, 25);

	// Clearing display shadow buffer
	SSD1306_ClearDisplay();
}

void SSD1306_Reset(void) {

	// Restoring initial settings
	SSD1306_Init();

	// Clearing display
	SSD1306_RefreshDisplay();
}

uint8_t* SSD1306_GetDisplayBuffer(void) {
	return SSD1306_PixelData;
}

void SSD1306_WriteCommand(uint8_t command) {

	// Sending START condition & indicating command
	SSD1306_I2CController.MasterSendStart(SSD1306_I2C_ADDR, SSD1306_I2C_WRITE);
	SSD1306_I2CController.MasterWriteByte(SSD1306_COMMAND);

	// Sending command
	SSD1306_I2CController.MasterWriteByte(command);

	// Sending STOP condition
	SSD1306_I2CController.MasterSendStop();
}

void SSD1306_WriteCommands(uint8_t commands[], uint8_t count) {

	// Sending START condition & indicating command stream 
	SSD1306_I2CController.MasterSendStart(SSD1306_I2C_ADDR, SSD1306_I2C_WRITE);
	SSD1306_I2CController.MasterWriteByte(SSD1306_COMMAND);

	// Sending commands
	for (uint8_t i = 0; i < count; i++) {
		SSD1306_I2CController.MasterWriteByte(commands[i]);
	}

	// Sending STOP condition
	SSD1306_I2CController.MasterSendStop();
}

void SSD1306_WriteData(uint8_t data[], uint16_t count) {

	// Sending START condition & indicating data stream 
	SSD1306_I2CController.MasterSendStart(SSD1306_I2C_ADDR, SSD1306_I2C_WRITE);
	SSD1306_I2CController.MasterWriteByte(SSD1306_DATA);

	// Sending data
	for (uint16_t i = 0; i < count; i++) {
		SSD1306_I2CController.MasterWriteByte(data[i]);
	}

	// Sending STOP condition
	SSD1306_I2CController.MasterSendStop();
}

void SSD1306_WritePixel(uint8_t x, uint8_t y, uint8_t color) {

	// CODE WORKS FOR HORIZONTAL MODE ONLY!!!

	// Coordinate bounds check
	if (x > SSD1306_WIDTH - 1 || y > SSD1306_HEIGHT - 1) return;

	// Calculating page and column index
	uint8_t page = y / 8;
	uint8_t column = x;

	// Calculating byte index in pixelData & bitshift value
	uint16_t byteIndex = page * SSD1306_WIDTH + column;
	uint8_t bitIndex = y % 8;

	// Setting or clearing the selected bit
    if (color) SSD1306_PixelData[byteIndex] |= (1 << bitIndex);
	else       SSD1306_PixelData[byteIndex] &= ~(1 << bitIndex);
}

void SSD1306_ClearDisplay(void) {

	// Clearing shadow buffer content
	for (unsigned int i = 0; i < SSD1306_BUFFER_SIZE; i++) {
		SSD1306_PixelData[i] = 0x00;
	}
}

void SSD1306_RefreshDisplay(void) {

	// Initialize memory addressing
	SSD1306_I2CController.MasterSendStart(SSD1306_I2C_ADDR, SSD1306_I2C_WRITE);
	SSD1306_I2CController.MasterWriteByte(SSD1306_COMMAND);

	// Setting column addressing to fullscale: [0; WIDTH - 1]
	SSD1306_I2CController.MasterWriteByte(SSD1306_COLUMN_ADDR);
	SSD1306_I2CController.MasterWriteByte(0);
	SSD1306_I2CController.MasterWriteByte(SSD1306_WIDTH - 1);

	// Setting page addressing to fullscale: [0; PAGES - 1]
	SSD1306_I2CController.MasterWriteByte(SSD1306_PAGE_ADDR);
	SSD1306_I2CController.MasterWriteByte(0);
	SSD1306_I2CController.MasterWriteByte((SSD1306_HEIGHT / 8) - 1);
	SSD1306_I2CController.MasterSendStop();

	// Writing pixel data
	SSD1306_WriteData(SSD1306_PixelData, SSD1306_BUFFER_SIZE);
}

#endif // DOXYGEN_SHOULD_SKIP_THIS

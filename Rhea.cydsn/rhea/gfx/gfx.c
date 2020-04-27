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
 * @file    gfx.c
 * @author  Peter Gyulai
 * @version 1.0.0
 * @date    2020.04.26
 * @brief   Library implementation.
 * @details
 * This file contains the function definitions used by the Rhea graphics library.
 */

// Doxygen documentation duplication suppression
#ifndef DOXYGEN_SHOULD_SKIP_THIS

// Standard includes
#include <math.h>
#include <stdlib.h>

// Project includes
#include "gfx.h"
#include "gfx_impl.h"
#include "fonts/codefont_8x8.h"
    
    
// Local font settings & data
static rhea_gfx_font rhea_gfx_localFont;

// Local cursor position
static rhea_gfx_coordinate rhea_gfx_cursorX = 0;
static rhea_gfx_coordinate rhea_gfx_cursorY = 0;

void rhea_gfx_Initialize(void) {

	// Invoking driver implementation
	rhea_gfx_initialize_impl();

	// Initializing default fonts
	rhea_gfx_localFont = (rhea_gfx_font) {
		.fontDescriptors = codefont_8x8_descriptors,
		.fontData        = codefont_8x8_data,
		.fontHeight      = 8
	};

	// Initializing text cursor
	rhea_gfx_cursorX = 0;
	rhea_gfx_cursorY = 0;
}

void rhea_gfx_Reset(void) {

	// Invoking driver implementation
	rhea_gfx_reset_impl();
}

void rhea_gfx_Clear(void) {

	// Invoking driver implementation
	rhea_gfx_clear_impl();
}

void rhea_gfx_Refresh(void) {

	// Invoking driver implementation
	rhea_gfx_refresh_impl();
}

void rhea_gfx_SetFont(rhea_gfx_font font) {

	// Setting local font instance
	rhea_gfx_localFont = font;
}

void rhea_gfx_DrawPixel(rhea_gfx_coordinate x, rhea_gfx_coordinate y, rhea_gfx_color color) {

	// Drawing pixel
	rhea_gfx_writePixel_impl(x, y, color);

	// Refreshing display
	rhea_gfx_Refresh();
}

void rhea_gfx_DrawLineLow(rhea_gfx_coordinate x0, rhea_gfx_coordinate y0, rhea_gfx_coordinate x1, rhea_gfx_coordinate y1, rhea_gfx_color color) {

	// Bresenham's Line Drawing Algorithm for negative slopes
	int16_t dx = x1 - x0;
	int16_t dy = y1 - y0;
	int16_t yi = 1;

	if (dy < 0) {
		yi = -1;
		dy = -dy;
	}

	int16_t D = 2 * dy - dx;
	int16_t y = y0;

	for (int16_t x = x0; x < x1; x++) {
		rhea_gfx_writePixel_impl(x, y, color);
		if (D > 0) {
			y = y + yi;
			D = D - 2 * dx;
		}

		D = D + 2 * dy;
	}
}

void rhea_gfx_DrawLineHigh(rhea_gfx_coordinate x0, rhea_gfx_coordinate y0, rhea_gfx_coordinate x1, rhea_gfx_coordinate y1, rhea_gfx_color color) {

	// Bresenham's Line Drawing Algorithm for positive slopes
	int16_t dx = x1 - x0;
	int16_t dy = y1 - y0;
	int16_t xi = 1;

	if (dx < 0) {
		xi = -1;
		dx = -dx;
	}

	int16_t D = 2 * dx - dy;
	int16_t x = x0;

	for (int16_t y = y0; y < y1; y++) {
		rhea_gfx_writePixel_impl(x, y, color);
		if (D > 0) {
			x = x + xi;
			D = D - 2 * dy;
		}

		D = D + 2 * dx;
	}
}

void rhea_gfx_DrawLine(rhea_gfx_coordinate x0, rhea_gfx_coordinate y0, rhea_gfx_coordinate x1, rhea_gfx_coordinate y1, rhea_gfx_color color) {

	// Checking if can be implemented efficiently
	if (x0 == x1) {
		rhea_gfx_DrawVerticalLine(x0, y0 < y1 ? y0 : y1, abs(y1 - y0), color); return;
	}
	if (y0 == y1) {
		rhea_gfx_DrawHorizontalLine(x0 < x1 ? x0 : x1, y0, abs(x1 - x0), color); return;
	}

	// Bresenham's Line Drawing Algorithm
	if (abs(y1 - y0) < abs(x1 - x0)) {
		if (x0 > x1) rhea_gfx_DrawLineLow(x1, y1, x0, y0, color);
		else         rhea_gfx_DrawLineLow(x0, y0, x1, y1, color);
	}
	else {
		if (y0 > y1) rhea_gfx_DrawLineHigh(x1, y1, x0, y0, color);
		else         rhea_gfx_DrawLineHigh(x0, y0, x1, y1, color);
	}

	// Refreshing display
	// rhea_gfx_Refresh();
}

void rhea_gfx_DrawVerticalLine(rhea_gfx_coordinate x, rhea_gfx_coordinate y, rhea_gfx_size_t height, rhea_gfx_color color) {

	// Drawing vertical line
	for (rhea_gfx_size_t i = 0; i < height; i++) rhea_gfx_writePixel_impl(x, y + i, color);

	// Refreshing display
	// rhea_gfx_Refresh();
}

void rhea_gfx_DrawHorizontalLine(rhea_gfx_coordinate x, rhea_gfx_coordinate y, rhea_gfx_size_t length, rhea_gfx_color color) {

	// Drawing horizontal line
	for (rhea_gfx_size_t i = 0; i < length; i++) rhea_gfx_writePixel_impl(x + i, y, color);

	// Refreshing display
	// rhea_gfx_Refresh();
}

void rhea_gfx_DrawCircle(rhea_gfx_coordinate x, rhea_gfx_coordinate y, rhea_gfx_size_t radius, rhea_gfx_color color) {

	// Drawing circle
	for (rhea_gfx_coordinate i = 0; i < RHEA_GFX_WIDTH; i++) {
		for (rhea_gfx_coordinate j = 0; j < RHEA_GFX_HEIGHT; j++) {
			rhea_gfx_size_t distance = (rhea_gfx_size_t) sqrt((x - i) * (x - i) + (y - j) * (y - j));
			if (distance == radius) rhea_gfx_writePixel_impl(i, j, color);
		}
	}

	// Refreshing display
	// rhea_gfx_Refresh();
}

void rhea_gfx_DrawFilledCircle(rhea_gfx_coordinate x, rhea_gfx_coordinate y, rhea_gfx_size_t radius, rhea_gfx_color color) {

	// Drawing filled circle
	for (rhea_gfx_coordinate i = 0; i < RHEA_GFX_WIDTH; i++) {
		for (rhea_gfx_coordinate j = 0; j < RHEA_GFX_HEIGHT; j++) {
			rhea_gfx_size_t distance = (rhea_gfx_size_t) sqrt((x - i) * (x - i) + (y - j) * (y - j));
			if (distance <= radius) rhea_gfx_writePixel_impl(i, j, color);
		}
	}

	// Refreshing display
	// rhea_gfx_Refresh();
}

void rhea_gfx_DrawRectangle(rhea_gfx_coordinate x, rhea_gfx_coordinate y, rhea_gfx_size_t width, rhea_gfx_size_t height, rhea_gfx_color color) {

	// Drawing rectangle
	for (rhea_gfx_size_t i = 0; i < width; i++) {
		for (rhea_gfx_size_t j = 0; j < height; j++) {
			if (i == 0 || i == width - 1 || j == 0 || j == height - 1) {
				rhea_gfx_writePixel_impl(x + i, y + j, color);
			}
		}
	}

	// Refreshing display
	// rhea_gfx_Refresh();
}

void rhea_gfx_DrawFilledRectangle(rhea_gfx_coordinate x, rhea_gfx_coordinate y, rhea_gfx_size_t width, rhea_gfx_size_t height, rhea_gfx_color color) {

	// Drawing filled rectangle
	for (rhea_gfx_size_t i = 0; i < width; i++) {
		for (rhea_gfx_size_t j = 0; j < height; j++) {
			rhea_gfx_writePixel_impl(x + i, y + j, color);
		}
	}

	// Refreshing display
	// rhea_gfx_Refresh();
}

void rhea_gfx_DrawSymbolHelper(rhea_gfx_coordinate x, rhea_gfx_coordinate y, rhea_gfx_symbol_id symbolID) {

	// Extracting symbol descriptor
	rhea_gfx_symbol symbol = rhea_gfx_localFont.fontDescriptors[symbolID];

	// Calculating coordinate limits
	rhea_gfx_coordinate limitHorizontal = x + symbol.width + symbol.paddingHorizontal;
	rhea_gfx_coordinate limitVertical = y + symbol.height + symbol.paddingVertical;

	for (rhea_gfx_coordinate j = y + symbol.paddingVertical; j < limitVertical; j++) {
		for (rhea_gfx_coordinate i = x + symbol.paddingHorizontal; i < limitHorizontal; i++) {

			// Calculating pixel databit position
			uint32_t byteIndex = symbol.offset / 8;
			uint8_t  bitIndex  = symbol.offset % 8;

			// Printing next pixel
			if (rhea_gfx_localFont.fontData[byteIndex] & (1 << (7 - bitIndex))) {
				rhea_gfx_writePixel_impl(i, j, 1);
			}
			else {
				rhea_gfx_writePixel_impl(i, j, 0);
			}

			// Increasing offset
			symbol.offset++;
		}
	}
}

void rhea_gfx_DrawSymbol(rhea_gfx_coordinate x, rhea_gfx_coordinate y, rhea_gfx_symbol_id symbolID) {
    
    // Drawing symbol to display buffer
    rhea_gfx_DrawSymbolHelper(x,y,symbolID);
    
    // Refreshing display
	// rhea_gfx_Refresh();
}

void rhea_gfx_SetCursor(rhea_gfx_coordinate x, rhea_gfx_coordinate y) {
	rhea_gfx_cursorX = x;
	rhea_gfx_cursorY = y;
}

void rhea_gfx_PrintSymbolHelper(rhea_gfx_symbol_id id) {

	// Getting symbol to print
	rhea_gfx_symbol symbol = rhea_gfx_localFont.fontDescriptors[id];

	// Checking display bounds
	if (rhea_gfx_cursorX + symbol.width > RHEA_GFX_WIDTH) {
		rhea_gfx_cursorX = 0;
		rhea_gfx_cursorY += symbol.height + symbol.paddingVertical;
	}

	// Printing symbol
	rhea_gfx_DrawSymbolHelper(rhea_gfx_cursorX, rhea_gfx_cursorY, id);

	// Moving cursor
	rhea_gfx_cursorX += symbol.width + symbol.paddingHorizontal;
}

void rhea_gfx_PrintSymbol(rhea_gfx_symbol_id id) {
 
    // Printing symbol to display buffer
    rhea_gfx_PrintSymbolHelper(id);
    
    // Refreshing display
    // rhea_gfx_Refresh();
}

void rhea_gfx_Print(const char* str) {

	while (*str != '\0') {

		// Handling newline character
		if (*str == '\n') {
			rhea_gfx_cursorX = 0;
			rhea_gfx_cursorY += rhea_gfx_localFont.fontHeight;
			str++;
			continue;
		}
		// Handling unprintable characters
		else if(*str < 32) {
			str++;
			continue;
		}

		// Printing next character
		rhea_gfx_PrintSymbolHelper(*str++ - 32);
	}
    
    // Refreshing display
    // rhea_gfx_Refresh();
}

#endif // DOXYGEN_SHOULD_SKIP_THIS
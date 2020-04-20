#pragma once
#ifndef RHEA_GFX_H_INCLUDED
#define RHEA_GFX_H_INCLUDED

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
 * @file    gfx.h
 * @author  Peter Gyulai
 * @version 1.0.0
 * @date    2020.04.19
 * @brief   Graphics utilities.
 * @details
 * This file contains the graphics utility functions that can draw to the Rhea display.
 */

// Standard includes
#include <stdint.h>

// Project includes
#include "gfx_config.h"
    

/** @brief This structure describes a symbol and it's properties. */
struct rhea_gfx_symbol {
	uint32_t offset;						/**< Bit offset from start of datastream. */
	uint8_t  width;							/**< Width of the symbol in pixels.       */
	uint8_t  height;						/**< Height of the symbol in pixels.      */
	uint8_t  paddingHorizontal;				/**< Horizontal padding in pixels.        */
	uint8_t  paddingVertical;				/**< Vertical padding in pixels.          */
};

/** @brief Typedef for omitting 'struct' keyword from the typename. */
typedef struct rhea_gfx_symbol rhea_gfx_symbol;

/** @brief This structure describes a font and it's properties. */
struct rhea_gfx_font{
	rhea_gfx_symbol*	fontDescriptors;	/**< Descriptors for the symbols.        */
	uint8_t*			fontData;			/**< Bytestream for the font symbols.    */
	uint8_t				fontHeight;			/**< Height of the characters in pixels. */
};

/** @brief Typedef for omitting 'struct' keyword from the typename. */
typedef struct rhea_gfx_font rhea_gfx_font;

/** @brief Typedef for size parameters. */
typedef uint8_t	rhea_gfx_size_t;

/** @brief Typedef for color parameters. */
typedef uint8_t	rhea_gfx_color;

/** @brief Typedef for symbol identifiers. */
typedef uint16_t rhea_gfx_symbol_id;

/** @brief Typedef for display coordinates. */
typedef uint16_t rhea_gfx_coordinate;

/** @{ @name Graphics settings & display control */
/** @brief Initializes the graphics library. */
void rhea_gfx_Initialize();

/** @brief Resets the graphics library. */
void rhea_gfx_Reset(void);

/** @brief Clears the graphics display. */
void rhea_gfx_Clear(void);

/** 
 * @brief Sets the text & symbol font used by the graphics. 
 * @param font The font description structure.
 */
void rhea_gfx_SetFont(rhea_gfx_font font);
/** @} */

/** @{ @name Graphics primitives */
/**
 * @brief Draws a pixel at the given coordinates with the specified color.
 * @param x The x coordinate.
 * @param y The y coordinate.
 * @param color The color of the pixel (zero - inactive, nonzero - active).
 */
void rhea_gfx_DrawPixel(rhea_gfx_coordinate x, rhea_gfx_coordinate y, rhea_gfx_color color);

/**
 * @brief Draws a line of the specified color between the specified coordinates.
 * @param x0 Starting x coordinate.
 * @param y0 Starting y coordinate.
 * @param x1 Ending x coordinate.
 * @param y1 Ending y coordinate.
 * @details 
 * If the line is purely vertical or horizontal the efficient version is called, otherwise
 * the function uses Bresenham's algorithm.
 */
void rhea_gfx_DrawLine(rhea_gfx_coordinate x0, rhea_gfx_coordinate y0, rhea_gfx_coordinate x1, rhea_gfx_coordinate y1, rhea_gfx_color color);

/**
 * @brief Efficiently draws a vertical line of the specified height (towards positive y from the starting coordinates).
 * @param x Starting x coordinate.
 * @param y Starting y coordinate.
 * @param height Height of the line in pixels.
 * @param color Color of the line.
 */
void rhea_gfx_DrawVerticalLine(rhea_gfx_coordinate x, rhea_gfx_coordinate y, rhea_gfx_size_t height, rhea_gfx_color color);

/**
 * @brief Efficiently draws a horizontal line of the specified length (towards positive x from the starting coordinates).
 * @param x Starting x coordinate.
 * @param y Starting y coordinate.
 * @param length Length of the line in pixels.
 * @param color Color of the line.
 */
void rhea_gfx_DrawHorizontalLine(rhea_gfx_coordinate x, rhea_gfx_coordinate y, rhea_gfx_size_t length, rhea_gfx_color color);

/**
 * @brief Draws a circle outline with a given radius centered on the specified coordinates. 
 * @param x Center x coordinate.
 * @param y Center y coordinate.
 * @param radius Radius in pixels.
 * @param color Color of the outline.
 */
void rhea_gfx_DrawCircle(rhea_gfx_coordinate x, rhea_gfx_coordinate y, rhea_gfx_size_t radius, rhea_gfx_color color);

/**
 * @brief Draws a filled circle with a given radius centered on the specified coordinates. 
 * @param x Center x coordinate.
 * @param y Center y coordinate.
 * @param radius Radius in pixels.
 * @param color Color of the circle.
 */
void rhea_gfx_DrawFilledCircle(rhea_gfx_coordinate x, rhea_gfx_coordinate y, rhea_gfx_size_t radius, rhea_gfx_color color);

/**
 * @brief Draws a rectangle outline with the given size at the given coordinates (representing the top-left corner).
 * @param x Starting x coordinate.
 * @param y Starting y coordinate.
 * @param width Width of the rectangle in pixels.
 * @param height Height of the rectangle in pixels.
 * @param color Color of the outline.
 */
void rhea_gfx_DrawRectangle(rhea_gfx_coordinate x, rhea_gfx_coordinate y, rhea_gfx_size_t width, rhea_gfx_size_t height, rhea_gfx_color color);

/**
 * @brief Draws a filled rectangle with the given size at the given coordinates (representing the top-left corner).
 * @param x Starting x coordinate.
 * @param y Starting y coordinate.
 * @param width Width of the rectangle in pixels.
 * @param height Height of the rectangle in pixels.
 * @param color Color of the rectangle.
 */
void rhea_gfx_DrawFilledRectangle(rhea_gfx_coordinate x, rhea_gfx_coordinate y, rhea_gfx_size_t width, rhea_gfx_size_t height, rhea_gfx_color color);

/**
 * @brief Draws a symbol from the current font symbol set at the given coordinates (representing the top-left corner).
 * @param x Starting x coordinate.
 * @param y Starting y coordinate.
 * @param symbolID The ID of the symbol (index in the provided font descriptor array).
 */
void rhea_gfx_DrawSymbol(rhea_gfx_coordinate x, rhea_gfx_coordinate y, rhea_gfx_symbol_id symbolID);
/** @} */

/** @{ @name Text utilities */
/**
 * @brief Sets the text cursor the the specified coordinates.
 * @param x The new x coordinate.
 * @param y The new y coordinate.
 */
void rhea_gfx_SetCursor(rhea_gfx_coordinate x, rhea_gfx_coordinate y);
/**
 * @brief Draws a symbol from the current font symbol set at the text cursor position (representing the top-left corner).
 * @param symbolID The ID of the symbol (index in the provided font descriptor array).
 * @see rhea_gfx_drawSymbol
 */
void rhea_gfx_PrintSymbol(rhea_gfx_symbol_id id);

/**
 * @brief Prints a C-type string at the text cursor position.
 * @details 
 * The cursor is automatically moved by the character width and to
 * a new line if necessary. Wrapping is performed in an every-symbol manner,
 * irrespective of whitespace separation. The function expects the string to
 * contain ASCII characters and automatically ignores non-printable symbols.
 * @param str A zero terminated string.
 */
void rhea_gfx_Print(const char* str);
/** @} */

#endif // RHEA_GFX_H_INLCUDED
#pragma once
#ifndef RHEA_GFX_IMPL_H_INCLUDED
#define RHEA_GFX_IMPL_H_INCLUDED

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
 * @file    gfx_impl.h
 * @author  Peter Gyulai
 * @version 1.0.0
 * @date    2020.04.19
 * @brief   Graphics driver declarations.
 * @details
 * This file contains the graphics driver interface functions that must be
 * implemented when interfacing with a new graphics driver.
 */
    
// Project includes
#include "gfx.h"

/**
 * @brief Initializes the graphics driver.
 * @todo  Implement this function to initialize the graphics driver.
 */
void rhea_gfx_initialize_impl(void);

/**
 * @brief Resets the graphics driver.
 * @todo  Implement this function to reset the graphics driver.
 */
void rhea_gfx_reset_impl(void);

/**
 * @brief Clears the graphics driver (clears the display screen).
 * @todo  Implement this function to clear the graphics driver.
 */
void rhea_gfx_clear_impl(void);

/**
 * @brief Refreshes the graphics driver (flushes the display content).
 * @todo  Implement this function to refresh the graphics driver.
 */
void rhea_gfx_refresh_impl(void);

/**
 * @brief Writes one pixel data to the graphics driver.
 * @todo  Implement this function to write pixels to the graphics driver.
 * @param [in] x The horizontal coordinate of the pixel.
 * @param [in] y The vertical coordinate of the pixel.
 * @param [in] c The color of the pixel.
 */
void rhea_gfx_writePixel_impl(rhea_gfx_coordinate x, rhea_gfx_coordinate y, rhea_gfx_color c);

#endif // RHEA_GFX_IMPL_H_INCLUDED
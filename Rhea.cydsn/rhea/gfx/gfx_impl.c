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
 * @file    gfx_impl.c
 * @author  Peter Gyulai
 * @version 1.0.0
 * @date    2020.04.19
 * @brief   Graphics driver implementation.
 * @details
 * This file contains the graphics driver implementation. Implement the driver 
 * functionality here when porting to a new graphics target driver.
 */

// Including global configuration
#include "../rhea_config.h"

// Including necessary headers
#include "gfx_config.h"
#include "gfx_impl.h"
#include "gfx.h"

// Implementation for SSD1306 graphics target
#if defined(RHEA_GFX_TARGET_SSD1306)

    // Defining display resolution
    #if     defined(RHEA_GFX_RESOLUTION_128X64) 
        #define SSD1306_128X64
    #elif   defined(RHEA_GFX_RESOLUTION_128X32) 
        #define SSD1306_128X32
    #elif   defined(RHEA_GFX_RESOLUTION_96X16)  
        #define SSD1306_96X16
    #endif

    // Including SSD1306 driver
    #include "../drivers/SSD1306/SSD1306.h"

    // Including I2C driver
    #include "../i2c/i2c.h"

    void rhea_gfx_initialize_impl(void) {

        // Initializing I2C controller structure
        SSD1306_I2CControllerStruct controller = {
            .MasterSendStart = rhea_i2c_MasterSendStart,
            .MasterSendStop  = rhea_i2c_MasterSendStop,
            .MasterWriteByte = rhea_i2c_MasterWriteByte
        };

        // Installing I2C controller to the driver
        SSD1306_SetI2CController(controller);

        // Initializing driver
        uint8_t status = RHEA_ENTER_CRITICAL_SECTION();
            SSD1306_Init();
        RHEA_EXIT_CRITICAL_SECTION(status);
    }

    void rhea_gfx_reset_impl(void) {

        // Resetting driver
        uint8_t status = RHEA_ENTER_CRITICAL_SECTION();
            SSD1306_Reset();
        RHEA_EXIT_CRITICAL_SECTION(status);
    }

    void rhea_gfx_clear_impl(void) {

        // Clearing driver
        SSD1306_ClearDisplay();
    }

    void rhea_gfx_refresh_impl(void) {

        // Refreshing display
        uint8_t status = RHEA_ENTER_CRITICAL_SECTION();
            SSD1306_RefreshDisplay();
        RHEA_EXIT_CRITICAL_SECTION(status);
        
    }

    void rhea_gfx_writePixel_impl(rhea_gfx_coordinate x, rhea_gfx_coordinate y, rhea_gfx_color color) {

        // Writing pixel to the display buffer
        SSD1306_WritePixel(x, y, color);
    }

#endif
    
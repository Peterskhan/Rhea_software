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
 * @file    i2c_impl.c
 * @author  Peter Gyulai
 * @version 1.0.0
 * @date    2020.04.19
 * @brief   I2C driver implementation.
 * @details
 * This file contains the I2C driver implementation. Implement the driver 
 * functionality here when porting to a new target microcontroller.
 */

// Including global configuration
#include "../rhea_config.h"

// Including header for function declarations
#include "i2c_impl.h"

// Implementation for PSoC5LP target
#if defined(RHEA_TARGET_PSOC5LP)

    // Including generated source
    #include "project.h"

    void rhea_i2c_initialize_impl(void) {

        // Invoking PSoC driver
        I2C_Start();
    }

    void rhea_i2c_masterSendStart_impl(uint8_t address, uint8_t read) {

        // Invoking PSoC driver
        I2C_MasterSendStart(address, read);
    }

    void rhea_i2c_masterSendStop_impl(void) {

        // Invoking PSoC driver
        I2C_MasterSendStop();
    }

    uint8_t rhea_i2c_masterReadByte_impl(uint8_t ack) {

        // Invoking PSoC driver
        return I2C_MasterReadByte(ack);
    }

    void rhea_i2c_masterWriteByte_impl(uint8_t byte) {

        // Invoking PSoC driver
        I2C_MasterWriteByte(byte);
    }

// Implementation for ESP32 target
#elif defined(RHEA_TARGET_ESP32)

    #error ESP32: I2C driver functions undefined!

#endif

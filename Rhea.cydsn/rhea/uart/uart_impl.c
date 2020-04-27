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
 * @file    uart_impl.c
 * @author  Peter Gyulai
 * @version 1.0.0
 * @date    2020.04.20
 * @brief   UART driver implementation.
 * @details
 * This file contains the UART driver implementation. Implement the driver 
 * functionality here when porting to a new target microcontroller.
 */

// Including global configuration
#include "../rhea_config.h"

// Including necessary headers
#include "uart_impl.h"


// Implementation for PSoC5LP target
#if defined(RHEA_TARGET_PSOC5LP)

    // Including generated source
    #include "project.h"
    
    void rhea_uart_initialize_impl(void) {
        UART_Start();
    }
    
    uint64_t rhea_uart_bytesAvailable_impl(void) {
        return UART_GetRxBufferSize();   
    }

    uint8_t rhea_uart_readByte_impl(void) {
        return UART_GetChar();
    }

    void rhea_uart_writeByte_impl(uint8_t byte) {
        UART_PutChar(byte);
    }

#elif defined(RHEA_TARGET_ESP32)
    
    #error ESP32 UART implementation undefined.

#endif
    
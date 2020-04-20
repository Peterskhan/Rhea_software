#pragma once
#ifndef RHEA_UART_IMPL_H_INCLUDED
#define RHEA_UART_IMPL_H_INCLUDED

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
 * @file    uart_impl.h
 * @author  Peter Gyulai
 * @version 1.0.0
 * @date    2020.04.20
 * @brief   UART driver declarations.
 * @details
 * This file contains the UART driver interface functions that must be
 * implemented when interfacing with a new target microcontroller.
 */
    
// Standard includes
#include <stdint.h>
    
    
/**
 * @brief Initializes the UART driver.
 * @todo  Implement this function to initialize the UART driver.
 */
void rhea_uart_initialize_impl(void);

/**
 * @brief Reads one byte from the UART.
 * @returns The byte read from the UART.
 * @todo Implement this function to read one byte from the UART.
 */
uint8_t rhea_uart_readByte_impl(void);

/**
 * @brief Writes one byte to the UART.
 * @param [in] byte The byte to write to the UART.
 * @todo  Implement this function to write one byte to the UART.
 */
void rhea_uart_writeByte_impl(uint8_t byte);

#endif // RHEA_UART_IMPL_H_INCLUDED
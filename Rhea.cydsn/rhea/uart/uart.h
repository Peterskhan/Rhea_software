#pragma once
#ifndef RHEA_UART_H_INCLUDED
#define RHEA_UART_H_INCLUDED

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
 * @file    uart.h
 * @author  Peter Gyulai
 * @version 1.0.0
 * @date    2020.04.20
 * @brief   UART utilities.
 * @details
 * This file contains the Rhea UART utility functions. 
 */

// Standard includes
#include <stdint.h>

  
/**
 * @brief Initializes the UART library.
 */
void rhea_uart_Initialize(void);
    
/**
 * @brief Reads one byte of data from the UART.
 * @returns The byte read from the UART.
 */
uint8_t rhea_uart_ReadByte(void);

/**
 * @brief Reads the specified number of bytes from the UART.
 * @param [out] bytes The array to store the bytes read.
 * @param [in] count The number of bytes to read.
 */
void rhea_uart_ReadBytes(uint8_t *bytes, uint64_t count);

/**
 * @brief Alias for #rhea_uart_ReadBytes().
 */
void rhea_uart_ReadBuffer(uint8_t *buffer, uint64_t size);

/**
 * @brief Alisas for #rhea_uart_ReadByte().
 */
char rhea_uart_ReadChar(void);

/**
 * @brief Reads a null-terminated string from the UART.
 */
void rhea_uart_ReadString(char *string);

/**
 * @brief Writes one byte of data to the UART.
 * @param [in] byte The byte to write.
 */
void rhea_uart_WriteByte(uint8_t byte);

/**
 * @brief Writes the specified number of bytes from the buffer.
 * @param [in] bytes Pointer to the buffer to write from.
 * @param [in] count The number of bytes to write.
 */
void rhea_uart_WriteBytes(const uint8_t *bytes, uint64_t count);

/** 
 * @brief Alias for #rhea_uart_WriteBytes(). 
 */
void rhea_uart_WriteBuffer(const uint8_t *buffer, uint64_t size);

/**
 * @brief Alias for #rhea_uart_writeByte().
 */
void rhea_uart_WriteChar(char c);

/**
 * @brief Writes a null-terminated string to the UART.
 * @param [in] string A null-terminated string to write.
 */
void rhea_uart_WriteString(const char *string);
    
#endif // RHEA_UART_H_INCLUDED
    
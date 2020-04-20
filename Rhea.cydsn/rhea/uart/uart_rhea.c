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
 * @file    uart_rhea.c
 * @author  Peter Gyulai
 * @version 1.0.0
 * @date    2020.04.20
 * @brief   UART library implementation.
 * @details
 * This file contains the function definitions used by the Rhea UART library.
 */

// Project includes
#include "uart.h"
#include "uart_impl.h"


void rhea_uart_Initialize(void) {
    
    // Invoking driver implementation
    rhea_uart_initialize_impl();
}
    
uint8_t rhea_uart_ReadByte(void) {
    
    // Invoking driver implementation
    return rhea_uart_readByte_impl();
}

void rhea_uart_ReadBytes(uint8_t *bytes, uint64_t count) {
    for(uint64_t i = 0; i < count; i++) {
        bytes[i] = rhea_uart_ReadByte();   
    }
}

void rhea_uart_ReadBuffer(uint8_t *buffer, uint64_t size) {
    rhea_uart_ReadBytes(buffer, size);
}

char rhea_uart_ReadChar(void) {
    return rhea_uart_ReadByte();
}

void rhea_uart_ReadString(char *string) {
    char c = rhea_uart_ReadChar();
    while(c != '\0') {
        *(string++) = c;
        c = rhea_uart_ReadChar();
    }
    *string = '\0';
}

void rhea_uart_WriteByte(uint8_t byte) {
    
    // Invoking driver implementation
    rhea_uart_writeByte_impl(byte);
}

void rhea_uart_WriteBytes(const uint8_t *bytes, uint64_t count) {
    for(uint64_t i = 0; i < count; i++) {
        rhea_uart_WriteByte(bytes[i]);
    }
}

void rhea_uart_WriteBuffer(const uint8_t *buffer, uint64_t size) {
    rhea_uart_WriteBytes(buffer, size);
}

void rhea_uart_WriteChar(char c) {
    rhea_uart_WriteByte(c);
}

void rhea_uart_WriteString(const char *string) {
    while(*string != '\0') {
        rhea_uart_WriteChar(*string++);   
    }
    rhea_uart_WriteChar('\0');
}

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
 * @file    command.c
 * @author  Peter Gyulai
 * @version 1.0.0
 * @date    2020.04.21
 * @brief   Serial command line parser implementations.
 * @details
 * This file contains the implementation for the serial command line parser.
 */

// Project includes
#include "../../rhea/uart/uart.h"
#include "command.h"


// Defines the size of the receive buffer
#define SERIAL_RX_BUFFER_SIZE (256)

// External serial status indicator flag 
volatile uint8_t serial_data_ready = 0;

// Serial RX buffer
uint8_t serialBuffer[SERIAL_RX_BUFFER_SIZE];
    
void InitializeSerialCommandLine(void) {
    
    // Initializing and enabling the serial interrupt
    UART_RX_INTR_StartEx(SERIAL_DATA_ARRIVED);
}

void processCommand(const char *buffer, uint64_t length) {
    
}

void ProcessCommandLine(void) {
    
    // Checking serial status flag
    if(!serial_data_ready) return;
    
    // Clearing serial status flag
    serial_data_ready = 0;
    
    // Reading the number of bytes available
    uint64_t bytesAvailable = rhea_uart_BytesAvailable();
    
    // Serial RX buffer current write index
    static uint64_t currentIndex = 0;
    
    // Serial RX buffer current read index
    static uint64_t currentReadIndex = 0;
    
    // Reading bytes
    for(uint64_t i = 0; i < bytesAvailable; i++) {
        
        // Reading next character
        uint8_t nextChar = rhea_uart_ReadByte();
        
        // Checking command termination
        if(nextChar == '\n') {
            
            // Processing command
            processCommand(serialBuffer, currentIndex);
            
            // Resetting buffer index
            currentIndex = 0;
        } 
        else {
            
            // Storing next character
            serialBuffer[currentIndex = (currentIndex + 1) % SERIAL_RX_BUFFER_SIZE] = nextChar;
        }
    }
}

CY_ISR_PROTO(SERIAL_DATA_ARRIVED) {
    serial_data_ready = 1;   
}

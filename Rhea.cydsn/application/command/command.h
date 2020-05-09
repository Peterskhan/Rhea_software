#pragma once
#ifndef APPLICATION_COMMAND_H_INCLUDED
#define APPLICATION_COMMAND_H_INCLUDED

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
 * @file    command.h
 * @author  Peter Gyulai
 * @version 1.0.0
 * @date    2020.04.21
 * @brief   Serial command line interfaces.
 * @details
 * This file contains the initializers and handlers for the 
 * serial port command line utility.
 */

// Project includes
#include "project.h"

  
// Ring buffer type for receiving bytes on UART
typedef struct ringbuffer_t {
    uint8_t data[256];
    uint8_t head;
    uint8_t tail;
} ringbuffer_t;

// External button status indicator flags 
extern volatile uint8_t serial_data_ready;

/**
 * @brief Puts one byte into the specified buffer.
 * @param [in] Pointer to the ringbuffer.
 * @param [in] The byte to put into the buffer.
 */
void ringbufferPutChar(volatile ringbuffer_t *buffer, uint8_t c);

/**
 * @brief   Gets one byte from the specified buffer.
 * @param   [in] Pointer to the ringbuffer.
 * @returns The byte from the ringbuffer.
 */
uint8_t ringbufferGetChar(volatile ringbuffer_t *buffer);

/**
 * @brief Initializes the serial port command line utility.
 */
void InitializeSerialCommandLine(void);

/**
 * @brief Processes input from the serial command line.
 */
void ProcessCommandLine(void);

/**
 * @brief Interrupt handler for serial data arriving.
 */
CY_ISR_PROTO(SERIAL_DATA_ARRIVED);
    
#endif // APPLICATION_COMMAND_H_INCLUDED

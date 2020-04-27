#pragma once
#ifndef APPLICATION_INPUT_H_INCLUDED
#define APPLICATION_INPUT_H_INCLUDED

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
 * @file    input.h
 * @author  Peter Gyulai
 * @version 1.0.0
 * @date    2020.04.21
 * @brief   Input button handling functions and ISRs.
 * @details
 * This file contains the initializers and interrupt service routines
 * that handle input button interrupts.
 */

// Project includes
#include "project.h"


// External button status indicator flags 
extern volatile uint8_t button_enter_pressed;
extern volatile uint8_t button_right_pressed;
extern volatile uint8_t button_left_pressed;
    
/**
 * @brief Initializes and enables the input button handler interrupts.
 */
void InitializeInputButtonInterrupts(void);

/**
 * @brief Interrupt handler for the ENTER button.
 */
CY_ISR_PROTO(BTN_ENTER_ISR);

/**
 * @brief Interrupt handler for the RIGHT button.
 */
CY_ISR_PROTO(BTN_RIGHT_ISR);

/**
 * @brief Interrupt handler for the LEFT button.
 */
CY_ISR_PROTO(BTN_LEFT_ISR);

#endif // APPLICATION_INPUT_H_INCLUDED
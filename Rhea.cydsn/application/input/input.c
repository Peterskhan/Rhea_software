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
 * @file    input.c
 * @author  Peter Gyulai
 * @version 1.0.0
 * @date    2020.04.21
 * @brief   Button input handler implementations.
 * @details
 * This file contains the implementation for the input button interrupt handlers.
 */

// Project includes
#include "input.h"


// Button press indicators
volatile uint8_t button_enter_pressed = 0;
volatile uint8_t button_right_pressed = 0;
volatile uint8_t button_left_pressed = 0;

void InitializeInputButtonInterrupts(void) {
    
    // Initializing and starting handlers
    BTN_ENTER_INTR_StartEx(BTN_ENTER_ISR);
    BTN_RIGHT_INTR_StartEx(BTN_RIGHT_ISR);
    BTN_LEFT_INTR_StartEx(BTN_LEFT_ISR);
}

CY_ISR(BTN_ENTER_ISR) {
    button_enter_pressed = 1;
}

CY_ISR(BTN_RIGHT_ISR) {
    button_right_pressed = 1;
}

CY_ISR(BTN_LEFT_ISR) {
    button_left_pressed = 1;
}
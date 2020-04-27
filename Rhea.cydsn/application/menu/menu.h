#pragma once
#ifndef APPLICATION_MENU_H_INCLUDED
#define APPLICATION_MENU_H_INCLUDED

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
 * @file    menu.h
 * @author  Peter Gyulai
 * @version 1.0.0
 * @date    2020.04.21
 * @brief   Application main menu declaration.
 * @details
 * This file contains the initializers for the application main menu.
 */
    
// Standard includes
#include <stdint.h>
    

/**
 * @brief Initializes the application main menu.
 */
void InitializeMainMenu(void);

/**
 * @brief Steps the application main menu based on the input
 *        button status.
 */
void StepMainMenuStateMachine(volatile uint8_t *button_enter_pressed,
                              volatile uint8_t *button_right_pressed,
                              volatile uint8_t *button_left_pressed);
    
#endif // APPLICATION_MENU_H_INCLUDED

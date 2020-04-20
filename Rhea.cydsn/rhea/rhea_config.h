#pragma once
#ifndef RHEA_CONFIG_H_INCLUDED
#define RHEA_CONFIG_H_INCLUDED

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
 * @file    rhea_config.h
 * @author  Peter Gyulai
 * @version 1.0.0
 * @date    2020.04.20
 * @brief   Generic Rhea configuration.
 * @details
 * This file contains the generic Rhea configuration options.
 */
   
/** @{ @name    Target microcontroller selection
 *     @details Select the target microcontroller by uncommenting 
 *              the corresponding macro. Leave all other macros
 *              commented.
 */
    
/** @brief Defines the PSoC-5LP as the target microcontroller. */
#define RHEA_TARGET_PSOC5LP
    
/** @brief Defines the ESP32 as the target microcontroller. */
// #define RHEA_TARGET_ESP32
    
/** @} */
    
#endif // RHEA_CONFIG_H_INCLUDED
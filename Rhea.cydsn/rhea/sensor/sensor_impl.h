#pragma once
#ifndef RHEA_SENSOR_IMPL_H_INCLUDED
#define RHEA_SENSOR_IMPL_H_INCLUDED

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
 * @file    sensor_impl.h
 * @author  Peter Gyulai
 * @version 1.0.0
 * @date    2020.04.19
 * @brief   Sensor interface declarations.
 * @details
 * This file contains the sensor interface functions that must be
 * implemented when interfacing with a new target microcontroller.
 */
    
// Project includes
#include "sensor_config.h"
    
    
// External necessary function declarations 
extern void rhea_sensor_periodicMeasure(void);
    
/**
 * @brief Initializes the sensor library.
 * @todo  Implement this function to initialize the sensor library.
 * @todo  Enable and attach a 1 milliseconds periodic interrupt source
 *        that invokes #rhea_sensor_periodicMeasure().
 */
void rhea_sensor_initialize_impl();
    
#endif // RHEA_SENSOR_IMPL_H_INCLUDED
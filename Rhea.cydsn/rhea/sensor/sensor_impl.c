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
 * @file    sensor_impl.c
 * @author  Peter Gyulai
 * @version 1.0.0
 * @date    2020.04.19
 * @brief   Sensor interface implementation.
 * @details
 * This file contains the sensor interface implementation. Implement the 
 * interface functionality here when porting to a new target microcontroller.
 */

// Including global configuration
#include "../rhea_config.h"

// Including necessary headers
#include "sensor_config.h"
#include "sensor_impl.h"

// Target specific includes
#if defined(RHEA_TARGET_PSOC5LP)
    
    // Including generated source
    #include "project.h"
    
#elif defined(RHEA_TARGET_ESP32)
    
#endif

// Optional sensor interface includes
#if RHEA_SENSOR_ADD_BME280
    
    // Include BME280 driver interface
    #include "interfaces/BME280/BME280_INTF.h"
    
#endif

void rhea_sensor_initialize_impl(void) {
    
    // Implementation for PSoC5LP target
    #if defined(RHEA_TARGET_PSOC5LP)
        
        // Enabling sensor timer
        SENSOR_TIMER_Start();
        
        // Enabling periodic sensor interrupt
        SENSOR_1MS_StartEx(rhea_sensor_periodicMeasure);
        
    // Implementation for ESP32 target
    #elif defined(RHEA_TARGET_ESP32) 
        
        #error ESP32 sensor library not initialized!
        
    #endif
    
    // Optionally add BME280 to the defult configuration
    #if RHEA_SENSOR_ADD_BME280
        
        // Adding sensor interface
        bme280_addInterface();
        
    #endif
}
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
 * @file    sensor.c
 * @author  Peter Gyulai
 * @version 1.0.0
 * @date    2020.04.20
 * @brief   Sensor library implementation.
 * @details
 * This file contains the function definitions used by the Rhea SENSOR library.
 */

 // Doxygen documentation duplication suppression
#ifndef DOXYGEN_SHOULD_SKIP_THIS
    
// Standard includes
#include <string.h>

// Project includes
#include "sensor.h"
#include "sensor_impl.h"
    

// Static array containing measurements
static struct rhea_sensor_measurementDescriptor measurementRegistry[RHEA_SENSOR_MEASUREMENT_LIMIT];

// Static counter for counting the number of measurements
static uint64_t measurementCount = 0;
    
// Static array containing attributes
static struct rhea_sensor_attributeDescriptor attributeRegistry[RHEA_SENSOR_ATTRIBUTE_LIMIT];

// Static counter for counting the number of attributes
static uint64_t attributeCount = 0;
    
void rhea_sensor_Initialize(void) {
    
    // Invoking implementation
    rhea_sensor_initialize_impl();
    
    // Initializing attribute and measurement counters
    attributeCount = 0;
    measurementCount = 0;
}

void rhea_sensor_AddMeasurement(const char *device, 
                                const char *parameter, 
                                uint64_t    period,
                                rhea_sensor_measurementFunction function) 
{
    measurementRegistry[measurementCount++] = (struct rhea_sensor_measurementDescriptor) {
        .device = device,
        .parameter = parameter,
        .period = period,
        .currentPeriod = 0,
        .lastMeasurement = (RHEA_SENSOR_MEASUREMENT_TYPE)(0),
        .measurementFunction = function
    };
}

void rhea_sensor_TakeMeasurement(const char *device,
                                 const char *parameter)
{
    for(uint64_t i = 0; i < measurementCount; i++) {
        if(strcmp(measurementRegistry[i].device, device) == 0 &&
           strcmp(measurementRegistry[i].parameter, parameter) == 0)
        {
            measurementRegistry[i].lastMeasurement = measurementRegistry[i].measurementFunction();
            measurementRegistry[i].currentPeriod = 0;
            return;
        }
    }
}

RHEA_SENSOR_MEASUREMENT_TYPE rhea_sensor_GetMeasurement(const char *device,
                                                        const char *parameter) 
{
    for(uint64_t i = 0; i < measurementCount; i++) {
        if(strcmp(measurementRegistry[i].device, device) == 0 &&
           strcmp(measurementRegistry[i].parameter, parameter) == 0)
        {
            return measurementRegistry[i].lastMeasurement;
        }
    }
    
    return (RHEA_SENSOR_MEASUREMENT_TYPE)(0);
}

uint64_t rhea_sensor_GetMeasurementPeriod(const char *device,
                                      const char *parameter)
{
    for(uint64_t i = 0; i < measurementCount; i++) {
        if(strcmp(measurementRegistry[i].device, device) == 0 &&
           strcmp(measurementRegistry[i].parameter, parameter) == 0)
        {
            return measurementRegistry[i].period;
        }
    }
    
    return 0;
}

void rhea_sensor_SetMeasurementPeriod(const char *device,
                                      const char *parameter,
                                      uint64_t    period)
{
    for(uint64_t i = 0; i < measurementCount; i++) {
        if(strcmp(measurementRegistry[i].device, device) == 0 &&
           strcmp(measurementRegistry[i].parameter, parameter) == 0)
        {
            measurementRegistry[i].period = period;
            return;
        }
    }
}

void rhea_sensor_AddAttribute(const char *device, 
                              const char *attribute, 
                              rhea_sensor_attributeGetter getter,
                              rhea_sensor_attributeSetter setter)
{
    attributeRegistry[attributeCount++] = (struct rhea_sensor_attributeDescriptor) {
        .device = device,
        .attributeName = attribute,
        .attributeValue = (RHEA_SENSOR_ATTRIBUTE_TYPE)(0),
        .getterFunction = getter,
        .setterFunction = setter
    };
}

RHEA_SENSOR_ATTRIBUTE_TYPE rhea_sensor_GetAttribute(const char *device,
                                                    const char *attribute) 
{
    for(uint64_t i = 0; i < attributeCount; i++) {
        if(strcmp(attributeRegistry[i].device, device) == 0 &&
           strcmp(attributeRegistry[i].attributeName, attribute) == 0)
        {
            if(attributeRegistry[i].getterFunction) {
                attributeRegistry[i].attributeValue = attributeRegistry[i].getterFunction();    
            }
            
            return attributeRegistry[i].attributeValue;
        }
    }
    
    return (RHEA_SENSOR_ATTRIBUTE_TYPE)(0);
}

void rhea_sensor_SetAttribute(const char *device,
                              const char *attribute,
                              RHEA_SENSOR_ATTRIBUTE_TYPE value) 
{
    for(uint64_t i = 0; i < attributeCount; i++) {
        if(strcmp(attributeRegistry[i].device, device) == 0 &&
           strcmp(attributeRegistry[i].attributeName, attribute) == 0)
        {
            attributeRegistry[i].attributeValue = value;
            
            if(attributeRegistry[i].setterFunction) {
                attributeRegistry[i].setterFunction(value);
            }
            
            return;
        }
    }
}

void rhea_sensor_periodicMeasure(void) {
    for(uint64_t i = 0; i < measurementCount; i++) {
        if(++measurementRegistry[i].currentPeriod == measurementRegistry[i].period) {
            measurementRegistry[i].lastMeasurement = measurementRegistry[i].measurementFunction();
            measurementRegistry[i].currentPeriod = 0;
        }
    }
}
    
    
#endif // DOXYGEN_SHOULD_SKIP_THIS
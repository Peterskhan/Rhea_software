#pragma once
#ifndef RHEA_SENSOR_BME280_INTF_H_INCLUDED
#define RHEA_SENSOR_BME280_INTF_H_INCLUDED

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
 * @file    BME280_INTF.h
 * @author  Peter Gyulai
 * @version 1.0.0
 * @date    2020.04.20
 * @brief   BME280 Rhea sensor interface.
 * @details
 * This file contains the Rhea sensor interface of the BME280 driver.
 */

// Project includes
#include "../../../drivers/BME280/BME280.h"
#include "../../sensor.h"


// Interface registering
void bme280_addInterface(void);

// Measurements
RHEA_SENSOR_MEASUREMENT_TYPE bme280_GetTemperatureCelsius(void);
RHEA_SENSOR_MEASUREMENT_TYPE bme280_GetPressure(void);
RHEA_SENSOR_MEASUREMENT_TYPE bme280_GetHumidity(void);

// Attributes
void bme280_SetFilterMode(RHEA_SENSOR_ATTRIBUTE_TYPE value);
RHEA_SENSOR_ATTRIBUTE_TYPE bme280_GetFilterMode(void);
void bme280_SetTemperatureMode(RHEA_SENSOR_ATTRIBUTE_TYPE value);
RHEA_SENSOR_ATTRIBUTE_TYPE bme280_GetTemperatureMode(void);
void bme280_SetPressureMode(RHEA_SENSOR_ATTRIBUTE_TYPE value);
RHEA_SENSOR_ATTRIBUTE_TYPE bme280_GetPressureMode(void);
void bme280_SetHumidityMode(RHEA_SENSOR_ATTRIBUTE_TYPE value);
RHEA_SENSOR_ATTRIBUTE_TYPE bme280_GetHumidityMode(void);
void bme280_SetMeasurementMode(RHEA_SENSOR_ATTRIBUTE_TYPE value);
RHEA_SENSOR_ATTRIBUTE_TYPE bme280_GetMeasurementMode(void);

#endif // RHEA_SENSOR_BME280_INTF_H_INCLUDED

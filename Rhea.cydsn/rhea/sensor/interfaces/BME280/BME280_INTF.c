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
 * @file    BME280_INTF.c
 * @author  Peter Gyulai
 * @version 1.0.0
 * @date    2020.04.19
 * @brief   BME280 Rhea interface implementation.
 * @details
 * This file contains the BME280 Rhea sensor interface implementation.
 */

// Project includes
#include "../../../i2c/i2c.h"
#include "BME280_INTF.h"


void bme280_addInterface(void) {
    
    // Setting up BME280 measurement callbacks
    rhea_sensor_AddMeasurement("BME280", "temperature", 0, bme280_GetTemperatureCelsius);
    rhea_sensor_AddMeasurement("BME280", "pressure",    0, bme280_GetPressure);
    rhea_sensor_AddMeasurement("BME280", "humidity",    0, bme280_GetHumidity);
    
    // Setting up BME280 attribute getter & setter callbacks
    rhea_sensor_AddAttribute("BME280", "filter",            bme280_GetFilterMode,      bme280_SetFilterMode);
    rhea_sensor_AddAttribute("BME280", "temperatureOVRS",   bme280_GetTemperatureMode, bme280_SetTemperatureMode);
    rhea_sensor_AddAttribute("BME280", "pressureOVRS",      bme280_GetPressureMode,    bme280_SetPressureMode);
    rhea_sensor_AddAttribute("BME280", "humidityOVRS",      bme280_GetHumidityMode,    bme280_SetHumidityMode);
    rhea_sensor_AddAttribute("BME280", "mode",              bme280_GetMeasurementMode, bme280_SetMeasurementMode);
        
    // Function pointers for I2C driver
    BME280_I2CControllerStruct cntr = {
        rhea_i2c_MasterSendStart,
        rhea_i2c_MasterSendStop,
        rhea_i2c_MasterWriteByte,
        rhea_i2c_MasterReadByte
    };
    
    // Initializing the BME280
    BME280_SetI2CController(cntr);
    BME280_Init();
    
    // Setting measurement parameters for the BME280
    rhea_sensor_SetAttribute("BME280", "filter",          BME280_FILTER_OFF);
    rhea_sensor_SetAttribute("BME280", "temperatureOVRS", BME280_TEMPERATURE_OVERSAMPLING_1X);
    rhea_sensor_SetAttribute("BME280", "pressureOVRS",    BME280_PRESSURE_OVERSAMPLING_1X);
    rhea_sensor_SetAttribute("BME280", "humidityOVRS",    BME280_HUMIDITY_OVERSAMPLING_1X);
    rhea_sensor_SetAttribute("BME280", "mode",            BME280_MODE_FORCED);
}

RHEA_SENSOR_MEASUREMENT_TYPE bme280_GetTemperatureCelsius(void) {
    
    // Reading measurement
    RHEA_SENSOR_MEASUREMENT_TYPE result = BME280_GetTemperatureCelsius(1);
    
    // Starting next measurement
    BME280_SetMeasurementMode(BME280_MODE_FORCED);
    
    return result;
}

RHEA_SENSOR_MEASUREMENT_TYPE bme280_GetPressure(void) {
    
    // Reading measurement
    RHEA_SENSOR_MEASUREMENT_TYPE result = BME280_GetPressure(1);
    
    // Starting next measurement
    BME280_SetMeasurementMode(BME280_MODE_FORCED);
    
    return result;
}

RHEA_SENSOR_MEASUREMENT_TYPE bme280_GetHumidity(void) {
    
    // Reading measurement
    RHEA_SENSOR_MEASUREMENT_TYPE result = BME280_GetHumidity(1);
    
    // Starting next measurement
    BME280_SetMeasurementMode(BME280_MODE_FORCED);
    
    return result;
}

void bme280_SetFilterMode(RHEA_SENSOR_ATTRIBUTE_TYPE value) {
    BME280_SetFilterMode(value);
}

RHEA_SENSOR_ATTRIBUTE_TYPE bme280_GetFilterMode(void) {
    return BME280_GetFilterMode();
}

void bme280_SetTemperatureMode(RHEA_SENSOR_ATTRIBUTE_TYPE value) {
    BME280_SetTemperatureMode(value);
}

RHEA_SENSOR_ATTRIBUTE_TYPE bme280_GetTemperatureMode(void) {
    return BME280_GetTemperatureMode();
}

void bme280_SetPressureMode(RHEA_SENSOR_ATTRIBUTE_TYPE value) {
    BME280_SetPressureMode(value);
}

RHEA_SENSOR_ATTRIBUTE_TYPE bme280_GetPressureMode(void) {
    return BME280_GetPressureMode();
}

void bme280_SetHumidityMode(RHEA_SENSOR_ATTRIBUTE_TYPE value) {
    BME280_SetHumidityMode(value);
}

RHEA_SENSOR_ATTRIBUTE_TYPE bme280_GetHumidityMode(void) {
    return BME280_GetHumidityMode();
}

void bme280_SetMeasurementMode(RHEA_SENSOR_ATTRIBUTE_TYPE value) {
    BME280_SetMeasurementMode(value);
}

RHEA_SENSOR_ATTRIBUTE_TYPE bme280_GetMeasurementMode(void) {
    return BME280_GetMeasurementMode();
}
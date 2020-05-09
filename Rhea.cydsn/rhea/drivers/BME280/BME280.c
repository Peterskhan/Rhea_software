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
 * @file    BME280.c
 * @author  Peter Gyulai
 * @version 1.1.0
 * @date    2020.04.14
 * @brief   Library implementation.
 * @details
 * This file contains the function definitions and static variable definitions used
 * by the BME280 driver library.
 */

// Doxygen documentation duplication suppression
#ifndef DOXYGEN_SHOULD_SKIP_THIS

// Project includes
#include "BME280.h"


// // Structure holding function pointers to I2C handlers
static BME280_I2CControllerStruct BME280_I2CController;

// Static instance holding a local copy of the BME280's registers
static BME280_RegisterStruct BME280_RegistersLocal;

void BME280_SetI2CController(BME280_I2CControllerStruct controller) {
	BME280_I2CController = controller;
}

void BME280_I2CReader(uint8_t address, uint8_t deviceAddress, unsigned char * buffer, uint8_t byteCount) {
    
    // Selecting the device for write
    BME280_I2CController.MasterSendStart(address, 0);
    
    // Writing first device address to read
    BME280_I2CController.MasterWriteByte(deviceAddress);

    // Sending STOP 
    BME280_I2CController.MasterSendStop();
    
    // Selecting the device for read
    BME280_I2CController.MasterSendStart(address, 1);
    
    // Reading bytes from the device
    for(uint8_t i = 0; i < byteCount; i++) {
        buffer[i] = BME280_I2CController.MasterReadByte(i < byteCount - 1 ? 1 : 0);   
    }
    
    // Sending STOP 
    BME280_I2CController.MasterSendStop();
}

void BME280_I2CWriter(uint8_t address, uint8_t deviceAddress, const unsigned char * buffer, uint8_t byteCount) {
    
    // Selecting the device for write
    BME280_I2CController.MasterSendStart(address, 0);
    
    // Writing bytes to the device
    for(uint8_t i = 0; i < byteCount; i++) {
        
        // Sending device address to write
        BME280_I2CController.MasterWriteByte(deviceAddress++);
        
        // Sending byte to write
        BME280_I2CController.MasterWriteByte(buffer[i]);
    }
    
    // Sending STOP 
    BME280_I2CController.MasterSendStop();
}
    
void BME280_Init(void) {

    // Reading & validating chip ID
    uint8_t ID = 0x00;
    BME280_I2CReader(BME280_I2C_ADDR, BME280_ID, &ID, 1);
        // Do assertion: ID == BME280_CHIP_ID
    
    // Reading calibration data
    uint8_t calibDataLow[BME280_CALIBRATION_REGS_LOW_COUNT];
    uint8_t calibDataHigh[BME280_CALIBRATION_REGS_HIGH_COUNT];
    BME280_I2CReader(BME280_I2C_ADDR, BME280_CALIBRATION_REGS_LOW, calibDataLow, BME280_CALIBRATION_REGS_LOW_COUNT);
    BME280_I2CReader(BME280_I2C_ADDR, BME280_CALIBRATION_REGS_HIGH, calibDataHigh, BME280_CALIBRATION_REGS_HIGH_COUNT);

    // Setting temperature compensation parameters
    BME280_RegistersLocal.dig_T1 = (uint16_t) calibDataLow[0]  | (uint16_t) calibDataLow[1] << 8;
    BME280_RegistersLocal.dig_T2 = (int16_t)  calibDataLow[2]  | (int16_t)  calibDataLow[3] << 8;
    BME280_RegistersLocal.dig_T3 = (int16_t)  calibDataLow[4]  | (int16_t)  calibDataLow[5] << 8;

    // Setting pressure compensation parameters
    BME280_RegistersLocal.dig_P1 = (uint16_t) calibDataLow[6]  | (uint16_t) calibDataLow[7] << 8;
    BME280_RegistersLocal.dig_P2 = (int16_t)  calibDataLow[8]  | (int16_t)  calibDataLow[9] << 8;
    BME280_RegistersLocal.dig_P3 = (int16_t)  calibDataLow[10] | (int16_t)  calibDataLow[11] << 8;
    BME280_RegistersLocal.dig_P4 = (int16_t)  calibDataLow[12] | (int16_t)  calibDataLow[13] << 8;
    BME280_RegistersLocal.dig_P5 = (int16_t)  calibDataLow[14] | (int16_t)  calibDataLow[15] << 8;
    BME280_RegistersLocal.dig_P6 = (int16_t)  calibDataLow[16] | (int16_t)  calibDataLow[17] << 8;
    BME280_RegistersLocal.dig_P7 = (int16_t)  calibDataLow[18] | (int16_t)  calibDataLow[19] << 8;
    BME280_RegistersLocal.dig_P8 = (int16_t)  calibDataLow[20] | (int16_t)  calibDataLow[21] << 8;
    BME280_RegistersLocal.dig_P9 = (int16_t)  calibDataLow[22] | (int16_t)  calibDataLow[23] << 8;

    // Setting humidity compensation parameters
    BME280_RegistersLocal.dig_H1 = (uint8_t)  calibDataLow[25];
    BME280_RegistersLocal.dig_H2 = (int16_t)  calibDataHigh[0]         | (int16_t) calibDataHigh[1] << 8;
    BME280_RegistersLocal.dig_H3 = (uint8_t)  calibDataHigh[2];
    BME280_RegistersLocal.dig_H4 = (int16_t) (calibDataHigh[4] | 0x0F) | (int16_t) calibDataHigh[3] << 4; 
    BME280_RegistersLocal.dig_H5 = (int16_t) (calibDataHigh[4] | 0xF0) | (int16_t) calibDataHigh[5] << 4; 
    BME280_RegistersLocal.dig_H6 = (int8_t)   calibDataHigh[6];

    // Performing software reset
    BME280_Reset();
}

void BME280_Reset(void) {

    // Writing reset word to RESET register
    const uint8_t resetWord = BME280_RESET_WORD;
    BME280_I2CWriter(BME280_I2C_ADDR, BME280_RESET, &resetWord, 1);
}

void BME280_ReadRegisters(void) {

    // Reading measurement registers [F7-FE]
    BME280_I2CReader(BME280_I2C_ADDR, BME280_PRESS_MSB, (uint8_t*) &BME280_RegistersLocal.PRESS_MSB, 1 + BME280_HUM_LSB - BME280_PRESS_MSB);

    // Reading configuration registers [F2-F5]
    BME280_I2CReader(BME280_I2C_ADDR, BME280_CTRL_HUM, (uint8_t*) &BME280_RegistersLocal.CTRL_HUM, 1 + BME280_CONFIG - BME280_CTRL_HUM);
}

void BME280_WriteRegisters(void) {

    // Writing configuration registers [F2-F5]
    BME280_I2CWriter(BME280_I2C_ADDR, BME280_CTRL_HUM, (const uint8_t*) &BME280_RegistersLocal.CTRL_HUM, 1 + BME280_CONFIG - BME280_CTRL_HUM);
}

BME280_RegisterStruct* BME280_GetLocalRegisters(void) {
    return &BME280_RegistersLocal;   
}

double BME280_GetTemperatureCelsius(uint8_t readNow) {

    // Loading measurements registers from the device
    if(readNow) BME280_ReadRegisters();
    
    // Preparing measurement register data
    uint32_t regData = BME280_RegistersLocal.TEMP_XLSB >> 4 | 
                       BME280_RegistersLocal.TEMP_LSB  << 4 | 
                       BME280_RegistersLocal.TEMP_MSB  << 12;

    // Compensation algorithm from Bosch Sensortech
    // https://github.com/BoschSensortec/BME280_driver

    double var1;
    double var2;
    double temperature;
    double temperature_min = -40;
    double temperature_max = 85;

    var1 = ((double)regData) / 16384.0 - ((double)BME280_RegistersLocal.dig_T1) / 1024.0;
    var1 = var1 * ((double)BME280_RegistersLocal.dig_T2);
    var2 = (((double)regData) / 131072.0 - ((double)BME280_RegistersLocal.dig_T1) / 8192.0);
    var2 = (var2 * var2) * ((double)BME280_RegistersLocal.dig_T3);
    BME280_RegistersLocal.t_fine = (int32_t)(var1 + var2);
    temperature = (var1 + var2) / 5120.0;

    if      (temperature < temperature_min) temperature = temperature_min;
    else if (temperature > temperature_max) temperature = temperature_max;

    return temperature;
}

int8_t BME280_GetTemperatureFahrenheit(uint8_t readNow) {

    // Converting results in degrees Celsius to degrees Fahrenheit
    return 1.8f * BME280_GetTemperatureCelsius(readNow) + 32;
}

uint32_t BME280_GetPressure(uint8_t readNow) {
    
    // Loading measurements registers from the device
    if(readNow) BME280_ReadRegisters();

    // Preparing measurement register data
    uint32_t regData = BME280_RegistersLocal.PRESS_XLSB >> 4 | 
                       BME280_RegistersLocal.PRESS_LSB  << 4 | 
                       BME280_RegistersLocal.PRESS_MSB  << 12;

    // Compensation algorithm from Bosch Sensortech
    // https://github.com/BoschSensortec/BME280_driver

    double var1;
    double var2;
    double var3;
    double pressure;
    double pressure_min = 30000.0;
    double pressure_max = 110000.0;

    var1 = ((double)BME280_RegistersLocal.t_fine / 2.0) - 64000.0;
    var2 = var1 * var1 * ((double)BME280_RegistersLocal.dig_P6) / 32768.0;
    var2 = var2 + var1 * ((double)BME280_RegistersLocal.dig_P5) * 2.0;
    var2 = (var2 / 4.0) + (((double)BME280_RegistersLocal.dig_P4) * 65536.0);
    var3 = ((double)BME280_RegistersLocal.dig_P3) * var1 * var1 / 524288.0;
    var1 = (var3 + ((double)BME280_RegistersLocal.dig_P2) * var1) / 524288.0;
    var1 = (1.0 + var1 / 32768.0) * ((double)BME280_RegistersLocal.dig_P1);

    pressure = 1048576.0 - (double) regData;
    pressure = (pressure - (var2 / 4096.0)) * 6250.0 / var1;
    var1 = ((double)BME280_RegistersLocal.dig_P9) * pressure * pressure / 2147483648.0;
    var2 = pressure * ((double)BME280_RegistersLocal.dig_P8) / 32768.0;
    pressure = pressure + (var1 + var2 + ((double)BME280_RegistersLocal.dig_P7)) / 16.0;

    if      (pressure < pressure_min) pressure = pressure_min;
    else if (pressure > pressure_max) pressure = pressure_max;

    return pressure;
}

uint8_t BME280_GetHumidity(uint8_t readNow) {
    
    // Loading measurements registers from the device
    if(readNow) BME280_ReadRegisters();

    // Preparing measurement register data
    uint32_t regData = BME280_RegistersLocal.HUM_LSB | 
                       BME280_RegistersLocal.HUM_MSB << 8;

    // Compensation algorithm from Bosch Sensortech
    // https://github.com/BoschSensortec/BME280_driver

    double humidity;
    double humidity_min = 0.0;
    double humidity_max = 100.0;
    double var1;
    double var2;
    double var3;
    double var4;
    double var5;
    double var6;

    var1 = ((double)BME280_RegistersLocal.t_fine) - 76800.0;
    var2 = (((double)BME280_RegistersLocal.dig_H4) * 64.0 + (((double)BME280_RegistersLocal.dig_H5) / 16384.0) * var1);
    var3 = regData - var2;
    var4 = ((double)BME280_RegistersLocal.dig_H2) / 65536.0;
    var5 = (1.0 + (((double)BME280_RegistersLocal.dig_H3) / 67108864.0) * var1);
    var6 = 1.0 + (((double)BME280_RegistersLocal.dig_H6) / 67108864.0) * var1 * var5;
    var6 = var3 * var4 * (var5 * var6);
    humidity = var6 * (1.0 - ((double)BME280_RegistersLocal.dig_H1) * var6 / 524288.0);

    if      (humidity > humidity_max) humidity = humidity_max;
    else if (humidity < humidity_min) humidity = humidity_min;

    return humidity;
}

uint8_t BME280_GetMeasurementDelay(void) {

    // Reading current configuration
    uint8_t temperature_ovrs = BME280_GetTemperatureMode();
    uint8_t pressure_ovrs = BME280_GetPressureMode();
    uint8_t humidity_ovrs = BME280_GetHumidityMode();

    // Parsing configuration
    switch(temperature_ovrs) {
    case BME280_TEMPERATURE_OVERSAMPLING_1X:  temperature_ovrs = 1; break;
    case BME280_TEMPERATURE_OVERSAMPLING_2X:  temperature_ovrs = 2; break;
    case BME280_TEMPERATURE_OVERSAMPLING_4X:  temperature_ovrs = 4; break;
    case BME280_TEMPERATURE_OVERSAMPLING_8X:  temperature_ovrs = 8; break;
    case BME280_TEMPERATURE_OVERSAMPLING_16X: temperature_ovrs = 16; break;
    case BME280_TEMPERATURE_DISABLED:         temperature_ovrs = 0; break;
    };

    switch(pressure_ovrs) {
    case BME280_PRESSURE_OVERSAMPLING_1X:  pressure_ovrs = 1; break;
    case BME280_PRESSURE_OVERSAMPLING_2X:  pressure_ovrs = 2; break;
    case BME280_PRESSURE_OVERSAMPLING_4X:  pressure_ovrs = 4; break;
    case BME280_PRESSURE_OVERSAMPLING_8X:  pressure_ovrs = 8; break;
    case BME280_PRESSURE_OVERSAMPLING_16X: pressure_ovrs = 16; break;
    case BME280_PRESSURE_DISABLED:         pressure_ovrs = 0; break;
    };

    switch(humidity_ovrs) {
    case BME280_HUMIDITY_OVERSAMPLING_1X:  humidity_ovrs = 1; break;
    case BME280_HUMIDITY_OVERSAMPLING_2X:  humidity_ovrs = 2; break;
    case BME280_HUMIDITY_OVERSAMPLING_4X:  humidity_ovrs = 4; break;
    case BME280_HUMIDITY_OVERSAMPLING_8X:  humidity_ovrs = 8; break;
    case BME280_HUMIDITY_OVERSAMPLING_16X: humidity_ovrs = 16; break;
    case BME280_HUMIDITY_DISABLED:         humidity_ovrs = 0; break;
    };

    // Calculating measurement delay components (values from the official datasheet)
    double temperature_delay = temperature_ovrs ? 2.3f * temperature_ovrs : 0;
    double pressure_delay = pressure_ovrs ? 2.3f * pressure_ovrs + 0.575 : 0;
    double humidity_delay = humidity_ovrs ? 2.3f * humidity_ovrs + 0.575 : 0;

    return 1.25 + temperature_delay + pressure_delay + humidity_delay;
}

uint8_t BME280_GetHumidityMode(void) {

    // Returning OSRS_H bits of CTRL_HUM register
    return BME280_RegistersLocal.CTRL_HUM & BME280_CTRL_HUM_OSRS_H;
}

void BME280_SetHumidityMode(uint8_t mode) {

    // Writing OSRS_H bits of CTRL_HUM register
    BME280_RegistersLocal.CTRL_HUM &= BME280_CTRL_HUM_OSRS_H;
    BME280_RegistersLocal.CTRL_HUM |= mode;
    
    // Writing changes to the device
    BME280_I2CWriter(BME280_I2C_ADDR, BME280_CTRL_HUM, &BME280_RegistersLocal.CTRL_HUM, 1);
}

uint8_t BME280_GetTemperatureMode(void) {

    // Returning OSRS_T bits of CTRL_MEAS register
    return BME280_RegistersLocal.CTRL_MEAS & BME280_CTRL_MEAS_OSRS_T;
}

void BME280_SetTemperatureMode(uint8_t mode) {

    // Writing OSRS_T bits of CTRL_MEAS register
    BME280_RegistersLocal.CTRL_MEAS &= ~BME280_CTRL_MEAS_OSRS_T;
    BME280_RegistersLocal.CTRL_MEAS |= mode;
    
    // Writing changes to the device
    BME280_I2CWriter(BME280_I2C_ADDR, BME280_CTRL_MEAS, &BME280_RegistersLocal.CTRL_MEAS, 1);
}

uint8_t BME280_GetPressureMode(void) {

    // Returning OSRS_P bits of CTRL_MEAS register
    return BME280_RegistersLocal.CTRL_MEAS & BME280_CTRL_MEAS_OSRS_P;
}

void BME280_SetPressureMode(uint8_t mode) {

    // Writing OSRS_P bits of CTRL_MEAS register
    BME280_RegistersLocal.CTRL_MEAS &= ~BME280_CTRL_MEAS_OSRS_P;
    BME280_RegistersLocal.CTRL_MEAS |= mode;
    
    // Writing changes to the device
    BME280_I2CWriter(BME280_I2C_ADDR, BME280_CTRL_MEAS, &BME280_RegistersLocal.CTRL_MEAS, 1);
}

uint8_t BME280_IsMeasuring(void) {
    
    // Reading STATUS register
    BME280_I2CReader(BME280_I2C_ADDR, BME280_STATUS, &BME280_RegistersLocal.STATUS, 1);

    // Returning MEASURING bits of STATUS register
    return BME280_RegistersLocal.STATUS & BME280_STATUS_MEASURING;
}

uint8_t BME280_IsUpdating(void) {
    
    // Reading STATUS register
    BME280_I2CReader(BME280_I2C_ADDR, BME280_STATUS, &BME280_RegistersLocal.STATUS, 1);

    // Returning IM_UPDATE bit of STATUS register
    return BME280_RegistersLocal.STATUS & BME280_STATUS_IM_UPDATE;
}

uint8_t BME280_GetMeasurementMode(void) {

    // Reading MODE bits of CTRL_MEAS register
    return BME280_RegistersLocal.CTRL_MEAS & BME280_CTRL_MEAS_MODE;
}

void BME280_SetMeasurementMode(uint8_t mode) {

    // Writing MODE bits of CTRL_MEAS register
    BME280_RegistersLocal.CTRL_MEAS &= ~BME280_CTRL_MEAS_MODE;
    BME280_RegistersLocal.CTRL_MEAS |= mode;
    
    // Writing changes to the device
    BME280_I2CWriter(BME280_I2C_ADDR, BME280_CTRL_MEAS, &BME280_RegistersLocal.CTRL_MEAS, 1);
}

uint8_t BME280_GetStandbyTime(void) {

    // Reading T_SB bits of CONFIG register
    return BME280_RegistersLocal.CONFIG & BME280_CONFIG_T_SB;
}

void BME280_SetStandbyTime(uint8_t standby) {

    // Writing T_SB bits of CONFIG register
    BME280_RegistersLocal.CONFIG &= ~BME280_CONFIG_T_SB;
    BME280_RegistersLocal.CONFIG |= standby;
    
    // Writing changes to the device
    BME280_I2CWriter(BME280_I2C_ADDR, BME280_CONFIG, &BME280_RegistersLocal.CONFIG, 1);
}

uint8_t BME280_GetFilterMode(void) {

    // Reading FILTER bits of CONFIG register
    return BME280_RegistersLocal.CONFIG & BME280_CONFIG_FILTER;
}

void BME280_SetFilterMode(uint8_t mode) {

    // Writing FILTER bits of CONFIG register
    BME280_RegistersLocal.CONFIG &= ~BME280_CONFIG_FILTER;
    BME280_RegistersLocal.CONFIG |= mode;
    
    // Writing changes to the device
    BME280_I2CWriter(BME280_I2C_ADDR, BME280_CONFIG, &BME280_RegistersLocal.CONFIG, 1);
}

void BME280_EnableSPI3Wire(void) {

    // Setting SPI3W_EN bit of CONFIG register
    BME280_RegistersLocal.CONFIG |= BME280_CONFIG_SPI3W_EN;
    
    // Writing changes to the device
    BME280_I2CWriter(BME280_I2C_ADDR, BME280_CONFIG, &BME280_RegistersLocal.CONFIG, 1);
}

void BME280_DisableSPI3Wire(void) {

    // Clearing SPI3W_EN bit of CONFIG register
    BME280_RegistersLocal.CONFIG &= ~BME280_CONFIG_SPI3W_EN;
    
    // Writing changes to the device
    BME280_I2CWriter(BME280_I2C_ADDR, BME280_CONFIG, &BME280_RegistersLocal.CONFIG, 1);
}

uint8_t BME280_IsSPI3WireEnabled() {

    // Reading SPI3W_EN bit of CONFIG register
    return BME280_RegistersLocal.CONFIG & BME280_CONFIG_SPI3W_EN;
}

#endif // DOXYGEN_SHOULD_SKIP_THIS

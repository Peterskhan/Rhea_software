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
 * @file    MCP7940N.c
 * @author  Peter Gyulai
 * @version 1.1.1
 * @date    2020.04.16
 * @brief   Library implementation.
 * @details
 * This file contains the function definitions and static variable definitions used
 * by the MCP7940N driver library.
 */

// Doxygen documentation duplication suppression
#ifndef DOXYGEN_SHOULD_SKIP_THIS

// Standard includes
#include <stdlib.h>

// Project includes
#include "MCP7940N.h"


// Static instance holding a local copy of the MCP7940N's registers
static MCP7940N_RegisterStruct MCP7940N_RegistersLocal;

// Structure holding function pointers to I2C handlers
static MCP7940N_I2CControllerStruct MCP7940N_I2CController;

void MCP7940N_I2CReader(uint8_t address, uint8_t deviceAddress, unsigned char * buffer, uint8_t byteCount) {
    
    // Selecting the device for write
    MCP7940N_I2CController.MasterSendStart(address, 0);
    
    // Writing first device address to read
    MCP7940N_I2CController.MasterWriteByte(deviceAddress);
    
    // Selecting the device for read
    MCP7940N_I2CController.MasterSendStart(address, 1);
    
    // Reading bytes from the device
    for(uint8_t i = 0; i < byteCount; i++) {
        buffer[i] = MCP7940N_I2CController.MasterReadByte(i < byteCount - 1 ? 1 : 0);   
    }
    
    // Sending STOP 
    MCP7940N_I2CController.MasterSendStop();
}

void MCP7940N_I2CWriter(uint8_t address, uint8_t deviceAddress, const unsigned char * buffer, uint8_t byteCount) {
    
    // Selecting the device for write
    MCP7940N_I2CController.MasterSendStart(address, 0);
    
    // Writing first device address to read
    MCP7940N_I2CController.MasterWriteByte(deviceAddress);
    
    // Writing bytes to the device
    for(uint8_t i = 0; i < byteCount; i++) {
                
        // Sending byte to write
        MCP7940N_I2CController.MasterWriteByte(buffer[i]);
    }
    
    // Sending STOP 
    MCP7940N_I2CController.MasterSendStop();
}

void MCP7940N_SetI2CController(MCP7940N_I2CControllerStruct controller) {
    MCP7940N_I2CController = controller;
}

void MCP7940N_ReadRegisters(void) {

    // Reading all registers from the MCP7940N to the local copy
    MCP7940N_I2CReader(MCP7940N_I2C_ADDR, MCP7940N_REGISTERS_START, (uint8_t*) &MCP7940N_RegistersLocal, 
                       MCP7940N_REGISTER_COUNT);
}

void MCP7940N_WriteRegisters(void) {
    
    // Oscillator status
    uint8_t externalStatus = MCP7940N_IsExternalOscillatorEnabled(); 
    uint8_t internalStatus = MCP7940N_IsOscillatorEnabled();
        
    // Disabling oscillator
    if(externalStatus)      MCP7940N_DisableExternalOscillator();
    else if(internalStatus) MCP7940N_DisableOscillator();
    
    // Waiting for oscillator to stop
    while(MCP7940N_IsOscillatorRunning());
    
    // Updating all registers of the MCP7940N from the local copy
    MCP7940N_I2CWriter(MCP7940N_I2C_ADDR, MCP7940N_REGISTERS_START, (uint8_t*) &MCP7940N_RegistersLocal,
                       MCP7940N_REGISTER_COUNT);

    // Enabling oscillator
    if(externalStatus)      MCP7940N_EnableExternalOscillator();
    else if(internalStatus) MCP7940N_EnableOscillator();
}

MCP7940N_RegisterStruct* MCP7940N_GetLocalRegisters(void) {

    // Returning address of the local copy
    return &MCP7940N_RegistersLocal;
}

MCP7940N_Datetime MCP7940N_GetDatetime(void) {
    
    // Reading timekeeping registers
    MCP7940N_I2CReader(MCP7940N_I2C_ADDR, MCP7940N_RTCSEC, (uint8_t*) &MCP7940N_RegistersLocal.RTCSEC, 
                       MCP7940N_RTCYEAR - MCP7940N_RTCSEC + 1);
    
    // Creating structure to store the datetime
    MCP7940N_Datetime result;
    
    // Populating datetime structure
    result.year = MCP7940N_GetYears();
    result.month = MCP7940N_GetMonths();
    result.date = MCP7940N_GetDate();
    result.weekday = MCP7940N_GetWeekday();
    result.hour = MCP7940N_GetHours();
    result.minute = MCP7940N_GetMinutes();
    result.second = MCP7940N_GetSeconds();
    
    return result;
}

uint8_t MCP7940N_GetSeconds(void) {
    
    // Reading RTCSEC register
    uint8_t registerValue = MCP7940N_RegistersLocal.RTCSEC;
    
    // Decoding BCD
    uint8_t ones = registerValue & MCP7940N_RTCSEC_SECONE;
    uint8_t tens = registerValue & MCP7940N_RTCSEC_SECTEN;
    tens = tens >> 4;
    
    // Returning result
    return tens * 10 + ones;
}

uint8_t MCP7940N_GetMinutes(void) {
    
    // Reading RTCMIN register
    uint8_t registerValue = MCP7940N_RegistersLocal.RTCMIN;
    
    // Decoding BCD
    uint8_t ones = registerValue & MCP7940N_RTCMIN_MINONE;
    uint8_t tens = registerValue & MCP7940N_RTCMIN_MINTEN;
    tens = tens >> 4;
    
    // Returning result
    return tens * 10 + ones;
}

uint8_t MCP7940N_GetHours(void) {
    
    // Reading RTCHOUR register
    uint8_t registerValue = MCP7940N_RegistersLocal.RTCHOUR;
    
    // Decoding BCD
    uint8_t ones = registerValue & MCP7940N_RTCHOUR_HRONE;
    uint8_t tens = registerValue & MCP7940N_RTCHOUR_HRTEN;
    tens = tens >> 4;
    
    // Returning result
    return tens * 10 + ones;
}

uint8_t MCP7940N_GetDate(void) {
    
    // Reading RTCDATE register
    uint8_t registerValue = MCP7940N_RegistersLocal.RTCDATE;
    
    // Decoding BCD
    uint8_t ones = registerValue & MCP7940N_RTCDATE_DATEONE;
    uint8_t tens = registerValue & MCP7940N_RTCDATE_DATETEN;
    tens = tens >> 4;
    
    // Returning result
    return tens * 10 + ones;
}

uint8_t MCP7940N_GetWeekday(void) {
    
    // Reading RTCWKDAY register
    uint8_t registerValue = MCP7940N_RegistersLocal.RTCWKDAY;
    
    // Returning result
    return registerValue & MCP7940N_RTCWKDAY_WKDAY;
}

uint8_t MCP7940N_GetMonths(void) {
    
    // Reading RTCMTH register
    uint8_t registerValue = MCP7940N_RegistersLocal.RTCMTH;
    
    // Decoding BCD
    uint8_t ones = registerValue & MCP7940N_RTCMTH_MTHONE;
    uint8_t tens = registerValue & MCP7940N_RTCMTH_MTHTEN;
    tens = tens >> 4;
    
    // Returning result
    return tens * 10 + ones;
}

uint16_t MCP7940N_GetYears(void) {
    
    // Reading RTCYEAR register
    uint8_t registerValue = MCP7940N_RegistersLocal.RTCYEAR;
    
    // Decoding BCD
    uint8_t ones = registerValue & MCP7940N_RTCYEAR_YRONE;
    uint8_t tens = registerValue & MCP7940N_RTCYEAR_YRTEN;
    tens = tens >> 4;
    
    // Returning result
    return 2000 + tens * 10 + ones;
}

void MCP7940N_SetDatetime(MCP7940N_Datetime datetime) {
    
    // Oscillator status
    uint8_t externalStatus = MCP7940N_IsExternalOscillatorEnabled();
    uint8_t internalStatus = MCP7940N_IsOscillatorEnabled();
    
    // Disabling oscillator sources
    if(externalStatus)      MCP7940N_DisableExternalOscillator();
    else if(internalStatus) MCP7940N_DisableOscillator();
    
    // Waiting for oscillator to stop
    while(MCP7940N_IsOscillatorRunning());
    
    // Reading current datetime and configuration
    MCP7940N_I2CReader(MCP7940N_I2C_ADDR, MCP7940N_RTCSEC, (uint8_t*) &MCP7940N_RegistersLocal.RTCSEC,
                       MCP7940N_RTCYEAR - MCP7940N_RTCSEC + 1);
    
    // Writing new datetime to local registers
    MCP7940N_SetYears(datetime.year);
    MCP7940N_SetMonths(datetime.month);
    MCP7940N_SetDate(datetime.date);
    MCP7940N_SetWeekday(datetime.weekday);
    MCP7940N_SetHours(datetime.hour);
    MCP7940N_SetMinutes(datetime.minute);
    MCP7940N_SetSeconds(datetime.second);
    
    // Updating timekeeping registers of the MCP7940N from the local copy
    MCP7940N_I2CWriter(MCP7940N_I2C_ADDR, MCP7940N_RTCSEC, (uint8_t*) &MCP7940N_RegistersLocal.RTCSEC,
                       MCP7940N_RTCYEAR - MCP7940N_RTCSEC + 1);

    // Enabling oscillator sources
    if(externalStatus)      MCP7940N_EnableExternalOscillator();
    else if(internalStatus) MCP7940N_EnableOscillator();
}

void MCP7940N_SetSeconds(uint8_t seconds) {
    
    // Encoding BCD
    uint8_t ones = seconds % 10;
    uint8_t tens = seconds / 10;
    uint8_t registerValue = ones | tens << 4 ;
    
    // Clearing seconds bits of RTCSEC register
    MCP7940N_RegistersLocal.RTCSEC &= ~(MCP7940N_RTCSEC_SECONE | MCP7940N_RTCSEC_SECTEN);
    
    // Writing seconds bits of RTCSEC register
    MCP7940N_RegistersLocal.RTCSEC |= registerValue;
}

void MCP7940N_SetMinutes(uint8_t minutes) {
    
    // Encoding BCD
    uint8_t ones = minutes % 10;
    uint8_t tens = minutes / 10;
    uint8_t registerValue = ones | tens << 4;
    
    // Writing RTCMIN register
    MCP7940N_RegistersLocal.RTCMIN = registerValue;
}

void MCP7940N_SetHours(uint8_t hours) {
    
    // Encoding BCD
    uint8_t ones = hours % 10;
    uint8_t tens = hours / 10;
    uint8_t registerValue = ones | tens << 4;
    
    // Clearing hour bits of RTCHOUR register
    MCP7940N_RegistersLocal.RTCHOUR &= ~(MCP7940N_RTCHOUR_HRONE | MCP7940N_RTCHOUR_HRTEN);
                                            
    // Writing hour bits of RTCHOUR register
    MCP7940N_RegistersLocal.RTCHOUR |= registerValue;
}

void MCP7940N_SetDate(uint16_t date) {
    
    // Encoding BCD
    uint8_t ones = date % 10;
    uint8_t tens = date / 10;
    uint8_t registerValue = ones | tens << 4;
    
    // Writing RTCDATE register
    MCP7940N_RegistersLocal.RTCDATE = registerValue;
}

void MCP7940N_SetWeekday(uint8_t weekday) {
    
    // Clearing weekday bits of RTCWKDAY register
    MCP7940N_RegistersLocal.RTCWKDAY &= ~MCP7940N_RTCWKDAY_WKDAY;
    
    // Writing weekday bits of RTCWKDAY register
    MCP7940N_RegistersLocal.RTCWKDAY |= weekday;
}

void MCP7940N_SetMonths(uint8_t months) {
    
    // Encoding BCD
    uint8_t ones = months % 10;
    uint8_t tens = months / 10;
    uint8_t registerValue = ones | tens << 4;
    
    // Writing RTCMTH register
    MCP7940N_RegistersLocal.RTCMTH = registerValue;
}

void MCP7940N_SetYears(uint16_t years) {
    
    // Encoding BCD
    years = years - 2000;
    uint8_t ones = years % 10;
    uint8_t tens = years / 10;
    uint8_t registerValue = ones | tens << 4;
    
    // Writing RTCYEAR register
    MCP7940N_RegistersLocal.RTCYEAR = registerValue;
}

uint8_t MCP7940N_IsOscillatorEnabled(void) {
    
    // Reading current content of RTCSEC register
    MCP7940N_I2CReader(MCP7940N_I2C_ADDR, MCP7940N_RTCSEC, (uint8_t*) &MCP7940N_RegistersLocal.RTCSEC, 1);
    
    // Returning whether ST flag is set
    return MCP7940N_RegistersLocal.RTCSEC & MCP7940N_RTCSEC_ST; 
}

void MCP7940N_EnableOscillator(void) {
    
    // Reading current content of RTCSEC register
    MCP7940N_I2CReader(MCP7940N_I2C_ADDR, MCP7940N_RTCSEC, (uint8_t*) &MCP7940N_RegistersLocal.RTCSEC, 1);
    
    // Setting ST flag of RTCSEC register
    MCP7940N_RegistersLocal.RTCSEC |= MCP7940N_RTCSEC_ST;
    
    // Writing changes to hardware
    MCP7940N_I2CWriter(MCP7940N_I2C_ADDR, MCP7940N_RTCSEC, (uint8_t*) &MCP7940N_RegistersLocal.RTCSEC, 1);
}

void MCP7940N_DisableOscillator(void) {
    
    // Reading current content of RTCSEC register
    MCP7940N_I2CReader(MCP7940N_I2C_ADDR, MCP7940N_RTCSEC, (uint8_t*) &MCP7940N_RegistersLocal.RTCSEC, 1);
    
    // Clearing ST flag of RTCSEC register
    MCP7940N_RegistersLocal.RTCSEC &= ~MCP7940N_RTCSEC_ST;
    
    // Writing changes to hardware
    MCP7940N_I2CWriter(MCP7940N_I2C_ADDR, MCP7940N_RTCSEC, (uint8_t*) &MCP7940N_RegistersLocal.RTCSEC, 1);
}

uint8_t MCP7940N_IsOscillatorRunning(void) {
    
    // Reading RTCWKDAY register
    MCP7940N_I2CReader(MCP7940N_I2C_ADDR, MCP7940N_RTCWKDAY, (uint8_t*) &MCP7940N_RegistersLocal.RTCWKDAY, 1);
    
    // Returning whether OSCRUN bit is set
    return MCP7940N_RegistersLocal.RTCWKDAY & MCP7940N_RTCWKDAY_OSCRUN;    
}

void MCP7940N_EnableBattery(void) {
    
    // Oscillator status
    uint8_t externalStatus = MCP7940N_IsExternalOscillatorEnabled();
    uint8_t internalStatus = MCP7940N_IsOscillatorEnabled();
    
    // Disabling oscillator sources
    if(externalStatus)      MCP7940N_DisableExternalOscillator();
    else if(internalStatus) MCP7940N_DisableOscillator();
    
    // Waiting for oscillator to stop
    while(MCP7940N_IsOscillatorRunning());
    
    // Reading current content of RTCWKDAY register
    MCP7940N_I2CReader(MCP7940N_I2C_ADDR, MCP7940N_RTCWKDAY, (uint8_t*) &MCP7940N_RegistersLocal.RTCWKDAY, 1);

    // Setting VBATEN flag of RTCWKDAY register
    MCP7940N_RegistersLocal.RTCWKDAY |= MCP7940N_RTCWKDAY_VBATEN;
    
    // Writing changes to hardware
    MCP7940N_I2CWriter(MCP7940N_I2C_ADDR, MCP7940N_RTCWKDAY, (uint8_t*) &MCP7940N_RegistersLocal.RTCWKDAY, 1);

    // Enabling oscillator sources
    if(externalStatus)      MCP7940N_EnableExternalOscillator();
    else if(internalStatus) MCP7940N_EnableOscillator();
}

void MCP7940N_DisableBattery(void) {
    
    // Oscillator status
    uint8_t externalStatus = MCP7940N_IsExternalOscillatorEnabled();
    uint8_t internalStatus = MCP7940N_IsOscillatorEnabled();
    
    // Disabling oscillator sources
    if(externalStatus)      MCP7940N_DisableExternalOscillator();
    else if(internalStatus) MCP7940N_DisableOscillator();
    
    // Waiting for oscillator to stop
    while(MCP7940N_IsOscillatorRunning());
    
    // Reading current content of RTCWKDAY register
    MCP7940N_I2CReader(MCP7940N_I2C_ADDR, MCP7940N_RTCWKDAY, (uint8_t*) &MCP7940N_RegistersLocal.RTCWKDAY, 1);
    
    // Clearing VBATEN flag of RTCWKDAY register
    MCP7940N_RegistersLocal.RTCWKDAY &= ~MCP7940N_RTCWKDAY_VBATEN;
    
    // Writing changes to hardware
    MCP7940N_I2CWriter(MCP7940N_I2C_ADDR, MCP7940N_RTCWKDAY, (uint8_t*) &MCP7940N_RegistersLocal.RTCWKDAY, 1);

    // Enabling oscillator sources
    if(externalStatus)      MCP7940N_EnableExternalOscillator();
    else if(internalStatus) MCP7940N_EnableOscillator();
}

uint8_t MCP7940N_IsBatteryEnabled(void) {
    
    // Reading RTCWKDAY register
    MCP7940N_I2CReader(MCP7940N_I2C_ADDR, MCP7940N_RTCWKDAY, (uint8_t*) &MCP7940N_RegistersLocal.RTCWKDAY, 1);
    
    // Returning whether VBATEN bit is set
    return MCP7940N_RegistersLocal.RTCWKDAY & MCP7940N_RTCWKDAY_VBATEN;
}

uint8_t MCP7940N_HasPowerFailed(void) {
    
    // Reading RTCWKDAY register
    MCP7940N_I2CReader(MCP7940N_I2C_ADDR, MCP7940N_RTCWKDAY, (uint8_t*) &MCP7940N_RegistersLocal.RTCWKDAY, 1);
    
    // Returning whether PWRFAIL bit is set
    return MCP7940N_RegistersLocal.RTCWKDAY & MCP7940N_RTCWKDAY_PWRFAIL;
}

void MCP7940N_ClearPowerFailed(void) {
    
    // Oscillator status
    uint8_t externalStatus = MCP7940N_IsExternalOscillatorEnabled();
    uint8_t internalStatus = MCP7940N_IsOscillatorEnabled();
    
    // Disabling oscillator sources
    if(externalStatus)      MCP7940N_DisableExternalOscillator();
    else if(internalStatus) MCP7940N_DisableOscillator();
    
    // Waiting for oscillator to stop
    while(MCP7940N_IsOscillatorRunning());
    
    // Reading current content of RTCWKDAY register
    MCP7940N_I2CReader(MCP7940N_I2C_ADDR, MCP7940N_RTCWKDAY, (uint8_t*) &MCP7940N_RegistersLocal.RTCWKDAY, 1);
    
    // Clearing PWRFAIL flag of RTCWKDAY register
    MCP7940N_RegistersLocal.RTCWKDAY &= ~MCP7940N_RTCWKDAY_PWRFAIL;
    
    // Writing changes to hardware
    MCP7940N_I2CWriter(MCP7940N_I2C_ADDR, MCP7940N_RTCWKDAY, (uint8_t*) &MCP7940N_RegistersLocal.RTCWKDAY, 1);

    // Enabling oscillator sources
    if(externalStatus)      MCP7940N_EnableExternalOscillator();
    else if(internalStatus) MCP7940N_EnableOscillator();
}

uint8_t MCP7940N_IsLeapYear(void) {
    
    // Reading RTCMTH register
    MCP7940N_I2CReader(MCP7940N_I2C_ADDR, MCP7940N_RTCWKDAY, (uint8_t*) &MCP7940N_RegistersLocal.RTCWKDAY, 1);
    
    // Returning whether LPYR bit is set
    return MCP7940N_RegistersLocal.RTCMTH & MCP7940N_RTCMTH_LPYR;
}

void MCP7940N_SetMFPMode(uint8_t mode) {
       
    // Writing MFP mode bits to CONTROL register
    switch(mode) {
    case MCP7940N_MFP_ALARM:  MCP7940N_RegistersLocal.CONTROL &= MCP7940N_MFP_ALARM; return;
    case MCP7940N_MFP_SQUARE: MCP7940N_RegistersLocal.CONTROL |= MCP7940N_MFP_SQUARE; return;
    case MCP7940N_MFP_GPIO:   MCP7940N_RegistersLocal.CONTROL &= MCP7940N_MFP_GPIO;  return;
    };
    
    // Writing changes to hardware
    MCP7940N_I2CWriter(MCP7940N_I2C_ADDR, MCP7940N_CONTROL, (uint8_t*) &MCP7940N_RegistersLocal.CONTROL, 1);
}

uint8_t MCP7940N_GetMFPMode() {
    
    // Reading CONTROL register
    uint8_t registerValue = MCP7940N_RegistersLocal.CONTROL;
    
    // Returning current mode based on the masked register values
    switch(registerValue & (MCP7940N_CONTROL_SQWEN | MCP7940N_CONTROL_ALM0EN | MCP7940N_CONTROL_ALM1EN)) {
    case MCP7940N_CONTROL_ALM0EN: 
    case MCP7940N_CONTROL_ALM1EN:
    case MCP7940N_CONTROL_ALM0EN | MCP7940N_CONTROL_ALM1EN: 
         return MCP7940N_MFP_ALARM;
    
    case MCP7940N_CONTROL_SQWEN:
    case MCP7940N_CONTROL_SQWEN | MCP7940N_CONTROL_ALM0EN:
    case MCP7940N_CONTROL_SQWEN | MCP7940N_CONTROL_ALM1EN:
    case MCP7940N_CONTROL_SQWEN | MCP7940N_CONTROL_ALM0EN | MCP7940N_CONTROL_ALM1EN: 
         return MCP7940N_MFP_SQUARE;
    
    default: return MCP7940N_MFP_GPIO;
    };
}

void MCP7940N_SetGPIO(uint8_t value) {

    // Writing CONTROL register
    MCP7940N_RegistersLocal.CONTROL &= ~MCP7940N_CONTROL_OUT;
    MCP7940N_RegistersLocal.CONTROL |=  value;
    
    // Writing changes to hardware
    MCP7940N_I2CWriter(MCP7940N_I2C_ADDR, MCP7940N_CONTROL, (uint8_t*) &MCP7940N_RegistersLocal.CONTROL, 1);
}

void MCP7940N_EnableCoarseTrimming(void) {

    // Setting CRSTRIM bit of CONTROL register
    MCP7940N_RegistersLocal.CONTROL |= MCP7940N_CONTROL_CRSTRIM;
    
    // Writing changes to hardware
    MCP7940N_I2CWriter(MCP7940N_I2C_ADDR, MCP7940N_CONTROL, (uint8_t*) &MCP7940N_RegistersLocal.CONTROL, 1);
}

void MCP7940N_DisableCoarseTrimming(void) {

    // Clearing CRSTRIM bit of CONTROL register
    MCP7940N_RegistersLocal.CONTROL &= ~MCP7940N_CONTROL_CRSTRIM;
    
    // Writing changes to hardware
    MCP7940N_I2CWriter(MCP7940N_I2C_ADDR, MCP7940N_CONTROL, (uint8_t*) &MCP7940N_RegistersLocal.CONTROL, 1);
}

uint8_t MCP7940N_IsCoarseTrimmingEnabled(void) {

    // Returning whether CRSTRIM bit is set
    return MCP7940N_RegistersLocal.CONTROL & MCP7940N_CONTROL_CRSTRIM;
}

void MCP7940N_SetTrimmingValue(int8_t value) {
    
    // Setting sign flag of OSCTRIM register
    if(value > 0) MCP7940N_RegistersLocal.OSCTRIM |=  MCP7940N_OSCTRIM_SIGN;
    else          MCP7940N_RegistersLocal.OSCTRIM &= ~MCP7940N_OSCTRIM_SIGN;
    
    // Setting trimming bits of OSCTRIM register
    MCP7940N_RegistersLocal.OSCTRIM &= ~MCP7940N_OSCTRIM_TRIMVAL;
    MCP7940N_RegistersLocal.OSCTRIM |= (uint8_t) abs(value);
    
    // Writing changes to hardware
    MCP7940N_I2CWriter(MCP7940N_I2C_ADDR, MCP7940N_CONTROL, (uint8_t*) &MCP7940N_RegistersLocal.CONTROL, 1);
}

int8_t MCP7940N_GetTrimmingValue(void) {
    
    // Reading OSCTRIM register
    uint8_t registerValue = MCP7940N_RegistersLocal.OSCTRIM & MCP7940N_OSCTRIM_TRIMVAL;
    
    // Returning trimming value
    return MCP7940N_RegistersLocal.OSCTRIM & MCP7940N_OSCTRIM_SIGN ? registerValue : -registerValue;
}

uint8_t MCP7940N_GetSquarewaveFrequency(void) {

    // Returning SQWFS bits of CONTROL register
    return MCP7940N_RegistersLocal.CONTROL & MCP7940N_CONTROL_SQWFS;
}

void MCP7940N_SetSquarewaveFrequency(uint8_t frequency) {
    
    // Clearing frequency bits of CONTROL register
    MCP7940N_RegistersLocal.CONTROL &= ~MCP7940N_CONTROL_SQWFS;
    
    // Setting frequency bits of CONTROL register
    MCP7940N_RegistersLocal.CONTROL |= frequency;
    
    // Writing changes to hardware
    MCP7940N_I2CWriter(MCP7940N_I2C_ADDR, MCP7940N_CONTROL, (uint8_t*) &MCP7940N_RegistersLocal.CONTROL, 1);
}

void MCP7940N_EnableExternalOscillator(void) {

    // Setting EXTOSC bit of CONTROL register
    MCP7940N_RegistersLocal.CONTROL |= MCP7940N_CONTROL_EXTOSC;
    
    // Writing changes to hardware
    MCP7940N_I2CWriter(MCP7940N_I2C_ADDR, MCP7940N_CONTROL, (uint8_t*) &MCP7940N_RegistersLocal.CONTROL, 1);
}

void MCP7940N_DisableExternalOscillator(void) {

    // Clearing EXTOSC bit of CONTROL register
    MCP7940N_RegistersLocal.CONTROL &= ~MCP7940N_CONTROL_EXTOSC;
    
    // Writing changes to hardware
    MCP7940N_I2CWriter(MCP7940N_I2C_ADDR, MCP7940N_CONTROL, (uint8_t*) &MCP7940N_RegistersLocal.CONTROL, 1);
}

uint8_t MCP7940N_IsExternalOscillatorEnabled(void) {

    // Returning whether EXTOSC bit of CONTROL register is set
    return MCP7940N_RegistersLocal.CONTROL & MCP7940N_CONTROL_EXTOSC;
}

MCP7940N_Datetime MCP7940N_GetAlarmDatetime(uint8_t id) {

    // Creating datetime structure to store the result
    MCP7940N_Datetime datetime;
    
    // Populating datetime structure
    datetime.month = MCP7940N_GetAlarmMonths(id);
    datetime.date = MCP7940N_GetAlarmDate(id);
    datetime.weekday = MCP7940N_GetAlarmWeekday(id);
    datetime.hour = MCP7940N_GetAlarmHours(id);
    datetime.minute = MCP7940N_GetAlarmMinutes(id);
    datetime.second = MCP7940N_GetAlarmSeconds(id);
    
    return datetime;
}

uint8_t MCP7940N_GetAlarmSeconds(uint8_t id) {
    
    // Reading ALMxSEC register
    uint8_t registerValue = 0;
    switch(id) {
    case MCP7940N_ALARM0: registerValue = MCP7940N_RegistersLocal.ALM0SEC; break;
    case MCP7940N_ALARM1: registerValue = MCP7940N_RegistersLocal.ALM1SEC; break;
    default: break;
    };
    
    // Decoding BCD
    uint8_t ones = registerValue & MCP7940N_ALMxSEC_SECONE;
    uint8_t tens = registerValue & MCP7940N_ALMxSEC_SECTEN;
    tens = tens >> 4;
    
    // Returning result
    return tens * 10 + ones;
}

uint8_t MCP7940N_GetAlarmMinutes(uint8_t id) {
    
    // Reading ALMxMIN register
    uint8_t registerValue = 0;
    switch(id) {
    case MCP7940N_ALARM0: registerValue = MCP7940N_RegistersLocal.ALM0MIN; break;
    case MCP7940N_ALARM1: registerValue = MCP7940N_RegistersLocal.ALM1MIN; break;
    default: break;
    };
    
    // Decoding BCD
    uint8_t ones = registerValue & MCP7940N_ALMxMIN_MINONE;
    uint8_t tens = registerValue & MCP7940N_ALMxMIN_MINTEN;
    tens = tens >> 4;
    
    // Returning result
    return tens * 10 + ones;
}

uint8_t MCP7940N_GetAlarmHours(uint8_t id) {
    
    // Reading ALMxHOUR register
    uint8_t registerValue = 0;
    switch(id) {
    case MCP7940N_ALARM0: registerValue = MCP7940N_RegistersLocal.ALM0HOUR; break;
    case MCP7940N_ALARM1: registerValue = MCP7940N_RegistersLocal.ALM1HOUR; break;
    default: break;
    };
    
    // Decoding BCD
    uint8_t ones = registerValue & MCP7940N_ALMxHOUR_HRONE;
    uint8_t tens = registerValue & MCP7940N_ALMxHOUR_HRTEN;
    tens = tens >> 4;
    
    // Returning result
    return tens * 10 + ones;
}

uint8_t MCP7940N_GetAlarmWeekday(uint8_t id) {
    
    // Reading ALMxWKDAY register
    uint8_t registerValue = 0;
    switch(id) {
    case MCP7940N_ALARM0: registerValue = MCP7940N_RegistersLocal.ALM0WKDAY; break;
    case MCP7940N_ALARM1: registerValue = MCP7940N_RegistersLocal.ALM1WKDAY; break;
    default: break;
    };
    
    // Returning result
    return registerValue & MCP7940N_ALMxWKDAY_WKDAY;
}

uint8_t MCP7940N_GetAlarmDate(uint8_t id) {
    
    // Reading ALMxDATE register
    uint8_t registerValue = 0;
    switch(id) {
    case MCP7940N_ALARM0: registerValue = MCP7940N_RegistersLocal.ALM0DATE; break;
    case MCP7940N_ALARM1: registerValue = MCP7940N_RegistersLocal.ALM1DATE; break;
    default: break;
    };
    
    // Decoding BCD
    uint8_t ones = registerValue & MCP7940N_ALMxDATE_DATEONE;
    uint8_t tens = registerValue & MCP7940N_ALMxDATE_DATETEN;
    tens = tens >> 4;
    
    // Returning result
    return tens * 10 + ones;
}

uint8_t MCP7940N_GetAlarmMonths(uint8_t id) {
    
    // Reading ALMxMTH register
    uint8_t registerValue = 0;
    switch(id) {
    case MCP7940N_ALARM0: registerValue = MCP7940N_RegistersLocal.ALM0MTH; break;
    case MCP7940N_ALARM1: registerValue = MCP7940N_RegistersLocal.ALM1MTH; break;
    default: break;
    };
    
    // Decoding BCD
    uint8_t ones = registerValue & MCP7940N_ALMxMTH_MTHONE;
    uint8_t tens = registerValue & MCP7940N_ALMxMTH_MTHTEN;
    tens = tens >> 4;
    
    // Returning result
    return tens * 10 + ones;
}

uint8_t MCP7940N_GetAlarmPolarity(void) {
    
    // Returning alarm polarity
    return MCP7940N_RegistersLocal.ALM0WKDAY & MCP7940N_ALMxWKDAY_ALMPOL;
}

uint8_t MCP7940N_GetAlarmMode(uint8_t id) {
    
    // Returning alarm mode mask
    switch(id) {
    case MCP7940N_ALARM0: return MCP7940N_RegistersLocal.ALM0WKDAY & MCP7940N_ALMxWKDAY_ALMxMSK;
    case MCP7940N_ALARM1: return MCP7940N_RegistersLocal.ALM1WKDAY & MCP7940N_ALMxWKDAY_ALMxMSK;
    default:     return 0;
    };
}

uint8_t MCP7940N_IsAlarmEnabled(uint8_t id) {
     
    // Returning whether ALMxEN flag is set
    switch(id) {
    case MCP7940N_ALARM0: return MCP7940N_RegistersLocal.CONTROL & MCP7940N_CONTROL_ALM0EN;
    case MCP7940N_ALARM1: return MCP7940N_RegistersLocal.CONTROL & MCP7940N_CONTROL_ALM1EN;
    default:              return MCP7940N_ALARM_DISABLED;
    };
}

uint8_t MCP7940N_HasAlarmFired(uint8_t id) {
    
    // Reading ALMxWKDAY registers
    MCP7940N_I2CReader(MCP7940N_I2C_ADDR, MCP7940N_ALM0WKDAY, (uint8_t*) &MCP7940N_RegistersLocal.ALM0WKDAY, 1);
    MCP7940N_I2CReader(MCP7940N_I2C_ADDR, MCP7940N_ALM1WKDAY, (uint8_t*) &MCP7940N_RegistersLocal.ALM1WKDAY, 1);
    
    // Register value initialization
    uint8_t registerValue = MCP7940N_ALARM_NOT_FIRED;
    
    // Returning whether ALMxIF flag is set
    switch(id) {
    case MCP7940N_ALARM0: registerValue = MCP7940N_RegistersLocal.ALM0WKDAY & MCP7940N_ALMxWKDAY_ALMxIF;
                          MCP7940N_RegistersLocal.ALM0WKDAY &= ~MCP7940N_ALMxWKDAY_ALMxIF;
    case MCP7940N_ALARM1: registerValue = MCP7940N_RegistersLocal.ALM1WKDAY & MCP7940N_ALMxWKDAY_ALMxIF;
                          MCP7940N_RegistersLocal.ALM1WKDAY &= ~MCP7940N_ALMxWKDAY_ALMxIF;
    default:              registerValue = MCP7940N_ALARM_NOT_FIRED;
    };
    
    return registerValue;
}

void MCP7940N_SetAlarmDatetime(uint8_t id, MCP7940N_Datetime datetime) {
    
    // Setting alarm registers
    MCP7940N_SetAlarmSeconds(id, datetime.second);
    MCP7940N_SetAlarmMinutes(id, datetime.minute);
    MCP7940N_SetAlarmHours(id, datetime.hour);
    MCP7940N_SetAlarmWeekday(id, datetime.weekday);
    MCP7940N_SetAlarmDate(id, datetime.date);
    MCP7940N_SetAlarmMonths(id, datetime.month);
    
    // Writing changes to hardware
    if(id == MCP7940N_ALARM0) {
        MCP7940N_I2CWriter(MCP7940N_I2C_ADDR, MCP7940N_ALM0SEC, (uint8_t*) &MCP7940N_RegistersLocal.ALM0SEC,
                           MCP7940N_ALM0MTH - MCP7940N_ALM0SEC + 1);
    }
    else if(id == MCP7940N_ALARM1) {
        MCP7940N_I2CWriter(MCP7940N_I2C_ADDR, MCP7940N_ALM0SEC, (uint8_t*) &MCP7940N_RegistersLocal.ALM0SEC,
                           MCP7940N_ALM0MTH - MCP7940N_ALM0SEC + 1);
    }
}

void MCP7940N_SetAlarmSeconds(uint8_t id, uint8_t seconds) {
  
    // Encoding BCD
    uint8_t ones = seconds % 10;
    uint8_t tens = seconds / 10;
    uint8_t registerValue = ones | tens << 4;
    
    // Writing alarm seconds register
    switch(id) {
    case MCP7940N_ALARM0: MCP7940N_RegistersLocal.ALM0SEC = registerValue; return;
    case MCP7940N_ALARM1: MCP7940N_RegistersLocal.ALM1SEC = registerValue; return;
    default: return;
    };
}

void MCP7940N_SetAlarmMinutes(uint8_t id, uint8_t minutes) {

    // Encoding BCD
    uint8_t ones = minutes % 10;
    uint8_t tens = minutes / 10;
    uint8_t registerValue = ones | tens << 4;
    
    // Writing alarm minute register
    switch(id) {
    case MCP7940N_ALARM0: MCP7940N_RegistersLocal.ALM0MIN = registerValue; return;
    case MCP7940N_ALARM1: MCP7940N_RegistersLocal.ALM1MIN = registerValue; return;
    default: return;
    };
}

void MCP7940N_SetAlarmHours(uint8_t id, uint8_t hours) {

    // Encoding BCD
    uint8_t ones = hours % 10;
    uint8_t tens = hours / 10;
    uint8_t registerValue = ones | tens << 4;
    
    // Writing alarm hour register
    switch(id) {
    case MCP7940N_ALARM0: MCP7940N_RegistersLocal.ALM0HOUR = registerValue; return;
    case MCP7940N_ALARM1: MCP7940N_RegistersLocal.ALM1HOUR = registerValue; return;
    default: return;
    };
}

void MCP7940N_SetAlarmWeekday(uint8_t id, uint8_t weekday) {
    
    // Writing alarm weekday register
    switch(id) {
    case MCP7940N_ALARM0:   MCP7940N_RegistersLocal.ALM0WKDAY &= ~MCP7940N_ALMxWKDAY_WKDAY;
                            MCP7940N_RegistersLocal.ALM0WKDAY |= weekday; 
                            return;
    case MCP7940N_ALARM1:   MCP7940N_RegistersLocal.ALM1WKDAY &= ~MCP7940N_ALMxWKDAY_WKDAY;
                            MCP7940N_RegistersLocal.ALM1WKDAY |= weekday; 
                            return;
    default:                return;
    };
}

void MCP7940N_SetAlarmDate(uint8_t id, uint8_t date) {

    // Encoding BCD
    uint8_t ones = date % 10;
    uint8_t tens = date / 10;
    uint8_t registerValue = ones | tens << 4;
    
    // Writing alarm date register
    switch(id) {
    case MCP7940N_ALARM0: MCP7940N_RegistersLocal.ALM0DATE = registerValue; return;
    case MCP7940N_ALARM1: MCP7940N_RegistersLocal.ALM1DATE = registerValue; return;
    default: return;
    };
}

void MCP7940N_SetAlarmMonths(uint8_t id, uint8_t months) {

    // Encoding BCD
    uint8_t ones = months % 10;
    uint8_t tens = months / 10;
    uint8_t registerValue = ones | tens << 4;
    
    // Writing alarm month register
    switch(id) {
    case MCP7940N_ALARM0: MCP7940N_RegistersLocal.ALM0MTH = registerValue; return;
    case MCP7940N_ALARM1: MCP7940N_RegistersLocal.ALM1MTH = registerValue; return;
    default: return;
    };
}

void MCP7940N_SetAlarmPolarity(uint8_t polarity) {
    
    // Writing ALM0WKDAY register
    MCP7940N_RegistersLocal.ALM0WKDAY &= ~MCP7940N_ALMxWKDAY_ALMPOL;
    MCP7940N_RegistersLocal.ALM0WKDAY |= polarity;
    
    // Writing changes to hardware
    MCP7940N_I2CWriter(MCP7940N_I2C_ADDR, MCP7940N_ALM0WKDAY, (uint8_t*) &MCP7940N_RegistersLocal.ALM0WKDAY, 1);
}

void MCP7940N_EnableAlarm(uint8_t id, uint8_t mode) {
    
    // Writing alarm weekday & CONTROL registers
    switch(id) {
    case MCP7940N_ALARM0:   MCP7940N_RegistersLocal.ALM0WKDAY &= ~MCP7940N_ALMxWKDAY_ALMxMSK;
                            MCP7940N_RegistersLocal.ALM0WKDAY |= mode;
                            MCP7940N_RegistersLocal.CONTROL   |= MCP7940N_CONTROL_ALM0EN;
                            return;
    case MCP7940N_ALARM1:   MCP7940N_RegistersLocal.ALM1WKDAY &= ~MCP7940N_ALMxWKDAY_ALMxMSK;
                            MCP7940N_RegistersLocal.ALM0WKDAY |= mode;
                            MCP7940N_RegistersLocal.CONTROL   |= MCP7940N_CONTROL_ALM1EN;
                            return;
    default:                return;
    };
    
    // Writing changes to hardware
    if(id == MCP7940N_ALARM0) {
        MCP7940N_I2CWriter(MCP7940N_I2C_ADDR, MCP7940N_ALM0WKDAY, (uint8_t*) &MCP7940N_RegistersLocal.ALM0WKDAY, 1);
    }
    else if(id == MCP7940N_ALARM1) {
        MCP7940N_I2CWriter(MCP7940N_I2C_ADDR, MCP7940N_ALM0WKDAY, (uint8_t*) &MCP7940N_RegistersLocal.ALM0WKDAY, 1);
    }
    MCP7940N_I2CWriter(MCP7940N_I2C_ADDR, MCP7940N_CONTROL, (uint8_t*) &MCP7940N_RegistersLocal.CONTROL, 1);
}

void MCP7940N_DisableAlarm(uint8_t id) {
    
    // Clearing alarm enable bit of CONTROL register
    switch(id) {
    case MCP7940N_ALARM0: MCP7940N_RegistersLocal.CONTROL &= ~MCP7940N_CONTROL_ALM0EN; return;
    case MCP7940N_ALARM1: MCP7940N_RegistersLocal.CONTROL &= ~MCP7940N_CONTROL_ALM1EN; return;
    default: return;
    };  
    
    // Writing changes to hardware
    MCP7940N_I2CWriter(MCP7940N_I2C_ADDR, MCP7940N_CONTROL, (uint8_t*) &MCP7940N_RegistersLocal.CONTROL, 1);
}

MCP7940N_Datetime MCP7940N_GetPowerFailDatetime(void) {
    
    // Reading power-fail timestamp registers
    MCP7940N_I2CReader(MCP7940N_I2C_ADDR, MCP7940N_PWRDNMIN, (uint8_t*) &MCP7940N_RegistersLocal.PWRDNMIN, 
                       MCP7940N_PWRDNMTH - MCP7940N_PWRDNMIN + 1);
    
    // Creating datetime structure to store the result
    MCP7940N_Datetime datetime;
    
    // Populating datetime structure
    datetime.year = 0;
    datetime.month = MCP7940N_GetPowerFailMonth();
    datetime.date = MCP7940N_GetPowerFailDate();
    datetime.weekday = MCP7940N_GetPowerFailWeekday();
    datetime.hour = MCP7940N_GetPowerFailHour();
    datetime.minute = MCP7940N_GetPowerFailMinute();
    datetime.second = 0;
    
    return datetime;
}

uint8_t MCP7940N_GetPowerFailMonth(void) {
    
    // Reading PWRDNMTH register
    uint8_t registerValue = MCP7940N_RegistersLocal.PWRDNMTH;
    
    // Decoding BCD
    uint8_t ones = registerValue & MCP7940N_PWRDNMTH_MTHONE;
    uint8_t tens = registerValue & MCP7940N_PWRDNMTH_MTHTEN;
    tens = tens >> 4;
    
    // Returning result
    return tens * 10 + ones;
}

uint8_t MCP7940N_GetPowerFailWeekday(void) {
    
    // Return weekday bits of PWRDNMTH register
    return (MCP7940N_RegistersLocal.PWRDNMTH & MCP7940N_PWRDNMTH_WKDAY) >> 5;  
}

uint8_t MCP7940N_GetPowerFailDate(void) {
    
    // Reading PWRDNDATE register
    uint8_t registerValue = MCP7940N_RegistersLocal.PWRDNDATE;
    
    // Decoding BCD
    uint8_t ones = registerValue & MCP7940N_PWRDNDATE_DATEONE;
    uint8_t tens = registerValue & MCP7940N_PWRDNDATE_DATETEN;
    tens = tens >> 4;
    
    // Returning result
    return tens * 10 + ones;
}

uint8_t MCP7940N_GetPowerFailHour(void) {
    
    // Reading PWRDNHOUR register
    uint8_t registerValue = MCP7940N_RegistersLocal.PWRDNHOUR;
    
    // Decoding BCD
    uint8_t ones = registerValue & MCP7940N_PWRDNHOUR_HRONE;
    uint8_t tens = registerValue & MCP7940N_PWRDNHOUR_HRTEN;
    tens = tens >> 4;
    
    // Returning result
    return tens * 10 + ones;
}

uint8_t MCP7940N_GetPowerFailMinute(void) {
    
    // Reading PWRDNMIN register
    uint8_t registerValue = MCP7940N_RegistersLocal.PWRDNMIN;
    
    // Decoding BCD
    uint8_t ones = registerValue & MCP7940N_PWRDNMIN_MINONE;
    uint8_t tens = registerValue & MCP7940N_PWRDNMIN_MINTEN;
    tens = tens >> 4;
    
    // Returning result
    return tens * 10 + ones;
}

MCP7940N_Datetime MCP7940N_GetPowerUpDatetime(void) {
    
    // Reading power-up timestamp registers
    MCP7940N_I2CReader(MCP7940N_I2C_ADDR, MCP7940N_PWRUPMIN, (uint8_t*) &MCP7940N_RegistersLocal.PWRUPMIN, 
                       MCP7940N_PWRUPMTH - MCP7940N_PWRUPMIN + 1);
    
    // Creating datetime structure to store the result
    MCP7940N_Datetime datetime;
    
    // Populating datetime structure
    datetime.year = 0;
    datetime.month = MCP7940N_GetPowerUpMonth();
    datetime.date = MCP7940N_GetPowerUpDate();
    datetime.weekday = MCP7940N_GetPowerUpWeekday();
    datetime.hour = MCP7940N_GetPowerUpHour();
    datetime.minute = MCP7940N_GetPowerUpMinute();
    datetime.second = 0;
    
    return datetime;
}

uint8_t MCP7940N_GetPowerUpMonth(void) {
    
    // Reading PWRUPMTH register
    uint8_t registerValue = MCP7940N_RegistersLocal.PWRDNMTH;
    
    // Decoding BCD
    uint8_t ones = registerValue & MCP7940N_PWRDNMTH_MTHONE;
    uint8_t tens = registerValue & MCP7940N_PWRDNMTH_MTHTEN;
    tens = tens >> 4;
    
    // Returning result
    return tens * 10 + ones;
}

uint8_t MCP7940N_GetPowerUpWeekday(void) {
    
    // Return weekday bits of PWRDNMTH register
    return (MCP7940N_RegistersLocal.PWRUPMTH & MCP7940N_PWRUPMTH_WKDAY) >> 5; 
}

uint8_t MCP7940N_GetPowerUpDate(void) {
    
    // Reading PWRDNDATE register
    uint8_t registerValue = MCP7940N_RegistersLocal.PWRUPDATE;
    
    // Decoding BCD
    uint8_t ones = registerValue & MCP7940N_PWRUPDATE_DATEONE;
    uint8_t tens = registerValue & MCP7940N_PWRUPDATE_DATETEN;
    tens = tens >> 4;
    
    // Returning result
    return tens * 10 + ones;
}

uint8_t MCP7940N_GetPowerUpHour(void) {
    
    // Reading PWRUPHOUR register
    uint8_t registerValue = MCP7940N_RegistersLocal.PWRUPHOUR;
    
    // Decoding BCD
    uint8_t ones = registerValue & MCP7940N_PWRUPHOUR_HRONE;
    uint8_t tens = registerValue & MCP7940N_PWRUPHOUR_HRTEN;
    tens = tens >> 4;
    
    // Returning result
    return tens * 10 + ones;
}

uint8_t MCP7940N_GetPowerUpMinute(void) {
    
    // Reading PWRUPMIN register
    uint8_t registerValue = MCP7940N_RegistersLocal.PWRUPMIN;
    
    // Decoding BCD
    uint8_t ones = registerValue & MCP7940N_PWRUPMIN_MINONE;
    uint8_t tens = registerValue & MCP7940N_PWRUPMIN_MINTEN;
    tens = tens >> 4;
    
    // Returning result
    return tens * 10 + ones;
}

void MCP7940N_ReadSRAM(uint8_t deviceAddress, unsigned char *buffer, uint8_t byteCount) {
    
    // Checking address & size
    if(deviceAddress < MCP7940N_SRAM_ADDRLOW || deviceAddress > MCP7940N_SRAM_ADDRHIGH ||
       byteCount > MCP7940N_SRAM_SIZE  || deviceAddress + byteCount > MCP7940N_SRAM_ADDRHIGH) return;
        
    // Reading SRAM
    MCP7940N_I2CReader(MCP7940N_I2C_ADDR, deviceAddress, buffer, byteCount);
}

void MCP7940N_WriteSRAM(uint8_t deviceAddress, const unsigned char *buffer, uint8_t byteCount) {
    
    // Checking address & size
    if(deviceAddress < MCP7940N_SRAM_ADDRLOW || deviceAddress > MCP7940N_SRAM_ADDRHIGH ||
       byteCount > MCP7940N_SRAM_SIZE  || deviceAddress + byteCount > MCP7940N_SRAM_ADDRHIGH) return;
    
    // Writing SRAM
    MCP7940N_I2CWriter(MCP7940N_I2C_ADDR, deviceAddress, buffer, byteCount);
}

#endif // DOXYGEN_SHOULD_SKIP_THIS

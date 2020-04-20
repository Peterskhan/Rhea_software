#pragma once
#ifndef RHEA_I2C_IMPL_H_INCLUDED
#define RHEA_I2C_IMPL_H_INCLUDED

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
 * @file    i2c_impl.h
 * @author  Peter Gyulai
 * @version 1.0.0
 * @date    2020.04.19
 * @brief   I2C driver declarations.
 * @details
 * This file contains the I2C driver interface functions that must be
 * implemented when interfacing with a new target microcontroller.
 */
    
// Standard includes
#include <stdint.h>
    

/**
 * @brief Initializes the I2C driver.
 * @todo  Implement this function to initialize the I2C driver.
 */
void rhea_i2c_initialize_impl(void);

/**
 * @brief Generates a START condition to the specified device.
 * @param address The 7-bit I2C device address.
 * @param read Zero for write, non-zero for read operation.
 * @todo  Implement this function to generate a START on the I2C bus.
 */
void rhea_i2c_masterSendStart_impl(uint8_t address, uint8_t read);

/**
 * @brief Generates a STOP condition on the I2C bus.
 * @todo  Implement this function to generate a STOP on the I2C bus.
 */
void rhea_i2c_masterSendStop_impl(void);

/**
 * @brief Reads one byte from the I2C bus.
 * @param ack Non-zero for sending ACK, or zero for sending NACK.
 * @returns The byte read from the bus.
 * @todo  Implement this function to read a byte from the I2C bus.
 */
uint8_t rhea_i2c_masterReadByte_impl(uint8_t ack);

/**
 * @brief Writes one byte to the I2C bus.
 * @param byte The byte to write to the I2C bus.
 * @todo  Implement this function to write a byte to the I2C bus.
 */
void rhea_i2c_masterWriteByte_impl(uint8_t byte);

#endif // RHEA_I2C_IMPL_H_INCLUDED
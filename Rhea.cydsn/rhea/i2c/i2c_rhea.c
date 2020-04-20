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
 * @file    i2c.c
 * @author  Peter Gyulai
 * @version 1.0.0
 * @date    2020.04.19
 * @brief   Library implementation.
 * @details
 * This file contains the function definitions used by the Rhea I2C library.
 */

// Doxygen documentation duplication suppression
#ifndef DOXYGEN_SHOULD_SKIP_THIS

// Project includes
#include "i2c.h"
#include "i2c_impl.h"

void rhea_i2c_Initialize(void) {

	// Invoking target driver
	rhea_i2c_initialize_impl();
}

void rhea_i2c_MasterSendStart(uint8_t address, uint8_t read) {

	// Invoking target driver
	rhea_i2c_masterSendStart_impl(address, read);
}


void rhea_i2c_MasterSendStop(void) {

	// Invoking target driver
	rhea_i2c_masterSendStop_impl();
}


uint8_t rhea_i2c_MasterReadByte(uint8_t ack) {

	// Invoking target driver
	return rhea_i2c_masterReadByte_impl(ack);
}

void rhea_i2c_MasterWriteByte(uint8_t byte) {

	// Invoking target driver
	rhea_i2c_masterWriteByte_impl(byte);
}

#endif // DOXYGEN_SHOULD_SKIP_THIS
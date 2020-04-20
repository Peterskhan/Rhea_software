#pragma once 
#ifndef BME280_H_INCLUDED
#define BME280_H_INCLUDED

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
 * @file    BME280.h
 * @author  Peter Gyulai
 * @version 1.1.0
 * @date    2020.04.14
 * @brief   Functions and datastructures.
 * @details
 * This file contains the declarations of the functions and datastructures 
 * available in the BME280 driver library. 
 */


// Standard includes
#include <stdint.h>

// Project includes
#include "BME280_Defs.h"
    

/**
 * @brief
 * Structure for passing the I2C bus controller functions,
 * that are used by the BME280 driver.
 * @details
 * The function pointer members must be provided for the library to
 * control trafic on the I2C bus. The library is independent from the
 * specific I2C implementation and only needs these callbacks to operate.
 * If the I2C implementation does not provide functions with these specific
 * function signatures, consider creating proxy functions to pass.
 */
typedef struct BME280_I2CControllerStruct {

	/**
	 * @brief Pointer to a function that generates a START condition.
	 * @param address The 7-bit I2C device address.
	 * @param read Zero for write, non-zero for read operation.
	 */
	void (*MasterSendStart)(uint8_t address, uint8_t read);

	/**
	 * @brief Pointer to a function that generates a STOP condition.
	 */
	void (*MasterSendStop)(void);

	/**
	 * @brief Pointer to a function that writes one byte to the bus.
	 * @param byte The byte to write to the I2C bus.
	 */
	void (*MasterWriteByte)(uint8_t byte);
    
    /**
     * @brief Pointer to a function that reads one byte from the bus.
     * @param ack Non-zero for ACK, or zero for NACK.
     * @returns The byte read from the bus.
     */
    uint8_t (*MasterReadByte)(uint8_t ack);

} BME280_I2CControllerStruct;

/**
 * @brief Installs the I2C bus controller structure holding function pointers to the bus control methods.
 * @param controller The structure containing control function pointers.
 */
void BME280_SetI2CController(BME280_I2CControllerStruct controller);

/**
 * @brief
 * This structure is used as a local in-memory copy of the BME280's register set.
 * 
 * @details
 * Specific sections of this structure (measurement and configuration block) are directly used as
 * a bytewise copy of the specific registers, and is marked with the \a packed GCC attribute. Names
 * of the struct members are mostly identical to the corresponding register names in the Bosch datasheet.
 * The structure also holds the parsed values of the calibration constants read in #BME280_Init().
 * There should only be one actively used instance of this struct, which the library automatically 
 * declares. To get a pointer to this instance see #BME280_GetLocalRegisters(). 
 * For more details check out the official product page and documentation.\n\n
 * <b>Product Page: </b> https://www.bosch-sensortec.com/products/environmental-sensors/humidity-sensors-bme280/ \n
 * <b>Datasheet (PDF): </b> https://www.bosch-sensortec.com/media/boschsensortec/downloads/datasheets/bst-bme280-ds002.pdf \n \n
 * 
 * \image html bme280_regs.png "Registers of the BME280" width=600px
 */
struct BME280_RegisterStruct {

    /** @{ @name Measurement registers */
    uint8_t PRESS_MSB;      /**< @brief Holds the most significant byte of the pressure. */
    uint8_t PRESS_LSB;      /**< @brief Holds the least significant byte of the pressure. */
    uint8_t PRESS_XLSB;     /**< @brief Holds the extended least significant byte of the pressure. */
    uint8_t TEMP_MSB;       /**< @brief Holds the most significant byte of the temperature. */
    uint8_t TEMP_LSB;       /**< @brief Holds the least significant byte of the temperature. */
    uint8_t TEMP_XLSB;      /**< @brief Holds the extended least significant byte of the temperature. */
    uint8_t HUM_MSB;        /**< @brief Holds the most significant byte of the humidity. */
    uint8_t HUM_LSB;        /**< @brief Holds the least significant byte of the humidity. */
    /** @} */

    /** @{ @name Configuration registers */
    uint8_t CTRL_HUM;       /**< @brief Holds the configuration for humidity measurement. */
    uint8_t STATUS;         /**< @brief Holds measurement and update status information. */
    uint8_t CTRL_MEAS;      /**< @brief Holds the configuration for temperature and pressure 
                             *          measurements and the mode of operation.
                             */
    uint8_t CONFIG;         /**< @brief Hold the configuration for standby time, filtering
                             *          and SPI 3-wire mode.
                             */
    /** @} */

    /** @{ @name Compensation values */
    uint16_t dig_T1;        /**< @brief Holds the dig_T1 temperature calibration constant. */
    int16_t  dig_T2;        /**< @brief Holds the dig_T2 temperature calibration constant. */
    int16_t  dig_T3;        /**< @brief Holds the dig_T3 temperature calibration constant. */
    uint16_t dig_P1;        /**< @brief Holds the dig_P1 pressure calibration constant.    */
    int16_t  dig_P2;        /**< @brief Holds the dig_P2 pressure calibration constant.    */
    int16_t  dig_P3;        /**< @brief Holds the dig_P3 pressure calibration constant.    */
    int16_t  dig_P4;        /**< @brief Holds the dig_P4 pressure calibration constant.    */
    int16_t  dig_P5;        /**< @brief Holds the dig_P5 pressure calibration constant.    */
    int16_t  dig_P6;        /**< @brief Holds the dig_P6 pressure calibration constant.    */
    int16_t  dig_P7;        /**< @brief Holds the dig_P7 pressure calibration constant.    */
    int16_t  dig_P8;        /**< @brief Holds the dig_P8 pressure calibration constant.    */
    int16_t  dig_P9;        /**< @brief Holds the dig_P9 pressure calibration constant.    */
    uint8_t  dig_H1;        /**< @brief Holds the dig_H1 humidity calibration constant.    */
    int16_t  dig_H2;        /**< @brief Holds the dig_H2 humidity calibration constant.    */
    uint8_t  dig_H3;        /**< @brief Holds the dig_H3 humidity calibration constant.    */
    int16_t  dig_H4;        /**< @brief Holds the dig_H4 humidity calibration constant.    */
    int16_t  dig_H5;        /**< @brief Holds the dig_H5 humidity calibration constant.    */
    int8_t   dig_H6;        /**< @brief Holds the dig_H6 humidity calibration constant.    */
    int32_t  t_fine;        /**< @brief Holds the fine temperature compensation value.     */
    /** @} */
} __attribute__ ((packed));

/** @cond */
typedef struct BME280_RegisterStruct BME280_RegisterStruct;
/** @endcond */

/** 
 * @brief Initializes the device.
 * @details
 * The BME280_Init() function checks the chip ID of the
 * device and ensures the correct device is being selected.
 * Then proceeds to read and store calibration data of the
 * device and finally performs a soft-reset.
 */
void BME280_Init(void);

/** @brief Resets the device from software. */
void BME280_Reset(void);

/**
 * @brief
 * Updates the measurement registers of the local copy from 
 * the physical device.
 *
 * @details
 * Most library functions are working on a local copy of the 
 * device registers stored in memory. To get the latest data 
 * out of the device #BME280_ReadRegisters() should be called.
 * This is necessary for data consistency and efficiency 
 * reasons, it is faster to read all of the registers of the
 * device at the same time then reading them individually,
 * and data consistency is also ensured, as the visible
 * registers of the device are frozen during a sequential
 * read operation. Please note, that measurement functions 
 * provide a flag that indicates if the registers should be 
 * read before returning the data, and configuration setter 
 * functions flush the appropriate registers automatically.
 */
void BME280_ReadRegisters(void);

/**
 * @brief
 * Updates the configuration registers of the physical device from 
 * the local copy stored in memory.
 *  
 * @details
 * Most library functions are working on a local copy of the
 * device registers stored in memory. To reflect any changes
 * in the local register values, the device must be updated
 * via the I2C bus. This is necessary for efficiency and
 * safety reasons, it is faster to write all of the registers
 * of the device at the same time then writing them individually,
 * and safety is also ensured by avoiding data corruption.
 * Measurement functions provide a flag that indicates if the
 * registers should be read before returning the data, and 
 * configuration setter functions flush the appropriate registers
 * automatically. #BME280_WriteRegisters() can be used when 
 * operating manually on the local register structure to batch
 * update the configuration registers after modifying changes.
 */
void BME280_WriteRegisters(void);

/**
 * @brief Returns a pointer to the local register structure.
 * 
 * @details
 * The individual registers can be accessed via the returned
 * structure manually, but using the library interface is highly 
 * recommended.
 */
BME280_RegisterStruct* BME280_GetLocalRegisters(void);

/**
 * @brief Returns the temperature in degrees Celsius.
 * 
 * @details
 * This function saves an intermediate version of the measured
 * temperature used in compensation of pressure and humidity
 * measurements. For those measurements to be fully accurate,
 * #BME280_GetTemperatureCelsius() or #BME280_GetTemperatureFahrenheit()
 * must be called first.
 *
 * @param readNow Non-zero for reading the physical measurement registers
 * first, zero for working with the preloaded register values.
 * 
 * @return The temperature in degrees Celsius.
 */
int8_t BME280_GetTemperatureCelsius(uint8_t readNow);

/**
 * @brief Returns the temperature in degrees Fahrenheit.
 * 
 * @details
 * This function is a proxy to #BME280_GetTemperatureCelsius(),
 * only it converts the degrees Celsius results to degrees
 * Fahrenheit. See #BME280_GetTemperatureCelsius() for usage
 * limitations.
 *
 * @param readNow Non-zero for reading the physical measurement registers
 * first, zero for working with the preloaded register values.
 * 
 * @return The temperature in degrees Fahrenheit.
 */
int8_t BME280_GetTemperatureFahrenheit(uint8_t readNow);

/**
 * @brief Returns the pressure in Pascals.
 * 
 * @details
 * For pressure compensation by temperature to be fully accurate,
 * either #BME280_GetTemperatureCelsius() or #BME280_GetTemperatureFahrenheit()
 * must be called prior to this function.
 *
 * @param readNow Non-zero for reading the physical measurement registers
 * first, zero for working with the preloaded register values.
 * 
 * @return The pressure in Pascals.
 */
uint32_t BME280_GetPressure(uint8_t readNow);

/**
 * @brief Returns the relative humidity in percents.
 * 
 * @details
 * For humidity compensation by temperature to be fully accurate,
 * either #BME280_GetTemperatureCelsius() or #BME280_GetTemperatureFahrenheit()
 * must be called prior to this function.
 *
 * @param readNow Non-zero for reading the physical measurement registers
 * first, zero for working with the preloaded register values.
 * 
 * @return The relative humidity in percents.
 */
uint8_t BME280_GetHumidity(uint8_t readNow);

/**
 * @brief Returns the maximum measurement period based on current settings.
 * @return The maximum measurement period in milliseconds.
 */
uint8_t BME280_GetMeasurementDelay(void);

/**
 * @brief Returns the humidity measurement mode.
 * @return
 * - #BME280_HUMIDITY_OVERSAMPLING_1X
 * - #BME280_HUMIDITY_OVERSAMPLING_2X
 * - #BME280_HUMIDITY_OVERSAMPLING_4X
 * - #BME280_HUMIDITY_OVERSAMPLING_8X
 * - #BME280_HUMIDITY_OVERSAMPLING_16X
 * - #BME280_HUMIDITY_DISABLED
 */
uint8_t BME280_GetHumidityMode(void);

/**
 * @brief Sets the humidity measurement mode.
 * @param [in] mode
 * - #BME280_HUMIDITY_OVERSAMPLING_1X
 * - #BME280_HUMIDITY_OVERSAMPLING_2X
 * - #BME280_HUMIDITY_OVERSAMPLING_4X
 * - #BME280_HUMIDITY_OVERSAMPLING_8X
 * - #BME280_HUMIDITY_OVERSAMPLING_16X
 * - #BME280_HUMIDITY_DISABLED
 */
void BME280_SetHumidityMode(uint8_t mode);

/**
 * @brief Returns the temperature measurement mode.
 * @return
 * - #BME280_TEMPERATURE_OVERSAMPLING_1X
 * - #BME280_TEMPERATURE_OVERSAMPLING_2X
 * - #BME280_TEMPERATURE_OVERSAMPLING_4X
 * - #BME280_TEMPERATURE_OVERSAMPLING_8X
 * - #BME280_TEMPERATURE_OVERSAMPLING_16X
 * - #BME280_TEMPERATURE_DISABLED
 */
uint8_t BME280_GetTemperatureMode(void);

/**
 * @brief Sets the temperature measurement mode.
 * @param [in] mode
 * - #BME280_TEMPERATURE_OVERSAMPLING_1X
 * - #BME280_TEMPERATURE_OVERSAMPLING_2X
 * - #BME280_TEMPERATURE_OVERSAMPLING_4X
 * - #BME280_TEMPERATURE_OVERSAMPLING_8X
 * - #BME280_TEMPERATURE_OVERSAMPLING_16X
 * - #BME280_TEMPERATURE_DISABLED
 */
void BME280_SetTemperatureMode(uint8_t mode);

/**
 * @brief Returns the pressure measurement mode.
 * @return
 * - #BME280_PRESSURE_OVERSAMPLING_1X
 * - #BME280_PRESSURE_OVERSAMPLING_2X
 * - #BME280_PRESSURE_OVERSAMPLING_4X
 * - #BME280_PRESSURE_OVERSAMPLING_8X
 * - #BME280_PRESSURE_OVERSAMPLING_16X
 * - #BME280_PRESSURE_DISABLED
 */
uint8_t BME280_GetPressureMode(void);

/**
 * @brief Sets the pressure measurement mode.
 * @param [in] mode
 * - #BME280_PRESSURE_OVERSAMPLING_1X
 * - #BME280_PRESSURE_OVERSAMPLING_2X
 * - #BME280_PRESSURE_OVERSAMPLING_4X
 * - #BME280_PRESSURE_OVERSAMPLING_8X
 * - #BME280_PRESSURE_OVERSAMPLING_16X
 * - #BME280_PRESSURE_DISABLED
 */
void BME280_SetPressureMode(uint8_t mode);

/**
 * @brief Returns whether the device is currently measuring.
 * @return
 * - #BME280_MEASURING
 * - #BME280_NOT_MEASURING
 */
uint8_t BME280_IsMeasuring(void);

/**
 * @brief 
 * Returns whether the device is currently updating from it's 
 * image registers in non-volatile memory.
 * @return 
 * - #BME280_IMAGE_UPDATING
 * - #BME280_IMAGE_NOT_UPDATING
 */
uint8_t BME280_IsUpdating(void);

/**
 * @brief Returns the current measurement mode of the device.
 * @return 
 * - #BME280_MODE_SLEEP
 * - #BME280_MODE_FORCED
 * - #BME280_MODE_NORMAL
 */
uint8_t BME280_GetMeasurementMode(void);

/**
 * @brief Sets the measurement mode of the device.
 * @param [in] mode
 * - #BME280_MODE_SLEEP
 * - #BME280_MODE_FORCED
 * - #BME280_MODE_NORMAL
 */
void BME280_SetMeasurementMode(uint8_t mode);

/**
 * @brief Returns the current standby time for Normal mode.
 * @return 
 * - #BME280_STANDBY_5MS
 * - #BME280_STANDBY_10MS
 * - #BME280_STANDBY_20MS
 * - #BME280_STANDBY_62_5MS
 * - #BME280_STANDBY_125MS
 * - #BME280_STANDBY_250MS
 * - #BME280_STANDBY_500MS
 * - #BME280_STANDBY_1000MS
 */
uint8_t BME280_GetStandbyTime(void);

/**
 * @brief Sets the standby time for Normal mode.
 * @param [in] standby
 * - #BME280_STANDBY_5MS
 * - #BME280_STANDBY_10MS
 * - #BME280_STANDBY_20MS
 * - #BME280_STANDBY_62_5MS
 * - #BME280_STANDBY_125MS
 * - #BME280_STANDBY_250MS
 * - #BME280_STANDBY_500MS
 * - #BME280_STANDBY_1000MS
 */
void BME280_SetStandbyTime(uint8_t standby);

/**
 * @brief Gets the IIR filter coefficient of the device.
 * @return
 * - #BME280_FILTER_COEFFICIENT_2
 * - #BME280_FILTER_COEFFICIENT_4
 * - #BME280_FILTER_COEFFICIENT_8
 * - #BME280_FILTER_COEFFICIENT_16
 * - #BME280_FILTER_OFF
 */
uint8_t BME280_GetFilterMode(void);

/**
 * @brief Sets the IIR filter coefficient of the device.
 * @param [in] mode
 * - #BME280_FILTER_COEFFICIENT_2
 * - #BME280_FILTER_COEFFICIENT_4
 * - #BME280_FILTER_COEFFICIENT_8
 * - #BME280_FILTER_COEFFICIENT_16
 * - #BME280_FILTER_OFF
 */
void BME280_SetFilterMode(uint8_t mode);

/** @brief Enables SPI 3-wire mode. */
void BME280_EnableSPI3Wire(void);

/** @brief Disables SPI 3-wire mode. */
void BME280_DisableSPI3Wire(void);

/** 
 * @brief Returns whether SPI 3-wire mode is enabled.
 * @return
 * - #BME280_SPI3WIRE_ENABLED
 * - #BME280_SPI3WIRE_DISABLED
 */
uint8_t BME280_IsSPI3WireEnabled();

#endif // BME280_H_INCLUDED

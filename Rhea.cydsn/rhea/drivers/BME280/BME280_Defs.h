#pragma once
#ifndef BME280_DEFS_H_INCLUDED
#define BME280_DEFS_H_INCLUDED

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
 * @file    BME280_Defs.h
 * @author  Peter Gyulai
 * @version 1.0.2
 * @date    2020.03.17
 * @brief   Macro definitions.
 * @details
 * This header file contains all the macro definitions used by the BME280 driver library.
 * These macros are used throughout the implementation and accessible by the end user. The
 * general convention is that all macros are preceeded by the BME280_ prefix.
 */

/** @{ @name I2C parameters */
/** @brief Defines the default I2C address. */
#define BME280_I2C_ADDR             (uint8_t)(0x76)
/** @} */

/** @{ @name Register addresses */
/** @brief Address of HUM_LSB register. */
#define BME280_HUM_LSB              (uint8_t)(0xFE)
/** @brief Address of HUM_MSB register. */
#define BME280_HUM_MSB              (uint8_t)(0xFD)
/** @brief Address of TEMP_XLSB register. */
#define BME280_TEMP_XLSB            (uint8_t)(0xFC)
/** @brief Address of TEMP_LSB register. */
#define BME280_TEMP_LSB             (uint8_t)(0xFB)
/** @brief Address of TEMP_MSB register. */
#define BME280_TEMP_MSB             (uint8_t)(0xFA)
/** @brief Address of PRESS_XLSB register. */
#define BME280_PRESS_XLSB           (uint8_t)(0xF9)
/** @brief Address of PRESS_LSB register. */
#define BME280_PRESS_LSB            (uint8_t)(0xF8)
/** @brief Address of PRESS_MSB register. */
#define BME280_PRESS_MSB            (uint8_t)(0xF7)
/** @brief Address of CONFIG register. */
#define BME280_CONFIG               (uint8_t)(0xF5)
/** @brief Address of CTRL_MEAS register. */
#define BME280_CTRL_MEAS            (uint8_t)(0xF4)
/** @brief Address of STATUS register. */
#define BME280_STATUS               (uint8_t)(0xF3)
/** @brief Address of CTRL_HUM register. */
#define BME280_CTRL_HUM             (uint8_t)(0xF2)
/** @brief Address of RESET register. */
#define BME280_RESET                (uint8_t)(0xE0)
/** @brief Address of ID register. */
#define BME280_ID                   (uint8_t)(0xD0)
/** @} */

/** @{ @name Register bitmasks */
/** @brief Bitmask for OSRS_H bits of CTRL_HUM register. */
#define BME280_CTRL_HUM_OSRS_H      (uint8_t)(0x07)
/** @brief Bitmask for OSRS_T bits of CTRL_MEAS register. */
#define BME280_CTRL_MEAS_OSRS_T     (uint8_t)(0xE0)
/** @brief Bitmask for OSRS_P bits of CTRL_MEAS register. */
#define BME280_CTRL_MEAS_OSRS_P     (uint8_t)(0x1C)
/** @brief Bitmask for MODE bits of CTRL_MEAS register. */
#define BME280_CTRL_MEAS_MODE       (uint8_t)(0x03)
/** @brief Bitmask for MEASURING bit of the STATUS register. */
#define BME280_STATUS_MEASURING     (uint8_t)(0x08)
/** @brief Bitmask for IM_UPDATE bit of the STATUS register. */
#define BME280_STATUS_IM_UPDATE     (uint8_t)(0x01)
/** @brief Bitmask for T_SB bits of the CONFIG register. */
#define BME280_CONFIG_T_SB          (uint8_t)(0xE0)
/** @brief Bitmask for FILTER bits of the CONFIG register. */
#define BME280_CONFIG_FILTER        (uint8_t)(0x1C)
/** @brief Bitmask for SPI33W_EN bit of the CONFIG register. */
#define BME280_CONFIG_SPI3W_EN      (uint8_t)(0x01)
/** @} */

/** @{ @name Calibration parameters */
/** @brief Defines the starting address of lower calibration data registers. */
#define BME280_CALIBRATION_REGS_LOW             (uint8_t)(0x88)
/** @brief Defines the number of lower calibration data registers. */
#define BME280_CALIBRATION_REGS_LOW_COUNT       (uint8_t)(26)
/** @brief Defines the starting address of higher calibration data registers. */
#define BME280_CALIBRATION_REGS_HIGH            (uint8_t)(0xE1)
/** @brief Defines the number of higher calibration data registers. */
#define BME280_CALIBRATION_REGS_HIGH_COUNT      (uint8_t)(7)
/** @} */



/** @brief Defines the expected chip ID of the BME280. */
#define BME280_CHIP_ID                          (uint8_t)(0x60)

/** @brief Defines the specific reset byte for software reset. */
#define BME280_RESET_WORD                       (uint8_t)(0xB6)

/** @{ @name Humidity measurement modes */
/** @brief Defines humidity 1X oversampling mode. */
#define BME280_HUMIDITY_OVERSAMPLING_1X         (uint8_t)(0x01)
/** @brief Defines humidity 2X oversampling mode. */
#define BME280_HUMIDITY_OVERSAMPLING_2X         (uint8_t)(0x02)
/** @brief Defines humidity 4X oversampling mode. */
#define BME280_HUMIDITY_OVERSAMPLING_4X         (uint8_t)(0x03)
/** @brief Defines humidity 8X oversampling mode. */
#define BME280_HUMIDITY_OVERSAMPLING_8X         (uint8_t)(0x04)
/** @brief Defines humidity 16X oversampling mode. */
#define BME280_HUMIDITY_OVERSAMPLING_16X        (uint8_t)(0x05)
/** @brief Defines humidity measurements disabled. */
#define BME280_HUMIDITY_DISABLED                (uint8_t)(0x00)
/** @} */

/** @{ @name Temperature measurement modes */
/** @brief Defines temperature 1X oversampling mode. */
#define BME280_TEMPERATURE_OVERSAMPLING_1X      (uint8_t)(0x20)
/** @brief Defines temperature 2X oversampling mode. */
#define BME280_TEMPERATURE_OVERSAMPLING_2X      (uint8_t)(0x40)
/** @brief Defines temperature 4X oversampling mode. */
#define BME280_TEMPERATURE_OVERSAMPLING_4X      (uint8_t)(0x60)
/** @brief Defines temperature 8X oversampling mode. */
#define BME280_TEMPERATURE_OVERSAMPLING_8X      (uint8_t)(0x80)
/** @brief Defines temperature 16X oversampling mode. */
#define BME280_TEMPERATURE_OVERSAMPLING_16X     (uint8_t)(0xA0)
/** @brief Defines temperature measurements disabled. */
#define BME280_TEMPERATURE_DISABLED             (uint8_t)(0x00)
/** @} */

/** @{ @name Pressure measurement modes */
/** @brief Defines pressure 1X oversampling mode. */
#define BME280_PRESSURE_OVERSAMPLING_1X         (uint8_t)(0x04)
/** @brief Defines pressure 2X oversampling mode. */
#define BME280_PRESSURE_OVERSAMPLING_2X         (uint8_t)(0x08)
/** @brief Defines pressure 4X oversampling mode. */
#define BME280_PRESSURE_OVERSAMPLING_4X         (uint8_t)(0x0C)
/** @brief Defines pressure 8X oversampling mode. */
#define BME280_PRESSURE_OVERSAMPLING_8X         (uint8_t)(0x10)
/** @brief Defines pressure 16X oversampling mode. */
#define BME280_PRESSURE_OVERSAMPLING_16X        (uint8_t)(0x14)
/** @brief Defines pressure measurements disabled. */
#define BME280_PRESSURE_DISABLED                (uint8_t)(0x00)
/** @} */

/** @{ @name Measurement status */
/** @brief Defines that the device is currently measuring. */
#define BME280_MEASURING                        (uint8_t)(0x08)
/** @brief Defines that the device is currently not measuring. */
#define BME280_NOT_MEASURING                    (uint8_t)(0x00)
/** @} */

/** @{ @name Image register status */
/** @brief Defines that the image registers are updating. */
#define BME280_IMAGE_UPDATING                   (uint8_t)(0x01)
/** @brief Defines that the image registers are not updating. */
#define BME280_IMAGE_NOT_UPDATING               (uint8_t)(0x00)
/** @} */

/** @{ @name Measurement modes */
/** @brief Define for Sleep mode. */
#define BME280_MODE_SLEEP                       (uint8_t)(0x00)
/** @brief Define for Forced mode. */
#define BME280_MODE_FORCED                      (uint8_t)(0x01)
/** @brief Define for Normal mode. */
#define BME280_MODE_NORMAL                      (uint8_t)(0x11)
/** @} */

/** @{ @name Standby intervals */
/** @brief Defines 5ms of standby time. */
#define BME280_STANDBY_5MS                      (uint8_t)(0x00)
/** @brief Defines 10ms of standby time. */
#define BME280_STANDBY_10MS                     (uint8_t)(0xC0)
/** @brief Defines 20ms of standby time. */
#define BME280_STANDBY_20MS                     (uint8_t)(0xE0)
/** @brief Defines 62.5ms of standby time. */
#define BME280_STANDBY_62_5MS                   (uint8_t)(0x20)
/** @brief Defines 125ms of standby time. */
#define BME280_STANDBY_125MS                    (uint8_t)(0x40)
/** @brief Defines 250ms of standby time. */
#define BME280_STANDBY_250MS                    (uint8_t)(0x60)
/** @brief Defines 500ms of standby time. */
#define BME280_STANDBY_500MS                    (uint8_t)(0x80)
/** @brief Defines 1000ms of standby time. */
#define BME280_STANDBY_1000MS                   (uint8_t)(0xA0)
/** @} */

/** @{ @name IIR filter coefficients */
/** @brief Defines IIR filter coefficient as 2. */
#define BME280_FILTER_COEFFICIENT_2             (uint8_t)(0x04)
/** @brief Defines IIR filter coefficient as 4. */
#define BME280_FILTER_COEFFICIENT_4             (uint8_t)(0x08)
/** @brief Defines IIR filter coefficient as 8. */
#define BME280_FILTER_COEFFICIENT_8             (uint8_t)(0x0C)
/** @brief Defines IIR filter coefficient as 16. */
#define BME280_FILTER_COEFFICIENT_16            (uint8_t)(0x10)
/** @brief Defines IIR filter as disabled. */
#define BME280_FILTER_OFF                       (uint8_t)(0x00)
/** @} */

/** @{ @name SPI 3-wire interface */
/** @brief Define for SPI 3-wire mode enabled. */
#define BME280_SPI3WIRE_ENABLED                 (uint8_t)(0x01)
/** @brief Define for SPI 3-wire mode disabled. */
#define BME280_SPI3WIRE_DISABLED                (uint8_t)(0x00)
/** @} */

#endif // BME280_DEFS_H_INCLUDED

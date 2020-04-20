#pragma once
#ifndef RHEA_SENSOR_H_INCLUDED
#define RHEA_SENSOR_H_INCLUDED

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
 * @file    sensor.h
 * @author  Peter Gyulai
 * @version 1.0.0
 * @date    2020.04.20
 * @brief   Sensor utilities.
 * @details
 * This file contains the sensor utility functions that interface sensor drivers.
 */
    
// Project includes
#include "sensor_config.h"
    
    
/**
 * @brief Defines a function that performs a sensor measurement.
 * @returns The result of the measurement.
 */
typedef RHEA_SENSOR_MEASUREMENT_TYPE (*rhea_sensor_measurementFunction)(void);

/**
 * @brief Defines a function that queries an attribute.
 * @returns The current value of the attribute.
 */
typedef RHEA_SENSOR_ATTRIBUTE_TYPE (*rhea_sensor_attributeGetter)(void);

/**
 * @brief Defines a function the modifies an attribute.
 * @param [in] The new attribute value.
 */
typedef void (*rhea_sensor_attributeSetter)(RHEA_SENSOR_ATTRIBUTE_TYPE);

/**
 * @brief Describes a sensor measurement entry.
 * @details Sensor devices are used to perform parameter measurements. Each 
 *          sensor can measure multiple environmental parameters. For this
 *          reason a measurement is identified by both the name of the sensor
 *          perfoming it and the name of the parameter being measured. The
 *          measurement results are buffered internally, and can be acquired
 *          by calling #rhea_sensor_GetMeasurement(). Measurements are performed
 *          by calling the measurement function provided. The type of the
 *          measurement results can be configured in the sensor configuration file.
 *          Measurements can be automatically performed periodically by specifying
 *          the measurement period in milliseconds upon registering the measurement.
 *          On-demand measurements can be performed by setting the period to zero
 *          and performing the measurement using #rhea_sensor_TakeMeasurement().
 *          Manually performing a measurement does not interfere with the periodic
 *          execution, and resets the timer scheduling the measurement.
 *
 * @see RHEA_SENSOR_MEASUREMENT_TYPE
 * @see rhea_sensor_measurementFunction
 */
struct rhea_sensor_measurementDescriptor {
    const char *                    device;                 /**< The name of the sensor device. */
    const char *                    parameter;              /**< The name of the parameter being measured. */
    uint64_t                        period;                 /**< The measurement period in milliseconds. */
    uint64_t                        currentPeriod;          /**< The counter counting since the last measurement. */
    RHEA_SENSOR_MEASUREMENT_TYPE    lastMeasurement;        /**< The last parameter value measured. */
    rhea_sensor_measurementFunction measurementFunction;    /**< The function performing the measurement. */
};

/**
 * @brief Describes a sensor attribute entry.
 * @details Sensor devices may have specific attributes and options associated.
 *          Attributes can be used to describe these properties. An attribute is
 *          identified by the name of the device, and the name of the attribute.
 *          Attributes can be directly or indirectly associated with the sensor.
 *          Direct attributes are such that the sensor itself knows about, for eg.
 *          it is a value in a configuration register. Such attributes need to be
 *          communicated to the sensor device, for which a setter function can be
 *          provided. Direct attributes may represent status information which can
 *          change independently from software. For such attributes a getter function
 *          can be provided. Indirect attributes are not in tight coupling with the
 *          devices, for eg. the measurement interval forced by a periodic interrupt
 *          source, only depending on software, independent from the sensor itself.
 *          Such attributes should not change outside the software and can be buffered.
 *          When registering an attribute, it is treated as direct or indirect depending 
 *          on whether a getter or setter is provided. The type of the attribute values
 *          can be configured in the sensor configuration file.
 * 
 * @see RHEA_SENSOR_ATTRIBUTE_TYPE
 * @see rhea_sensor_attributeGetter
 * @see rhea_sensor_attributeSetter
 */
struct rhea_sensor_attributeDescriptor {
    const char *                device;         /**< The name of the sensor device. */
    const char *                attributeName;  /**< The name of the attribute. */
    RHEA_SENSOR_ATTRIBUTE_TYPE  attributeValue; /**< The last set value of the attribute. */
    rhea_sensor_attributeGetter getterFunction; /**< Optional getter function for the attribute. */
    rhea_sensor_attributeSetter setterFunction; /**< Optional setter function for the attribute. */
};
    
/**
 * @brief Initializes the sensor library.
 */
void rhea_sensor_Initialize(void);

/**
 * @brief Registers a new measurement to the measurement registry.
 * @param [in] device The name of the sensor device performing the measurement.
 * @param [in] parameter The name of the parameter being measured by the sensor.
 * @param [in] function The function performing the measurement.
 */
void rhea_sensor_AddMeasurement(const char *device, 
                                const char *parameter, 
                                uint64_t    period,
                                rhea_sensor_measurementFunction function);

/**
 * @brief Performs the specified measurement, and updates the latest measured value.
 * @param [in] device The name of the sensor device performing the measurement.
 * @param [in] parameter The name of the parameter being measured by the sensor.
 */
void rhea_sensor_TakeMeasurement(const char *device,
                                 const char *parameter);

/**
 * @brief Returns the latest measured value of the specified measurement.
 * @param [in] device The name of the sensor device performing the measurement.
 * @param [in] parameter The name of the parameter being measured by the sensor.
 * @returns The latest measured value of the specified measurement.
 */
RHEA_SENSOR_MEASUREMENT_TYPE rhea_sensor_GetMeasurement(const char *device,
                                                        const char *parameter);

/**
 * @brief Returns the period of the specified measurement.
 * @param [in] device The name of the sensor device performing the measurement.
 * @param [in] parameter The name of the parameter being measured by the sensor.
 * @returns The measurement period value in milliseconds.
 */
uint64_t rhea_sensor_GetMeasurementPeriod(const char *device,
                                          const char *parameter);

/**
 * @brief Modifies the period of the specified measurement.
 * @param [in] device The name of the sensor device performing the measurement.
 * @param [in] parameter The name of the parameter being measured by the sensor.
 * @param [in] period The new measurement period value in milliseconds.
 */
void rhea_sensor_SetMeasurementPeriod(const char *device,
                                      const char *parameter,
                                      uint64_t    period);

/**
 * @brief Registers an attribute to the specified device.
 * @param [in] device The name of the sensor device having the attribute.
 * @param [in] attribute The name of the attribute.
 * @param [in] getter Optional getter for the attribute if it can change on it's own.
 * @param [in] setter Optional setter for the attribute if it is an external value.
 */
void rhea_sensor_AddAttribute(const char *device, 
                              const char *attribute, 
                              rhea_sensor_attributeGetter getter,
                              rhea_sensor_attributeSetter setter);

/**
 * @brief Returns the value of the specified attribute, optionally by
 *        invoking the getter when provided.
 * @param [in] device The name of the sensor device having the attribute.
 * @param [in] attribute The name of the attribute.
 * @returns The current value of the attribute.
 */
RHEA_SENSOR_ATTRIBUTE_TYPE rhea_sensor_GetAttribute(const char *device,
                                                    const char *attribute);

/**
 * @brief Modifies the value of the specified attribute, optionally by 
 *        invoking the setter when provided.
 * @param [in] device The name of the sensor device having the attribute.
 * @param [in] attribute The name of the attribute.
 * @param [in] value The new value of the attribute.
 */
void rhea_sensor_SetAttribute(const char *device,
                              const char *attribute,
                              RHEA_SENSOR_ATTRIBUTE_TYPE value);

#endif // RHEA_SENSOR_H_INCLUDED
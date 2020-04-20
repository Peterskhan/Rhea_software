#pragma once
#ifndef MCP7940N_H_INCLUDED
#define MCP7940N_H_INCLUDED

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
 * @file    MCP7940N.h
 * @author  Peter Gyulai
 * @version 1.1.0
 * @date    2020.04.14
 * @brief   Functions and datastructures.
 * @details
 * This file contains the declarations of the functions and datastructures 
 * available in the MCP7940N driver library. 
 */


// Standard includes
#include <stdint.h>

// Project includes
#include "MCP7940N_Defs.h"
    
    
typedef struct MCP7940N_Datetime {
    uint16_t year;
    uint8_t  month;
    uint8_t  date;
    uint8_t  weekday;
    uint8_t  hour;
    uint8_t  minute;
    uint8_t  second;
} MCP7940N_Datetime;

/**
 * @brief
 * Structure for passing the I2C bus controller functions,
 * that are used by the MCP7940N driver.
 * @details
 * The function pointer members must be provided for the library to
 * control trafic on the I2C bus. The library is independent from the
 * specific I2C implementation and only needs these callbacks to operate.
 * If the I2C implementation does not provide functions with these specific
 * function signatures, consider creating proxy functions to pass.
 */
typedef struct MCP7940N_I2CControllerStruct {

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

} MCP7940N_I2CControllerStruct;

/**
 * @brief Installs the I2C bus controller structure holding function pointers to the bus control methods.
 * @param controller The structure containing control function pointers.
 */
void MCP7940N_SetI2CController(MCP7940N_I2CControllerStruct controller);

/**
 * @brief 
 * This structure is used as a local in-memory copy of the MCP7940N's register set.  
 * 
 * @details
 * The structure is directly used as a bytewise copy of the specific registers, and
 * is marked with the \a packed GCC attribute. Names of the struct members are directly
 * corresponding with the register names depicted in the Microchip official datasheet.
 * There should only be one actively used instance of this struct, which the library 
 * automatically declares. To get a pointer to this instance see #MCP7940N_GetLocalRegisters(). 
 * For more details check out the official product page and documentation.\n\n
 * <b>Product Page: </b> https://www.microchip.com/wwwproducts/en/MCP7940N \n
 * <b>Datasheet (PDF): </b> http://ww1.microchip.com/downloads/en/DeviceDoc/MCP7940N-Battery-Backed-I2C-RTCC-with-SRAM-20005010G.pdf \n \n
 * 
 * \image html mcp7940n_regs.png "Registers of the MCP7940N" width=600px
 **/
struct MCP7940N_RegisterStruct {
    
    /** @{ @name Timekeeping registers */
    uint8_t RTCSEC;     /**< @brief Holds the current seconds in BCD format and the \a ST bit for starting the oscillator. */
    uint8_t RTCMIN;     /**< @brief Holds the current minutes in BCD format. */
    uint8_t RTCHOUR;    /**< @brief Holds the current hours in 12+AMPM / 24 hour BCD format. */
    uint8_t RTCWKDAY;   /**< @brief Holds the current weekdays and the <i> battery enable, power-failed indicator and oscillator running bits. </i> */
    uint8_t RTCDATE;    /**< @brief Holds the current date in BCD format. */
    uint8_t RTCMTH;     /**< @brief Holds the current month in BCD format and the <i> leapyear incdicator bit. </i> */
    uint8_t RTCYEAR;    /**< @brief Holds the current year in BCD format as an offset to 2000. */
    uint8_t CONTROL;    /**< @brief Holds configuration and control options: <i> squarewave frequency, coarse trimming enable, external 
                         *   clock enable, alarm enable, squarewave enable and GPIO output. </i>
                         */
    uint8_t OSCTRIM;    /**< @brief Holds the oscillator trimming value. */
    /** @} */

    /** @{ @name Alarm registers */
    uint8_t ALM0SEC;    /**< @brief Holds the Alarm 0. seconds in BCD format. */
    uint8_t ALM0MIN;    /**< @brief Holds the Alarm 0. minutes in BCD format. */
    uint8_t ALM0HOUR;   /**< @brief Holds the Alarm 0. hours in 12+AMPM / 24 hour BCD format. */
    uint8_t ALM0WKDAY;  /**< @brief Holds the Alarm 0. weekday and the <i> IT flag, mode mask and polarity bits. </i> */
    uint8_t ALM0DATE;   /**< @brief Holds the Alarm 0. date in BCD format. */
    uint8_t ALM0MTH;    /**< @brief Holds the Alarm 0. month in BCD format. */
    uint8_t ALM1SEC;    /**< @brief Holds the Alarm 1. seconds in BCD format. */
    uint8_t ALM1MIN;    /**< @brief Holds the Alarm 1. minutes in BCD format. */
    uint8_t ALM1HOUR;   /**< @brief Holds the Alarm 1. hours in 12+AMPM / 24 hour BCD format. */
    uint8_t ALM1WKDAY;  /**< @brief Holds the Alarm 1. weekday and the <i> IT flag, mode mask and polarity bits. </i> */
    uint8_t ALM1DATE;   /**< @brief Holds the Alarm 1. date in BCD format. */
    uint8_t ALM1MTH;    /**< @brief Holds the Alarm 1. month in BCD format. */
    /** @} */

    /** @{ @name Power-fail & Power-up Timestamp registers */
    uint8_t PWRDNMIN;   /**< @brief Holds the last power-fail minutes in BCD format. */
    uint8_t PWRDNHOUR;  /**< @brief Holds the last power-fail hours in 12+AMPM / 24 hour BCD format. */
    uint8_t PWRDNDATE;  /**< @brief Holds the last power-fail date in BCD format. */
    uint8_t PWRDNMTH;   /**< @brief Holds the last power-fail month and weekday in BCD format. */
    uint8_t PWRUPMIN;   /**< @brief Holds the last power-up minutes in BCD format. */
    uint8_t PWRUPHOUR;  /**< @brief Holds the last power-up hours in 12+AMPM / 24 hour BCD format. */
    uint8_t PWRUPDATE;  /**< @brief Holds the last power-up date in BCD format. */
    uint8_t PWRUPMTH;   /**< @brief Holds the last power-up month and weekday in BCD format. */
    /** @} */
} __attribute__ ((packed));
 
/** @cond */
typedef struct MCP7940N_RegisterStruct MCP7940N_RegisterStruct;
/** @endcond */

/**
 * @brief
 * Updates the local copy of the register structure
 * from the physical device.
 *
 * @details
 * The library functions are working on a local copy of the 
 * device registers stored in memory. To get the latest data 
 * out of the device #MCP7940N_ReadRegisters() should be called.
 * This is necessary for data consistency and efficiency 
 * reasons, it is faster to read all of the registers of the
 * device at the same time then reading them individually,
 * and data consistency is also ensured, as the visible
 * registers of the device are frozen during a sequential
 * read operation. Note that aggregate getters are available
 * that automatically read the physical device and return 
 * aggregated results for date and time. This function may 
 * be used for directly operating on the local registers.
 */
void MCP7940N_ReadRegisters(void);

/**
 * @brief
 * Updates the registers of the physical device from 
 * the local copy stored in memory.
 *  
 * @details
 * The library functions are working on a local copy of the
 * device registers stored in memory. To reflect any changes
 * in the local register values, the device must be updated
 * via the I2C bus. This is necessary for efficiency and
 * safety reasons, it is faster to write all of the registers
 * of the device at the same time then writing them individually,
 * and safety is also ensured by avoiding data corruption. Note
 * that aggregate setters are available that automatically write
 * aggregated data to the physical device, and configuration
 * changes are written automatically. This function may be used
 * for diretly operating on the local registers.
 */
void MCP7940N_WriteRegisters(void);
/** @} */

/** @{ @name Register access */
/**
 * @brief Returns a pointer to the local register structure.
 * 
 * @details
 * The individual registers can be accessed via the returned
 * structure manually, but using the library interface is highly 
 * recommended.
 */
MCP7940N_RegisterStruct* MCP7940N_GetLocalRegisters(void);
/** @} */

/** @{ @name Calendar getters */
/**
 * @brief Retuns a Datetime structure containing the current date and time.
 * @details
 * This is an aggregate function to acquire the current date and time in one
 * step. While the individual datetime getters operate directly on the local
 * register copies, this function automatically reads the data from hardware
 * first. This is the preferred method for reading date and time information,
 * while the individual getters may be used for direct operation on register
 * content.
 *
 * @returns An MCP7940N_Datetime containing the current date and time.
 */
MCP7940N_Datetime MCP7940N_GetDatetime(void);

/**
 * @brief Returns the currently stored seconds.
 */
uint8_t MCP7940N_GetSeconds(void);

/**
 * @brief Returns the currently stored minutes.
 */
uint8_t MCP7940N_GetMinutes(void);

/**
 * @brief Returns the currently stored hours.
 */
uint8_t MCP7940N_GetHours(void);

/**
 * @brief Returns the currently stored date.
 */
uint8_t MCP7940N_GetDate(void);

/**
 *  @brief 
 *  Returns the currently stored weekday.
 * 
 *  @return 
 *  - #MCP7940N_WEEKDAY_NONE
 *  - #MCP7940N_WEEKDAY_MONDAY
 *  - #MCP7940N_WEEKDAY_TUESDAY
 *  - #MCP7940N_WEEKDAY_WEDNESDAY
 *  - #MCP7940N_WEEKDAY_THURSDAY
 *  - #MCP7940N_WEEKDAY_FRIDAY
 *  - #MCP7940N_WEEKDAY_SATURDAY
 *  - #MCP7940N_WEEKDAY_SUNDAY
 */
uint8_t MCP7940N_GetWeekday(void);

/**
 * @brief Returns the currently stored month.
 */
uint8_t MCP7940N_GetMonths(void);

/**
 * @brief Returns the currently stored year.
 */
uint16_t MCP7940N_GetYears(void);

/**
 * @brief 
 * Returns whether the currently stored year is a leapyear.
 *
 * @return
 * - #MCP7940N_LEAPYEAR
 * - #MCP7940N_NOT_LEAPYEAR
 */
uint8_t MCP7940N_IsLeapYear(void);
/** @} */


/** @{ @name Calendar setters */
/**
 * @brief Sets the current date and time of the physical device.
 * @details
 * This is an aggregate function to set the current date and time in one
 * step. While the individual datetime setters operate directly on the local
 * register copies, this function automatically flushes the data to hardware
 * afterwards. This is the preferred method for setting date and time information,
 * while the individual setters may be used for direct operation on register
 * content.
 */
void MCP7940N_SetDatetime(MCP7940N_Datetime datetime);

/**
 * @brief Sets the locally stored seconds.
 * @param [in] seconds
 * The seconds to set in the local register.
 */
void MCP7940N_SetSeconds(uint8_t seconds);

/**
 * @brief Sets the locally stored minutes.
 * @param [in] minutes
 * The minutes to set in the local register.
 */
void MCP7940N_SetMinutes(uint8_t minutes);

/**
 * @brief Sets the locally stored hours.
 * @param [in] hours
 * The hours to set in the local register.
 */
void MCP7940N_SetHours(uint8_t hours);

/**
 * @brief Sets the locally stored date.
 * @param [in] date
 * The date to set in the local register.
 */
void MCP7940N_SetDate(uint16_t date);

/**
 * @brief Sets the locally stored weekday.
 *
 * @param [in] weekday
 * The weekday to set in the local register.
 * - #MCP7940N_WEEKDAY_MONDAY
 * - #MCP7940N_WEEKDAY_TUESDAY
 * - #MCP7940N_WEEKDAY_WEDNESDAY
 * - #MCP7940N_WEEKDAY_THURSDAY
 * - #MCP7940N_WEEKDAY_FRIDAY
 * - #MCP7940N_WEEKDAY_SATURDAY
 * - #MCP7940N_WEEKDAY_SUNDAY
 */
void MCP7940N_SetWeekday(uint8_t weekday);

/**
 * @brief Sets the locally stored months.
 * @param [in] months
 * The month to set in the local register.
 */
void MCP7940N_SetMonths(uint8_t months);

/**
 * @brief Sets the locally stored years.
 * @param [in] years
 * The year to set in the local register.
 */
void MCP7940N_SetYears(uint16_t years);
/** @} */

/** @{ @name Oscillator control */
/**
 * @brief Returns whether the oscillator is enabled.
 * @returns Zero if disabled, non-zero if enabled.
 */
uint8_t MCP7940N_IsOscillatorEnabled(void);

/**
 * @brief 
 * Enables the oscillator of the device,
 * and lets the time advance forward.
 */
void MCP7940N_EnableOscillator(void);

/**
 * @brief
 * Disables the oscillator of the device,
 * and keeps time from advancing forward.
 * 
 * @details
 * When updating the timekeeping registers
 * the oscillator must be disabled.
 */
void MCP7940N_DisableOscillator(void);

/**
 * @brief 
 * Returns whether the oscillator of the device is running.
 *
 * @return 
 * - #MCP7940N_OSCILLATOR_RUNNING
 * - #MCP7940N_OSCILLATOR_NOT_RUNNING
 */
uint8_t MCP7940N_IsOscillatorRunning(void);
/** @} */

/** @{ @name Battery control */
/**
 * @brief Enables the usage of the backup battery of the device.
 */
void MCP7940N_EnableBattery(void);

/**
 * @brief Disables the usage of the backup battery of the device.
 */
void MCP7940N_DisableBattery(void);

/**
 * @brief Returns whether the usage of the backup battery is enabled.
 * @return 
 * - #MCP7940N_BATTERY_ENABLED
 * - #MCP7940N_BATTERY_DISABLED
 */
uint8_t MCP7940N_IsBatteryEnabled(void);
/** @} */

/** @{ @name Power status */
/**
 * @brief Returns whether primary power has failed.
 * @return
 * - #MCP7940N_POWER_FAILED or
 * - #MCP7940N_POWER_NOT_FAILED
 */
uint8_t MCP7940N_HasPowerFailed(void);

/**
 * @brief Clears the power fail flag of the local register.
 */
void MCP7940N_ClearPowerFailed(void);
/** @} */

/** @{ @name Power status */
/**
 * @brief Sets the configuration of the multifunction output pin (MFP).
 * @param [in] mode
 * - #MCP7940N_MFP_ALARM
 * - #MCP7940N_MFP_SQUARE
 * - #MCP7940N_MFP_GPIO
 */
void MCP7940N_SetMFPMode(uint8_t mode);

/**
 * @brief Returns the current configuration of the multifunction output pin (MFP).
 * @return
 * - #MCP7940N_MFP_ALARM
 * - #MCP7940N_MFP_SQUARE
 * - #MCP7940N_MFP_GPIO
 */
uint8_t MCP7940N_GetMFPMode();
/** @} */

/** @{ @name MFP GPIO mode */
/**
 * @brief Sets the desired output state of the MFP GPIO pin.
 * @param [in] value
 * - #MCP7940N_GPIO_HIGH
 * - #MCP7940N_GPIO_LOW
 */
void MCP7940N_SetGPIO(uint8_t value);
/** @} */

/** @{ @name Coarse trimming */
/**
 * @brief Enables coarse trimming of the oscillator.
 * @details
 * When coarse trimming is enabled the trimming value
 * is added/subtracted every SECOND.
 */
void MCP7940N_EnableCoarseTrimming(void);

/**
 * @brief Disables coarse trimming of the oscillator.
 * @details
 * When coarse trimming is disabled the DOUBLE of the
 * trimming value is added/subtracted every MINUTE.
 */
void MCP7940N_DisableCoarseTrimming(void);

/**
 * @brief Returns whether coarse trimming is enabled.
 * @return
 * - #MCP7940N_COARSE_TRIMMING_ENABLED 
 * - #MCP7940N_COARSE_TRIMMING_DISABLED
 */
uint8_t MCP7940N_IsCoarseTrimmingEnabled(void);

/**
 * @brief Sets the trimming value of the oscillator.
 * @param [in] value
 * The trimming value of the oscillator [-128;128].
 */
void MCP7940N_SetTrimmingValue(int8_t value);

/**
 * @brief Returns the currently set trimming value.
 */
int8_t MCP7940N_GetTrimmingValue(void);
/** @} */

/** @{ @name MFP Squarewave mode */
/**
 * @brief Returns the currently set squarewave frequency.
 * @return
 * - #MCP7940N_SQUAREWAVE_1HZ
 * - #MCP7940N_SQUAREWAVE_4096KHZ
 * - #MCP7940N_SQUAREWAVE_8192KHZ
 * - #MCP7940N_SQUAREWAVE_32768KHZ
 */
uint8_t MCP7940N_GetSquarewaveFrequency(void);

/**
 * @brief Sets the MFP squarewave frequency.
 * @param [in] frequency
 * - #MCP7940N_SQUAREWAVE_1HZ
 * - #MCP7940N_SQUAREWAVE_4096KHZ
 * - #MCP7940N_SQUAREWAVE_8192KHZ
 * - #MCP7940N_SQUAREWAVE_32768KHZ
 */
void MCP7940N_SetSquarewaveFrequency(uint8_t frequency);
/** @} */

/** @{ @name External clock source */
/**
 * @brief Enables the usage of an external clock signal.
 */
void MCP7940N_EnableExternalOscillator(void);

/**
 * @brief Disables the usafe of an external clock signal.
 */
void MCP7940N_DisableExternalOscillator(void);

/**
 * @brief Returns whether the usage of an external clock signal is enabled.
 * @return
 * - #MCP7940N_EXTERNAL_OSC_ENABLED
 * - #MCP7940N_EXTERNAL_OSC_DISABLED
 */
uint8_t MCP7940N_IsExternalOscillatorEnabled(void);
/** @} */

/** @{ @name Alarm getters */
/**
 * @brief Returns the date and time of the specified alarm.
 * @details
 * This is an aggregate function to acquire the date and time of specified alarms
 * in one step. This is the preferred method for getting current alarm configuration,
 * the individual getters may be used for direct operation on the local registers.
 *
 * @param [in] id
 * - #MCP7940N_ALARM0
 * - #MCP7940N_ALARM1.
 *
 * @returns An MCP7940N_Datetime structure containing the date and time of alarm.
 */
MCP7940N_Datetime MCP7940N_GetAlarmDatetime(uint8_t id);

/**
 * @brief Returns the alarm seconds of the specified alarm.
 * @param [in] id 
 * - #MCP7940N_ALARM0
 * - #MCP7940N_ALARM1.
 */
uint8_t MCP7940N_GetAlarmSeconds(uint8_t id);

/**
 * @brief Returns the alarm minutes of the specified alarm.
 * @param [in] id 
 * - #MCP7940N_ALARM0
 * - #MCP7940N_ALARM1.
 */
uint8_t MCP7940N_GetAlarmMinutes(uint8_t id);

/**
 *  @brief Returns the alarm hours of the specified alarm.
 *  @param [in] id 
 * - #MCP7940N_ALARM0
 * - #MCP7940N_ALARM1.
 */
uint8_t MCP7940N_GetAlarmHours(uint8_t id);

/**
 * @brief Returns the alarm weekday of the specified alarm.
 * @param [in] id 
 * - #MCP7940N_ALARM0
 * - #MCP7940N_ALARM1
 * @return
 * - #MCP7940N_WEEKDAY_NONE
 * - #MCP7940N_WEEKDAY_MONDAY
 * - #MCP7940N_WEEKDAY_TUESDAY
 * - #MCP7940N_WEEKDAY_WEDNESDAY
 * - #MCP7940N_WEEKDAY_THURSDAY
 * - #MCP7940N_WEEKDAY_FRIDAY
 * - #MCP7940N_WEEKDAY_SATURDAY
 * - #MCP7940N_WEEKDAY_SUNDAY
 */
uint8_t MCP7940N_GetAlarmWeekday(uint8_t id);

/**
 * @brief Returns the alarm date of the specified alarm.
 * @param [in] id 
 * - #MCP7940N_ALARM0
 * - #MCP7940N_ALARM1
 */
uint8_t MCP7940N_GetAlarmDate(uint8_t id);

/**
 * @brief Returns the alarm months of the specified alarm.
 * @param [in] id  
 * - #MCP7940N_ALARM0
 * - #MCP7940N_ALARM1
 */
uint8_t MCP7940N_GetAlarmMonths(uint8_t id);

/**
 * @brief Returns the GPIO polarity when an alarm has fired.
 * @return
 * - #MCP7940N_ALARM_POLARITY_HIGH
 * - #MCP7940N_ALARM_POLARITY_LOW 
 */
uint8_t MCP7940N_GetAlarmPolarity(void);

/**
 * @brief Returns the alarm mode of the specified alarm.
 * @param [in] id 
 * - #MCP7940N_ALARM0
 * - #MCP7940N_ALARM1
 * @return
 * - #MCP7940N_ALARM_MODE_SECONDS
 * - #MCP7940N_ALARM_MODE_MINUTES
 * - #MCP7940N_ALARM_MODE_HOURS
 * - #MCP7940N_ALARM_MODE_WEEKDAYS
 * - #MCP7940N_ALARM_MODE_DATES
 * - #MCP7940N_ALARM_MODE_ALL
 */
uint8_t MCP7940N_GetAlarmMode(uint8_t id);

/**
 * @brief Returns whether the specified alarm is enabled or not.
 * @param [in] id 
 * - #MCP7940N_ALARM0
 * - #MCP7940N_ALARM1
 * @return
 * - #MCP7940N_ALARM0_ENABLED
 * - #MCP7940N_ALARM1_ENABLED
 * - #MCP7940N_ALARM_DISABLED
 */
uint8_t MCP7940N_IsAlarmEnabled(uint8_t id);

/**
 * @brief Returns the alarm seconds of the specified alarm.
 * @details The alarm interrupt flag is also cleared.
 * @param [in] id
 * - #MCP7940N_ALARM0
 * - #MCP7940N_ALARM1
 * @return 
 * - #MCP7940N_ALARM_FIRED or
 * - #MCP7940N_ALARM_NOT_FIRED
 */
uint8_t MCP7940N_HasAlarmFired(uint8_t id);
/** @} */


/** @{ @name Alarm setters */
/**
 * @brief Returns the date and time of the specified alarm.
 * @details
 * This is an aggregate function to set the date and time of specified alarms
 * in one step. This is the preferred method for setting the alarm configuration,
 * the individual setters may be used for direct operation on the local registers.
 *
 * @param id [in]
 * - #MCP7940N_ALARM0
 * - #MCP7940N_ALARM1.
 * 
 * @param datetime [in] The date and time of the alarm to set.
 */
void MCP7940N_SetAlarmDatetime(uint8_t id, MCP7940N_Datetime datetime);

/**
 * @brief Sets the alarm seconds of the specified alarm.
 * @param [in] id 
 * - #MCP7940N_ALARM0
 * - #MCP7940N_ALARM1.
 * @param [in] seconds The seconds of the alarm.
 */
void MCP7940N_SetAlarmSeconds(uint8_t id, uint8_t seconds);

/**
 * @brief Sets the alarm minutes of the specified alarm.
 * @param [in] id Either MCP7940N_ALARM0 or MCP7940N_ALARM1.
 * - #MCP7940N_ALARM0
 * - #MCP7940N_ALARM1
 * @param [in] minutes The minutes of the alarm.
 */
void MCP7940N_SetAlarmMinutes(uint8_t id, uint8_t minutes);

/**
 * @brief Sets the alarm hours of the specified alarm.
 * @param [in] id
 * - #MCP7940N_ALARM0
 * - #MCP7940N_ALARM1
 * @param [in] hours The hours of the alarm.
 */
void MCP7940N_SetAlarmHours(uint8_t id, uint8_t hours);

/**
 * @brief Sets the alarm weekday of the specified alarm.
 * @param [in] id 
 * - #MCP7940N_ALARM0
 * - #MCP7940N_ALARM1
 * @param [in] weekday The weekday of the alarm.
 * - #MCP7940N_WEEKDAY_MONDAY
 * - #MCP7940N_WEEKDAY_TUESDAY
 * - #MCP7940N_WEEKDAY_WEDNESDAY
 * - #MCP7940N_WEEKDAY_THURSDAY
 * - #MCP7940N_WEEKDAY_FRIDAY
 * - #MCP7940N_WEEKDAY_SATURDAY
 * - #MCP7940N_WEEKDAY_SUNDAY
 */
void MCP7940N_SetAlarmWeekday(uint8_t id, uint8_t weekday);

/**
 * @brief Sets the alarm date of the specified alarm.
 * @param [in] id 
 * - #MCP7940N_ALARM0
 * - #MCP7940N_ALARM1
 * @param [in] date The date of the alarm.
 */
void MCP7940N_SetAlarmDate(uint8_t id, uint8_t date);

/**
 * @brief Sets the alarm months of the specified alarm.
 * @param [in] id 
 * - #MCP7940N_ALARM0
 * - #MCP7940N_ALARM1
 * @param [in] months The months of the alarm.
 */
void MCP7940N_SetAlarmMonths(uint8_t id, uint8_t months);

/**
 * @brief Returns the GPIO polarity when an alarm has fired.
 * @return
 * - #MCP7940N_ALARM_POLARITY_HIGH
 * - #MCP7940N_ALARM_POLARITY_LOW 
 */
void MCP7940N_SetAlarmPolarity(uint8_t polarity);

/**
 * @brief Enables the specified alarm.
 * @param [in] id 
 * - #MCP7940N_ALARM0
 * - #MCP7940N_ALARM1
 * @param [in] mode The alarm mode is one of the following:
 * - #MCP7940N_ALARM_MODE_SECONDS
 * - #MCP7940N_ALARM_MODE_MINUTES
 * - #MCP7940N_ALARM_MODE_HOURS
 * - #MCP7940N_ALARM_MODE_WEEKDAYS
 * - #MCP7940N_ALARM_MODE_DATES
 * - #MCP7940N_ALARM_MODE_ALL
 * 
 *  @details 
 *  The alarm will trigger every time when the specific
 *  alarm registers are matching with the timekeeping
 *  registers. The alarm mode defines which registers
 *  need to match in order to trigger an alarm.
 */
void MCP7940N_EnableAlarm(uint8_t id, uint8_t mode);

/**
 * @brief Disables the specified alarm.
 * @param [in] id 
 * - #MCP7940N_ALARM0
 * - #MCP7940N_ALARM1
 */
void MCP7940N_DisableAlarm(uint8_t id);
/** @} */


/** @{ @name Power-fail getters */
/**
 * @brief Returns the date and time of the latest power-fail.
 * @details 
 * This is an aggregate function to acquire the date and time information of
 * the latest power-fail. This is the preferred method for reading power-fail
 * information, while the individual getters may be used for direct operation
 * on the local registers. This function automatically reads the physical
 * device registers.
 * 
 * @returns An MCP7940N_Datetime structure containing the latest power-fail.
 */
MCP7940N_Datetime MCP7940N_GetPowerFailDatetime(void);

/** @brief Returns the month of the last power-fail. */
uint8_t MCP7940N_GetPowerFailMonth(void);

/**
 * @brief Returns the weekday of the last power-fail.
 * @returns
 * - #MCP7940N_WEEKDAY_MONDAY
 * - #MCP7940N_WEEKDAY_TUESDAY
 * - #MCP7940N_WEEKDAY_WEDNESDAY
 * - #MCP7940N_WEEKDAY_THURSDAY
 * - #MCP7940N_WEEKDAY_FRIDAY
 * - #MCP7940N_WEEKDAY_SATURDAY
 * - #MCP7940N_WEEKDAY_SUNDAY
 */
uint8_t MCP7940N_GetPowerFailWeekday(void);

/** @brief Returns the date of the last power-fail. */
uint8_t MCP7940N_GetPowerFailDate(void);

/** @brief Returns the hour of the last power-fail. */
uint8_t MCP7940N_GetPowerFailHour(void);

/** @brief Returns the minute of the last power-fail. */
uint8_t MCP7940N_GetPowerFailMinute(void);
/** @} */


/** @{ @name Power-up getters */
/**
 * @brief Returns the date and time of the latest power-up.
 * @details 
 * This is an aggregate function to acquire the date and time information of
 * the latest power-up. This is the preferred method for reading power-up
 * information, while the individual getters may be used for direct operation
 * on the local registers. This function automatically reads the physical 
 * device registers.
 * 
 * @returns An MCP7940N_Datetime structure containing the latest power-up.
 */
MCP7940N_Datetime MCP7940N_GetPowerUpDatetime(void);

/** @brief Returns the month of the last power-up. */
uint8_t MCP7940N_GetPowerUpMonth(void);

/**
 * @brief Returns the weekday of the last power-up.
 * @returns
 * - #MCP7940N_WEEKDAY_MONDAY
 * - #MCP7940N_WEEKDAY_TUESDAY
 * - #MCP7940N_WEEKDAY_WEDNESDAY
 * - #MCP7940N_WEEKDAY_THURSDAY
 * - #MCP7940N_WEEKDAY_FRIDAY
 * - #MCP7940N_WEEKDAY_SATURDAY
 * - #MCP7940N_WEEKDAY_SUNDAY
 */
uint8_t MCP7940N_GetPowerUpWeekday(void);

/** @brief Returns the date of the last power-up. */
uint8_t MCP7940N_GetPowerUpDate(void);

/** @brief Returns the hour of the last power-up. */
uint8_t MCP7940N_GetPowerUpHour(void);

/** @brief Returns the minute of the last power-up. */
uint8_t MCP7940N_GetPowerUpMinute(void);
/** @} */

/** @{ @name Onboard SRAM */
/**
 * @brief Reads the content of the on-chip SRAM.
 * @param [in] deviceAddress SRAM address to read from.
 * @param [out] buffer Data buffer to read into.
 * @param [in] byteCount The number of bytes to read.
 */
void MCP7940N_ReadSRAM(uint8_t deviceAddress, unsigned char *buffer, uint8_t byteCount);

/**
 *  @brief Writes to the on-chip SRAM.
 *  @param [in] deviceAddress SRAM address to write to.
 *  @param [in] buffer Data buffer to write from.
 *  @param [in] byteCount The number of bytes to write.
 */
void MCP7940N_WriteSRAM(uint8_t deviceAddress, const unsigned char *buffer, uint8_t byteCount);
/** @} */

#endif // MCP7940N_H_INCLUDED

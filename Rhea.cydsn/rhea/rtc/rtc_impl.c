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
 * @file    rtc_impl.c
 * @author  Peter Gyulai
 * @version 1.0.0
 * @date    2020.04.19
 * @brief   RTC driver implementation.
 * @details
 * This file contains the RTC driver implementation. Implement the driver 
 * functionality here when porting to a new RTC target driver.
 */

// Including global configuration
#include "../rhea_config.h"

// Including header for function declarations
#include "rtc_config.h"
#include "rtc_impl.h"
#include "rtc.h"

// Target specific includes
#if defined(RHEA_TARGET_PSOC5LP)			
	#include "project.h"
#elif defined(RHEA_TARGET_ESP32)
#endif

// Implementation for MCP7940N RTC target
#if defined(RHEA_RTC_TARGET_MCP7940N)

	// Checking configuration
	#if RHEA_RTC_HARDWARE_ALARM_COUNT > 8 
		#error MCP7940N driver does not support more than 8 hardware stored alarms.
	#endif

	// Standard includes - memset()
	#include <string.h>

	// Include RTC driver
	#include "../drivers/MCP7940N/MCP7940N.h"

	// Include I2C driver
	#include "../i2c/i2c.h"

	/**
	 * @brief 
	 * This structure is an extended representation of the alarm registers in
	 * the MCP7940N RTC chip. 
	 * @details 
	 * The bytes from ALMSEC to ALMMTH are mostly directly corresponding to the device
	 * alarm registers and are handled by using the MCP7940N driver library macros.
	 * The alarm mode bits of the ALMWKDAY field are storing a #rhea_rtc_alarmMode 
	 * value, which is NOT corresponding with the value to be stored in the MCP7940N.
	 * The extra field ALMYEAR is an extension to support alarms more than one year
	 * into the future. The lower 12 bits of ALMYEAR describe the year of the alarm
	 * in unsigned binary format. The upper 4 bits are flags associated with the
	 * alarm, accessible with the previously declared bitmask macros:
	 * - ACTIVE: Describes that the alarm is active or can be replaced.
	 * - RECURRING: Describes that the alarm is recurring after being reset.
	 * The structure is exactly 64 bits wide, so exactly 8 can be placed in the 
	 * MCP7940N's 64 byte SRAM memory, to be used as persistent alarms.
	 */
	struct rhea_rtc_alarmRegisterStruct {
	    uint8_t  ALMSEC;    /**< @brief Holds the Alarm seconds in BCD format. */
	    uint8_t  ALMMIN;    /**< @brief Holds the Alarm minutes in BCD format. */
	    uint8_t  ALMHOUR;   /**< @brief Holds the Alarm hours in 12+AMPM / 24 hour BCD format. */
	    uint8_t  ALMWKDAY;  /**< @brief Holds the Alarm weekday and the <i> IT flag, mode mask and polarity bits. </i> */
	    uint8_t  ALMDATE;   /**< @brief Holds the Alarm date in BCD format. */
	    uint8_t  ALMMTH;    /**< @brief Holds the Alarm month in BCD format. */
	    uint16_t ALMYEAR;   /**< @brief Holds the Alarm year and flags. */
	} __attribute__ ((packed));

	/** @brief Defines a bitmask for the year bits of the ALMYEAR byte. */
	#define RHEA_RTC_ALMYEAR_YEAR       (0x0FFF)
	/** @brief Defines a bitmask for the ACTIVE bit of the ALMYEAR byte. */
	#define RHEA_RTC_ALMYEAR_ACTIVE     (0x1000)
	/** @brief Defines a bitmask for the RECURRING bit of the ALMYEAR byte. */
	#define RHEA_RTC_ALMYEAR_RECURRING  (0x2000)

	// Typedef for omitting 'struct' keyword
	typedef struct rhea_rtc_alarmRegisterStruct rhea_rtc_alarmRegisterStruct;

	// Forward declarations for driver specific functions
	rhea_rtc_alarm rhea_rtc_fromAlarmRegisterStruct(rhea_rtc_alarmRegisterStruct regs);
	rhea_rtc_alarmRegisterStruct rhea_rtc_toAlarmRegisterStruct(rhea_rtc_alarm alarm);
    MCP7940N_Datetime toDriverDatetime(rhea_rtc_datetime datetime);
    rhea_rtc_datetime fromDriverDatetime(MCP7940N_Datetime datetime);

	void rhea_rtc_initialize_impl(void) {

		// Function pointers to I2C driver
		MCP7940N_I2CControllerStruct controller = {
			.MasterSendStart = rhea_i2c_MasterSendStart,
			.MasterSendStop  = rhea_i2c_MasterSendStop,
			.MasterReadByte  = rhea_i2c_MasterReadByte,
			.MasterWriteByte = rhea_i2c_MasterWriteByte
		};

		// Initializing the MCP7940N driver
		MCP7940N_SetI2CController(controller);

		// Reading initial RTC register data
		MCP7940N_ReadRegisters();

        // Reading power-fail timestamp
        rhea_rtc_powerFailTimestamp = fromDriverDatetime(MCP7940N_GetPowerFailDatetime());
        
        // Reading power-up timestamp
        rhea_rtc_powerUpTimestamp = fromDriverDatetime(MCP7940N_GetPowerUpDatetime());

		// Clearing power event timestamps
		MCP7940N_ClearPowerFailed();

		// Enabling battery backup
		MCP7940N_EnableBattery();

		// Setting alarm mode for multifunction pin
		MCP7940N_SetMFPMode(MCP7940N_MFP_ALARM);

		// Setting oscillator trimming value
		MCP7940N_SetTrimmingValue(0);

		// Disabling coarse trimming mode
		MCP7940N_DisableCoarseTrimming();

		// Disabling alarms
		MCP7940N_DisableAlarm(MCP7940N_ALARM0);
		MCP7940N_DisableAlarm(MCP7940N_ALARM1);  

		// Enable alarm interrupts
		#if defined(RHEA_TARGET_PSOC5LP) 
		
			// Enabling interrupt handler
			RTC_INTR_StartEx(rhea_rtc_alarmISR);

		#elif defined(RHEA_TARGET_ESP32)

			// Enabling interrupt handler
			#error ESP32: Enable interrupt handler!

		#endif 
	}

	rhea_rtc_datetime rhea_rtc_now_impl(void) {
		
		#if defined(RHEA_TARGET_PSOC5LP)

			// Returning datetime
	    	return fromDriverDatetime(MCP7940N_GetDatetime());

		#elif defined(RHEA_TARGET_ESP32)

	    	// Returning datetime
	    	#error ESP32: Return current datetime!

		#endif
	}

	void rhea_rtc_setDatetime_impl(rhea_rtc_datetime newDatetime) {

		#if defined(RHEA_TARGET_PSOC5LP)

			// Updating datetime 
    		MCP7940N_SetDatetime(toDriverDatetime(newDatetime));

		#elif defined(RHEA_TARGET_ESP32)

	    	// Updating datetime
	    	#error ESP32: Update current datetime!

		#endif
	}

	void rhea_rtc_enableAlarms_impl(void) {

		// Enabling alarms
		MCP7940N_EnableAlarm(MCP7940N_ALARM1, MCP7940N_ALARM_MODE_ALL);
	}

	void rhea_rtc_disableAlarms_impl(void) {

		// Disabling alarms
		MCP7940N_DisableAlarm(MCP7940N_ALARM1);
	}

	void rhea_rtc_setAlarmDatetime_impl(rhea_rtc_datetime alarmDatetime) {

		// Setting alarm datetime 
		MCP7940N_SetAlarmDatetime(MCP7940N_ALARM1, toDriverDatetime(alarmDatetime));
	}

	void rhea_rtc_loadAlarms_impl(void) {

		// Array to load persistent alarms from SRAM
	    rhea_rtc_alarmRegisterStruct persistentAlarms[RHEA_RTC_HARDWARE_ALARM_COUNT];

	    // Reading RTC-chip SRAM
	    MCP7940N_ReadSRAM(MCP7940N_SRAM_ADDRLOW, (uint8_t*) persistentAlarms, MCP7940N_SRAM_SIZE);

	    // Decoding register representation of the alarm
	    for(uint8_t i = 0; i < RHEA_RTC_HARDWARE_ALARM_COUNT; i++) {
	        rhea_rtc_alarmRegistry[i] = rhea_rtc_fromAlarmRegisterStruct(persistentAlarms[i]);
	    }
	}

	void rhea_rtc_storeAlarms_impl(void) {

		// Array to store persistent alarms to SRAM
		rhea_rtc_alarmRegisterStruct persistentAlarms[RHEA_RTC_HARDWARE_ALARM_COUNT];

		// 
		for(uint8_t i = 0; i < RHEA_RTC_HARDWARE_ALARM_COUNT; i++) {
			persistentAlarms[i] = rhea_rtc_toAlarmRegisterStruct(rhea_rtc_alarmRegistry[i]);
		}

		// Writing RTC-chip SRAM
		MCP7940N_WriteSRAM(MCP7940N_SRAM_ADDRLOW, (uint8_t*) persistentAlarms, MCP7940N_SRAM_SIZE);
	}

	rhea_rtc_alarmRegisterStruct rhea_rtc_toAlarmRegisterStruct(rhea_rtc_alarm alarm) {
    
	    // Alarm register structure to populate
	    rhea_rtc_alarmRegisterStruct regs;
	    
	    // Clearing register content
	    memset(&regs, 0x00, sizeof(rhea_rtc_alarmRegisterStruct));
	    
	    // Setting seconds
	    uint8_t secOnes = alarm.datetime.second % 10;
	    uint8_t secTens = alarm.datetime.second / 10;
	    regs.ALMSEC |= (secOnes & MCP7940N_ALMxSEC_SECONE);
	    regs.ALMSEC |= (secTens << 4 & MCP7940N_ALMxSEC_SECTEN);
	    
	    // Setting minutes
	    uint8_t minOnes = alarm.datetime.minute % 10;
	    uint8_t minTens = alarm.datetime.minute / 10;
	    regs.ALMMIN |= (minOnes & MCP7940N_ALMxMIN_MINONE);
	    regs.ALMMIN |= (minTens << 4 & MCP7940N_ALMxMIN_MINTEN);
	    
	    // Setting hours
	    uint8_t hourOnes = alarm.datetime.hour % 10;
	    uint8_t hourTens = alarm.datetime.hour / 10;
	    regs.ALMHOUR |= (hourOnes & MCP7940N_ALMxHOUR_HRONE);
	    regs.ALMHOUR |= (hourTens << 4 & MCP7940N_ALMxHOUR_HRTEN);
	    
	    // Setting weekday
	    uint8_t weekday = alarm.datetime.weekday;
	    regs.ALMWKDAY |= (weekday & MCP7940N_ALMxWKDAY_WKDAY);
	    
	    // Setting date
	    uint8_t dateOnes = alarm.datetime.date % 10;
	    uint8_t dateTens = alarm.datetime.date / 10;
	    regs.ALMDATE |= (dateOnes & MCP7940N_ALMxDATE_DATEONE);
	    regs.ALMDATE |= (dateTens << 4 & MCP7940N_ALMxDATE_DATETEN);
	    
	    // Setting month
	    uint8_t monthOnes = alarm.datetime.month % 10;
	    uint8_t monthTens = alarm.datetime.month / 10;
	    regs.ALMMTH |= (monthOnes & MCP7940N_ALMxMTH_MTHONE);
	    regs.ALMMTH |= (monthTens << 4 & MCP7940N_ALMxMTH_MTHTEN);
	    
	    // Setting years
	    uint8_t years = alarm.datetime.year;
	    regs.ALMYEAR |= (years & RHEA_RTC_ALMYEAR_YEAR);

	    // Setting mode
	    uint8_t mode = alarm.mode;
	    regs.ALMWKDAY |= (mode << 4 & MCP7940N_ALMxWKDAY_ALMxMSK);

	    // Setting polarity
	    regs.ALMWKDAY |= MCP7940N_ALARM_POLARITY_HIGH;

	    // Setting ACTIVE flag
	    if(alarm.active) regs.ALMYEAR |= RHEA_RTC_ALMYEAR_ACTIVE;

	    // Setting RECURRING flag
	    if(alarm.recurring) regs.ALMYEAR |= RHEA_RTC_ALMYEAR_RECURRING;
	        
	    return regs;
	}

	rhea_rtc_alarm rhea_rtc_fromAlarmRegisterStruct(rhea_rtc_alarmRegisterStruct alarm) {

	    // Regular alarm to populate
	    rhea_rtc_alarm regular;

	    // Setting seconds
	    uint8_t secOnes = (alarm.ALMSEC & MCP7940N_ALMxSEC_SECONE);
	    uint8_t secTens = (alarm.ALMSEC & MCP7940N_ALMxSEC_SECTEN) >> 4;
	    regular.datetime.second = secTens * 10 + secOnes;
	    
	    // Setting minutes
	    uint8_t minOnes = (alarm.ALMMIN & MCP7940N_ALMxMIN_MINONE);
	    uint8_t minTens = (alarm.ALMMIN & MCP7940N_ALMxMIN_MINTEN) >> 4;
	    regular.datetime.minute = minTens * 10 + minOnes;
	    
	    // Setting hours
	    uint8_t hourOnes = (alarm.ALMHOUR & MCP7940N_ALMxHOUR_HRONE);
	    uint8_t hourTens = (alarm.ALMHOUR & MCP7940N_ALMxHOUR_HRTEN) >> 4;
	    regular.datetime.hour = hourTens * 10 + hourOnes;
	    
	    // Setting weekday
	    regular.datetime.weekday = (alarm.ALMWKDAY & MCP7940N_ALMxWKDAY_WKDAY);
	    
	    // Setting date
	    uint8_t dateOnes = (alarm.ALMDATE & MCP7940N_ALMxDATE_DATEONE);
	    uint8_t dateTens = (alarm.ALMDATE & MCP7940N_ALMxDATE_DATETEN) >> 4;
	    regular.datetime.date = dateTens * 10 + dateOnes;
	    
	    // Setting month
	    uint8_t monthOnes = (alarm.ALMMTH & MCP7940N_ALMxMTH_MTHONE);
	    uint8_t monthTens = (alarm.ALMMTH & MCP7940N_ALMxMTH_MTHTEN) >> 4;
	    regular.datetime.month = monthTens * 10 + monthOnes;
	    
	    // Setting years
	    regular.datetime.year = (alarm.ALMYEAR & RHEA_RTC_ALMYEAR_YEAR);

	    // Setting mode
	    regular.mode = (alarm.ALMWKDAY & MCP7940N_ALMxWKDAY_ALMxMSK) >> 4;

	    // Setting ACTIVE flag
	    regular.active = (alarm.ALMYEAR & RHEA_RTC_ALMYEAR_ACTIVE) >> 12;

	    // Setting RECURRING flag
	    regular.recurring = (alarm.ALMYEAR & RHEA_RTC_ALMYEAR_RECURRING) >> 13;

	    return regular;
	}
    
    MCP7940N_Datetime toDriverDatetime(rhea_rtc_datetime datetime) {
        
        // Creating driver datetime structure
        MCP7940N_Datetime result;
        
        // Populating driver datetime
        result.year = datetime.year;
        result.month = datetime.month;
        result.date = datetime.date;
        result.weekday = datetime.weekday;
        result.hour = datetime.hour;
        result.minute = datetime.minute;
        result.second = datetime.second;
        
        return result;
    }
    
    rhea_rtc_datetime fromDriverDatetime(MCP7940N_Datetime datetime) {
        
        // Creating Rhea datetime structure
        rhea_rtc_datetime result;
        
        // Populating driver datetime
        result.year = datetime.year;
        result.month = datetime.month;
        result.date = datetime.date;
        result.weekday = datetime.weekday;
        result.hour = datetime.hour;
        result.minute = datetime.minute;
        result.second = datetime.second;
        
        return result;
    }

#endif

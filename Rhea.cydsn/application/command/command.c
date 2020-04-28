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
 * @file    command.c
 * @author  Peter Gyulai
 * @version 1.0.0
 * @date    2020.04.21
 * @brief   Serial command line parser implementations.
 * @details
 * This file contains the implementation for the serial command line parser.
 */

// Standard includes
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "getopt.h"

// Project includes
#include "../../rhea/uart/uart.h"
#include "../../rhea/sensor/sensor.h"
#include "../../rhea/drivers/BME280/BME280.h"
#include "command.h"


// Defines the size of the receive buffer
#define SERIAL_RX_BUFFER_SIZE (256)

// External serial status indicator flag 
volatile uint8_t serial_data_ready = 0;

// Serial RX buffer
volatile uint8_t serialBuffer[SERIAL_RX_BUFFER_SIZE + 1];

// Serial write index
volatile uint8_t bufferSize;

static const struct option rhea_long_options[] = {
	{"help", no_argument, NULL, 'h'},
	{"version", no_argument, NULL, 'v'},
	{0,0,0,0}
};

static const struct option measure_long_options[] = {
	{"temperature", no_argument, NULL, 't'},
	{"pressure", no_argument, NULL, 'p'},
	{"moisture", no_argument, NULL, 'm'},
	{"humidity", no_argument, NULL, 'm'},
	{"filter", required_argument, NULL, 'f'},
	{"oversampling", required_argument, NULL, 'o'},
	{"period", required_argument, NULL, 'T'},
	{"display", no_argument, NULL, 'd'},
	{"print", no_argument, NULL, 'd'},
	{"help", no_argument, NULL, 'h'},
	{0,0,0,0}
};

/*
static const struct option alarm_long_options[] = {
	{"set", required_argument, NULL, 's'},
	{"setalarm", required_argument, NULL, 's'},
	{"get", no_argument, NULL, 'g'},
	{"getalarm", no_argument, NULL, 'g'},
	{"delete", required_argument, NULL, 'd'},
	{"reset", no_argument, NULL, 'r'},
	{"persist", no_argument, NULL, 'p'},
	{"persistent", no_argument, NULL, 'p'},
	{"help", no_argument, NULL, 'h'},
	{0,0,0,0}
};

static const struct option datetime_long_options[] = {
	{"date", no_argument, NULL, 'd'},
	{"time", no_argument, NULL, 't'},
	{"set", required_argument, NULL, 's'},
	{"get", no_argument, NULL, 'g'},
	{"help", no_argument, NULL, 'h'},
	{0,0,0,0}
};

static const struct option power_long_options[] = {
	{"fail", no_argument, NULL, 'f'},
	{"turnon", no_argument, NULL, 't' },
	{"uptime", no_argument, NULL, 'u' },
	{"help", no_argument, NULL, 'h' },
	{0,0,0,0}
};
*/

void command_rhea(int argc, const char **argv);
void command_measure(int argc, const char **argv);

void toArgumentArray(char* str, int* argc, const char ** argv) {
	char* token = strtok(str, " ");
	int i = 0;
	while (token != NULL) {
		argv[i++] = token;
		token = strtok(NULL, " ");
	}

	*argc = i;
}
    
void InitializeSerialCommandLine(void) {
    
    // Initializing buffer size
    bufferSize = 0;
    
    // Terminating buffer for overflow safety
    serialBuffer[SERIAL_RX_BUFFER_SIZE] = '\0';
    serialBuffer[0] = '\0';
    
    // Initializing and enabling the serial interrupt
    UART_RX_INTR_StartEx(SERIAL_DATA_ARRIVED);
}

void ProcessCommandLine(void) {
    
    // Checking serial status flag
    if(!serial_data_ready) return;
    
    // Clearing serial status flag
    serial_data_ready = 0;

    // Reading command
    char command[SERIAL_RX_BUFFER_SIZE] = {0};
    sscanf((const char *) serialBuffer, "%s", command); 
    
    // Command parsing helpers    
    int argc;
	const char* argv[10];

    // Creating argc-argv format
	toArgumentArray((char*) serialBuffer, &argc, argv);
    
    // Jumping to next line
    rhea_uart_WriteString("\n\r");
    
    rhea_uart_WriteBuffer(serialBuffer, 10);
    
    // Interpreting command
    if(strcmp(command, "rhea") == 0) 
    {
        command_rhea(argc, argv);
    } 
    else if(strcmp(command, "measure") == 0) 
    {
        command_measure(argc, argv);
    } 
    else 
    {
        rhea_uart_WriteString("Unrecognized command: \"");
        rhea_uart_WriteString(command);
        rhea_uart_WriteString("\"");
    }
    
    rhea_uart_WriteString("\n\rRhea testboard: >> ");
}

CY_ISR(SERIAL_DATA_ARRIVED) {

    uint8_t status = CyEnterCriticalSection();
    
    unsigned char c = rhea_uart_ReadChar();
    
    // Reading character received
    serialBuffer[bufferSize++] = c;
    
    // Echoing back to terminal
    rhea_uart_WriteChar(c);
    
    // Checking character received
    if(c == '\n' ||  c == '\r')
    {
        // Setting command received flag
        serial_data_ready = 1;
        
        // Adding string terminator to end of buffer
        serialBuffer[bufferSize - 1] = '\0';
        
        // Resetting buffer index
        bufferSize = 0;
    }
    
    CyExitCriticalSection(status);
}

////////////////////////////////////////////////////////////
// 
// Command handlers
//
////////////////////////////////////////////////////////////


void rhea_print_help() {
    rhea_uart_WriteString(
        "                                                               \n\r"
        "Command: rhea                                                  \n\r"
        "-------------                                                  \n\r"
        "                                                               \n\r"
        "-h, --help                                                     \n\r"    
        "Prints the available commands.                                 \n\r"
        "                                                               \n\r"
        "-v, --version                                                  \n\r"
        "Prints the Rhea firmware version.                              \n\r"
        "                                                               \n\r"
        "                                                               \n\r"
        "Command: measure                                               \n\r"
        "----------------                                               \n\r"
        "                                                               \n\r"
        "-t, --temperature                                              \n\r"
        "Selects the temperature measurement for subsequent commands.   \n\r"
        "                                                               \n\r"
        "-p, --pressure                                                 \n\r"
        "Selects the pressure measurement for subsequent commands.      \n\r"
        "                                                               \n\r"  
        "-m, --moisture, --humidity                                     \n\r"
        "Selects the humidity measurement for subsequent commands.      \n\r"
        "                                                               \n\r"
        "-f, --filter (OFF|2|4|8|16)                                    \n\r"
        "Sets the global IIR filter coefficient all measurements.       \n\r"
        "                                                               \n\r"
        "-o, --oversampling (1|2|4|8|16)                                \n\r"
        "Sets the oversampling mode for the selected measurements.      \n\r"
        "                                                               \n\r"
        "-T, --period <millisecs>                                       \n\r"
        "Sets the measurement period for the selected measurements.     \n\r"
        "                                                               \n\r"
        "-d, --display, --print                                         \n\r"
        "Prints the selected measurements.                              \n\r"
        "                                                               \n\r"
        "-h, --help                                                     \n\r"
        "Prints this help.                                              \n\r"
    );
}

void rhea_print_version() {
    rhea_uart_WriteString("1.0.0\n\r");
}

void rhea_print_error() {
    rhea_uart_WriteString("Error: Unrecognized argument.\n\r");
}

void command_rhea(int argc, const char **argv) {
	int opt = 0;
	int longopt = 0;
	optind = 1;

	while ((opt = getopt_long(argc, (char*const*)argv, "hv", rhea_long_options, &longopt)) != -1) {
		switch (opt) {
		case 'h': rhea_print_help();
		   break;
		case 'v': rhea_print_version();
		   break;
		default: rhea_print_error(); return;
		};
	}
}

void command_measure(int argc, const char **argv) {
	
	// Getopt parameters
	int longopt = 0;
	int opt = 0;
	optind = 1;

	// Flags and option arguments
	int t = 0, p = 0, m = 0, d = 0, ovrs = 0, T = 0;

	// Parsing options
	while ((opt = getopt_long(argc, (char*const*)argv, "tpmf:o:T:dh", measure_long_options, &longopt)) != -1) {
		switch (opt) {

		// Setting measurement flags
		case 't': t = 1; break;
		case 'p': p = 1; break;
		case 'm': m = 1; break;

		case 'f': 
			// Setting IIR filter mode
			if (strcmp(optarg, "OFF") == 0) rhea_sensor_SetAttribute("BME280", "filter", BME280_FILTER_OFF);            break;
			if (strcmp(optarg, "2") == 0)   rhea_sensor_SetAttribute("BME280", "filter", BME280_FILTER_COEFFICIENT_2);  break;
			if (strcmp(optarg, "4") == 0)   rhea_sensor_SetAttribute("BME280", "filter", BME280_FILTER_COEFFICIENT_4);  break;
			if (strcmp(optarg, "8") == 0)   rhea_sensor_SetAttribute("BME280", "filter", BME280_FILTER_COEFFICIENT_8);  break;
			if (strcmp(optarg, "16") == 0)  rhea_sensor_SetAttribute("BME280", "filter", BME280_FILTER_COEFFICIENT_16); break;
			rhea_uart_WriteString("Wrong IIR filter value.\n\r"); break;

		case 'o': 
			// Getting oversampling rate
			if      (strcmp(optarg, "1") == 0)  ovrs = 1;
			else if (strcmp(optarg, "2") == 0)  ovrs = 2;
			else if (strcmp(optarg, "4") == 0)  ovrs = 4;
			else if (strcmp(optarg, "8") == 0)  ovrs = 8;
			else if (strcmp(optarg, "16") == 0) ovrs = 16;
			else rhea_uart_WriteString("Wrong oversampling value.\n\r"); break;

			// Applying temperature oversampling
			if (t) {
				switch (ovrs) {
				case 1:  rhea_sensor_SetAttribute("BME280", "temperatureOVRS", BME280_TEMPERATURE_OVERSAMPLING_1X); break;
				case 2:  rhea_sensor_SetAttribute("BME280", "temperatureOVRS", BME280_TEMPERATURE_OVERSAMPLING_2X); break;
				case 4:  rhea_sensor_SetAttribute("BME280", "temperatureOVRS", BME280_TEMPERATURE_OVERSAMPLING_4X); break;
				case 8:  rhea_sensor_SetAttribute("BME280", "temperatureOVRS", BME280_TEMPERATURE_OVERSAMPLING_8X); break;
				case 16: rhea_sensor_SetAttribute("BME280", "temperatureOVRS", BME280_TEMPERATURE_OVERSAMPLING_16X); break;
				};
			}

			// Applying pressure oversampling
			if (p) {
				switch (ovrs) {
				case 1:  rhea_sensor_SetAttribute("BME280", "pressureOVRS", BME280_PRESSURE_OVERSAMPLING_1X); break;
				case 2:  rhea_sensor_SetAttribute("BME280", "pressureOVRS", BME280_PRESSURE_OVERSAMPLING_2X); break;
				case 4:  rhea_sensor_SetAttribute("BME280", "pressureOVRS", BME280_PRESSURE_OVERSAMPLING_4X); break;
				case 8:  rhea_sensor_SetAttribute("BME280", "pressureOVRS", BME280_PRESSURE_OVERSAMPLING_8X); break;
				case 16: rhea_sensor_SetAttribute("BME280", "pressureOVRS", BME280_PRESSURE_OVERSAMPLING_16X); break;
				};
			}

			// Applying humidity oversampling
			if (m) {
				switch (ovrs) {
				case 1:  rhea_sensor_SetAttribute("BME280", "humidityOVRS", BME280_HUMIDITY_OVERSAMPLING_1X); break;
				case 2:  rhea_sensor_SetAttribute("BME280", "humidityOVRS", BME280_HUMIDITY_OVERSAMPLING_2X); break;
				case 4:  rhea_sensor_SetAttribute("BME280", "humidityOVRS", BME280_HUMIDITY_OVERSAMPLING_4X); break;
				case 8:  rhea_sensor_SetAttribute("BME280", "humidityOVRS", BME280_HUMIDITY_OVERSAMPLING_8X); break;
				case 16: rhea_sensor_SetAttribute("BME280", "humidityOVRS", BME280_HUMIDITY_OVERSAMPLING_16X); break;
				};
			} break;

		case 'T': 
			T = strtol(optarg, NULL, 10);
			if (t) rhea_sensor_SetMeasurementPeriod("BME280", "temperature", T);
			if (p) rhea_sensor_SetMeasurementPeriod("BME280", "pressure", T);
			if (m) rhea_sensor_SetMeasurementPeriod("BME280", "humidity", T);
			break;

		case 'd': d = 1;
			break;

		case 'h': 
			rhea_print_help();
			break;

		default: 
			rhea_print_error();
			break;
		};
	}
    
    if(d) {
        if (t) {
            unsigned temperature = rhea_sensor_GetMeasurement("BME280", "temperature");
            char temp[50] = {0};
            sprintf(temp, "Temperature: %u Celsius\n\r", temperature);
            rhea_uart_WriteString(temp);
        }
    	if (p) {
            unsigned pressure = rhea_sensor_GetMeasurement("BME280", "pressure");
            char temp[50] = {0};
            sprintf(temp, "Pressure: %u Pa\n\r", pressure);
            rhea_uart_WriteString(temp);
        }
    	if (m) {
            unsigned humidity = rhea_sensor_GetMeasurement("BME280", "humidity");
            char temp[50] = {0};
            sprintf(temp, "Humidity: %u %%\n\r", humidity);
            rhea_uart_WriteString(temp);
        }
    }
}

/*
void command_alarm(int argc, const char** argv) {

	// Getopt parameters
	int longopt = 0;
	int opt = 0;
	optind = 1;

	// Flags and option arguments
	int p = 0, id = -1;

	// Parsing options
	while ((opt = getopt_long(argc, argv, "s:gd:rph", alarm_long_options, &longopt)) != -1) {
		switch (opt) {
		case 's':
			// TODO: Parse datetime: optarg, add alarm (check p for persistence)
			break;
		case 'g':
			// TODO: Print alarms
			break;
		case 'd':
			id = strtoul(optarg, NULL, 10);
			// TODO: Delete alarm: id
			break;
		case 'r':
			// TODO: Reset alarms
			break;
		case 'p': p = 1;
			break;
		case 'h':
			// TODO: Print help
			break;
		default:
			// TODO: Print error
			break;
		};
	}
}

void command_datetime(int argc, const char** argv) {

	// Getopt parameters
	int longopt = 0;
	int opt = 0;
	optind = 1;

	// Flags and option parameters


	// Parsing options
	while ((opt = getopt_long(argc, argv, "dts:gh", alarm_long_options, &longopt)) != -1) {
		switch (opt) {
		case 'd':
			// TODO: Print MCP7940N_GetYears() . MCP7940N_GetMonths() . MCP7940N_GetDate();
			break;
		case 't':
			// TODO: Print MCP7940N_GetHours() : MCP7940N_GetMinutes() : MCP7940N_GetSeconds();
			break;
		case 's':
			// TODO: parse optarg, set parameters:
			// MCP7940N_SetYears(), MCP7940N_SetMonths(), MCP7940N_SetDate(), 
			// MCP7940N_SetHours(), MCP7940N_SetMinutes(), MCP7940N_SetSeconds(),
			break;
		case 'g':
			// TODO: Print MCP7940N_GetYears() : MCP7940N_GetMonths() : MCP7940N_GetDate();
			// TODO: Print MCP7940N_GetHours() : MCP7940N_GetMinutes() : MCP7940N_GetSeconds();
			break;
		case 'h':
			// TODO: Print help.
			break;
		default:
			// TODO: Print error.
			break;
		};
	}
}

void command_power(int argc, const char** argv) {
	
	// Getopt parameters
	int longopt = 0;
	int opt = 0;
	optind = 1;

	// Flags and option arguments

	// Parsing options
	while ((opt = getopt_long(argc, argv, "ftuh", alarm_long_options, &longopt)) != -1) {
		switch (opt) {
		case 'f':
			// TODO: Print MCP7940N_GetPowerFailMonth() / MCP7940N_GetPowerFailDate()
			//             MCP7940N_GetPowerFailHour() / MCP7940N_GetPowerFailMinute()
			break;
		case 't':
			// TODO: Print MCP7940N_GetPowerUpMonth() / MCP7940N_GetPowerUpDate()
			//             MCP7940N_GetPowerUpHour() / MCP7940N_GetPowerUpMinute()
			break;
		case 'u':
			// TODO: Print difference between now and fail time
			break;
		case 'h':
			// TODO: Print help
			break;
		default:
			// TODO: Print error
			break;
		};
	}
}
*/


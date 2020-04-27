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
 * @file    menu.c
 * @author  Peter Gyulai
 * @version 1.0.0
 * @date    2020.04.21
 * @brief   Application main menu implementation.
 * @details
 * This file contains the implementation for the application main menu.
 */

// Standard includes
#include <stdio.h>

// Project includes
#include "../../rhea/sensor/sensor.h"
#include "../../rhea/state/state.h"
#include "../../rhea/gfx/gfx.h"
#include "menu.h"


// Application main menu states
enum MainMenuStates {
    
    // Main display states
    TEMPERATURE_MAIN,
    PRESSURE_MAIN,
    HUMIDITY_MAIN,
    
    // Temperature setup 
    TEMPERATURE_SETUP,
    
    // Pressure setup
    PRESSURE_SETUP,
    
    // Humidity setup
    HUMIDITY_SETUP,
    
    // Number of states
    STATE_COUNT
};

// Application inputs
enum MainMenuInputs {
    
    // No input
    NONE, 
    
    // Button pressed input
    BUTTON_ENTER, 
    BUTTON_RIGHT, 
    BUTTON_LEFT,
    
    // Number of inputs
    INPUT_COUNT
};

// Application main menu state-machine
rhea_state_StateMachine mainStateMachine;

// Forward declarations for on-transition actions
void showTemperatureMain(void);
void showTemperaturePeriod(void);
void increaseTemperaturePeriod(void);
void decreaseTemperaturePeriod(void);
void showPressureMain(void);
void showPressurePeriod(void);
void increasePressurePeriod(void);
void decreasePressurePeriod(void);
void showHumidityMain(void);
void showHumidityPeriod(void);
void increaseHumidityPeriod(void);
void decreaseHumidityPeriod(void);


void InitializeMainMenu(void) {
    
    // Setting state and input counts
    mainStateMachine.stateCount = STATE_COUNT;
    mainStateMachine.inputCount = INPUT_COUNT;
    
    // Setting initial state
    mainStateMachine.currentState = TEMPERATURE_MAIN;
    
    // Creating main menu transition table
    rhea_state_Transition mainTransitions[STATE_COUNT][INPUT_COUNT];
    
    // Setting state transitions
    mainStateMachine.transitions = (rhea_state_Transition*) mainTransitions;
    
    // Temperature main transitions
    mainTransitions[TEMPERATURE_MAIN][BUTTON_ENTER] = (rhea_state_Transition) {
        .nextState = TEMPERATURE_SETUP,
        .action = showTemperaturePeriod
    };
    mainTransitions[TEMPERATURE_MAIN][BUTTON_RIGHT] = (rhea_state_Transition) {
        .nextState = PRESSURE_MAIN,
        .action = showPressureMain
    };
    mainTransitions[TEMPERATURE_MAIN][BUTTON_LEFT] = (rhea_state_Transition) {
        .nextState = HUMIDITY_MAIN,
        .action = showHumidityMain
    };
    mainTransitions[TEMPERATURE_MAIN][NONE] = (rhea_state_Transition) {
        .nextState = TEMPERATURE_MAIN,
        .action = showTemperatureMain
    };
    
    // Temperature setup transitions
    mainTransitions[TEMPERATURE_SETUP][BUTTON_ENTER] = (rhea_state_Transition) {
        .nextState = TEMPERATURE_MAIN,
        .action = showTemperatureMain
    };
    mainTransitions[TEMPERATURE_SETUP][BUTTON_RIGHT] = (rhea_state_Transition) {
        .nextState = TEMPERATURE_SETUP,
        .action = increaseTemperaturePeriod
    };
    mainTransitions[TEMPERATURE_SETUP][BUTTON_LEFT] = (rhea_state_Transition) {
        .nextState = TEMPERATURE_SETUP,
        .action = decreaseTemperaturePeriod
    };
    mainTransitions[TEMPERATURE_SETUP][NONE] = (rhea_state_Transition) {
        .nextState = TEMPERATURE_SETUP,
        .action = showTemperaturePeriod
    };
    
    // Pressure main transitions
    mainTransitions[PRESSURE_MAIN][BUTTON_ENTER] = (rhea_state_Transition) {
        .nextState = PRESSURE_SETUP,
        .action = showPressurePeriod
    };
    mainTransitions[PRESSURE_MAIN][BUTTON_RIGHT] = (rhea_state_Transition) {
        .nextState = HUMIDITY_MAIN,
        .action = showHumidityMain
    };
    mainTransitions[PRESSURE_MAIN][BUTTON_LEFT] = (rhea_state_Transition) {
        .nextState = TEMPERATURE_MAIN,
        .action = showTemperatureMain
    };
    mainTransitions[PRESSURE_MAIN][NONE] = (rhea_state_Transition) {
        .nextState = PRESSURE_MAIN,
        .action = showPressureMain
    };
    
    // Pressure setup transitions
    mainTransitions[PRESSURE_SETUP][BUTTON_ENTER] = (rhea_state_Transition) {
        .nextState = PRESSURE_MAIN,
        .action = showPressureMain
    };
    mainTransitions[PRESSURE_SETUP][BUTTON_RIGHT] = (rhea_state_Transition) {
        .nextState = PRESSURE_SETUP,
        .action = increasePressurePeriod
    };
    mainTransitions[PRESSURE_SETUP][BUTTON_LEFT] = (rhea_state_Transition) {
        .nextState = PRESSURE_SETUP,
        .action = decreasePressurePeriod
    };
    mainTransitions[PRESSURE_SETUP][NONE] = (rhea_state_Transition) {
        .nextState = PRESSURE_SETUP,
        .action = showPressurePeriod
    };
    
    // Humidity main transitions
    mainTransitions[HUMIDITY_MAIN][BUTTON_ENTER] = (rhea_state_Transition) {
        .nextState = HUMIDITY_SETUP,
        .action = showHumidityPeriod
    };
    mainTransitions[HUMIDITY_MAIN][BUTTON_RIGHT] = (rhea_state_Transition) {
        .nextState = TEMPERATURE_MAIN,
        .action = showTemperatureMain
    };
    mainTransitions[HUMIDITY_MAIN][BUTTON_LEFT] = (rhea_state_Transition) {
        .nextState = PRESSURE_MAIN,
        .action = showPressureMain
    };
    mainTransitions[HUMIDITY_MAIN][NONE] = (rhea_state_Transition) {
        .nextState = HUMIDITY_MAIN,
        .action = showHumidityMain
    };
    
    // Humidity setup transitions
    mainTransitions[HUMIDITY_SETUP][BUTTON_ENTER] = (rhea_state_Transition) {
        .nextState = HUMIDITY_MAIN,
        .action = showHumidityMain
    };
    mainTransitions[HUMIDITY_SETUP][BUTTON_RIGHT] = (rhea_state_Transition) {
        .nextState = HUMIDITY_SETUP,
        .action = increaseHumidityPeriod
    };
    mainTransitions[HUMIDITY_SETUP][BUTTON_LEFT] = (rhea_state_Transition) {
        .nextState = HUMIDITY_SETUP,
        .action = decreaseHumidityPeriod
    };
    mainTransitions[HUMIDITY_SETUP][NONE] = (rhea_state_Transition) {
        .nextState = HUMIDITY_SETUP,
        .action = showHumidityPeriod
    };
}

void StepMainMenuStateMachine(volatile uint8_t *button_enter_pressed,
                              volatile uint8_t *button_right_pressed,
                              volatile uint8_t *button_left_pressed)
{
    // Default input identifier
    rhea_state_inputID input = NONE;
    
    // Checking input buttons
    if(*button_enter_pressed) {
        input = BUTTON_ENTER;
        *button_enter_pressed = 0;
    } 
    else if(*button_right_pressed) {
        input = BUTTON_RIGHT;
        *button_right_pressed = 0;
    }
    else if(*button_left_pressed) {
        input = BUTTON_LEFT;
        *button_left_pressed = 0;
    }
    
    // Advancing main menu state-machine
    rhea_state_nextState(&mainStateMachine, input);
}

void showTemperatureMain(void) {
    
    // Creating output buffer
    char buffer[32] = {0};
    
    // Populating buffer
    sprintf(buffer, "Temperature: %lf ", rhea_sensor_GetMeasurement("BME280", "temperature"));
    
    // Printing to display
    rhea_gfx_Clear();
    rhea_gfx_Print(buffer);
    rhea_gfx_PrintSymbol(95); // Codefont_8x8_Celsius symbol
}

void showTemperaturePeriod(void) {
    
    // Creating output buffer
    char buffer[32] = {0};
    
    // Populating buffer
    sprintf(buffer, "T_period: %u ms", (unsigned) rhea_sensor_GetMeasurementPeriod("BME280", "temperature"));
    
    // Printing to display
    rhea_gfx_Clear();
    rhea_gfx_Print(buffer);
}

void increaseTemperaturePeriod(void) {
    
    // Querying current period
    uint64_t period = rhea_sensor_GetMeasurementPeriod("BME280", "temperature");
    
    // Increasing period
    rhea_sensor_SetMeasurementPeriod("BME280", "temperature", ++period);
}

void decreaseTemperaturePeriod(void) {
    
    // Querying current period
    uint64_t period = rhea_sensor_GetMeasurementPeriod("BME280", "temperature");
    
    // Decreasing period
    rhea_sensor_SetMeasurementPeriod("BME280", "temperature", --period);
}

void showPressureMain(void) {
    
    // Creating output buffer
    char buffer[32] = {0};
    
    // Populating buffer
    sprintf(buffer, "Pressure: %lf ", rhea_sensor_GetMeasurement("BME280", "pressure"));
    
    // Printing to display
    rhea_gfx_Clear();
    rhea_gfx_Print(buffer);
    rhea_gfx_PrintSymbol(98); // Codefont_8x8_Pascal symbol
}

void showPressurePeriod(void) {
    
    // Creating output buffer
    char buffer[32] = {0};
    
    // Populating buffer
    sprintf(buffer, "P_period: %u ms", (unsigned) rhea_sensor_GetMeasurementPeriod("BME280", "pressure"));
    
    // Printing to display
    rhea_gfx_Clear();
    rhea_gfx_Print(buffer);
}

void increasePressurePeriod(void) {
    
    // Querying current period
    uint64_t period = rhea_sensor_GetMeasurementPeriod("BME280", "pressure");
    
    // Increasing period
    rhea_sensor_SetMeasurementPeriod("BME280", "pressure", ++period);
}

void decreasePressurePeriod(void) {
    
    // Querying current period
    uint64_t period = rhea_sensor_GetMeasurementPeriod("BME280", "pressure");
    
    // Increasing period
    rhea_sensor_SetMeasurementPeriod("BME280", "pressure", --period);
}

void showHumidityMain(void) {
    
    // Creating output buffer
    char buffer[32] = {0};
    
    // Populating buffer
    sprintf(buffer, "Humidity: %lf %%", rhea_sensor_GetMeasurement("BME280", "humidity"));
    
    // Printing to display
    rhea_gfx_Clear();
    rhea_gfx_Print(buffer);
}

void showHumidityPeriod(void) {
    
    // Creating output buffer
    char buffer[32] = {0};
    
    // Populating buffer
    sprintf(buffer, "H_period: %u ms", (unsigned) rhea_sensor_GetMeasurementPeriod("BME280", "humidity"));
    
    // Printing to display
    rhea_gfx_Clear();
    rhea_gfx_Print(buffer);
}

void increaseHumidityPeriod(void) {
    
    // Querying current period
    uint64_t period = rhea_sensor_GetMeasurementPeriod("BME280", "humidity");
    
    // Increasing period
    rhea_sensor_SetMeasurementPeriod("BME280", "humidity", ++period);
}

void decreaseHumidityPeriod(void) {
    
    // Querying current period
    uint64_t period = rhea_sensor_GetMeasurementPeriod("BME280", "humidity");
    
    // Increasing period
    rhea_sensor_SetMeasurementPeriod("BME280", "humidity", --period);
}
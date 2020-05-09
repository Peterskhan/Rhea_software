#include "project.h"

// Including Rhea libraries
#include "rhea/i2c/i2c.h"
#include "rhea/gfx/gfx.h"
#include "rhea/rtc/rtc.h"
#include "rhea/uart/uart.h"
#include "rhea/sensor/sensor.h"

// Including application headers
#include "command/command.h"
#include "input/input.h"
#include "menu/menu.h"

// Including standard headers
#include <stdio.h>


// Test function for graphics display
void test_graphics(void) {
    rhea_gfx_Clear();
    rhea_gfx_Print("Hello\nBello\n");
    rhea_gfx_PrintSymbol(95);
    rhea_gfx_PrintSymbol(96);
    rhea_gfx_PrintSymbol(97);
    rhea_gfx_PrintSymbol(98);
    rhea_gfx_PrintSymbol(99);
}

void test_sensor(void) {
        rhea_sensor_SetMeasurementPeriod("BME280", "temperature", 250);
        rhea_sensor_SetMeasurementPeriod("BME280", "pressure", 250);
        rhea_sensor_SetMeasurementPeriod("BME280", "humidity", 250);
        
        CyDelay(250);

        int temperatureInt = (int) rhea_sensor_GetMeasurement("BME280", "temperature");;
        int pressureInt = (int) rhea_sensor_GetMeasurement("BME280", "pressure");
        int humidityInt = (int) rhea_sensor_GetMeasurement("BME280", "humidity");
        
        char buffer[50];
        sprintf(buffer, "T: %d ", temperatureInt);
        rhea_gfx_SetCursor(0,0);
        rhea_gfx_Print(buffer); rhea_gfx_PrintSymbol(95); rhea_gfx_Print("\n");
        
        sprintf(buffer, "P: %d ", pressureInt); 
        rhea_gfx_Print(buffer); rhea_gfx_PrintSymbol(98); rhea_gfx_Print("\n");
        
        sprintf(buffer, "H: %d %%\n", humidityInt);
        rhea_gfx_Print(buffer);
        
        rhea_gfx_Refresh();
}

int main(void)
{ 
    // Enabling global interrupts
    CyGlobalIntEnable;
    
    // Initializing Rhea libraries
    rhea_i2c_Initialize();
    rhea_gfx_Initialize();
    //rhea_rtc_Initialize();
    rhea_uart_Initialize();
    rhea_sensor_Initialize();

    // Initializing application
    InitializeInputButtonInterrupts();
    InitializeSerialCommandLine();
    InitializeMainMenu();
        
    // Showing start-up logo
    rhea_gfx_DrawSymbol(3,1,103);
    rhea_gfx_Refresh();
    CyDelay(2000);
    
    // Executing application logic
    for(;;)
    {     
        
        // Handling UART command line 
        ProcessCommandLine();
        
        // Handling RTC alarms
        // rhea_rtc_HandleAlarms();
        
        // Processing user input 
        StepMainMenuStateMachine(&button_enter_pressed, 
                                 &button_right_pressed, 
                                 &button_left_pressed);
    }
}

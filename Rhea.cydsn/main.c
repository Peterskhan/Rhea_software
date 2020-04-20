#include "project.h"

// Including Rhea libraries
#include "rhea/i2c/i2c.h"
#include "rhea/gfx/gfx.h"
#include "rhea/rtc/rtc.h"
#include "rhea/uart/uart.h"
#include "rhea/sensor/sensor.h"

int main(void)
{
    // Initializing Rhea libraries
    rhea_i2c_Initialize();
    rhea_gfx_Initialize();
    rhea_rtc_Initialize();
    rhea_uart_Initialize();
    rhea_sensor_Initialize();

    // Initializing application
    // ...
    
    // Enabling global interrupts
    CyGlobalIntEnable;

    // Executing application logic
    for(;;)
    {
        // ...
    }
}

#include "Arduino_FreeRTOS.h"
#include "LED.h"
#include "Task_LED.h"
#include "Task_LCD.h"
#include "Task_Bluetooth.h"


void setup()
{
    LED_TurnOff(LED_Internal);
    Task_LED_Initialize();
    Task_LCD_Initialize();
    Task_Bluetooth_Initialize();
}

void loop()
{
    if (LED_isOn(LED_Internal))
    {
        LED_TurnOff(LED_Internal);
    }
    else
    {
        LED_TurnOn(LED_Internal);
    }
    _delay_ms(500);
}

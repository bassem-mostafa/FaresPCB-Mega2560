#include "Arduino_FreeRTOS.h"

#include "LED.h"
#include "Bluetooth.h"
#include "LCD.h"
#include "Task_LED.h"
#include "Task_LCD.h"

uint8_t buffer[20];
uint8_t length;

void setup()
{
    LED_TurnOff(LED_Internal);
    Bluetooth_Initialize();
    Bluetooth_Write((uint8_t*)"\nFaresPCB Ready\n", strlen("\nFaresPCB Ready\n"));
    Task_LED_Initialize();
    Task_LCD_Initialize();
}

void loop()
{
    if ( ( length = Bluetooth_Read(buffer, sizeof(buffer)) ) > 0)
    {
        Bluetooth_Write(buffer, length);
    }
    if (LED_isOn(LED_Internal))
    {
        LED_TurnOff(LED_Internal);
    }
    else
    {
        LED_TurnOn(LED_Internal);
        static uint8_t timeout = 0; // in seconds
        if (timeout > 0)
        {
            --timeout;
        }
        else
        {
            timeout = 3; // in seconds
            static enum
            {
                DEMO_None = 0,
                DEMO_1,
                DEMO_2,
                DEMO_3,
                DEMO_4,
                DEMO_5,
                DEMO_6,
                DEMO_7,
            } demo = DEMO_1;
            switch (demo)
            {
                case DEMO_1:
                    Task_LED_Request(Task_LED_Request_On);
                    Task_LCD_Request(Task_LCD_Request_On);
                    Task_LCD_Request(Task_LCD_Request_Loading);
                    demo = DEMO_2;
                    break;
                case DEMO_2:
                    Task_LED_Request(Task_LED_Request_Off);
                    Task_LCD_Request(Task_LCD_Request_DateTime);
                    demo = DEMO_3;
                    break;
                case DEMO_3:
                    Task_LED_Request(Task_LED_Request_Blink);
                    Task_LCD_Request(Task_LCD_Request_Bluetooth);
                    demo = DEMO_4;
                    break;
                case DEMO_4:
                    Task_LED_Request(Task_LED_Request_Increase);
                    Task_LCD_Request(Task_LCD_Request_Temperature);
                    demo = DEMO_5;
                    break;
                case DEMO_5:
                    Task_LED_Request(Task_LED_Request_Decrease);
                    Task_LCD_Request(Task_LCD_Request_Distance);
                    demo = DEMO_6;
                    break;
                case DEMO_6:
                    Task_LCD_Request(Task_LCD_Request_Off);
                    demo = DEMO_1;
                    break;
                default:
                    demo = DEMO_1;
                    break;
            }
        }

    }
    _delay_ms(500);
}

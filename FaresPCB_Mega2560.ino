#include "Arduino_FreeRTOS.h"

#include "LED.h"
#include "Bluetooth.h"

uint8_t buffer[20];
uint8_t length;

void setup()
{
    LED_TurnOff(LED_Internal);
    Bluetooth_Initialize();
    Bluetooth_Write((uint8_t*)"\nFaresPCB Ready\n", strlen("\nFaresPCB Ready\n"));
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
    }
    _delay_ms(500);
}

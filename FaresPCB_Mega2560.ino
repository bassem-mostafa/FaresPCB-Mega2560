#include "Arduino_FreeRTOS.h"
#include "LED.h"
#include "Task_LED.h"
#include "Task_LCD.h"
#include "Task_Bluetooth.h"
#include "Task_7Segment.h"

#define _VERIFY_MONTH(MMM) (__TIMESTAMP__[4] == MMM[0] && __TIMESTAMP__[5] == MMM[1] && __TIMESTAMP__[6] == MMM[2])

#define _VALUE_UNKNOWN  "??"
#define _VALUE_YEAR     ( (const char[]){__TIMESTAMP__[22], __TIMESTAMP__[23]} )
#define _VALUE_MONTH    ( _VERIFY_MONTH("Jan") ? "01" : \
                          _VERIFY_MONTH("Feb") ? "02" : \
                          _VERIFY_MONTH("Mar") ? "03" : \
                          _VERIFY_MONTH("Apr") ? "04" : \
                          _VERIFY_MONTH("May") ? "05" : \
                          _VERIFY_MONTH("Jun") ? "06" : \
                          _VERIFY_MONTH("Jul") ? "07" : \
                          _VERIFY_MONTH("Aug") ? "08" : \
                          _VERIFY_MONTH("Sep") ? "09" : \
                          _VERIFY_MONTH("Oct") ? "10" : \
                          _VERIFY_MONTH("Nov") ? "11" : \
                          _VERIFY_MONTH("Dec") ? "12" : \
                          _VALUE_UNKNOWN )
#define _VALUE_DAY      ( (const char[]){__TIMESTAMP__[ 8], __TIMESTAMP__[ 9]} )
#define _VALUE_HOUR     ( (const char[]){__TIMESTAMP__[11], __TIMESTAMP__[12]} )
#define _VALUE_MINUTE   ( (const char[]){__TIMESTAMP__[14], __TIMESTAMP__[15]} )
#define _VALUE_SECOND   ( (const char[]){__TIMESTAMP__[17], __TIMESTAMP__[18]} )

extern const char FW_VERSION[30] = {
    _VALUE_YEAR[0], _VALUE_YEAR[1],
    '.',
    _VALUE_MONTH[0], _VALUE_MONTH[1],
    '.',
    _VALUE_DAY[0], _VALUE_DAY[1],
    '.',
    _VALUE_HOUR[0], _VALUE_HOUR[1],
    '.',
    _VALUE_MINUTE[0], _VALUE_MINUTE[1],
    '.',
    _VALUE_SECOND[0], _VALUE_SECOND[1],
    '\0',
};

void setup()
{
    LED_TurnOff(LED_Internal);
    Task_LED_Initialize();
    Task_LCD_Initialize();
    Task_Bluetooth_Initialize();
    Task_7Segment_Initialize();
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

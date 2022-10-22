#include "Platform.h"
#include "LED.h"
#include "string.h"

#ifndef __TIMESTAMP__
// Reference: https://gcc.gnu.org/onlinedocs/cpp/Common-Predefined-Macros.html
#define __TIMESTAMP__ "??? ??? ?? ??:??:?? ????" /* Sun Sep 16 01:03:52 1973 */
#endif

#define _MONTH_IS(MMM) ( __TIMESTAMP__[4] == MMM[0] && __TIMESTAMP__[5] == MMM[1] && __TIMESTAMP__[6] == MMM[2] )
#define _YEAR          ( (const char[]){__TIMESTAMP__[22], __TIMESTAMP__[23]} )
#define _MONTH         ( _MONTH_IS("Jan") ? "01" : \
                         _MONTH_IS("Feb") ? "02" : \
                         _MONTH_IS("Mar") ? "03" : \
                         _MONTH_IS("Apr") ? "04" : \
                         _MONTH_IS("May") ? "05" : \
                         _MONTH_IS("Jun") ? "06" : \
                         _MONTH_IS("Jul") ? "07" : \
                         _MONTH_IS("Aug") ? "08" : \
                         _MONTH_IS("Sep") ? "09" : \
                         _MONTH_IS("Oct") ? "10" : \
                         _MONTH_IS("Nov") ? "11" : \
                         _MONTH_IS("Dec") ? "12" : \
                                            "??" )
#define _DAY           ( (const char[]){__TIMESTAMP__[ 8], __TIMESTAMP__[ 9]} )
#define _HOUR          ( (const char[]){__TIMESTAMP__[11], __TIMESTAMP__[12]} )
#define _MINUTE        ( (const char[]){__TIMESTAMP__[14], __TIMESTAMP__[15]} )
#define _SECOND        ( (const char[]){__TIMESTAMP__[17], __TIMESTAMP__[18]} )

const char * _FW_LABEL = strrchr(__FILE__, '\\');
const char _FW_VERSION[30] =
{
        _YEAR[0], _YEAR[1],
        '.',
        _MONTH[0], _MONTH[1],
        '.',
        _DAY[0], _DAY[1],
        '.',
        _HOUR[0], _HOUR[1],
        '.',
        _MINUTE[0], _MINUTE[1],
        '.',
        _SECOND[0], _SECOND[1],
        '\0',
};

void setup()
{
    Serial.begin(115200);
    while(!Serial);
    Serial.print("FW ");
    Serial.print(_FW_LABEL);
    Serial.print(" ");
    Serial.print(_FW_VERSION);
    Serial.println("\n");
}

void loop()
{
    LED_IntensitySet(LED_Internal, LED_Intensity_Zero);
    LED_IntensitySet(LED_1,        LED_Intensity_Zero);
    LED_IntensitySet(LED_2,        LED_Intensity_Zero);
    LED_IntensitySet(LED_3,        LED_Intensity_Zero);
    LED_IntensitySet(LED_4,        LED_Intensity_Zero);
    LED_IntensitySet(LED_5,        LED_Intensity_Zero);
    LED_IntensitySet(LED_RGB,      LED_Intensity_Zero);
    _delay_ms(500);
    LED_IntensitySet(LED_Internal, LED_Intensity_Full);
    LED_IntensitySet(LED_1,        LED_Intensity_Full);
    LED_IntensitySet(LED_2,        LED_Intensity_Full);
    LED_IntensitySet(LED_3,        LED_Intensity_Full);
    LED_IntensitySet(LED_4,        LED_Intensity_Full);
    LED_IntensitySet(LED_5,        LED_Intensity_Full);
    // LED RGB Blinking With Colors
    {
        static LED_Intensity_t LED_Intensity = LED_Intensity_Red;
        switch (LED_Intensity)
        {
            case LED_Intensity_Red:
                LED_IntensitySet(LED_RGB, LED_Intensity_Red);
                LED_Intensity = LED_Intensity_Green;
                break;
            case LED_Intensity_Green:
                LED_IntensitySet(LED_RGB, LED_Intensity_Green);
                LED_Intensity = LED_Intensity_Blue;
                break;
            case LED_Intensity_Blue:
                LED_IntensitySet(LED_RGB, LED_Intensity_Blue);
                LED_Intensity = LED_Intensity_Yellow;
                break;
            case LED_Intensity_Yellow:
                LED_IntensitySet(LED_RGB, LED_Intensity_Yellow);
                LED_Intensity = LED_Intensity_Cyan;
                break;
            case LED_Intensity_Cyan:
                LED_IntensitySet(LED_RGB, LED_Intensity_Cyan);
                LED_Intensity = LED_Intensity_Magenta;
                break;
            case LED_Intensity_Magenta:
                LED_IntensitySet(LED_RGB, LED_Intensity_Magenta);
                LED_Intensity = LED_Intensity_Full;
                break;
            case LED_Intensity_Full:
                LED_IntensitySet(LED_RGB, LED_Intensity_Full);
                LED_Intensity = LED_Intensity_Red;
                break;
            default:
                LED_Intensity = LED_Intensity_Red;
                break;
        }
    }
    _delay_ms(500);
}

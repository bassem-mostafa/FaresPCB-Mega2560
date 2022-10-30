#include "Platform.h"
#include "string.h"
#include "stdio.h"
#include "Buzzer.h"
#include "util/delay.h"

#ifndef __TIMESTAMP__
// Reference: https://gcc.gnu.org/onlinedocs/cpp/Common-Predefined-Macros.html
#define __TIMESTAMP__ "??? ??? ?? ??:??:?? ????" /* Sun Sep 16 01:03:52 1973 */
#endif

#define _MONTH_IS(MMM) ( __TIMESTAMP__[4] == MMM[0] && __TIMESTAMP__[5] == MMM[1] && __TIMESTAMP__[6] == MMM[2] )
#define _WEEKDAY       ( (const char[]){__TIMESTAMP__[0], __TIMESTAMP__[1], __TIMESTAMP__[2]} )
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

const char * _FW_LABEL = strrchr(__FILE__, '\\') + 1;
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

const Note_t Mario_Theme_Underworld[] =
{
        Note_C4, Note_C5, Note_A3, Note_A4,
        Note_A3S, Note_A4S, 0,
        0,
        Note_C4, Note_C5, Note_A3, Note_A4,
        Note_A3S, Note_A4S, 0,
        0,
        Note_F3, Note_F4, Note_D3, Note_D4,
        Note_D3S, Note_D4S, 0,
        0,
        Note_F3, Note_F4, Note_D3, Note_D4,
        Note_D3S, Note_D4S, 0,
        0, Note_D4S, Note_C4S, Note_D4,
        Note_C4S, Note_D4S,
        Note_D4S, Note_G3S,
        Note_G3, Note_C4S,
        Note_C4, Note_F4S,Note_F4, Note_E3, Note_A4S, Note_A4,
        Note_G4S, Note_D4S, Note_B3,
        Note_A3S, Note_A3, Note_G3S,
        0, 0, 0
};

const int Mario_Theme_Underworld_Tempo[] = {
        12, 12, 12, 12,
        12, 12, 6,
        3,
        12, 12, 12, 12,
        12, 12, 6,
        3,
        12, 12, 12, 12,
        12, 12, 6,
        3,
        12, 12, 12, 12,
        12, 12, 6,
        6, 18, 18, 18,
        6, 6,
        6, 6,
        6, 6,
        18, 18, 18,18, 18, 18,
        10, 10, 10,
        10, 10, 10,
        3, 3, 3
};

void setup()
{
    char FW_Info[50];
    snprintf(FW_Info, sizeof(FW_Info), "\nFW %s V%s\n", _FW_LABEL, _FW_VERSION);
    FW_Info[sizeof(FW_Info)-1] = '\0';

    Platform_USART_Setting_t Platform_USART_Setting = NULL;
    Platform_USART_Setting_Initialize(&Platform_USART_Setting);
    Platform_USART_Setting_Baudrate_Set(Platform_USART_Setting, Platform_USART_Baudrate_115200);
    Platform_USART_Setup(Platform_USART_USB, Platform_USART_Setting);

    Platform_USART_Write
    (
            Platform_USART_USB,
            (Platform_USART_Data_t)FW_Info,
            (Platform_USART_Data_Length_t)strlen(FW_Info)
    );
}

void loop()
{
    do
    {
        static bool isDone = false;
        if (isDone) break;
        const uint32_t Note_Period = 1000;
        const double Note_Period_Pause_Factor = 1.3;
        for (uint32_t i = 0; i < (sizeof(Mario_Theme_Underworld)/sizeof(Mario_Theme_Underworld[0])); ++i)
        {
            const uint32_t Note_Duration = Note_Period/Mario_Theme_Underworld_Tempo[0];
            Buzzer_TurnOn(Mario_Theme_Underworld[i], Note_Duration);
            _delay_ms(Note_Period_Pause_Factor*Note_Duration);
        }
        isDone = true;
    }
    while(0);
}

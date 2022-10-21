#include "Platform.h"
#include "string.h"
#include "stdio.h"

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
    char FW_Info[50];
    snprintf(FW_Info, sizeof(FW_Info), "\nFW %s V%s\n", _FW_LABEL, _FW_VERSION);
    Platform_USART_Write
    (
            Platform_USART_1,
            Platform_USART_Baudrate_115200,
            (uint8_t*)FW_Info,
            strlen(FW_Info)
    );
    const char User_Prompt[] = "Write 10 Characters";
    Platform_USART_Write
    (
            Platform_USART_1,
            Platform_USART_Baudrate_115200,
            (uint8_t*)User_Prompt,
            strlen(User_Prompt)
    );
    char User_Input[11];
    memset(User_Input, 0, sizeof(User_Input));
    Platform_USART_Read
    (
            Platform_USART_1,
            Platform_USART_Baudrate_115200,
            (uint8_t*)User_Input,
            strlen(User_Input)
    );
    char User_Response[50];
    snprintf(User_Response, sizeof(User_Response), "\n\nYou've Entered %s\n\nThanks", User_Input);
    Platform_USART_Write
    (
            Platform_USART_1,
            Platform_USART_Baudrate_115200,
            (uint8_t*)User_Response,
            strlen(User_Response)
    );
}

void loop()
{
    do
    {
        static bool demo_done = false;
        if (demo_done) break;
        static Platform_Pin_t Platform_Pin_LED = Platform_Pin_0;
        Platform_Pin_Setup(Platform_Pin_LED, Platform_Pin_Mode_OUTPUT);
        Platform_Pin_Write(Platform_Pin_LED, Platform_Pin_Value_HIGH);
        _delay_ms(1000);
        Platform_Pin_Write(Platform_Pin_LED, Platform_Pin_Value_LOW);
        _delay_ms(1000);
        Platform_Pin_Setup(Platform_Pin_LED, Platform_Pin_Mode_TRI_STATE);
    }
    while(0);
}
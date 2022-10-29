#include "Platform.h"
#include "string.h"
#include "stdio.h"
#include "LCD.h"
#include "RTC.h"

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

    LCD_Setup(LCD_Custom_Character_1, LCD_Icon_Calendar);
    LCD_Setup(LCD_Custom_Character_2, LCD_Icon_Clock);
    LCD_LightOn();
}

void loop()
{
    do
    {
        static const char WeekDay[][4] = {"???", "Sat", "Sun", "Mon", "Tue", "Wed", "Thu", "Fri"};
        static const char DayPeriod[][3] = {"  ", "AM", "PM"};
        static LCD_Screen_t LCD_Screen = {"                ", "                "};
        static RTC_Date_t RTC_Date = RTC_DateGet();
        static RTC_Time_t RTC_Time = RTC_TimeGet();

        RTC_Date = RTC_DateGet();
        RTC_Time = RTC_TimeGet();
        LCD_Screen[0][0] = LCD_Custom_Character_1;
        snprintf((char*)&LCD_Screen[0][2], LCD_SCREEN_WIDTH-1, "%3s %2d/%2d/%4d", WeekDay[RTC_Date.weekday], RTC_Date.day, RTC_Date.month, RTC_Date.year);
        LCD_Screen[1][0] = LCD_Custom_Character_2;
        snprintf((char*)&LCD_Screen[1][5], LCD_SCREEN_WIDTH-1, "%02d:%02d:%02d %2s", RTC_Time.hour, RTC_Time.minute, RTC_Time.second, DayPeriod[RTC_Time.period]);

        LCD_Write(LCD_Screen);
        _delay_ms(250);
    }
    while(0);
}

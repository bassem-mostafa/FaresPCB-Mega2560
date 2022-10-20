#include "Arduino.h"
#include "Arduino_FreeRTOS.h"
#include "string.h"
#include "LCD.h"

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
    LCD_Setup(LCD_Custom_Character_1, LCD_Icon_Bar_Loading_StartEmpty);
    LCD_Setup(LCD_Custom_Character_2, LCD_Icon_Bar_Loading_StartFull);
    LCD_Setup(LCD_Custom_Character_3, LCD_Icon_Bar_Loading_MiddleEmpty);
    LCD_Setup(LCD_Custom_Character_4, LCD_Icon_Bar_Loading_MiddleHalf);
    LCD_Setup(LCD_Custom_Character_5, LCD_Icon_Bar_Loading_MiddleFull);
    LCD_Setup(LCD_Custom_Character_6, LCD_Icon_Bar_Loading_EndEmpty);
    LCD_Setup(LCD_Custom_Character_7, LCD_Icon_Bar_Loading_EndFull);
    LCD_LightOn();
}

void loop()
{
    static uint8_t loading_bar_index = -1;
    static LCD_Screen_t LCD_Screen_Loading =
    {
            " Loading Screen ",
            {
                    LCD_Custom_Character_1,
                    LCD_Custom_Character_3,
                    LCD_Custom_Character_3,
                    LCD_Custom_Character_3,
                    LCD_Custom_Character_3,
                    LCD_Custom_Character_3,
                    LCD_Custom_Character_3,
                    LCD_Custom_Character_3,
                    LCD_Custom_Character_3,
                    LCD_Custom_Character_3,
                    LCD_Custom_Character_3,
                    LCD_Custom_Character_3,
                    LCD_Custom_Character_3,
                    LCD_Custom_Character_3,
                    LCD_Custom_Character_3,
                    LCD_Custom_Character_6},
    };
    do
    {
        if (loading_bar_index == -1)
        {
            loading_bar_index = 0;
            break;
        }

        if (loading_bar_index > LCD_SCREEN_WIDTH)
        {
            break;
        }

        if (loading_bar_index == LCD_SCREEN_WIDTH)
        {
            loading_bar_index++;
            strcpy((char*)LCD_Screen_Loading[1], "      Done      ");
            break;
        }

        switch (LCD_Screen_Loading[1][loading_bar_index])
        {
            case LCD_Custom_Character_1:
                LCD_Screen_Loading[1][loading_bar_index++] = LCD_Custom_Character_2;
                break;
            case LCD_Custom_Character_3:
                LCD_Screen_Loading[1][loading_bar_index] = LCD_Custom_Character_4;
                break;
            case LCD_Custom_Character_4:
                LCD_Screen_Loading[1][loading_bar_index++] = LCD_Custom_Character_5;
                break;
            case LCD_Custom_Character_6:
                LCD_Screen_Loading[1][loading_bar_index++] = LCD_Custom_Character_7;
                break;
            default:
                strcpy((char*)LCD_Screen_Loading[1], "      Error     ");
                loading_bar_index = LCD_SCREEN_WIDTH + 1;
                break;
        }
    }
    while(0);
    LCD_Write(LCD_Screen_Loading);
}

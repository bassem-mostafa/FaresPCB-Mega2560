#include "Platform.h"
#include "string.h"
#include "stdio.h"

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


// Reference: https://www.mobilefish.com/tutorials/rtttl/rtttl_quickguide_specification.html
#define _default_duration           RTTTL_Duration_4
#define _default_octave             RTTTL_Octave_6
#define _default_beats_per_minute   RTTTL_Beats_Per_Minute_63

typedef char RTTTL_Name_t[20];

typedef enum RTTTL_Beats_Per_Minute_t
{
    RTTTL_Beats_Per_Minute_25  = 25,
    RTTTL_Beats_Per_Minute_28  = 28,
    RTTTL_Beats_Per_Minute_31  = 31,
    RTTTL_Beats_Per_Minute_35  = 35,
    RTTTL_Beats_Per_Minute_40  = 40,
    RTTTL_Beats_Per_Minute_45  = 45,
    RTTTL_Beats_Per_Minute_50  = 50,
    RTTTL_Beats_Per_Minute_56  = 56,
    RTTTL_Beats_Per_Minute_63  = 63,
    RTTTL_Beats_Per_Minute_70  = 70,
    RTTTL_Beats_Per_Minute_80  = 80,
    RTTTL_Beats_Per_Minute_90  = 90,
    RTTTL_Beats_Per_Minute_100 = 100,
    RTTTL_Beats_Per_Minute_112 = 112,
    RTTTL_Beats_Per_Minute_125 = 125,
    RTTTL_Beats_Per_Minute_140 = 140,
    RTTTL_Beats_Per_Minute_160 = 160,
    RTTTL_Beats_Per_Minute_180 = 180,
    RTTTL_Beats_Per_Minute_200 = 200,
    RTTTL_Beats_Per_Minute_225 = 225,
    RTTTL_Beats_Per_Minute_250 = 250,
    RTTTL_Beats_Per_Minute_285 = 285,
    RTTTL_Beats_Per_Minute_320 = 320,
    RTTTL_Beats_Per_Minute_355 = 355,
    RTTTL_Beats_Per_Minute_400 = 400,
    RTTTL_Beats_Per_Minute_450 = 450,
    RTTTL_Beats_Per_Minute_500 = 500,
    RTTTL_Beats_Per_Minute_565 = 565,
    RTTTL_Beats_Per_Minute_635 = 635,
    RTTTL_Beats_Per_Minute_715 = 715,
    RTTTL_Beats_Per_Minute_800 = 800,
    RTTTL_Beats_Per_Minute_900 = 900,
} RTTTL_Beats_Per_Minute_t;

typedef enum RTTTL_Octave_t
{
    RTTTL_Octave_4 = 4,
    RTTTL_Octave_5 = 5,
    RTTTL_Octave_6 = 6,
    RTTTL_Octave_7 = 7,
} RTTTL_Octave_t;

typedef enum RTTTL_Duration_t
{
    RTTTL_Duration_1  = 1 ,
    RTTTL_Duration_2  = 2 ,
    RTTTL_Duration_4  = 4 ,
    RTTTL_Duration_8  = 8 ,
    RTTTL_Duration_16 = 16,
    RTTTL_Duration_32 = 32,
} RTTTL_Duration_t;

typedef char* RTTTL_Data_t;

typedef struct RTTTL_t
{
        RTTTL_Name_t RTTTL_Name;
        struct
        {
                RTTTL_Beats_Per_Minute_t RTTTL_Beats_Per_Minute;
                RTTTL_Octave_t RTTTL_Octave;
                RTTTL_Duration_t RTTTL_Duration;
        };
        RTTTL_Data_t RTTTL_Data;
} RTTTL_t;

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
    const char description[] = ""
            "\nFor Usage Guide Use The Following Link"
            "\n\thttps://www.mobilefish.com/tutorials/rtttl/rtttl_quickguide_specification.html"
            "\nPlease Write ';' without quotes at the end of the RTTTL melody"
            "\n";
    Platform_USART_Write
    (
            Platform_USART_USB,
            (Platform_USART_Data_t)description,
            (Platform_USART_Data_Length_t)strlen(description)
    );
}

void loop()
{
    static RTTTL_t RTTTL;
    do
    {
        static bool isInitialized = false;
        if (isInitialized) break;
        RTTTL.RTTTL_Beats_Per_Minute = _default_beats_per_minute;
        RTTTL.RTTTL_Duration = _default_duration;
        RTTTL.RTTTL_Octave = _default_octave;
        isInitialized = true;
    }
    while(0);
    do
    {
        static char data[4*1024];
        static uint16_t data_length = 0;
        static uint16_t data_length_read = 0;
        Platform_USART_Read
        (
                Platform_USART_USB,
                (Platform_USART_Data_t)(data+data_length),
                (Platform_USART_Data_Length_t)(sizeof(data)-data_length),
                (Platform_USART_Data_Length_t*)&data_length_read
        );
        data_length += data_length_read;
        if (data[data_length-1] == ';')
        {
            Platform_USART_Write
            (
                    Platform_USART_USB,
                    (Platform_USART_Data_t)data,
                    (Platform_USART_Data_Length_t)data_length
            );
            data_length = 0;
        }
    }
    while(0);
}

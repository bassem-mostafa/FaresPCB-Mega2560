#include "Platform.h"
#include "string.h"
#include "stdio.h"
#include "EEPROM.h"

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
    char _info[50];
    char _info_write[20];
    char _info_read[20];
    EEPROM_Memory_Address_t EEPROM_Memory_Address = 0x0001;
    EEPROM_Memory_Data_Length_t _info_read_length = 0;
    for (uint8_t i = 0; i < sizeof(_info_write); ++i) _info_write[i] = 'A'+i;
    memset(_info_read, 0, sizeof(_info_read));
    _info_write[sizeof(_info_write)-1] = '\0';
    _info_read[sizeof(_info_read)-1] = '\0';

    snprintf(_info, sizeof(_info), "\nEEPROM Write '%s'", _info_write);
    _info[sizeof(_info)-1] = '\0';
    Platform_USART_Write
    (
            Platform_USART_USB,
            (Platform_USART_Data_t)_info,
            (Platform_USART_Data_Length_t)strlen(_info)
    );

    if (EEPROM_Write(EEPROM_Memory_Address, (uint8_t*)_info_write, sizeof(_info_write)-1) != EEPROM_Status_Success)
    {
        Platform_USART_Write
        (
                Platform_USART_USB,
                (Platform_USART_Data_t)"\n\e[31mEEPROM Failed\e[39m",
                (Platform_USART_Data_Length_t)strlen("\n\e[31mEEPROM Failed\e[39m")
        );
    }

    snprintf(_info, sizeof(_info), "\nEEPROM Reading...");
    _info[sizeof(_info)-1] = '\0';
    Platform_USART_Write
    (
            Platform_USART_USB,
            (Platform_USART_Data_t)_info,
            (Platform_USART_Data_Length_t)strlen(_info)
    );

    if (EEPROM_Read(EEPROM_Memory_Address, (uint8_t*)_info_read, sizeof(_info_read)-1, &_info_read_length) != EEPROM_Status_Success || _info_read_length != (sizeof(_info_read)-1))
    {
        Platform_USART_Write
        (
                Platform_USART_USB,
                (Platform_USART_Data_t)"\n\e[31mEEPROM Failed\e[39m",
                (Platform_USART_Data_Length_t)strlen("\n\e[31mEEPROM Failed\e[39m")
        );
    }
    snprintf(_info, sizeof(_info), "\nEEPROM Read '%s'", _info_read);
    _info[sizeof(_info)-1] = '\0';
    Platform_USART_Write
    (
            Platform_USART_USB,
            (Platform_USART_Data_t)_info,
            (Platform_USART_Data_Length_t)strlen(_info)
    );
    Platform_USART_Write
    (
            Platform_USART_USB,
            (Platform_USART_Data_t)"\n\nEEPROM Demo Done\n",
            (Platform_USART_Data_Length_t)strlen("\n\nEEPROM Demo Done\n")
    );
}

void loop()
{

}

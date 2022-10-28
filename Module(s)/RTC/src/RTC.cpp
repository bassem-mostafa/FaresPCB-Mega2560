// #############################################################################
// #### Copyright ##############################################################
// #############################################################################

/*
 * Copyright (C) 2023 BaSSeM
 *
 * This software is distributed under the terms and conditions of the 'Apache-2.0'
 * license which can be found in the file 'LICENSE.txt' in this package distribution
 * or at 'http://www.apache.org/licenses/LICENSE-2.0'.
 */

// #############################################################################
// #### Description ############################################################
// #############################################################################

// #############################################################################
// #### Include(s) #############################################################
// #############################################################################

#include "RTC.h"
#include "Platform.h"
#include "util/delay.h"
#include "stddef.h"

// #############################################################################
// #### Private Macro(s) #######################################################
// #############################################################################

#define _RTC_YEAR_OFFSET 2000
#define _RTC_RAM_SIZE 56 // in bytes
#define _RTC_BCD2DEC(BCD) ( ( ( ( (BCD) >> 4 ) & 0xFF )  * 10 ) + ( ( (BCD) & 0xFF ) * 1 ) )
#define _RTC_DEC2BCD(DEC) ( ( ( ( (DEC) / 10 ) % 10 ) << 4 ) | ( (DEC) % 10 ) )

// #############################################################################
// #### Private Type(s) ########################################################
// #############################################################################

typedef uint8_t _RTC_Byte_t;

typedef enum _00h_Clock_t
{
    _00h_Clock_Enable = 0,
    _00h_Clock_Disable,
} _00h_Clock_t;

typedef union __attribute__((packed, aligned(1))) _00h_t
{
    _RTC_Byte_t value;
    struct
    {
        _RTC_Byte_t second      : 4;
        _RTC_Byte_t second_10   : 3;
        _RTC_Byte_t             : 1;
    };
    struct
    {
        _RTC_Byte_t         : 7;
        _00h_Clock_t clock  : 1;
    };
} _00h_t;

typedef union __attribute__((packed, aligned(1))) _01h_t
{
    _RTC_Byte_t value;
    struct
    {
        _RTC_Byte_t minute      : 4;
        _RTC_Byte_t minute_10   : 3;
        _RTC_Byte_t             : 1;
    };
} _01h_t;

typedef enum __attribute__((packed, aligned(1))) _02h_Period_t
{
    _02h_Period_AM = 0,
    _02h_Period_PM,
} _02h_Period_t;

typedef enum __attribute__((packed, aligned(1))) _02h_Mode_t
{
    _02h_Mode_24h = 0,
    _02h_Mode_12h,
} _02h_Mode_t;

typedef union __attribute__((packed, aligned(1))) _02h_t
{
    _RTC_Byte_t value;
    struct
    {
        _RTC_Byte_t hour            : 4;
        _RTC_Byte_t hour_10         : 1;
        _02h_Period_t period        : 1;
        _RTC_Byte_t                 : 2;
    } _12h;
    struct
    {
        _RTC_Byte_t hour        : 4;
        _RTC_Byte_t hour_10     : 2;
        _RTC_Byte_t             : 2;
    } _24h;
    struct
    {
        _RTC_Byte_t         : 6;
        _02h_Mode_t mode    : 1;
        _RTC_Byte_t         : 1;
    };
} _02h_t;

typedef enum __attribute__((packed, aligned(1))) _03h_Day_t
{
    _03h_Day_Unknown = 0,
    _03h_Day_Saturday,
    _03h_Day_Sunday,
    _03h_Day_Monday,
    _03h_Day_Tuesday,
    _03h_Day_Wednesday,
    _03h_Day_Thursday,
    _03h_Day_Friday,
} _03h_Day_t;

typedef union __attribute__((packed, aligned(1))) _03h_t
{
    _RTC_Byte_t value;
    struct
    {
        _03h_Day_t day : 3;
        _RTC_Byte_t    : 5;
    };
} _03h_t;

typedef union __attribute__((packed, aligned(1))) _04h_t
{
    _RTC_Byte_t value;
    struct
    {
        _RTC_Byte_t date        : 4;
        _RTC_Byte_t date_10     : 2;
        _RTC_Byte_t             : 2;
    };
} _04h_t;

typedef union __attribute__((packed, aligned(1))) _05h_t
{
    _RTC_Byte_t value;
    struct
    {
        _RTC_Byte_t month        : 4;
        _RTC_Byte_t month_10     : 1;
        _RTC_Byte_t              : 3;
    };
} _05h_t;

typedef union __attribute__((packed, aligned(1))) _06h_t
{
    _RTC_Byte_t value;
    struct
    {
        _RTC_Byte_t year            : 4;
        _RTC_Byte_t year_10         : 4;
    };
} _06h_t;

typedef enum __attribute__((packed, aligned(1))) _07h_RateSelect_t
{
    _07h_RateSelect_1HZ         = 0b00,
    _07h_RateSelect_4096HZ      = 0b01,
    _07h_RateSelect_8192HZ      = 0b10,
    _07h_RateSelect_32768HZ     = 0b11,
} _07h_RateSelect_t;

typedef enum __attribute__((packed, aligned(1))) _07h_SquareWave_t
{
    _07h_SquareWave_Disable = 0,
    _07h_SquareWave_Enable,
} _07h_SquareWave_t;

typedef enum __attribute__((packed, aligned(1))) _07h_OutputDefault_t
{
    _07h_OutputDefault_Low = 0,
    _07h_OutputDefault_High,
} _07h_OutputDefault_t;

typedef union __attribute__((packed, aligned(1))) _07h_t
{
    _RTC_Byte_t value;
    struct
    {
        _07h_RateSelect_t rate      : 2;
        _RTC_Byte_t                 : 2;
        _07h_SquareWave_t wave      : 1;
        _RTC_Byte_t                 : 2;
        _07h_OutputDefault_t out    : 1;
    };
} _07h_t;

typedef _RTC_Byte_t _RAM_t[_RTC_RAM_SIZE];

typedef struct __attribute__((packed, aligned(1))) _RTC_t
{
    _00h_t _00h;
    _01h_t _01h;
    _02h_t _02h;
    _03h_t _03h;
    _04h_t _04h;
    _05h_t _05h;
    _06h_t _06h;
    _07h_t _07h;
    _RAM_t _RAM;
} _RTC_t;

typedef struct __attribute__((packed, aligned(1))) _RTC_Packet_t
{
        _RTC_Byte_t content_length;
        struct __attribute__((packed, aligned(1)))
        {
                _RTC_Byte_t address;
                _RTC_Byte_t data[];
        } content;
} _RTC_Packet_t;

// #############################################################################
// #### Private Method(s) Prototype ############################################
// #############################################################################

// #############################################################################
// #### Private Variable(s) ####################################################
// #############################################################################

_RTC_t _RTC;

// #############################################################################
// #### Private Method(s) ######################################################
// #############################################################################

bool _RTC_Initialize
(
        void
)
{
    static bool isInitialized = false;
    do
    {
        if (isInitialized) break;

        Platform_I2C_Setting_t Platform_I2C_Setting = NULL;
        Platform_I2C_Setting_Initialize(&Platform_I2C_Setting);
        Platform_I2C_Setup(Platform_I2C_1, Platform_I2C_Setting);
        isInitialized = true;
    }
    while(0);
    return isInitialized;
}

// #############################################################################
// #### Public Method(s) #######################################################
// #############################################################################

/*
 * @brief Gets RTC date
 *
 * @param[in] void   : None
 *
 * @return RTC_Date_t     : RTC date
 */
RTC_Date_t RTC_DateGet( void )
{
    RTC_Date_t RTC_Date;

    _RTC_Packet_t _RTC_Packet = (_RTC_Packet_t) {
        1 /* content_length */,
        {
                /* content.address */
                offsetof(_RTC_t, _03h),
                /* content.data */
        }
    };

    _RTC_Initialize();

    if ( Platform_I2C_Write(Platform_I2C_1, Platform_I2C_Address_RTC, (uint8_t*)&_RTC_Packet.content, _RTC_Packet.content_length) == Platform_Status_Success )
    {

    }

    if (Platform_I2C_Read(Platform_I2C_1, Platform_I2C_Address_RTC, (uint8_t*)&_RTC._03h, offsetof(_RTC_t, _06h) - offsetof(_RTC_t, _03h) + 1) == Platform_Status_Success )
    {
        RTC_Date.year = _RTC._06h.year_10 * 10 + _RTC._06h.year + _RTC_YEAR_OFFSET;
        RTC_Date.month = _RTC._05h.month_10 * 10 + _RTC._05h.month;
        RTC_Date.day = _RTC._04h.date_10 * 10 + _RTC._04h.date;
        switch (_RTC._03h.day)
        {
            case _03h_Day_Saturday:
                RTC_Date.weekday = RTC_WeekDay_Saturday;
                break;
            case _03h_Day_Sunday:
                RTC_Date.weekday = RTC_WeekDay_Sunday;
                break;
            case _03h_Day_Monday:
                RTC_Date.weekday = RTC_WeekDay_Monday;
                break;
            case _03h_Day_Tuesday:
                RTC_Date.weekday = RTC_WeekDay_Tuesday;
                break;
            case _03h_Day_Wednesday:
                RTC_Date.weekday = RTC_WeekDay_Wednesday;
                break;
            case _03h_Day_Thursday:
                RTC_Date.weekday = RTC_WeekDay_Thursday;
                break;
            case _03h_Day_Friday:
                RTC_Date.weekday = RTC_WeekDay_Friday;
                break;
            case _03h_Day_Unknown:
            default:
                RTC_Date.weekday = RTC_WeekDay_Unknown;
                break;
        }
    }
    return RTC_Date;
}

/*
 * @brief Sets RTC date
 *
 * @param[in] RTC_Date   : Date to be set
 *
 * @return void     : None
 */
void RTC_DateSet( RTC_Date_t RTC_Date )
{
    _RTC._06h.year_10 = _RTC_DEC2BCD( ( (RTC_Date.year - _RTC_YEAR_OFFSET) / 10 ) % 10);
    _RTC._06h.year = _RTC_DEC2BCD( ( (RTC_Date.year - _RTC_YEAR_OFFSET) /  1 ) % 10);
    _RTC._05h.month_10 = _RTC_DEC2BCD( (RTC_Date.month / 10 ) % 10);
    _RTC._05h.month = _RTC_DEC2BCD( (RTC_Date.month /  1 ) % 10);
    _RTC._04h.date_10 = _RTC_DEC2BCD( (RTC_Date.day / 10 ) % 10);
    _RTC._04h.date = _RTC_DEC2BCD( (RTC_Date.day /  1 ) % 10);
    switch (RTC_Date.weekday)
    {
        case RTC_WeekDay_Saturday:
            _RTC._03h.day = _03h_Day_Saturday;
            break;
        case RTC_WeekDay_Sunday:
            _RTC._03h.day = _03h_Day_Sunday;
            break;
        case RTC_WeekDay_Monday:
            _RTC._03h.day = _03h_Day_Monday;
            break;
        case RTC_WeekDay_Tuesday:
            _RTC._03h.day = _03h_Day_Tuesday;
            break;
        case RTC_WeekDay_Wednesday:
            _RTC._03h.day = _03h_Day_Wednesday;
            break;
        case RTC_WeekDay_Thursday:
            _RTC._03h.day = _03h_Day_Thursday;
            break;
        case RTC_WeekDay_Friday:
            _RTC._03h.day = _03h_Day_Friday;
            break;
        case RTC_WeekDay_Unknown:
        default:
            // Don't Change Day
            break;
    }

    _RTC_Packet_t _RTC_Packet = (_RTC_Packet_t) {
        5 /* content_length */,
        {
                /* content.address */
                offsetof(_RTC_t, _03h) ,
                /* content.data */
                _RTC._03h.value,
                _RTC._04h.value,
                _RTC._05h.value,
                _RTC._06h.value,
        }
    };

    _RTC_Initialize();

    if ( Platform_I2C_Write(Platform_I2C_1, Platform_I2C_Address_RTC, (uint8_t*)&_RTC_Packet.content, _RTC_Packet.content_length) == Platform_Status_Success )
    {

    }
}

/*
 * @brief Gets RTC time
 *
 * @param[in] void   : None
 *
 * @return RTC_Time_t     : RTC time
 */
RTC_Time_t RTC_TimeGet( void )
{
    RTC_Time_t RTC_Time;

    _RTC_Packet_t _RTC_Packet = (_RTC_Packet_t) {
        1 /* content_length */,
        {
                /* content.address */
                offsetof(_RTC_t, _00h),
                /* content.data */
        }
    };

    _RTC_Initialize();

    if ( Platform_I2C_Write(Platform_I2C_1, Platform_I2C_Address_RTC, (uint8_t*)&_RTC_Packet.content, _RTC_Packet.content_length) == Platform_Status_Success )
    {

    }

    if (Platform_I2C_Read(Platform_I2C_1, Platform_I2C_Address_RTC, (uint8_t*)&_RTC._00h, offsetof(_RTC_t, _02h) - offsetof(_RTC_t, _00h) + 1) == Platform_Status_Success )
    {
        switch (_RTC._02h.mode)
        {
            case _02h_Mode_12h:
                RTC_Time.hour = _RTC._02h._12h.hour_10 * 10 + _RTC._02h._12h.hour;
                RTC_Time.minute = _RTC._01h.minute_10 * 10 + _RTC._01h.minute;
                RTC_Time.second = _RTC._00h.second_10 * 10 + _RTC._00h.second;
                switch (_RTC._02h._12h.period)
                {
                    case _02h_Period_AM:
                        RTC_Time.period = RTC_Period_12H_AM;
                        break;
                    case _02h_Period_PM:
                    default:
                        RTC_Time.period = RTC_Period_12H_PM;
                        break;
                }
                break;
            case _02h_Mode_24h:
            default:
                RTC_Time.hour = _RTC._02h._24h.hour_10 * 10 + _RTC._02h._24h.hour;
                RTC_Time.minute = _RTC._01h.minute_10 * 10 + _RTC._01h.minute;
                RTC_Time.second = _RTC._00h.second_10 * 10 + _RTC._00h.second;
                RTC_Time.period = RTC_Period_24H;
                break;
        }
    }
    return RTC_Time;
}

/*
 * @brief Sets RTC time
 *
 * @param[in] RTC_Time   : Time to be set
 *
 * @return void     : None
 */
void RTC_TimeSet( RTC_Time_t RTC_Time )
{
    switch (RTC_Time.period)
    {
    case RTC_Period_12H_AM:
    case RTC_Period_12H_PM:
        _RTC._02h.mode = _02h_Mode_12h;
        _RTC._02h._12h.hour_10 = _RTC_DEC2BCD((RTC_Time.hour / 10) % 10);
        _RTC._02h._12h.hour = _RTC_DEC2BCD((RTC_Time.hour /  1) % 10);
        _RTC._01h.minute_10 = _RTC_DEC2BCD((RTC_Time.minute / 10) % 10);
        _RTC._01h.minute = _RTC_DEC2BCD((RTC_Time.minute /  1) % 10);
        _RTC._00h.second_10 = _RTC_DEC2BCD((RTC_Time.second / 10) % 10);
        _RTC._00h.second = _RTC_DEC2BCD((RTC_Time.second /  1) % 10);
        switch (RTC_Time.period)
        {
            case RTC_Period_12H_AM:
                _RTC._02h._12h.period = _02h_Period_AM;
                break;
            case RTC_Period_12H_PM:
            default:
                _RTC._02h._12h.period = _02h_Period_PM;
                break;
        }
        break;
    case RTC_Period_24H:
    default:
        _RTC._02h.mode = _02h_Mode_24h;
        _RTC._02h._24h.hour_10 = _RTC_DEC2BCD((RTC_Time.hour / 10) % 10);
        _RTC._02h._24h.hour = _RTC_DEC2BCD((RTC_Time.hour /  1) % 10);
        _RTC._01h.minute_10 = _RTC_DEC2BCD((RTC_Time.minute / 10) % 10);
        _RTC._01h.minute = _RTC_DEC2BCD((RTC_Time.minute /  1) % 10);
        _RTC._00h.second_10 = _RTC_DEC2BCD((RTC_Time.second / 10) % 10);
        _RTC._00h.second = _RTC_DEC2BCD((RTC_Time.second /  1) % 10);
        break;
    }
    _RTC._00h.clock = _00h_Clock_Enable;

    _RTC_Packet_t _RTC_Packet = (_RTC_Packet_t) {
        4 /* content_length */,
        {
                /* content.address */
                offsetof(_RTC_t, _00h) ,
                /* content.data */
                _RTC._00h.value,
                _RTC._01h.value,
                _RTC._02h.value,
        }
    };

    _RTC_Initialize();

    if ( Platform_I2C_Write(Platform_I2C_1, Platform_I2C_Address_RTC, (uint8_t*)&_RTC_Packet.content, _RTC_Packet.content_length) == Platform_Status_Success )
    {

    }
}

/*
 * @brief Gets RTC memory
 *
 * @param[in] index   : memory index
 *
 * @return uint8_t     : memory value at given index
 */
RTC_Memory_Value_t RTC_MemoryGet( RTC_Memory_Index_t RTC_Memory_Index )
{
    uint8_t value;

    _RTC_Packet_t _RTC_Packet = (_RTC_Packet_t) {
        1 /* content_length */,
        {
                /* content.address */
                offsetof(_RTC_t, _RAM) + RTC_Memory_Index ,
                /* content.data */
        }
    };

    _RTC_Initialize();

    if ( Platform_I2C_Write(Platform_I2C_1, Platform_I2C_Address_RTC, (uint8_t*)&_RTC_Packet.content, _RTC_Packet.content_length) == Platform_Status_Success )
    {

    }

    if (Platform_I2C_Read(Platform_I2C_1, Platform_I2C_Address_RTC, (uint8_t*)&_RTC._RAM[RTC_Memory_Index], 1) == Platform_Status_Success )
    {
        value = _RTC._RAM[RTC_Memory_Index];
    }
    return value;
}

/*
 * @brief Sets RTC memory
 *
 * @param[in] index   : memory index
 * @param[in] value   : value to be set at given index
 *
 * @return void     : None
 */
void RTC_MemorySet( RTC_Memory_Index_t RTC_Memory_Index, RTC_Memory_Value_t RTC_Memory_Value )
{
    _RTC._RAM[RTC_Memory_Index] = RTC_Memory_Value;

    _RTC_Packet_t _RTC_Packet = (_RTC_Packet_t) {
        2 /* content_length */,
        {
                /* content.address */
                offsetof(_RTC_t, _RAM) + RTC_Memory_Index ,
                /* content.data */
                _RTC._RAM[RTC_Memory_Index],
        }
    };

    _RTC_Initialize();

    if ( Platform_I2C_Write(Platform_I2C_1, Platform_I2C_Address_RTC, (uint8_t*)&_RTC_Packet.content, _RTC_Packet.content_length) == Platform_Status_Success )
    {

    }
}

// #############################################################################
// #### Public Variable(s) #####################################################
// #############################################################################

// #############################################################################
// #### END OF FILE ############################################################
// #############################################################################

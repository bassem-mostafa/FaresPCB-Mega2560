// #############################################################################
// #### Copyright ##############################################################
// #############################################################################

/*
 * Copyright (C) 2022 BaSSeM
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

#include "FaresPCB.h"
#include "RTC.h"
#include "Wire.h"

// #############################################################################
// #### Private Macro(s) #######################################################
// #############################################################################

#define YEAR_OFFSET 2000
#define RAM_SIZE 56 // in bytes
#define BCD2DEC(BCD) ( ( ( ( (BCD) >> 4 ) & 0xFF )  * 10 ) + ( ( (BCD) & 0xFF ) * 1 ) )
#define DEC2BCD(DEC) ( ( ( ( (DEC) / 10 ) % 10 ) << 4 ) | ( (DEC) % 10 ) )

// #############################################################################
// #### Private Type(s) ########################################################
// #############################################################################

typedef enum _00h_Clock_t
{
    _00h_Clock_Enable = 0,
    _00h_Clock_Disable,
} _00h_Clock_t;

typedef union __attribute__((packed, aligned(1))) _00h_t
{
    uint8_t value;
    struct
    {
        uint8_t second      : 4;
        uint8_t second_10   : 3;
        uint8_t             : 1;
    };
    struct
    {
        uint8_t             : 7;
        _00h_Clock_t clock  : 1;
    };
} _00h_t;

typedef union __attribute__((packed, aligned(1))) _01h_t
{
    uint8_t value;
    struct
    {
        uint8_t minute      : 4;
        uint8_t minute_10   : 3;
        uint8_t             : 1;
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
    uint8_t value;
    struct
    {
        uint8_t hour            : 4;
        uint8_t hour_10         : 1;
        _02h_Period_t period    : 1;
        uint8_t                 : 2;
    } _12h;
    struct
    {
        uint8_t hour        : 4;
        uint8_t hour_10     : 2;
        uint8_t             : 2;
    } _24h;
    struct
    {
        uint8_t             : 6;
        _02h_Mode_t mode    : 1;
        uint8_t             : 1;
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
    uint8_t value;
    struct
    {
        _03h_Day_t day : 3;
        uint8_t        : 5;
    };
} _03h_t;

typedef union __attribute__((packed, aligned(1))) _04h_t
{
    uint8_t value;
    struct
    {
        uint8_t date        : 4;
        uint8_t date_10     : 2;
        uint8_t             : 2;
    };
} _04h_t;

typedef union __attribute__((packed, aligned(1))) _05h_t
{
    uint8_t value;
    struct
    {
        uint8_t month        : 4;
        uint8_t month_10     : 1;
        uint8_t              : 3;
    };
} _05h_t;

typedef union __attribute__((packed, aligned(1))) _06h_t
{
    uint8_t value;
    struct
    {
        uint8_t year            : 4;
        uint8_t year_10         : 4;
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

typedef enum __attribute__((packed, aligned(1))) s
{
    _07h_OutputDefault_Low = 0,
    _07h_OutputDefault_High,
} _07h_OutputDefault_t;

typedef union __attribute__((packed, aligned(1))) _07h_t
{
    uint8_t value;
    struct
    {
        _07h_RateSelect_t rate      : 2;
        uint8_t                     : 2;
        _07h_SquareWave_t wave      : 1;
        uint8_t                     : 2;
        _07h_OutputDefault_t out    : 1;
    };
} _07h_t;

typedef uint8_t _RAM_t[RAM_SIZE];

typedef struct __attribute__((packed, aligned(1))) RTC_t
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
} RTC_t;

// #############################################################################
// #### Private Variable(s) ####################################################
// #############################################################################

RTC_t RTC;

// #############################################################################
// #### Private Method(s) ######################################################
// #############################################################################

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
    Wire.begin();
    Wire.beginTransmission(HW_RTC_ADDRESS);
    Wire.write(offsetof(RTC_t, _03h));
    Wire.endTransmission(false);
    Wire.requestFrom(HW_RTC_ADDRESS, offsetof(RTC_t, _06h) - offsetof(RTC_t, _03h) + 1);
    for( uint8_t timeout = 0x0F; Wire.available() < (offsetof(RTC_t, _06h) - offsetof(RTC_t, _03h) + 1); --timeout)
    {
        _delay_ms(1);
    }
    Wire.end();

    if (Wire.available() == (offsetof(RTC_t, _06h) - offsetof(RTC_t, _03h) + 1) )
    {
        Wire.readBytes((uint8_t*)&RTC._03h, offsetof(RTC_t, _06h) - offsetof(RTC_t, _03h) + 1);
        RTC_Date.year = RTC._06h.year_10 * 10 + RTC._06h.year + YEAR_OFFSET;
        RTC_Date.month = RTC._05h.month_10 * 10 + RTC._05h.month;
        RTC_Date.day = RTC._04h.date_10 * 10 + RTC._04h.date;
        switch (RTC._03h.day)
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
    RTC._06h.year_10 = DEC2BCD( ( (RTC_Date.year - YEAR_OFFSET) / 10 ) % 10);
    RTC._06h.year = DEC2BCD( ( (RTC_Date.year - YEAR_OFFSET) /  1 ) % 10);
    RTC._05h.month_10 = DEC2BCD( (RTC_Date.month / 10 ) % 10);
    RTC._05h.month = DEC2BCD( (RTC_Date.month /  1 ) % 10);
    RTC._04h.date_10 = DEC2BCD( (RTC_Date.day / 10 ) % 10);
    RTC._04h.date = DEC2BCD( (RTC_Date.day /  1 ) % 10);
    switch (RTC_Date.weekday)
    {
        case RTC_WeekDay_Saturday:
            RTC._03h.day = _03h_Day_Saturday;
            break;
        case RTC_WeekDay_Sunday:
            RTC._03h.day = _03h_Day_Sunday;
            break;
        case RTC_WeekDay_Monday:
            RTC._03h.day = _03h_Day_Monday;
            break;
        case RTC_WeekDay_Tuesday:
            RTC._03h.day = _03h_Day_Tuesday;
            break;
        case RTC_WeekDay_Wednesday:
            RTC._03h.day = _03h_Day_Wednesday;
            break;
        case RTC_WeekDay_Thursday:
            RTC._03h.day = _03h_Day_Thursday;
            break;
        case RTC_WeekDay_Friday:
            RTC._03h.day = _03h_Day_Friday;
            break;
        case RTC_WeekDay_Unknown:
        default:
            // Don't Change Day
            break;
    }

    Wire.begin();
    Wire.beginTransmission(HW_RTC_ADDRESS);
    Wire.write(offsetof(RTC_t, _03h));
    Wire.write((uint8_t*)&RTC._03h, offsetof(RTC_t, _06h) - offsetof(RTC_t, _03h) + 1);
    Wire.endTransmission();
    Wire.end();
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
    Wire.begin();
    Wire.beginTransmission(HW_RTC_ADDRESS);
    Wire.write(offsetof(RTC_t, _00h));
    Wire.endTransmission(false);
    Wire.requestFrom(HW_RTC_ADDRESS, offsetof(RTC_t, _02h) - offsetof(RTC_t, _00h) + 1);
    for( uint8_t timeout = 0x0F; Wire.available() < (offsetof(RTC_t, _02h) - offsetof(RTC_t, _00h) + 1); --timeout)
    {
        _delay_ms(1);
    }
    Wire.end();

    if (Wire.available() == (offsetof(RTC_t, _02h) - offsetof(RTC_t, _00h) + 1) )
    {
        Wire.readBytes((uint8_t*)&RTC._00h, offsetof(RTC_t, _02h) - offsetof(RTC_t, _00h) + 1);
        switch (RTC._02h.mode)
        {
            case _02h_Mode_12h:
                RTC_Time.hour = RTC._02h._12h.hour_10 * 10 + RTC._02h._12h.hour;
                RTC_Time.minute = RTC._01h.minute_10 * 10 + RTC._01h.minute;
                RTC_Time.second = RTC._00h.second_10 * 10 + RTC._00h.second;
                switch (RTC._02h._12h.period)
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
                RTC_Time.hour = RTC._02h._24h.hour_10 * 10 + RTC._02h._24h.hour;
                RTC_Time.minute = RTC._01h.minute_10 * 10 + RTC._01h.minute;
                RTC_Time.second = RTC._00h.second_10 * 10 + RTC._00h.second;
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
        RTC._02h.mode = _02h_Mode_12h;
        RTC._02h._12h.hour_10 = DEC2BCD((RTC_Time.hour / 10) % 10);
        RTC._02h._12h.hour = DEC2BCD((RTC_Time.hour /  1) % 10);
        RTC._01h.minute_10 = DEC2BCD((RTC_Time.minute / 10) % 10);
        RTC._01h.minute = DEC2BCD((RTC_Time.minute /  1) % 10);
        RTC._00h.second_10 = DEC2BCD((RTC_Time.second / 10) % 10);
        RTC._00h.second = DEC2BCD((RTC_Time.second /  1) % 10);
        switch (RTC_Time.period)
        {
            case RTC_Period_12H_AM:
                RTC._02h._12h.period = _02h_Period_AM;
                break;
            case RTC_Period_12H_PM:
            default:
                RTC._02h._12h.period = _02h_Period_PM;
                break;
        }
        break;
    case RTC_Period_24H:
    default:
        RTC._02h.mode = _02h_Mode_24h;
        RTC._02h._24h.hour_10 = DEC2BCD((RTC_Time.hour / 10) % 10);
        RTC._02h._24h.hour = DEC2BCD((RTC_Time.hour /  1) % 10);
        RTC._01h.minute_10 = DEC2BCD((RTC_Time.minute / 10) % 10);
        RTC._01h.minute = DEC2BCD((RTC_Time.minute /  1) % 10);
        RTC._00h.second_10 = DEC2BCD((RTC_Time.second / 10) % 10);
        RTC._00h.second = DEC2BCD((RTC_Time.second /  1) % 10);
        break;
    }

    Wire.begin();
    Wire.beginTransmission(HW_RTC_ADDRESS);
    Wire.write(offsetof(RTC_t, _00h));
    Wire.write((uint8_t*)&RTC._00h, offsetof(RTC_t, _02h) - offsetof(RTC_t, _00h) + 1);
    Wire.endTransmission();
    Wire.end();
}

/*
 * @brief Gets RTC memory
 *
 * @param[in] index   : memory index
 *
 * @return uint8_t     : memory value at given index
 */
uint8_t RTC_MemoryGet( uint8_t index )
{
    uint8_t value;
    Wire.begin();
    Wire.beginTransmission(HW_RTC_ADDRESS);
    Wire.write(offsetof(RTC_t, _RAM) + index);
    Wire.endTransmission(false);
    Wire.requestFrom(HW_RTC_ADDRESS, 1);
    for( uint8_t timeout = 0x0F; Wire.available() < (1); --timeout)
    {
        _delay_ms(1);
    }
    Wire.end();
    if (Wire.available() == (1) )
    {
        Wire.readBytes((uint8_t*)&RTC._RAM[index], 1);
        value = RTC._RAM[index];
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
void RTC_MemorySet( uint8_t index, uint8_t value )
{
    RTC._RAM[index] = value;

    Wire.begin();
    Wire.beginTransmission(HW_RTC_ADDRESS);
    Wire.write(offsetof(RTC_t, _RAM) + index);
    Wire.write(RTC._RAM[index]);
    Wire.endTransmission();
    Wire.end();
}

// #############################################################################
// #### Public Variable(s) #####################################################
// #############################################################################

// #############################################################################
// #### END OF FILE ############################################################
// #############################################################################

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
// #### File Guard #############################################################
// #############################################################################

#ifndef FARESPCB_RTC_H_
#define FARESPCB_RTC_H_

// #############################################################################
// #### Include(s) #############################################################
// #############################################################################

// #############################################################################
// #### Public Macro(s) ########################################################
// #############################################################################

// #############################################################################
// #### Public Type(s) #########################################################
// #############################################################################

typedef enum __attribute__((packed, aligned(1))) RTC_WeekDay_t
{
    RTC_WeekDay_Unknown = 0,
    RTC_WeekDay_Saturday,
    RTC_WeekDay_Sunday,
    RTC_WeekDay_Monday,
    RTC_WeekDay_Tuesday,
    RTC_WeekDay_Wednesday,
    RTC_WeekDay_Thursday,
    RTC_WeekDay_Friday,
} RTC_WeekDay_t;

typedef struct __attribute__((packed, aligned(1))) RTC_Date_t
{
    uint16_t year;
    uint8_t month;
    uint8_t day;
    RTC_WeekDay_t weekday;
} RTC_Date_t;

typedef enum __attribute__((packed, aligned(1))) RTC_Period_t
{
    RTC_Period_24H = 0,
    RTC_Period_12H_AM,
    RTC_Period_12H_PM,
} RTC_Period_t;

typedef struct __attribute__((packed, aligned(1))) RTC_Time_t
{
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
    RTC_Period_t period;
} RTC_Time_t;

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
RTC_Date_t RTC_DateGet( void );

/*
 * @brief Sets RTC date
 *
 * @param[in] RTC_Date   : Date to be set
 *
 * @return void     : None
 */
void RTC_DateSet( RTC_Date_t RTC_Date );

/*
 * @brief Gets RTC time
 *
 * @param[in] void   : None
 *
 * @return RTC_Time_t     : RTC time
 */
RTC_Time_t RTC_TimeGet( void );

/*
 * @brief Sets RTC time
 *
 * @param[in] RTC_Time   : Time to be set
 *
 * @return void     : None
 */
void RTC_TimeSet( RTC_Time_t RTC_Time );

/*
 * @brief Gets RTC memory
 *
 * @param[in] index   : memory index
 *
 * @return uint8_t     : memory value at given index
 */
uint8_t RTC_MemoryGet( uint8_t index );

/*
 * @brief Sets RTC memory
 *
 * @param[in] index   : memory index
 * @param[in] value   : value to be set at given index
 *
 * @return void     : None
 */
void RTC_MemorySet( uint8_t index, uint8_t value );

// #############################################################################
// #### Public Variable(s) #####################################################
// #############################################################################

// #############################################################################
// #### File Guard #############################################################
// #############################################################################

#endif /* FARESPCB_RTC_H_ */

// #############################################################################
// #### END OF FILE ############################################################
// #############################################################################

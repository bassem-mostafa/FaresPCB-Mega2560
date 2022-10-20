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
// #### File Guard #############################################################
// #############################################################################

#ifndef LCD_H_
#define LCD_H_

// #############################################################################
// #### Include(s) #############################################################
// #############################################################################

#include "stdint.h"

// #############################################################################
// #### Public Macro(s) ########################################################
// #############################################################################

#define LCD_SCREEN_HEIGHT   ( 2)
#define LCD_SCREEN_WIDTH    (16)

// #############################################################################
// #### Public Type(s) #########################################################
// #############################################################################

typedef uint8_t LCD_Screen_t[LCD_SCREEN_HEIGHT][LCD_SCREEN_WIDTH];

typedef enum __attribute__((packed, aligned(1))) LCD_Icon_t
{
    LCD_Icon_Empty = 0,
    LCD_Icon_Bluetooth,
    LCD_Icon_LockOn,
    LCD_Icon_LockOff,
    LCD_Icon_Calendar,
    LCD_Icon_Clock,
    LCD_Icon_Bell,
    LCD_Icon_Degree,
    LCD_Icon_Thermometer,
    LCD_Icon_WaterDrop,
    LCD_Icon_Bar_Loading_StartEmpty,
    LCD_Icon_Bar_Loading_StartFull,
    LCD_Icon_Bar_Loading_MiddleEmpty,
    LCD_Icon_Bar_Loading_MiddleHalf,
    LCD_Icon_Bar_Loading_MiddleFull,
    LCD_Icon_Bar_Loading_EndEmpty,
    LCD_Icon_Bar_Loading_EndFull,
    LCD_Icon_MelodySingle,
    LCD_Icon_MelodyDual,
    LCD_Icon_MelodyPlay,
    LCD_Icon_MelodyStop,
    LCD_Icon_MelodyPause,
    LCD_Icon_MelodyNext,
    LCD_Icon_MelodyPrevious,
    LCD_Icon_Heart,
    LCD_Icon_BatteryLow,
    LCD_Icon_BatteryHalf,
    LCD_Icon_BatteryFull,
    LCD_Icon_SignalLow,
    LCD_Icon_SignalHalf,
    LCD_Icon_SignalFull,
    LCD_Icon_Alarm,
} LCD_Icon_t;

typedef enum __attribute__((packed, aligned(1))) LCD_Custom_Character_t
{
    LCD_Custom_Character_1 = 0,
    LCD_Custom_Character_2,
    LCD_Custom_Character_3,
    LCD_Custom_Character_4,
    LCD_Custom_Character_5,
    LCD_Custom_Character_6,
    LCD_Custom_Character_7,
    LCD_Custom_Character_8,
} LCD_Custom_Character_t;

// #############################################################################
// #### Public Method(s) #######################################################
// #############################################################################

/*
 * @brief Turns LCD back-light on
 *
 * @param[in] void  : None
 *
 * @return void     : None
 */
void LCD_LightOn( void );

/*
 * @brief Turns LCD back-light off
 *
 * @param[in] void  : None
 *
 * @return void     : None
 */
void LCD_LightOff( void );

/*
 * @brief Writes a screen content to display
 *
 * @param[in] LCD_Screen : screen content
 *
 * @return void     : None
 */
void LCD_Write( LCD_Screen_t LCD_Screen );

/*
 * @brief Links an icon to specific custom character
 *
 * @param[in] LCD_Custom_Character  : custom character selected
 * @param[in] LCD_Icon              : icon selected
 *
 * @return void     : None
 */
void LCD_Setup( LCD_Custom_Character_t LCD_Custom_Character, LCD_Icon_t LCD_Icon );

// #############################################################################
// #### Public Variable(s) #####################################################
// #############################################################################

// #############################################################################
// #### File Guard #############################################################
// #############################################################################

#endif /* LCD_H_ */

// #############################################################################
// #### END OF FILE ############################################################
// #############################################################################

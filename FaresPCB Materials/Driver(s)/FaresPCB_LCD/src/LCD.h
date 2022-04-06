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

#ifndef FARESPCB_LCD_H_
#define FARESPCB_LCD_H_

// #############################################################################
// #### Include(s) #############################################################
// #############################################################################

#include "stdint.h"

// #############################################################################
// #### Public Macro(s) ########################################################
// #############################################################################

#define LCD_ICON_SIZE 8

// #############################################################################
// #### Public Type(s) #########################################################
// #############################################################################

typedef const uint8_t /*__attribute__((packed, aligned(1)))*/ LCD_Icon_t[LCD_ICON_SIZE];

typedef enum __attribute__((packed, aligned(1))) LCD_Line_t
{
    LCD_Line_1 = 0,
    LCD_Line_2,
} LCD_Line_t;

typedef enum __attribute__((packed, aligned(1))) LCD_Character_t
{
    LCD_Character_1 = 0,
    LCD_Character_2,
    LCD_Character_3,
    LCD_Character_4,
    LCD_Character_5,
    LCD_Character_6,
    LCD_Character_7,
    LCD_Character_8,
    LCD_Character_9,
    LCD_Character_10,
    LCD_Character_11,
    LCD_Character_12,
    LCD_Character_13,
    LCD_Character_14,
    LCD_Character_15,
    LCD_Character_16,
} LCD_Character_t;

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
 * @brief Initializes LCD
 *
 * @param[in] void  : None
 *
 * @return void     : None
 */
void LCD_Initialize( void );

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
 * @brief Writes a text into LCD starting from selected line / character
 *
 * @param[in] LCD_Line          : line selected
 * @param[in] LCD_Character     : character selected
 * @param[in] text              : text reference
 * @param[in] length            : text length
 *
 * @return void     : None
 */
void LCD_Write( LCD_Line_t LCD_Line, LCD_Character_t LCD_Character, uint8_t * text, uint8_t length );

/*
 * @brief Links an icon to specific custom character
 *
 * @param[in] LCD_Custom_Character  : custom character selected
 * @param[in] LCD_Icon              : icon selected
 *
 * @return void     : None
 */
void LCD_Setup( LCD_Custom_Character_t LCD_Custom_Character, LCD_Icon_t LCD_Icon );

/*
 * @brief Draws an icon linked to a custom character
 *
 * @param[in] LCD_Line              : line selected
 * @param[in] LCD_Character         : character selected
 * @param[in] LCD_Custom_Character  : custom character selected
 *
 * @return void     : None
 */
void LCD_Draw( LCD_Line_t LCD_Line, LCD_Character_t LCD_Character, LCD_Custom_Character_t LCD_Custom_Character );

// #############################################################################
// #### Public Variable(s) #####################################################
// #############################################################################

extern LCD_Icon_t LCD_Icon_Empty;
extern LCD_Icon_t LCD_Icon_Bluetooth;
extern LCD_Icon_t LCD_Icon_LockOn;
extern LCD_Icon_t LCD_Icon_LockOff;
extern LCD_Icon_t LCD_Icon_Calendar;
extern LCD_Icon_t LCD_Icon_Clock;
extern LCD_Icon_t LCD_Icon_Bell;
extern LCD_Icon_t LCD_Icon_Degree;
extern LCD_Icon_t LCD_Icon_Thermometer;
extern LCD_Icon_t LCD_Icon_WaterDrop;
extern LCD_Icon_t LCD_Icon_Bar_Loading_StartEmpty;
extern LCD_Icon_t LCD_Icon_Bar_Loading_StartFull;
extern LCD_Icon_t LCD_Icon_Bar_Loading_MiddleEmpty;
extern LCD_Icon_t LCD_Icon_Bar_Loading_MiddleHalf;
extern LCD_Icon_t LCD_Icon_Bar_Loading_MiddleFull;
extern LCD_Icon_t LCD_Icon_Bar_Loading_EndEmpty;
extern LCD_Icon_t LCD_Icon_Bar_Loading_EndFull;
extern LCD_Icon_t LCD_Icon_MelodySingle;
extern LCD_Icon_t LCD_Icon_MelodyDual;
extern LCD_Icon_t LCD_Icon_MelodyPlay;
extern LCD_Icon_t LCD_Icon_MelodyStop;
extern LCD_Icon_t LCD_Icon_MelodyPause;
extern LCD_Icon_t LCD_Icon_MelodyNext;
extern LCD_Icon_t LCD_Icon_MelodyPrevious;
extern LCD_Icon_t LCD_Icon_Heart;
extern LCD_Icon_t LCD_Icon_BatteryLow;
extern LCD_Icon_t LCD_Icon_BatteryHalf;
extern LCD_Icon_t LCD_Icon_BatteryFull;
extern LCD_Icon_t LCD_Icon_SignalLow;
extern LCD_Icon_t LCD_Icon_SignalHalf;
extern LCD_Icon_t LCD_Icon_SignalFull;

// #############################################################################
// #### File Guard #############################################################
// #############################################################################

#endif /* FARESPCB_LCD_H_ */

// #############################################################################
// #### END OF FILE ############################################################
// #############################################################################

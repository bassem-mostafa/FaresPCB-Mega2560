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

// #############################################################################
// #### Include(s) #############################################################
// #############################################################################

#include "Platform_ArduinoMega2560.h"
#include <Arduino.h>

// #############################################################################
// #### Private Macro(s) #######################################################
// #############################################################################

// #############################################################################
// #### Private Type(s) ########################################################
// #############################################################################

typedef enum __attribute__((packed, aligned(1))) _Platform_Pin_Setting_Status_t
{
    _Platform_Pin_Setting_Status_Invalid = 0,
    _Platform_Pin_Setting_Status_Updated,
    _Platform_Pin_Setting_Status_Applied,
} _Platform_Pin_Setting_Status_t;

typedef struct __attribute__((packed, aligned(1))) _Platform_Pin_Setting_t
{
        const Platform_Pin_t Platform_Pin;
        _Platform_Pin_Setting_Status_t _Platform_Pin_Setting_Status;
        Platform_Pin_Mode_t Platform_Pin_Mode;
        // TODO Add more pin settings
} _Platform_Pin_Setting_t;

// #############################################################################
// #### Private Method(s) Prototype ############################################
// #############################################################################

// #############################################################################
// #### Private Variable(s) ####################################################
// #############################################################################

static _Platform_Pin_Setting_t _Platform_Pin_Setting_Instance[] =
{
        {Platform_Pin_LED_INTERNAL,       _Platform_Pin_Setting_Status_Invalid},
        {Platform_Pin_LED_1,              _Platform_Pin_Setting_Status_Invalid},
        {Platform_Pin_LED_2,              _Platform_Pin_Setting_Status_Invalid},
        {Platform_Pin_LED_3,              _Platform_Pin_Setting_Status_Invalid},
        {Platform_Pin_LED_4,              _Platform_Pin_Setting_Status_Invalid},
        {Platform_Pin_LED_5,              _Platform_Pin_Setting_Status_Invalid},
        {Platform_Pin_LED_RGB_RED,        _Platform_Pin_Setting_Status_Invalid},
        {Platform_Pin_LED_RGB_GREEN,      _Platform_Pin_Setting_Status_Invalid},
        {Platform_Pin_LED_RGB_BLUE,       _Platform_Pin_Setting_Status_Invalid},
        {Platform_Pin_RELAY_1,            _Platform_Pin_Setting_Status_Invalid},
        {Platform_Pin_RELAY_2,            _Platform_Pin_Setting_Status_Invalid},
        {Platform_Pin_BUZZER,             _Platform_Pin_Setting_Status_Invalid},
        {Platform_Pin_7SEGMENT_BIT0,      _Platform_Pin_Setting_Status_Invalid},
        {Platform_Pin_7SEGMENT_BIT1,      _Platform_Pin_Setting_Status_Invalid},
        {Platform_Pin_7SEGMENT_BIT2,      _Platform_Pin_Setting_Status_Invalid},
        {Platform_Pin_7SEGMENT_BIT3,      _Platform_Pin_Setting_Status_Invalid},
        {Platform_Pin_7SEGMENT_SEL1,      _Platform_Pin_Setting_Status_Invalid},
        {Platform_Pin_7SEGMENT_SEL2,      _Platform_Pin_Setting_Status_Invalid},
        {Platform_Pin_7SEGMENT_SEL3,      _Platform_Pin_Setting_Status_Invalid},
        {Platform_Pin_7SEGMENT_SEL4,      _Platform_Pin_Setting_Status_Invalid},
        {Platform_Pin_LCD_BL,             _Platform_Pin_Setting_Status_Invalid},
        {Platform_Pin_LCD_RS,             _Platform_Pin_Setting_Status_Invalid},
        {Platform_Pin_LCD_EN,             _Platform_Pin_Setting_Status_Invalid},
        {Platform_Pin_LCD_D0,             _Platform_Pin_Setting_Status_Invalid},
        {Platform_Pin_LCD_D1,             _Platform_Pin_Setting_Status_Invalid},
        {Platform_Pin_LCD_D2,             _Platform_Pin_Setting_Status_Invalid},
        {Platform_Pin_LCD_D3,             _Platform_Pin_Setting_Status_Invalid},
        {Platform_Pin_LCD_D4,             _Platform_Pin_Setting_Status_Invalid},
        {Platform_Pin_LCD_D5,             _Platform_Pin_Setting_Status_Invalid},
        {Platform_Pin_LCD_D6,             _Platform_Pin_Setting_Status_Invalid},
        {Platform_Pin_LCD_D7,             _Platform_Pin_Setting_Status_Invalid},
        {Platform_Pin_LCD_CS1,            _Platform_Pin_Setting_Status_Invalid},
        {Platform_Pin_LCD_CS2,            _Platform_Pin_Setting_Status_Invalid},
        {Platform_Pin_KEYPAD_ROW1,        _Platform_Pin_Setting_Status_Invalid},
        {Platform_Pin_KEYPAD_ROW2,        _Platform_Pin_Setting_Status_Invalid},
        {Platform_Pin_KEYPAD_ROW3,        _Platform_Pin_Setting_Status_Invalid},
        {Platform_Pin_KEYPAD_ROW4,        _Platform_Pin_Setting_Status_Invalid},
        {Platform_Pin_KEYPAD_COL1,        _Platform_Pin_Setting_Status_Invalid},
        {Platform_Pin_KEYPAD_COL2,        _Platform_Pin_Setting_Status_Invalid},
        {Platform_Pin_KEYPAD_COL3,        _Platform_Pin_Setting_Status_Invalid},
        {Platform_Pin_KEYPAD_COL4,        _Platform_Pin_Setting_Status_Invalid},
        {Platform_Pin_TEMPERATURE_SENSOR, _Platform_Pin_Setting_Status_Invalid},
        {Platform_Pin_VARIABLE_RESISTOR,  _Platform_Pin_Setting_Status_Invalid},
        {Platform_Pin_BLUETOOTH_KEY,      _Platform_Pin_Setting_Status_Invalid},
        {Platform_Pin_BLUETOOTH_STATE,    _Platform_Pin_Setting_Status_Invalid},
        {Platform_Pin_ULTRASONIC_ECHO,    _Platform_Pin_Setting_Status_Invalid},
        {Platform_Pin_ULTRASONIC_TRIG,    _Platform_Pin_Setting_Status_Invalid},
};

// #############################################################################
// #### Private Method(s) ######################################################
// #############################################################################

// #############################################################################
// #### Public Method(s) #######################################################
// #############################################################################

Platform_Status_t Platform_Pin_Setting_Initialize
(
        Platform_Pin_t Platform_Pin,
        Platform_Pin_Setting_t * Platform_Pin_Setting
)
{
    Platform_Status_t Platform_Status = Platform_Status_NotSupported;
    return Platform_Status;
}

Platform_Status_t Platform_Pin_Setting_Mode_Set
(
        Platform_Pin_Setting_t Platform_Pin_Setting,
        Platform_Pin_Mode_t Platform_Pin_Mode
)
{
    Platform_Status_t Platform_Status = Platform_Status_NotSupported;
    return Platform_Status;
}

Platform_Status_t Platform_Pin_Setup
(
        Platform_Pin_t Platform_Pin,
        Platform_Pin_Setting_t Platform_Pin_Setting
)
{
    Platform_Status_t Platform_Status = Platform_Status_NotSupported;
    return Platform_Status;
}

Platform_Status_t Platform_Pin_Write
(
        Platform_Pin_t Platform_Pin,
        Platform_Pin_Value_t Platform_Pin_Value
)
{
    Platform_Status_t Platform_Status = Platform_Status_NotSupported;
    return Platform_Status;
}

Platform_Status_t Platform_Pin_Write_PWM
(
        const Platform_Pin_t Platform_Pin,
        const Platform_Pin_Value_PWM_t Platform_Pin_Value_PWM
)
{
    Platform_Status_t Platform_Status = Platform_Status_NotSupported;
    return Platform_Status;
}

Platform_Status_t Platform_Pin_Read
(
        Platform_Pin_t Platform_Pin,
        Platform_Pin_Value_t * Platform_Pin_Value
)
{
    Platform_Status_t Platform_Status = Platform_Status_NotSupported;
    return Platform_Status;
}

// #############################################################################
// #### Public Variable(s) #####################################################
// #############################################################################

// #############################################################################
// #### File Guard #############################################################
// #############################################################################

// #############################################################################
// #### END OF FILE ############################################################
// #############################################################################

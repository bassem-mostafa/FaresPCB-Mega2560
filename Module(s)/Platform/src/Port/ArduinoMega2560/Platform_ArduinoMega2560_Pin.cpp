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

typedef uint8_t _Platform_Pin_Instance_t;

typedef struct __attribute__((packed, aligned(1))) _Platform_Pin_Setting_t
{
} _Platform_Pin_Setting_t;

// #############################################################################
// #### Private Method(s) Prototype ############################################
// #############################################################################

// #############################################################################
// #### Private Variable(s) ####################################################
// #############################################################################

// #############################################################################
// #### Private Method(s) ######################################################
// #############################################################################

_Platform_Pin_Instance_t _Platform_Pin_Instance_Get
(
        Platform_Pin_t Platform_Pin
)
{
    _Platform_Pin_Instance_t _Platform_Pin_Instance = -1;
    switch (Platform_Pin)
    {
        case Platform_Pin_LED_INTERNAL:       _Platform_Pin_Instance = Platform_Pin_LED_INTERNAL;       break;
        case Platform_Pin_LED_1:              _Platform_Pin_Instance = Platform_Pin_LED_1;              break;
        case Platform_Pin_LED_2:              _Platform_Pin_Instance = Platform_Pin_LED_2;              break;
        case Platform_Pin_LED_3:              _Platform_Pin_Instance = Platform_Pin_LED_3;              break;
        case Platform_Pin_LED_4:              _Platform_Pin_Instance = Platform_Pin_LED_4;              break;
        case Platform_Pin_LED_5:              _Platform_Pin_Instance = Platform_Pin_LED_5;              break;
        case Platform_Pin_LED_RGB_RED:        _Platform_Pin_Instance = Platform_Pin_LED_RGB_RED;        break;
        case Platform_Pin_LED_RGB_GREEN:      _Platform_Pin_Instance = Platform_Pin_LED_RGB_GREEN;      break;
        case Platform_Pin_LED_RGB_BLUE:       _Platform_Pin_Instance = Platform_Pin_LED_RGB_BLUE;       break;
        case Platform_Pin_RELAY_1:            _Platform_Pin_Instance = Platform_Pin_RELAY_1;            break;
        case Platform_Pin_RELAY_2:            _Platform_Pin_Instance = Platform_Pin_RELAY_2;            break;
        case Platform_Pin_BUZZER:             _Platform_Pin_Instance = Platform_Pin_BUZZER;             break;
        case Platform_Pin_7SEGMENT_BIT0:      _Platform_Pin_Instance = Platform_Pin_7SEGMENT_BIT0;      break;
        case Platform_Pin_7SEGMENT_BIT1:      _Platform_Pin_Instance = Platform_Pin_7SEGMENT_BIT1;      break;
        case Platform_Pin_7SEGMENT_BIT2:      _Platform_Pin_Instance = Platform_Pin_7SEGMENT_BIT2;      break;
        case Platform_Pin_7SEGMENT_BIT3:      _Platform_Pin_Instance = Platform_Pin_7SEGMENT_BIT3;      break;
        case Platform_Pin_7SEGMENT_SEL1:      _Platform_Pin_Instance = Platform_Pin_7SEGMENT_SEL1;      break;
        case Platform_Pin_7SEGMENT_SEL2:      _Platform_Pin_Instance = Platform_Pin_7SEGMENT_SEL2;      break;
        case Platform_Pin_7SEGMENT_SEL3:      _Platform_Pin_Instance = Platform_Pin_7SEGMENT_SEL3;      break;
        case Platform_Pin_7SEGMENT_SEL4:      _Platform_Pin_Instance = Platform_Pin_7SEGMENT_SEL4;      break;
        case Platform_Pin_LCD_BL:             _Platform_Pin_Instance = Platform_Pin_LCD_BL;             break;
        case Platform_Pin_LCD_RS:             _Platform_Pin_Instance = Platform_Pin_LCD_RS;             break;
        case Platform_Pin_LCD_EN:             _Platform_Pin_Instance = Platform_Pin_LCD_EN;             break;
        case Platform_Pin_LCD_D0:             _Platform_Pin_Instance = Platform_Pin_LCD_D0;             break;
        case Platform_Pin_LCD_D1:             _Platform_Pin_Instance = Platform_Pin_LCD_D1;             break;
        case Platform_Pin_LCD_D2:             _Platform_Pin_Instance = Platform_Pin_LCD_D2;             break;
        case Platform_Pin_LCD_D3:             _Platform_Pin_Instance = Platform_Pin_LCD_D3;             break;
        case Platform_Pin_LCD_D4:             _Platform_Pin_Instance = Platform_Pin_LCD_D4;             break;
        case Platform_Pin_LCD_D5:             _Platform_Pin_Instance = Platform_Pin_LCD_D5;             break;
        case Platform_Pin_LCD_D6:             _Platform_Pin_Instance = Platform_Pin_LCD_D6;             break;
        case Platform_Pin_LCD_D7:             _Platform_Pin_Instance = Platform_Pin_LCD_D7;             break;
        case Platform_Pin_LCD_CS1:            _Platform_Pin_Instance = Platform_Pin_LCD_CS1;            break;
        case Platform_Pin_LCD_CS2:            _Platform_Pin_Instance = Platform_Pin_LCD_CS2;            break;
        case Platform_Pin_KEYPAD_ROW1:        _Platform_Pin_Instance = Platform_Pin_KEYPAD_ROW1;        break;
        case Platform_Pin_KEYPAD_ROW2:        _Platform_Pin_Instance = Platform_Pin_KEYPAD_ROW2;        break;
        case Platform_Pin_KEYPAD_ROW3:        _Platform_Pin_Instance = Platform_Pin_KEYPAD_ROW3;        break;
        case Platform_Pin_KEYPAD_ROW4:        _Platform_Pin_Instance = Platform_Pin_KEYPAD_ROW4;        break;
        case Platform_Pin_KEYPAD_COL1:        _Platform_Pin_Instance = Platform_Pin_KEYPAD_COL1;        break;
        case Platform_Pin_KEYPAD_COL2:        _Platform_Pin_Instance = Platform_Pin_KEYPAD_COL2;        break;
        case Platform_Pin_KEYPAD_COL3:        _Platform_Pin_Instance = Platform_Pin_KEYPAD_COL3;        break;
        case Platform_Pin_KEYPAD_COL4:        _Platform_Pin_Instance = Platform_Pin_KEYPAD_COL4;        break;
        case Platform_Pin_TEMPERATURE_SENSOR: _Platform_Pin_Instance = Platform_Pin_TEMPERATURE_SENSOR; break;
        case Platform_Pin_VARIABLE_RESISTOR:  _Platform_Pin_Instance = Platform_Pin_VARIABLE_RESISTOR;  break;
        case Platform_Pin_BLUETOOTH_KEY:      _Platform_Pin_Instance = Platform_Pin_BLUETOOTH_KEY;      break;
        case Platform_Pin_BLUETOOTH_STATE:    _Platform_Pin_Instance = Platform_Pin_BLUETOOTH_STATE;    break;
        case Platform_Pin_ULTRASONIC_ECHO:    _Platform_Pin_Instance = Platform_Pin_ULTRASONIC_ECHO;    break;
        case Platform_Pin_ULTRASONIC_TRIG:    _Platform_Pin_Instance = Platform_Pin_ULTRASONIC_TRIG;    break;
        default:                              _Platform_Pin_Instance = -1;                              break;
    }
    return _Platform_Pin_Instance;
}

Platform_Status_t _Platform_Pin_Instance_Mode_Set
(
        _Platform_Pin_Instance_t _Platform_Pin_Instance,
        Platform_Pin_Mode_t Platform_Pin_Mode
)
{
    Platform_Status_t Platform_Status = Platform_Status_NotSupported;
    do
    {
        if (_Platform_Pin_Instance == -1) { Platform_Status = Platform_Status_Error; break; }
        switch (Platform_Pin_Mode)
        {
            case Platform_Pin_Mode_INPUT:
            case Platform_Pin_Mode_TRI_STATE:
                pinMode(_Platform_Pin_Instance, INPUT);
                Platform_Status = Platform_Status_Success;
                break;
            case Platform_Pin_Mode_INPUT_PullUp:
                pinMode(_Platform_Pin_Instance, INPUT_PULLUP);
                Platform_Status = Platform_Status_Success;
                break;
            case Platform_Pin_Mode_OUTPUT:
            case Platform_Pin_Mode_OUTPUT_PushPull:
                pinMode(_Platform_Pin_Instance, OUTPUT);
                Platform_Status = Platform_Status_Success;
                break;
            default:
                break;
        }
    }
    while(0);
    return Platform_Status;
}

Platform_Status_t _Platform_Pin_Instance_Write
(
        _Platform_Pin_Instance_t _Platform_Pin_Instance,
        Platform_Pin_Value_t Platform_Pin_Value
)
{
    Platform_Status_t Platform_Status = Platform_Status_NotSupported;
    do
    {
        if (_Platform_Pin_Instance == -1) { Platform_Status = Platform_Status_Error; break; }
        switch (Platform_Pin_Value)
        {
            case Platform_Pin_Value_HIGH:
                digitalWrite(_Platform_Pin_Instance, HIGH);
                Platform_Status = Platform_Status_Success;
                break;
            case Platform_Pin_Value_LOW:
                digitalWrite(_Platform_Pin_Instance, LOW);
                Platform_Status = Platform_Status_Success;
                break;
            default:
                break;
        }
    }
    while(0);
    return Platform_Status;
}

Platform_Status_t _Platform_Pin_Instance_Write_PWM
(
        _Platform_Pin_Instance_t _Platform_Pin_Instance,
        Platform_Pin_Value_PWM_t Platform_Pin_Value_PWM
)
{
    Platform_Status_t Platform_Status = Platform_Status_NotSupported;
    do
    {
        if (_Platform_Pin_Instance == -1) { Platform_Status = Platform_Status_Error; break; }
        analogWrite(_Platform_Pin_Instance, (uint8_t)Platform_Pin_Value_PWM);
        Platform_Status = Platform_Status_Success;
    }
    while(0);
    return Platform_Status;
}

Platform_Status_t _Platform_Pin_Instance_Read
(
        _Platform_Pin_Instance_t _Platform_Pin_Instance,
        Platform_Pin_Value_t * Platform_Pin_Value
)
{
    Platform_Status_t Platform_Status = Platform_Status_NotSupported;
    do
    {
        if (Platform_Pin_Value == NULL) { Platform_Status = Platform_Status_Error; break; }
        if (_Platform_Pin_Instance == -1) { Platform_Status = Platform_Status_Error; break; }
        switch (digitalRead(_Platform_Pin_Instance))
        {
            case HIGH:
                *Platform_Pin_Value = Platform_Pin_Value_HIGH;
                Platform_Status = Platform_Status_Success;
                break;
            case LOW:
                *Platform_Pin_Value = Platform_Pin_Value_LOW;
                Platform_Status = Platform_Status_Success;
                break;
            default:
                break;
        }
    }
    while(0);
    return Platform_Status;
}

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
    do
    {
        _Platform_Pin_Instance_t _Platform_Pin_Instance = -1;
        if ( (_Platform_Pin_Instance = _Platform_Pin_Instance_Get(Platform_Pin) ) == -1 ) break;
//        FIXME
//        if ( ( Platform_Status = _Platform_Pin_Instance_Mode_Set(_Platform_Pin_Instance, Platform_Pin_Mode) ) != Platform_Status_Success ) break;
        Platform_Status = Platform_Status_Success;
    }
    while(0);
    return Platform_Status;
}

Platform_Status_t Platform_Pin_Write
(
        Platform_Pin_t Platform_Pin,
        Platform_Pin_Value_t Platform_Pin_Value
)
{
    Platform_Status_t Platform_Status = Platform_Status_NotSupported;
    do
    {
        _Platform_Pin_Instance_t _Platform_Pin_Instance = -1;
        if ( (_Platform_Pin_Instance = _Platform_Pin_Instance_Get(Platform_Pin) ) == -1 ) break;
        if ( ( Platform_Status = _Platform_Pin_Instance_Write(_Platform_Pin_Instance, Platform_Pin_Value) ) != Platform_Status_Success ) break;
        Platform_Status = Platform_Status_Success;
    }
    while(0);
    return Platform_Status;
}

Platform_Status_t Platform_Pin_Write_PWM
(
        const Platform_Pin_t Platform_Pin,
        const Platform_Pin_Value_PWM_t Platform_Pin_Value_PWM
)
{
    Platform_Status_t Platform_Status = Platform_Status_NotSupported;
    do
    {
        _Platform_Pin_Instance_t _Platform_Pin_Instance = -1;
        if ( (_Platform_Pin_Instance = _Platform_Pin_Instance_Get(Platform_Pin) ) == -1 ) break;
        if ( ( Platform_Status = _Platform_Pin_Instance_Write_PWM(_Platform_Pin_Instance, Platform_Pin_Value_PWM) ) != Platform_Status_Success ) break;
        Platform_Status = Platform_Status_Success;
    }
    while(0);
    return Platform_Status;
}

Platform_Status_t Platform_Pin_Read
(
        Platform_Pin_t Platform_Pin,
        Platform_Pin_Value_t * Platform_Pin_Value
)
{
    Platform_Status_t Platform_Status = Platform_Status_NotSupported;
    do
    {
        _Platform_Pin_Instance_t _Platform_Pin_Instance = -1;
        if ( (_Platform_Pin_Instance = _Platform_Pin_Instance_Get(Platform_Pin) ) == -1 ) break;
        if ( ( Platform_Status = _Platform_Pin_Instance_Read(_Platform_Pin_Instance, Platform_Pin_Value) ) != Platform_Status_Success ) break;
        Platform_Status = Platform_Status_Success;
    }
    while(0);
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

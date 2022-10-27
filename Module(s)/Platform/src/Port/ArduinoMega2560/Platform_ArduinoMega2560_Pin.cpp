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
    _Platform_Pin_Setting_Status_Free = 0,
    _Platform_Pin_Setting_Status_Active,
    _Platform_Pin_Setting_Status_Applied,
} _Platform_Pin_Setting_Status_t;

typedef struct __attribute__((packed, aligned(1))) _Platform_Pin_Setting_t
{
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

static _Platform_Pin_Setting_t _Platform_Pin_Setting_Pool[] =
{
        {_Platform_Pin_Setting_Status_Free},
        {_Platform_Pin_Setting_Status_Free},
        {_Platform_Pin_Setting_Status_Free},
        {_Platform_Pin_Setting_Status_Free},
        {_Platform_Pin_Setting_Status_Free},
        {_Platform_Pin_Setting_Status_Free},
        {_Platform_Pin_Setting_Status_Free},
        {_Platform_Pin_Setting_Status_Free},
        {_Platform_Pin_Setting_Status_Free},
        {_Platform_Pin_Setting_Status_Free},
        {_Platform_Pin_Setting_Status_Free},
        {_Platform_Pin_Setting_Status_Free},
        {_Platform_Pin_Setting_Status_Free},
        {_Platform_Pin_Setting_Status_Free},
        {_Platform_Pin_Setting_Status_Free},
        {_Platform_Pin_Setting_Status_Free},
        {_Platform_Pin_Setting_Status_Free},
        {_Platform_Pin_Setting_Status_Free},
        {_Platform_Pin_Setting_Status_Free},
        {_Platform_Pin_Setting_Status_Free},
        {_Platform_Pin_Setting_Status_Free},
        {_Platform_Pin_Setting_Status_Free},
        {_Platform_Pin_Setting_Status_Free},
        {_Platform_Pin_Setting_Status_Free},
        {_Platform_Pin_Setting_Status_Free},
        {_Platform_Pin_Setting_Status_Free},
        {_Platform_Pin_Setting_Status_Free},
        {_Platform_Pin_Setting_Status_Free},
        {_Platform_Pin_Setting_Status_Free},
        {_Platform_Pin_Setting_Status_Free},
        {_Platform_Pin_Setting_Status_Free},
        {_Platform_Pin_Setting_Status_Free},
        {_Platform_Pin_Setting_Status_Free},
        {_Platform_Pin_Setting_Status_Free},
        {_Platform_Pin_Setting_Status_Free},
        {_Platform_Pin_Setting_Status_Free},
        {_Platform_Pin_Setting_Status_Free},
        {_Platform_Pin_Setting_Status_Free},
        {_Platform_Pin_Setting_Status_Free},
        {_Platform_Pin_Setting_Status_Free},
        {_Platform_Pin_Setting_Status_Free},
        {_Platform_Pin_Setting_Status_Free},
        {_Platform_Pin_Setting_Status_Free},
        {_Platform_Pin_Setting_Status_Free},
        {_Platform_Pin_Setting_Status_Free},
        {_Platform_Pin_Setting_Status_Free},
        {_Platform_Pin_Setting_Status_Free},
};

// #############################################################################
// #### Private Method(s) ######################################################
// #############################################################################

Platform_Pin_Setting_t _Platform_Pin_Setting_Get
(
        void
)
{
    Platform_Pin_Setting_t Platform_Pin_Setting = NULL;
    for (uint32_t i = 0; i < (sizeof(_Platform_Pin_Setting_Pool)/sizeof(_Platform_Pin_Setting_Pool[0])); ++i)
    {
        if (_Platform_Pin_Setting_Pool[i]._Platform_Pin_Setting_Status == _Platform_Pin_Setting_Status_Free)
        {
            Platform_Pin_Setting = &_Platform_Pin_Setting_Pool[i];
            Platform_Pin_Setting->_Platform_Pin_Setting_Status = _Platform_Pin_Setting_Status_Active;
            break;
        }
    }
    return Platform_Pin_Setting;
}

Platform_Status_t _Platform_Pin_Setting_Mode_Apply
(
        const Platform_Pin_t Platform_Pin,
        const Platform_Pin_Setting_t Platform_Pin_Setting
)
{
    Platform_Status_t Platform_Status = Platform_Status_NotSupported;
    do
    {
        if ( Platform_Pin_Setting == NULL ) { Platform_Status = Platform_Status_Error; break; }
        switch (Platform_Pin_Setting->Platform_Pin_Mode)
        {
            case Platform_Pin_Mode_OUTPUT:
            case Platform_Pin_Mode_OUTPUT_PushPull:
                pinMode(Platform_Pin, OUTPUT);
                Platform_Status = Platform_Status_Success;
                break;
            case Platform_Pin_Mode_INPUT:
                pinMode(Platform_Pin, INPUT);
                Platform_Status = Platform_Status_Success;
                break;
            case Platform_Pin_Mode_INPUT_PullUp:
                pinMode(Platform_Pin, INPUT_PULLUP);
                Platform_Status = Platform_Status_Success;
                break;
            default:
                Platform_Status = Platform_Status_NotSupported;
                break;
        }
    }
    while(0);
    return Platform_Status;
}

Platform_Status_t _Platform_Pin_Setting_Apply
(
        const Platform_Pin_t Platform_Pin,
        const Platform_Pin_Setting_t Platform_Pin_Setting
)
{
    Platform_Status_t Platform_Status = Platform_Status_NotSupported;
    do
    {
        if ( Platform_Pin_Setting == NULL ) { Platform_Status = Platform_Status_Error; break; }
        // TODO Verify settings completeness; All settings have been set to valid values
        if ( (Platform_Status = _Platform_Pin_Setting_Mode_Apply(Platform_Pin, Platform_Pin_Setting) ) != Platform_Status_Success) { break; }
        // TODO Apply more pin settings
        Platform_Status = Platform_Status_Success;
    }
    while(0);
    return Platform_Status;
}

Platform_Status_t _Platform_Pin_Value_Write
(
        const Platform_Pin_t Platform_Pin,
        const Platform_Pin_Value_t Platform_Pin_Value
)
{
    Platform_Status_t Platform_Status = Platform_Status_NotSupported;
    do
    {
        digitalWrite(Platform_Pin, Platform_Pin_Value);
        Platform_Status = Platform_Status_Success;
    }
    while(0);
    return Platform_Status;
}

Platform_Status_t _Platform_Pin_Value_Write_PWM
(
        const Platform_Pin_t Platform_Pin,
        const Platform_Pin_Value_PWM_t Platform_Pin_Value_PWM
)
{
    Platform_Status_t Platform_Status = Platform_Status_NotSupported;
    do
    {

        analogWrite(Platform_Pin, Platform_Pin_Value_PWM);
        Platform_Status = Platform_Status_Success;
    }
    while(0);
    return Platform_Status;
}

Platform_Status_t _Platform_Pin_Value_Read
(
        const Platform_Pin_t Platform_Pin,
        Platform_Pin_Value_t * const Platform_Pin_Value
)
{
    Platform_Status_t Platform_Status = Platform_Status_NotSupported;
    do
    {
        if ( Platform_Pin_Value == NULL ) { Platform_Status = Platform_Status_Error; break; }
        *Platform_Pin_Value = (digitalRead(Platform_Pin) == HIGH ? Platform_Pin_Value_HIGH : Platform_Pin_Value_LOW);
        Platform_Status = Platform_Status_Success;
    }
    while(0);
    return Platform_Status;
}

// #############################################################################
// #### Public Method(s) #######################################################
// #############################################################################

Platform_Status_t Platform_Pin_Setting_Initialize
(
        Platform_Pin_Setting_t * Platform_Pin_Setting
)
{
    Platform_Status_t Platform_Status = Platform_Status_NotSupported;
    do
    {
        if ( Platform_Pin_Setting == NULL ) { Platform_Status = Platform_Status_Error; break; }
        if ( (*Platform_Pin_Setting = _Platform_Pin_Setting_Get()) == NULL ) { Platform_Status = Platform_Status_NotSupported; break; }

        Platform_Status = Platform_Status_Success;
    }
    while(0);
    return Platform_Status;
}

Platform_Status_t Platform_Pin_Setting_Mode_Set
(
        Platform_Pin_Setting_t Platform_Pin_Setting,
        Platform_Pin_Mode_t Platform_Pin_Mode
)
{
    Platform_Status_t Platform_Status = Platform_Status_NotSupported;
    do
    {
        if ( Platform_Pin_Setting == NULL ) { Platform_Status = Platform_Status_Error; break; }
        Platform_Pin_Setting->Platform_Pin_Mode = Platform_Pin_Mode;

        Platform_Pin_Setting->_Platform_Pin_Setting_Status = _Platform_Pin_Setting_Status_Active;
        Platform_Status = Platform_Status_Success;
    }
    while(0);
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
        if ( Platform_Pin_Setting == NULL ) { Platform_Status = Platform_Status_Error; break; }
        if ( (Platform_Status = _Platform_Pin_Setting_Apply(Platform_Pin, Platform_Pin_Setting) ) != Platform_Status_Success ) { break; }

        Platform_Pin_Setting->_Platform_Pin_Setting_Status = _Platform_Pin_Setting_Status_Free;
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
        if ( (Platform_Status = _Platform_Pin_Value_Write(Platform_Pin, Platform_Pin_Value)) != Platform_Status_Success ) { break; }

        Platform_Status = Platform_Status_Success;
    }
    while(0);
    return Platform_Status;
}

Platform_Status_t Platform_Pin_Write_PWM
(
        Platform_Pin_t Platform_Pin,
        Platform_Pin_Value_PWM_t Platform_Pin_Value_PWM
)
{
    Platform_Status_t Platform_Status = Platform_Status_NotSupported;
    do
    {
        if ( (Platform_Status = _Platform_Pin_Value_Write_PWM(Platform_Pin, Platform_Pin_Value_PWM)) != Platform_Status_Success ) { break; }

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
        if ( (Platform_Status = _Platform_Pin_Value_Read(Platform_Pin, Platform_Pin_Value)) != Platform_Status_Success ) { break; }

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

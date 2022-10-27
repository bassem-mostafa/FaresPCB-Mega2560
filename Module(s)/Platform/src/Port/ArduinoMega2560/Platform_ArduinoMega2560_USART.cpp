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
#include <HardwareSerial.h>

// #############################################################################
// #### Private Macro(s) #######################################################
// #############################################################################

#define _Platform_USART_Setting_Pool_Size 10

// #############################################################################
// #### Private Type(s) ########################################################
// #############################################################################

typedef HardwareSerial * _Platform_USART_Instance_t;

typedef struct __attribute__((packed, aligned(1))) _Platform_USART_Setting_t
{
        Platform_USART_Setting_t * Platform_USART_Setting;
        Platform_USART_Baudrate_t Platform_USART_Baudrate;
        // TODO Add more USART settings
} _Platform_USART_Setting_t;

// #############################################################################
// #### Private Method(s) Prototype ############################################
// #############################################################################

// #############################################################################
// #### Private Variable(s) ####################################################
// #############################################################################

static _Platform_USART_Setting_t _Platform_USART_Setting_Pool[_Platform_USART_Setting_Pool_Size] =
{
        {NULL},
        {NULL},
        {NULL},
};

// #############################################################################
// #### Private Method(s) ######################################################
// #############################################################################

static _Platform_USART_Instance_t _Platform_USART_Instance_Get
(
        const Platform_USART_t Platform_USART
)
{
    _Platform_USART_Instance_t _Platform_USART_Instance = NULL;
    switch (Platform_USART)
    {
        case Platform_USART_1:
            _Platform_USART_Instance = &Serial;
            break;
        case Platform_USART_2:
            _Platform_USART_Instance = &Serial1;
            break;
        case Platform_USART_3:
            _Platform_USART_Instance = &Serial2;
            break;
        case Platform_USART_4:
            _Platform_USART_Instance = &Serial3;
            break;
        default:
            _Platform_USART_Instance = NULL;
            break;
    }
    return _Platform_USART_Instance;
}

static Platform_USART_Setting_t _Platform_USART_Setting_Get
(
        void
)
{
    Platform_USART_Setting_t Platform_USART_Setting = NULL;
    for (uint32_t i = 0; i < (sizeof(_Platform_USART_Setting_Pool)/sizeof(_Platform_USART_Setting_Pool[0])); ++i)
    {
        if (_Platform_USART_Setting_Pool[i].Platform_USART_Setting == NULL)
        {
            Platform_USART_Setting = &_Platform_USART_Setting_Pool[i];
            break;
        }
    }
    return Platform_USART_Setting;
}

static Platform_Status_t _Platform_USART_Setting_Release
(
        Platform_USART_Setting_t Platform_USART_Setting
)
{
    Platform_Status_t Platform_Status = Platform_Status_NotSupported;
    do
    {
        if (Platform_USART_Setting == NULL) { Platform_Status = Platform_Status_Error; break; }
        Platform_USART_Setting->Platform_USART_Setting = NULL;
        Platform_Status = Platform_Status_Success;
    }
    while(0);
    return Platform_Status;
}

static Platform_Status_t _Platform_USART_Setting_Baudrate_Apply
(
        const Platform_USART_t Platform_USART,
        const Platform_USART_Setting_t Platform_USART_Setting
)
{
    Platform_Status_t Platform_Status = Platform_Status_NotSupported;
    do
    {
        _Platform_USART_Instance_t _Platform_USART_Instance = NULL;
        if ( Platform_USART_Setting == NULL ) { Platform_Status = Platform_Status_Error; break; }
        if ( (_Platform_USART_Instance = _Platform_USART_Instance_Get(Platform_USART)) == NULL) { Platform_Status = Platform_Status_NotSupported; break; }
        switch (Platform_USART_Setting->Platform_USART_Baudrate)
        {
            case Platform_USART_Baudrate_9600:
                _Platform_USART_Instance->begin(9600);
                Platform_Status = Platform_Status_Success;
                break;
            case Platform_USART_Baudrate_115200:
                _Platform_USART_Instance->begin(115200);
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

static Platform_Status_t _Platform_USART_Setting_Apply
(
        const Platform_USART_t Platform_USART,
        const Platform_USART_Setting_t Platform_USART_Setting
)
{
    Platform_Status_t Platform_Status = Platform_Status_NotSupported;
    do
    {
        if ( Platform_USART_Setting == NULL ) { Platform_Status = Platform_Status_Error; break; }
        // TODO Verify settings completeness; All settings have been set to valid values
        if ( (Platform_Status = _Platform_USART_Setting_Baudrate_Apply(Platform_USART, Platform_USART_Setting) ) != Platform_Status_Success) { break; }
        // TODO Apply more USART settings
        Platform_Status = Platform_Status_Success;
    }
    while(0);
    return Platform_Status;
}

static Platform_Status_t _Platform_USART_Write
(
        const Platform_USART_t Platform_USART,
        const Platform_USART_Data_t Platform_USART_Data,
        const Platform_USART_Data_Length_t Platform_USART_Data_Length
)
{
    Platform_Status_t Platform_Status = Platform_Status_NotSupported;
    do
    {
        _Platform_USART_Instance_t _Platform_USART_Instance = NULL;
        if (Platform_USART_Data == NULL) { Platform_Status = Platform_Status_Error; break; }
        if (Platform_USART_Data_Length <= 0) { Platform_Status = Platform_Status_Error; break; }
        if ( (_Platform_USART_Instance = _Platform_USART_Instance_Get(Platform_USART)) == NULL) { Platform_Status = Platform_Status_NotSupported; break; }
        if (_Platform_USART_Instance->write(Platform_USART_Data, Platform_USART_Data_Length) != Platform_USART_Data_Length) { Platform_Status = Platform_Status_Error; break; }
        Platform_Status = Platform_Status_Success;
    }
    while(0);
    return Platform_Status;
}

static Platform_Status_t _Platform_USART_Read
(
        const Platform_USART_t Platform_USART,
        const Platform_USART_Data_t Platform_USART_Data,
        const Platform_USART_Data_Length_t Platform_USART_Data_Length,
        Platform_USART_Data_Length_t * const Platform_USART_Data_Length_Read
)
{
    Platform_Status_t Platform_Status = Platform_Status_NotSupported;
    do
    {
        _Platform_USART_Instance_t _Platform_USART_Instance = NULL;
        if (Platform_USART_Data == NULL) { Platform_Status = Platform_Status_Error; break; }
        if (Platform_USART_Data_Length <= 0) { Platform_Status = Platform_Status_Error; break; }
        if ( (_Platform_USART_Instance = _Platform_USART_Instance_Get(Platform_USART)) == NULL) { Platform_Status = Platform_Status_NotSupported; break; }
        if (Platform_USART_Data_Length_Read == NULL)
        {
            if (_Platform_USART_Instance->readBytes(Platform_USART_Data, Platform_USART_Data_Length) == 0 ) { Platform_Status = Platform_Status_Timeout; break; }
        }
        else
        {
            if ( ( (*Platform_USART_Data_Length_Read) = _Platform_USART_Instance->readBytes(Platform_USART_Data, Platform_USART_Data_Length)) == 0 ) { Platform_Status = Platform_Status_Timeout; break; }
        }
        Platform_Status = Platform_Status_Success;
    }
    while(0);
    return Platform_Status;
}

// #############################################################################
// #### Public Method(s) #######################################################
// #############################################################################

Platform_Status_t Platform_USART_Setting_Initialize
(
        Platform_USART_Setting_t * Platform_USART_Setting
)
{
    Platform_Status_t Platform_Status = Platform_Status_NotSupported;
    do
    {
        if ( Platform_USART_Setting == NULL ) { Platform_Status = Platform_Status_Error; break; }
        if ( ((*Platform_USART_Setting) = _Platform_USART_Setting_Get()) == NULL ) { Platform_Status = Platform_Status_NotSupported; break; }

        (*Platform_USART_Setting)->Platform_USART_Setting = Platform_USART_Setting;
        Platform_Status = Platform_Status_Success;
    }
    while(0);
    return Platform_Status;
}

Platform_Status_t Platform_USART_Setting_Baudrate_Set
(
        Platform_USART_Setting_t Platform_USART_Setting,
        Platform_USART_Baudrate_t Platform_USART_Baudrate
)
{
    Platform_Status_t Platform_Status = Platform_Status_NotSupported;
    do
    {
        if ( Platform_USART_Setting == NULL ) { Platform_Status = Platform_Status_Error; break; }
        if ( Platform_USART_Setting->Platform_USART_Setting == NULL ) { Platform_Status = Platform_Status_Error; break; }
        Platform_USART_Setting->Platform_USART_Baudrate = Platform_USART_Baudrate;
        Platform_Status = Platform_Status_Success;
    }
    while(0);
    return Platform_Status;
}

Platform_Status_t Platform_USART_Setup
(
        Platform_USART_t Platform_USART,
        Platform_USART_Setting_t Platform_USART_Setting
)
{
    Platform_Status_t Platform_Status = Platform_Status_NotSupported;
    do
    {
        if ( Platform_USART_Setting == NULL ) { Platform_Status = Platform_Status_Error; break; }
        if ( Platform_USART_Setting->Platform_USART_Setting == NULL ) { Platform_Status = Platform_Status_Error; break; }
        if ( (Platform_Status = _Platform_USART_Setting_Apply(Platform_USART, Platform_USART_Setting) ) != Platform_Status_Success ) { break; }
        if ( (Platform_Status = _Platform_USART_Setting_Release(Platform_USART_Setting)) != Platform_Status_Success ) { break; }
        Platform_Status = Platform_Status_Success;
    }
    while(0);
    return Platform_Status;
}

Platform_Status_t Platform_USART_Write
(
        Platform_USART_t Platform_USART,
        Platform_USART_Data_t Platform_USART_Data,
        Platform_USART_Data_Length_t Platform_USART_Data_Length
)
{
    Platform_Status_t Platform_Status = Platform_Status_NotSupported;
    do
    {
        if (Platform_USART_Data == NULL) { Platform_Status = Platform_Status_Error; break; }
        if (Platform_USART_Data_Length <= 0) { Platform_Status = Platform_Status_Error; break; }
        if ( (Platform_Status = _Platform_USART_Write(Platform_USART, Platform_USART_Data, Platform_USART_Data_Length)) != Platform_Status_Success ) { break; }

        Platform_Status = Platform_Status_Success;
    }
    while(0);
    return Platform_Status;
}

Platform_Status_t Platform_USART_Read
(
        Platform_USART_t Platform_USART,
        Platform_USART_Data_t Platform_USART_Data,
        Platform_USART_Data_Length_t Platform_USART_Data_Length,
        Platform_USART_Data_Length_t * Platform_USART_Data_Length_Read
)
{
    Platform_Status_t Platform_Status = Platform_Status_NotSupported;
    do
    {
        if (Platform_USART_Data == NULL) { Platform_Status = Platform_Status_Error; break; }
        if (Platform_USART_Data_Length <= 0) { Platform_Status = Platform_Status_Error; break; }
        if ( (Platform_Status = _Platform_USART_Read(Platform_USART, Platform_USART_Data, Platform_USART_Data_Length, Platform_USART_Data_Length_Read)) != Platform_Status_Success ) { break; }

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

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
#include "Wire.h"

// #############################################################################
// #### Private Macro(s) #######################################################
// #############################################################################

#define _Platform_I2C_Setting_Pool_Size 10

// #############################################################################
// #### Private Type(s) ########################################################
// #############################################################################

typedef TwoWire * _Platform_I2C_Instance_t;

typedef enum __attribute__((packed, aligned(1))) _Platform_I2C_Mode_t
{
    _Platform_I2C_Mode_Master = 0,
    _Platform_I2C_Mode_Slave,
} _Platform_I2C_Mode_t;

typedef struct __attribute__((packed, aligned(1))) _Platform_I2C_Setting_t
{
        Platform_I2C_Setting_t * Platform_I2C_Setting;
        _Platform_I2C_Mode_t _Platform_I2C_Mode;
} _Platform_I2C_Setting_t;

// #############################################################################
// #### Private Method(s) Prototype ############################################
// #############################################################################

// #############################################################################
// #### Private Variable(s) ####################################################
// #############################################################################

static _Platform_I2C_Setting_t _Platform_I2C_Setting_Pool[_Platform_I2C_Setting_Pool_Size] =
{
        {NULL},
        {NULL},
        {NULL},
};

// #############################################################################
// #### Private Method(s) ######################################################
// #############################################################################

static _Platform_I2C_Instance_t _Platform_I2C_Instance_Get
(
        const Platform_I2C_t Platform_I2C
)
{
    _Platform_I2C_Instance_t _Platform_I2C_Instance = NULL;
    switch (Platform_I2C)
    {
        case Platform_I2C_1:
            _Platform_I2C_Instance = &Wire;
            break;
        default:
            _Platform_I2C_Instance = NULL;
            break;
    }
    return _Platform_I2C_Instance;
}

static Platform_I2C_Setting_t _Platform_I2C_Setting_Get
(
        void
)
{
    Platform_I2C_Setting_t Platform_I2C_Setting = NULL;
    for (uint32_t i = 0; i < (sizeof(_Platform_I2C_Setting_Pool)/sizeof(_Platform_I2C_Setting_Pool[0])); ++i)
    {
        if (_Platform_I2C_Setting_Pool[i].Platform_I2C_Setting == NULL)
        {
            Platform_I2C_Setting = &_Platform_I2C_Setting_Pool[i];
            break;
        }
    }
    return Platform_I2C_Setting;
}

static Platform_Status_t _Platform_I2C_Setting_Release
(
        Platform_I2C_Setting_t Platform_I2C_Setting
)
{
    Platform_Status_t Platform_Status = Platform_Status_NotSupported;
    do
    {
        if (Platform_I2C_Setting == NULL) { Platform_Status = Platform_Status_Error; break; }
        Platform_I2C_Setting->Platform_I2C_Setting = NULL;
        Platform_Status = Platform_Status_Success;
    }
    while(0);
    return Platform_Status;
}

static Platform_Status_t _Platform_I2C_Setting_Mode_Apply
(
        const Platform_I2C_t Platform_I2C,
        const Platform_I2C_Setting_t Platform_I2C_Setting
)
{
    Platform_Status_t Platform_Status = Platform_Status_NotSupported;
    do
    {
        _Platform_I2C_Instance_t _Platform_I2C_Instance = NULL;
        if ( Platform_I2C_Setting == NULL ) { Platform_Status = Platform_Status_Error; break; }
        if ( (_Platform_I2C_Instance = _Platform_I2C_Instance_Get(Platform_I2C)) == NULL) { Platform_Status = Platform_Status_NotSupported; break; }
        switch (Platform_I2C_Setting->_Platform_I2C_Mode)
        {
            case _Platform_I2C_Mode_Master:
                _Platform_I2C_Instance->begin();
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

static Platform_Status_t _Platform_I2C_Setting_Apply
(
        const Platform_I2C_t Platform_I2C,
        const Platform_I2C_Setting_t Platform_I2C_Setting
)
{
    Platform_Status_t Platform_Status = Platform_Status_NotSupported;
    do
    {
        if ( Platform_I2C_Setting == NULL ) { Platform_Status = Platform_Status_Error; break; }
        // TODO Verify settings completeness; All settings have been set to valid values
        if ( (Platform_Status = _Platform_I2C_Setting_Mode_Apply(Platform_I2C, Platform_I2C_Setting) ) != Platform_Status_Success) { break; }
        // TODO Apply more I2C settings
        Platform_Status = Platform_Status_Success;
    }
    while(0);
    return Platform_Status;
}

static Platform_Status_t _Platform_I2C_Write
(
        const Platform_I2C_t Platform_I2C,
        const Platform_I2C_Address_t Platform_I2C_Address,
        const Platform_I2C_Data_t Platform_I2C_Data,
        const Platform_I2C_Data_Length_t Platform_I2C_Data_Length
)
{
    Platform_Status_t Platform_Status = Platform_Status_NotSupported;
    do
    {
        _Platform_I2C_Instance_t _Platform_I2C_Instance = NULL;
        if (Platform_I2C_Address <= 0x00 || Platform_I2C_Address >= 0x80) { Platform_Status = Platform_Status_NotSupported; break; }
        if ( (_Platform_I2C_Instance = _Platform_I2C_Instance_Get(Platform_I2C)) == NULL) { Platform_Status = Platform_Status_NotSupported; break; }

        _Platform_I2C_Instance->beginTransmission(Platform_I2C_Address);
        if (_Platform_I2C_Instance->write(Platform_I2C_Data, Platform_I2C_Data_Length) != Platform_I2C_Data_Length) { Platform_Status = Platform_Status_Error; break; }
        switch (_Platform_I2C_Instance->endTransmission())
        {
            case 0:
                // success
                Platform_Status = Platform_Status_Success;
                break;
            case 1:
                // length to long for buffer
                Platform_Status = Platform_Status_Error;
                break;
            case 2:
                //address send, NACK received
                Platform_Status = Platform_Status_Error;
                break;
            case 3:
                //data send, NACK received
                Platform_Status = Platform_Status_Error;
                break;
            case 4:
                //other twi error (lost bus arbitration, bus error, ..)
                Platform_Status = Platform_Status_Error;
                break;
            case 5:
                //timeout:
                Platform_Status = Platform_Status_Timeout;
                break;
            default:
                Platform_Status = Platform_Status_NotSupported;
                break;
        }
    }
    while(0);
    return Platform_Status;
}

static Platform_Status_t _Platform_I2C_Read
(
        const Platform_I2C_t Platform_I2C,
        const Platform_I2C_Address_t Platform_I2C_Address,
        const Platform_I2C_Data_t Platform_I2C_Data,
        const Platform_I2C_Data_Length_t Platform_I2C_Data_Length,
        Platform_I2C_Data_Length_t * const Platform_I2C_Data_Length_Read
)
{
    Platform_Status_t Platform_Status = Platform_Status_NotSupported;
    do
    {
        _Platform_I2C_Instance_t _Platform_I2C_Instance = NULL;
        if (Platform_I2C_Address <= 0x00 || Platform_I2C_Address >= 0x80) { Platform_Status = Platform_Status_NotSupported; break; }
        if ( (_Platform_I2C_Instance = _Platform_I2C_Instance_Get(Platform_I2C)) == NULL) { Platform_Status = Platform_Status_NotSupported; break; }
        if (_Platform_I2C_Instance->requestFrom(Platform_I2C_Address, Platform_I2C_Data_Length) != Platform_I2C_Data_Length) { Platform_Status = Platform_Status_Error; break; }
        if (Platform_I2C_Data_Length_Read == NULL)
        {
            if (_Platform_I2C_Instance->readBytes(Platform_I2C_Data, Platform_I2C_Data_Length) == 0 ) { Platform_Status = Platform_Status_Timeout; break; }
        }
        else
        {
            if ( ( (*Platform_I2C_Data_Length_Read) = _Platform_I2C_Instance->readBytes(Platform_I2C_Data, Platform_I2C_Data_Length)) == 0 ) { Platform_Status = Platform_Status_Timeout; break; }
        }
        Platform_Status = Platform_Status_Success;
    }
    while(0);
    return Platform_Status;
}

// #############################################################################
// #### Public Method(s) #######################################################
// #############################################################################

Platform_Status_t Platform_I2C_Setting_Initialize
(
        Platform_I2C_Setting_t * Platform_I2C_Setting
)
{
    Platform_Status_t Platform_Status = Platform_Status_NotSupported;
    do
    {
        if ( Platform_I2C_Setting == NULL ) { Platform_Status = Platform_Status_Error; break; }
        if ( ((*Platform_I2C_Setting) = _Platform_I2C_Setting_Get()) == NULL ) { Platform_Status = Platform_Status_NotSupported; break; }

        (*Platform_I2C_Setting)->Platform_I2C_Setting = Platform_I2C_Setting;
        Platform_Status = Platform_Status_Success;
    }
    while(0);
    return Platform_Status;
}

Platform_Status_t Platform_I2C_Setup
(
        Platform_I2C_t Platform_I2C,
        Platform_I2C_Setting_t Platform_I2C_Setting
)
{
    Platform_Status_t Platform_Status = Platform_Status_NotSupported;
    do
    {
        if ( Platform_I2C_Setting == NULL ) { Platform_Status = Platform_Status_Error; break; }
        if ( Platform_I2C_Setting->Platform_I2C_Setting == NULL ) { Platform_Status = Platform_Status_Error; break; }
        if ( (Platform_Status = _Platform_I2C_Setting_Apply(Platform_I2C, Platform_I2C_Setting) ) != Platform_Status_Success ) { break; }
        if ( (Platform_Status = _Platform_I2C_Setting_Release(Platform_I2C_Setting)) != Platform_Status_Success ) { break; }
        Platform_Status = Platform_Status_Success;
    }
    while(0);
    return Platform_Status;
}

Platform_Status_t Platform_I2C_Write
(
        Platform_I2C_t Platform_I2C,
        Platform_I2C_Address_t Platform_I2C_Address,
        Platform_I2C_Data_t Platform_I2C_Data,
        Platform_I2C_Data_Length_t Platform_I2C_Data_Length
)
{
    Platform_Status_t Platform_Status = Platform_Status_NotSupported;
    do
    {
        if (Platform_I2C_Address <= 0x00 || Platform_I2C_Address >= 0x80) { Platform_Status = Platform_Status_NotSupported; break; }
        if ( (Platform_Status = _Platform_I2C_Write(Platform_I2C, Platform_I2C_Address, Platform_I2C_Data, Platform_I2C_Data_Length)) != Platform_Status_Success ) { break; }

        Platform_Status = Platform_Status_Success;
    }
    while(0);
    return Platform_Status;
}

Platform_Status_t Platform_I2C_Read
(
        Platform_I2C_t Platform_I2C,
        Platform_I2C_Address_t Platform_I2C_Address,
        Platform_I2C_Data_t Platform_I2C_Data,
        Platform_I2C_Data_Length_t Platform_I2C_Data_Length,
        Platform_I2C_Data_Length_t * Platform_I2C_Data_Length_Read
)
{
    Platform_Status_t Platform_Status = Platform_Status_NotSupported;
    do
    {
        if (Platform_I2C_Address <= 0x00 || Platform_I2C_Address >= 0x80) { Platform_Status = Platform_Status_NotSupported; break; }
        if ( (Platform_Status = _Platform_I2C_Read(Platform_I2C, Platform_I2C_Address, Platform_I2C_Data, Platform_I2C_Data_Length, Platform_I2C_Data_Length_Read)) != Platform_Status_Success ) { break; }

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

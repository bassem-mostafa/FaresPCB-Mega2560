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

#if defined(ARDUINO) && defined(ARDUINO_AVR_MEGA2560) && defined(__AVR_ATmega2560__)

// #############################################################################
// #### Include(s) #############################################################
// #############################################################################

#include "Platform.h"
#include "Platform_ArduinoMega2560.h"
#include <Arduino.h>

// #############################################################################
// #### Private Macro(s) #######################################################
// #############################################################################

// #############################################################################
// #### Private Type(s) ########################################################
// #############################################################################

typedef HardwareSerial _USART_Instance_t;

typedef void _SPI_Instance_t;

typedef void _I2C_Instance_t;

typedef uint8_t _Pin_Instance_t;

// #############################################################################
// #### Private Method(s) Prototype ############################################
// #############################################################################

// #############################################################################
// #### Private Variable(s) ####################################################
// #############################################################################

// #############################################################################
// #### Private Method(s) ######################################################
// #############################################################################

_USART_Instance_t * const _Platform_USART_InstanceGet
(
        const Platform_USART_t Platform_USART
)
{
    _USART_Instance_t * _USART_Instance = NULL;
    switch (Platform_USART)
    {
        case Platform_USART_1: _USART_Instance = &Serial;  break;
        case Platform_USART_2: _USART_Instance = &Serial1; break;
        case Platform_USART_3: _USART_Instance = &Serial2; break;
        case Platform_USART_4: _USART_Instance = &Serial3; break;
        default:               _USART_Instance = NULL;     break;
    }
    return _USART_Instance;
}

Platform_Status_t _Platform_USART_InstanceBaudrateSet
(
        _USART_Instance_t * const _USART_Instance,
        const Platform_USART_Baudrate_t Platform_USART_Baudrate
)
{
    Platform_Status_t Platform_Status = Platform_Status_NotSupported;
    do
    {
        if ( _USART_Instance == NULL ) {Platform_Status = Platform_Status_Error; break;}
        switch (Platform_USART_Baudrate)
        {
            case Platform_USART_Baudrate_9600:
                _USART_Instance->begin(9600);
                Platform_Status = Platform_Status_Success;
                break;
            case Platform_USART_Baudrate_115200:
                _USART_Instance->begin(115200);
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

Platform_Status_t _Platform_USART_InstanceWrite
(
        _USART_Instance_t * _USART_Instance,
        Platform_USART_Data_t Platform_USART_Data,
        Platform_USART_Data_Length_t Platform_USART_Data_Length
)
{
    Platform_Status_t Platform_Status = Platform_Status_NotSupported;
    do
    {
        if ( _USART_Instance == NULL ) {Platform_Status = Platform_Status_Error; break;}
        if ( _USART_Instance->write(Platform_USART_Data, Platform_USART_Data_Length) != Platform_USART_Data_Length )
        {
            Platform_Status = Platform_Status_Error;
            break;
        }
        Platform_Status = Platform_Status_Success;
    }
    while(0);
    return Platform_Status;
}

Platform_Status_t _Platform_USART_InstanceRead
(
        _USART_Instance_t * _USART_Instance,
        Platform_USART_Data_t Platform_USART_Data,
        Platform_USART_Data_Length_t Platform_USART_Data_Length
)
{
    Platform_Status_t Platform_Status = Platform_Status_NotSupported;
    do
    {
        if ( _USART_Instance == NULL ) {Platform_Status = Platform_Status_Error; break;}
        if ( _USART_Instance->readBytes(Platform_USART_Data, Platform_USART_Data_Length) != Platform_USART_Data_Length )
        {
            Platform_Status = Platform_Status_Error;
            break;
        }
        Platform_Status = Platform_Status_Success;
    }
    while(0);
    return Platform_Status;
}

// #############################################################################
// #### Public Method(s) #######################################################
// #############################################################################

Platform_Status_t Platform_Pin_Setup
(
        const Platform_Pin_t Platform_Pin,
        const Platform_Pin_Mode_t Platform_Pin_Mode
)
{
    Platform_Status_t Platform_Status = Platform_Status_NotSupported;
    return Platform_Status;
}

Platform_Status_t Platform_Pin_Write
(
        const Platform_Pin_t Platform_Pin,
        const Platform_Pin_Value_t Platform_Pin_Value
)
{
    Platform_Status_t Platform_Status = Platform_Status_NotSupported;
    return Platform_Status;
}

Platform_Status_t Platform_Pin_Read
(
        const Platform_Pin_t Platform_Pin,
        Platform_Pin_Value_t * const Platform_Pin_Value
)
{
    Platform_Status_t Platform_Status = Platform_Status_NotSupported;
    return Platform_Status;
}

Platform_Status_t Platform_I2C_Write
(
        const Platform_I2C_t Platform_I2C,
        const Platform_I2C_Address_t Platform_I2C_Address,
        const Platform_I2C_Data_t Platform_I2C_Data,
        const Platform_I2C_Data_Length_t Platform_I2C_Data_Length
)
{
    Platform_Status_t Platform_Status = Platform_Status_NotSupported;
    return Platform_Status;
}

Platform_Status_t Platform_I2C_Read
(
        const Platform_I2C_t Platform_I2C,
        const Platform_I2C_Address_t Platform_I2C_Address,
        Platform_I2C_Data_t Platform_I2C_Data,
        const Platform_I2C_Data_Length_t Platform_I2C_Data_Length
)
{
    Platform_Status_t Platform_Status = Platform_Status_NotSupported;
    return Platform_Status;
}

Platform_Status_t Platform_SPI_Transaction
(
        const Platform_SPI_t Platform_SPI,
        Platform_SPI_Data_t Platform_SPI_Data,
        const Platform_SPI_Data_Length_t Platform_SPI_Data_Length
)
{
    Platform_Status_t Platform_Status = Platform_Status_NotSupported;
    return Platform_Status;
}

Platform_Status_t Platform_USART_Write
(
        const Platform_USART_t Platform_USART,
        const Platform_USART_Baudrate_t Platform_USART_Baudrate,
        const Platform_USART_Data_t Platform_USART_Data,
        const Platform_USART_Data_Length_t Platform_USART_Data_Length
)
{
    Platform_Status_t Platform_Status = Platform_Status_NotSupported;
    do
    {
        _USART_Instance_t * _USART_Instance = NULL;
        if ( (_USART_Instance = _Platform_USART_InstanceGet(Platform_USART)) == NULL ) break;
        if ( (Platform_Status = _Platform_USART_InstanceBaudrateSet(_USART_Instance, Platform_USART_Baudrate) ) != Platform_Status_Success ) break;
        if ( (Platform_Status = _Platform_USART_InstanceWrite(_USART_Instance, Platform_USART_Data, Platform_USART_Data_Length) ) != Platform_Status_Success ) break;
        Platform_Status = Platform_Status_Success;
    }
    while(0);
    return Platform_Status;
}

Platform_Status_t Platform_USART_Read
(
        const Platform_USART_t Platform_USART,
        const Platform_USART_Baudrate_t Platform_USART_Baudrate,
        Platform_USART_Data_t Platform_USART_Data,
        const Platform_USART_Data_Length_t Platform_USART_Data_Length
)
{
    Platform_Status_t Platform_Status = Platform_Status_NotSupported;
    do
    {
        _USART_Instance_t * _USART_Instance = NULL;
        if ( (_USART_Instance = _Platform_USART_InstanceGet(Platform_USART)) == NULL ) break;
        if ( (Platform_Status = _Platform_USART_InstanceBaudrateSet(_USART_Instance, Platform_USART_Baudrate) ) != Platform_Status_Success ) break;
        if ( (Platform_Status = _Platform_USART_InstanceRead(_USART_Instance, Platform_USART_Data, Platform_USART_Data_Length) ) != Platform_Status_Success ) break;
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

#endif /* defined(ARDUINO) && defined(ARDUINO_AVR_MEGA2560) && defined(__AVR_ATmega2560__) */

// #############################################################################
// #### END OF FILE ############################################################
// #############################################################################

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
// #### Include(s) #############################################################
// #############################################################################

#include "LED.h"
#include "stdint.h"
#include "stddef.h"

// #############################################################################
// #### Private Macro(s) #######################################################
// #############################################################################

#define _LED_CHANNEL_VALUE_INITIAL 0

// #############################################################################
// #### Private Type(s) ########################################################
// #############################################################################

typedef enum __attribute__((packed, aligned(1))) _LED_ID_t
{
    _LED_ID_Internal = 0,
    _LED_ID_1,
    _LED_ID_2,
    _LED_ID_3,
    _LED_ID_4,
    _LED_ID_5,
    _LED_ID_RGB,
} _LED_ID_t;

typedef enum __attribute__((packed, aligned(1))) _LED_Type_t
{
    _LED_Type_Mono = 0,
    _LED_Type_RGB,
} _LED_Type_t;

typedef enum __attribute__((packed, aligned(1))) _LED_Channel_ID_t
{
    _LED_Channel_ID_Mono = 0,
    _LED_Channel_ID_R,
    _LED_Channel_ID_G,
    _LED_Channel_ID_B,
} _LED_Channel_ID_t;

typedef uint8_t _LED_Channel_Value_t;

typedef struct __attribute__((packed, aligned(1))) _LED_Channel_t
{
    const _LED_Channel_ID_t _LED_Channel_ID;
    _LED_Channel_Value_t _LED_Channel_Value;
} _LED_Channel_t;

typedef struct __attribute__((packed, aligned(1))) _LED_t
{
    const _LED_ID_t _LED_ID;
    const _LED_Type_t _LED_Type;
    _LED_Channel_t _LED_Channel[];
} _LED_t;

// #############################################################################
// #### Private Method(s) Prototype ############################################
// #############################################################################

// #############################################################################
// #### Private Variable(s) ####################################################
// #############################################################################

static _LED_t _LED_Internal = (_LED_t){_LED_ID_Internal, _LED_Type_Mono, {{_LED_Channel_ID_Mono, _LED_CHANNEL_VALUE_INITIAL },}};
static _LED_t _LED_1        = (_LED_t){_LED_ID_1,        _LED_Type_Mono, {{_LED_Channel_ID_Mono, _LED_CHANNEL_VALUE_INITIAL },}};
static _LED_t _LED_2        = (_LED_t){_LED_ID_2,        _LED_Type_Mono, {{_LED_Channel_ID_Mono, _LED_CHANNEL_VALUE_INITIAL },}};
static _LED_t _LED_3        = (_LED_t){_LED_ID_3,        _LED_Type_Mono, {{_LED_Channel_ID_Mono, _LED_CHANNEL_VALUE_INITIAL },}};
static _LED_t _LED_4        = (_LED_t){_LED_ID_4,        _LED_Type_Mono, {{_LED_Channel_ID_Mono, _LED_CHANNEL_VALUE_INITIAL },}};
static _LED_t _LED_5        = (_LED_t){_LED_ID_5,        _LED_Type_Mono, {{_LED_Channel_ID_Mono, _LED_CHANNEL_VALUE_INITIAL },}};
static _LED_t _LED_RGB      = (_LED_t){_LED_ID_RGB,      _LED_Type_RGB,  {{_LED_Channel_ID_R,    _LED_CHANNEL_VALUE_INITIAL },
                                                                          {_LED_Channel_ID_G,    _LED_CHANNEL_VALUE_INITIAL },
                                                                          {_LED_Channel_ID_B,    _LED_CHANNEL_VALUE_INITIAL },}};
static _LED_t * const _LED[] =
{
        [_LED_ID_Internal] = &_LED_Internal,
        [_LED_ID_1]        = &_LED_1,
        [_LED_ID_2]        = &_LED_2,
        [_LED_ID_3]        = &_LED_3,
        [_LED_ID_4]        = &_LED_4,
        [_LED_ID_5]        = &_LED_5,
        [_LED_ID_RGB]      = &_LED_RGB,
};

// #############################################################################
// #### Private Method(s) ######################################################
// #############################################################################

/*
 * @brief Gets number of channels for a LED
 *
 * @param[in] _LED : selected _LED instance @Ref _LED_t, _LED[]
 *
 * @return uint8_t : Number of channels
 */
static const uint8_t _LED_Instance_Channels_Number_Get
(
        const _LED_t * const _LED
)
{
    uint8_t nChannels = 0;
    do
    {
        if (_LED == NULL) break;
        switch (_LED->_LED_Type)
        {
            case _LED_Type_Mono:
                nChannels = 1;
                break;
            case _LED_Type_RGB:
                nChannels = 3;
                break;
            default:
                nChannels = 0;
                break;
        }
    }
    while(0);
    return nChannels;
}

/*
 * @brief Gets a LED instance for specified ID
 *
 * @param[in] LED         : selected LED ID @Ref _LED[]
 *
 * @return _LED_t * const : LED instance reference
 */
static _LED_t * const _LED_Instance_Get
(
        const LED_t LED
)
{
    _LED_t * _LED_instance = NULL;
    do
    {
        switch (LED)
        {
            case LED_Internal:
                _LED_instance = _LED[_LED_ID_Internal];
                break;
            case LED_1:
                _LED_instance = _LED[_LED_ID_1];
                break;
            case LED_2:
                _LED_instance = _LED[_LED_ID_2];
                break;
            case LED_3:
                _LED_instance = _LED[_LED_ID_3];
                break;
            case LED_4:
                _LED_instance = _LED[_LED_ID_4];
                break;
            case LED_5:
                _LED_instance = _LED[_LED_ID_5];
                break;
            case LED_RGB:
                _LED_instance = _LED[_LED_ID_RGB];
                break;
            default:
                _LED_instance = NULL;
                break;
        }
    }
    while(0);
    return _LED_instance;
}

/*
 * @brief Sets a channel of a LED to specific value
 *
 * @param[in] _LED               : selected _LED instance   @Ref _LED[]
 * @param[in] _LED_Channel_ID    : selected channel ID      @Ref _LED_Channel_ID_t
 * @param[in] _LED_Channel_Value : channel value to be set  @Ref _LED_Channel_Value_t
 *
 * @return _LED_t * const : LED instance reference
 */
static bool _LED_Instance_Channel_Set
(
        _LED_t * const _LED,
        const _LED_Channel_ID_t _LED_Channel_ID,
        const _LED_Channel_Value_t _LED_Channel_Value
)
{
    bool isOk = false;
    do
    {
        if ( _LED == NULL ) break;
        const uint8_t nChannels = _LED_Instance_Channels_Number_Get(_LED);
        for (uint8_t i = 0; i < nChannels; ++i)
        {
            if (  _LED_Channel_ID == _LED_Channel_ID_Mono
               || _LED_Channel_ID == _LED->_LED_Channel[i]._LED_Channel_ID)
            {
                _LED->_LED_Channel[i]._LED_Channel_Value = _LED_Channel_Value;
                isOk = true;
            }
        }
    }
    while(0);
    return isOk;
}

// #############################################################################
// #### Public Method(s) #######################################################
// #############################################################################

/*
 * @brief Sets Intensity of a LED
 *
 * @param[in] LED           : selected LED      @Ref LED_t
 * @param[in] LED_Intensity : Intensity value   @Ref LED_Intensity_t
 *
 * @return LED_Status_t : LED_Status_t
 */
LED_Status_t LED_IntensitySet
(
        const LED_t LED,
        const LED_Intensity_t LED_Intensity
)
{
    LED_Status_t LED_Status = LED_Status_Error;
    do
    {
        _LED_t * _LED = NULL;
        if ( (_LED = _LED_Instance_Get(LED)) == NULL) break;
        switch (LED_Intensity)
        {
            case LED_Intensity_Zero:
                _LED_Instance_Channel_Set(_LED, _LED_Channel_ID_Mono, 0x00);
                LED_Status = LED_Status_Success;
                break;
            case LED_Intensity_Full:
                _LED_Instance_Channel_Set(_LED, _LED_Channel_ID_Mono, 0xFF);
                LED_Status = LED_Status_Success;
                break;
            case LED_Intensity_Red:
                _LED_Instance_Channel_Set(_LED, _LED_Channel_ID_Mono, 0x00);
                _LED_Instance_Channel_Set(_LED, _LED_Channel_ID_R,    0xFF);
                LED_Status = LED_Status_Success;
                break;
            case LED_Intensity_Green:
                _LED_Instance_Channel_Set(_LED, _LED_Channel_ID_Mono, 0x00);
                _LED_Instance_Channel_Set(_LED, _LED_Channel_ID_G,    0xFF);
                LED_Status = LED_Status_Success;
                break;
            case LED_Intensity_Blue:
                _LED_Instance_Channel_Set(_LED, _LED_Channel_ID_Mono, 0x00);
                _LED_Instance_Channel_Set(_LED, _LED_Channel_ID_B,    0xFF);
                LED_Status = LED_Status_Success;
                break;
            case LED_Intensity_Yellow:
                _LED_Instance_Channel_Set(_LED, _LED_Channel_ID_Mono, 0x00);
                _LED_Instance_Channel_Set(_LED, _LED_Channel_ID_R,    0xFF);
                _LED_Instance_Channel_Set(_LED, _LED_Channel_ID_G,    0xFF);
                LED_Status = LED_Status_Success;
                break;
            case LED_Intensity_Cyan:
                _LED_Instance_Channel_Set(_LED, _LED_Channel_ID_Mono, 0x00);
                _LED_Instance_Channel_Set(_LED, _LED_Channel_ID_G,    0xFF);
                _LED_Instance_Channel_Set(_LED, _LED_Channel_ID_B,    0xFF);
                LED_Status = LED_Status_Success;
                break;
            case LED_Intensity_Magenta:
                _LED_Instance_Channel_Set(_LED, _LED_Channel_ID_Mono, 0x00);
                _LED_Instance_Channel_Set(_LED, _LED_Channel_ID_R,    0xFF);
                _LED_Instance_Channel_Set(_LED, _LED_Channel_ID_B,    0xFF);
                LED_Status = LED_Status_Success;
                break;
            default:
                LED_Status = LED_Status_Error;
                break;
        }
    }
    while(0);
    return LED_Status;
}

// #############################################################################
// #### Public Variable(s) #####################################################
// #############################################################################

// #############################################################################
// #### END OF FILE ############################################################
// #############################################################################

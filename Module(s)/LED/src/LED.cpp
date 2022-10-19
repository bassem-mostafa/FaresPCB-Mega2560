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

static _LED_t _LED[] =
{
        {_LED_ID_Internal, _LED_Type_Mono, {{_LED_Channel_ID_Mono, _LED_CHANNEL_VALUE_INITIAL },}},
        {_LED_ID_1,        _LED_Type_Mono, {{_LED_Channel_ID_Mono, _LED_CHANNEL_VALUE_INITIAL },}},
        {_LED_ID_2,        _LED_Type_Mono, {{_LED_Channel_ID_Mono, _LED_CHANNEL_VALUE_INITIAL },}},
        {_LED_ID_3,        _LED_Type_Mono, {{_LED_Channel_ID_Mono, _LED_CHANNEL_VALUE_INITIAL },}},
        {_LED_ID_4,        _LED_Type_Mono, {{_LED_Channel_ID_Mono, _LED_CHANNEL_VALUE_INITIAL },}},
        {_LED_ID_5,        _LED_Type_Mono, {{_LED_Channel_ID_Mono, _LED_CHANNEL_VALUE_INITIAL },}},
        {_LED_ID_RGB,      _LED_Type_RGB,  {{_LED_Channel_ID_R,    _LED_CHANNEL_VALUE_INITIAL },
                                            {_LED_Channel_ID_G,    _LED_CHANNEL_VALUE_INITIAL },
                                            {_LED_Channel_ID_B,    _LED_CHANNEL_VALUE_INITIAL },}},
};

// #############################################################################
// #### Private Method(s) ######################################################
// #############################################################################

static _LED_t * const _LED_InstanceGet
(
        const _LED_ID_t _LED_ID
)
{
    _LED_t * _LED_instance = NULL;
    for (_LED_t * _LED_ptr = _LED; sizeof(_LED) / sizeof(_LED_t); ++_LED_ptr)
    {

    }
    return _LED_instance;
}

static bool _LED_ChannelSet
(
        const _LED_ID_t _LED_ID,
        const _LED_Channel_ID_t _LED_Channel_ID,
        const _LED_Channel_Value_t _LED_Channel_Value
)
{
    _LED_t * _LED_instance = _LED_InstanceGet(_LED_ID);
    return false;
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
        LED_t LED,
        LED_Intensity_t LED_Intensity
)
{
    LED_Status_t LED_Status = LED_Status_Success;
    do
    {
        switch (LED)
        {
            case LED_Internal:
                break;
            case LED_1:
                break;
            case LED_2:
                break;
            case LED_3:
                break;
            case LED_4:
                break;
            case LED_5:
                break;
            case LED_RGB:
                break;
            default:
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

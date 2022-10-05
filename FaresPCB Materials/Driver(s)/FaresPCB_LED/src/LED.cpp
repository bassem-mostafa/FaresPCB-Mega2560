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
// #### Include(s) #############################################################
// #############################################################################

#include "FaresPCB.h"
#include "LED.h"

// #############################################################################
// #### Private Macro(s) #######################################################
// #############################################################################

// #############################################################################
// #### Private Type(s) ########################################################
// #############################################################################

typedef enum _LED_ID_t
{
    _LED_ID_Internal = 0,
    _LED_ID_1,
    _LED_ID_2,
    _LED_ID_3,
    _LED_ID_4,
    _LED_ID_5,
    _LED_ID_RGB,
} _LED_ID_t;

typedef enum _LED_Type_t
{
    _LED_Type_Mono = 0,
    _LED_Type_RGB,
} _LED_Type_t;

typedef enum _LED_Channel_ID_t
{
    _LED_Channel_ID_Mono = 0,
    _LED_Channel_ID_R,
    _LED_Channel_ID_G,
    _LED_Channel_ID_B,
} _LED_Channel_ID_t;

typedef uint8_t _LED_Channel_Value_t;

typedef struct _LED_Channel_t
{
    const _LED_Channel_ID_t _LED_Channel_ID;
    _LED_Channel_Value_t _LED_Channel_Value;
} _LED_Channel_t;

typedef struct _LED_t
{
    const _LED_Type_t _LED_Type;
    const _LED_ID_t _LED_ID;
    _LED_Channel_t _LED_Channel[];
} _LED_t;

// #############################################################################
// #### Private Method(s) Prototype ############################################
// #############################################################################

// #############################################################################
// #### Private Variable(s) ####################################################
// #############################################################################

static _LED_t _LED_Internal =
{
        _LED_Type_Mono,
        _LED_ID_Internal,
        {
                {_LED_Channel_ID_Mono, 0},
        }
};

static _LED_t _LED_1 =
{
        _LED_Type_Mono,
        _LED_ID_1,
        {
                {_LED_Channel_ID_Mono, 0},
        }
};

static _LED_t _LED_2 =
{
        _LED_Type_Mono,
        _LED_ID_2,
        {
                {_LED_Channel_ID_Mono, 0},
        }
};

static _LED_t _LED_3 =
{
        _LED_Type_Mono,
        _LED_ID_3,
        {
                {_LED_Channel_ID_Mono, 0},
        }
};

static _LED_t _LED_4 =
{
        _LED_Type_Mono,
        _LED_ID_4,
        {
                {_LED_Channel_ID_Mono, 0},
        }
};

static _LED_t _LED_5 =
{
        _LED_Type_Mono,
        _LED_ID_5,
        {
                {_LED_Channel_ID_Mono, 0},
        }
};

static _LED_t _LED_RGB =
{
        _LED_Type_RGB,
        _LED_ID_RGB,
        {
                {_LED_Channel_ID_R,    0},
                {_LED_Channel_ID_G,    0},
                {_LED_Channel_ID_B,    0},
        }
};

static _LED_t * _LED_Table[] =
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

bool _LED_VerifyID( _LED_ID_t _LED_ID )
{
    bool isOk = true;
    switch (_LED_ID)
    {
        case _LED_ID_Internal:
        case _LED_ID_1:
        case _LED_ID_2:
        case _LED_ID_3:
        case _LED_ID_4:
        case _LED_ID_5:
        case _LED_ID_RGB:
            // Ok
            break;
        default:
            isOk = false;
            break;
    }
    return isOk;
}

bool _LED_VerifyChannelID( _LED_Type_t _LED_Type, _LED_Channel_ID_t _LED_Channel_ID )
{
    bool isOk = true;
    switch (_LED_Channel_ID)
    {
        case _LED_Channel_ID_Mono:
            // Supported for all LED types by default
            // ok
            break;
        case _LED_Channel_ID_R:
        case _LED_Channel_ID_G:
        case _LED_Channel_ID_B:
            if (_LED_Type != _LED_Type_RGB) isOk = false;
            break;
        default:
            isOk = false;
            break;
    }
    return isOk;
}

void _LED_Update( _LED_t * _LED )
{
    switch ( _LED->_LED_ID )
    {
        case _LED_ID_Internal:
            switch (_LED->_LED_Channel[0]._LED_Channel_Value)
            {
            case 0:
                // has pull-up on board
                HW_PIN_OUTPUT(HW_LED_INTERNAL);
                HW_PIN_CLEAR(HW_LED_INTERNAL);
                break;
            default:
                HW_PIN_OUTPUT(HW_LED_INTERNAL);
                HW_PIN_SET(HW_LED_INTERNAL);
                break;
            }
            break;
        case _LED_ID_1:
            switch (_LED->_LED_Channel[0]._LED_Channel_Value)
            {
                case 0:
                    HW_PIN_TRI_STATE(HW_LED_1);
                    break;
                default:
                    HW_PIN_OUTPUT(HW_LED_1);
                    HW_PIN_SET(HW_LED_1);
                    break;
            }
            break;
        case _LED_ID_2:
            switch (_LED->_LED_Channel[0]._LED_Channel_Value)
            {
                case 0:
                    HW_PIN_TRI_STATE(HW_LED_2);
                    break;
                default:
                    HW_PIN_OUTPUT(HW_LED_2);
                    HW_PIN_SET(HW_LED_2);
                    break;
            }
            break;
        case _LED_ID_3:
            switch (_LED->_LED_Channel[0]._LED_Channel_Value)
            {
                case 0:
                    HW_PIN_TRI_STATE(HW_LED_3);
                    break;
                default:
                    HW_PIN_OUTPUT(HW_LED_3);
                    HW_PIN_SET(HW_LED_3);
                    break;
            }
            break;
        case _LED_ID_4:
            switch (_LED->_LED_Channel[0]._LED_Channel_Value)
            {
                case 0:
                    HW_PIN_TRI_STATE(HW_LED_4);
                    break;
                default:
                    HW_PIN_OUTPUT(HW_LED_4);
                    HW_PIN_SET(HW_LED_4);
                    break;
            }
            break;
        case _LED_ID_5:
            switch (_LED->_LED_Channel[0]._LED_Channel_Value)
            {
                case 0:
                    HW_PIN_TRI_STATE(HW_LED_5);
                    break;
                default:
                    HW_PIN_OUTPUT(HW_LED_5);
                    HW_PIN_SET(HW_LED_5);
                    break;
            }
            break;
        case _LED_ID_RGB:
            for ( uint8_t channel_index = 0; channel_index < 3; ++channel_index )
            {
                switch (_LED->_LED_Channel[channel_index]._LED_Channel_ID)
                {
                    case _LED_Channel_ID_R:
                        pinMode(HW_LED_RGB_RED, OUTPUT);
                        analogWrite(HW_LED_RGB_RED, _LED->_LED_Channel[channel_index]._LED_Channel_Value);
                        break;
                    case _LED_Channel_ID_G:
                        pinMode(HW_LED_RGB_GREEN, OUTPUT);
                        analogWrite(HW_LED_RGB_GREEN, _LED->_LED_Channel[channel_index]._LED_Channel_Value);
                        break;
                    case _LED_Channel_ID_B:
                        pinMode(HW_LED_RGB_BLUE, OUTPUT);
                        analogWrite(HW_LED_RGB_BLUE, _LED->_LED_Channel[channel_index]._LED_Channel_Value);
                        break;
                    default:
                        // TODO Should NOT reach here
                        break;
                }
            }
            break;
        default:
            // TODO Should NOT reach here
            break;
    }
}

bool _LED_ChannelIntensity( _LED_ID_t _LED_ID, _LED_Channel_ID_t _LED_Channel_ID, _LED_Channel_Value_t _LED_Channel_Value )
{
    bool isOk = true;
    do
    {
        if ((isOk = _LED_VerifyID(_LED_ID)) == false) break;
        _LED_t * led = _LED_Table[_LED_ID];

        if ((isOk = _LED_VerifyChannelID(led->_LED_Type, _LED_Channel_ID)) == false) break;
        uint8_t nChannels = 0;

        switch (led->_LED_Type)
        {
            case _LED_Type_Mono:
                nChannels = 1;
                break;
            case _LED_Type_RGB:
                nChannels = 3;
                break;
            default:
                isOk = false;
                break;
        }
        if (isOk == false) break;
        for ( uint8_t channel_index = 0; channel_index < nChannels; ++channel_index )
        {
            if ( _LED_Channel_ID == _LED_Channel_ID_Mono || led->_LED_Channel[channel_index]._LED_Channel_ID == _LED_Channel_ID)
            {
                led->_LED_Channel[channel_index]._LED_Channel_Value = _LED_Channel_Value;
            }
        }
        _LED_Update(led);
    }
    while(0);
    return isOk;
}

// #############################################################################
// #### Public Method(s) #######################################################
// #############################################################################

/*
 * @brief Turns on a LED
 *
 * @param[in] LED   : selected LED
 *
 * @return void
 */
void LED_TurnOn( LED_t LED )
{
    do {
        switch (LED)
        {
            case LED_Internal:
                HW_PIN_OUTPUT(HW_LED_INTERNAL);
                HW_PIN_SET(HW_LED_INTERNAL);
                break;
            case LED_1:
                HW_PIN_OUTPUT(HW_LED_1);
                HW_PIN_SET(HW_LED_1);
                break;
            case LED_2:
                HW_PIN_OUTPUT(HW_LED_2);
                HW_PIN_SET(HW_LED_2);
                break;
            case LED_3:
                HW_PIN_OUTPUT(HW_LED_3);
                HW_PIN_SET(HW_LED_3);
                break;
            case LED_4:
                HW_PIN_OUTPUT(HW_LED_4);
                HW_PIN_SET(HW_LED_4);
                break;
            case LED_5:
                HW_PIN_OUTPUT(HW_LED_5);
                HW_PIN_SET(HW_LED_5);
                break;
            default:
                break;
        }
    } while(0);
}

/*
 * @brief Turns off a LED
 *
 * @param[in] LED   : selected LED
 *
 * @return void
 */
void LED_TurnOff( LED_t LED )
{
    do {
        switch (LED)
        {
            case LED_Internal:
                // has pull-up on board
                HW_PIN_OUTPUT(HW_LED_INTERNAL);
                HW_PIN_CLEAR(HW_LED_INTERNAL);
                break;
            case LED_1:
                HW_PIN_TRI_STATE(HW_LED_1);
                break;
            case LED_2:
                HW_PIN_TRI_STATE(HW_LED_2);
                break;
            case LED_3:
                HW_PIN_TRI_STATE(HW_LED_3);
                break;
            case LED_4:
                HW_PIN_TRI_STATE(HW_LED_4);
                break;
            case LED_5:
                HW_PIN_TRI_STATE(HW_LED_5);
                break;
            default:
                break;
        }
    } while(0);
}

/*
 * @brief Reads LED state
 *
 * @param[in] LED   : selected LED
 *
 * @return true     : LED is turned on
 * @return false    : LED is turned off
 */
bool LED_isOn( LED_t LED )
{
    bool isOn = false;

    do {
        switch (LED)
        {
            case LED_Internal:
                // has pull-up on board
                isOn = (HW_PIN_READ(HW_LED_INTERNAL) == HIGH);
                break;
            case LED_1:
                isOn = (HW_PIN_READ(HW_LED_1) == HIGH);
                break;
            case LED_2:
                isOn = (HW_PIN_READ(HW_LED_2) == HIGH);
                break;
            case LED_3:
                isOn = (HW_PIN_READ(HW_LED_3) == HIGH);
                break;
            case LED_4:
                isOn = (HW_PIN_READ(HW_LED_4) == HIGH);
                break;
            case LED_5:
                isOn = (HW_PIN_READ(HW_LED_5) == HIGH);
                break;
            default:
                break;
        }
    } while(0);

    return isOn;
}

/*
 * @brief Sets RGB LED intensity
 *
 * @param[in] red    : red intensity
 * @param[in] green  : green intensity
 * @param[in] blue   : blue intensity
 *
 * @return void     : None
 */
void LED_RGB_SetIntensity( uint8_t red, uint8_t green, uint8_t blue )
{
    if (red == 0 && green == 0 && blue == 0)
    {
        pinMode(HW_LED_RGB_RED, INPUT);
        pinMode(HW_LED_RGB_GREEN, INPUT);
        pinMode(HW_LED_RGB_BLUE, INPUT);
    }
    else
    {
        pinMode(HW_LED_RGB_RED, OUTPUT);
        pinMode(HW_LED_RGB_GREEN, OUTPUT);
        pinMode(HW_LED_RGB_BLUE, OUTPUT);
        analogWrite(HW_LED_RGB_RED, red);
        analogWrite(HW_LED_RGB_GREEN, green);
        analogWrite(HW_LED_RGB_BLUE, blue);
    }
}

// #############################################################################
// #### Public Variable(s) #####################################################
// #############################################################################

// #############################################################################
// #### END OF FILE ############################################################
// #############################################################################

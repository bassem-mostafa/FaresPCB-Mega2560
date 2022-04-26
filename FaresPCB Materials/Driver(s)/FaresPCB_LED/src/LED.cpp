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

// #############################################################################
// #### Private Method(s) Prototype ############################################
// #############################################################################

// #############################################################################
// #### Private Variable(s) ####################################################
// #############################################################################

// #############################################################################
// #### Private Method(s) ######################################################
// #############################################################################

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

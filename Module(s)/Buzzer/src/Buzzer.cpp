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

#include "Buzzer.h"
#include "Platform.h"
#include "Tone.h"

// #############################################################################
// #### Private Macro(s) #######################################################
// #############################################################################

// #############################################################################
// #### Private Type(s) ########################################################
// #############################################################################

typedef Tone _Buzzer_Tone_Instance_t;

// #############################################################################
// #### Private Method(s) Prototype ############################################
// #############################################################################

// #############################################################################
// #### Private Variable(s) ####################################################
// #############################################################################

static _Buzzer_Tone_Instance_t _Buzzer_Tone_Instance;

// #############################################################################
// #### Private Method(s) ######################################################
// #############################################################################

static void _Buzzer_Tone_Initialize
(
        _Buzzer_Tone_Instance_t * const _Buzzer_Tone_Instance
)
{
    _Buzzer_Tone_Instance->begin(Platform_Pin_BUZZER);
}

static bool _Buzzer_Initialize
(
        void
)
{
    static bool isInitialized = false;
    do
    {
        if (isInitialized) break;
        _Buzzer_Tone_Initialize(&_Buzzer_Tone_Instance);
        isInitialized = true;
    }
    while(0);
    return isInitialized;
}

static void _Buzzer_Tone_Play
(
        const _Buzzer_Tone_Instance_t * const _Buzzer_Tone_Instance,
        const Buzzer_Note_t Buzzer_Note,
        const Buzzer_Note_Duration_t Buzzer_Note_Duration
)
{
    _Buzzer_Tone_Instance->play((uint16_t)Buzzer_Note, (uint32_t)Buzzer_Note_Duration);
}

static void _Buzzer_Tone_Stop
(
        _Buzzer_Tone_Instance_t * const _Buzzer_Tone_Instance
)
{
    _Buzzer_Tone_Instance->stop();
}

// #############################################################################
// #### Public Method(s) #######################################################
// #############################################################################

/*
 * @brief Turns on Buzzer on specific frequency
 *
 * @param[in] Buzzer_Note             : selected Note
 * @param[in] Buzzer_Note_Duration    : Note duration in milli-seconds
 *
 * @return void     : None
 */
void Buzzer_TurnOn
(
        Buzzer_Note_t Buzzer_Note,
        Buzzer_Note_Duration_t Buzzer_Note_Duration
)
{
    _Buzzer_Initialize();
    _Buzzer_Tone_Play(&_Buzzer_Tone_Instance, Buzzer_Note, Buzzer_Note_Duration);
}

/*
 * @brief Turns off Buzzer
 *
 * @param[in] void   : None
 *
 * @return void     : None
 */
void Buzzer_TurnOff( void )
{
    _Buzzer_Initialize();
    _Buzzer_Tone_Stop(&_Buzzer_Tone_Instance);
}

// #############################################################################
// #### Public Variable(s) #####################################################
// #############################################################################

// #############################################################################
// #### END OF FILE ############################################################
// #############################################################################

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
 * @brief Turns on Buzzer on specific frequency
 *
 * @param[in] Note        : selected Note
 * @param[in] duration    : Note duration in milli-seconds
 *
 * @return void     : None
 */
void Buzzer_TurnOn( Note_t Note, uint32_t duration )
{
    tone(HW_BUZZER_PIN, Note, duration);
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
    noTone(HW_BUZZER_PIN);
    pinMode(HW_BUZZER_PIN, INPUT);
}

// #############################################################################
// #### Public Variable(s) #####################################################
// #############################################################################

// #############################################################################
// #### END OF FILE ############################################################
// #############################################################################

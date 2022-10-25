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
#include "Relay.h"

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
 * @brief Turns on a Relay
 *
 * @param[in] Relay   : selected Relay
 *
 * @return void     : None
 */
void Relay_TurnOn( Relay_t Relay )
{
    do {
        switch (Relay)
        {
            case Relay_1:
                HW_PIN_OUTPUT(HW_RELAY_1);
                HW_PIN_SET(HW_RELAY_1);
                break;
            case Relay_2:
                HW_PIN_OUTPUT(HW_RELAY_2);
                HW_PIN_SET(HW_RELAY_2);
                break;
            default:
                break;
        }
    } while(0);
}

/*
 * @brief Turns off a Relay
 *
 * @param[in] Relay   : selected Relay
 *
 * @return void     : None
 */
void Relay_TurnOff( Relay_t Relay )
{
    do {
        switch (Relay)
        {
            case Relay_1:
                HW_PIN_TRI_STATE(HW_RELAY_1);
                break;
            case Relay_2:
                HW_PIN_TRI_STATE(HW_RELAY_2);
                break;
            default:
                break;
        }
    } while(0);
}

// #############################################################################
// #### Public Variable(s) #####################################################
// #############################################################################

// #############################################################################
// #### END OF FILE ############################################################
// #############################################################################
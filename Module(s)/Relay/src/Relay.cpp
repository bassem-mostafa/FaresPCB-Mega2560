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

#include "Relay.h"
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

bool _Relay_Initialize
(
        void
)
{
    bool isInitialized = false;
    do
    {
        Platform_Pin_Setting_t Platform_Pin_Setting = NULL;

        Platform_Pin_Setting_Initialize(&Platform_Pin_Setting);
        Platform_Pin_Setting_Mode_Set(Platform_Pin_Setting, Platform_Pin_Mode_OUTPUT);
        Platform_Pin_Setup(Platform_Pin_RELAY_1, Platform_Pin_Setting);

        Platform_Pin_Setting_Initialize(&Platform_Pin_Setting);
        Platform_Pin_Setting_Mode_Set(Platform_Pin_Setting, Platform_Pin_Mode_OUTPUT);
        Platform_Pin_Setup(Platform_Pin_RELAY_2, Platform_Pin_Setting);
        isInitialized = true;
    }
    while(0);
    return isInitialized;
}

// #############################################################################
// #### Public Method(s) #######################################################
// #############################################################################

/*
 * @brief Sets a Relay to specified state
 *
 * @param[in] Relay       : selected Relay
 * @param[in] Relay_State : requested state
 *
 * @return void     : None
 */
void Relay_State_Set( Relay_t Relay, Relay_State_t Relay_State )
{
    switch (Relay)
    {
        case Relay_1:
            Platform_Pin_Write(Platform_Pin_RELAY_1, Relay_State == Relay_State_On ? Platform_Pin_Value_HIGH : Platform_Pin_Value_LOW);
            break;
        case Relay_2:
            Platform_Pin_Write(Platform_Pin_RELAY_2, Relay_State == Relay_State_On ? Platform_Pin_Value_HIGH : Platform_Pin_Value_LOW);
            break;
        default:
            break;
    }
}

// #############################################################################
// #### Public Variable(s) #####################################################
// #############################################################################

// #############################################################################
// #### END OF FILE ############################################################
// #############################################################################

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

#include "Platform_Pin.h"

// #############################################################################
// #### Private Macro(s) #######################################################
// #############################################################################

// #############################################################################
// #### Private Type(s) ########################################################
// #############################################################################

typedef struct __attribute__((packed, aligned(1))) _Platform_Pin_Setting_t
{
} _Platform_Pin_Setting_t;

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

__attribute((weak))
Platform_Status_t Platform_Pin_Setting_Initialize
(
        Platform_Pin_t Platform_Pin,
        Platform_Pin_Setting_t * Platform_Pin_Setting
)
{
    Platform_Status_t Platform_Status = Platform_Status_NotSupported;
    return Platform_Status;
}

__attribute((weak))
Platform_Status_t Platform_Pin_Setting_Mode_Set
(
        Platform_Pin_Setting_t Platform_Pin_Setting,
        Platform_Pin_Mode_t Platform_Pin_Mode
)
{
    Platform_Status_t Platform_Status = Platform_Status_NotSupported;
    return Platform_Status;
}

__attribute((weak))
Platform_Status_t Platform_Pin_Setup
(
        Platform_Pin_t Platform_Pin,
        Platform_Pin_Setting_t Platform_Pin_Setting
)
{
    Platform_Status_t Platform_Status = Platform_Status_NotSupported;
    return Platform_Status;
}

__attribute((weak))
Platform_Status_t Platform_Pin_Write
(
        Platform_Pin_t Platform_Pin,
        Platform_Pin_Value_t Platform_Pin_Value
)
{
    Platform_Status_t Platform_Status = Platform_Status_NotSupported;
    return Platform_Status;
}

__attribute((weak))
Platform_Status_t Platform_Pin_Read
(
        Platform_Pin_t Platform_Pin,
        Platform_Pin_Value_t * Platform_Pin_Value
)
{
    Platform_Status_t Platform_Status = Platform_Status_NotSupported;
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

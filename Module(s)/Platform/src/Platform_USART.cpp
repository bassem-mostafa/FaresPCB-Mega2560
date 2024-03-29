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

#include "Platform_USART.h"

// #############################################################################
// #### Private Macro(s) #######################################################
// #############################################################################

// #############################################################################
// #### Private Type(s) ########################################################
// #############################################################################

typedef struct __attribute__((packed, aligned(1))) _Platform_USART_Setting_t
{
} _Platform_USART_Setting_t;

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
Platform_Status_t Platform_USART_Setting_Initialize
(
        Platform_USART_Setting_t * Platform_USART_Setting
)
{
    Platform_Status_t Platform_Status = Platform_Status_NotSupported;
    return Platform_Status;
}

__attribute((weak))
Platform_Status_t Platform_USART_Setting_Baudrate_Set
(
        Platform_USART_Setting_t Platform_USART_Setting,
        Platform_USART_Baudrate_t Platform_USART_Baudrate
)
{
    Platform_Status_t Platform_Status = Platform_Status_NotSupported;
    return Platform_Status;
}

__attribute((weak))
Platform_Status_t Platform_USART_Setup
(
        Platform_USART_t Platform_USART,
        Platform_USART_Setting_t Platform_USART_Setting
)
{
    Platform_Status_t Platform_Status = Platform_Status_NotSupported;
    return Platform_Status;
}

__attribute((weak))
Platform_Status_t Platform_USART_Write
(
        Platform_USART_t Platform_USART,
        Platform_USART_Data_t Platform_USART_Data,
        Platform_USART_Data_Length_t Platform_USART_Data_Length
)
{
    Platform_Status_t Platform_Status = Platform_Status_NotSupported;
    return Platform_Status;
}

__attribute((weak))
Platform_Status_t Platform_USART_Read
(
        Platform_USART_t Platform_USART,
        Platform_USART_Data_t Platform_USART_Data,
        Platform_USART_Data_Length_t Platform_USART_Data_Length,
        Platform_USART_Data_Length_t * Platform_USART_Data_Length_Read
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

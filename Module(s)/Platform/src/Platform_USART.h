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

#ifndef PLATFORM_USART_H_
#define PLATFORM_USART_H_

// #############################################################################
// #### Include(s) #############################################################
// #############################################################################

#include "Platform_Types.h"
#include "stdint.h"
#include "stddef.h"

// #############################################################################
// #### Public Macro(s) ########################################################
// #############################################################################

// #############################################################################
// #### Public Type(s) #########################################################
// #############################################################################

typedef enum __attribute__((packed, aligned(1))) Platform_USART_t
{
    Platform_USART_1,
    Platform_USART_2,
    Platform_USART_3,
    Platform_USART_4,
    Platform_USART_5,
    Platform_USART_6,
    Platform_USART_7,
    Platform_USART_8,
    Platform_USART_9,
    Platform_USART_10,
    // TODO Need More USARTs ?
} Platform_USART_t;

typedef enum __attribute__((packed, aligned(1))) Platform_USART_Baudrate_t
{
    Platform_USART_Baudrate_110,
    Platform_USART_Baudrate_300,
    Platform_USART_Baudrate_600,
    Platform_USART_Baudrate_1200,
    Platform_USART_Baudrate_2400,
    Platform_USART_Baudrate_4800,
    Platform_USART_Baudrate_9600,
    Platform_USART_Baudrate_14400,
    Platform_USART_Baudrate_19200,
    Platform_USART_Baudrate_38400,
    Platform_USART_Baudrate_57600,
    Platform_USART_Baudrate_115200,
    Platform_USART_Baudrate_230400,
    Platform_USART_Baudrate_460800,
    Platform_USART_Baudrate_921600,
} Platform_USART_Baudrate_t;

typedef uint8_t* Platform_USART_Data_t;

typedef uint16_t Platform_USART_Data_Length_t;

typedef struct _Platform_USART_Setting_t* Platform_USART_Setting_t;

// #############################################################################
// #### Public Method(s) #######################################################
// #############################################################################

Platform_Status_t Platform_USART_Setting_Initialize
(
        Platform_USART_Setting_t * Platform_USART_Setting
);

Platform_Status_t Platform_USART_Setting_Baudrate_Set
(
        Platform_USART_Setting_t Platform_USART_Setting,
        Platform_USART_Baudrate_t Platform_USART_Baudrate
);

Platform_Status_t Platform_USART_Setup
(
        Platform_USART_t Platform_USART,
        Platform_USART_Setting_t Platform_USART_Setting
);

Platform_Status_t Platform_USART_Write
(
        Platform_USART_t Platform_USART,
        Platform_USART_Data_t Platform_USART_Data,
        Platform_USART_Data_Length_t Platform_USART_Data_Length
);

Platform_Status_t Platform_USART_Read
(
        Platform_USART_t Platform_USART,
        Platform_USART_Data_t Platform_USART_Data,
        Platform_USART_Data_Length_t Platform_USART_Data_Length,
        Platform_USART_Data_Length_t * Platform_USART_Data_Length_Read = NULL
);

// #############################################################################
// #### Public Variable(s) #####################################################
// #############################################################################

// #############################################################################
// #### File Guard #############################################################
// #############################################################################

#endif /* PLATFORM_USART_H_ */

// #############################################################################
// #### END OF FILE ############################################################
// #############################################################################

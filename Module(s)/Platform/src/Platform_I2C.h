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

#ifndef PLATFORM_I2C_H_
#define PLATFORM_I2C_H_

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

typedef enum __attribute__((packed, aligned(1))) Platform_I2C_t
{
    Platform_I2C_1,
    Platform_I2C_2,
    Platform_I2C_3,
    Platform_I2C_4,
    Platform_I2C_5,
    Platform_I2C_6,
    Platform_I2C_7,
    Platform_I2C_8,
    Platform_I2C_9,
    Platform_I2C_10,
    // TODO Need More I2Cs ?
} Platform_I2C_t;

typedef uint8_t Platform_I2C_Address_t;

typedef uint8_t* Platform_I2C_Data_t;

typedef uint8_t Platform_I2C_Data_Length_t;

typedef struct _Platform_I2C_Setting_t* Platform_I2C_Setting_t;

// #############################################################################
// #### Public Method(s) #######################################################
// #############################################################################

Platform_Status_t Platform_I2C_Setting_Initialize
(
        Platform_I2C_Setting_t * Platform_I2C_Setting
);

Platform_Status_t Platform_I2C_Setup
(
        Platform_I2C_t Platform_I2C,
        Platform_I2C_Setting_t Platform_I2C_Setting
);

Platform_Status_t Platform_I2C_Write
(
        Platform_I2C_t Platform_I2C,
        Platform_I2C_Address_t Platform_I2C_Address,
        Platform_I2C_Data_t Platform_I2C_Data,
        Platform_I2C_Data_Length_t Platform_I2C_Data_Length
);

Platform_Status_t Platform_I2C_Read
(
        Platform_I2C_t Platform_I2C,
        Platform_I2C_Address_t Platform_I2C_Address,
        Platform_I2C_Data_t Platform_I2C_Data,
        Platform_I2C_Data_Length_t Platform_I2C_Data_Length,
        Platform_I2C_Data_Length_t * Platform_I2C_Data_Length_Read = NULL
);

// #############################################################################
// #### Public Variable(s) #####################################################
// #############################################################################

// #############################################################################
// #### File Guard #############################################################
// #############################################################################

#endif /* PLATFORM_I2C_H_ */

// #############################################################################
// #### END OF FILE ############################################################
// #############################################################################

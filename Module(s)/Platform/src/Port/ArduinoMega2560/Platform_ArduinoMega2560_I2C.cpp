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

#include "Platform_ArduinoMega2560.h"
#include "Wire.h"

// #############################################################################
// #### Private Macro(s) #######################################################
// #############################################################################

// #############################################################################
// #### Private Type(s) ########################################################
// #############################################################################

typedef enum __attribute__((packed, aligned(1))) _Platform_I2C_Instance_Mode_t
{
    _Platform_I2C_Instance_Mode_Master = 0,
    _Platform_I2C_Instance_Mode_Slave,
} _Platform_I2C_Instance_Mode_t;

typedef TwoWire * _Platform_I2C_Instance_t;

typedef struct __attribute__((packed, aligned(1))) _Platform_I2C_Setting_t
{
} _Platform_I2C_Setting_t;

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

Platform_Status_t Platform_I2C_Setting_Initialize
(
        Platform_I2C_Setting_t * Platform_I2C_Setting
)
{
    Platform_Status_t Platform_Status = Platform_Status_NotSupported;
    return Platform_Status;
}

Platform_Status_t Platform_I2C_Setup
(
        Platform_I2C_t Platform_I2C,
        Platform_I2C_Setting_t Platform_I2C_Setting
)
{
    Platform_Status_t Platform_Status = Platform_Status_NotSupported;
    return Platform_Status;
}

Platform_Status_t Platform_I2C_Write
(
        Platform_I2C_t Platform_I2C,
        Platform_I2C_Address_t Platform_I2C_Address,
        Platform_I2C_Data_t Platform_I2C_Data,
        Platform_I2C_Data_Length_t Platform_I2C_Data_Length
)
{
    Platform_Status_t Platform_Status = Platform_Status_NotSupported;
    return Platform_Status;
}

Platform_Status_t Platform_I2C_Read
(
        Platform_I2C_t Platform_I2C,
        Platform_I2C_Address_t Platform_I2C_Address,
        Platform_I2C_Data_t Platform_I2C_Data,
        Platform_I2C_Data_Length_t Platform_I2C_Data_Length,
        Platform_I2C_Data_Length_t * Platform_I2C_Data_Length_Read
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

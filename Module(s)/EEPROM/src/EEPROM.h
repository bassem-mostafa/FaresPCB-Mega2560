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

#ifndef EEPROM_H_
#define EEPROM_H_

// #############################################################################
// #### Include(s) #############################################################
// #############################################################################

#include "stdint.h"
#include "stddef.h"

// #############################################################################
// #### Public Macro(s) ########################################################
// #############################################################################

// #############################################################################
// #### Public Type(s) #########################################################
// #############################################################################

typedef enum __attribute__((packed, aligned(1))) EEPROM_Status_t
{
    EEPROM_Status_Success,
    EEPROM_Status_Error,
    EEPROM_Status_Timeout,
} EEPROM_Status_t;

typedef uint32_t EEPROM_Memory_Address_t;

typedef uint8_t* EEPROM_Memory_Data_t;

typedef uint8_t EEPROM_Memory_Data_Length_t;

// #############################################################################
// #### Public Method(s) #######################################################
// #############################################################################

EEPROM_Status_t EEPROM_Write
(
        EEPROM_Memory_Address_t EEPROM_Memory_Address,
        EEPROM_Memory_Data_t EEPROM_Memory_Data,
        EEPROM_Memory_Data_Length_t EEPROM_Memory_Data_Length
);

EEPROM_Status_t EEPROM_Read
(
        EEPROM_Memory_Address_t EEPROM_Memory_Address,
        EEPROM_Memory_Data_t EEPROM_Memory_Data,
        EEPROM_Memory_Data_Length_t EEPROM_Memory_Data_Length,
        EEPROM_Memory_Data_Length_t * EEPROM_Memory_Data_Length_Read = NULL
);

// #############################################################################
// #### Public Variable(s) #####################################################
// #############################################################################

// #############################################################################
// #### File Guard #############################################################
// #############################################################################

#endif /* EEPROM_H_ */

// #############################################################################
// #### END OF FILE ############################################################
// #############################################################################
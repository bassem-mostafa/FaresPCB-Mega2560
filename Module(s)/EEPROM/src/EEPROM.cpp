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

#include "EEPROM.h"
#include "Platform.h"
#include "string.h"
#include "util/delay.h"

// #############################################################################
// #### Private Macro(s) #######################################################
// #############################################################################

#define _EEPROM_BANK_SIZE       (32*1024) // 32 KB
#define _EEPROM_NUMBER_OF_BANKS (2)

// #############################################################################
// #### Private Type(s) ########################################################
// #############################################################################

typedef uint8_t _EEPROM_Byte_t;
typedef uint16_t _EEPROM_Half_Word_t;

typedef struct __attribute__((packed, aligned(1))) _EEPROM_Packet_t
{
        _EEPROM_Byte_t content_length;
        struct __attribute__((packed, aligned(1)))
        {
                _EEPROM_Half_Word_t address;
                _EEPROM_Byte_t data[0xFF-sizeof(address)];
        } content;
} _EEPROM_Packet_t;

// #############################################################################
// #### Private Method(s) Prototype ############################################
// #############################################################################

// #############################################################################
// #### Private Variable(s) ####################################################
// #############################################################################

// #############################################################################
// #### Private Method(s) ######################################################
// #############################################################################

bool _EEPROM_Initialize
(
        void
)
{
    static bool isInitialized = false;
    do
    {
        if (isInitialized) break;

        Platform_I2C_Setting_t Platform_I2C_Setting = NULL;
        Platform_I2C_Setting_Initialize(&Platform_I2C_Setting);
        Platform_I2C_Setup(Platform_I2C_1, Platform_I2C_Setting);
        isInitialized = true;
    }
    while(0);
    return isInitialized;
}
#include "stdio.h"
EEPROM_Status_t _EEPROM_Write
(
        const EEPROM_Memory_Address_t EEPROM_Memory_Address,
        const EEPROM_Memory_Data_t EEPROM_Memory_Data,
        const EEPROM_Memory_Data_Length_t EEPROM_Memory_Data_Length
)
{
    EEPROM_Status_t EEPROM_Status = EEPROM_Status_Error;
    do
    {
        if (_EEPROM_Initialize() != true) { EEPROM_Status = EEPROM_Status_Error; break; }
        if (EEPROM_Memory_Address > 0x7FFF) { EEPROM_Status = EEPROM_Status_Error; break; }
        if ((EEPROM_Memory_Address + EEPROM_Memory_Data_Length) > 0x7FFF) { EEPROM_Status = EEPROM_Status_Error; break; }

        _EEPROM_Packet_t _EEPROM_Packet = (_EEPROM_Packet_t) {
            2 /* content_length */,
            {
                    /* content.address */
                    EEPROM_Memory_Address,
                    /* content.data */
            }
        };
        if (sizeof(_EEPROM_Packet.content.data) < EEPROM_Memory_Data_Length) { EEPROM_Status = EEPROM_Status_Error; break; }

        memcpy(_EEPROM_Packet.content.data, EEPROM_Memory_Data, EEPROM_Memory_Data_Length);
        _EEPROM_Packet.content_length += EEPROM_Memory_Data_Length;

        if (Platform_I2C_Write(Platform_I2C_1, Platform_I2C_Address_EEPROM, (Platform_I2C_Data_t)&(_EEPROM_Packet.content), _EEPROM_Packet.content_length) != Platform_Status_Success) { EEPROM_Status = EEPROM_Status_Error; break; }
        _delay_ms(10); // wait for EEPROM to finish its internal operations
        EEPROM_Status = EEPROM_Status_Success;
    }
    while(0);
    return EEPROM_Status;
}

EEPROM_Status_t _EEPROM_Read
(
        const EEPROM_Memory_Address_t EEPROM_Memory_Address,
        const EEPROM_Memory_Data_t EEPROM_Memory_Data,
        const EEPROM_Memory_Data_Length_t EEPROM_Memory_Data_Length,
        const EEPROM_Memory_Data_Length_t * EEPROM_Memory_Data_Length_Read
)
{
    EEPROM_Status_t EEPROM_Status = EEPROM_Status_Error;
    do
    {
        if (_EEPROM_Initialize() != true) { EEPROM_Status = EEPROM_Status_Error; break; }
        if (EEPROM_Memory_Address > 0x7FFF) { EEPROM_Status = EEPROM_Status_Error; break; }
        if ((EEPROM_Memory_Address + EEPROM_Memory_Data_Length) > 0x7FFF) { EEPROM_Status = EEPROM_Status_Error; break; }

        _EEPROM_Packet_t _EEPROM_Packet = (_EEPROM_Packet_t) {
            2 /* content_length */,
            {
                    /* content.address */
                    EEPROM_Memory_Address,
                    /* content.data */
            }
        };

        if ( Platform_I2C_Write(Platform_I2C_1, Platform_I2C_Address_EEPROM, (Platform_I2C_Data_t)&(_EEPROM_Packet.content), _EEPROM_Packet.content_length) != Platform_Status_Success ) {}

        if (Platform_I2C_Read(Platform_I2C_1, Platform_I2C_Address_EEPROM, EEPROM_Memory_Data, EEPROM_Memory_Data_Length, (Platform_I2C_Data_Length_t*)EEPROM_Memory_Data_Length_Read) != Platform_Status_Success) { EEPROM_Status = EEPROM_Status_Error; break; }
        EEPROM_Status = EEPROM_Status_Success;
    }
    while(0);
    return EEPROM_Status;
}

// #############################################################################
// #### Public Method(s) #######################################################
// #############################################################################

EEPROM_Status_t EEPROM_Write
(
        EEPROM_Memory_Address_t EEPROM_Memory_Address,
        EEPROM_Memory_Data_t EEPROM_Memory_Data,
        EEPROM_Memory_Data_Length_t EEPROM_Memory_Data_Length
)
{
    EEPROM_Status_t EEPROM_Status = EEPROM_Status_Error;
    do
    {
        if ( (EEPROM_Status = _EEPROM_Write(EEPROM_Memory_Address, EEPROM_Memory_Data, EEPROM_Memory_Data_Length)) != EEPROM_Status_Success) { break; }
        EEPROM_Status = EEPROM_Status_Success;
    }
    while(0);
    return EEPROM_Status;
}

EEPROM_Status_t EEPROM_Read
(
        EEPROM_Memory_Address_t EEPROM_Memory_Address,
        EEPROM_Memory_Data_t EEPROM_Memory_Data,
        EEPROM_Memory_Data_Length_t EEPROM_Memory_Data_Length,
        EEPROM_Memory_Data_Length_t * EEPROM_Memory_Data_Length_Read
)
{
    EEPROM_Status_t EEPROM_Status = EEPROM_Status_Error;
    do
    {
        if ( (EEPROM_Status = _EEPROM_Read(EEPROM_Memory_Address, EEPROM_Memory_Data, EEPROM_Memory_Data_Length, EEPROM_Memory_Data_Length_Read)) != EEPROM_Status_Success) { break; }
        EEPROM_Status = EEPROM_Status_Success;
    }
    while(0);
    return EEPROM_Status;
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

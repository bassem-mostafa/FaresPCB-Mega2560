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
#include "Bluetooth.h"

// #############################################################################
// #### Private Macro(s) #######################################################
// #############################################################################

#define SERIAL_BAUD     9600
#define MIN(N1, N2)     ( (N1) < (N2) ? (N1) : (N2) )

// #############################################################################
// #### Private Type(s) ########################################################
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
 * @brief Initializes bluetooth
 *
 * @param[in] void  : None
 *
 * @return void  : None
 */
void Bluetooth_Init( void )
{
    HW_PIN_INPUT(HW_BLUETOOTH_STATE);
    HW_PIN_OUTPUT(HW_BLUETOOTH_KEY);
    HW_BLUETOOTH_SERIAL.begin(SERIAL_BAUD);
    while(!HW_BLUETOOTH_SERIAL);

    HW_PIN_CLEAR(HW_BLUETOOTH_KEY);
}

/*
 * @brief Gets bluetooth status
 *
 * @param[in] void  : None
 *
 * @return Bluetooth_Status_Connected   : if connected
 * @return Bluetooth_Status_Idle        : if idle or disconnected
 */
Bluetooth_Status_t Bluetooth_Status( void )
{
    Bluetooth_Status_t Bluetooth_Status = Bluetooth_Status_Idle;
    Bluetooth_Status = ( (HW_PIN_READ(HW_BLUETOOTH_STATE) == HIGH) ? Bluetooth_Status_Connected : Bluetooth_Status_Idle);
    return Bluetooth_Status;
}

/*
 * @brief Reads bluetooth received data
 *
 * @param[in] buffer  : buffer reference
 * @param[in] length  : buffer length
 *
 * @return uint32_t     : number of bytes read
 */
uint32_t Bluetooth_Read( uint8_t * buffer, uint32_t length )
{
    uint32_t bytes_read = 0;
    if (HW_BLUETOOTH_SERIAL.available() > 0)
    {
        bytes_read = HW_BLUETOOTH_SERIAL.readBytes(buffer, MIN(length, HW_BLUETOOTH_SERIAL.available()));
    }
    return bytes_read;
}

/*
 * @brief Writes bluetooth data
 *
 * @param[in] buffer  : buffer reference
 * @param[in] length  : buffer length
 *
 * @return uint32_t     : number of bytes sent
 */
uint32_t Bluetooth_Write( uint8_t * buffer, uint32_t length )
{
    uint32_t bytes_sent = 0;
    bytes_sent = HW_BLUETOOTH_SERIAL.write(buffer, length);
    return bytes_sent;
}

// #############################################################################
// #### Public Variable(s) #####################################################
// #############################################################################

// #############################################################################
// #### END OF FILE ############################################################
// #############################################################################

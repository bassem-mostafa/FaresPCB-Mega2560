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
// #### File Guard #############################################################
// #############################################################################

#ifndef FARESPCB_BLUETOOTH_H_
#define FARESPCB_BLUETOOTH_H_

// #############################################################################
// #### Include(s) #############################################################
// #############################################################################

#include <stdint.h>

// #############################################################################
// #### Public Macro(s) ########################################################
// #############################################################################

// #############################################################################
// #### Public Type(s) #########################################################
// #############################################################################

typedef enum Bluetooth_Status_t
{
    Bluetooth_Status_Idle = 0,
    Bluetooth_Status_Connected,
} Bluetooth_Status_t;

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
void Bluetooth_Initialize( void );

/*
 * @brief Gets bluetooth status
 *
 * @param[in] void  : None
 *
 * @return Bluetooth_Status_Connected   : if connected
 * @return Bluetooth_Status_Idle        : if idle or disconnected
 */
Bluetooth_Status_t Bluetooth_Status( void );

/*
 * @brief Reads bluetooth received data
 *
 * @param[in] buffer  : buffer reference
 * @param[in] length  : buffer length
 *
 * @return uint32_t     : number of bytes read
 */
uint32_t Bluetooth_Read( uint8_t * buffer, uint32_t length );

/*
 * @brief Writes bluetooth data
 *
 * @param[in] buffer  : buffer reference
 * @param[in] length  : buffer length
 *
 * @return uint32_t     : number of bytes sent
 */
uint32_t Bluetooth_Write( uint8_t * buffer, uint32_t length );

// #############################################################################
// #### Public Variable(s) #####################################################
// #############################################################################

// #############################################################################
// #### File Guard #############################################################
// #############################################################################

#endif /* FARESPCB_BLUETOOTH_H_ */

// #############################################################################
// #### END OF FILE ############################################################
// #############################################################################

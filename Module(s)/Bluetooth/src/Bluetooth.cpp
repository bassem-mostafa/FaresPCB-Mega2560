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

#include "Bluetooth.h"
#include "Platform.h"

// #############################################################################
// #### Private Macro(s) #######################################################
// #############################################################################

#define _Bluetooth_Min(N1, N2)     ( (N1) < (N2) ? (N1) : (N2) )

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

/*
 * @brief Initializes bluetooth
 *
 * @param[in] void  : None
 *
 * @return void  : None
 */
bool _Bluetooth_Initialize( void )
{
    static bool isInitialized = false;
    do
    {
        if (isInitialized) break;
        Platform_Pin_Setup(Platform_Pin_BLUETOOTH_STATE, Platform_Pin_Mode_INPUT);
        Platform_Pin_Setup(Platform_Pin_BLUETOOTH_KEY, Platform_Pin_Mode_OUTPUT);
        Platform_Pin_Write(Platform_Pin_BLUETOOTH_KEY, Platform_Pin_Value_LOW);
        isInitialized = true;
    }
    while(0);
    return isInitialized;
}

// #############################################################################
// #### Public Method(s) #######################################################
// #############################################################################

/*
 * @brief Gets bluetooth status
 *
 * @param[in] void  : None
 *
 * @return Bluetooth_Status_Connected   : if connected
 * @return Bluetooth_Status_Idle        : if idle or disconnected
 */
Bluetooth_Status_t Bluetooth_StatusGet( void )
{
    _Bluetooth_Initialize();
    Bluetooth_Status_t Bluetooth_Status = Bluetooth_Status_Idle;
    Platform_Pin_Value_t Platform_Pin_Value = Platform_Pin_Value_LOW;
    Platform_Pin_Read(Platform_Pin_BLUETOOTH_STATE, &Platform_Pin_Value);
    Bluetooth_Status = ( (Platform_Pin_Value == Platform_Pin_Value_HIGH) ? Bluetooth_Status_Connected : Bluetooth_Status_Idle);
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
    _Bluetooth_Initialize();
    Platform_USART_Read(Platform_USART_BLUETOOTH, Platform_USART_Baudrate_9600, buffer, length);
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
    if (Platform_USART_Write(Platform_USART_BLUETOOTH, Platform_USART_Baudrate_9600, buffer, length) == Platform_Status_Success )
    {
        bytes_sent = length;
    }
    return bytes_sent;
}

// #############################################################################
// #### Public Variable(s) #####################################################
// #############################################################################

// #############################################################################
// #### END OF FILE ############################################################
// #############################################################################

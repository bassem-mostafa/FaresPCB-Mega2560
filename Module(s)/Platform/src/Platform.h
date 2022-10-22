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

#ifndef PLATFORM_H_
#define PLATFORM_H_

// #############################################################################
// #### Include(s) #############################################################
// #############################################################################

#include "stdint.h"
#include "Platform_ArduinoMega2560.h" // Platform Dependent Header

// #############################################################################
// #### Public Macro(s) ########################################################
// #############################################################################

// #############################################################################
// #### Public Type(s) #########################################################
// #############################################################################

typedef enum __attribute__((packed, aligned(1))) Platform_Status_t
{
    Platform_Status_Success,
    Platform_Status_Error,
    Platform_Status_Timeout,
    Platform_Status_NotSupported,
} Platform_Status_t;

typedef enum __attribute__((packed, aligned(1))) Platform_Pin_t
{
    Platform_Pin_0 = 0,
    Platform_Pin_1,
    Platform_Pin_2,
    Platform_Pin_3,
    Platform_Pin_4,
    Platform_Pin_5,
    Platform_Pin_6,
    Platform_Pin_7,
    Platform_Pin_8,
    Platform_Pin_9,
    Platform_Pin_10,
    Platform_Pin_11,
    Platform_Pin_12,
    Platform_Pin_13,
    Platform_Pin_14,
    Platform_Pin_15,
    Platform_Pin_16,
    Platform_Pin_17,
    Platform_Pin_18,
    Platform_Pin_19,
    Platform_Pin_20,
    Platform_Pin_21,
    Platform_Pin_22,
    Platform_Pin_23,
    Platform_Pin_24,
    Platform_Pin_25,
    Platform_Pin_26,
    Platform_Pin_27,
    Platform_Pin_28,
    Platform_Pin_29,
    Platform_Pin_30,
    Platform_Pin_31,
    Platform_Pin_32,
    Platform_Pin_33,
    Platform_Pin_34,
    Platform_Pin_35,
    Platform_Pin_36,
    Platform_Pin_37,
    Platform_Pin_38,
    Platform_Pin_39,
    Platform_Pin_40,
    Platform_Pin_41,
    Platform_Pin_42,
    Platform_Pin_43,
    Platform_Pin_44,
    Platform_Pin_45,
    Platform_Pin_46,
    Platform_Pin_47,
    Platform_Pin_48,
    Platform_Pin_49,
    Platform_Pin_50,
    Platform_Pin_51,
    Platform_Pin_52,
    Platform_Pin_53,
    Platform_Pin_54,
    Platform_Pin_55,
    Platform_Pin_56,
    Platform_Pin_57,
    Platform_Pin_58,
    Platform_Pin_59,
    Platform_Pin_60,
    Platform_Pin_61,
    Platform_Pin_62,
    Platform_Pin_63,
    Platform_Pin_64,
    Platform_Pin_65,
    Platform_Pin_66,
    Platform_Pin_67,
    Platform_Pin_68,
    Platform_Pin_69,
    Platform_Pin_70,
    Platform_Pin_71,
    Platform_Pin_72,
    Platform_Pin_73,
    Platform_Pin_74,
    Platform_Pin_75,
    Platform_Pin_76,
    Platform_Pin_77,
    Platform_Pin_78,
    Platform_Pin_79,
    Platform_Pin_80,
    Platform_Pin_81,
    Platform_Pin_82,
    Platform_Pin_83,
    Platform_Pin_84,
    Platform_Pin_85,
    Platform_Pin_86,
    Platform_Pin_87,
    Platform_Pin_88,
    Platform_Pin_89,
    Platform_Pin_90,
    Platform_Pin_91,
    Platform_Pin_92,
    Platform_Pin_93,
    Platform_Pin_94,
    Platform_Pin_95,
    Platform_Pin_96,
    Platform_Pin_97,
    Platform_Pin_98,
    Platform_Pin_99,
    Platform_Pin_100,
    // TODO Need More Pins ?
} Platform_Pin_t;

typedef enum __attribute__((packed, aligned(1))) Platform_Pin_Mode_t
{
    Platform_Pin_Mode_OUTPUT,
    Platform_Pin_Mode_OUTPUT_OpenDrain,
    Platform_Pin_Mode_OUTPUT_PushPull,
    Platform_Pin_Mode_INPUT,
    Platform_Pin_Mode_INPUT_PullUp,
    Platform_Pin_Mode_INPUT_PullDown,
    Platform_Pin_Mode_TRI_STATE,
} Platform_Pin_Mode_t;

typedef enum __attribute__((packed, aligned(1))) Platform_Pin_Value_t
{
    Platform_Pin_Value_LOW,
    Platform_Pin_Value_HIGH
} Platform_Pin_Value_t;

typedef uint8_t Platform_Pin_Value_PWM_t;

typedef enum __attribute__((packed, aligned(1))) Platform_I2C_t
{
    Platform_I2C_1,
    Platform_I2C_2,
    Platform_I2C_3,
    Platform_I2C_4,
} Platform_I2C_t;

typedef const uint8_t Platform_I2C_Address_t;

typedef uint8_t* const Platform_I2C_Data_t;

typedef const uint16_t Platform_I2C_Data_Length_t;

typedef enum __attribute__((packed, aligned(1))) Platform_SPI_t
{
    Platform_SPI_1,
    Platform_SPI_2,
    Platform_SPI_3,
    Platform_SPI_4,
} Platform_SPI_t;

typedef uint8_t* const Platform_SPI_Data_t;

typedef const uint16_t Platform_SPI_Data_Length_t;

typedef enum __attribute__((packed, aligned(1))) Platform_USART_t
{
    Platform_USART_1,
    Platform_USART_2,
    Platform_USART_3,
    Platform_USART_4,
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

typedef uint8_t* const Platform_USART_Data_t;

typedef const uint16_t Platform_USART_Data_Length_t;

// #############################################################################
// #### Public Method(s) #######################################################
// #############################################################################

Platform_Status_t Platform_Pin_Setup
(
        const Platform_Pin_t Platform_Pin,
        const Platform_Pin_Mode_t Platform_Pin_Mode
);

Platform_Status_t Platform_Pin_Write
(
        const Platform_Pin_t Platform_Pin,
        const Platform_Pin_Value_t Platform_Pin_Value
);

Platform_Status_t Platform_Pin_Write_PWM
(
        const Platform_Pin_t Platform_Pin,
        const Platform_Pin_Value_PWM_t Platform_Pin_Value_PWM
);

Platform_Status_t Platform_Pin_Read
(
        const Platform_Pin_t Platform_Pin,
        Platform_Pin_Value_t * const Platform_Pin_Value
);

Platform_Status_t Platform_I2C_Write
(
        const Platform_I2C_t Platform_I2C,
        const Platform_I2C_Address_t Platform_I2C_Address,
        const Platform_I2C_Data_t Platform_I2C_Data,
        const Platform_I2C_Data_Length_t Platform_I2C_Data_Length
);

Platform_Status_t Platform_I2C_Read
(
        const Platform_I2C_t Platform_I2C,
        const Platform_I2C_Address_t Platform_I2C_Address,
        Platform_I2C_Data_t Platform_I2C_Data,
        const Platform_I2C_Data_Length_t Platform_I2C_Data_Length
);

Platform_Status_t Platform_SPI_Transaction
(
        const Platform_SPI_t Platform_SPI,
        Platform_SPI_Data_t Platform_SPI_Data,
        const Platform_SPI_Data_Length_t Platform_SPI_Data_Length
);

Platform_Status_t Platform_USART_Write
(
        const Platform_USART_t Platform_USART,
        const Platform_USART_Baudrate_t Platform_USART_Baudrate,
        const Platform_USART_Data_t Platform_USART_Data,
        const Platform_USART_Data_Length_t Platform_USART_Data_Length
);

Platform_Status_t Platform_USART_Read
(
        const Platform_USART_t Platform_USART,
        const Platform_USART_Baudrate_t Platform_USART_Baudrate,
        Platform_USART_Data_t Platform_USART_Data,
        const Platform_USART_Data_Length_t Platform_USART_Data_Length
);

// #############################################################################
// #### Public Variable(s) #####################################################
// #############################################################################

// #############################################################################
// #### File Guard #############################################################
// #############################################################################

#endif /* PLATFORM_H_ */

// #############################################################################
// #### END OF FILE ############################################################
// #############################################################################

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

#ifndef PLATFORM_ARDUINO_MEGA2560_H_
#define PLATFORM_ARDUINO_MEGA2560_H_

#if defined(ARDUINO) && defined(ARDUINO_AVR_MEGA2560) && defined(__AVR_ATmega2560__)
// Platform Matches
#else
#error "Platform Does NOT Match"
#endif

// #############################################################################
// #### Include(s) #############################################################
// #############################################################################

#include "Platform.h"

// #############################################################################
// #### Public Macro(s) ########################################################
// #############################################################################

//====================================
//Arduino Mega 2560 PIN mapping table:
//====================================
//
//Pin Number  Pin Name                    Mapped Pin Name               Fares PCB Board Pin
//-----------------------------------------------------------------------------------------
//1           PG5 ( OC0B )                Digital pin 4 (PWM)           7SEGMENT BIT2
//2           PE0 ( RXD0/PCINT8 )         Digital pin 0 (RX0)           SERIAL RX0 (USB)
//3           PE1 ( TXD0 )                Digital pin 1 (TX0)           SERIAL TX0 (USB)
//4           PE2 ( XCK0/AIN0 )
//5           PE3 ( OC3A/AIN1 )           Digital pin 5 (PWM)           7SEGMENT BIT3
//6           PE4 ( OC3B/INT4 )           Digital pin 2 (PWM)           7SEGMENT BIT0
//7           PE5 ( OC3C/INT5 )           Digital pin 3 (PWM)           7SEGMENT BIT1
//8           PE6 ( T3/INT6 )
//9           PE7 ( CLKO/ICP3/INT7 )
//10          VCC                         VCC
//11          GND                         GND
//12          PH0 ( RXD2 )                Digital pin 17 (RX2)
//13          PH1 ( TXD2 )                Digital pin 16 (TX2)
//14          PH2 ( XCK2 )
//15          PH3 ( OC4A )                Digital pin 6 (PWM)           7SEGMENT SEL4
//16          PH4 ( OC4B )                Digital pin 7 (PWM)           7SEGMENT SEL3
//17          PH5 ( OC4C )                Digital pin 8 (PWM)           7SEGMENT SEL2
//18          PH6 ( OC2B )                Digital pin 9 (PWM)           7SEGMENT SEL1
//19          PB0 ( SS/PCINT0 )           Digital pin 53 (SS)           LCD BL
//20          PB1 ( SCK/PCINT1 )          Digital pin 52 (SCK)
//21          PB2 ( MOSI/PCINT2 )         Digital pin 51 (MOSI)
//22          PB3 ( MISO/PCINT3 )         Digital pin 50 (MISO)
//23          PB4 ( OC2A/PCINT4 )         Digital pin 10 (PWM)          LED RGB Red Color
//24          PB5 ( OC1A/PCINT5 )         Digital pin 11 (PWM)          LED RGB Green Color
//25          PB6 ( OC1B/PCINT6 )         Digital pin 12 (PWM)          LED RGB Blue
//26          PB7 ( OC0A/OC1C/PCINT7 )    Digital pin 13 (PWM)          LED BUILTIN / LED INTERNAL
//27          PH7 ( T4 )
//28          PG3 ( TOSC2 )
//29          PG4 ( TOSC1 )
//30          RESET                       RESET
//31          VCC                         VCC
//32          GND                         GND
//33          XTAL2                       XTAL2
//34          XTAL1                       XTAL1
//35          PL0 ( ICP4 )                Digital pin 49                BUZZER
//36          PL1 ( ICP5 )                Digital pin 48                RELAY2
//37          PL2 ( T5 )                  Digital pin 47                RELAY1
//38          PL3 ( OC5A )                Digital pin 46 (PWM)          LED5
//39          PL4 ( OC5B )                Digital pin 45 (PWM)          LED4
//40          PL5 ( OC5C )                Digital pin 44 (PWM)          LED3
//41          PL6                         Digital pin 43                LED2
//42          PL7                         Digital pin 42                LED1
//43          PD0 ( SCL/INT0 )            Digital pin 21 (SCL)          EEPROM SCL
//44          PD1 ( SDA/INT1 )            Digital pin 20 (SDA)          EEPROM SDA
//45          PD2 ( RXD1/INT2 )           Digital pin 19 (RX1)          BLUETOOTH TX
//46          PD3 ( TXD1/INT3 )           Digital pin 18 (TX1)          BLUETOOTH RX
//47          PD4 ( ICP1 )
//48          PD5 ( XCK1 )
//49          PD6 ( T1 )
//50          PD7 ( T0 )                  Digital pin 38                LCD CS2
//51          PG0 ( WR )                  Digital pin 41                LCD RS
//52          PG1 ( RD )                  Digital pin 40                LCD EN
//53          PC0 ( A8 )                  Digital pin 37                KEYPAD ROW1
//54          PC1 ( A9 )                  Digital pin 36                KEYPAD ROW2
//55          PC2 ( A10 )                 Digital pin 35                KEYPAD ROW3
//56          PC3 ( A11 )                 Digital pin 34                KEYPAD ROW4
//57          PC4 ( A12 )                 Digital pin 33                KEYPAD COL1
//58          PC5 ( A13 )                 Digital pin 32                KEYPAD COL2
//59          PC6 ( A14 )                 Digital pin 31                KEYPAD COL3
//60          PC7 ( A15 )                 Digital pin 30                KEYPAD COL4
//61          VCC                         VCC
//62          GND                         GND
//63          PJ0 ( RXD3/PCINT9 )         Digital pin 15 (RX3)          RS232 RX
//64          PJ1 ( TXD3/PCINT10 )        Digital pin 14 (TX3)          RS232 TX
//65          PJ2 ( XCK3/PCINT11 )
//66          PJ3 ( PCINT12 )
//67          PJ4 ( PCINT13 )
//68          PJ5 ( PCINT14 )
//69          PJ6 ( PCINT 15 )
//70          PG2 ( ALE )                 Digital pin 39                LCD CS1
//71          PA7 ( AD7 )                 Digital pin 29                LCD D7
//72          PA6 ( AD6 )                 Digital pin 28                LCD D6
//73          PA5 ( AD5 )                 Digital pin 27                LCD D5
//74          PA4 ( AD4 )                 Digital pin 26                LCD D4
//75          PA3 ( AD3 )                 Digital pin 25                LCD D3
//76          PA2 ( AD2 )                 Digital pin 24                LCD D2
//77          PA1 ( AD1 )                 Digital pin 23                LCD D1
//78          PA0 ( AD0 )                 Digital pin 22                LCD D0
//79          PJ7
//80          VCC                         VCC
//81          GND                         GND
//82          PK7 ( ADC15/PCINT23 )       Analog pin 15
//83          PK6 ( ADC14/PCINT22 )       Analog pin 14
//84          PK5 ( ADC13/PCINT21 )       Analog pin 13
//85          PK4 ( ADC12/PCINT20 )       Analog pin 12
//86          PK3 ( ADC11/PCINT19 )       Analog pin 11
//87          PK2 ( ADC10/PCINT18 )       Analog pin 10
//88          PK1 ( ADC9/PCINT17 )        Analog pin 9
//89          PK0 ( ADC8/PCINT16 )        Analog pin 8
//90          PF7 ( ADC7 )                Analog pin 7                  ULTRA-SONIC ECHO
//91          PF6 ( ADC6 )                Analog pin 6                  ULTRA-SONIC TRIG
//92          PF5 ( ADC5/TMS )            Analog pin 5                  BLUETOOTH STATE
//93          PF4 ( ADC4/TMK )            Analog pin 4                  BLUETOOTH KEY
//94          PF3 ( ADC3 )                Analog pin 3
//95          PF2 ( ADC2 )                Analog pin 2
//96          PF1 ( ADC1 )                Analog pin 1                  TEMPERATURE SENSOR
//97          PF0 ( ADC0 )                Analog pin 0                  VARIABLE RESISTOR
//98          AREF                        Analog Reference
//99          GND                         GND
//100         AVCC                        VCC

// LEDs Information
#define Platform_Pin_LED_INTERNAL               Platform_Pin_13         // 13
#define Platform_Pin_LED_1                      Platform_Pin_42         // 42
#define Platform_Pin_LED_2                      Platform_Pin_43         // 43
#define Platform_Pin_LED_3                      Platform_Pin_44         // 44
#define Platform_Pin_LED_4                      Platform_Pin_45         // 45
#define Platform_Pin_LED_5                      Platform_Pin_46         // 46
#define Platform_Pin_LED_RGB_RED                Platform_Pin_10         // 10
#define Platform_Pin_LED_RGB_GREEN              Platform_Pin_11         // 11
#define Platform_Pin_LED_RGB_BLUE               Platform_Pin_12         // 12

// RELAYs Information
#define Platform_Pin_RELAY_1                    Platform_Pin_47         // 47
#define Platform_Pin_RELAY_2                    Platform_Pin_48         // 48

// BUZZERs Information
#define Platform_Pin_BUZZER                     Platform_Pin_49         // 49

// 7-SEGMENTs Information
#define Platform_Pin_7SEGMENT_BIT0              Platform_Pin_2          // 2
#define Platform_Pin_7SEGMENT_BIT1              Platform_Pin_3          // 3
#define Platform_Pin_7SEGMENT_BIT2              Platform_Pin_4          // 4
#define Platform_Pin_7SEGMENT_BIT3              Platform_Pin_5          // 5

#define Platform_Pin_7SEGMENT_SEL1              Platform_Pin_9          // 9
#define Platform_Pin_7SEGMENT_SEL2              Platform_Pin_8          // 8
#define Platform_Pin_7SEGMENT_SEL3              Platform_Pin_7          // 7
#define Platform_Pin_7SEGMENT_SEL4              Platform_Pin_6          // 6

// LCD Information
#define Platform_Pin_LCD_BL                     Platform_Pin_53         // 53
#define Platform_Pin_LCD_RS                     Platform_Pin_41         // 41
#define Platform_Pin_LCD_EN                     Platform_Pin_40         // 40
#define Platform_Pin_LCD_D0                     Platform_Pin_22         // 22
#define Platform_Pin_LCD_D1                     Platform_Pin_23         // 23
#define Platform_Pin_LCD_D2                     Platform_Pin_24         // 24
#define Platform_Pin_LCD_D3                     Platform_Pin_25         // 25
#define Platform_Pin_LCD_D4                     Platform_Pin_26         // 26
#define Platform_Pin_LCD_D5                     Platform_Pin_27         // 27
#define Platform_Pin_LCD_D6                     Platform_Pin_28         // 28
#define Platform_Pin_LCD_D7                     Platform_Pin_29         // 29
#define Platform_Pin_LCD_CS1                    Platform_Pin_39         // 39
#define Platform_Pin_LCD_CS2                    Platform_Pin_38         // 38

// KEYPADs Information
#define Platform_Pin_KEYPAD_ROW1                Platform_Pin_37         // 37
#define Platform_Pin_KEYPAD_ROW2                Platform_Pin_36         // 36
#define Platform_Pin_KEYPAD_ROW3                Platform_Pin_35         // 35
#define Platform_Pin_KEYPAD_ROW4                Platform_Pin_34         // 34
#define Platform_Pin_KEYPAD_COL1                Platform_Pin_33         // 33
#define Platform_Pin_KEYPAD_COL2                Platform_Pin_32         // 32
#define Platform_Pin_KEYPAD_COL3                Platform_Pin_31         // 31
#define Platform_Pin_KEYPAD_COL4                Platform_Pin_30         // 30

// RS232s Information
#define Platform_USART_RS232                    Platform_USART_4        // Serial3

// TEMPERATURE SENSORs Information
#define Platform_Pin_TEMPERATURE_SENSOR         Platform_Pin_55         // A1

// VARIABLE RESISTORs Information
#define Platform_Pin_VARIABLE_RESISTOR          Platform_Pin_54         // A0

// RTC Information
#define Platform_I2C_Address_RTC                0x68

// EEPROM Information
#define Platform_I2C_Address_EEPROM             0x50

// BLUETOOTH Information
#define Platform_Pin_BLUETOOTH_KEY              Platform_Pin_58         // A4
#define Platform_Pin_BLUETOOTH_STATE            Platform_Pin_59         // A5
#define Platform_USART_BLUETOOTH                Platform_USART_2        // Serial1

// ULTRA-SONIC Information
#define Platform_Pin_ULTRASONIC_ECHO            Platform_Pin_61         // A7
#define Platform_Pin_ULTRASONIC_TRIG            Platform_Pin_60         // A6

// USB Information
#define Platform_USART_USB                      Platform_USART_1        // Serial

// #############################################################################
// #### Public Type(s) #########################################################
// #############################################################################

// #############################################################################
// #### Public Method(s) #######################################################
// #############################################################################

// #############################################################################
// #### Public Variable(s) #####################################################
// #############################################################################

// #############################################################################
// #### File Guard #############################################################
// #############################################################################

#endif /* PLATFORM_ARDUINO_MEGA2560_H_ */

// #############################################################################
// #### END OF FILE ############################################################
// #############################################################################

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

#ifndef FARESPCB_H_
#define FARESPCB_H_

// #############################################################################
// #### Include(s) #############################################################
// #############################################################################

#include <Arduino.h>

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
//23          PB4 ( OC2A/PCINT4 )         Digital pin 10 (PWM)
//24          PB5 ( OC1A/PCINT5 )         Digital pin 11 (PWM)
//25          PB6 ( OC1B/PCINT6 )         Digital pin 12 (PWM)
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
//45          PD2 ( RXDI/INT2 )           Digital pin 19 (RX1)          BLUETOOTH TX
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
//86          PK3 ( ADC11/PCINT19 )       Analog pin 11                 BLUETOOTH KEY
//87          PK2 ( ADC10/PCINT18 )       Analog pin 10                 BLUETOOTH STATE
//88          PK1 ( ADC9/PCINT17 )        Analog pin 9
//89          PK0 ( ADC8/PCINT16 )        Analog pin 8
//90          PF7 ( ADC7 )                Analog pin 7                  ULTRA-SONIC ECHO
//91          PF6 ( ADC6 )                Analog pin 6                  ULTRA-SONIC TRIG
//92          PF5 ( ADC5/TMS )            Analog pin 5
//93          PF4 ( ADC4/TMK )            Analog pin 4
//94          PF3 ( ADC3 )                Analog pin 3
//95          PF2 ( ADC2 )                Analog pin 2
//96          PF1 ( ADC1 )                Analog pin 1                  VARIABLE RESISTOR
//97          PF0 ( ADC0 )                Analog pin 0                  TEMPERATURE SENSOR
//98          AREF                        Analog Reference
//99          GND                         GND
//100         AVCC                        VCC


// LEDs PINs
#define HW_LED_INTERNAL             (const HW_PinDef) {&DDRB, &PORTB, &PINB, (0x01 << 7)}
#define HW_LED_1                    (const HW_PinDef) {&DDRL, &PORTL, &PINL, (0x01 << 7)}
#define HW_LED_2                    (const HW_PinDef) {&DDRL, &PORTL, &PINL, (0x01 << 6)}
#define HW_LED_3                    (const HW_PinDef) {&DDRL, &PORTL, &PINL, (0x01 << 5)}
#define HW_LED_4                    (const HW_PinDef) {&DDRL, &PORTL, &PINL, (0x01 << 4)}
#define HW_LED_5                    (const HW_PinDef) {&DDRL, &PORTL, &PINL, (0x01 << 3)}

// RELAYs PINs
#define HW_RELAY_1                  (const HW_PinDef) {&DDRL, &PORTL, &PINL, (0x01 << 2)}
#define HW_RELAY_2                  (const HW_PinDef) {&DDRL, &PORTL, &PINL, (0x01 << 1)}

// BUZZERs PINs
#define HW_BUZZER                   (const HW_PinDef) {&DDRL, &PORTL, &PINL, (0x01 << 0)}
#define HW_BUZZER_PIN               49
// 7-SEGMENTs PINs
#define HW_7SEGMENT_BIT0            (const HW_PinDef) {&DDRE, &PORTE, &PINE, (0x01 << 4)}
#define HW_7SEGMENT_BIT1            (const HW_PinDef) {&DDRE, &PORTE, &PINE, (0x01 << 5)}
#define HW_7SEGMENT_BIT2            (const HW_PinDef) {&DDRG, &PORTG, &PING, (0x01 << 5)}
#define HW_7SEGMENT_BIT3            (const HW_PinDef) {&DDRE, &PORTE, &PINE, (0x01 << 3)}

#define HW_7SEGMENT_SEL1            (const HW_PinDef) {&DDRH, &PORTH, &PINH, (0x01 << 6)}
#define HW_7SEGMENT_SEL2            (const HW_PinDef) {&DDRH, &PORTH, &PINH, (0x01 << 5)}
#define HW_7SEGMENT_SEL3            (const HW_PinDef) {&DDRH, &PORTH, &PINH, (0x01 << 4)}
#define HW_7SEGMENT_SEL4            (const HW_PinDef) {&DDRH, &PORTH, &PINH, (0x01 << 3)}

// LCD PINs
#define HW_LCD_BL                   (const HW_PinDef) {&DDRB, &PORTB, &PINB, (0x01 << 0)}
#define HW_LCD_RS                   (const HW_PinDef) {&DDRG, &PORTG, &PING, (0x01 << 0)}
#define HW_LCD_EN                   (const HW_PinDef) {&DDRG, &PORTG, &PING, (0x01 << 1)}
#define HW_LCD_D0                   (const HW_PinDef) {&DDRA, &PORTA, &PINA, (0x01 << 0)}
#define HW_LCD_D1                   (const HW_PinDef) {&DDRA, &PORTA, &PINA, (0x01 << 1)}
#define HW_LCD_D2                   (const HW_PinDef) {&DDRA, &PORTA, &PINA, (0x01 << 2)}
#define HW_LCD_D3                   (const HW_PinDef) {&DDRA, &PORTA, &PINA, (0x01 << 3)}
#define HW_LCD_D4                   (const HW_PinDef) {&DDRA, &PORTA, &PINA, (0x01 << 4)}
#define HW_LCD_D5                   (const HW_PinDef) {&DDRA, &PORTA, &PINA, (0x01 << 5)}
#define HW_LCD_D6                   (const HW_PinDef) {&DDRA, &PORTA, &PINA, (0x01 << 6)}
#define HW_LCD_D7                   (const HW_PinDef) {&DDRA, &PORTA, &PINA, (0x01 << 7)}
#define HW_LCD_CS1                  (const HW_PinDef) {&DDRG, &PORTG, &PING, (0x01 << 2)}
#define HW_LCD_CS2                  (const HW_PinDef) {&DDRD, &PORTD, &PIND, (0x01 << 7)}

// KEYPADs PINs
#define HW_KEYPAD_ROW1              (const HW_PinDef) {&DDRC, &PORTC, &PINC, (0x01 << 0)}
#define HW_KEYPAD_ROW2              (const HW_PinDef) {&DDRC, &PORTC, &PINC, (0x01 << 1)}
#define HW_KEYPAD_ROW3              (const HW_PinDef) {&DDRC, &PORTC, &PINC, (0x01 << 2)}
#define HW_KEYPAD_ROW4              (const HW_PinDef) {&DDRC, &PORTC, &PINC, (0x01 << 3)}
#define HW_KEYPAD_COL1              (const HW_PinDef) {&DDRC, &PORTC, &PINC, (0x01 << 4)}
#define HW_KEYPAD_COL2              (const HW_PinDef) {&DDRC, &PORTC, &PINC, (0x01 << 5)}
#define HW_KEYPAD_COL3              (const HW_PinDef) {&DDRC, &PORTC, &PINC, (0x01 << 6)}
#define HW_KEYPAD_COL4              (const HW_PinDef) {&DDRC, &PORTC, &PINC, (0x01 << 7)}

// RS232s PINs
#define HW_RS232_TX                 (const HW_PinDef) {&DDRJ, &PORTJ, &PINJ, (0x01 << 1)}
#define HW_RS232_RX                 (const HW_PinDef) {&DDRJ, &PORTJ, &PINJ, (0x01 << 0)}

// TEMPERATURE SENSORs PINs
#define HW_TEMPERATURE_SENSOR       (const HW_PinDef) {&DDRF, &PORTF, &PINF, (0x01 << 0)}

// VARIABLE RESISTORs PINs
#define HW_VARIABLE_RESISTOR        (const HW_PinDef) {&DDRF, &PORTF, &PINF, (0x01 << 1)}

// RTC Info
#define HW_RTC_ADDRESS              0x68 // 1101000 (W/R)

// EEPROM Info
#define HW_EEPROM_ADDRESS           0x50

// BLUETOOTH Info
#define HW_BLUETOOTH_KEY            (const HW_PinDef) {&DDRK, &PORTK, &PINK, (0x01 << 3)}
#define HW_BLUETOOTH_STATE          (const HW_PinDef) {&DDRK, &PORTK, &PINK, (0x01 << 2)}
//#define HW_BLUETOOTH_TX             18
//#define HW_BLUETOOTH_RX             19
#define HW_BLUETOOTH_SERIAL         Serial1

// ULTRA-SONIC Info
#define HW_ULTRASONIC_ECHO          A7
#define HW_ULTRASONIC_TRIG          A6

// #############################################################################
// #### Public Type(s) #########################################################
// #############################################################################

typedef struct __attribute__((packed, aligned(1))) HW_PinDef
{
    volatile uint8_t * DDR;
    volatile uint8_t * PORT;
    volatile uint8_t * PIN;
    uint8_t            MASK;
} HW_PinDef;

// #############################################################################
// #### Public Method(s) #######################################################
// #############################################################################

/*
 * @brief Configures a pin as output
 *
 * @param[in] HW_Pin   : selected Pin @HW_PinDef
 *
 * @return void
 */
void    HW_PIN_OUTPUT      (HW_PinDef HW_Pin);

/*
 * @brief Configures a pin as input
 *
 * @param[in] HW_Pin   : selected Pin @HW_PinDef
 *
 * @return void
 */
void    HW_PIN_INPUT       (HW_PinDef HW_Pin);

/*
 * @brief Configures a pin as tri-state (high impedance)
 *
 * @param[in] HW_Pin   : selected Pin @HW_PinDef
 *
 * @return void
 */
void    HW_PIN_TRI_STATE   (HW_PinDef HW_Pin);

/*
 * @brief Sets a pin value logic high
 *
 * @param[in] HW_Pin   : selected Pin @HW_PinDef
 *
 * @return void
 */
void    HW_PIN_SET         (HW_PinDef HW_Pin);

/*
 * @brief Sets a pin value logic low
 *
 * @param[in] HW_Pin   : selected Pin @HW_PinDef
 *
 * @return void
 */
void    HW_PIN_CLEAR       (HW_PinDef HW_Pin);

/*
 * @brief Reads a pin value
 *
 * @param[in] HW_Pin   : selected Pin @HW_PinDef
 *
 * @return HIGH : on logic high
 * @return LOW  : on logic low
 */
uint8_t HW_PIN_READ        (HW_PinDef HW_Pin);

// #############################################################################
// #### Public Variable(s) #####################################################
// #############################################################################

// #############################################################################
// #### File Guard #############################################################
// #############################################################################

#endif /* FARESPCB_H_ */

// #############################################################################
// #### END OF FILE ############################################################
// #############################################################################

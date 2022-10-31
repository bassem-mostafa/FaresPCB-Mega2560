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

#ifndef BUZZER_H_
#define BUZZER_H_

// #############################################################################
// #### Include(s) #############################################################
// #############################################################################

#include "stdint.h"

// #############################################################################
// #### Public Macro(s) ########################################################
// #############################################################################

// #############################################################################
// #### Public Type(s) #########################################################
// #############################################################################

typedef enum __attribute__((packed, aligned(1))) Buzzer_Note_t
{
    Buzzer_Note_C0  = (int)  16.35,
    Buzzer_Note_C0S = (int)  17.32,
    Buzzer_Note_D0  = (int)  18.35,
    Buzzer_Note_D0S = (int)  19.45,
    Buzzer_Note_E0  = (int)  20.60,
    Buzzer_Note_F0  = (int)  21.83,
    Buzzer_Note_F0S = (int)  23.12,
    Buzzer_Note_G0  = (int)  24.50,
    Buzzer_Note_G0S = (int)  25.96,
    Buzzer_Note_A0  = (int)  27.50,
    Buzzer_Note_A0S = (int)  29.14,
    Buzzer_Note_B0  = (int)  30.87,
    Buzzer_Note_C1  = (int)  32.70,
    Buzzer_Note_C1S = (int)  34.65,
    Buzzer_Note_D1  = (int)  36.71,
    Buzzer_Note_D1S = (int)  38.89,
    Buzzer_Note_E1  = (int)  41.20,
    Buzzer_Note_F1  = (int)  43.65,
    Buzzer_Note_F1S = (int)  46.25,
    Buzzer_Note_G1  = (int)  49.00,
    Buzzer_Note_G1S = (int)  51.91,
    Buzzer_Note_A1  = (int)  55.00,
    Buzzer_Note_A1S = (int)  58.27,
    Buzzer_Note_B1  = (int)  61.74,
    Buzzer_Note_C2  = (int)  65.41,
    Buzzer_Note_C2S = (int)  69.30,
    Buzzer_Note_D2  = (int)  73.42,
    Buzzer_Note_D2S = (int)  77.78,
    Buzzer_Note_E2  = (int)  82.41,
    Buzzer_Note_F2  = (int)  87.31,
    Buzzer_Note_F2S = (int)  92.50,
    Buzzer_Note_G2  = (int)  98.00,
    Buzzer_Note_G2S = (int) 103.83,
    Buzzer_Note_A2  = (int) 110.00,
    Buzzer_Note_A2S = (int) 116.54,
    Buzzer_Note_B2  = (int) 123.47,
    Buzzer_Note_C3  = (int) 130.81,
    Buzzer_Note_C3S = (int) 138.59,
    Buzzer_Note_D3  = (int) 146.83,
    Buzzer_Note_D3S = (int) 155.56,
    Buzzer_Note_E3  = (int) 164.81,
    Buzzer_Note_F3  = (int) 174.61,
    Buzzer_Note_F3S = (int) 185.00,
    Buzzer_Note_G3  = (int) 196.00,
    Buzzer_Note_G3S = (int) 207.65,
    Buzzer_Note_A3  = (int) 220.00,
    Buzzer_Note_A3S = (int) 233.08,
    Buzzer_Note_B3  = (int) 246.94,
    Buzzer_Note_C4  = (int) 261.63,
    Buzzer_Note_C4S = (int) 277.18,
    Buzzer_Note_D4  = (int) 293.66,
    Buzzer_Note_D4S = (int) 311.13,
    Buzzer_Note_E4  = (int) 329.63,
    Buzzer_Note_F4  = (int) 349.23,
    Buzzer_Note_F4S = (int) 369.99,
    Buzzer_Note_G4  = (int) 392.00,
    Buzzer_Note_G4S = (int) 415.30,
    Buzzer_Note_A4  = (int) 440.00,
    Buzzer_Note_A4S = (int) 466.16,
    Buzzer_Note_B4  = (int) 493.88,
    Buzzer_Note_C5  = (int) 523.25,
    Buzzer_Note_C5S = (int) 554.37,
    Buzzer_Note_D5  = (int) 587.33,
    Buzzer_Note_D5S = (int) 622.25,
    Buzzer_Note_E5  = (int) 659.25,
    Buzzer_Note_F5  = (int) 698.46,
    Buzzer_Note_F5S = (int) 739.99,
    Buzzer_Note_G5  = (int) 783.99,
    Buzzer_Note_G5S = (int) 830.61,
    Buzzer_Note_A5  = (int) 880.00,
    Buzzer_Note_A5S = (int) 932.33,
    Buzzer_Note_B5  = (int) 987.77,
    Buzzer_Note_C6  = (int)1046.50,
    Buzzer_Note_C6S = (int)1108.73,
    Buzzer_Note_D6  = (int)1174.66,
    Buzzer_Note_D6S = (int)1244.51,
    Buzzer_Note_E6  = (int)1318.51,
    Buzzer_Note_F6  = (int)1396.91,
    Buzzer_Note_F6S = (int)1479.98,
    Buzzer_Note_G6  = (int)1567.98,
    Buzzer_Note_G6S = (int)1661.22,
    Buzzer_Note_A6  = (int)1760.00,
    Buzzer_Note_A6S = (int)1864.66,
    Buzzer_Note_B6  = (int)1975.53,
    Buzzer_Note_C7  = (int)2093.00,
    Buzzer_Note_C7S = (int)2217.46,
    Buzzer_Note_D7  = (int)2349.32,
    Buzzer_Note_D7S = (int)2489.02,
    Buzzer_Note_E7  = (int)2637.02,
    Buzzer_Note_F7  = (int)2793.83,
    Buzzer_Note_F7S = (int)2959.96,
    Buzzer_Note_G7  = (int)3135.96,
    Buzzer_Note_G7S = (int)3322.44,
    Buzzer_Note_A7  = (int)3520.00,
    Buzzer_Note_A7S = (int)3729.31,
    Buzzer_Note_B7  = (int)3951.07,
    Buzzer_Note_C8  = (int)4186.01,
    Buzzer_Note_C8S = (int)4434.92,
    Buzzer_Note_D8  = (int)4698.63,
    Buzzer_Note_D8S = (int)4978.03,
    Buzzer_Note_E8  = (int)5274.04,
    Buzzer_Note_F8  = (int)5587.65,
    Buzzer_Note_F8S = (int)5919.91,
    Buzzer_Note_G8  = (int)6271.93,
    Buzzer_Note_G8S = (int)6644.88,
    Buzzer_Note_A8  = (int)7040.00,
    Buzzer_Note_A8S = (int)7458.62,
    Buzzer_Note_B8  = (int)7902.13,
} Buzzer_Note_t;

typedef uint32_t Buzzer_Note_Duration_t;

// #############################################################################
// #### Public Method(s) #######################################################
// #############################################################################

/*
 * @brief Turns on Buzzer on specific frequency
 *
 * @param[in] Buzzer_Note             : selected Note
 * @param[in] Buzzer_Note_Duration    : Note duration in milli-seconds
 *
 * @return void     : None
 */
void Buzzer_TurnOn( Buzzer_Note_t Buzzer_Note, Buzzer_Note_Duration_t Buzzer_Note_Duration );

/*
 * @brief Turns off Buzzer
 *
 * @param[in] void   : None
 *
 * @return void     : None
 */
void Buzzer_TurnOff( void );

// #############################################################################
// #### Public Variable(s) #####################################################
// #############################################################################

// #############################################################################
// #### File Guard #############################################################
// #############################################################################

#endif /* BUZZER_H_ */

// #############################################################################
// #### END OF FILE ############################################################
// #############################################################################

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

#ifndef LED_H_
#define LED_H_

// #############################################################################
// #### Include(s) #############################################################
// #############################################################################

// #############################################################################
// #### Public Macro(s) ########################################################
// #############################################################################

// #############################################################################
// #### Public Type(s) #########################################################
// #############################################################################

typedef enum __attribute__((packed, aligned(1))) LED_Status_t
{
    LED_Status_Success = 0,
    LED_Status_Error,
} LED_Status_t;

typedef enum __attribute__((packed, aligned(1))) LED_t
{
    LED_Internal = 0,
    LED_1,
    LED_2,
    LED_3,
    LED_4,
    LED_5,
    LED_RGB,
} LED_t;

typedef enum __attribute__((packed, aligned(1))) LED_Intensity_t
{
    LED_Intensity_Zero = 0,
    LED_Intensity_Full,
    LED_Intensity_Red,
    LED_Intensity_Green,
    LED_Intensity_Blue,
    // TODO Support Other Intensities
} LED_Intensity_t;

// #############################################################################
// #### Public Method(s) #######################################################
// #############################################################################

/*
 * @brief Sets Intensity of a LED
 *
 * @param[in] LED           : selected LED      @Ref LED_t
 * @param[in] LED_Intensity : Intensity value   @Ref LED_Intensity_t
 *
 * @return LED_Status_t : LED_Status_t
 */
LED_Status_t LED_IntensitySet
(
        LED_t LED,
        LED_Intensity_t LED_Intensity
);

// #############################################################################
// #### Public Variable(s) #####################################################
// #############################################################################

// #############################################################################
// #### File Guard #############################################################
// #############################################################################

#endif /* LED_H_ */

// #############################################################################
// #### END OF FILE ############################################################
// #############################################################################

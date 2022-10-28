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

#include "Platform.h"
#include "Segment.h"
#include "util/delay.h"

// #############################################################################
// #### Private Macro(s) #######################################################
// #############################################################################

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

bool _Segment_Initialize
(
        void
)
{
    bool isInitialized = false;
    do
    {
        if (isInitialized) break;
        Platform_Pin_Setting_t Platform_Pin_Setting = NULL;

        Platform_Pin_Setting_Initialize(&Platform_Pin_Setting);
        Platform_Pin_Setting_Mode_Set(Platform_Pin_Setting, Platform_Pin_Mode_OUTPUT);
        Platform_Pin_Setup(Platform_Pin_7SEGMENT_SEL1, Platform_Pin_Setting);

        Platform_Pin_Setting_Initialize(&Platform_Pin_Setting);
        Platform_Pin_Setting_Mode_Set(Platform_Pin_Setting, Platform_Pin_Mode_OUTPUT);
        Platform_Pin_Setup(Platform_Pin_7SEGMENT_SEL2, Platform_Pin_Setting);

        Platform_Pin_Setting_Initialize(&Platform_Pin_Setting);
        Platform_Pin_Setting_Mode_Set(Platform_Pin_Setting, Platform_Pin_Mode_OUTPUT);
        Platform_Pin_Setup(Platform_Pin_7SEGMENT_SEL3, Platform_Pin_Setting);

        Platform_Pin_Setting_Initialize(&Platform_Pin_Setting);
        Platform_Pin_Setting_Mode_Set(Platform_Pin_Setting, Platform_Pin_Mode_OUTPUT);
        Platform_Pin_Setup(Platform_Pin_7SEGMENT_SEL4, Platform_Pin_Setting);

        Platform_Pin_Setting_Initialize(&Platform_Pin_Setting);
        Platform_Pin_Setting_Mode_Set(Platform_Pin_Setting, Platform_Pin_Mode_OUTPUT);
        Platform_Pin_Setup(Platform_Pin_7SEGMENT_BIT0, Platform_Pin_Setting);

        Platform_Pin_Setting_Initialize(&Platform_Pin_Setting);
        Platform_Pin_Setting_Mode_Set(Platform_Pin_Setting, Platform_Pin_Mode_OUTPUT);
        Platform_Pin_Setup(Platform_Pin_7SEGMENT_BIT1, Platform_Pin_Setting);

        Platform_Pin_Setting_Initialize(&Platform_Pin_Setting);
        Platform_Pin_Setting_Mode_Set(Platform_Pin_Setting, Platform_Pin_Mode_OUTPUT);
        Platform_Pin_Setup(Platform_Pin_7SEGMENT_BIT2, Platform_Pin_Setting);

        Platform_Pin_Setting_Initialize(&Platform_Pin_Setting);
        Platform_Pin_Setting_Mode_Set(Platform_Pin_Setting, Platform_Pin_Mode_OUTPUT);
        Platform_Pin_Setup(Platform_Pin_7SEGMENT_BIT3, Platform_Pin_Setting);
        isInitialized = true;
    }
    while(0);
    return isInitialized;
}

// #############################################################################
// #### Public Method(s) #######################################################
// #############################################################################

/*
 * @brief Clears ALL 7-Segments
 *
 * @param[in] void   : None
 *
 * @return void     : None
 */
void Segment_Clear( void )
{
    _Segment_Initialize();
    Platform_Pin_Write(Platform_Pin_7SEGMENT_SEL1, Platform_Pin_Value_HIGH);
    Platform_Pin_Write(Platform_Pin_7SEGMENT_SEL2, Platform_Pin_Value_HIGH);
    Platform_Pin_Write(Platform_Pin_7SEGMENT_SEL3, Platform_Pin_Value_HIGH);
    Platform_Pin_Write(Platform_Pin_7SEGMENT_SEL4, Platform_Pin_Value_HIGH);
}

/*
 * @brief Writes to a 7-Segment
 *
 * @param[in] Segment   : selected 7-Segment
 * @param[in] Digit     : digit to be written
 *
 * @return void     : None
 */
void Segment_Write( Segment_t Segment, Digit_t Digit )
{
    _Segment_Initialize();
    switch (Segment)
    {
        case Segment_1:
        case Segment_2:
        case Segment_3:
        case Segment_4:
            Platform_Pin_Write(Platform_Pin_7SEGMENT_BIT0, ( Digit & (0x01 << 0) ) ? Platform_Pin_Value_HIGH : Platform_Pin_Value_LOW);
            Platform_Pin_Write(Platform_Pin_7SEGMENT_BIT1, ( Digit & (0x01 << 1) ) ? Platform_Pin_Value_HIGH : Platform_Pin_Value_LOW);
            Platform_Pin_Write(Platform_Pin_7SEGMENT_BIT2, ( Digit & (0x01 << 2) ) ? Platform_Pin_Value_HIGH : Platform_Pin_Value_LOW);
            Platform_Pin_Write(Platform_Pin_7SEGMENT_BIT3, ( Digit & (0x01 << 3) ) ? Platform_Pin_Value_HIGH : Platform_Pin_Value_LOW);
            break;
        default:
            Platform_Pin_Write(Platform_Pin_7SEGMENT_BIT0, Platform_Pin_Value_LOW);
            Platform_Pin_Write(Platform_Pin_7SEGMENT_BIT1, Platform_Pin_Value_LOW);
            Platform_Pin_Write(Platform_Pin_7SEGMENT_BIT2, Platform_Pin_Value_LOW);
            Platform_Pin_Write(Platform_Pin_7SEGMENT_BIT3, Platform_Pin_Value_LOW);
            break;
    }
    switch (Segment)
    {
        case Segment_1:
            Platform_Pin_Write(Platform_Pin_7SEGMENT_SEL1, Platform_Pin_Value_LOW);
            Platform_Pin_Write(Platform_Pin_7SEGMENT_SEL2, Platform_Pin_Value_HIGH);
            Platform_Pin_Write(Platform_Pin_7SEGMENT_SEL3, Platform_Pin_Value_HIGH);
            Platform_Pin_Write(Platform_Pin_7SEGMENT_SEL4, Platform_Pin_Value_HIGH);
            break;
        case Segment_2:
            Platform_Pin_Write(Platform_Pin_7SEGMENT_SEL1, Platform_Pin_Value_HIGH);
            Platform_Pin_Write(Platform_Pin_7SEGMENT_SEL2, Platform_Pin_Value_LOW);
            Platform_Pin_Write(Platform_Pin_7SEGMENT_SEL3, Platform_Pin_Value_HIGH);
            Platform_Pin_Write(Platform_Pin_7SEGMENT_SEL4, Platform_Pin_Value_HIGH);
            break;
        case Segment_3:
            Platform_Pin_Write(Platform_Pin_7SEGMENT_SEL1, Platform_Pin_Value_HIGH);
            Platform_Pin_Write(Platform_Pin_7SEGMENT_SEL2, Platform_Pin_Value_HIGH);
            Platform_Pin_Write(Platform_Pin_7SEGMENT_SEL3, Platform_Pin_Value_LOW);
            Platform_Pin_Write(Platform_Pin_7SEGMENT_SEL4, Platform_Pin_Value_HIGH);
            break;
        case Segment_4:
            Platform_Pin_Write(Platform_Pin_7SEGMENT_SEL1, Platform_Pin_Value_HIGH);
            Platform_Pin_Write(Platform_Pin_7SEGMENT_SEL2, Platform_Pin_Value_HIGH);
            Platform_Pin_Write(Platform_Pin_7SEGMENT_SEL3, Platform_Pin_Value_HIGH);
            Platform_Pin_Write(Platform_Pin_7SEGMENT_SEL4, Platform_Pin_Value_LOW);
            break;
        default:
            Platform_Pin_Write(Platform_Pin_7SEGMENT_SEL1, Platform_Pin_Value_HIGH);
            Platform_Pin_Write(Platform_Pin_7SEGMENT_SEL2, Platform_Pin_Value_HIGH);
            Platform_Pin_Write(Platform_Pin_7SEGMENT_SEL3, Platform_Pin_Value_HIGH);
            Platform_Pin_Write(Platform_Pin_7SEGMENT_SEL4, Platform_Pin_Value_HIGH);
            break;
    }
    _delay_ms(5);
}

// #############################################################################
// #### Public Variable(s) #####################################################
// #############################################################################

// #############################################################################
// #### END OF FILE ############################################################
// #############################################################################

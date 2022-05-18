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
#include "Segment.h"

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
    HW_PIN_TRI_STATE(HW_7SEGMENT_SEL1);
    HW_PIN_TRI_STATE(HW_7SEGMENT_SEL2);
    HW_PIN_TRI_STATE(HW_7SEGMENT_SEL3);
    HW_PIN_TRI_STATE(HW_7SEGMENT_SEL4);
    HW_PIN_TRI_STATE(HW_7SEGMENT_BIT0);
    HW_PIN_TRI_STATE(HW_7SEGMENT_BIT1);
    HW_PIN_TRI_STATE(HW_7SEGMENT_BIT2);
    HW_PIN_TRI_STATE(HW_7SEGMENT_BIT3);
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
    switch (Segment)
    {
        case Segment_1:
        case Segment_2:
        case Segment_3:
        case Segment_4:
            HW_PIN_OUTPUT(HW_7SEGMENT_BIT0);
            HW_PIN_OUTPUT(HW_7SEGMENT_BIT1);
            HW_PIN_OUTPUT(HW_7SEGMENT_BIT2);
            HW_PIN_OUTPUT(HW_7SEGMENT_BIT3);
            ( Digit & (0x01 << 0) ) ? HW_PIN_SET(HW_7SEGMENT_BIT0) : HW_PIN_CLEAR(HW_7SEGMENT_BIT0) ;
            ( Digit & (0x01 << 1) ) ? HW_PIN_SET(HW_7SEGMENT_BIT1) : HW_PIN_CLEAR(HW_7SEGMENT_BIT1) ;
            ( Digit & (0x01 << 2) ) ? HW_PIN_SET(HW_7SEGMENT_BIT2) : HW_PIN_CLEAR(HW_7SEGMENT_BIT2) ;
            ( Digit & (0x01 << 3) ) ? HW_PIN_SET(HW_7SEGMENT_BIT3) : HW_PIN_CLEAR(HW_7SEGMENT_BIT3) ;
            break;
        default:
            HW_PIN_TRI_STATE(HW_7SEGMENT_BIT0);
            HW_PIN_TRI_STATE(HW_7SEGMENT_BIT1);
            HW_PIN_TRI_STATE(HW_7SEGMENT_BIT2);
            HW_PIN_TRI_STATE(HW_7SEGMENT_BIT3);
            break;
    }
    switch (Segment)
    {
        case Segment_1:
            HW_PIN_OUTPUT(HW_7SEGMENT_SEL1);
            HW_PIN_OUTPUT(HW_7SEGMENT_SEL2);
            HW_PIN_OUTPUT(HW_7SEGMENT_SEL3);
            HW_PIN_OUTPUT(HW_7SEGMENT_SEL4);
            HW_PIN_CLEAR(HW_7SEGMENT_SEL1);
            HW_PIN_SET(HW_7SEGMENT_SEL2);
            HW_PIN_SET(HW_7SEGMENT_SEL3);
            HW_PIN_SET(HW_7SEGMENT_SEL4);
            break;
        case Segment_2:
            HW_PIN_OUTPUT(HW_7SEGMENT_SEL1);
            HW_PIN_OUTPUT(HW_7SEGMENT_SEL2);
            HW_PIN_OUTPUT(HW_7SEGMENT_SEL3);
            HW_PIN_OUTPUT(HW_7SEGMENT_SEL4);
            HW_PIN_SET(HW_7SEGMENT_SEL1);
            HW_PIN_CLEAR(HW_7SEGMENT_SEL2);
            HW_PIN_SET(HW_7SEGMENT_SEL3);
            HW_PIN_SET(HW_7SEGMENT_SEL4);
            break;
        case Segment_3:
            HW_PIN_OUTPUT(HW_7SEGMENT_SEL1);
            HW_PIN_OUTPUT(HW_7SEGMENT_SEL2);
            HW_PIN_OUTPUT(HW_7SEGMENT_SEL3);
            HW_PIN_OUTPUT(HW_7SEGMENT_SEL4);
            HW_PIN_SET(HW_7SEGMENT_SEL1);
            HW_PIN_SET(HW_7SEGMENT_SEL2);
            HW_PIN_CLEAR(HW_7SEGMENT_SEL3);
            HW_PIN_SET(HW_7SEGMENT_SEL4);
            break;
        case Segment_4:
            HW_PIN_OUTPUT(HW_7SEGMENT_SEL1);
            HW_PIN_OUTPUT(HW_7SEGMENT_SEL2);
            HW_PIN_OUTPUT(HW_7SEGMENT_SEL3);
            HW_PIN_OUTPUT(HW_7SEGMENT_SEL4);
            HW_PIN_SET(HW_7SEGMENT_SEL1);
            HW_PIN_SET(HW_7SEGMENT_SEL2);
            HW_PIN_SET(HW_7SEGMENT_SEL3);
            HW_PIN_CLEAR(HW_7SEGMENT_SEL4);
            break;
        default:
            HW_PIN_TRI_STATE(HW_7SEGMENT_SEL1);
            HW_PIN_TRI_STATE(HW_7SEGMENT_SEL2);
            HW_PIN_TRI_STATE(HW_7SEGMENT_SEL3);
            HW_PIN_TRI_STATE(HW_7SEGMENT_SEL4);
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

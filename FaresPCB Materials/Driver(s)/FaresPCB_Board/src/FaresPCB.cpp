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

// #############################################################################
// #### Private Macro(s) #######################################################
// #############################################################################

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
 * @brief Configures a pin as output
 *
 * @param[in] HW_Pin   : selected Pin @HW_PinDef
 *
 * @return void
 */
void HW_PIN_OUTPUT(HW_PinDef HW_Pin)
{
    *(HW_Pin.DDR) |= (HW_Pin.MASK);
}

/*
 * @brief Configures a pin as input
 *
 * @param[in] HW_Pin   : selected Pin @HW_PinDef
 *
 * @return void
 */
void HW_PIN_INPUT(HW_PinDef HW_Pin)
{
    *(HW_Pin.DDR) &= ~(HW_Pin.MASK);
}

/*
 * @brief Configures a pin as tri-state (high impedance)
 *
 * @param[in] HW_Pin   : selected Pin @HW_PinDef
 *
 * @return void
 */
void HW_PIN_TRI_STATE(HW_PinDef HW_Pin)
{
    HW_PIN_OUTPUT(HW_Pin);
    HW_PIN_CLEAR(HW_Pin);
    HW_PIN_INPUT(HW_Pin); // TRI-STATE Active
}

/*
 * @brief Sets a pin value logic high
 *
 * @param[in] HW_Pin   : selected Pin @HW_PinDef
 *
 * @return void
 */
void HW_PIN_SET(HW_PinDef HW_Pin)
{
    *(HW_Pin.PORT) |= (HW_Pin.MASK);
}

/*
 * @brief Sets a pin value logic low
 *
 * @param[in] HW_Pin   : selected Pin @HW_PinDef
 *
 * @return void
 */
void HW_PIN_CLEAR(HW_PinDef HW_Pin)
{
    *(HW_Pin.PORT) &= ~(HW_Pin.MASK);
}

/*
 * @brief Reads a pin value
 *
 * @param[in] HW_Pin   : selected Pin @HW_PinDef
 *
 * @return HIGH : on logic high
 * @return LOW  : on logic low
 */
uint8_t HW_PIN_READ(HW_PinDef HW_Pin)
{
    return ( ( *(HW_Pin.PIN) & (HW_Pin.MASK) ) ? HIGH : LOW );
}

// #############################################################################
// #### Public Variable(s) #####################################################
// #############################################################################

// #############################################################################
// #### END OF FILE ############################################################
// #############################################################################
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

// #############################################################################
// #### Include(s) #############################################################
// #############################################################################

#include "Keypad.h"
#include "Platform.h"

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

bool _Keypad_Initiliaze()
{
    static bool isInitialized = false;
    do
    {
        if (isInitialized) break;
        Platform_Pin_Setting_t Platform_Pin_Setting = NULL;
        Platform_Pin_Setting_Initialize(&Platform_Pin_Setting);
        Platform_Pin_Setting_Mode_Set(Platform_Pin_Setting, Platform_Pin_Mode_OUTPUT);
        Platform_Pin_Setup(Platform_Pin_KEYPAD_ROW1, Platform_Pin_Setting);
        Platform_Pin_Setting_Initialize(&Platform_Pin_Setting);
        Platform_Pin_Setting_Mode_Set(Platform_Pin_Setting, Platform_Pin_Mode_OUTPUT);
        Platform_Pin_Setup(Platform_Pin_KEYPAD_ROW2, Platform_Pin_Setting);
        Platform_Pin_Setting_Initialize(&Platform_Pin_Setting);
        Platform_Pin_Setting_Mode_Set(Platform_Pin_Setting, Platform_Pin_Mode_OUTPUT);
        Platform_Pin_Setup(Platform_Pin_KEYPAD_ROW3, Platform_Pin_Setting);
        Platform_Pin_Setting_Initialize(&Platform_Pin_Setting);
        Platform_Pin_Setting_Mode_Set(Platform_Pin_Setting, Platform_Pin_Mode_OUTPUT);
        Platform_Pin_Setup(Platform_Pin_KEYPAD_ROW4, Platform_Pin_Setting);
        Platform_Pin_Setting_Initialize(&Platform_Pin_Setting);
        Platform_Pin_Setting_Mode_Set(Platform_Pin_Setting, Platform_Pin_Mode_INPUT);
        Platform_Pin_Setup(Platform_Pin_KEYPAD_COL1, Platform_Pin_Setting);
        Platform_Pin_Setting_Initialize(&Platform_Pin_Setting);
        Platform_Pin_Setting_Mode_Set(Platform_Pin_Setting, Platform_Pin_Mode_INPUT);
        Platform_Pin_Setup(Platform_Pin_KEYPAD_COL2, Platform_Pin_Setting);
        Platform_Pin_Setting_Initialize(&Platform_Pin_Setting);
        Platform_Pin_Setting_Mode_Set(Platform_Pin_Setting, Platform_Pin_Mode_INPUT);
        Platform_Pin_Setup(Platform_Pin_KEYPAD_COL3, Platform_Pin_Setting);
        Platform_Pin_Setting_Initialize(&Platform_Pin_Setting);
        Platform_Pin_Setting_Mode_Set(Platform_Pin_Setting, Platform_Pin_Mode_INPUT);
        Platform_Pin_Setup(Platform_Pin_KEYPAD_COL4, Platform_Pin_Setting);

        Platform_Pin_Write(Platform_Pin_KEYPAD_ROW1, Platform_Pin_Value_HIGH);
        Platform_Pin_Write(Platform_Pin_KEYPAD_ROW2, Platform_Pin_Value_HIGH);
        Platform_Pin_Write(Platform_Pin_KEYPAD_ROW3, Platform_Pin_Value_HIGH);
        Platform_Pin_Write(Platform_Pin_KEYPAD_ROW4, Platform_Pin_Value_HIGH);
        isInitialized = true;
    }
    while(0);
    return isInitialized;
}

Platform_Pin_t _Keypad_Row_Pin_Get(Keypad_Key_t Keypad_Key)
{
    Platform_Pin_t Platform_Pin_KEYPAD_ROW = -1;
    switch (Keypad_Key)
    {
        case Keypad_Key_1:
        case Keypad_Key_2:
        case Keypad_Key_3:
        case Keypad_Key_4:
            Platform_Pin_KEYPAD_ROW = Platform_Pin_KEYPAD_ROW1;
            break;
        case Keypad_Key_5:
        case Keypad_Key_6:
        case Keypad_Key_7:
        case Keypad_Key_8:
            Platform_Pin_KEYPAD_ROW = Platform_Pin_KEYPAD_ROW2;
            break;
        case Keypad_Key_9:
        case Keypad_Key_10:
        case Keypad_Key_11:
        case Keypad_Key_12:
            Platform_Pin_KEYPAD_ROW = Platform_Pin_KEYPAD_ROW3;
            break;
        case Keypad_Key_13:
        case Keypad_Key_14:
        case Keypad_Key_15:
        case Keypad_Key_16:
            Platform_Pin_KEYPAD_ROW = Platform_Pin_KEYPAD_ROW4;
            break;
        default:
            Platform_Pin_KEYPAD_ROW = -1;
            break;
    }
    return Platform_Pin_KEYPAD_ROW;
}

Platform_Pin_t _Keypad_Col_Pin_Get(Keypad_Key_t Keypad_Key)
{
    Platform_Pin_t Platform_Pin_KEYPAD_COL = -1;
    switch (Keypad_Key)
    {
        case Keypad_Key_1:
        case Keypad_Key_5:
        case Keypad_Key_9:
        case Keypad_Key_13:
            Platform_Pin_KEYPAD_COL = Platform_Pin_KEYPAD_COL1;
            break;
        case Keypad_Key_2:
        case Keypad_Key_6:
        case Keypad_Key_10:
        case Keypad_Key_14:
            Platform_Pin_KEYPAD_COL = Platform_Pin_KEYPAD_COL2;
            break;
        case Keypad_Key_3:
        case Keypad_Key_7:
        case Keypad_Key_11:
        case Keypad_Key_15:
            Platform_Pin_KEYPAD_COL = Platform_Pin_KEYPAD_COL3;
            break;
        case Keypad_Key_4:
        case Keypad_Key_8:
        case Keypad_Key_12:
        case Keypad_Key_16:
            Platform_Pin_KEYPAD_COL = Platform_Pin_KEYPAD_COL4;
            break;
        default:
            Platform_Pin_KEYPAD_COL = -1;
            break;
    }
    return Platform_Pin_KEYPAD_COL;
}

// #############################################################################
// #### Public Method(s) #######################################################
// #############################################################################

Keypad_Key_State_t Keypad_Key_State_Get(Keypad_Key_t Keypad_Key)
{
    Keypad_Key_State_t Keypad_Key_State = Keypad_Key_State_Up;
    Platform_Pin_Value_t Platform_Pin_Value_COL;
    Platform_Pin_t Platform_Pin_KEYPAD_ROW = _Keypad_Row_Pin_Get(Keypad_Key);
    Platform_Pin_t Platform_Pin_KEYPAD_COL = _Keypad_Col_Pin_Get(Keypad_Key);

    _Keypad_Initiliaze();
    Platform_Pin_Write(Platform_Pin_KEYPAD_ROW, Platform_Pin_Value_LOW);
    Platform_Pin_Read(Platform_Pin_KEYPAD_COL, &Platform_Pin_Value_COL);
    Keypad_Key_State = (Platform_Pin_Value_COL == Platform_Pin_Value_LOW ? Keypad_Key_State_Down : Keypad_Key_State_Up);
    Platform_Pin_Write(Platform_Pin_KEYPAD_ROW, Platform_Pin_Value_HIGH);
    return Keypad_Key_State;
}

// #############################################################################
// #### Public Variable(s) #####################################################
// #############################################################################

// #############################################################################
// #### File Guard #############################################################
// #############################################################################

// #############################################################################
// #### END OF FILE ############################################################
// #############################################################################

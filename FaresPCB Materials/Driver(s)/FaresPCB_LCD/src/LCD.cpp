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
#include "LCD.h"

// #############################################################################
// #### Private Macro(s) #######################################################
// #############################################################################

#define POWER_ON_DELAY      50 // in milli-seconds

// #############################################################################
// #### Private Type(s) ########################################################
// #############################################################################

typedef enum __attribute__((packed, aligned(1))) LCD_Command_t
{
    LCD_Command_Clear       = 0b00000001,
    LCD_Command_Home        = 0b00000010,
    LCD_Command_Mode        = 0b00000100,
    LCD_Command_Display     = 0b00001000,
    LCD_Command_Shift       = 0b00010000,
    LCD_Command_Function    = 0b00100000,
    LCD_Command_CGRAM       = 0b01000000,
    LCD_Command_DDRAM       = 0b10000000,
} LCD_Command_t;

typedef union __attribute__((packed, aligned(1))) LCD_Clear_t
{
    const LCD_Command_t command;
} LCD_Clear_t;

typedef union __attribute__((packed, aligned(1))) LCD_Home_t
{
    const LCD_Command_t command;
} LCD_Home_t;

typedef enum __attribute__((packed, aligned(1))) LCD_Mode_Select_t
{
    LCD_Mode_Select_Cursor = 0,
    LCD_Mode_Select_Screen,
} LCD_Mode_Select_t;

typedef enum __attribute__((packed, aligned(1))) LCD_Mode_Screen_t
{
    LCD_Mode_Screen_Shift_Right = 0,
    LCD_Mode_Screen_Shift_Left,
} LCD_Mode_Screen_t;

typedef enum __attribute__((packed, aligned(1))) LCD_Mode_Cursor_t
{
    LCD_Mode_Cursor_Decrement = 0,
    LCD_Mode_Cursor_Increment,
} LCD_Mode_Cursor_t;

typedef union __attribute__((packed, aligned(1))) LCD_Mode_t
{
    const LCD_Command_t command;
    struct
    {
        LCD_Mode_Select_t select : 1;
        uint8_t : 7;
    };
    struct
    {
        uint8_t : 1;
        LCD_Mode_Screen_t screen : 1;
        uint8_t : 6;
    };
    struct
    {
        uint8_t : 1;
        LCD_Mode_Cursor_t cursor : 1;
        uint8_t : 6;
    };
} LCD_Mode_t;

typedef enum __attribute__((packed, aligned(1))) LCD_Setting_Cursor_Blink_t
{
    LCD_Setting_Cursor_Blink_Disable = 0,
    LCD_Setting_Cursor_Blink_Enable,
} LCD_Setting_Cursor_Blink_t;

typedef enum __attribute__((packed, aligned(1))) LCD_Setting_Cursor_t
{
    LCD_Setting_Cursor_Disable = 0,
    LCD_Setting_Cursor_Enable,
} LCD_Setting_Cursor_t;

typedef enum __attribute__((packed, aligned(1))) LCD_Setting_Display_t
{
    LCD_Setting_Display_Disable = 0,
    LCD_Setting_Display_Enable,
} LCD_Setting_Display_t;

typedef union __attribute__((packed, aligned(1))) LCD_Setting_t
{
    const LCD_Command_t command;
    struct
    {
        LCD_Setting_Cursor_Blink_t cursor_blink : 1;
        LCD_Setting_Cursor_t cursor : 1;
        LCD_Setting_Display_t display : 1;
    };
} LCD_Setting_t;

typedef enum __attribute__((packed, aligned(1))) LCD_Shift_Direction_t
{
    LCD_Shift_Direction_Left = 0,
    LCD_Shift_Direction_Right,
} LCD_Shift_Direction_t;

typedef enum __attribute__((packed, aligned(1))) LCD_Shift_Select_t
{
    LCD_Shift_Select_Cursor = 0,
    LCD_Shift_Select_Screen,
} LCD_Shift_Select_t;

typedef union __attribute__((packed, aligned(1))) LCD_Shift_t
{
    const LCD_Command_t command;
    struct
    {
        uint8_t : 2;
        LCD_Shift_Direction_t direction : 1;
        LCD_Shift_Select_t select : 1;
    };
} LCD_Shift_t;

typedef enum __attribute__((packed, aligned(1))) LCD_Function_Font_t
{
    LCD_Function_Font_5x8 = 0,
    LCD_Function_Font_5x11,
} LCD_Function_Font_t;

typedef enum __attribute__((packed, aligned(1))) LCD_Function_Line_t
{
    LCD_Function_Line_1_Line = 0,
    LCD_Function_Line_2_Line,
} LCD_Function_Line_t;

typedef enum __attribute__((packed, aligned(1))) LCD_Function_Interface_t
{
    LCD_Function_Interface_4bit = 0,
    LCD_Function_Interface_8bit,
} LCD_Function_Interface_t;

typedef union __attribute__((packed, aligned(1))) LCD_Function_t
{
    const LCD_Command_t command;
    struct
    {
        uint8_t : 2;
        LCD_Function_Font_t font : 1;
        LCD_Function_Line_t line : 1;
        LCD_Function_Interface_t interface: 1;
    };
} LCD_Function_t;

typedef union __attribute__((packed, aligned(1))) LCD_CGRAM_t
{
    const LCD_Command_t command;
    struct
    {
        uint8_t address : 6;
    };
} LCD_CGRAM_t;

typedef union __attribute__((packed, aligned(1))) LCD_DDRAM_t
{
    const LCD_Command_t command;
    struct
    {
        uint8_t address : 7;
    };
} LCD_DDRAM_t;

// #############################################################################
// #### Private Variable(s) ####################################################
// #############################################################################

static LCD_Clear_t    LCD_Clear    = {LCD_Command_Clear};
static LCD_Home_t     LCD_Home     = {LCD_Command_Home};
static LCD_Mode_t     LCD_Mode     = {LCD_Command_Mode};
static LCD_Setting_t  LCD_Setting  = {LCD_Command_Display};
static LCD_Shift_t    LCD_Shift    = {LCD_Command_Shift};
static LCD_Function_t LCD_Function = {LCD_Command_Function};
static LCD_CGRAM_t    LCD_CGRAM    = {LCD_Command_CGRAM};
static LCD_DDRAM_t    LCD_DDRAM    = {LCD_Command_DDRAM};

// #############################################################################
// #### Private Method(s) ######################################################
// #############################################################################

#include "Bluetooth.h"

static void send( uint8_t value, bool command=false )
{
    HW_PIN_SET(HW_LCD_EN);
    command ? HW_PIN_CLEAR(HW_LCD_RS) : HW_PIN_SET(HW_LCD_RS);

    ( value & ( 0x01 << 0) ) ? HW_PIN_SET(HW_LCD_D0) : HW_PIN_CLEAR(HW_LCD_D0);
    ( value & ( 0x01 << 1) ) ? HW_PIN_SET(HW_LCD_D1) : HW_PIN_CLEAR(HW_LCD_D1);
    ( value & ( 0x01 << 2) ) ? HW_PIN_SET(HW_LCD_D2) : HW_PIN_CLEAR(HW_LCD_D2);
    ( value & ( 0x01 << 3) ) ? HW_PIN_SET(HW_LCD_D3) : HW_PIN_CLEAR(HW_LCD_D3);
    ( value & ( 0x01 << 4) ) ? HW_PIN_SET(HW_LCD_D4) : HW_PIN_CLEAR(HW_LCD_D4);
    ( value & ( 0x01 << 5) ) ? HW_PIN_SET(HW_LCD_D5) : HW_PIN_CLEAR(HW_LCD_D5);
    ( value & ( 0x01 << 6) ) ? HW_PIN_SET(HW_LCD_D6) : HW_PIN_CLEAR(HW_LCD_D6);
    ( value & ( 0x01 << 7) ) ? HW_PIN_SET(HW_LCD_D7) : HW_PIN_CLEAR(HW_LCD_D7);

    HW_PIN_CLEAR(HW_LCD_EN);
    _delay_ms(2);
}

// #############################################################################
// #### Public Method(s) #######################################################
// #############################################################################

/*
 * @brief Initializes LCD
 *
 * @param[in] void  : None
 *
 * @return void     : None
 */
void LCD_Initialize( void )
{
    HW_PIN_OUTPUT(HW_LCD_BL);
    HW_PIN_OUTPUT(HW_LCD_RS);
    HW_PIN_OUTPUT(HW_LCD_EN);
    HW_PIN_OUTPUT(HW_LCD_D0);
    HW_PIN_OUTPUT(HW_LCD_D1);
    HW_PIN_OUTPUT(HW_LCD_D2);
    HW_PIN_OUTPUT(HW_LCD_D3);
    HW_PIN_OUTPUT(HW_LCD_D4);
    HW_PIN_OUTPUT(HW_LCD_D5);
    HW_PIN_OUTPUT(HW_LCD_D6);
    HW_PIN_OUTPUT(HW_LCD_D7);
    HW_PIN_OUTPUT(HW_LCD_CS1);
    HW_PIN_OUTPUT(HW_LCD_CS2);

    HW_PIN_CLEAR(HW_LCD_BL);
    HW_PIN_CLEAR(HW_LCD_RS);
    HW_PIN_CLEAR(HW_LCD_EN);
    HW_PIN_CLEAR(HW_LCD_D0);
    HW_PIN_CLEAR(HW_LCD_D1);
    HW_PIN_CLEAR(HW_LCD_D2);
    HW_PIN_CLEAR(HW_LCD_D3);
    HW_PIN_CLEAR(HW_LCD_D4);
    HW_PIN_CLEAR(HW_LCD_D5);
    HW_PIN_CLEAR(HW_LCD_D6);
    HW_PIN_CLEAR(HW_LCD_D7);
    HW_PIN_CLEAR(HW_LCD_CS1);
    HW_PIN_CLEAR(HW_LCD_CS2);
    _delay_ms(POWER_ON_DELAY);
    LCD_Function.font = LCD_Function_Font_5x8;
    LCD_Function.interface = LCD_Function_Interface_8bit;
    LCD_Function.line = LCD_Function_Line_2_Line;
    send(LCD_Function.command, true);
    send(LCD_Function.command, true);

    LCD_Setting.cursor = LCD_Setting_Cursor_Disable;
    LCD_Setting.cursor_blink = LCD_Setting_Cursor_Blink_Disable;
    LCD_Setting.display = LCD_Setting_Display_Enable;
    send(LCD_Setting.command, true);

    send(LCD_Clear.command, true);

    LCD_Mode.select = LCD_Mode_Select_Cursor;
    LCD_Mode.cursor = LCD_Mode_Cursor_Increment;
    send(LCD_Mode.command, true);
}

/*
 * @brief Turns LCD back-light on
 *
 * @param[in] void  : None
 *
 * @return void     : None
 */
void LCD_LightOn( void )
{
    HW_PIN_SET(HW_LCD_BL);
}

/*
 * @brief Turns LCD back-light off
 *
 * @param[in] void  : None
 *
 * @return void     : None
 */
void LCD_LightOff( void )
{
    HW_PIN_CLEAR(HW_LCD_BL);
}

/*
 * @brief Writes a text into LCD starting from selected line / character
 *
 * @param[in] LCD_Line          : line selected
 * @param[in] LCD_Character     : character selected
 * @param[in] text              : text reference
 * @param[in] length            : text length
 *
 * @return void     : None
 */
void LCD_Write( LCD_Line_t LCD_Line, LCD_Character_t LCD_Character, uint8_t * text, uint8_t length )
{
    switch (LCD_Line)
    {
        case LCD_Line_1:
            LCD_DDRAM.address = 0x00;
            break;
        case LCD_Line_2:
            LCD_DDRAM.address = 0x40;
            break;
        default:
            break;
    }
    LCD_DDRAM.address += LCD_Character;
    send(LCD_DDRAM.command, true);
    for (uint8_t i = 0; (LCD_Character <= LCD_Character_16) && (i < length); LCD_Character = LCD_Character + 1, ++i)
    {
        send(text[i]);
    }
}

/*
 * @brief Links an icon to specific custom character
 *
 * @param[in] LCD_Custom_Character  : custom character selected
 * @param[in] LCD_Icon              : icon selected
 *
 * @return void     : None
 */
void LCD_Setup( LCD_Custom_Character_t LCD_Custom_Character, LCD_Icon_t LCD_Icon )
{
    LCD_CGRAM.address = LCD_Custom_Character;
    LCD_CGRAM.address <<= 3;
    send(LCD_CGRAM.command, true);
    for (uint8_t i = 0; i < sizeof(LCD_Icon_t); ++i)
    {
        send(LCD_Icon[i]);
    }
}

/*
 * @brief Draws an icon linked to a custom character
 *
 * @param[in] LCD_Line              : line selected
 * @param[in] LCD_Character         : character selected
 * @param[in] LCD_Custom_Character  : custom character selected
 *
 * @return void     : None
 */
void LCD_Draw( LCD_Line_t LCD_Line, LCD_Character_t LCD_Character, LCD_Custom_Character_t LCD_Custom_Character )
{
    switch (LCD_Line)
    {
        case LCD_Line_1:
            LCD_DDRAM.address = 0x00;
            break;
        case LCD_Line_2:
            LCD_DDRAM.address = 0x40;
            break;
        default:
            break;
    }
    LCD_DDRAM.address += LCD_Character;
    send(LCD_DDRAM.command, true);

    send(LCD_Custom_Character);
}


// #############################################################################
// #### Public Variable(s) #####################################################
// #############################################################################

LCD_Icon_t LCD_Icon_Empty =
{
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
};
LCD_Icon_t LCD_Icon_Bluetooth =
{
        0b00000100,
        0b00010110,
        0b00001101,
        0b00000110,
        0b00001101,
        0b00010110,
        0b00000100,
        0b00000000,
};
LCD_Icon_t LCD_Icon_LockOn =
{
        0b00000000,
        0b00001110,
        0b00010001,
        0b00010001,
        0b00011111,
        0b00011111,
        0b00011111,
        0b00000000,
};
LCD_Icon_t LCD_Icon_LockOff =
{
        0b00001110,
        0b00010000,
        0b00010000,
        0b00010000,
        0b00011111,
        0b00011111,
        0b00011111,
        0b00000000,
};
LCD_Icon_t LCD_Icon_Calendar =
{
        0b00000000,
        0b00001010,
        0b00011111,
        0b00010101,
        0b00011111,
        0b00010101,
        0b00011111,
        0b00000000,
};
LCD_Icon_t LCD_Icon_Clock =
{
        0b00000000,
        0b00000000,
        0b00001110,
        0b00010101,
        0b00010111,
        0b00010001,
        0b00001110,
        0b00000000,
};
LCD_Icon_t LCD_Icon_Bell =
{
        0b00000100,
        0b00001110,
        0b00001110,
        0b00001110,
        0b00011111,
        0b00011111,
        0b00000000,
        0b00000100,
};
LCD_Icon_t LCD_Icon_Degree =
{
        0b00000000,
        0b00000110,
        0b00001001,
        0b00001001,
        0b00000110,
        0b00000000,
        0b00000000,
        0b00000000,
};
LCD_Icon_t LCD_Icon_Thermometer =
{
        0b00000100,
        0b00001010,
        0b00001010,
        0b00001110,
        0b00001110,
        0b00011111,
        0b00011111,
        0b00001110,
};
LCD_Icon_t LCD_Icon_WaterDrop =
{
        0b00000000,
        0b00000100,
        0b00001010,
        0b00010001,
        0b00010001,
        0b00010001,
        0b00001110,
        0b00000000,
};
LCD_Icon_t LCD_Icon_Bar_Loading_StartEmpty =
{
        0b00000000,
        0b00000111,
        0b00001000,
        0b00010000,
        0b00010000,
        0b00001000,
        0b00000111,
        0b00000000,
};
LCD_Icon_t LCD_Icon_Bar_Loading_StartFull =
{
        0b00000000,
        0b00000111,
        0b00001000,
        0b00010011,
        0b00010011,
        0b00001000,
        0b00000111,
        0b00000000,
};
LCD_Icon_t LCD_Icon_Bar_Loading_MiddleEmpty =
{
        0b00000000,
        0b00011111,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00011111,
        0b00000000,
};
LCD_Icon_t LCD_Icon_Bar_Loading_MiddleHalf =
{
        0b00000000,
        0b00011111,
        0b00000000,
        0b00011000,
        0b00011000,
        0b00000000,
        0b00011111,
        0b00000000,
};
LCD_Icon_t LCD_Icon_Bar_Loading_MiddleFull =
{
        0b00000000,
        0b00011111,
        0b00000000,
        0b00011011,
        0b00011011,
        0b00000000,
        0b00011111,
        0b00000000,
};
LCD_Icon_t LCD_Icon_Bar_Loading_EndEmpty =
{
        0b00000000,
        0b00011100,
        0b00000010,
        0b00000001,
        0b00000001,
        0b00000010,
        0b00011100,
        0b00000000,
};
LCD_Icon_t LCD_Icon_Bar_Loading_EndFull =
{
        0b00000000,
        0b00011100,
        0b00000010,
        0b00011001,
        0b00011001,
        0b00000010,
        0b00011100,
        0b00000000,
};
LCD_Icon_t LCD_Icon_MelodySingle =
{
        0b00000010,
        0b00000011,
        0b00000010,
        0b00000010,
        0b00000010,
        0b00001110,
        0b00011110,
        0b00001100,
};
LCD_Icon_t LCD_Icon_MelodyDual =
{
        0b00000001,
        0b00000011,
        0b00000101,
        0b00001001,
        0b00001011,
        0b00001011,
        0b00011000,
        0b00011000,
};
LCD_Icon_t LCD_Icon_MelodyPlay =
{
        0b00000000,
        0b00000000,
        0b00001100,
        0b00001110,
        0b00001111,
        0b00001110,
        0b00001100,
        0b00000000,
};
LCD_Icon_t LCD_Icon_MelodyStop =
{
        0b00000000,
        0b00000000,
        0b00001110,
        0b00011111,
        0b00011111,
        0b00001110,
        0b00000000,
        0b00000000,
};
LCD_Icon_t LCD_Icon_MelodyPause =
{
        0b00000000,
        0b00000000,
        0b00011011,
        0b00011011,
        0b00011011,
        0b00011011,
        0b00000000,
        0b00000000,
};
LCD_Icon_t LCD_Icon_MelodyNext =
{
        0b00000000,
        0b00000000,
        0b00010100,
        0b00010110,
        0b00010111,
        0b00010110,
        0b00010100,
        0b00000000,
};
LCD_Icon_t LCD_Icon_MelodyPrevious =
{
        0b00000000,
        0b00000000,
        0b00000101,
        0b00001101,
        0b00011101,
        0b00001101,
        0b00000101,
        0b00000000,
};
LCD_Icon_t LCD_Icon_Heart =
{
        0b00000000,
        0b00001010,
        0b00011111,
        0b00011111,
        0b00001110,
        0b00000100,
        0b00000000,
        0b00000000,
};
LCD_Icon_t LCD_Icon_BatteryLow =
{
        0b00000000,
        0b00001110,
        0b00010001,
        0b00010001,
        0b00010001,
        0b00010001,
        0b00011111,
        0b00011111,
};
LCD_Icon_t LCD_Icon_BatteryHalf =
{
        0b00000000,
        0b00001110,
        0b00010001,
        0b00010001,
        0b00011111,
        0b00011111,
        0b00011111,
        0b00011111,
};
LCD_Icon_t LCD_Icon_BatteryFull =
{
        0b00000000,
        0b00001110,
        0b00011111,
        0b00011111,
        0b00011111,
        0b00011111,
        0b00011111,
        0b00011111,
};
LCD_Icon_t LCD_Icon_SignalLow =
{
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00010000,
        0b00010000,
};
LCD_Icon_t LCD_Icon_SignalHalf =
{
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000100,
        0b00000100,
        0b00010100,
        0b00010100,
};
LCD_Icon_t LCD_Icon_SignalFull =
{
        0b00000000,
        0b00000000,
        0b00000001,
        0b00000001,
        0b00000101,
        0b00000101,
        0b00010101,
        0b00010101,
};

// #############################################################################
// #### END OF FILE ############################################################
// #############################################################################

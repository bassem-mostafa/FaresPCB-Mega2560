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
// #### Include(s) #############################################################
// #############################################################################

#include "LCD.h"
#include "Platform.h"
#include "util/delay.h"
#include "stddef.h"

// #############################################################################
// #### Private Macro(s) #######################################################
// #############################################################################

#define _LCD_POWER_ON_DELAY         (50) // in milli-seconds
#define _LCD_ICON_SIZE              ( 8) // in bytes

// #############################################################################
// #### Private Type(s) ########################################################
// #############################################################################

typedef enum __attribute__((packed, aligned(1))) _Command_t
{
    _Command_CLEAR       = 0b00000001,
    _Command_HOME        = 0b00000010,
    _Command_MODE        = 0b00000100,
    _Command_DISPLAY     = 0b00001000,
    _Command_SHIFT       = 0b00010000,
    _Command_FUNCTION    = 0b00100000,
    _Command_CGRAM       = 0b01000000,
    _Command_DDRAM       = 0b10000000,
} _Command_t;

typedef union __attribute__((packed, aligned(1))) _Clear_t
{
    const _Command_t _command;
} _Clear_t;

typedef union __attribute__((packed, aligned(1))) _Home_t
{
    const _Command_t _command;
} _Home_t;

typedef enum __attribute__((packed, aligned(1))) _Mode_Select_t
{
    _Mode_Select_Cursor = 0,
    _Mode_Select_Screen,
} _Mode_Select_t;

typedef enum __attribute__((packed, aligned(1))) _Mode_Screen_t
{
    _Mode_Screen_Shift_Right = 0,
    _Mode_Screen_Shift_Left,
} _Mode_Screen_t;

typedef enum __attribute__((packed, aligned(1))) _Mode_Cursor_t
{
    _Mode_Cursor_Decrement = 0,
    _Mode_Cursor_Increment,
} _Mode_Cursor_t;

typedef union __attribute__((packed, aligned(1))) _Mode_t
{
    const _Command_t _command;
    struct
    {
        _Mode_Select_t _select : 1;
        uint8_t : 7;
    };
    struct
    {
        uint8_t : 1;
        _Mode_Screen_t _screen : 1;
        uint8_t : 6;
    };
    struct
    {
        uint8_t : 1;
        _Mode_Cursor_t _cursor : 1;
        uint8_t : 6;
    };
} _Mode_t;

typedef enum __attribute__((packed, aligned(1))) _Setting_Cursor_Blink_t
{
    _Setting_Cursor_Blink_Disable = 0,
    _Setting_Cursor_Blink_Enable,
} _Setting_Cursor_Blink_t;

typedef enum __attribute__((packed, aligned(1))) _Setting_Cursor_t
{
    _Setting_Cursor_Disable = 0,
    _Setting_Cursor_Enable,
} _Setting_Cursor_t;

typedef enum __attribute__((packed, aligned(1))) _Setting_Display_t
{
    _Setting_Display_Disable = 0,
    _Setting_Display_Enable,
} _Setting_Display_t;

typedef union __attribute__((packed, aligned(1))) _Setting_t
{
    const _Command_t _command;
    struct
    {
        _Setting_Cursor_Blink_t _cursor_blink : 1;
        _Setting_Cursor_t _cursor : 1;
        _Setting_Display_t _display : 1;
    };
} _Setting_t;

typedef enum __attribute__((packed, aligned(1))) _Shift_Direction_t
{
    _Shift_Direction_Left = 0,
    _Shift_Direction_Right,
} _Shift_Direction_t;

typedef enum __attribute__((packed, aligned(1))) _Shift_Select_t
{
    _Shift_Select_Cursor = 0,
    _Shift_Select_Screen,
} _Shift_Select_t;

typedef union __attribute__((packed, aligned(1))) _Shift_t
{
    const _Command_t _command;
    struct
    {
        uint8_t : 2;
        _Shift_Direction_t _direction : 1;
        _Shift_Select_t _select : 1;
    };
} _Shift_t;

typedef enum __attribute__((packed, aligned(1))) _Function_Font_t
{
    _Function_Font_5x8 = 0,
    _Function_Font_5x11,
} _Function_Font_t;

typedef enum __attribute__((packed, aligned(1))) _Function_Line_t
{
    _Function_Line_1_Line = 0,
    _Function_Line_2_Line,
} _Function_Line_t;

typedef enum __attribute__((packed, aligned(1))) _Function_Interface_t
{
    _Function_Interface_4bit = 0,
    _Function_Interface_8bit,
} _Function_Interface_t;

typedef union __attribute__((packed, aligned(1))) _Function_t
{
    const _Command_t _command;
    struct
    {
        uint8_t : 2;
        _Function_Font_t _font : 1;
        _Function_Line_t _line : 1;
        _Function_Interface_t _interface: 1;
    };
} _Function_t;

typedef union __attribute__((packed, aligned(1))) _CGRAM_t
{
    const _Command_t _command;
    struct
    {
        uint8_t _address : 6;
    };
} _CGRAM_t;

typedef union __attribute__((packed, aligned(1))) _DDRAM_t
{
    const _Command_t _command;
    struct
    {
        uint8_t _address : 7;
    };
} _DDRAM_t;

typedef const uint8_t /*__attribute__((packed, aligned(1)))*/ _LCD_Icon_t[_LCD_ICON_SIZE];

// #############################################################################
// #### Private Method(s) Prototype ############################################
// #############################################################################

// #############################################################################
// #### Private Variable(s) ####################################################
// #############################################################################

static _Clear_t    _Clear    = {_Command_CLEAR};
static _Home_t     _Home     = {_Command_HOME};
static _Mode_t     _Mode     = {_Command_MODE};
static _Setting_t  _Setting  = {_Command_DISPLAY};
static _Shift_t    _Shift    = {_Command_SHIFT};
static _Function_t _Function = {_Command_FUNCTION};
static _CGRAM_t    _CGRAM    = {_Command_CGRAM};
static _DDRAM_t    _DDRAM    = {_Command_DDRAM};

static const _LCD_Icon_t _LCD_Icon_Empty =
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
static const _LCD_Icon_t _LCD_Icon_Bluetooth =
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
static const _LCD_Icon_t _LCD_Icon_LockOn =
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
static const _LCD_Icon_t _LCD_Icon_LockOff =
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
static const _LCD_Icon_t _LCD_Icon_Calendar =
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
static const _LCD_Icon_t _LCD_Icon_Clock =
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
static const _LCD_Icon_t _LCD_Icon_Bell =
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
static const _LCD_Icon_t _LCD_Icon_Degree =
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
static const _LCD_Icon_t _LCD_Icon_Thermometer =
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
static const _LCD_Icon_t _LCD_Icon_WaterDrop =
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
static const _LCD_Icon_t _LCD_Icon_Bar_Loading_StartEmpty =
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
static const _LCD_Icon_t _LCD_Icon_Bar_Loading_StartFull =
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
static const _LCD_Icon_t _LCD_Icon_Bar_Loading_MiddleEmpty =
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
static const _LCD_Icon_t _LCD_Icon_Bar_Loading_MiddleHalf =
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
static const _LCD_Icon_t _LCD_Icon_Bar_Loading_MiddleFull =
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
static const _LCD_Icon_t _LCD_Icon_Bar_Loading_EndEmpty =
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
static const _LCD_Icon_t _LCD_Icon_Bar_Loading_EndFull =
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
static const _LCD_Icon_t _LCD_Icon_MelodySingle =
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
static const _LCD_Icon_t _LCD_Icon_MelodyDual =
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
static const _LCD_Icon_t _LCD_Icon_MelodyPlay =
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
static const _LCD_Icon_t _LCD_Icon_MelodyStop =
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
static const _LCD_Icon_t _LCD_Icon_MelodyPause =
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
static const _LCD_Icon_t _LCD_Icon_MelodyNext =
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
static const _LCD_Icon_t _LCD_Icon_MelodyPrevious =
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
static const _LCD_Icon_t _LCD_Icon_Heart =
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
static const _LCD_Icon_t _LCD_Icon_BatteryLow =
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
static const _LCD_Icon_t _LCD_Icon_BatteryHalf =
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
static const _LCD_Icon_t _LCD_Icon_BatteryFull =
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
static const _LCD_Icon_t _LCD_Icon_SignalLow =
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
static const _LCD_Icon_t _LCD_Icon_SignalHalf =
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
static const _LCD_Icon_t _LCD_Icon_SignalFull =
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
// #### Private Method(s) ######################################################
// #############################################################################

static void _send( uint8_t value, bool command=false )
{
    Platform_Pin_Write(Platform_Pin_LCD_EN, Platform_Pin_Value_HIGH);

    Platform_Pin_Write(Platform_Pin_LCD_RS, command ? Platform_Pin_Value_LOW : Platform_Pin_Value_HIGH);

    Platform_Pin_Write(Platform_Pin_LCD_D0, ( value & ( 0x01 << 0) ) ? Platform_Pin_Value_HIGH : Platform_Pin_Value_LOW);
    Platform_Pin_Write(Platform_Pin_LCD_D1, ( value & ( 0x01 << 1) ) ? Platform_Pin_Value_HIGH : Platform_Pin_Value_LOW);
    Platform_Pin_Write(Platform_Pin_LCD_D2, ( value & ( 0x01 << 2) ) ? Platform_Pin_Value_HIGH : Platform_Pin_Value_LOW);
    Platform_Pin_Write(Platform_Pin_LCD_D3, ( value & ( 0x01 << 3) ) ? Platform_Pin_Value_HIGH : Platform_Pin_Value_LOW);
    Platform_Pin_Write(Platform_Pin_LCD_D4, ( value & ( 0x01 << 4) ) ? Platform_Pin_Value_HIGH : Platform_Pin_Value_LOW);
    Platform_Pin_Write(Platform_Pin_LCD_D5, ( value & ( 0x01 << 5) ) ? Platform_Pin_Value_HIGH : Platform_Pin_Value_LOW);
    Platform_Pin_Write(Platform_Pin_LCD_D6, ( value & ( 0x01 << 6) ) ? Platform_Pin_Value_HIGH : Platform_Pin_Value_LOW);
    Platform_Pin_Write(Platform_Pin_LCD_D7, ( value & ( 0x01 << 7) ) ? Platform_Pin_Value_HIGH : Platform_Pin_Value_LOW);

    Platform_Pin_Write(Platform_Pin_LCD_EN, Platform_Pin_Value_LOW);
    _delay_ms(2);
}

/*
 * @brief Initializes LCD
 *
 * @param[in] void  : None
 *
 * @return void     : None
 */
bool _LCD_Initialize( void )
{
    static bool isInitialized = false;
    do
    {
        if (isInitialized) break;
        Platform_Pin_Setup(Platform_Pin_LCD_BL,  Platform_Pin_Mode_OUTPUT);
        Platform_Pin_Setup(Platform_Pin_LCD_EN,  Platform_Pin_Mode_OUTPUT);
        Platform_Pin_Setup(Platform_Pin_LCD_RS,  Platform_Pin_Mode_OUTPUT);
        Platform_Pin_Setup(Platform_Pin_LCD_D0,  Platform_Pin_Mode_OUTPUT);
        Platform_Pin_Setup(Platform_Pin_LCD_D1,  Platform_Pin_Mode_OUTPUT);
        Platform_Pin_Setup(Platform_Pin_LCD_D2,  Platform_Pin_Mode_OUTPUT);
        Platform_Pin_Setup(Platform_Pin_LCD_D3,  Platform_Pin_Mode_OUTPUT);
        Platform_Pin_Setup(Platform_Pin_LCD_D4,  Platform_Pin_Mode_OUTPUT);
        Platform_Pin_Setup(Platform_Pin_LCD_D5,  Platform_Pin_Mode_OUTPUT);
        Platform_Pin_Setup(Platform_Pin_LCD_D6,  Platform_Pin_Mode_OUTPUT);
        Platform_Pin_Setup(Platform_Pin_LCD_D7,  Platform_Pin_Mode_OUTPUT);
        Platform_Pin_Setup(Platform_Pin_LCD_CS1, Platform_Pin_Mode_OUTPUT);
        Platform_Pin_Setup(Platform_Pin_LCD_CS2, Platform_Pin_Mode_OUTPUT);

        Platform_Pin_Write(Platform_Pin_LCD_BL,  Platform_Pin_Value_LOW);
        Platform_Pin_Write(Platform_Pin_LCD_EN,  Platform_Pin_Value_LOW);
        Platform_Pin_Write(Platform_Pin_LCD_RS,  Platform_Pin_Value_LOW);
        Platform_Pin_Write(Platform_Pin_LCD_D0,  Platform_Pin_Value_LOW);
        Platform_Pin_Write(Platform_Pin_LCD_D1,  Platform_Pin_Value_LOW);
        Platform_Pin_Write(Platform_Pin_LCD_D2,  Platform_Pin_Value_LOW);
        Platform_Pin_Write(Platform_Pin_LCD_D3,  Platform_Pin_Value_LOW);
        Platform_Pin_Write(Platform_Pin_LCD_D4,  Platform_Pin_Value_LOW);
        Platform_Pin_Write(Platform_Pin_LCD_D5,  Platform_Pin_Value_LOW);
        Platform_Pin_Write(Platform_Pin_LCD_D6,  Platform_Pin_Value_LOW);
        Platform_Pin_Write(Platform_Pin_LCD_D7,  Platform_Pin_Value_LOW);
        Platform_Pin_Write(Platform_Pin_LCD_CS1, Platform_Pin_Value_LOW);
        Platform_Pin_Write(Platform_Pin_LCD_CS2, Platform_Pin_Value_LOW);

        _delay_ms(_LCD_POWER_ON_DELAY);
        _Function._font = _Function_Font_5x8;
        _Function._interface = _Function_Interface_8bit;
        _Function._line = _Function_Line_2_Line;
        _send(_Function._command, true);
        _send(_Function._command, true);

        _Setting._cursor = _Setting_Cursor_Disable;
        _Setting._cursor_blink = _Setting_Cursor_Blink_Disable;
        _Setting._display = _Setting_Display_Enable;
        _send(_Setting._command, true);

        _send(_Clear._command, true);

        _Mode._select = _Mode_Select_Cursor;
        _Mode._cursor = _Mode_Cursor_Increment;
        _send(_Mode._command, true);

        isInitialized = true;
    }
    while(0);
    return isInitialized;
}

/*
 * @brief Clears LCD
 *
 * @param[in] void  : None
 *
 * @return void     : None
 */
void _LCD_Clear( void )
{
    _send(_Clear._command, true);
}

// #############################################################################
// #### Public Method(s) #######################################################
// #############################################################################

/*
 * @brief Turns LCD back-light on
 *
 * @param[in] void  : None
 *
 * @return void     : None
 */
void LCD_LightOn( void )
{
    _LCD_Initialize();
    Platform_Pin_Setup(Platform_Pin_LCD_BL, Platform_Pin_Mode_OUTPUT);
    Platform_Pin_Write(Platform_Pin_LCD_BL, Platform_Pin_Value_HIGH);
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
    _LCD_Initialize();
    Platform_Pin_Setup(Platform_Pin_LCD_BL, Platform_Pin_Mode_OUTPUT);
    Platform_Pin_Write(Platform_Pin_LCD_BL, Platform_Pin_Value_LOW);
}

/*
 * @brief Writes a screen content to display
 *
 * @param[in] LCD_Screen : screen content
 *
 * @return void     : None
 */
void LCD_Write( LCD_Screen_t LCD_Screen )
{
    _LCD_Initialize();
    for (uint8_t line = 0; line < LCD_SCREEN_HEIGHT; ++line)
    {
        _DDRAM._address = (line == 0 ? 0x00 : 0x40);
        _send(_DDRAM._command, true);
        for (uint8_t i = 0; i < LCD_SCREEN_WIDTH; ++i)
        {
            _send(LCD_Screen[line][i]);
        }
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
    _LCD_Initialize();
    do
    {
        _LCD_Icon_t * _LCD_Icon = NULL;
        switch (LCD_Icon)
        {
            case LCD_Icon_Empty:                   _LCD_Icon = &_LCD_Icon_Empty;                   break;
            case LCD_Icon_Bluetooth:               _LCD_Icon = &_LCD_Icon_Bluetooth;               break;
            case LCD_Icon_LockOn:                  _LCD_Icon = &_LCD_Icon_LockOn;                  break;
            case LCD_Icon_LockOff:                 _LCD_Icon = &_LCD_Icon_LockOff;                 break;
            case LCD_Icon_Calendar:                _LCD_Icon = &_LCD_Icon_Calendar;                break;
            case LCD_Icon_Clock:                   _LCD_Icon = &_LCD_Icon_Clock;                   break;
            case LCD_Icon_Bell:                    _LCD_Icon = &_LCD_Icon_Bell;                    break;
            case LCD_Icon_Degree:                  _LCD_Icon = &_LCD_Icon_Degree;                  break;
            case LCD_Icon_Thermometer:             _LCD_Icon = &_LCD_Icon_Thermometer;             break;
            case LCD_Icon_WaterDrop:               _LCD_Icon = &_LCD_Icon_WaterDrop;               break;
            case LCD_Icon_Bar_Loading_StartEmpty:  _LCD_Icon = &_LCD_Icon_Bar_Loading_StartEmpty;  break;
            case LCD_Icon_Bar_Loading_StartFull:   _LCD_Icon = &_LCD_Icon_Bar_Loading_StartFull;   break;
            case LCD_Icon_Bar_Loading_MiddleEmpty: _LCD_Icon = &_LCD_Icon_Bar_Loading_MiddleEmpty; break;
            case LCD_Icon_Bar_Loading_MiddleHalf:  _LCD_Icon = &_LCD_Icon_Bar_Loading_MiddleHalf;  break;
            case LCD_Icon_Bar_Loading_MiddleFull:  _LCD_Icon = &_LCD_Icon_Bar_Loading_MiddleFull;  break;
            case LCD_Icon_Bar_Loading_EndEmpty:    _LCD_Icon = &_LCD_Icon_Bar_Loading_EndEmpty;    break;
            case LCD_Icon_Bar_Loading_EndFull:     _LCD_Icon = &_LCD_Icon_Bar_Loading_EndFull;     break;
            case LCD_Icon_MelodySingle:            _LCD_Icon = &_LCD_Icon_MelodySingle;            break;
            case LCD_Icon_MelodyDual:              _LCD_Icon = &_LCD_Icon_MelodyDual;              break;
            case LCD_Icon_MelodyPlay:              _LCD_Icon = &_LCD_Icon_MelodyPlay;              break;
            case LCD_Icon_MelodyStop:              _LCD_Icon = &_LCD_Icon_MelodyStop;              break;
            case LCD_Icon_MelodyPause:             _LCD_Icon = &_LCD_Icon_MelodyPause;             break;
            case LCD_Icon_MelodyNext:              _LCD_Icon = &_LCD_Icon_MelodyNext;              break;
            case LCD_Icon_MelodyPrevious:          _LCD_Icon = &_LCD_Icon_MelodyPrevious;          break;
            case LCD_Icon_Heart:                   _LCD_Icon = &_LCD_Icon_Heart;                   break;
            case LCD_Icon_BatteryLow:              _LCD_Icon = &_LCD_Icon_BatteryLow;              break;
            case LCD_Icon_BatteryHalf:             _LCD_Icon = &_LCD_Icon_BatteryHalf;             break;
            case LCD_Icon_BatteryFull:             _LCD_Icon = &_LCD_Icon_BatteryFull;             break;
            case LCD_Icon_SignalLow:               _LCD_Icon = &_LCD_Icon_SignalLow;               break;
            case LCD_Icon_SignalHalf:              _LCD_Icon = &_LCD_Icon_SignalHalf;              break;
            case LCD_Icon_SignalFull:              _LCD_Icon = &_LCD_Icon_SignalFull;              break;
            case LCD_Icon_Alarm:                   _LCD_Icon = &_LCD_Icon_Bell;                    break;
            default:                               _LCD_Icon = NULL;                               break;
        }
        if (_LCD_Icon == NULL) break;

        _CGRAM._address = LCD_Custom_Character;
        _CGRAM._address <<= 3;
        _send(_CGRAM._command, true);
        for (uint8_t i = 0; i < sizeof(_LCD_Icon_t); ++i)
        {
            _send((uint8_t)_LCD_Icon[i]);
        }
    }
    while(0);
}

// #############################################################################
// #### Public Variable(s) #####################################################
// #############################################################################

// #############################################################################
// #### END OF FILE ############################################################
// #############################################################################

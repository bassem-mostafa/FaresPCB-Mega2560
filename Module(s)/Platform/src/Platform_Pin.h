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

#ifndef PLATFORM_PIN_H_
#define PLATFORM_PIN_H_

// #############################################################################
// #### Include(s) #############################################################
// #############################################################################

#include "Platform_Types.h"

// #############################################################################
// #### Public Macro(s) ########################################################
// #############################################################################

// #############################################################################
// #### Public Type(s) #########################################################
// #############################################################################

typedef enum __attribute__((packed, aligned(1))) Platform_Pin_t
{
    Platform_Pin_0 = 0,
    Platform_Pin_1,
    Platform_Pin_2,
    Platform_Pin_3,
    Platform_Pin_4,
    Platform_Pin_5,
    Platform_Pin_6,
    Platform_Pin_7,
    Platform_Pin_8,
    Platform_Pin_9,
    Platform_Pin_10,
    Platform_Pin_11,
    Platform_Pin_12,
    Platform_Pin_13,
    Platform_Pin_14,
    Platform_Pin_15,
    Platform_Pin_16,
    Platform_Pin_17,
    Platform_Pin_18,
    Platform_Pin_19,
    Platform_Pin_20,
    Platform_Pin_21,
    Platform_Pin_22,
    Platform_Pin_23,
    Platform_Pin_24,
    Platform_Pin_25,
    Platform_Pin_26,
    Platform_Pin_27,
    Platform_Pin_28,
    Platform_Pin_29,
    Platform_Pin_30,
    Platform_Pin_31,
    Platform_Pin_32,
    Platform_Pin_33,
    Platform_Pin_34,
    Platform_Pin_35,
    Platform_Pin_36,
    Platform_Pin_37,
    Platform_Pin_38,
    Platform_Pin_39,
    Platform_Pin_40,
    Platform_Pin_41,
    Platform_Pin_42,
    Platform_Pin_43,
    Platform_Pin_44,
    Platform_Pin_45,
    Platform_Pin_46,
    Platform_Pin_47,
    Platform_Pin_48,
    Platform_Pin_49,
    Platform_Pin_50,
    Platform_Pin_51,
    Platform_Pin_52,
    Platform_Pin_53,
    Platform_Pin_54,
    Platform_Pin_55,
    Platform_Pin_56,
    Platform_Pin_57,
    Platform_Pin_58,
    Platform_Pin_59,
    Platform_Pin_60,
    Platform_Pin_61,
    Platform_Pin_62,
    Platform_Pin_63,
    Platform_Pin_64,
    Platform_Pin_65,
    Platform_Pin_66,
    Platform_Pin_67,
    Platform_Pin_68,
    Platform_Pin_69,
    Platform_Pin_70,
    Platform_Pin_71,
    Platform_Pin_72,
    Platform_Pin_73,
    Platform_Pin_74,
    Platform_Pin_75,
    Platform_Pin_76,
    Platform_Pin_77,
    Platform_Pin_78,
    Platform_Pin_79,
    Platform_Pin_80,
    Platform_Pin_81,
    Platform_Pin_82,
    Platform_Pin_83,
    Platform_Pin_84,
    Platform_Pin_85,
    Platform_Pin_86,
    Platform_Pin_87,
    Platform_Pin_88,
    Platform_Pin_89,
    Platform_Pin_90,
    Platform_Pin_91,
    Platform_Pin_92,
    Platform_Pin_93,
    Platform_Pin_94,
    Platform_Pin_95,
    Platform_Pin_96,
    Platform_Pin_97,
    Platform_Pin_98,
    Platform_Pin_99,
    Platform_Pin_100,
    Platform_Pin_101,
    Platform_Pin_102,
    Platform_Pin_103,
    Platform_Pin_104,
    Platform_Pin_105,
    Platform_Pin_106,
    Platform_Pin_107,
    Platform_Pin_108,
    Platform_Pin_109,
    Platform_Pin_110,
    Platform_Pin_111,
    Platform_Pin_112,
    Platform_Pin_113,
    Platform_Pin_114,
    Platform_Pin_115,
    Platform_Pin_116,
    Platform_Pin_117,
    Platform_Pin_118,
    Platform_Pin_119,
    Platform_Pin_120,
    Platform_Pin_121,
    Platform_Pin_122,
    Platform_Pin_123,
    Platform_Pin_124,
    Platform_Pin_125,
    Platform_Pin_126,
    Platform_Pin_127,
    Platform_Pin_128,
    Platform_Pin_129,
    Platform_Pin_130,
    Platform_Pin_131,
    Platform_Pin_132,
    Platform_Pin_133,
    Platform_Pin_134,
    Platform_Pin_135,
    Platform_Pin_136,
    Platform_Pin_137,
    Platform_Pin_138,
    Platform_Pin_139,
    Platform_Pin_140,
    Platform_Pin_141,
    Platform_Pin_142,
    Platform_Pin_143,
    Platform_Pin_144,
    Platform_Pin_145,
    Platform_Pin_146,
    Platform_Pin_147,
    Platform_Pin_148,
    Platform_Pin_149,
    Platform_Pin_150,
    Platform_Pin_151,
    Platform_Pin_152,
    Platform_Pin_153,
    Platform_Pin_154,
    Platform_Pin_155,
    Platform_Pin_156,
    Platform_Pin_157,
    Platform_Pin_158,
    Platform_Pin_159,
    Platform_Pin_160,
    Platform_Pin_161,
    Platform_Pin_162,
    Platform_Pin_163,
    Platform_Pin_164,
    Platform_Pin_165,
    Platform_Pin_166,
    Platform_Pin_167,
    Platform_Pin_168,
    Platform_Pin_169,
    Platform_Pin_170,
    Platform_Pin_171,
    Platform_Pin_172,
    Platform_Pin_173,
    Platform_Pin_174,
    Platform_Pin_175,
    Platform_Pin_176,
    Platform_Pin_177,
    Platform_Pin_178,
    Platform_Pin_179,
    Platform_Pin_180,
    Platform_Pin_181,
    Platform_Pin_182,
    Platform_Pin_183,
    Platform_Pin_184,
    Platform_Pin_185,
    Platform_Pin_186,
    Platform_Pin_187,
    Platform_Pin_188,
    Platform_Pin_189,
    Platform_Pin_190,
    Platform_Pin_191,
    Platform_Pin_192,
    Platform_Pin_193,
    Platform_Pin_194,
    Platform_Pin_195,
    Platform_Pin_196,
    Platform_Pin_197,
    Platform_Pin_198,
    Platform_Pin_199,
    Platform_Pin_200,
    // TODO Need More Pins ?
} Platform_Pin_t;

typedef enum __attribute__((packed, aligned(1))) Platform_Pin_Mode_t
{
    Platform_Pin_Mode_OUTPUT,
    Platform_Pin_Mode_OUTPUT_OpenDrain,
    Platform_Pin_Mode_OUTPUT_PushPull,
    Platform_Pin_Mode_INPUT,
    Platform_Pin_Mode_INPUT_PullUp,
    Platform_Pin_Mode_INPUT_PullDown,
    Platform_Pin_Mode_TRI_STATE,
} Platform_Pin_Mode_t;

typedef enum __attribute__((packed, aligned(1))) Platform_Pin_Value_t
{
    Platform_Pin_Value_LOW,
    Platform_Pin_Value_HIGH
} Platform_Pin_Value_t;

typedef struct _Platform_Pin_Setting_t* Platform_Pin_Setting_t;

// #############################################################################
// #### Public Method(s) #######################################################
// #############################################################################

Platform_Status_t Platform_Pin_Setting_Initialize
(
        Platform_Pin_Setting_t * Platform_Pin_Setting
);

Platform_Status_t Platform_Pin_Setting_Mode_Set
(
        Platform_Pin_Setting_t Platform_Pin_Setting,
        Platform_Pin_Mode_t Platform_Pin_Mode
);

Platform_Status_t Platform_Pin_Setup
(
        Platform_Pin_t Platform_Pin,
        Platform_Pin_Setting_t Platform_Pin_Setting
);

Platform_Status_t Platform_Pin_Write
(
        Platform_Pin_t Platform_Pin,
        Platform_Pin_Value_t Platform_Pin_Value
);

Platform_Status_t Platform_Pin_Read
(
        Platform_Pin_t Platform_Pin,
        Platform_Pin_Value_t * Platform_Pin_Value
);

// #############################################################################
// #### Public Variable(s) #####################################################
// #############################################################################

// #############################################################################
// #### File Guard #############################################################
// #############################################################################

#endif /* PLATFORM_PIN_H_ */

// #############################################################################
// #### END OF FILE ############################################################
// #############################################################################

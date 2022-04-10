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
#include "Temperature.h"

// #############################################################################
// #### Private Macro(s) #######################################################
// #############################################################################

#define SENSOR_SENSITIVITY      (10) // in milli-Volt per degree celsius
#define TO_VOLT(READING)        ( ( (double) (READING) /* ADC Reading */ / (1 << 10 /* ADC Resolution in bits */) ) * (5000 /* Reference Voltage in milli-volt */) )
#define TO_CELSIUS(VOLT)        ( (double) (VOLT) / (SENSOR_SENSITIVITY) )

// #############################################################################
// #### Private Type(s) ########################################################
// #############################################################################

// #############################################################################
// #### Private Variable(s) ####################################################
// #############################################################################

// #############################################################################
// #### Private Method(s) ######################################################
// #############################################################################

static void sortBubble(uint16_t * readings, uint8_t size)
{
    uint8_t min_idx = 0;
    for (uint8_t i = 0; i < size; ++i)
    {
        min_idx = i;
        for (uint8_t j = i + 1; j < size; ++j)
        {
            if (readings[j] < readings[min_idx])
            {
                min_idx = j;
            }
        }
        if (min_idx != i)
        {
            uint16_t temp = readings[i];
            readings[i] = readings[min_idx];
            readings[min_idx] = temp;
        }
    }
}

// #############################################################################
// #### Public Method(s) #######################################################
// #############################################################################

/*
 * @brief Reads temperature value
 *
 * @param[in] void   : None
 *
 * @return double     : Temperature value in degrees celsius
 */
double Temperature_Celsius( void )
{
    double temperature = 0.0l;
    uint16_t readings[7];

    pinMode(HW_TEMPERATURE_SENSOR, INPUT);
    for (uint8_t i = 0; i < (sizeof(readings) / sizeof(readings[0])); ++i)
    {
        readings[i] = analogRead(HW_TEMPERATURE_SENSOR);
    }
    sortBubble(readings, (sizeof(readings) / sizeof(readings[0])));
    temperature = TO_CELSIUS( TO_VOLT( readings[(sizeof(readings) / sizeof(readings[0])) / 2 /* Median Value */] ) );
    return temperature;
}

// #############################################################################
// #### Public Variable(s) #####################################################
// #############################################################################

// #############################################################################
// #### END OF FILE ############################################################
// #############################################################################

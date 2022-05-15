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

#include "Arduino_FreeRTOS.h"
#include "Task_LED.h"
#include "LED.h"
#include "queue.h"

// #############################################################################
// #### Private Macro(s) #######################################################
// #############################################################################

#define TASK_NAME           ("Task_LED")
#define TASK_STACK          (200) // in words
#define TASK_PRIORITY       (configMAX_PRIORITIES-4)
#define TASK_PERIOD         (200) // in milli-seconds
#define TASK_QUEUE_LENGTH   (2) // in milli-seconds

// #############################################################################
// #### Private Type(s) ########################################################
// #############################################################################

typedef struct __attribute__((packed, aligned(1))) Request_t
{
    Task_LED_Request_t request;
    union
    {
        struct
        {
            bool status;
        } _blink;
        struct
        {
            LED_t LED;
        } _increase;
        struct
        {
            LED_t LED;
        } _decrease;
        struct
        {
            uint8_t red;
            uint8_t green;
            uint8_t blue;
        } _rgb;
    };
} Request_t;

// #############################################################################
// #### Private Method(s) Prototype ############################################
// #############################################################################

// #############################################################################
// #### Private Variable(s) ####################################################
// #############################################################################

static QueueHandle_t QueueHandle = NULL;

// #############################################################################
// #### Private Method(s) ######################################################
// #############################################################################

static void vTask( void *pvParameters )
{
    const TickType_t xFrequency = pdMS_TO_TICKS(TASK_PERIOD);
    TickType_t xLastWakeTime = xTaskGetTickCount();
    Request_t Request;

    QueueHandle = xQueueCreate( TASK_QUEUE_LENGTH, sizeof(Request_t) );

    Task_LED_Request(Task_LED_Request_RGB);

    for( ;; )
    {
        if ( xQueueReceive(QueueHandle, &Request, pdMS_TO_TICKS(0)) == pdTRUE )
        {
            LED_TurnOff(LED_1);
            LED_TurnOff(LED_2);
            LED_TurnOff(LED_3);
            LED_TurnOff(LED_4);
            LED_TurnOff(LED_5);
            LED_RGB_SetIntensity(0, 0, 0);

            switch (Request.request)
            {
                case Task_LED_Request_Off:
                    // Nothing To Be Done
                    break;
                case Task_LED_Request_On:
                    // Nothing To Be Done
                    break;
                case Task_LED_Request_Blink:
                    Request._blink.status = false;
                    break;
                case Task_LED_Request_Increase:
                    Request._increase.LED = LED_5;
                    break;
                case Task_LED_Request_Decrease:
                    Request._decrease.LED = LED_1;
                    break;
                case Task_LED_Request_RGB:
                    Request._rgb.red = 0;
                    Request._rgb.green = 0;
                    Request._rgb.blue = 0;
                    break;
                default:
                    break;
            }
        }
        switch (Request.request)
        {
            case Task_LED_Request_Off:
                LED_TurnOff(LED_1);
                LED_TurnOff(LED_2);
                LED_TurnOff(LED_3);
                LED_TurnOff(LED_4);
                LED_TurnOff(LED_5);
                Request.request = Task_LED_Request_None;
                break;
            case Task_LED_Request_On:
                LED_TurnOn(LED_1);
                LED_TurnOn(LED_2);
                LED_TurnOn(LED_3);
                LED_TurnOn(LED_4);
                LED_TurnOn(LED_5);
                Request.request = Task_LED_Request_None;
                break;
            case Task_LED_Request_Blink:
                if (Request._blink.status == false)
                {
                    LED_TurnOn(LED_1);
                    LED_TurnOn(LED_2);
                    LED_TurnOn(LED_3);
                    LED_TurnOn(LED_4);
                    LED_TurnOn(LED_5);
                    Request._blink.status = true;
                }
                else
                {
                    LED_TurnOff(LED_1);
                    LED_TurnOff(LED_2);
                    LED_TurnOff(LED_3);
                    LED_TurnOff(LED_4);
                    LED_TurnOff(LED_5);
                    Request._blink.status = false;
                }
                break;
            case Task_LED_Request_Increase:
                LED_TurnOff(Request._increase.LED);
                Request._increase.LED =  Request._increase.LED >= LED_5 ? LED_1 : Request._increase.LED + 1;
                LED_TurnOn(Request._increase.LED);
                break;
            case Task_LED_Request_Decrease:
                LED_TurnOff(Request._decrease.LED);
                Request._decrease.LED =  Request._increase.LED <= LED_1 ? LED_5 : Request._increase.LED - 1;
                LED_TurnOn(Request._decrease.LED);
                break;
            case Task_LED_Request_RGB:
                LED_RGB_SetIntensity(Request._rgb.red, Request._rgb.green, Request._rgb.blue);
                Request._rgb.red += 50;
                if (Request._rgb.red >= 250)
                {
                    Request._rgb.red = 0;
                    Request._rgb.green += 50;
                    if (Request._rgb.green >= 250)
                    {
                        Request._rgb.green = 0;
                        Request._rgb.blue += 50;
                        if (Request._rgb.blue >= 250)
                        {
                            Request._rgb.blue = 0;
                        }
                    }
                }
                break;
            default:
                break;
        }
        vTaskDelayUntil( &xLastWakeTime, xFrequency );
    }
}

// #############################################################################
// #### Public Method(s) #######################################################
// #############################################################################

/*
 * @brief Initializes LED Task
 *
 * @param[in] void   : None
 *
 * @return true     : task initialized successfully
 * @return false    : task couldn't be initialized
 */
bool Task_LED_Initialize( void )
{
    return xTaskCreate(vTask, TASK_NAME, TASK_STACK, NULL, TASK_PRIORITY, NULL) == pdPASS ? true : false;
}

/*
 * @brief Requests from LED Task
 *
 * @param[in] Task_LED_Request   : selected Task_LED_Request
 *
 * @return true     : request pushed successfully
 * @return false    : request couldn't be pushed
 */
bool Task_LED_Request( Task_LED_Request_t Task_LED_Request)
{
    Request_t Request;
    Request.request = Task_LED_Request;
    return xQueueSend(QueueHandle, &Request, pdMS_TO_TICKS(0)) == pdTRUE ? true : false;
}

// #############################################################################
// #### Public Variable(s) #####################################################
// #############################################################################

// #############################################################################
// #### END OF FILE ############################################################
// #############################################################################

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
#include "Task_7Segment.h"
#include "Segment.h"
#include "queue.h"

// #############################################################################
// #### Private Macro(s) #######################################################
// #############################################################################

#define TASK_NAME           ("Task_7Segment")
#define TASK_STACK          (200) // in words
#define TASK_PRIORITY       (configMAX_PRIORITIES-3)
#define TASK_PERIOD         (25) // in milli-seconds
#define TASK_QUEUE_LENGTH   (2) // in milli-seconds

// #############################################################################
// #### Private Type(s) ########################################################
// #############################################################################

typedef struct __attribute__((packed, aligned(1))) Request_t
{
    Task_7Segment_Request_t request;
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
// #############################################################################]

static void vTask( void *pvParameters )
{
    const TickType_t xFrequency = pdMS_TO_TICKS(TASK_PERIOD);
    TickType_t xLastWakeTime = xTaskGetTickCount();
    Request_t Request;

    QueueHandle = xQueueCreate( TASK_QUEUE_LENGTH, sizeof(Request_t) );

    Task_7Segment_Request({1234});

    for( ;; )
    {
        if ( xQueueReceive(QueueHandle, &Request, pdMS_TO_TICKS(0)) == pdTRUE )
        {
        }
        Segment_Write(Segment_1, (Digit_t)( (Request.request.value /    1) % 10) );
        Segment_Write(Segment_2, (Digit_t)( (Request.request.value /   10) % 10) );
        Segment_Write(Segment_3, (Digit_t)( (Request.request.value /  100) % 10) );
        Segment_Write(Segment_4, (Digit_t)( (Request.request.value / 1000) % 10) );
        vTaskDelayUntil( &xLastWakeTime, xFrequency );
    }
}

// #############################################################################
// #### Public Method(s) #######################################################
// #############################################################################

/*
 * @brief Initializes 7-Segment Task
 *
 * @param[in] void   : None
 *
 * @return true     : task initialized successfully
 * @return false    : task couldn't be initialized
 */
bool Task_7Segment_Initialize( void )
{
    return xTaskCreate(vTask, TASK_NAME, TASK_STACK, NULL, TASK_PRIORITY, NULL) == pdPASS ? true : false;
}

/*
 * @brief Requests from 7-Segment Task
 *
 * @param[in] Task_Segment_Request   : selected Task_Segment_Request value
 *
 * @return true     : request pushed successfully
 * @return false    : request couldn't be pushed
 */
bool Task_7Segment_Request( Task_7Segment_Request_t Task_7Segment_Request)
{
    Request_t Request;
    Request.request = Task_7Segment_Request;
    return xQueueSend(QueueHandle, &Request, pdMS_TO_TICKS(0)) == pdTRUE ? true : false;
}

// #############################################################################
// #### Public Variable(s) #####################################################
// #############################################################################

// #############################################################################
// #### END OF FILE ############################################################
// #############################################################################

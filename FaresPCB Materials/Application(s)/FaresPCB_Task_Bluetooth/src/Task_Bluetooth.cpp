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
#include "Task_Bluetooth.h"
#include "Bluetooth.h"
#include "queue.h"
#include "string.h"
#include "Task_LED.h"
#include "Task_LCD.h"

// #############################################################################
// #### Private Macro(s) #######################################################
// #############################################################################

#define TASK_NAME           ("Task_Bluetooth")
#define TASK_STACK          (200) // in words
#define TASK_PRIORITY       (configMAX_PRIORITIES-3)
#define TASK_PERIOD         (50) // in milli-seconds
#define TASK_QUEUE_LENGTH   (2) // in milli-seconds


#define RECEIVED_DATA_SIZE  50

// #############################################################################
// #### Private Type(s) ########################################################
// #############################################################################

typedef enum __attribute__((packed, aligned(1))) Task_Bluetooth_Request_t
{
    Task_Bluetooth_Request_None = 0,

    Task_Bluetooth_Request_LED_Off,
    Task_Bluetooth_Request_LED_On,
    Task_Bluetooth_Request_LED_Blink,
    Task_Bluetooth_Request_LED_Increase,
    Task_Bluetooth_Request_LED_Decrease,
    Task_Bluetooth_Request_LED_RGB,

    Task_Bluetooth_Request_LCD_Off,
    Task_Bluetooth_Request_LCD_On,
    Task_Bluetooth_Request_LCD_Empty,
    Task_Bluetooth_Request_LCD_Loading,
    Task_Bluetooth_Request_LCD_DateTime,
    Task_Bluetooth_Request_LCD_Bluetooth,
    Task_Bluetooth_Request_LCD_Temperature,
    Task_Bluetooth_Request_LCD_Distance,
    Task_Bluetooth_Request_LCD_Version,
} Task_Bluetooth_Request_t;

typedef struct __attribute__((packed, aligned(1))) Request_t
{
    Task_Bluetooth_Request_t request;
    union
    {
        struct
        {
            char data[RECEIVED_DATA_SIZE];
            uint8_t length;
        } _received;
    };
} Request_t;

typedef struct __attribute__((packed, aligned(1))) Command_t
{
    char command[30];
    Task_Bluetooth_Request_t request;
} Command_t;

// #############################################################################
// #### Private Method(s) Prototype ############################################
// #############################################################################

// #############################################################################
// #### Private Variable(s) ####################################################
// #############################################################################

static QueueHandle_t QueueHandle = NULL;

Command_t commandSet[] =
{
        {"led off",      Task_Bluetooth_Request_LED_Off},
        {"led on",       Task_Bluetooth_Request_LED_On},
        {"led blink",    Task_Bluetooth_Request_LED_Blink},
        {"led increase", Task_Bluetooth_Request_LED_Increase},
        {"led decrease", Task_Bluetooth_Request_LED_Decrease},
        {"led rgb",      Task_Bluetooth_Request_LED_RGB},

        {"lcd off",         Task_Bluetooth_Request_LCD_Off},
        {"lcd on",          Task_Bluetooth_Request_LCD_On},
        {"lcd empty",       Task_Bluetooth_Request_LCD_Empty},
        {"lcd loading",     Task_Bluetooth_Request_LCD_Loading},
        {"lcd date",        Task_Bluetooth_Request_LCD_DateTime},
        {"lcd time",        Task_Bluetooth_Request_LCD_DateTime},
        {"lcd bluetooth",   Task_Bluetooth_Request_LCD_Bluetooth},
        {"lcd temperature", Task_Bluetooth_Request_LCD_Temperature},
        {"lcd distance",    Task_Bluetooth_Request_LCD_Distance},
        {"lcd version",     Task_Bluetooth_Request_LCD_Version},
};
// #############################################################################
// #### Private Method(s) ######################################################
// #############################################################################

bool Task_Request( Task_Bluetooth_Request_t Task_Bluetooth_Request)
{
    Request_t Request;
    Request.request = Task_Bluetooth_Request;
    return xQueueSend(QueueHandle, &Request, pdMS_TO_TICKS(0)) == pdTRUE ? true : false;
}

static void vTask( void *pvParameters )
{
    const TickType_t xFrequency = pdMS_TO_TICKS(TASK_PERIOD);
    TickType_t xLastWakeTime = xTaskGetTickCount();
    Request_t Request;

    QueueHandle = xQueueCreate( TASK_QUEUE_LENGTH, sizeof(Request_t) );

    Bluetooth_Initialize();

    Request._received.length = 0;

    extern const char FW_VERSION[30];
    Bluetooth_Write((uint8_t*)"\nFirmware Version: ", strlen("\nFirmware Version: "));
    Bluetooth_Write((uint8_t*)FW_VERSION, strlen(FW_VERSION));
    Bluetooth_Write((uint8_t*)"\nFaresPCB Ready\n", strlen("\nFaresPCB Ready\n"));

    for( ;; )
    {
        if ( xQueueReceive(QueueHandle, &Request, pdMS_TO_TICKS(0)) == pdTRUE )
        {
            switch (Request.request)
            {
                default:
                    break;
            }
        }
        switch (Request.request)
        {
            default:
                break;
        }

        {
            uint32_t length_read = Bluetooth_Read((uint8_t *)Request._received.data + Request._received.length, sizeof(Request._received.data) - Request._received.length);
            Request._received.length += length_read;
            if (length_read > 0)
            {
                Bluetooth_Write((uint8_t*)Request._received.data + Request._received.length - length_read, length_read);
            }
        }
        for (uint8_t i = 0; i < Request._received.length; ++i)
        {
            if (Request._received.data[i] == ';')
            {
                memcpy(Request._received.data, Request._received.data + (i + 1), Request._received.length - (i + 1));
                Request._received.length -= (i + 1);
                Bluetooth_Write((uint8_t*)"\nCommand [Clear]\n", strlen("\nCommand [Clear]\n"));
                break;
            }
        }
        for (uint8_t i = 0; i < sizeof(commandSet) / sizeof(commandSet[0]); ++i)
        {
            if (Request._received.length < strlen(commandSet[i].command) || memcmp(Request._received.data, commandSet[i].command, strlen(commandSet[i].command)) != 0)
            {
                continue;
            }
            Bluetooth_Write((uint8_t*)"\nCommand [", strlen("\nCommand ["));
            Bluetooth_Write((uint8_t*)commandSet[i].command, strlen(commandSet[i].command));
            Bluetooth_Write((uint8_t*)"]\n", strlen("]\n"));
            memcpy(Request._received.data, Request._received.data + strlen(commandSet[i].command), Request._received.length - strlen(commandSet[i].command));
            Request._received.length -= strlen(commandSet[i].command);
            switch (commandSet[i].request)
            {
                case Task_Bluetooth_Request_LED_Off:
                    Task_LED_Request(Task_LED_Request_Off);
                    break;
                case Task_Bluetooth_Request_LED_On:
                    Task_LED_Request(Task_LED_Request_On);
                    break;
                case Task_Bluetooth_Request_LED_Blink:
                    Task_LED_Request(Task_LED_Request_Blink);
                    break;
                case Task_Bluetooth_Request_LED_Increase:
                    Task_LED_Request(Task_LED_Request_Increase);
                    break;
                case Task_Bluetooth_Request_LED_Decrease:
                    Task_LED_Request(Task_LED_Request_Decrease);
                    break;
                case Task_Bluetooth_Request_LED_RGB:
                    Task_LED_Request(Task_LED_Request_RGB);
                    break;

                case Task_Bluetooth_Request_LCD_Off:
                    Task_LCD_Request(Task_LCD_Request_Off);
                    break;
                case Task_Bluetooth_Request_LCD_On:
                    Task_LCD_Request(Task_LCD_Request_On);
                    break;
                case Task_Bluetooth_Request_LCD_Empty:
                    Task_LCD_Request(Task_LCD_Request_Empty);
                    break;
                case Task_Bluetooth_Request_LCD_Loading:
                    Task_LCD_Request(Task_LCD_Request_Loading);
                    break;
                case Task_Bluetooth_Request_LCD_DateTime:
                    Task_LCD_Request(Task_LCD_Request_DateTime);
                    break;
                case Task_Bluetooth_Request_LCD_Bluetooth:
                    Task_LCD_Request(Task_LCD_Request_Bluetooth);
                    break;
                case Task_Bluetooth_Request_LCD_Temperature:
                    Task_LCD_Request(Task_LCD_Request_Temperature);
                    break;
                case Task_Bluetooth_Request_LCD_Distance:
                    Task_LCD_Request(Task_LCD_Request_Distance);
                    break;
                case Task_Bluetooth_Request_LCD_Version:
                    Task_LCD_Request(Task_LCD_Request_Version);
                    break;
                default:
                    break;
            }
        }
        vTaskDelayUntil( &xLastWakeTime, xFrequency );
    }
}

// #############################################################################
// #### Public Method(s) #######################################################
// #############################################################################

/*
 * @brief Initializes Bluetooth Task
 *
 * @param[in] void   : None
 *
 * @return true     : task initialized successfully
 * @return false    : task couldn't be initialized
 */
bool Task_Bluetooth_Initialize( void )
{
    return xTaskCreate(vTask, TASK_NAME, TASK_STACK, NULL, TASK_PRIORITY, NULL) == pdPASS ? true : false;
}

// #############################################################################
// #### Public Variable(s) #####################################################
// #############################################################################

// #############################################################################
// #### END OF FILE ############################################################
// #############################################################################

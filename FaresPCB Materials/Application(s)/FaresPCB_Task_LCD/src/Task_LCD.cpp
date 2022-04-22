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
#include "Task_LCD.h"
#include "LCD.h"
#include "queue.h"
#include "string.h"
#include "Bluetooth.h"
#include "Temperature.h"
#include "stdlib.h"
#include "stdio.h"

// #############################################################################
// #### Private Macro(s) #######################################################
// #############################################################################

#define TASK_NAME           ("Task_LCD")
#define TASK_STACK          (200) // in words
#define TASK_PRIORITY       (configMAX_PRIORITIES-4)
#define TASK_PERIOD         (100) // in milli-seconds
#define TASK_QUEUE_LENGTH   (2) // in milli-seconds

#define LOADING_BAR_SIZE    9
#if LOADING_BAR_SIZE < 3
#warning "macro LOADING_BAR_SIZE should be equal to 3 or higher"
#endif
#define TEMPERATURE_TEXT_SIZE 6

// #############################################################################
// #### Private Type(s) ########################################################
// #############################################################################

typedef struct __attribute__((packed, aligned(1))) Request_t
{
    Task_LCD_Request_t request;
    union
    {
        struct
        {
            uint8_t index;
            LCD_Custom_Character_t bar[LOADING_BAR_SIZE];
        } _loading;
        struct
        {
            Bluetooth_Status_t status;
        } _bluetooth;
        struct
        {
            char text[TEMPERATURE_TEXT_SIZE];
            double celsius;
        } _temperature;
    };
} Request_t;

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

    LCD_Initialize();

    for( ;; )
    {
        if ( xQueueReceive(QueueHandle, &Request, pdMS_TO_TICKS(0)) == pdTRUE )
        {
            LCD_Clear();

            switch (Request.request)
            {
                case Task_LCD_Request_Off:
                    break;
                case Task_LCD_Request_On:
                    break;
                case Task_LCD_Request_Empty:
                    break;
                case Task_LCD_Request_Loading:
                    LCD_Setup(LCD_Custom_Character_1, LCD_Icon_Bar_Loading_StartEmpty);
                    LCD_Setup(LCD_Custom_Character_2, LCD_Icon_Bar_Loading_StartFull);
                    LCD_Setup(LCD_Custom_Character_3, LCD_Icon_Bar_Loading_MiddleEmpty);
                    LCD_Setup(LCD_Custom_Character_4, LCD_Icon_Bar_Loading_MiddleHalf);
                    LCD_Setup(LCD_Custom_Character_5, LCD_Icon_Bar_Loading_MiddleFull);
                    LCD_Setup(LCD_Custom_Character_6, LCD_Icon_Bar_Loading_EndEmpty);
                    LCD_Setup(LCD_Custom_Character_7, LCD_Icon_Bar_Loading_EndFull);

                    Request._loading.bar[0] = LCD_Custom_Character_1;
                    for (uint8_t i = 1; i < LOADING_BAR_SIZE; i++)
                    {
                        Request._loading.bar[i] = LCD_Custom_Character_3;
                    }
                    Request._loading.bar[LOADING_BAR_SIZE - 1] = LCD_Custom_Character_6;
                    Request._loading.index = 0;
                    break;
                case Task_LCD_Request_DateTime:
                    LCD_Setup(LCD_Custom_Character_1, LCD_Icon_Calendar);
                    LCD_Setup(LCD_Custom_Character_2, LCD_Icon_Clock);
                    LCD_Setup(LCD_Custom_Character_3, LCD_Icon_Alarm);
                    break;
                case Task_LCD_Request_Bluetooth:
                    LCD_Setup(LCD_Custom_Character_1, LCD_Icon_Bluetooth);
                    Request._bluetooth.status = Bluetooth_Status();
                    break;
                case Task_LCD_Request_Temperature:
                    LCD_Setup(LCD_Custom_Character_1, LCD_Icon_Thermometer);
                    LCD_Setup(LCD_Custom_Character_2, LCD_Icon_Degree);
                    break;
                case Task_LCD_Request_Distance:
                    break;
                case Task_LCD_Request_Version:
                    break;
                default:
                    break;
            }
        }
        switch (Request.request)
        {
            case Task_LCD_Request_Off:
                LCD_LightOff();
                break;
            case Task_LCD_Request_On:
                LCD_LightOn();
                break;
            case Task_LCD_Request_Empty:
                break;
            case Task_LCD_Request_Loading:
                if (Request._loading.index >= LOADING_BAR_SIZE) break;
                LCD_Write(LCD_Line_1, LCD_Character_5, (uint8_t*)"Loading", strlen("Loading"));
                switch (Request._loading.bar[Request._loading.index])
                {
                    case LCD_Custom_Character_1:
                        Request._loading.bar[Request._loading.index++] = LCD_Custom_Character_2;
                        break;
                    case LCD_Custom_Character_3:
                        Request._loading.bar[Request._loading.index] = LCD_Custom_Character_4;
                        break;
                    case LCD_Custom_Character_4:
                        Request._loading.bar[Request._loading.index++] = LCD_Custom_Character_5;
                        break;
                    case LCD_Custom_Character_6:
                        Request._loading.bar[Request._loading.index++] = LCD_Custom_Character_7;
                        break;
                    default:
                        break;
                }
                for (uint8_t i = 0; i < LOADING_BAR_SIZE; i++)
                {
                    LCD_Draw(LCD_Line_2, (LCD_Character_t)(LCD_Character_8 - (LOADING_BAR_SIZE / 2) + i), Request._loading.bar[i]);
                }
                break;
            case Task_LCD_Request_DateTime:
                LCD_Draw(LCD_Line_1, LCD_Character_1, LCD_Custom_Character_1);
                LCD_Draw(LCD_Line_2, LCD_Character_1, LCD_Custom_Character_2);
                LCD_Draw(LCD_Line_2, LCD_Character_2, LCD_Custom_Character_3);
                LCD_Write(LCD_Line_1, LCD_Character_3, (uint8_t*)"??? ??/??/????", strlen("??? ??/??/????"));
                LCD_Write(LCD_Line_2, LCD_Character_6, (uint8_t*)"??:??:?? ??", strlen("??:??:?? ??"));
                break;
            case Task_LCD_Request_Bluetooth:
                if (Request._bluetooth.status != Bluetooth_Status())
                {
                    Request._bluetooth.status = Bluetooth_Status();
                    LCD_Clear();
                }
                LCD_Write(LCD_Line_1, LCD_Character_4, (uint8_t*)"Bluetooth", strlen("Bluetooth"));
                LCD_Draw(LCD_Line_1, LCD_Character_1, LCD_Custom_Character_1);
                switch (Bluetooth_Status())
                {
                    case Bluetooth_Status_Idle:
                        LCD_Write(LCD_Line_2, LCD_Character_5, (uint8_t*)"Waiting", strlen("Waiting"));
                        break;
                    case Bluetooth_Status_Connected:
                        LCD_Write(LCD_Line_2, LCD_Character_4, (uint8_t*)"Connected", strlen("Connected"));
                        break;
                    default:
                        break;
                }
                break;
            case Task_LCD_Request_Temperature:
                Request._temperature.celsius = Temperature_Celsius();
                snprintf(Request._temperature.text, sizeof(Request._temperature.text), "%5.5s", dtostrf(Request._temperature.celsius, 5, 2, Request._temperature.text));
                LCD_Write(LCD_Line_1, LCD_Character_3, (uint8_t*)"Temperature", strlen("Temperature"));
                LCD_Draw(LCD_Line_2, LCD_Character_1, LCD_Custom_Character_1);
                LCD_Write(LCD_Line_2, LCD_Character_10, (uint8_t*)Request._temperature.text, strlen(Request._temperature.text));
                LCD_Draw(LCD_Line_2, LCD_Character_15, LCD_Custom_Character_2);
                LCD_Write(LCD_Line_2, LCD_Character_16, (uint8_t*)"C", strlen("C"));
                break;
            case Task_LCD_Request_Distance:
                LCD_Write(LCD_Line_1, LCD_Character_5, (uint8_t*)"Distance", strlen("Distance"));
                LCD_Write(LCD_Line_2, LCD_Character_10, (uint8_t*)"???.?", strlen("???.?"));
                LCD_Write(LCD_Line_2, LCD_Character_15, (uint8_t*)"CM", strlen("CM"));
                break;
            case Task_LCD_Request_Version:
                extern const char FW_VERSION[30];
                LCD_Write(LCD_Line_1, LCD_Character_5, (uint8_t*)"Version", strlen("Version"));
                LCD_Write(LCD_Line_2, LCD_Character_2, (uint8_t*)FW_VERSION, strlen(FW_VERSION)-3);
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
 * @brief Initializes LCD Task
 *
 * @param[in] void   : None
 *
 * @return true     : task initialized successfully
 * @return false    : task couldn't be initialized
 */
bool Task_LCD_Initialize( void )
{
    return xTaskCreate(vTask, TASK_NAME, TASK_STACK, NULL, TASK_PRIORITY, NULL) == pdPASS ? true : false;
}

/*
 * @brief Requests from LCD Task
 *
 * @param[in] Task_LCD_Request   : selected Task_LCD_Request
 *
 * @return true     : request pushed successfully
 * @return false    : request couldn't be pushed
 */
bool Task_LCD_Request( Task_LCD_Request_t Task_LCD_Request)
{
    Request_t Request;
    Request.request = Task_LCD_Request;
    return xQueueSend(QueueHandle, &Request, pdMS_TO_TICKS(0)) == pdTRUE ? true : false;
}

// #############################################################################
// #### Public Variable(s) #####################################################
// #############################################################################

// #############################################################################
// #### END OF FILE ############################################################
// #############################################################################

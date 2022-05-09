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
#include "stdio.h"

// #############################################################################
// #### Private Macro(s) #######################################################
// #############################################################################

#define TASK_NAME           ("Task_Bluetooth")
#define TASK_STACK          (800) // in words
#define TASK_PRIORITY       (configMAX_PRIORITIES-3)
#define TASK_PERIOD         (50) // in milli-seconds
#define TASK_QUEUE_LENGTH   (2) // in milli-seconds


#define RECEIVED_DATA_SIZE  50

// #############################################################################
// #### Private Type(s) ########################################################
// #############################################################################

typedef char Command_t[10];

typedef char CommandManual_t[200];

typedef void (*CommandCallback_t)( void * handle, int argc, char * argv[] );

typedef struct __attribute__((packed, aligned(1)))  CommandArgument_t
{
    int argc;
    char argv[10][10];
} CommandArgument_t;

typedef struct __attribute__((packed, aligned(1))) CommandStatus_t
{
    struct
    {
        char data[50];
        uint8_t length;
    } _received;
    bool _ready;
    bool _error;
} CommandStatus_t;

typedef struct __attribute__((packed, aligned(1))) CommandHandle_t
{
    const Command_t Command;
    const CommandManual_t CommandManual;
    const CommandCallback_t CommandCallback;
} CommandHandle_t;

// #############################################################################
// #### Private Method(s) Prototype ############################################
// #############################################################################

static void handleLED( void * handle, int argc, char * argv[] );
static void handleLCD( void * handle, int argc, char * argv[] );
static void handle7Segment( void * handle, int argc, char * argv[] );
static void handleUnknown( void * handle, int argc, char * argv[] );

// #############################################################################
// #### Private Variable(s) ####################################################
// #############################################################################

CommandHandle_t CommandHandle[] =
{
    {
     /* Command keyword */
     "led",
     /* Command Description */
     "led command usage"        // no comma
         "\n\t led off"         // no comma
         "\n\t led on"          // no comma
         "\n\t led blink"       // no comma
         "\n\t led increase"    // no comma
         "\n\t led decrease"    // no comma
         "\n\t led rgb",
     /* Command Handler */
     handleLED
    },
    {
     /* Command keyword */
     "lcd",
     /* Command Description */
     "lcd command usage"            // no comma
         "\n\t lcd off"             // no comma
         "\n\t lcd on"              // no comma
         "\n\t lcd empty"           // no comma
         "\n\t lcd loading"         // no comma
         "\n\t lcd date"            // no comma
         "\n\t lcd time"            // no comma
         "\n\t lcd bluetooth"       // no comma
         "\n\t lcd temperature"     // no comma
         "\n\t lcd distance"        // no comma
         "\n\t lcd version",
         /* Command Handler */
     handleLCD},
    {
     /* Command keyword */
     "segment",
     /* Command Description */
     "segment command usage"            // no comma
         "\n\t segment <number 0-9999>",
         /* Command Handler */
     handle7Segment
    },

    // TODO add more commands here

    {// Note: MUST be the last handle
     /* Command keyword */
     "", // any command not listed above will be unknown command
     /* Command Description */
     "Unknown Command",
     /* Command Handler */
     handleUnknown
    },
};

// #############################################################################
// #### Private Method(s) ######################################################
// #############################################################################

static void handleLED( void * handle, int argc, char * argv[] )
{
    bool displayManual = false;
    char * command[] =
    {
            "off",
            "on",
            "blink",
            "increase",
            "decrease",
            "rgb",
    };
    do
    {
        if (argc != 1)
        {
            displayManual = true;
            break;
        }
        for (int i = 0, c = 0; i < argc; ++i)
        {
            for (c = 0; c < sizeof(command) / sizeof(command[0]); ++c)
            {
                if ((strlen(command[c]) == strlen(argv[i]))
                 && (memcmp(command[c], argv[i], strlen(command[c])) == 0))
                {
                    switch (c)
                    {
                        case 0:
                            Task_LED_Request(Task_LED_Request_Off);
                            break;
                        case 1:
                            Task_LED_Request(Task_LED_Request_On);
                            break;
                        case 2:
                            Task_LED_Request(Task_LED_Request_Blink);
                            break;
                        case 3:
                            Task_LED_Request(Task_LED_Request_Increase);
                            break;
                        case 4:
                            Task_LED_Request(Task_LED_Request_Decrease);
                            break;
                        case 5:
                            Task_LED_Request(Task_LED_Request_RGB);
                            break;
                        default:
                            break;
                    }
                    break;
                }
            }
            if (c == (sizeof(command) / sizeof(command[0])))
            {
                displayManual = true;
                break;
            }
        }
    } while(0);
    if (displayManual)
    {
        CommandHandle_t * CommandHandle = handle;
        Bluetooth_Write((uint8_t*)CommandHandle->CommandManual, strlen(CommandHandle->CommandManual));
        Bluetooth_Write((uint8_t*)"\n", strlen("\n"));
    }
}

static void handleLCD( void * handle, int argc, char * argv[] )
{
    bool displayManual = false;
    char * command[] =
    {
            "off",
            "on",
            "empty",
            "loading",
            "date",
            "time",
            "bluetooth",
            "temperature",
            "distance",
            "version",
    };
    do
    {
        if (argc != 1)
        {
            displayManual = true;
            break;
        }
        for (int i = 0, c = 0; i < argc; ++i)
        {
            for (c = 0; c < sizeof(command) / sizeof(command[0]); ++c)
            {
                if ((strlen(command[c]) == strlen(argv[i]))
                 && (memcmp(command[c], argv[i], strlen(command[c])) == 0))
                {
                    switch (c)
                    {
                        case 0:
                            Task_LCD_Request(Task_LCD_Request_Off);
                            break;
                        case 1:
                            Task_LCD_Request(Task_LCD_Request_On);
                            break;
                        case 2:
                            Task_LCD_Request(Task_LCD_Request_Empty);
                            break;
                        case 3:
                            Task_LCD_Request(Task_LCD_Request_Loading);
                            break;
                        case 4:
                        case 5:
                            Task_LCD_Request(Task_LCD_Request_DateTime);
                            break;
                        case 6:
                            Task_LCD_Request(Task_LCD_Request_Bluetooth);
                            break;
                        case 7:
                            Task_LCD_Request(Task_LCD_Request_Temperature);
                            break;
                        case 8:
                            Task_LCD_Request(Task_LCD_Request_Distance);
                            break;
                        case 9:
                            Task_LCD_Request(Task_LCD_Request_Version);
                            break;
                        default:
                            break;
                    }
                    break;
                }
            }
            if (c == (sizeof(command) / sizeof(command[0])))
            {
                displayManual = true;
                break;
            }
        }
    } while(0);
    if (displayManual)
    {
        CommandHandle_t * CommandHandle = handle;
        Bluetooth_Write((uint8_t*)CommandHandle->CommandManual, strlen(CommandHandle->CommandManual));
        Bluetooth_Write((uint8_t*)"\n", strlen("\n"));
    }
}

static void handle7Segment( void * handle, int argc, char * argv[] )
{
    bool displayManual = false;
    int number;
    do
    {
        if (argc != 1)
        {
            displayManual = true;
            break;
        }
        if (sscanf(argv[0], "%d", &number) != 1)
        {
            displayManual = true;
            break;
        }
        char number_str[10];
        snprintf(number_str, sizeof(number_str), "%d", number);
        Bluetooth_Write((uint8_t*)"number read <", strlen("number read <"));
        Bluetooth_Write((uint8_t*)number_str, strlen(number_str));
        Bluetooth_Write((uint8_t*)">\n", strlen(">\n"));
    } while(0);
    if (displayManual)
    {
        CommandHandle_t * CommandHandle = handle;
        Bluetooth_Write((uint8_t*)CommandHandle->CommandManual, strlen(CommandHandle->CommandManual));
        Bluetooth_Write((uint8_t*)"\n", strlen("\n"));
    }
}

static void handleUnknown( void * handle, int argc, char * argv[] )
{
    bool displayManual = true; //false;
    if (displayManual)
    {
        CommandHandle_t * CommandHandle = handle;
        Bluetooth_Write((uint8_t*)CommandHandle->CommandManual, strlen(CommandHandle->CommandManual));
        Bluetooth_Write((uint8_t*)"\n", strlen("\n"));
    }
}

static void vTask( void *pvParameters )
{
    const TickType_t xFrequency = pdMS_TO_TICKS(TASK_PERIOD);
    TickType_t xLastWakeTime = xTaskGetTickCount();

    CommandStatus_t CommandStatus;
    CommandStatus._received.length = 0;
    CommandStatus._error = false;
    CommandStatus._ready = false;

    Bluetooth_Initialize();

    extern const char FW_VERSION[30];
    Bluetooth_Write((uint8_t*)"\nFirmware Version: ", strlen("\nFirmware Version: "));
    Bluetooth_Write((uint8_t*)FW_VERSION, strlen(FW_VERSION));
    Bluetooth_Write((uint8_t*)"\nFaresPCB Ready\n", strlen("\nFaresPCB Ready\n"));

    for( ;; )
    {
        do
        {
            do
            {
                if (CommandStatus._error) break;
                // In Case Of No Error
                if (sizeof(CommandStatus._received.data) - CommandStatus._received.length <= 0)
                {
                    Bluetooth_Write((uint8_t*)"\nCommand [Overflow]\n", strlen("\nCommand [Overflow]\n"));
                    Bluetooth_Write((uint8_t*)"\nPress Enter or write ';' to continue\n", strlen("\nPress Enter or write ';' to continue\n"));
                    CommandStatus._error = true;
                    break;
                }
                uint32_t length_read = Bluetooth_Read((uint8_t *)CommandStatus._received.data + CommandStatus._received.length, sizeof(CommandStatus._received.data) - CommandStatus._received.length);
                CommandStatus._received.length += length_read;
                if (length_read > 0)
                {
                    Bluetooth_Write((uint8_t*)CommandStatus._received.data + CommandStatus._received.length - length_read, length_read);
                }
            }
            while(0);
            do
            {
                if (!CommandStatus._error) break;
                // In Case Of Error
                CommandStatus._received.length = 0;
                uint32_t length_read = Bluetooth_Read((uint8_t *)CommandStatus._received.data + CommandStatus._received.length, sizeof(CommandStatus._received.data) - CommandStatus._received.length);
                CommandStatus._received.length += length_read;
                if (length_read > 0)
                {
                    // Do Nothing
                }
            }
            while(0);
            for (uint8_t i = 0; i < CommandStatus._received.length; ++i)
            {
                if (CommandStatus._received.data[i] == '\n' || CommandStatus._received.data[i] == '\r' || CommandStatus._received.data[i] == ';')
                {
                    CommandStatus._received.data[CommandStatus._received.length] = '\0';
                    CommandStatus._ready = true;
                    break;
                }
            }
            if (!CommandStatus._ready) break;
            if (CommandStatus._error)
            {
                CommandStatus._error = false;
                CommandStatus._ready = false;
                CommandStatus._received.length = 0;
                Bluetooth_Write((uint8_t*)"\nCommand [Ready]\n", strlen("\nCommand [Ready]\n"));
                break;
            }

            do
            {
                Command_t Command = "";
                CommandArgument_t CommandArgument;
                char * argv[sizeof(CommandArgument.argv) / sizeof(CommandArgument.argv[0])]; // wrapper for CommandArgument.argv
                sscanf(CommandStatus._received.data, "%s", &Command);
                CommandArgument.argc = 0;
                for( char format[50] = "%*s%s"; sscanf(CommandStatus._received.data, format, CommandArgument.argv[CommandArgument.argc]) == 1; CommandArgument.argc++)
                {
                    argv[CommandArgument.argc] = CommandArgument.argv[CommandArgument.argc];
                    uint32_t format_length = strlen(format);
                    format[format_length - 1] = '*';
                    format[format_length] = 's';
                    format[format_length + 1] = '\%';
                    format[format_length + 2] = 's';
                    format[format_length + 3] = '\0';
                }
                for (uint8_t i = 0; i < sizeof(CommandHandle) / sizeof(CommandHandle[0]); ++i)
                {
                    if( (memcmp(CommandHandle[i].Command, "", strlen(CommandHandle[i].Command)) == 0) // Unknown Command Reached
                    || ((strlen(CommandHandle[i].Command) == strlen(Command))
                    && (memcmp(CommandHandle[i].Command, Command, strlen(CommandHandle[i].Command)) == 0)))
                    {
                        CommandHandle[i].CommandCallback(&CommandHandle[i], CommandArgument.argc, argv);
                        CommandStatus._error = false;
                        CommandStatus._ready = false;
                        CommandStatus._received.length = 0;
                        break;
                    }
                }
                if (CommandStatus._ready)
                {
                    Bluetooth_Write((uint8_t*)"\nCommand Error\n", strlen("\nCommand Error\n"));
                    Bluetooth_Write((uint8_t*)"\nCommand Reset\n", strlen("\nCommand Reset\n"));
                    CommandStatus._error = false;
                    CommandStatus._ready = false;
                    CommandStatus._received.length = 0;
                }
            }
            while(0);
        }
        while(0);

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

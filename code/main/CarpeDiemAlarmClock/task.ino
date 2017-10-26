/*  CarpeDiem Alarm clock

    task.c

    FreeRTOS tasks
 */

#include <MapleFreeRTOS900.h>
#include "rtc.h"
#include "rgb.h"
#include "settings.h"
#include "command.h"

String serial_data;
bool serial_data_complete;
SemaphoreHandle_t semaphore = NULL;

void setup_tasks()
{
    semaphore = xSemaphoreCreateMutex();

    xTaskCreate(
        get_rtc_time,
        "get_time",
        configMINIMAL_STACK_SIZE,
        NULL,
        tskIDLE_PRIORITY + 2,
        NULL);

    xTaskCreate(
        show_time_on_rgb,
        "show_time",
        configMINIMAL_STACK_SIZE,
        NULL,
        tskIDLE_PRIORITY + 2,
        NULL);

    xTaskCreate(
        serial_command,
        "serial_command",
        configMINIMAL_STACK_SIZE + 128,
        NULL,
        tskIDLE_PRIORITY + 3,
        NULL);

    vTaskStartScheduler();
}

/* Handles serial commands */
static void serial_command(void *pvParameters)
{
    while(1)
    {
        while(serial_available())
        {
            char read_byte = (char)serial_read();
            serial_data += read_byte;

            if (read_byte == '\n')
            {
                serial_print_ln("Got command: " + serial_data);

                switch (serial_data[0])
                {
                    case 'S': // Set time as HH:MM -> S1245
                        rtc_set_hour_minute(
                            serial_data.substring(1, 3).toInt(),
                            serial_data.substring(3, 5).toInt()
                        );
                        break;

                    case 'T': // Print time as HH:MM:SS
                        rtc_serial_print();
                        break;

                    case 'Q': // Test
                        serial_print_ln("Hello!");
                        break;

                    default:
                        break;
                }

                serial_data = "";
            }
        }

        vTaskDelay(40);
    }
}

/* Updates rtc_time struct from RTC device */
static void get_rtc_time(void *pvParameters)
{
    while(1)
    {
        rtc_update();
        vTaskDelay(900);
    }
}


/* Displays current time on LED-rings and LED-strip */
static void show_time_on_rgb(void *pvParameters)
{
    while(1)
    {
        if(rtc_has_ticked())
        {
            strip_show_second(rtc_second(), 0, 0, 10);
        }

        vTaskDelay(100);
    }
}

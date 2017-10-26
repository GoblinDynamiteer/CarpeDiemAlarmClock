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

void setup_tasks()
{
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
        blinker,
        "blink_onboard_led",
        configMINIMAL_STACK_SIZE,
        NULL,
        tskIDLE_PRIORITY + 2,
        NULL);

    xTaskCreate(
        serial_command,
        "serial_command",
        configMINIMAL_STACK_SIZE,
        NULL,
        tskIDLE_PRIORITY + 4,
        NULL);

    vTaskStartScheduler();
}

/* Handles serial commands */
static void serial_command(void *pvParameters)
{
    while(1)
    {
        if(serial_data_complete)
        {
            while(serial_available())
            {
                serial_print(".");
                char read_byte = (char)serial_read();
                serial_data += read_byte;

                if (read_byte == '\n')
                {
                    serial_data_complete = false;
                    handle_command();
                }
            }
        }
    }
}

/* Updates rtc_time struct from RTC device */
static void get_rtc_time(void *pvParameters)
{
    while(1)
    {
        rtc_update();
        vTaskDelay(50);
    }
}

/* Updates rtc_time struct from RTC device */
static void blinker(void *pvParameters)
{
    while(1)
    {
        toggle_on_board_led();
        vTaskDelay(1000);
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

        vTaskDelay(20);
    }
}

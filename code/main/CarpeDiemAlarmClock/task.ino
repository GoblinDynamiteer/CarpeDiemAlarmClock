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

SemaphoreHandle_t semaphore_rtc = NULL; // RTC Device access
SemaphoreHandle_t semaphore_rgb = NULL; // NeoPixel access

void setup_tasks()
{
    semaphore_rtc = xSemaphoreCreateMutex();
    semaphore_rgb = xSemaphoreCreateMutex();

    xTaskCreate(
        time_handler,
        "time_handler",
        configMINIMAL_STACK_SIZE,
        NULL,
        tskIDLE_PRIORITY + 2,
        NULL);

    xTaskCreate(
        rgb_display_handler,
        "rgb_display_handler",
        configMINIMAL_STACK_SIZE,
        NULL,
        tskIDLE_PRIORITY + 2,
        NULL);

    xTaskCreate(
        rgb_updater,
        "rgb_updater",
        configMINIMAL_STACK_SIZE,
        NULL,
        tskIDLE_PRIORITY + 2,
        NULL);

    xTaskCreate(
        serial_command,
        "serial_command",
        configMINIMAL_STACK_SIZE + 128,
        NULL,
        tskIDLE_PRIORITY + 2,
        NULL);

    xTaskCreate(
        joystick_input,
        "joystick",
        configMINIMAL_STACK_SIZE,
        NULL,
        tskIDLE_PRIORITY + 2,
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
                switch (serial_data[0])
                {
                    case 'S': // Set time as HH:MM -> S1245
                        if(xSemaphoreTake(semaphore_rtc,
                            (TickType_t)200) == pdTRUE)
                        {
                            serial_print_ln("Setting RTC time to " +
                                serial_data.substring(1, 3) + ":" +
                                serial_data.substring(3, 5));
                            rtc_set_hour_minute(
                                serial_data.substring(1, 3).toInt(),
                                serial_data.substring(3, 5).toInt()
                            );
                            xSemaphoreGive(semaphore_rtc);
                        }
                        else
                        {
                            serial_print_ln("Error: Could not set time!");
                        }
                        break;

                    case 'D': // Cycle rgb show demos D1 : next D2: previous
                        if(xSemaphoreTake(semaphore_rgb,
                            (TickType_t)100) == pdTRUE)
                        {
                            bool dir = serial_data[1] == '1' ?
                                RGB_SHOW_NEXT : RGB_SHOW_PREV;
                            rgb_lightshows_select(dir);
                            xSemaphoreGive(semaphore_rgb);
                        }
                        break;

                    case 'T': // Print time as HH:MM:SS
                        if(xSemaphoreTake(semaphore_rtc,
                            (TickType_t)200) == pdTRUE)
                        {
                            serial_print_ln("Current RTC time: ");
                            rtc_serial_print();
                            xSemaphoreGive(semaphore_rtc);
                        }
                        else
                        {
                            serial_print_ln(
                                "Error: Unable to display current time!");
                        }
                        break;

                    case 'Q': // Test
                        serial_print_ln("Connected to " + device_name + "!");
                        break;

                    default:
                        break;
                }

                serial_data = "";
            }
        }

        vTaskDelay(100);
    }
}

/* Displays current time on LED-rings and LED-strip */
static void time_handler(void *pvParameters)
{
    while(1)
    {
        if(xSemaphoreTake(semaphore_rtc,
            (TickType_t)200) == pdTRUE)
        {
            rtc_update();

            if(rtc_second_changed())
            {
                if(xSemaphoreTake(semaphore_rgb,
                    (TickType_t)200) == pdTRUE)
                {
                    strip_show_second(rtc_second(), 0, 0, 10);

                    if(show_time_on_ring &&
                        (rtc_minute_changed() || force_time_display_update))
                    {
                        ring_show_minute(rtc_minute(), 0, 0, 10);
                        ring_show_hour(rtc_hour(), rtc_minute(), 0, 10, 0);
                        force_time_display_update = false;
                    }

                    xSemaphoreGive(semaphore_rgb);
                }
            }

            xSemaphoreGive(semaphore_rtc);
        }

        vTaskDelay(100);
    }
}

/* Displays current time on LED-rings and LED-strip */
static void rgb_display_handler(void *pvParameters)
{
    while(1)
    {
        if(xSemaphoreTake(semaphore_rgb,
            (TickType_t)300) == pdTRUE)
        {
            if(!status_rgb) // Disable all LEDs
            {
                rgb_all_led_off();

                while(!status_rgb)
                {
                    vTaskDelay(100);
                }

                /* Force clock display update if clock is enabled */
                force_time_display_update = show_time_on_ring;
            }

            strip_set_status_bits();

            if(show_time_on_ring)
            {
                xSemaphoreGive(semaphore_rgb);
            }

            else
            {
                rgb_show_func[current_rgb_show_mode]();
                xSemaphoreGive(semaphore_rgb);
                vTaskDelay(rgb_show_delay[current_rgb_show_mode]);
            }
        }
    }
}

/* Updates RGBs if needed */
static void rgb_updater(void *pvParameters)
{
    while(1)
    {
        if(xSemaphoreTake(semaphore_rgb,
            (TickType_t)100) == pdTRUE && status_rgb)
        {
            rgb_update();
            xSemaphoreGive(semaphore_rgb);
        }

        else
        {
            vTaskDelay(100);
        }
    }
}

/* Handle joystick input */
static void joystick_input(void *pvParameters)
{
    while(1)
    {
        int y = analogRead(JOYSTICK_PIN_Y);
        int x = analogRead(JOYSTICK_PIN_X);
        int sw = !digitalRead(JOYSTICK_PIN_SW);

        /* Joystick left -- toggle alarm */
        if (analogRead(JOYSTICK_PIN_X) < JOYSTICK_THRESHOLD_LEFT)
        {
            status_toggle_alarm();
            while(analogRead(JOYSTICK_PIN_X) < JOYSTICK_THRESHOLD_LEFT)
            {
                vTaskDelay(1);
            }
        }

        /* Joystick left -- toggle buzzer */
        if (analogRead(JOYSTICK_PIN_X) > JOYSTICK_THRESHOLD_RIGHT)
        {
            status_toggle_buzzer();
            while(analogRead(JOYSTICK_PIN_X) > JOYSTICK_THRESHOLD_RIGHT)
            {
                vTaskDelay(1);
            }
        }

        /* Joystick up -- toggle rgb */
        if (analogRead(JOYSTICK_PIN_Y) < JOYSTICK_THRESHOLD_UP)
        {
            status_toggle_rgb();
            while(analogRead(JOYSTICK_PIN_Y) < JOYSTICK_THRESHOLD_UP)
            {
                vTaskDelay(1);
            }
        }

        /* Joystick down -- cycle rgb show modes and clock display */
        if (analogRead(JOYSTICK_PIN_Y) > JOYSTICK_THRESHOLD_DOWN)
        {
            rgb_lightshows_select(RGB_SHOW_NEXT);
            while(analogRead(JOYSTICK_PIN_Y) > JOYSTICK_THRESHOLD_DOWN)
            {
                vTaskDelay(1);
            }
        }

        vTaskDelay(100);
    }
}

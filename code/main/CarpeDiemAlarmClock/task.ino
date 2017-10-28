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
        alarm_handler,
        "alarm_handler",
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
        configMINIMAL_STACK_SIZE,
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

                            rgb_force_clock_update = show_time_on_ring;
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
                            serial_print_ln("Cycling Demo!");
                        }
                        break;

                    case 'R': // Reset status flags
                            reset_status_flags();
                            serial_print_ln("Reset status flags!");
                        break;


                    case 'T': // Print time as HH:MM:SS
                        if(xSemaphoreTake(semaphore_rtc,
                            (TickType_t)200) == pdTRUE)
                        {
                            serial_print("Current RTC time: ");
                            rtc_serial_print();
                            xSemaphoreGive(semaphore_rtc);
                        }
                        else
                        {
                            serial_print_ln(
                                "Error: Unable to display current time!");
                        }
                        break;

                    case 'Q': // Query -- Show status
                        serial_print_ln("Connected to " + device_name + "!");
                        if(xSemaphoreTake(semaphore_rtc,
                            (TickType_t)200) == pdTRUE)
                        {
                            serial_print("Current RTC time: ");
                            rtc_serial_print();
                            xSemaphoreGive(semaphore_rtc);
                        }
                        serial_print_ln(status_rgb ?
                            "RGB ON" : "RGB OFF");
                        serial_print_ln(show_time_on_ring ?
                            "CLOCK ON" : "CLOCK OFF");
                        serial_print_ln(status_buzzer ?
                            "BUZZER ON" : "BUZZER OFF");
                        serial_print_ln(status_alarm ?
                            "ALARM ON" : "ALARM OFF");
                        serial_print_ln(serial_debug_output ?
                            "SERIAL DEBUG ON" : "SERIAL DEBUG OFF");
                        serial_print_ln("------------------------");
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
                    rgb_strip_show_second(rtc_second(), 0, 0, 10);

                    if(show_time_on_ring &&
                        (rtc_minute_changed() || rgb_force_clock_update))
                    {
                        rgb_ring_show_clock(
                            rtc_hour(),
                            rtc_minute(),
                            rgb_current_clock_mode);

                        rgb_force_clock_update = false;
                    }

                    xSemaphoreGive(semaphore_rgb);
                }
            }

            xSemaphoreGive(semaphore_rtc);
        }

        vTaskDelay(100);
    }
}

/* BEEP BEEP BEEP ! */
static void alarm_handler(void *pvParameters)
{
    while(1)
    {
        buzzer_on(60000);
        vTaskDelay(400);
        buzzer_off();
        vTaskDelay(3000);
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

                if(serial_debug_output)
                    serial_print_ln("rgb_handler: all led off");

                while(!status_rgb)
                {
                    vTaskDelay(100);
                }

                if(serial_debug_output)
                    serial_print_ln("rgb_handler: passed status_rgb");

                /* Force clock display update if clock is enabled */
                rgb_force_clock_update = show_time_on_ring;
            }

            rgb_strip_set_status_bits();

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

        else
        {
            if(serial_debug_output)
                serial_print_ln("rgb_display_handler: no sema!");
            vTaskDelay(500);
        }
    }
}

/* Updates RGBs if needed */
static void rgb_updater(void *pvParameters)
{
    while(1)
    {
        if(status_rgb)
        {
            if(xSemaphoreTake(semaphore_rgb,
                (TickType_t)1000) == pdTRUE)
            {
                rgb_update();
                xSemaphoreGive(semaphore_rgb);
            }

            else
            {
                if(serial_debug_output)
                    serial_print_ln("rgb_updater: no sema!");
            }
        }

        else
        {
            vTaskDelay(500);  //ZZZZ
        }

    }
}

/* Handle joystick input */
static void joystick_input(void *pvParameters)
{
    while(1)
    {
        /* Joystick left -- toggle alarm */
        if (analogRead(JOYSTICK_PIN_X) < JOYSTICK_THRESHOLD_LEFT)
        {
            status_toggle_alarm();
            while(analogRead(JOYSTICK_PIN_X) < JOYSTICK_THRESHOLD_LEFT)
            {
                vTaskDelay(1);
            }

            if(serial_debug_output)
                serial_print_ln("joystick: toggled status_alarm");
        }

        /* Joystick right -- toggle buzzer */
        if (analogRead(JOYSTICK_PIN_X) > JOYSTICK_THRESHOLD_RIGHT)
        {
            status_toggle_buzzer();
            while(analogRead(JOYSTICK_PIN_X) > JOYSTICK_THRESHOLD_RIGHT)
            {
                vTaskDelay(1);
            }

            if(serial_debug_output)
                serial_print_ln("joystick: toggled status_buzzer");
        }

        /* Joystick up -- toggle rgb */
        if (analogRead(JOYSTICK_PIN_Y) < JOYSTICK_THRESHOLD_UP)
        {
            status_toggle_rgb();
            while(analogRead(JOYSTICK_PIN_Y) < JOYSTICK_THRESHOLD_UP)
            {
                vTaskDelay(1);
            }

            if(serial_debug_output)
                serial_print_ln("joystick: toggled status_rgb");
        }

        /* Joystick down -- cycle rgb show modes and clock display */
        if (analogRead(JOYSTICK_PIN_Y) > JOYSTICK_THRESHOLD_DOWN)
        {
            rgb_lightshows_select(RGB_SHOW_NEXT);
            while(analogRead(JOYSTICK_PIN_Y) > JOYSTICK_THRESHOLD_DOWN)
            {
                vTaskDelay(1);
            }

            if(serial_debug_output)
                serial_print_ln("joystick: cycled show");
        }

        /* Joystick button pressed --
            set alarm (click) / time (2 second press) */
        if (!digitalRead(JOYSTICK_PIN_SW))
        {
            unsigned long press_timer = 0;
            bool set_alarm = true;

            if(serial_debug_output)
                serial_print_ln("joystick: button press");

            while(!digitalRead(JOYSTICK_PIN_SW))
            {
                bool blink_on = true;

                if(press_timer++ > 2000)
                {
                    if(xSemaphoreTake(semaphore_rgb,
                        (TickType_t)1500) == pdTRUE)
                    {
                        rgb_strip_set_color(blink_on ? 20 : 0, 0, 0);
                        xSemaphoreGive(semaphore_rgb);
                        blink_on = !blink_on;
                        vTaskDelay(200);
                    }

                    set_alarm = false;
                }

                vTaskDelay(1);
            }

            if(serial_debug_output)
                serial_print_ln(set_alarm ?
                    "joystick: set alarm" : "joystick: set clock");

            /* Control pixel location on ring to set hour / minute */
            if(xSemaphoreTake(semaphore_rgb,
                (TickType_t)1500) == pdTRUE)
            {
                if(serial_debug_output)
                    serial_print_ln("joystick: took rgb sema");

                rgb_all_led_off();
                rgb_strip_set_color(0, 20, 0);

                uint8_t hour_pixel = get_pixel_with_joystick(0, 20, 0); //CONVERT

                rgb_all_led_off();
                rgb_strip_set_color(0, 0, 20);

                uint8_t minute_pixel = get_pixel_with_joystick(0, 0, 20); //CONVERT

                uint8_t hour = (uint8_t)(hour_pixel / 2);
                uint8_t minute = (uint8_t)(minute_pixel * 2.5);

                rgb_force_clock_update = true;

                xSemaphoreGive(semaphore_rgb);
                while(!joystick_button_released());

                if(xSemaphoreTake(semaphore_rtc,
                    (TickType_t)1500) == pdTRUE)
                {
                    if(set_alarm)
                    {
                        if(serial_debug_output)
                            serial_print_ln("joystick: alarm set " +
                                String(hour) + ":" + String(minute));
                        // BUILD
                    }

                    else
                    {
                        rtc_set_hour_minute(hour, minute);
                        serial_print_ln("joystick: clock set " +
                            String(hour) + ":" + String(minute));
                    }

                    xSemaphoreGive(semaphore_rtc);
                }
            }

        }

        vTaskDelay(100);
    }
}

/* Make sure the button is released */
bool joystick_button_released()
{
    uint16_t counter = 0;
    serial_print_ln("joystick counter!");
    while(digitalRead(JOYSTICK_PIN_SW) == 0)
    {
        vTaskDelay(1);
    }

    serial_print_ln("joystick counting!");
    for(uint16_t i = 0; i < 100; i++)
    {
        if(digitalRead(JOYSTICK_PIN_SW) == 1)
        {
            counter++;
        }
    }
    serial_print_ln("joystick counter: " + String(counter));
    return (counter == 100);
}

/* Select hour or minute on rgb-rings with joystick! */
uint8_t get_pixel_with_joystick(uint8_t red, uint8_t green, uint8_t blue)
{
    uint8_t pixel_index = 0;
    rgb_ring_set_one_pixel(pixel_index, red, green, blue, true);
    while(!joystick_button_released());

    while(1)
    {
        if (analogRead(JOYSTICK_PIN_X) < JOYSTICK_THRESHOLD_LEFT)
        {
            pixel_index = RGB_RING_NEXT_PIXEL(pixel_index);
            rgb_ring_set_one_pixel(pixel_index, red, green, blue, true);
            vTaskDelay(300);
        }

        if (analogRead(JOYSTICK_PIN_X) > JOYSTICK_THRESHOLD_RIGHT)
        {
            pixel_index = RGB_RING_PREV_PIXEL(pixel_index);
            rgb_ring_set_one_pixel(pixel_index, red, green, blue, true);
            vTaskDelay(300);
        }

        if (!digitalRead(JOYSTICK_PIN_SW))
        {
            while(!joystick_button_released());
            if(serial_debug_output)
                serial_print_ln("joystick set: returning pixel " +
                    String(pixel_index));
            return pixel_index;
        }
    }

    vTaskDelay(40);
}

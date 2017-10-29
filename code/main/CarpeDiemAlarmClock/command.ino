/*  CarpeDiem Alarm clock

    command.ino

    Handles serial commands
 */

#include <MapleFreeRTOS900.h>
#include "rtc.h"
#include "rgb.h"
#include "settings.h"
#include "command.h"

extern SemaphoreHandle_t semaphore_rtc;
extern SemaphoreHandle_t semaphore_rgb;
extern void rgb_lightshows_select(bool);

void command_init()
{
    serial_data.reserve(SETTING_SERIAL_DATA_COMMAND_SIZE);
    serial_data_complete = true;
}

void handle_commands()
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

                case 'A': // Set alarm as HH:MM -> A1245
                    if(xSemaphoreTake(semaphore_rtc,
                        (TickType_t)200) == pdTRUE)
                    {
                        serial_print_ln("Setting alarm time to " +
                            serial_data.substring(1, 3) + ":" +
                            serial_data.substring(3, 5));
                        rtc_set_alarm(
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
                        serial_print_ln("Time to alarm: " +
                            String(rtc_time_to_alarm()));
                        xSemaphoreGive(semaphore_rtc);
                    }
                    serial_print_ln(status_rgb ?
                        "RGB ON" : "RGB OFF");
                    serial_print_ln(status_buzzer ?
                        "BUZZER ON" : "BUZZER OFF");
                    serial_print_ln(status_alarm ?
                        "ALARM ON" : "ALARM OFF");
                    serial_print_ln(rtc_alarm_countdown_running ?
                        "ALARM COUNTDOWN ON" : "ALARM COUNTDOWN OFF");
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
}

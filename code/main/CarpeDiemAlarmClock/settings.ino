/*  CarpeDiem Alarm clock

    rtc.c

    RTC Functions
    Default I2C Pins:
        PB06 SCL
        PB07 SDA
 */

#include "settings.h"

bool status_change[3] =
{
    false,      // STATUS_ALARM
    false,      // STATUS_BUZZER
    false       // STATUS_RGB
};


void on_board_led_init()
{
    pinMode(SETTING_ON_BOARD_LED_PIN, OUTPUT);
}

void joystick_init()
{
    pinMode(JOYSTICK_PIN_SW, INPUT_PULLUP);
}

void serial_begin()
{
    #ifdef SERIAL_0
        Serial.begin(SETTINGS_BAUD_RATE);
    #endif

    #ifdef SERIAL_1
        Serial1.begin(SETTINGS_BAUD_RATE);
    #endif

    #ifdef SERIAL_2
        Serial2.begin(SETTINGS_BAUD_RATE);
    #endif

    #ifdef SERIAL_3
        Serial3.begin(SETTINGS_BAUD_RATE);
    #endif

    #ifdef SERIAL_DEBUG_OUTPUT_ENABLE
        serial_debug_output = true;
    #else
        serial_debug_output = false;
    #endif
}

void status_toggle_alarm()
{
    status_alarm = !status_alarm;
    status_change[STATUS_ALARM] = true;

    if(serial_debug_output)
        serial_print_ln(status_alarm ?
            "alarm_status: on" : "alarm_status: off");
}

void status_toggle_rgb()
{
    status_rgb = !status_rgb;
    status_change[STATUS_RGB] = true;

    if(serial_debug_output)
        serial_print_ln(status_rgb ?
            "rgb_status: on" : "rgb_status: off");
}

void status_toggle_buzzer()
{
    status_buzzer = !status_buzzer;
    status_change[STATUS_BUZZER] = true;

    if(!status_buzzer)
    {
        buzzer_off();
    }

    if(serial_debug_output)
        serial_print_ln(status_buzzer ?
            "buzzer_status: on" : "buzzer_status: off");
}

bool status_changed(uint8_t type)
{
    if(status_change[type])
    {
        if(serial_debug_output)
            serial_print_ln("status_changed request!");

        status_change[type] = false;
        return true;
    }

    return false;
}

/* Toggles onboard LED */
void toggle_on_board_led()
{
    static bool on = true;
    digitalWrite(SETTING_ON_BOARD_LED_PIN, on);
    on = !on;
}

void reset_status_flags()
{
    status_alarm = true;
    status_alarm_running = false;
    status_buzzer = true;
    status_rgb = true;
    show_time_on_ring = true;
    current_rgb_show_mode = 0;
}

void toggle_on_board_led_n_times(uint8_t n)
{
    if(serial_debug_output)
        serial_print_ln("onboard led: toggling " + String(n) + " times");

    for (size_t i = 0; i < n; i++)
    {
        toggle_on_board_led();
        delay(100);
    }
}

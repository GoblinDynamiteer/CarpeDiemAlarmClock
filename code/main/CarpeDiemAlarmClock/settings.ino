/*  CarpeDiem Alarm clock

    rtc.c

    RTC Functions
    Default I2C Pins:
        PB06 SCL
        PB07 SDA
 */
#include "settings.h"

void on_board_led_init()
{
    pinMode(SETTING_ON_BOARD_LED_PIN, OUTPUT);
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
}

/* Toggles onboard LED */
void toggle_on_board_led()
{
    static bool on = true;
    digitalWrite(SETTING_ON_BOARD_LED_PIN, on);
    on = !on;
}

void toggle_on_board_led_n_times(uint8_t n)
{
    for (size_t i = 0; i < n; i++)
    {
        toggle_on_board_led();
        delay(100);
    }

}

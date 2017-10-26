/*  CarpeDiem Alarm clock

    rtc.c

    RTC Functions
    Default I2C Pins:
        PB06 SCL
        PB07 SDA
 */

void on_board_led_init()
{
    pinMode(PC13, OUTPUT);
}

void toggle_on_board_led()
{
    static bool on = true;
    digitalWrite(PC13, on);
    on = !on;
}

/*  CarpeDiem Alarm clock

    https://github.com/GoblinDynamiteer/CarpeDiemAlarmClock
 */

void setup()
{
    rgb_init();
    rtc_init();
}

void loop()
{
    //ring_random_blink(1000);
    sound_beep(300);
    delay(1000);
}

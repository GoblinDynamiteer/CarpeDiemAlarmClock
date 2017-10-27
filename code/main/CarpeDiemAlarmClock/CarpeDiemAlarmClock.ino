/*  CarpeDiem Alarm clock

    https://github.com/GoblinDynamiteer/CarpeDiemAlarmClock
 */

#include <MapleFreeRTOS900.h>
#include "rgb.h"
#include "rtc.h"
#include "settings.h"

void setup()
{
    status_alarm = true;
    status_buzzer = true;
    status_rgb = true;

    serial_begin();
    rtc_init();
    rgb_init();
    joystick_init();
    setup_tasks();
}

void loop()
{
}

/*  CarpeDiem Alarm clock

    https://github.com/GoblinDynamiteer/CarpeDiemAlarmClock
 */

#include <MapleFreeRTOS900.h>
#include "rgb.h"
#include "rtc.h"
#include "settings.h"

void setup()
{

    serial_begin();
    rtc_init();
    rgb_init();
    setup_tasks();
}

void loop()
{
}

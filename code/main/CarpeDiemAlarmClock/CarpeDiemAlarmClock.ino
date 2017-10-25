/*  CarpeDiem Alarm clock

    https://github.com/GoblinDynamiteer/CarpeDiemAlarmClock
 */

//#include <MapleFreeRTOS900.h>
#include "rgb.h"
#include "rtc.h"
#include "settings.h"

void setup()
{
    rgb_init();
    rtc_init();
    Serial2.begin(9600);
    rtc_set(30, 20, 12, 4, 26, 10, 17);
}

void loop()
{
    if(rtc_has_ticked())
    {
        strip_show_second(rtc_second());
    }
}

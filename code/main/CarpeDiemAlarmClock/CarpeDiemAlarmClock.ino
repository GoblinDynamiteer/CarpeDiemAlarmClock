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
    rtc_set(30, 20, 12, 4, 26, 10, 17);
    Serial2.begin(9600);
    on_board_led_init();
}

void loop()
{
    if(rtc_has_ticked())
    {
        serial_print("Tick!\n");
        strip_show_second(rtc_second(), 0, 0, 10);
        toggle_on_board_led();
    }
    serial_print(".");
    delay(20);
}

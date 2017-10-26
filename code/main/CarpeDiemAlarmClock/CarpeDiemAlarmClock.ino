/*  CarpeDiem Alarm clock

    https://github.com/GoblinDynamiteer/CarpeDiemAlarmClock
 */

#include <MapleFreeRTOS900.h>
#include "rgb.h"
#include "rtc.h"
#include "settings.h"

void setup()
{
    rgb_init();
    rtc_init();
    command_init();

    rtc_set(30, 20, 12, 4, 26, 10, 17);
    Serial2.begin(SETTINGS_BAUD_RATE);
    delay(100);

    setup_tasks();
    vTaskStartScheduler();
}

void loop()
{
}

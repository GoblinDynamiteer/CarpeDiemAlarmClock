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
    Serial2.begin(SETTINGS_BAUD_RATE);
    toggle_on_board_led_n_times(10); // Debug
    setup_tasks();
    vTaskStartScheduler();
}

void loop()
{
}

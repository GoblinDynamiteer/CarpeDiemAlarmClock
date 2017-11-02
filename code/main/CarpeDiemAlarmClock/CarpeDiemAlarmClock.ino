/*  CarpeDiem Alarm clock
    Project for course "Realtidssystem"
    Mjukvaruutvecklare inbyggda system
    MÖLK Utbildning 2017

    Project members:
    Dylan Saleh
    Johan Kämpe
    Pay-Shin Quach
    Stefan Ekström

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
    buzzer_init();
    setup_tasks(); // Set up and start FreeRTOS tasks
}

/* Should not get here */
void loop()
{
}

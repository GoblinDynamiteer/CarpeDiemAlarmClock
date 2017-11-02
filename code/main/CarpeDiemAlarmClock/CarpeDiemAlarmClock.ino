/*  CarpeDiem Alarm clock
    Project for course "Realtidssystem"
    Mjukvaruutvecklare inbyggda system
    M�LK Utbildning 2017

    Project members:
    Dylan Saleh
    Johan K�mpe
    Pay-Shin Quach
    Stefan Ekstr�m

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

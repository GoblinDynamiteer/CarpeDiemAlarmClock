/*  CarpeDiem Alarm clock

    buzzer.ino

    Sound generation with buzzer
 */

#include "settings.h"

void buzzer_init()
{
   pinMode(BUZZER_PIN, OUTPUT);
}

void buzzer_on()
{
   digitalWrite(BUZZER_PIN, 1);
}

void buzzer_off()
{
    digitalWrite(BUZZER_PIN, 0);
}

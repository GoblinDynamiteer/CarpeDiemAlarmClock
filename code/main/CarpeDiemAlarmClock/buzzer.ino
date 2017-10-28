/*  CarpeDiem Alarm clock

    buzzer.ino

    Sound generation with buzzer
 */

#include "settings.h"

void buzzer_init()
{
   pinMode(BUZZER_PIN, OUTPUT);
}

void buzzer_on(uint16_t frequency)
{
   //analogWrite(BUZZER_PIN, frequency);
   pwmWrite(BUZZER_PIN, frequency);
}

void buzzer_off()
{
    //analogWrite(BUZZER_PIN, 0);
    pwmWrite(BUZZER_PIN, 0);
}

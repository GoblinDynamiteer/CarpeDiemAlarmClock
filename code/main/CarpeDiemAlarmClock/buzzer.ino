/*  CarpeDiem Alarm clock

    buzzer.ino

    Sound generation with buzzer
 */

#include "settings.h"

/* Set pin mode for buzzer */
void buzzer_init()
{
   pinMode(BUZZER_PIN, OUTPUT);
}

/* Turn buzzer on */
void buzzer_on()
{
   digitalWrite(BUZZER_PIN, 1);
}

/* Turn buzzer off */
void buzzer_off()
{
    digitalWrite(BUZZER_PIN, 0);
}

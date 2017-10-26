/*  CarpeDiem Alarm clock

    sound.c

    Sound generation with buzzer
 */

#define SOUND_BUZZER_PIN PA1

void sound_beep(int on_time)
{
    tone(SOUND_BUZZER_PIN, 1000);
    delay(on_time);
    noTone(SOUND_BUZZER_PIN);
}

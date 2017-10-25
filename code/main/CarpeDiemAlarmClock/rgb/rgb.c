/*  CarpeDiem Alarm clock

    rtc.c

    LED-strip and LED-Ring Functions
 */

#include <NeoMaple.h>
#include "rgb.h"

NeoMaple ring = NeoMaple(NUM_LEDS, NEO_GRB + NEO_KHZ800);

void rgb_init()
{
    ring.begin();
}

void ring_blink_mode(int blink_delay, int red, int green, int blue)
{
    for (int i = 0; i <NUM_LEDS; i++)
    {
        ledring.setPixelColor (i, red, green, blue);
    }

    ledring.show();
    delay(blink_delay);

    for (int i = 0; i <NUM_LEDS; i++)
    {
        ledring.setPixelColor (i, 0, 0, 0);
    }

    ledring.show();
    delay(blink_delay);
}

/* Fade LED-ring color up and down, one cycle */
void ring_fade_mode(int blink_delay)
{
    for (int fade_led = 0; fade_led < 120; fade_led++)
    {
        for (int i = 0; i < 24; i++)
        {
            ring.setPixelColor (i, 0, 0, fade_led);
        }
        ring.show();
        delay(blink_delay);
    }

    for (int fade_led = 120; fade_led > 0; fade_led--)
    {
        for (int i = 0; i < 24; i++)
        {
            ring.setPixelColor (i, 0, 0, fade_led);
        }

        ring.show();
        delay(blink_delay);
    }
}

/* Set LED-ring color */
void ring_steady_light(int red, int green, int blue)
{
    for (int i = 0; i < NUM_LEDS; i++)
    {
        ledring.setPixelColor (i, red, green, blue);
    }

    ledring.show();
}

/* Blink LED-ring with random color */
void ring_random_blink(int delay)
{
    int red = random(100);
    int green = random(100);
    int blue = random(100);
    ring_blink_mode(delay, red, green, blue);
}

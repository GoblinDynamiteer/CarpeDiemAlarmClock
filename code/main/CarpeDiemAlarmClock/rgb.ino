/*  CarpeDiem Alarm clock

    rtc.c

    LED-strip and LED-Ring Functions
 */


#include <NeoMaple.h>

#define RING_NUM_LEDS 24
#define STRIP_NUM_LEDS 8

enum{RED, GREEN, BLUE};

NeoMaple ring = NeoMaple(RING_NUM_LEDS, NEO_GRB + NEO_KHZ800);

void rgb_init()
{
    ring.begin();

    for (int i = 0; i < RING_NUM_LEDS; i++)
    {
        ring.setPixelColor (i, 0, 0, 0);
    }

    ring.show();
}

void ring_blink_mode(
    int blink_delay, int red, int green, int blue)
{
    for (int i = 0; i < RING_NUM_LEDS; i++)
    {
        ring.setPixelColor (i, red, green, blue);
    }

    ring.show();
    delay(blink_delay);

    for (int i = 0; i < RING_NUM_LEDS; i++)
    {
        ring.setPixelColor (i, 0, 0, 0);
    }

    ring.show();
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
    for (int i = 0; i < RING_NUM_LEDS; i++)
    {
        ring.setPixelColor (i, red, green, blue);
    }

    ring.show();
}

/* Blink LED-ring with random color */
void ring_random_blink(int delay)
{
    int red = random(100);
    int green = random(100);
    int blue = random(100);
    ring_blink_mode(delay, red, green, blue);
}

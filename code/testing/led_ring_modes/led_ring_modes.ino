/*  LED ring strenght test
NeoPixel Led-Ring with STM32 devboard

https://github.com/fergul/NeoMaple
*/

// #include <NeoMaple.h>
#include <Adafruit_NeoPixel.h>
#define NUM_LEDS 24
#define pin 6

/* Default data-pin is PA0 */

Adafruit_NeoPixel ledring = Adafruit_NeoPixel(NUM_LEDS, pin, NEO_GRB + NEO_KHZ800);

//NeoMaple ledring = NeoMaple(NUM_LEDS, NEO_GRB + NEO_KHZ800);

void setup()
{
    ledring.begin();
}

void loop()
{
    fade_mode(10);
    blink_mode(1000, 50,0,0);
    steady_light_mode(100,100,100);
    random_blink(200);
}

void fade_mode(int blink_delay)
{
    for (int fade_led = 0; fade_led < 100; fade_led++)
    {
        for (int i = 0; i < 24; i++)
        {
            ledring.setPixelColor (i, fade_led, fade_led, fade_led);
        }
        ledring.show();
        delay(blink_delay);
    }
    for (int fade_led = 100; fade_led > 0; fade_led--)
    {
        for (int i = 0; i < 24; i++)
        {
            ledring.setPixelColor (i, fade_led, fade_led, fade_led);
        }
        ledring.show();
        delay(blink_delay);
    }
}

void blink_mode(int blink_delay, int red, int green, int blue)
{
    for (int i = 0; i <NUM_LEDS; i++)
    {
        ledring.setPixelColor (i, red, green, blue);
    }
    ledring.show();
    delay(blink_delay);
    /* code */


    for (int i = 0; i <NUM_LEDS; i++)
    {
        ledring.setPixelColor (i, 0, 0, 0);
    }
    ledring.show();
    delay(blink_delay);
}
void steady_light_mode(int red, int green, int blue)
{
    for (int i = 0; i < NUM_LEDS; i++)
    {
        ledring.setPixelColor (i, red, green, blue);
    }
    ledring.show();

}
void random_blink (int delay)
{
    int red = random(100);
    int green = random (100);
    int blue = random (100);
    blink_mode (delay, red, green, blue);
}

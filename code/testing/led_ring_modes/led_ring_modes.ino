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
    wake_up_mode_blinker(20, 1);
}

void wake_up_mode_blinker(int blink_delay, int pwm_strenght)
{
    for (int fade_led = 1; fade_led < 100; fade_led++) 
    {
        for (int i = 1; i < 24; i++)
        {
          ledring.setPixelColor (i, fade_led, fade_led, fade_led);
        }
        ledring.show();
        delay(blink_delay);        
    }
}
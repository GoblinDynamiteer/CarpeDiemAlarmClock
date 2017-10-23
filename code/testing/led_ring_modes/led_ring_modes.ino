/*  LED ring strenght test
    NeoPixel Led-Ring with STM32 devboard

    https://github.com/fergul/NeoMaple
 */

#include <NeoMaple.h>

#define NUM_LEDS 24

/* Default data-pin is PA0 */
NeoMaple ledring = NeoMaple(NUM_LEDS, NEO_GRB + NEO_KHZ800);

void setup()
{
   ledring.begin();

   for (int i = 0; i < 5; i++)
   {
       ledring.setPixelColor(i, 0, 0, 0);
   }

   ledring.show();
}

void loop()
{
    wake_up_mode_blinker(70, 10);
}

void wake_up_mode_blinker(int blink_delay, int pwm_strenght)
{
    for (int i = 0; i < NUM_LEDS; i++)
    {
        ledring.setPixelColor(
            i, pwm_strenght, pwm_strenght, pwm_strenght);
    }

    ledring.show();
    delay(blink_delay);

    for (int i = 0; i < NUM_LEDS; i++)
    {
        ledring.setPixelColor(
            i, 0, 0, 0);
    }

    ledring.show();
    delay(blink_delay);
}

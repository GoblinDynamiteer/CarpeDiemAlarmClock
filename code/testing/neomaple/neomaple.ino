/*  Test with NeoMaple lib
    NeoPixel Led-Ring with STM32 devboard

    https://github.com/fergul/NeoMaple
 */

#include <NeoMaple.h>

#define NUM_LEDS 16

NeoMaple ledring = NeoMaple(NUM_LEDS, NEO_GRB + NEO_KHZ800);

void setup()
{
   ledring.begin();
   ledring.show();
   ledring.setBrightness(40);
}

void loop()
{
   for (int i = 0; i < NUM_LEDS; i++)
   {
        ledring.setPixelColor(i, ledring.Color(0, 150, 0));
        ledring.show();
   }
}

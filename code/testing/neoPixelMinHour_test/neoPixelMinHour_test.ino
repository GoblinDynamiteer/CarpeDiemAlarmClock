#include <Adafruit_NeoPixel.h>

/* To show minute, every LED represents 5 minutes and if all the 12 LEDS
 * are lit, then 1 hour have past.
 */

const byte neoRingLittlePin = 12;
const byte neoRingLittle = 12;
byte neoBright = 10;

Adafruit_NeoPixel ringLittle = Adafruit_NeoPixel(neoRingLittle, neoRingLittlePin, NEO_RGB);

void setup()
{
  ringLittle.begin();
  ringLittle.setBrightness(neoBright);
}

void loop() 
{
  for(int i = 0; i < 12; i++)
  {
    showMinute(i);
    delay(60000*5);
  }
}

int showMinute(int minute)
{
  for(int i = 0; i < 12; i++) 
  {
    if(minute >= i)
    {
    ringLittle.setPixelColor(i, ringLittle.Color(10, 118, 200));
    }
    else
    {
      //ringLittle.setPixelColor(i, ringLittle.Color(100, 0, 100));
      ringLittle.setPixelColor(i, ringLittle.Color(0, 0, 0));
    }
  }
  ringLittle.show();
}


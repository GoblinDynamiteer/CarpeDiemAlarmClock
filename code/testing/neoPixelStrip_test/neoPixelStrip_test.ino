#include <Adafruit_NeoPixel.h>

const byte neoStripPin = 11;
const byte neoStrip = 8;
byte neoBright = 10;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(neoStrip, neoStripPin, NEO_RGB);

void setup()
{
  strip.begin();
  //strip.setBrightness(neoBright);
}

void loop()
{
  for(int i = 0; i < 60; i++)
  {
    showSecond(i);
    delay(1000);
  }
}

int showSecond(int second)
{ 
  for(int i = 0; i < 6; i++)
  {
    if((second >> i) & 1) //Testar det binära talet om det är en 1 eller 0, för att testa så skiftar vi siffran
    {
      strip.setPixelColor(i, strip.Color(10, 118, 200));
    }
    else
    {
      strip.setPixelColor(i, strip.Color(0, 0, 0));
    }
  }
  strip.show();
}

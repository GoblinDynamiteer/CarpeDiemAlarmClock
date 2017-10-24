#include <Adafruit_NeoPixel.h>

const byte neoPin = 12;
const byte neoPixel = 24;
byte neoBright = 10;

Adafruit_NeoPixel ring = Adafruit_NeoPixel(neoPixel, neoPin, NEO_RGB);

void setup()
{
  ring.begin();
  ring.setBrightness(neoBright);
  ring.show();
}

void loop()
{  
  for(int i = 0; i < neoPixel; i++)
  {
    ring.setPixelColor(i, ring.Color(195, 80, 50));
    ring.setPixelColor(0, ring.Color(0, 0, 255));
    ring.setPixelColor(6, ring.Color(10, 118, 200));
    ring.setPixelColor(12, ring.Color(10, 118, 200));
    ring.setPixelColor(18, ring.Color(10, 118, 200));
    ring.show();
    delay(1000);
    ring.setPixelColor(i, ring.Color(0, 0, 0));
  }
 
}

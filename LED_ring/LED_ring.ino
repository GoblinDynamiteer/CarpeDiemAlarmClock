#include <Adafruit_NeoPixel.h>

#define PIN PA0
#define NUM_LEDS 24

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB);

uint32_t color = strip.Color(75, 250, 100);

void setup() {
   strip.begin();
   strip.show();
   strip.setBrightness(40);
}

void loop() {
   for (int i = 0; i < NUM_LEDS; i++) {
      strip.setPixelColor(i, 20, 20, 20);
      strip.show();
   }
}

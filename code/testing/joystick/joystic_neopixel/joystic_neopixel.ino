/*  LED ring strenght test
NeoPixel Led-Ring with STM32 devboard

https://github.com/fergul/NeoMaple
*/

// #include <NeoMaple.h>
#include <Adafruit_NeoPixel.h>

#define NUM_LEDS 24
#define pin 6

int xpotPin = 0; // Define UNO board A0 pin connect the Ioystick x
int ypotPin = 1; // Define UNO board A1 pin connect the Ioystick y
int swPin = 9;   // Define UNO board digital 9 pin connect the Ioystick sw

int yval = 0;
int current_ledpix = 0;

/* Default data-pin is PA0 */
Adafruit_NeoPixel ledring = Adafruit_NeoPixel(NUM_LEDS, pin, NEO_GRB + NEO_KHZ800);

//NeoMaple ledring = NeoMaple(NUM_LEDS, NEO_GRB + NEO_KHZ800);

void setup()
{
    Serial.begin(9600);
    ledring.begin();
    pinMode(swPin,INPUT_PULLUP);//Set swPin inputand pull up
}

void loop()
{       int yval = analogRead(ypotPin);

    if (yval < 200)
    {
        Serial.println(yval);
        current_ledpix++;
        delay(200);
    }
    for (int i = 0; i < 24; i++)
    {
        ledring.setPixelColor(i, 0,0,0);
    }

    Serial.println(yval);
    if (yval > 600 )
    {
        Serial.println(yval);
        current_ledpix--;
        delay(200);
    }
    for (int i = 0; i < 24; i++)
    {
        ledring.setPixelColor(i, 0,0,0);
    }
    if (current_ledpix < 0)
    {
        current_ledpix = 23;
    }
        if (current_ledpix > 23)
        {
            current_ledpix = 0;
        }
    ledring.setPixelColor(current_ledpix, 100,0,0);
    ledring.show();
}

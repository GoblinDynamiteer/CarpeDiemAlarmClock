/*  LED ring strenght test
NeoPixel Led-Ring with STM32 devboard

https://github.com/fergul/NeoMaple
*/

// #include <NeoMaple.h>
#include <Adafruit_NeoPixel.h>

#define NUM_LEDS 24
#define pin 6
const int buzzer = 8; //buzzer to arduino pin 8

bool alarm = true;
bool light = true;
bool sound = true;

int xpotPin = 0; // Define UNO board A0 pin connect the Ioystick x
int ypotPin = 1; // Define UNO board A1 pin connect the Ioystick y
int swPin = 9;   // Define UNO board digital 9 pin connect the Ioystick sw

int xval = 0;
int yval = 0;
int swval= 0;

/* Default data-pin is PA0 */
Adafruit_NeoPixel ledring = Adafruit_NeoPixel(NUM_LEDS, pin, NEO_GRB + NEO_KHZ800);

//NeoMaple ledring = NeoMaple(NUM_LEDS, NEO_GRB + NEO_KHZ800);

void setup()
{
    Serial.begin(9600);
    ledring.begin();
    pinMode(buzzer, OUTPUT); // Set buzzer - pin 8 as an output
    pinMode(swPin,INPUT_PULLUP);//Set swPin inputand pull up
}

void loop()
{
    // Read the Joystick x y sw information
    int xval = analogRead(xpotPin);
    int yval = analogRead(ypotPin);
    int swval = digitalRead(swPin);

    //
    if (xval > 800)
    {
        //Down
        Serial.println(xval);
        //fade_mode(10);
    }

    if (xval < 400)
    {
        //Up - Alarm
        if(alarm == true)
        {
            alarm = false;
            Serial.println("Alarm is off");
        }
        else if (alarm == false)
        {
            alarm = true;
            Serial.println("Alarm is on");
        }
        delay(500);

        //blink_mode(1000,50,0,0);
    }

    if (yval > 800)
    {
        //Left - Light
        if(light == true)
        {
            light = false;
            Serial.println("Light is off");
        }
        else if (light == false)
        {
            light = true;
            Serial.println("Light is on");
        }
        delay(500);
        //steady_light_mode(100,100,100);

    }

    if (yval < 400)
    {
        //Right - Sound
        if(sound == true)
        {
            sound = false;
            Serial.println("Sound is off");
        }
        else if (sound == false)
        {
            sound = true;
            Serial.println("Sound is on");
        }
        delay(500);
        //random_blink(200);
    }
    if (swval == 0)
    {
        //Push
        unsigned long now = millis();

        while (swval==0)
        {
            swval = digitalRead(swPin);
        }
        int diff = millis() - now;
        if (diff > 2000)
        Serial.println("Set time");

        else
        {
            Serial.println("Set alarm");
        }
    }
}

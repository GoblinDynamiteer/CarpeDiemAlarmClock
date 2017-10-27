/*  Test with NeoMaple lib
    NeoPixel Led-Ring with STM32 devboard

    https://github.com/fergul/NeoMaple
 */

#include <NeoMaple.h>

#define NUM_LEDS 32
#define DELAY 50

enum{RED, GREEN, BLUE};

/* Default data-pin is PA0 */
NeoMaple ledring = NeoMaple(NUM_LEDS, NEO_GRB + NEO_KHZ800);
int pwm = 20;

void setup()
{
   ledring.begin();
   clearRing(true);

}

int increase_pwm(int current_pwm)
{
    return (current_pwm < 120 ? current_pwm + 2 : 2);
}

void loop()
{
   /*for (int i = 0; i < NUM_LEDS; i++)
   {
      //clearRing(false);
      ledring.setPixelColor(i, 0, 0, 0);
      //ledring.setPixelColor(opposite_pixel(i), 0, 0, pwm);
   }
   ledring.show();*/


    for (int i = 0; i < NUM_LEDS; i++)
    {
        //clearRing(false);
        ledring.setPixelColor(i, 0, pwm, 0);
        //ledring.setPixelColor(opposite_pixel(i), 0, 0, pwm);
        ledring.show();
        delay(DELAY);
    }

    //pwm = increase_pwm(pwm);
}

/* Sets all pixels to zero (off) */
void clearRing(bool update)
{
    for (int i = 0; i < NUM_LEDS; i++)
    {
         ledring.setPixelColor(i, 0, 0, 0);
    }

    if(update)
    {
        ledring.show();
    }
}

int opposite_pixel(int i)
{
    int ret_val = i + NUM_LEDS / 2;
    return (ret_val >= NUM_LEDS ? ret_val - NUM_LEDS : ret_val);
}

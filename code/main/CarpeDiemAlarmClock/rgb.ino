/*  CarpeDiem Alarm clock

    rtc.c

    LED-strip and LED-Ring Functions
    Default pin for LED-ring data pin is PA0
 */

/* Port of NeoPixel library */
#include <NeoMaple.h>

NeoMaple ring = NeoMaple(RGB_TOTAL_NUM_LED, NEO_GRB + NEO_KHZ800);
bool show_pixels;

void rgb_init()
{
    ring.begin();
    on_board_led_init();
    rgb_lightshows_init();
    rgb_all_led_test();
    show_pixels = false;
}

void rgb_all_led_test()
{
    for (int i = 0; i < RGB_TOTAL_NUM_LED; i++)
    {
        ring.setPixelColor(i, 10, 10, 10);
        delay(20);
        ring.show();
    }
}

void rgb_update()
{
    if(show_pixels)
    {
        ring.show();
        show_pixels = false;
    }
}

void rgb_need_update()
{
    show_pixels = true;
}

/* Set LED-ring to specific color */
void ring_set_color(int red, int green, int blue)
{
    for (int i = 0; i < RING_NUM_LEDS; i++)
    {
        ring.setPixelColor(i, red, green, blue);
    }

    ring.show();
}

/* Set LED-ring to specific color */
void strip_set_color(int red, int green, int blue)
{
    for (int i = STRIP_LED_INDEX_START; i < STRIP_LED_INDEX_END; i++)
    {
        ring.setPixelColor(i, red, green, blue);
    }

    ring.show();
}

/* Set one pixel to specific color */
void ring_set_one_pixel(
    int pixel, int red, int green, int blue,
    bool clear_first, bool update = true)
{
    if(pixel > RING_NUM_LEDS)
    {
        return;
    }

    /* Clear all existing pixels */
    if(clear_first)
    {
        ring_set_color(0, 0, 0);
    }

    ring.setPixelColor(pixel, red, green, blue);

    if(update)
    {
        ring.show();
    }
}

/* Sets every nth (third, fourth etc) pixel */
void ring_set_nth_pixel(int n, int red, int green, int blue)
{
    ring_set_color(0, 0, 0);

    for (int i = 0; i < RING_NUM_LEDS; i++)
    {
        if(!(i % n))
        {
            ring.setPixelColor(i, red, green, blue);
        }
    }

    ring.show();
}

/* Blink color on / off, one cycle */
void ring_blink_mode(
    int blink_delay, int red, int green, int blue)
{
    ring_set_color(red, green, blue);
    delay(blink_delay);

    ring_set_color(0, 0, 0);
    delay(blink_delay);
}

/* Fade LED-ring color up and down, one cycle */
void ring_fade_mode(int step_delay, int fade_color, int pwm_limit)
{
    bool up = true;

    for (int pwm = 1; pwm >= 1; up ? pwm++ : pwm--)
    {
        ring_set_color(
            fade_color == COLOR_RED ? pwm : 0,
            fade_color == COLOR_GREEN ? pwm : 0,
            fade_color == COLOR_BLUE ? pwm : 0);
        delay(step_delay);

        if(pwm > pwm_limit)
        {
            up = !up;
        }
    }
}

/* Shows seconds on LED-strip */
void strip_show_second(
    uint8_t second,uint8_t red, uint8_t green, uint8_t blue)
{
    uint8_t shift_amount = 0;
    for(uint8_t i = STRIP_LED_INDEX_START; i < STRIP_LED_INDEX_END; i++)
    {
        if((second >> shift_amount++) & 1)
        {
            ring.setPixelColor(i, red, green, blue);
        }

        else
        {
            ring.setPixelColor(i, 0, 0, 0);
        }
    }

    rgb_need_update();
}

/* Blink LED-ring with random color, one cycle */
void ring_random_blink(int delay, int max_pwm)
{
    int red = random(max_pwm);
    int green = random(max_pwm);
    int blue = random(max_pwm);
    ring_blink_mode(delay, red, green, blue);
}

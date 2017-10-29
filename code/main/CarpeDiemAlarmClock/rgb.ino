/*  CarpeDiem Alarm clock

    rtc.c

    LED-strip and LED-Ring Functions
    Default pin for LED-ring data pin is PA0
 */

/* Port of NeoPixel library */
#include <NeoMaple.h>
#include "settings.h"

NeoMaple rgb = NeoMaple(RGB_TOTAL_NUM_LED, NEO_GRB + NEO_KHZ800);
bool show_pixels;

void rgb_init()
{
    rgb.begin();
    on_board_led_init();
    rgb_lightshows_init();
    rgb_all_led_test();
    show_pixels = false;
    rgb_current_clock_mode = RGB_CLOCK_MODE_REGULAR;
}

void rgb_all_led_test()
{
    for (int i = 0; i < RGB_TOTAL_NUM_LED; i++)
    {
        rgb.setPixelColor(i, 10, 10, 10);
        delay(20);
        rgb.show();
    }
}

void rgb_all_led_off()
{
    for (int i = 0; i < RGB_TOTAL_NUM_LED; i++)
    {
        rgb.setPixelColor(i, 0, 0, 0);
    }

    rgb.show();
}

void rgb_update()
{
    if(show_pixels)
    {
        rgb.show();
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
        rgb.setPixelColor(i, red, green, blue);
    }

    rgb.show();
}

/* Set LED-ring to specific color */
void strip_set_color(int red, int green, int blue)
{
    for (int i = STRIP_LED_INDEX_START; i < STRIP_LED_INDEX_END; i++)
    {
        rgb.setPixelColor(i, red, green, blue);
    }

    rgb.show();
}

/* Set colors from selected index, lenght amount */
void rgb_ring_set_color_from_lenght(uint8_t start_index, uint8_t lenght,
    uint8_t red, uint8_t green, uint8_t blue)
{
    for (uint8_t i = 0; i < lenght; i++)
    {
        if(start_index >= RING_NUM_LEDS)
        {
            rgb.setPixelColor(start_index - RING_NUM_LEDS - 1,
                red, green, blue);
        }

        else
        {
            rgb.setPixelColor(start_index, red, green, blue);
        }

        start_index++;
    }
}

/* Set LED-ring to specific color */
void rgb_strip_set_status_bits()
{
    rgb.setPixelColor(STRIP_LED_STATUS_INDEX1, 0,
        status_alarm ? 20 : 0, 0);
    rgb.setPixelColor(STRIP_LED_STATUS_INDEX2, 0,
        status_buzzer ? 20 : 0, 0);

    rgb_need_update();
}

/* Set one pixel to specific color */
void rgb_ring_set_one_pixel(
    uint8_t pixel, uint8_t red, uint8_t green, uint8_t blue,
    bool clear_first = true)
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

    rgb.setPixelColor(pixel, red, green, blue);
}

/* Sets every nth (third, fourth etc) pixel */
void rgb_ring_set_nth_pixel(uint8_t n, uint8_t red, uint8_t green, uint8_t blue)
{
    ring_set_color(0, 0, 0);

    for (uint8_t i = 0; i < RING_NUM_LEDS; i++)
    {
        if(!(i % n))
        {
            rgb.setPixelColor(i, red, green, blue);
        }

        else
        {
            rgb.setPixelColor(i, 0, 0, 0);
        }
    }
}

/* Blink color on / off, one cycle */
void ring_blink_mode(
    int blink_delay, uint8_t red, uint8_t green, uint8_t blue)
{
    ring_set_color(red, green, blue);
    delay(blink_delay);

    ring_set_color(0, 0, 0);
    delay(blink_delay);
}

/* Fade LED-ring color up and down, one cycle */
void ring_fade_mode(int step_delay, int fade_color, uint8_t pwm_limit)
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

/* Set static color on strip */
void rgb_strip_set_color(uint8_t red, uint8_t green, uint8_t blue)
{
    for(uint8_t i = STRIP_LED_INDEX_START; i < STRIP_LED_INDEX_END; i++)
    {
        rgb.setPixelColor(i, red, green, blue);
    }

    rgb.show();
}

/* Shows seconds on LED-strip */
void rgb_strip_show_second(
    uint8_t second, uint8_t red, uint8_t green, uint8_t blue)
{
    uint8_t shift_amount = 0;
    for(uint8_t i = STRIP_LED_INDEX_START; i < STRIP_LED_INDEX_END - 2; i++)
    {
        if((second >> shift_amount++) & 1)
        {
            rgb.setPixelColor(i, red, green, blue);
        }

        else
        {
            rgb.setPixelColor(i, 0, 0, 0);
        }
    }

    rgb_need_update();
}

uint8_t rgb_ring_calc_pixel_minute(
    uint8_t minute)
{
    uint8_t index = (uint8_t)(minute / 2.5);
    index = index > RING_NUM_LEDS ? 23 : index;
    return index;
}

uint8_t rgb_ring_calc_pixel_hour(
    uint8_t hour, uint8_t minute)
{
    hour = hour >= 12 ? hour - 12 : hour; // Convert 22 23 .. -> 10 11 ..

    /* Index is hour * 2 if minutes passed is < 30,
        else hour * 2 + 1 */
    uint8_t index = minute >= 30 ?  hour * 2 + 1 : hour * 2;
    index = index > RING_NUM_LEDS ? 23 : index;
    return index;
}

/* Show clock on led-ring */
void rgb_ring_show_clock(uint8_t hour, uint8_t minute, uint8_t mode)
{
    switch(mode)
    {
        case RGB_CLOCK_MODE_REGULAR:
            rgb_ring_set_one_pixel(
                rgb_ring_calc_pixel_minute(minute), 0, 0, 20, true);
            rgb_ring_set_one_pixel(
                rgb_ring_calc_pixel_hour(hour, minute), 0, 20, 0, false);
            break;

        default:
            break;
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

/*  CarpeDiem Alarm clock

    rgb_shows.c

    Functions running cool neopixel demos / lightshows
 */

#include "rgb.h"

void rgb_lightshows_init()
{
    rgb_show_func[RGB_SHOW_RAINBOW_SPINNER] = rgb_lightshow_rainbow_spinner;
    rgb_show_func[RGB_SHOW_SPLITTER] = rgb_lightshow_splitter;
    current_rgb_show_mode = RGB_SHOW_RAINBOW_SPINNER;
}

/* Cycle function pointer and delay array indexes */
void rgb_lightshows_select(bool next_previous = RGB_SHOW_NEXT)
{
    if(next_previous) // next
    {
        current_rgb_show_mode =
            current_rgb_show_mode + 1 >= RGB_SHOW_MAX_MODES ?
            0 : current_rgb_show_mode + 1;
    }

    else
    {
        current_rgb_show_mode =
            current_rgb_show_mode == 0 ?
            (RGB_SHOW_MAX_MODES - 1) : (current_rgb_show_mode - 1);
    }
}

void rgb_lightshow_splitter(void)
{
    static uint8_t n = 1;
    static uint8_t red = 2;
    static uint8_t blue = 2;
    static uint8_t green = 3;

    ring_set_nth_pixel(n, red, green, blue);

    red = random(RGB_SHOW_MAX_PWM);
    green = random(RGB_SHOW_MAX_PWM);
    blue = random(RGB_SHOW_MAX_PWM);

    n == 6 ? n = 0 : n++;
}

void rgb_lightshow_rainbow_spinner(void)
{
    static int16_t blue = RGB_SHOW_MAX_PWM;
    static int16_t red = 0;
    static int16_t green = 0;
    static uint8_t inc = INC_RED;
    static uint8_t dec = DEC_BLUE;
    static uint8_t led_index = 0;

    ring_set_one_pixel(led_index++, red, green, blue, false, false);

    (inc == INC_BLUE) ? blue++ : 0;
    (inc == INC_RED) ? red++ : 0;
    (inc == INC_GREEN) ? green++ : 0;

    (dec == DEC_RED) ? red-- : 0;
    (dec == DEC_BLUE) ? blue-- : 0;
    (dec == DEC_GREEN) ? green-- : 0;

    if(red > RGB_SHOW_MAX_PWM)
    {
        dec = DEC_RED;
        inc = INC_GREEN;
    }

    if(green > RGB_SHOW_MAX_PWM)
    {
        dec = DEC_GREEN;
        inc = INC_BLUE;
    }

    if(blue > RGB_SHOW_MAX_PWM)
    {
        dec = DEC_BLUE;
        inc = INC_RED;
    }

    blue = blue <= 0 ? 0 : blue;
    red = red <= 0 ? 0 : red;
    green = green <= 0 ? 0 : green;
    led_index = led_index >= RING_NUM_LEDS ? 0 : led_index;

    rgb_need_update();
}

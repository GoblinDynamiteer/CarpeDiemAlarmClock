/*  CarpeDiem Alarm clock

    rgb_shows.c

    Functions running cool neopixel demos / lightshows
 */

#include "rgb.h"
#include "settings.h"

void rgb_lightshows_init()
{
    rgb_show_func[RGB_SHOW_RAINBOW_SPINNER] = rgb_lightshow_rainbow_spinner;
    rgb_show_func[RGB_SHOW_SPLITTER] = rgb_lightshow_splitter;
    rgb_show_func[RGB_SHOW_PIE_CHASER] = rgb_lightshow_pie_chaser;

    current_rgb_show_mode = RGB_SHOW_RAINBOW_SPINNER;
}

/* Cycle function pointer and delay array indexes */
void rgb_lightshows_select(bool next_previous = RGB_SHOW_NEXT)
{
    if(show_time_on_ring)
    {
        show_time_on_ring = false;
        current_rgb_show_mode = RGB_SHOW_RAINBOW_SPINNER;
        return;
    }

    if(next_previous) // next
    {
        if(current_rgb_show_mode == RGB_SHOW_MAX_MODES - 1)
        {
            show_time_on_ring = true;
            force_time_display_update = true;
            current_rgb_show_mode = 0;
        }

        else
        {
            current_rgb_show_mode++;
        }
    }

    else
    {
        if(current_rgb_show_mode == 0)
        {
            show_time_on_ring = true;
            force_time_display_update = true;
            current_rgb_show_mode = RGB_SHOW_MAX_MODES - 1;
        }

        else
        {
            current_rgb_show_mode--;
        }
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

    n == 6 ? n = 1 : n++;
    rgb_need_update();
}

/* Four "pie pieces" rotating counter-clockwise */
void rgb_lightshow_pie_chaser(void)
{
    static uint8_t led_index = 0;
    static uint8_t offset = 0;
    static const uint8_t pie = (RING_NUM_LEDS / 4);

    led_index <= 0 ? led_index = RING_NUM_LEDS-1 : led_index--;

    strip_set_color_from_lenght(led_index, pie, 25, 0, 0);

    offset = STRING_PIXEL_OFFSET(led_index, pie);
    strip_set_color_from_lenght(offset, pie, 0, 25, 0);

    offset = STRING_PIXEL_OFFSET(led_index, pie * 2);
    strip_set_color_from_lenght(offset, pie, 0, 0, 25);

    offset = STRING_PIXEL_OFFSET(led_index, pie * 3);
    strip_set_color_from_lenght(offset, pie, 2, 2, 0);

    rgb_need_update();
}

/* Colors rotating and blending clockwise */
void rgb_lightshow_rainbow_spinner(void)
{
    static int16_t blue = RGB_SHOW_MAX_PWM;
    static int16_t red = 0;
    static int16_t green = 0;
    static uint8_t inc = INC_RED;
    static uint8_t dec = DEC_BLUE;
    static uint8_t led_index = 0;

    ring_set_one_pixel(led_index++, red, green, blue, false);

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

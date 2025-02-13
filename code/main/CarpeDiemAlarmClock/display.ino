/*  CarpeDiem Alarm clock

    display.ino

    Functions for different display modes
 */

#include "rgb.h"
#include "settings.h"

/* Semaphore defined in task.ino */
extern SemaphoreHandle_t semaphore_rtc;

bool has_cycled = false;

/* Init function pointer array and set start display mode */
void rgb_lightshows_init()
{
    rgb_show_func[RGB_SHOW_CLOCK] = rgb_lightshow_clock;
    rgb_show_func[RGB_SHOW_RAINBOW_SPINNER] = rgb_lightshow_rainbow_spinner;
    rgb_show_func[RGB_SHOW_SPLITTER] = rgb_lightshow_splitter;
    rgb_show_func[RGB_SHOW_PIE_CHASER] = rgb_lightshow_pie_chaser;
    rgb_show_func[RGB_SHOW_WAKE_UP_BEFORE_ALARM] = rgb_lightshow_before_alarm;
    rgb_show_func[RGB_SHOW_ALARM] = rgb_lightshow_alarm;

    /* Index for function pointer array and delay array */
    current_rgb_show_mode = RGB_SHOW_CLOCK;
}

/* Cycle current display mode */
extern void rgb_lightshows_select(bool next_previous = RGB_SHOW_NEXT)
{
    if(next_previous) // Next mode
    {
        current_rgb_show_mode =
            (current_rgb_show_mode == RGB_SHOW_MAX_MODES - 2) ?
                0 : current_rgb_show_mode + 1;

        has_cycled = true;
    }

    else // Previous mode
    {
        current_rgb_show_mode =
            (current_rgb_show_mode == 0) ?
             RGB_SHOW_MAX_MODES - 2 : current_rgb_show_mode - 1;

        has_cycled = true;
    }
}

/* Show clock on LED-ring */
void rgb_lightshow_clock(void)
{
    if(xSemaphoreTake(semaphore_rtc, (TickType_t)100) == pdTRUE)
    {
        if(rtc_minute_changed() || has_cycled || status_changed(STATUS_RGB))
        {
            rgb_ring_show_clock(
                rtc_hour(),
                rtc_minute(),
                rgb_current_clock_mode);

            has_cycled = false;
        }

        xSemaphoreGive(semaphore_rtc);
    }
}

/* Lightshow */
void rgb_lightshow_splitter(void)
{
    static uint8_t n = 1;
    static uint8_t red = 2;
    static uint8_t blue = 2;
    static uint8_t green = 3;

    rgb_ring_set_nth_pixel(n, red, green, blue);

    red = random(RGB_SHOW_MAX_PWM);
    green = random(RGB_SHOW_MAX_PWM);
    blue = random(RGB_SHOW_MAX_PWM);

    n == 6 ? n = 1 : n++;
    rgb_need_update();
}

/* Lightshow : four "pie pieces" rotating counter-clockwise */
void rgb_lightshow_pie_chaser(void)
{
    static uint8_t led_index = 0;
    static uint8_t offset = 0;
    static const uint8_t pie = (RING_NUM_LEDS / 4);

    led_index <= 0 ? led_index = RING_NUM_LEDS-1 : led_index--;

    rgb_ring_set_color_from_lenght(led_index, pie, 25, 0, 0);

    offset = STRING_PIXEL_OFFSET(led_index, pie);
    rgb_ring_set_color_from_lenght(offset, pie, 0, 25, 0);

    offset = STRING_PIXEL_OFFSET(led_index, pie * 2);
    rgb_ring_set_color_from_lenght(offset, pie, 0, 0, 25);

    offset = STRING_PIXEL_OFFSET(led_index, pie * 3);
    rgb_ring_set_color_from_lenght(offset, pie, 2, 2, 0);

    rgb_need_update();
}

/* Lightshow: Colors rotating and blending clockwise */
void rgb_lightshow_rainbow_spinner(void)
{
    static int16_t blue = RGB_SHOW_MAX_PWM;
    static int16_t red = 0;
    static int16_t green = 0;
    static uint8_t inc = INC_RED;
    static uint8_t dec = DEC_BLUE;
    static uint8_t led_index = 0;

    rgb_ring_set_one_pixel(led_index++, red, green, blue, false);

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

/* Alarm: Blinking LEDs */
void rgb_lightshow_alarm(void)
{
    static bool on = false;

    rgb_strip_set_color(
        on ? 40 : 0,
        on ? 40 : 0,
        on ? 40 : 0
    );

    ring_set_color(
        !on ? 40 : 0,
        !on ? 40 : 0,
        !on ? 40 : 0
    );

    on = !on;
}


/* Alramr buildup*/
void rgb_lightshow_before_alarm(void)
{
    static uint8_t intensity = 0;
    static uint8_t n = 6;
    static uint8_t prev_intensity = 0;
    static uint16_t time_until_alarm = 0;
    static bool ticked = true;

    if(!rtc_alarm_countdown_running)
    {
        rgb_lightshows_select(RGB_SHOW_NEXT);
        return;
    }

    if(xSemaphoreTake(semaphore_rtc, (TickType_t)100) == pdTRUE)
    {
        time_until_alarm = (uint16_t)rtc_time_to_alarm();
        xSemaphoreGive(semaphore_rtc);

        if(time_until_alarm > RTC_ALARM_START_MINUTES)
        {
            return;
        }

        intensity = RTC_ALARM_START_MINUTES + 1 - time_until_alarm;

        n = 8;
        if(intensity > 5)   n = 6;
        if(intensity > 10)  n = 4;
        if(intensity > 15)  n = 3;
        if(intensity > 20)  n = 2;
        if(intensity > 25)  n = 1;

        if(prev_intensity != intensity || status_changed(STATUS_ALARM))
        {
            if(serial_debug_output)
                serial_print_ln("show alarm: intensity: " + String(intensity));

            rgb_ring_set_nth_pixel(n,
                intensity, intensity, intensity);

            prev_intensity = intensity;
            rgb_need_update();
        }
    }
}

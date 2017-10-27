/*  CarpeDiem Alarm clock

    rgb_shows.c

    Functions running cool neopixel demos / lightshows
 */

enum { INC_RED, INC_GREEN, INC_BLUE };
enum { DEC_RED, DEC_GREEN, DEC_BLUE };

#define SHOW_MAX_PWM 30

void rgb_lightshow_splitter(void)
{
    static uint8_t n = 1;
    static uint8_t red = 2;
    static uint8_t blue = 2;
    static uint8_t green = 3;

    ring_set_nth_pixel(n, red, green, blue);

    red = random(SHOW_MAX_PWM);
    green = random(SHOW_MAX_PWM);
    blue = random(SHOW_MAX_PWM);

    n == 6 ? n = 0 : n++;

    delay(30);
}

void rgb_lightshow_rainbow_spinner(void)
{
    static int16_t blue = SHOW_MAX_PWM;
    static int16_t red = 0;
    static int16_t green = 0;
    static uint8_t inc = INC_RED;
    static uint8_t dec = DEC_BLUE;

    for (size_t i = 0; i < RING_NUM_LEDS; i++)
    {
        ring_set_one_pixel(i, red, green, blue, false);
        delay(40);

        (inc == INC_BLUE) ? blue++ : 0;
        (inc == INC_RED) ? red++ : 0;
        (inc == INC_GREEN) ? green++ : 0;

        (dec == DEC_RED) ? red-- : 0;
        (dec == DEC_BLUE) ? blue-- : 0;
        (dec == DEC_GREEN) ? green-- : 0;

        if(red > SHOW_MAX_PWM)
        {
            dec = DEC_RED;
            inc = INC_GREEN;
        }

        if(green > SHOW_MAX_PWM)
        {
            dec = DEC_GREEN;
            inc = INC_BLUE;
        }

        if(blue > SHOW_MAX_PWM)
        {
            dec = DEC_BLUE;
            inc = INC_RED;
        }

        blue = blue <= 0 ? 0 : blue;
        red = red <= 0 ? 0 : red;
        green = green <= 0 ? 0 : green;
    }
}

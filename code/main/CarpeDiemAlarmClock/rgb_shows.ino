/*  CarpeDiem Alarm clock

    rgb_shows.c

    Functions running cool neopixel demos / lightshows
 */

enum { INC_RED, INC_GREEN, INC_BLUE };
enum { DEC_RED, DEC_GREEN, DEC_BLUE };


void rgb_lightshow_splitter(void)
{
    static int n = 1;
    static int red = 2;
    static int blue = 2;
    static int green = 3;

    ring_set_nth_pixel(n, red, green, blue);

    red = random(30);
    green = random(30);
    blue = random(30);

    n == 6 ? n = 0 : n++;

    delay(600);
}

void rgb_lightshow_rainbow_spinner(void)
{
    static int blue = 20;
    static int red = 0;
    static int green = 0;
    static int inc = INC_RED;
    static int dec = DEC_BLUE;

    for (size_t i = 0; i < RING_NUM_LEDS; i++)
    {
        ring_set_one_pixel(i, red, green, blue, false);
        delay(30);

        inc == INC_BLUE ? blue++ : 0;
        inc == INC_RED ? red++ : 0;
        inc == INC_GREEN ? green++ : 0;

        dec == DEC_BLUE ? blue-- : 0;
        dec == DEC_RED ? red-- : 0;
        dec == DEC_GREEN ? green-- : 0;

        if(red > 20)
        {
            dec = DEC_RED;
            inc = INC_GREEN;
        }

        if(green > 20)
        {
            dec = DEC_GREEN;
            inc = INC_BLUE;
        }

        if(blue > 20)
        {
            dec = DEC_BLUE;
            inc = INC_RED;
        }

        blue = blue <= 0 ? 0 : blue;
        red = red <= 0 ? 0 : red;
        green = green <= 0 ? 0 : green;
    }
}

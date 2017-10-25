/*  CarpeDiem Alarm clock

    rtc.c

    LED-strip and LED-Ring Functions
 */

enum { INC_RED, INC_GREEN, INC_BLUE };
enum { DEC_RED, DEC_GREEN, DEC_BLUE };
int blue = 20;
int red = 0;
int green = 0;
int inc = INC_RED;
int dec = DEC_BLUE;

void rgb_show_rainbow_spinner(void)
{
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

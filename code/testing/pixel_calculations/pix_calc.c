#define RING_NUM_LEDS 24
#define STRING_PIXEL_OFFSET(PIX, LEN) ((PIX + LEN) > RING_NUM_LEDS) ? \
    (PIX + LEN - RING_NUM_LEDS) : (PIX + LEN)

#include <stdio.h>

void strip_set_color_from_lenght(int start_index, int lenght);

int main()
{
    const int pie = (RING_NUM_LEDS / 4);
    int offset;

    for (int i = 0; i < 24; i++)
    {
        printf("i: %d\n", i);
        strip_set_color_from_lenght(i, pie);

        offset = STRING_PIXEL_OFFSET(i, pie);
        strip_set_color_from_lenght(offset, pie);

        offset = STRING_PIXEL_OFFSET(i, pie * 2);
        strip_set_color_from_lenght(offset, pie);

        offset = STRING_PIXEL_OFFSET(i, pie * 3);
        strip_set_color_from_lenght(offset, pie);
    }
}


void strip_set_color_from_lenght(int start_index, int lenght)
{
    for (int i = 0; i < lenght; i++)
    {
        if(start_index > RING_NUM_LEDS)
        {
            printf("Setting pixel: %d\n", start_index - RING_NUM_LEDS - 1);
        }

        else
        {
            printf("Setting pixel: %d\n", start_index);
        }

        start_index++;
    }
}

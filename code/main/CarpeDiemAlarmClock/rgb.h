#ifndef RGB_H
#define RGB_H

/* LED Amounts */
#define RING_NUM_LEDS 24
#define STRIP_NUM_LEDS 8
#define RGB_TOTAL_NUM_LED RING_NUM_LEDS + STRIP_NUM_LEDS
#define STRIP_LED_INDEX_START RING_NUM_LEDS
#define STRIP_LED_INDEX_END RGB_TOTAL_NUM_LED
#define STRIP_LED_STATUS_INDEX1 (RGB_TOTAL_NUM_LED - 2)
#define STRIP_LED_STATUS_INDEX2 (RGB_TOTAL_NUM_LED - 1)

/* For fade-mode */
enum { COLOR_RED, COLOR_GREEN, COLOR_BLUE };


/* For rgb shows/demos */
enum { INC_RED, INC_GREEN, INC_BLUE };
enum { DEC_RED, DEC_GREEN, DEC_BLUE };
enum {
    RGB_SHOW_RAINBOW_SPINNER,
    RGB_SHOW_SPLITTER,
    RGB_SHOW_PIE_CHASER,
    RGB_SHOW_MAX_MODES
};

#define RGB_SHOW_MAX_PWM 30
#define RBG_SHOW_RAINBOW_SPINNER_DELAY 50
#define RGB_SHOW_SPLITTER_DELAY 500
#define RGB_SHOW_PIE_CHASER_DELAY 100

#define RGB_SHOW_NEXT true
#define RGB_SHOW_PREV false

#define STRING_PIXEL_OFFSET(PIX, LEN) ((PIX + LEN) > RING_NUM_LEDS) ? \
    (PIX + LEN - RING_NUM_LEDS) : (PIX + LEN)

/* Function pointer used with tasks */
void(*rgb_show_func[3])(void);
uint8_t current_rgb_show_mode; // Index for function pointer and delay array
uint16_t rgb_show_delay[3] =
{
    RBG_SHOW_RAINBOW_SPINNER_DELAY,
    RGB_SHOW_SPLITTER_DELAY,
    RGB_SHOW_PIE_CHASER_DELAY
};

bool force_time_display_update;

#endif

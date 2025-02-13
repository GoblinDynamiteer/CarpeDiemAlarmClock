#ifndef RGB_H
#define RGB_H

/*  LED Amounts, Ring has 24 LEDs and strip has 8 LEDs
    Strip and Ring are connected in series,
    data out from ring to data in on strip.
*/
#define RING_NUM_LEDS 24
#define STRIP_NUM_LEDS 8
#define RGB_TOTAL_NUM_LED RING_NUM_LEDS + STRIP_NUM_LEDS
#define STRIP_LED_INDEX_START RING_NUM_LEDS
#define STRIP_LED_INDEX_END RGB_TOTAL_NUM_LED
#define STRIP_LED_STATUS_INDEX1 (RGB_TOTAL_NUM_LED - 2)
#define STRIP_LED_STATUS_INDEX2 (RGB_TOTAL_NUM_LED - 1)

/* For fade-mode */
enum { COLOR_RED, COLOR_GREEN, COLOR_BLUE };

/* For rgb shows/demos/clock */
enum { INC_RED, INC_GREEN, INC_BLUE };
enum { DEC_RED, DEC_GREEN, DEC_BLUE };
enum {
    RGB_SHOW_CLOCK,
    RGB_SHOW_RAINBOW_SPINNER,
    RGB_SHOW_SPLITTER,
    RGB_SHOW_PIE_CHASER,
    RGB_SHOW_WAKE_UP_BEFORE_ALARM,
    RGB_SHOW_ALARM,
    RGB_SHOW_MAX_MODES
};

enum {
    RGB_CLOCK_MODE_REGULAR,
    RGB_CLOCK_MODE_BINARY,
    RGB_CLOCK_MODE_SLICES
};

#define RGB_SHOW_MAX_PWM 30
#define RBG_SHOW_RAINBOW_SPINNER_DELAY 50
#define RGB_SHOW_SPLITTER_DELAY 500
#define RGB_SHOW_PIE_CHASER_DELAY 100
#define RGB_SHOW_WAKE_UP_BEFORE_ALARM_DELAY 2000
#define RGB_SHOW_CLOCK_DELAY 200
#define RGB_SHOW_ALARM_DELAY 300

#define RGB_SHOW_NEXT true
#define RGB_SHOW_PREV false

#define STRING_PIXEL_OFFSET(PIX, LEN) ((PIX + LEN) > RING_NUM_LEDS) ? \
    (PIX + LEN - RING_NUM_LEDS) : (PIX + LEN)
#define RGB_RING_NEXT_PIXEL(PIX) (PIX == RING_NUM_LEDS - 1) ? 0 : PIX + 1
#define RGB_RING_PREV_PIXEL(PIX) (PIX == 0) ? RING_NUM_LEDS - 1 : PIX - 1

/* Function pointer used with tasks */
void(*rgb_show_func[6])(void);
uint8_t current_rgb_show_mode; // Index for function pointer and delay array
uint16_t rgb_show_delay[6] =
{
    RGB_SHOW_CLOCK_DELAY,
    RBG_SHOW_RAINBOW_SPINNER_DELAY,
    RGB_SHOW_SPLITTER_DELAY,
    RGB_SHOW_PIE_CHASER_DELAY,
    RGB_SHOW_WAKE_UP_BEFORE_ALARM_DELAY,
    RGB_SHOW_ALARM_DELAY
};

uint8_t rgb_current_clock_mode;

/* Functions in rgb.ino  */
void rgb_ring_set_one_pixel(
    uint8_t pixel, uint8_t red, uint8_t green,
    uint8_t blue, bool clear_first);

#endif

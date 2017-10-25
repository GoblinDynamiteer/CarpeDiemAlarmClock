/*  CarpeDiem Alarm clock

    rtc.c

    RTC Functions
    Default I2C Pins:
        PB06 SCL
        PB07 SDA
 */

#include "uRTCLib.h"
#include "rtc.h"
#include "settings.h"

uRTCLib rtc;
rtc_time_struct time;

void rtc_init()
{
    rtc_update();
}

/* Sets time and date in RTC */
void rtc_set(uint8_t s, uint8_t m, uint8_t h, uint8_t dow,
             uint8_t dom, uint8_t month, uint8_t year)
{
    rtc.set(
        s,      // Seconds
        m,      // Minute
        h,      // Hour
        dow,    // Day of week
        dom,    // Day of month
        month,  // Month
        year);   // Year
}

/* Read RTC data to struct */
void rtc_update()
{
    rtc.refresh();
    time.hour = rtc.hour();
    time.minute = rtc.minute();;
    time.second = rtc.second();;
    time.year = rtc.year();;
    time.month = rtc.month();;
    time.day = rtc.day();;
    time.weekday = rtc.dayOfWeek();;
}

/* Prints date and time to serial */
void rtc_serial_print()
{
    rtc_update();

    serial_print(String(time.hour) + ":"  +
                String(time.minute) + ":" +
                String(time.second) + "\n" +
                "20" + String(time.year) + "-" +
                String(time.month) + "-" +
                String(time.day) + "\n");
}

int rtc_second()
{
    return (int)time.second;
}

/* Check if a second has ticked since last check */
bool rtc_has_ticked()
{
    static uint8_t last_tick = time.second;
    rtc_update();

    if(last_tick != time.second)
    {
        last_tick = time.second;
        return true;
    }

    return false;
}

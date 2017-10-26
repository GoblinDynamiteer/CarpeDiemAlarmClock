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
rtc_time_struct rtc_time;

void rtc_init()
{
    rtc_time.last_sec = 61;
    rtc_set(30, 20, 12, 4, 26, 10, 17);
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

uint8_t rtc_second()
{
    return rtc_time.second;
}


/* Read RTC data to struct */
void rtc_update()
{
    rtc.refresh();
    rtc_time.hour = rtc.hour();
    rtc_time.minute = rtc.minute();
    rtc_time.second = rtc.second();
    rtc_time.year = rtc.year();
    rtc_time.month = rtc.month();
    rtc_time.day = rtc.day();
    rtc_time.weekday = rtc.dayOfWeek();
}

/* Prints date and time to serial */
void rtc_serial_print(void)
{
    rtc_update();

    serial_print(String(rtc_time.hour) + ":"  +
                String(rtc_time.minute) + ":" +
                String(rtc_time.second) + "\n");

    /*
    serial_print(String(rtc_time.hour) + ":"  +
                String(rtc_time.minute) + ":" +
                String(rtc_time.second) + "\n" +
                "20" + String(rtc_time.year) + "-" +
                String(rtc_time.month) + "-" +
                String(rtc_time.day) + "\n"); */
}

/* Check if a second has ticked since last check */
bool rtc_has_ticked()
{
    rtc_update();
    if(rtc_time.second != rtc_time.last_sec)
    {
        rtc_time.last_sec = rtc_time.second;
        return true;
    }

    return false;
}

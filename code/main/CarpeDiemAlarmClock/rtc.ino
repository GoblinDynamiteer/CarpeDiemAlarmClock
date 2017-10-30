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
rtc_alarm_struct rtc_alarm;

void rtc_init()
{
    rtc_alarm_countdown_running = false;
    rtc_time.last_checked_second = 61;
    rtc_time.last_checked_minute = 61;
    rtc_alarm.hour = 8;
    rtc_alarm.minute = 31;

    rtc_set(
        58,
        30,
        8,
        RTC_DEFAULT_WEEKDAY,
        RTC_DEFAULT_DAY,
        RTC_DEFAULT_MONTH,
        RTC_DEFAULT_YEAR
    );

    rtc_update();
}

/* Sets time and date in RTC */
void rtc_set(uint8_t s, uint8_t m, uint8_t h, uint8_t dow,
             uint8_t dom, uint8_t month, uint8_t year)
{
    rtc.set(
        s,       // Seconds
        m,       // Minute
        h,       // Hour
        dow,     // Day of week
        dom,     // Day of month
        month,   // Month
        year);   // Year
}

/* Sets time and date in RTC */
void rtc_set_alarm(uint8_t hour, uint8_t minute)
{
    rtc_alarm.hour = hour;
    rtc_alarm.minute = minute;
}

/* Calculate minutes to alarm  */
int32_t rtc_time_to_alarm()
{
    rtc_update();

    uint16_t total_minutes_clock = rtc_time.hour * 60 + rtc_time.minute;
    uint16_t total_minutes_alarm = rtc_alarm.hour * 60 + rtc_alarm.minute;

    int32_t diff = total_minutes_alarm - total_minutes_clock;

    return (diff < 0 ? 24 * 60 + diff : diff);
}

/* Sets time and date in RTC */
void rtc_set_hour_minute(uint8_t h, uint8_t m)
{
    rtc_set(
        RTC_DEFAULT_SECOND,
        m,
        h,
        rtc_time.weekday,
        rtc_time.day,
        rtc_time.month,
        rtc_time.year);
}

uint8_t rtc_second()
{
    return rtc_time.second;
}

uint8_t rtc_minute()
{
    return rtc_time.minute;
}

uint8_t rtc_hour()
{
    return rtc_time.hour;
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
}

/* Check if a second has ticked since last check */
bool rtc_second_changed()
{
    rtc_update();
    if(rtc_time.second != rtc_time.last_checked_second)
    {
        rtc_time.last_checked_second = rtc_time.second;
        return true;
    }

    return false;
}

/* Check if a minute has passed since last check */
bool rtc_minute_changed()
{
    rtc_update();
    if(rtc_time.minute != rtc_time.last_checked_minute)
    {
        rtc_time.last_checked_minute = rtc_time.minute;
        return true;
    }

    return false;
}

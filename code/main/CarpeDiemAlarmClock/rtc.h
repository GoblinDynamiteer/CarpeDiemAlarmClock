#ifndef RTC_H
#define RTC_H

typedef struct
{
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
    uint8_t year;
    uint8_t month;
    uint8_t day;
    uint8_t weekday;
    uint8_t last_sec;
} rtc_time_struct;

#define RTC_DEFAULT_YEAR 17
#define RTC_DEFAULT_MONTH 10
#define RTC_DEFAULT_DAY 26
#define RTC_DEFAULT_SECOND 0
#define RTC_DEFAULT_WEEKDAY 1

extern rtc_time_struct rtc_time;

#endif

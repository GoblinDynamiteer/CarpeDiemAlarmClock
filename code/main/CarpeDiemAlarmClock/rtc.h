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
    uint8_t last_checked_second;
    uint8_t last_checked_minute;
} rtc_time_struct;

typedef struct
{
    uint8_t hour;
    uint8_t minute;
} rtc_alarm_struct;

#define RTC_DEFAULT_YEAR 17
#define RTC_DEFAULT_MONTH 10
#define RTC_DEFAULT_DAY 26
#define RTC_DEFAULT_SECOND 0
#define RTC_DEFAULT_WEEKDAY 1

#define RTC_ALARM_START_MINUTES 30
bool rtc_alarm_countdown_running;

#endif

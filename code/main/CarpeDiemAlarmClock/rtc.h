#ifndef RTC_H
#define RTC_H

enum
{
    RTC_SUNDAY,
    RTC_MONDAY,
    RTC_TUESDAY,
    RTC_WEDNESDAY,
    RTC_THURSDAY,
    RTC_FRIDAY,
    RTC_SATURDAY
};

typedef struct
{
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
    uint8_t year;
    uint8_t month;
    uint8_t day;
    uint8_t weekday;
} rtc_time_struct;

#endif

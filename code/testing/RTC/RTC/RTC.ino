#include <Wire.h>
#include "uRTCLib.h"

#define DS3231_I2C_ADDRESS 0x68

/*
 * Koppling
 * PB6 - SCL
 * PB7 - SDA
 */


typedef struct {
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
    uint8_t year;
    uint8_t month;
    uint8_t day;
    uint8_t weekday;
} RTC_Time;
RTC_Time tk;

void setup()
{
    Serial.begin(9600);
    Wire.begin();

    set_date_time();

}

void loop()
{
    //Serial.println("1");
    //rtc.print_calendar();
    //Serial.println("2");
    get_date_time();
    //Serial.println("3");
    delay(1000);
}

/* Fix dec to bcd coding */
void set_date_time()
{
    Wire.beginTransmission(DS3231_I2C_ADDRESS);
    Wire.write(0x00);
    Wire.write(RTC_DecimalToBCD(30));  // Second
    Wire.write(RTC_DecimalToBCD(10));  // Minute
    Wire.write(RTC_DecimalToBCD(10));  // Hour
    Wire.write(RTC_DecimalToBCD(7));   // Day 1-7
    Wire.write(RTC_DecimalToBCD(20));  // Date 1-31
    Wire.write(RTC_DecimalToBCD(12));  // Month 1-12 + Century
    Wire.write(RTC_DecimalToBCD(17));  // Year 0-99
    Wire.endTransmission();
}

uint8_t RTC_DecimalToBCD(uint8_t decimal_value)
{
    uint8_t upper_value = decimal_value / 10;
    uint8_t lower_value = decimal_value % 10;
    return ((upper_value << 4) | lower_value);
}

/* Fix bcd to dec coding */
void get_date_time()
{
    Wire.beginTransmission(DS3231_I2C_ADDRESS);
    Wire.write(0); // set DS3231 register pointer to 00h
    Wire.endTransmission();
    Wire.requestFrom(DS3231_I2C_ADDRESS, 7);
    int _second = Wire.read();  // Second
    uRTCLIB_bcdToDec(_second);
    Serial.println("Second: " + String(_second));
    Wire.read();  // Minute
    Wire.read();  // Hour
    Wire.read();   // Day 1-7
    Wire.read();  // Date 1-31
    Wire.read();  // Month 1-12 + Century
    Wire.read();  // Year 0-99
}

#include <Wire.h>
#include <RTC_DS3231.h>

#define DS3231_I2C_ADDRESS 0x68

/*
 * Koppling
 * PB6 - SCL
 * PB7 - SDA
 */

DS3231 rtc;

void setup()
{
    Serial.begin(9600);
    Wire.begin();

    set_date_time();

}

void loop()
{
    rtc.print_calendar();
    delay(1000);
}

/* Fix dec to bcd coding */
void set_date_time()
{
    Wire.beginTransmission(DS3231_I2C_ADDRESS);
    Wire.write(0x00);
    Wire.write(30);  // Second
    Wire.write(10);  // Minute
    Wire.write(10);  // Hour
    Wire.write(3);   // Day 1-7
    Wire.write(20);  // Date 1-31
    Wire.write(12);  // Month 1-12 + Century
    Wire.write(17);  // Year 0-99
    Wire.endTransmission();
}

/* Fix bcd to dec coding */
void get_date_time()
{
    Wire.requestFrom(DS3231_I2C_ADDRESS, 0x00);
    Wire.beginTransmission(DS3231_I2C_ADDRESS);
    Wire.write(0x00);
    Wire.write(30);  // Second
    Wire.write(10);  // Minute
    Wire.write(10);  // Hour
    Wire.write(3);   // Day 1-7
    Wire.write(20);  // Date 1-31
    Wire.write(12);  // Month 1-12 + Century
    Wire.write(17);  // Year 0-99
    Wire.endTransmission();
}

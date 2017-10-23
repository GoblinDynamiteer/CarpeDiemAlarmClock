#include <Wire.h>
#include <RTC_DS3231.h>

/*
 * Koppling
 * PB6 - SCL
 * PB7 - SDA
 * PA0 - SQW
 */

#define LED PC13
#define SQW PA0

DS3231 rtc;

void handler();
volatile int state = LOW;

void setup()
{
  Serial.begin(9600);
  Wire.begin();

  pinMode(LED, OUTPUT);
  digitalWrite(LED, state);
  pinMode(SQW, INPUT_PULLUP);

  // RTC Setup ////////
  rtc.force_update(); // get date from RTC
  rtc.set_self_update(ENABLE); // enable calculation date on  microcontroller side
  rtc.set_sqw(DS3231_1HZ); // enable calculation date through external interrupt, 1sec=1tick
  rtc.reset_control(DS3231_INTCH); // enable SQW mode for INT/SQW pin DS3231
}

void loop()
{
  rtc.print_calendar();
  state=!state;
  digitalWrite(LED, state);
  delay(1000);
}

void handler() {
  rtc++;
}

#ifndef SETTINGS_H
#define SETTINGS_H

/* Uncomment (one) to use specific serial communication pins */
//#define SERIAL_0 // USB
//#define SERIAL_1
#define SERIAL_2
//#define SERIAL_3

/* Comment to disable serial output debugging */
#define SERIAL_DEBUG_OUTPUT_ENABLE

#ifdef SERIAL_0
    #define serial_print(x) Serial.print(x)
    #define serial_read() Serial.read()
    #define serial_available() Serial.available()
    #define serial_print_ln(x) Serial.println(x)
#endif

#ifdef SERIAL_1
    #define serial_print(x) Serial1.print(x)
    #define serial_read() Serial1.read()
    #define serial_available() Serial1.available()
    #define serial_print_ln(x) Serial1.println(x)
#endif

#ifdef SERIAL_2  //RX: PA3  TX: PA2
    #define serial_print(x) Serial2.print(x)
    #define serial_read() Serial2.read()
    #define serial_available() Serial2.available()
    #define serial_print_ln(x) Serial2.println(x)
#endif

#ifdef SERIAL_3
    #define serial_print(x) Serial3.print(x)
    #define serial_read() Serial3.read()
    #define serial_available() Serial3.available()
    #define serial_print_ln(x) Serial3.println(x)
#endif

const String device_name = "CarpeDiem Alarm Clock";

#define SETTING_ON_BOARD_LED_PIN PC13
#define SETTINGS_BAUD_RATE 9600
#define SETTING_SERIAL_DATA_COMMAND_SIZE 12

#define BUZZER_PIN PB12

#define JOYSTICK_PIN_Y PA6      // Analog Y
#define JOYSTICK_PIN_X PA7      // Analog X
#define JOYSTICK_PIN_SW PB11    // Switch (Top)

#define JOYSTICK_MEDIAN_VALUE 2900  // Joystick "middle" position analog value
#define JOYSTICK_THRESHOLD 500      // Threshold for left / right / up / down
#define JOYSTICK_THRESHOLD_LEFT (JOYSTICK_MEDIAN_VALUE - JOYSTICK_THRESHOLD)
#define JOYSTICK_THRESHOLD_RIGHT (JOYSTICK_MEDIAN_VALUE + JOYSTICK_THRESHOLD)
#define JOYSTICK_THRESHOLD_UP (JOYSTICK_MEDIAN_VALUE - JOYSTICK_THRESHOLD)
#define JOYSTICK_THRESHOLD_DOWN (JOYSTICK_MEDIAN_VALUE + JOYSTICK_THRESHOLD)

/* Alarm clock statuses */
bool status_alarm;              // Alarm on / off
bool status_alarm_running;      // Alarm running
bool status_buzzer;             // Buzzer (sound) on / off
bool status_rgb;                // Display on / off

enum
{
    STATUS_ALARM,
    STATUS_BUZZER,
    STATUS_RGB
};

bool serial_debug_output;

#endif

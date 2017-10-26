#ifndef SETTINGS_H
#define SETTINGS_H

//#define SERIAL_0 // USB
//#define SERIAL_1
#define SERIAL_2
//#define SERIAL_3

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

#define SETTING_ON_BOARD_LED_PIN PC13
#define SETTINGS_BAUD_RATE 4800
#define SETTING_SERIAL_DATA_COMMAND_SIZE 10

#endif

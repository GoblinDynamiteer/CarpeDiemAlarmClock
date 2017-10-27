# CarpeDiemAlarmClock
Project for course "Realtidssystem"  
Mjukvaruutvecklare inbyggda system  @ [MÖLK Utbildning](http://dev.molk.com)  
Embedded software developing  

### Project members:  
Dylan Saleh [LinkedIn](https://www.linkedin.com/in/dylansaleh)  
Johan Kämpe [LinkedIn](linkedin.com/in/johankampe) | [GitHub](https://github.com/GoblinDynamiteer)  
Pay-Shin Quach [LinkedIn](https://www.linkedin.com/in/pay-shin-quach-6b276113b)  
Stefan Ekström [LinkedIn](https://www.linkedin.com/in/stefan-ekstr%C3%B6m-47717147)  

### Project goals  
CarpeDiemAlarmClock is an alarm clock that is waking you up "gently" by gradually increasing the intensity of a NeoPixel LED-ring, before the alarm hits.  

- The alarm clock also has an option to sound a buzzer at alarm time.  
- The alarm clock will have several modes: Alarm on/off, sound on/off, light on/off.  

### Code 
- Code is built with the Arduino core for an STM32F103C8 devboard, using the [STM32duino](https://github.com/rogerclarkmelbourne/Arduino_STM32) tools.  
- FreeRTOS is used, with several tasks and semaphores.  

### Hardware 
- STM32F103C8 devboard (Bluepill clone)
- Adafruit NeoPixel 24-LED ring (show hour/minute, wake up, cool light shows)
- Adafruit NeoPixel 8-LED strip (show seconds in binary format, and status)
- DS3231 RTC Breakout board  
- HC‑05 bluetooth module (for serial communication / app)
- Joystick module  (user input, setting alarm/time etc)

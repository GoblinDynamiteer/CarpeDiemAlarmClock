# CarpeDiemAlarmClock
Project for course "Realtidssystem"  
Mjukvaruutvecklare inbyggda system  @ [MÖLK Utbildning](http://dev.molk.com)  
Embedded software developing  

![The clock!](https://raw.githubusercontent.com/GoblinDynamiteer/CarpeDiemAlarmClock/master/doc/img/photos/complete_build_clock_mode.jpg)  

### Project members:  
Dylan Saleh [LinkedIn](https://www.linkedin.com/in/dylansaleh)  
Johan Kämpe [LinkedIn](linkedin.com/in/johankampe) | [GitHub](https://github.com/GoblinDynamiteer)  
Pay-Shin Quach [LinkedIn](https://www.linkedin.com/in/pay-shin-quach-6b276113b)  
Stefan Ekström [LinkedIn](https://www.linkedin.com/in/stefan-ekstr%C3%B6m-47717147)  

### Videos
YouTube  
[CarpeDiem AlarmClock Showcase](https://www.youtube.com/watch?v=_YS_Tcxn2Ls)  
[Clock display with seconds as binary](https://www.youtube.com/watch?v=4Z99qmlPT-4)  
[Mode switching](https://www.youtube.com/watch?v=f26hjNdRtAU)  
[Alarm](https://www.youtube.com/watch?v=duoRIRUpNNA)  
["Until Alarm"-buildup](https://www.youtube.com/watch?v=sp_SiLhKh64)  
[Joystick & Mode Switch Test](https://youtu.be/ULnAHqrvtyQ)  

### Project goals  
CarpeDiemAlarmClock is an alarm clock that is waking you up "gently" by gradually increasing the intensity of a NeoPixel LED-ring, before the alarm hits.  

- The alarm clock shall also has an option to sound a buzzer at alarm time.  
- User must be able to set clock and alarm time  
- The alarm clock will have at least the following modes: Alarm on/off, sound on/off, light on/off.  
- Time will be displayed with NeoPixel devices  

### Project extras  
- Serial commands / debugging  
- Display light shows / demos instead of clock time  

### Code
- Code is built with the Arduino core for an STM32F103C8 devboard, using the [STM32duino](https://github.com/rogerclarkmelbourne/Arduino_STM32) tools.  
- FreeRTOS is used, with several tasks and semaphores.  

### Hardware
- STM32F103C8 devboard (Bluepill clone)
- Adafruit NeoPixel 24-LED ring (show hour/minute, wake up, cool light shows)
- Adafruit NeoPixel 8-LED strip (show seconds in binary format, and status)
- DS3231 RTC Breakout board  
- HC-05 bluetooth module (for serial communication / app)
- Joystick module  (user input, setting alarm/time etc)

### Images  
Serial commands   
![Serial commands](https://raw.githubusercontent.com/GoblinDynamiteer/CarpeDiemAlarmClock/master/doc/img/screenshots/serial_commands.png)  

Clock display test   
18:45  
![clock_1845](https://raw.githubusercontent.com/GoblinDynamiteer/CarpeDiemAlarmClock/master/doc/img/photos/clock_display_18_45_edit.png)  
![clock_1845_arms](https://raw.githubusercontent.com/GoblinDynamiteer/CarpeDiemAlarmClock/master/doc/img/photos/clock_display_18_45_edit_clock_arms.png)  

SET arduino_path="C:\Program Files (x86)\Arduino\arduino_debug.exe"
SET ino_file=%~dp0code\main\CarpeDiemAlarmClock\CarpeDiemAlarmClock.ino
SET opt --verify --verbose-build --board Arduino_STM32:STM32F1:genericSTM32F103C:device_variant=STM32F103C8
SET build_path=%~dp0code\build
%arduino_path% --pref build.path=%build_path% %opt:"=% %ino_file%
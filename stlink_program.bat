SET stlink_path="C:\Program Files (x86)\STMicroelectronics\STM32 ST-LINK Utility\ST-LINK Utility\ST-LINK_CLI.exe"
SET bin_path=%~dp0code\build\CarpeDiemAlarmClock.ino.bin
SET address=0x08000000
SET verify_mode="while_programming"
SET settings=HOTPLUG
%stlink_path% -c %settings% -P %bin_path% %address% -V %verify_mode% -Rst -Run
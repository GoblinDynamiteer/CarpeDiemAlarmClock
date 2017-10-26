/*  CarpeDiem Alarm clock

    command.ino

    Handles serial commands
 */

#include <MapleFreeRTOS900.h>
#include "rtc.h"
#include "rgb.h"
#include "settings.h"
#include "command.h"

void command_init()
{
    serial_data.reserve(SETTING_SERIAL_DATA_COMMAND_SIZE);;
    serial_data_complete = true;
}

void handle_command()
{
    serial_print_ln("Got command " + serial_data);
    serial_data_complete = true;
    serial_data = "";
}

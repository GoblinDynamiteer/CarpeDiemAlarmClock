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
    serial_data.reserve(SETTING_SERIAL_DATA_COMMAND_SIZE);
    serial_data_complete = true;
}

void handle_command()
{
    serial_print_ln("Got command " + serial_data);

    switch (serial_data[0])
    {
        case 'S': // Set time/date
            serial_print_ln(serial_data.substring(1, 3));
            serial_print_ln(serial_data.substring(3, 5));
            break;

        case 'T': // Print time
            serial_print_ln("HEJ!");
            //rtc_serial_print();
            break;

        case 'Q': // Print time
            serial_print_ln("Hello!");
            break;

        default:
            break;
    }

    serial_data_complete = true;
    serial_data = "";
}

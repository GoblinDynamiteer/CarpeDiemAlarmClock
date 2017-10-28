#define JOYSTICK_PIN_Y PA6
#define JOYSTICK_PIN_X PA7
#define JOYSTICK_PIN_SW PA5

#define JOYSTICK_MEDIAN_VALUE 2900
#define JOYSTICK_THRESHOLD 500
#define JOYSTICK_THRESHOLD_LEFT (JOYSTICK_MEDIAN_VALUE - JOYSTICK_THRESHOLD)
#define JOYSTICK_THRESHOLD_RIGHT (JOYSTICK_MEDIAN_VALUE + JOYSTICK_THRESHOLD)
#define JOYSTICK_THRESHOLD_UP (JOYSTICK_MEDIAN_VALUE - JOYSTICK_THRESHOLD)
#define JOYSTICK_THRESHOLD_DOWN (JOYSTICK_MEDIAN_VALUE + JOYSTICK_THRESHOLD)

enum{
    FULL_LEFT,
    MID_LEFT,
    FULL_RIGHT,
    MID_RIGHT,
    NEUTRAL,
    FULL_UP,
    MID_UP,
    FULL_DOWN,
    MID_DOWN
};

String dir_name[9] =
{
    " FULL_LEFT ",
    " MID_LEFT  ",
    " FULL_RIGHT",
    " MID_RIGHT ",
    " NEUTRAL   ",
    " FULL_UP   ",
    " MID_UP    ",
    " FULL_DOWN ",
    " MID_DOWN  "
};


int y;
int x;
int sw;

void setup()
{
    Serial2.begin(9600);
}

void loop()
{
    y = analogRead(JOYSTICK_PIN_Y);
    x = analogRead(JOYSTICK_PIN_X);
    sw = !digitalRead(JOYSTICK_PIN_SW);

    int XDIR = joystick_get_x();
    int YDIR = joystick_get_y();

    Serial2.print("Y: " + dir_name[YDIR] + " VAL " + String(y));
    Serial2.println("|  X: " + dir_name[XDIR] + " VAL " + String(x));
    delay(300);

}

int joystick_get_x()
{
    if (analogRead(JOYSTICK_PIN_X) < 20)
    {
        return FULL_LEFT;
    }

    if (analogRead(JOYSTICK_PIN_X) > 3600)
    {
        return FULL_RIGHT;
    }

    if (analogRead(JOYSTICK_PIN_X) < JOYSTICK_MEDIAN_VALUE - 800)
    {
        return MID_LEFT;
    }

    if (analogRead(JOYSTICK_PIN_X) > JOYSTICK_MEDIAN_VALUE + 800)
    {
        return MID_RIGHT;
    }

    return NEUTRAL;
}


int joystick_get_y()
{
    if (analogRead(JOYSTICK_PIN_Y) < 20)
    {
        return FULL_UP;
    }

    if (analogRead(JOYSTICK_PIN_Y) > 3600)
    {
        return FULL_DOWN;
    }

    if (analogRead(JOYSTICK_PIN_Y) < JOYSTICK_MEDIAN_VALUE - 800)
    {
        return MID_UP;
    }

    if (analogRead(JOYSTICK_PIN_Y) > JOYSTICK_MEDIAN_VALUE + 800)
    {
        return MID_DOWN;
    }

    return NEUTRAL;
}

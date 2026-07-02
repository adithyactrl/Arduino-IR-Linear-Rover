/*
==========================================================
            IR CONTROLLED LINEAR ROVER
==========================================================

Author : Adithya J

Description
-----------
A simple Arduino rover controlled using an IR remote.

Features
--------
✔ Forward
✔ Reverse
✔ Stop
✔ LED Direction Indicators

Hardware
--------
IR Receiver        -> D2
Red LED            -> D3
White LED          -> D4
Front Servo        -> D6
Rear Servo         -> D7

Remote Codes
------------
Forward : 0xEF10BF00UL
Reverse : 0xEE11BF00UL
Stop    : 0xED12BF00UL

==========================================================
*/

#include <Servo.h>
#include <IRremote.hpp>

/* -------------------- Pins -------------------- */

#define RED_LED          3
#define WHITE_LED        4

#define IR_PIN           2

#define FRONT_SERVO_PIN  6
#define REAR_SERVO_PIN   7

/* ---------------- Servo Objects ---------------- */

Servo frontServo;
Servo rearServo;

/* ---------------- Robot States ---------------- */

const int STOP     = 0;
const int FORWARD  = 1;
const int REVERSE  = 2;

int state = STOP;

/* ---------------- Remote Codes ---------------- */

const unsigned long FORWARD_CODE = 0xEF10BF00UL;
const unsigned long REVERSE_CODE = 0xEE11BF00UL;
const unsigned long STOP_CODE    = 0xED12BF00UL;

/* ================================================= */

void setup()
{
    pinMode(RED_LED, OUTPUT);
    pinMode(WHITE_LED, OUTPUT);

    frontServo.attach(FRONT_SERVO_PIN);
    rearServo.attach(REAR_SERVO_PIN);

    IrReceiver.begin(IR_PIN, ENABLE_LED_FEEDBACK);
}

/* ================================================= */

void moveForward()
{
    frontServo.write(180);
    rearServo.write(180);

    digitalWrite(WHITE_LED, HIGH);
    digitalWrite(RED_LED, LOW);
}

/* ================================================= */

void moveReverse()
{
    frontServo.write(0);
    rearServo.write(0);

    digitalWrite(WHITE_LED, LOW);
    digitalWrite(RED_LED, HIGH);
}

/* ================================================= */

void stopRobot()
{
    frontServo.write(90);
    rearServo.write(90);

    digitalWrite(WHITE_LED, LOW);
    digitalWrite(RED_LED, LOW);
}

/* ================================================= */

void loop()
{
    if (IrReceiver.decode())
    {
        unsigned long code =
        IrReceiver.decodedIRData.decodedRawData;

        switch(code)
        {
            case FORWARD_CODE:
                state = FORWARD;
                break;

            case REVERSE_CODE:
                state = REVERSE;
                break;

            case STOP_CODE:
                state = STOP;
                break;
        }

        IrReceiver.resume();
    }

    switch(state)
    {
        case FORWARD:
            moveForward();
            break;

        case REVERSE:
            moveReverse();
            break;

        default:
            stopRobot();
            break;
    }
}

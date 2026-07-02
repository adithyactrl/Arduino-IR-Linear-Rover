#include <Servo.h>
#include <IRremote.hpp>

//IR Remote Libs(v4 or something)

#define Red 3
#define White 4
#define IR 2
#define front 6
#define back 7
Servo frontServo;
Servo backServo;
// two servos defined each for front and back respectively
int state = 0;


// 0 = Stop
// 1 = Forward
// 2 = Reverse


void setup()
{
  pinMode(Red, OUTPUT);
  pinMode(White, OUTPUT);
  frontServo.attach(front);
  backServo.attach(back);
  IrReceiver.begin(IR, ENABLE_LED_FEEDBACK);     //no arguemnts taken
}


void loop(){
// We run a test code to assign each button to a task i,e the hexdecimal code we get below
    if (IrReceiver.decode())
    {
        switch (IrReceiver.decodedIRData.decodedRawData)
        {
            case 0xEF10BF00UL:   // Front
                state = 1;
                break;

            case 0xEE11BF00UL:   // Back
                state = 2;
                break;

            case 0xED12BF00UL:   // Stop
                state = 0;
                break;
        }

        IrReceiver.resume();
    }

    if(state == 1)
    {
        frontServo.write(180);
        backServo.write(180);
      //foreward we go

        digitalWrite(White, HIGH);
        digitalWrite(Red, LOW);
    }
    else if(state == 2)
    {
        frontServo.write(0);
        backServo.write(0);
      //back we go

        digitalWrite(White, LOW);
        digitalWrite(Red, HIGH);
    }
    else
    {
        frontServo.write(93);
        backServo.write(93);
      //we aint going nowhere, 93 is sweet spot i think 

        digitalWrite(White, LOW);
        digitalWrite(Red, LOW);
    }
}

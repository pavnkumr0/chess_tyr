#include <Stepper.h>

// Number of steps per output rotation
const int stepsPerRevolution = 200;

// Create Instance of Stepper library
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);
Stepper rowStepper(stepsPerRevolution, 4, 5, 6, 7);


void setup()
{
  // set the speed at 60 rpm:
  myStepper.setSpeed(200);
    rowStepper.setSpeed(200);
  // initialize the serial port:
  Serial.begin(9600);
    pinMode(A0, OUTPUT);
      pinMode(A1, OUTPUT);
        pinMode(A2, OUTPUT);
      pinMode(A3, OUTPUT);

   //............here for 1st col or 891011.................
//     digitalWrite(A0, HIGH);
//
//      digitalWrite(A1, HIGH);


   //............here for 2nd row or 4567.................
      
      digitalWrite(A2, HIGH);

      digitalWrite(A3, HIGH);
}

void loop() 
{

  Serial.println("clockwise");
  rowStepper.step(-stepsPerRevolution);


}
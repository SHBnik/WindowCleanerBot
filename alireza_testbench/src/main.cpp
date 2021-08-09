#include <Arduino.h>

/*Example sketch to control a stepper motor with A4988 stepper motor driver, AccelStepper library and Arduino: acceleration and deceleration. More info: https://www.makerguides.com */
// Include the AccelStepper library:
#include <AccelStepper.h>
// Define stepper motor connections and motor interface type. Motor interface type must be set to 1 when using a driver:
#define dirPin 3
#define stepPin 4
#define motorInterfaceType 1
// Create a new instance of the AccelStepper class:
AccelStepper stepper = AccelStepper(motorInterfaceType, stepPin, dirPin);
void setup() {
  // Set the maximum speed and acceleration:
  Serial.begin(9600);
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);
  pinMode(10,INPUT);
  stepper.setMaxSpeed(600);
  stepper.setAcceleration(8000);
// stepper.setSpeed(-1000);

}
void loop() {

  uint16_t knob = analogRead(A2);
  if(knob > 420 && knob < 530){
    stepper.setSpeed(0);
    stepper.runSpeed();
  }
  else if(knob <= 490){
    stepper.setSpeed(map(knob,420,0,0,-600));
    stepper.runSpeed();
  }
  else if(knob >= 510){
    stepper.setSpeed(map(knob,530,1023,0,600));
    stepper.runSpeed();
  }

  if(!digitalRead(10)){
    stepper.setCurrentPosition(0);
  }

  // if(analogRead(A1) == 1023){
  //   stepper.moveTo(26000);
  //   stepper.runToPosition();
  // }
}
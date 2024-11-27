/**
 * motion1.ino
 * Group 6: Zihan Zhao, Bertrand Juan, Marco Chen
 * Behavior: Make robot drive forward 1 meter, stop 2 seconds, reverse 1 meter, stop 2 seconds. Repeat this 3 times.
 */

#include <rcc.h>
#include <Servo.h>

// <<<<<<<<<<<<<<<<<<<<<<< Setup >>>>>>>>>>>>>>>>>>>>>>
Servo servo;
int led = 13;
int leftIRSensor1 = A1, leftIRSensor2 = 2, rightIRSensor1 = 11, rightIRSensor2 = 12, middleIRSensor = A0;
int in1 = 5, in2 = 6, in3 = 7, in4 = 8;
int enA = 9, enB = 10;
int leftEncA = 3, leftEncB = 4, rightEncA = 2, rightEncB = 12; //These are opposite from in the rcc library because of different motor orientations (Will be explained in write-up)
Right_Dir_Odom rodom;
Left_Dir_Odom lodom;

// <<<<<<<<<<<<<<<<<< Gloabl Values >>>>>>>>>>>>>>>>>>>
// Structs
struct IRSensorData{
  int l2Value = 1;
  int l1Value = 1;
  int mValue = 1;
  int r1Value = 1;
  int r2Value = 1;
};

IRSensorData irData;

// <<<<<<<<<<<<<<<<<<<<< Functions >>>>>>>>>>>>>>>>>>>>
// Setup.ino functions
void setupMotorController();

// Drivetrain.ino functions
void drive(int move_spd);
void turn(int turn_spd);
int sensorDrive();

void setup() {
  setupMotorController(); //initializes all pinModes and GPIO connections
  Serial.begin(115200);
}

void loop() {
  //get left and right encoder data
  int lcount = lodom.getCount();
  int rcount = rodom.getCount();

  // robot moves forward 1 meter, stops 2 seconds, back 1 meter, stops 2 seconds, and repeats this a total of 3 times.
  for (int i = 0; i < 3; i++)
  {
    moveDistance(1.0); //move forward 1 meter
    delay(2000); //stop 2 seconds
    moveDistance(-1.0); //move backward 1 meter
    delay(2000); //stop 2 seconds
  }
  
  finishProcedure(); //light up the finish LED as a visual indicator of stopping
}

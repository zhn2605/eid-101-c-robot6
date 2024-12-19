<<<<<<< HEAD
/*
AS OF 
12/06/2024 
ARDUINO UNO HAS BEEN SWITCHED FOR AN ARDUINO MEGA
*/

#include <rcc.h>
#include <Wire.h>
#include <Servo.h>

// <<<<<<<<<<<<<<<<<<<<<<< Setup >>>>>>>>>>>>>>>>>>>>>>
Servo servo;

MPU6050 IMU;

// Mega pins
int led = 27;
int leftIRSensor2 = 26, leftIRSensor1 = 25, middleIRSensor = 24, rightIRSensor1 = 23, rightIRSensor2 = 22; 
int in1 = 6, in2 = 7, in3 = 8, in4 = 11;
int enA = 5, enB = 9;
int leftEncA = 3, leftEncB = 4, rightEncA = 2, rightEncB = 12;

// <<<<<<<<<<<<<<<<<< Gloabl Values >>>>>>>>>>>>>>>>>>>
// Structs
struct IRSensorData{
  int l2Value = 1;
  int l1Value = 1;
  int mValue = 1;
  int r1Value = 1;
  int r2Value = 1;
};

Right_Dir_Odom rodom;
Left_Dir_Odom lodom;

IRSensorData irData;

// Encoders
volatile long leftEncoderCount = 0;

// <<<<<<<<<<<<<<<<<<<<< Funcitons >>>>>>>>>>>>>>>>>>>>
// Setup
void setupMotorController();

// Drive
void drive(int move_spd);
void turn(int turn_spd);
int sensorDrive();

void setup() {
  setupComponents();
  Serial.begin(115200);
}

void loop() {
  // Driving loop
  int driving = 1;

  float Kp = 20;
  float Ki = .01;
  float Kd = 20 ;
  
  while (driving) {
    // Updating necessary sensors
    updateIR();
    int junction = identifyJunction();
    driving = PIDSensorDrive(Kp, Ki, Kd);
  }

  finishProcedure();
}
=======
/**
 * motion2.ino
 * Group 6: Zihan Zhao, Bertrand Juan, Marco Chen
 * Behavior: Make robot turn counterclockwise 90 degrees, stop 2 seconds, turn clockwise 90 degrees, stop 2 seconds. Repeat this 3 times.
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

  // robot turns 90 degrees counterclockwise, stops 2 seconds, turns 90 degrees clockwise, stops 2 seconds, and repeats this a total of 3 times.
  for (int i = 0; i < 3; i++)
  {
    turnAngle(-90.0); //turn 90 degrees counterclockwise
    delay(2000); //stop 2 seconds
    turnAngle(90.0); //turn 90 degrees clockwise
    delay(2000); //stop 2 seconds
  }
  
  finishProcedure(); //light up the finish LED as a visual indicator of stopping
}
>>>>>>> 993e03ca53f80d3e30909c735584acc1e3eaf744

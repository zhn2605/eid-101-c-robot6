/**
 * motion3.ino
 * Group 6: Zihan Zhao, Bertrand Juan, Marco Chen
 * Behavior: Have the robot move towards a wall, but stop when the contact point of the wheels with the ground is 300mm from the wall. 
 * When the robot stops take a measurement, or have an indicator on the ground showing where 300mm would be.
 */
 
#include <Servo.h>

#include "Sensors.h"

// <<<<<<<<<<<<<<<<<<<<<<< Setup >>>>>>>>>>>>>>>>>>>>>>
Servo servo;
int led = 27;
int leftIRSensor2 = 26, leftIRSensor1 = 25, middleIRSensor = 24, rightIRSensor1 = 23, rightIRSensor2 = 22;
int in1 = 6, in2 = 7, in3 = 8, in4 = 11;
int enA = 5, enB = 9;
int leftEncA = 12, leftEncB = 2, rightEncA = 23, rightEncB = 4;
Right_Dir_Odom rodom;
Left_Dir_Odom lodom;

bool isTurning = false;
int currentMillis = 0;

// <<<<<<<<<<<<<<<<<< Gloabl Values >>>>>>>>>>>>>>>>>>>
// Sensors library object
Sensors sensors;

// <<<<<<<<<<<<<<<<<<<<< Functions >>>>>>>>>>>>>>>>>>>>
// Setup.ino functions
void setupMotorController();

// Drivetrain.ino functions
void drive(int move_spd);
void turn(int turn_spd);
void turnAngle(float deg);
int sensorDrive();

void setup() {
  setupMotorController(); // initializes all pinModes and GPIO connections
  sensors.set_IR(leftIRSensor2, leftIRSensor1, middleIRSensor, rightIRSensor1, rightIRSensor2);
  Serial.begin(115200);
}

void loop() {
  // update IMU, Lidar, and Ultrasonic Sensor readings
  sensors.updateIMU();
  sensors.updateLidar();
  sensors.updateUltrasonic();

  // Have the robot approach 155 mm (calculated distance based on lidar angle and chassis length
  if (sensors.sensorData.lidar_dist > 156) // if the lidar detects 156 mm, drive forward
  {
    drive(-120); // drive forward (our lidar sensor is on the back of the robot, so we have to technically drive "backward" to drive forward)
  }
  else if (sensors.sensorData.lidar_dist < 154) // if the lidar detects 154 mm, then the robot overshot, so drive backward
  {
    drive(120); // drive backward (or lidar sensor is on the back of the robot, so we have to technically drive "forward" to drive backward)
  }
  else
  {
    finishProcedure(); // if the lidar detects between 154 and 156 mm, then stop the robot and turn on the LED
  }

}

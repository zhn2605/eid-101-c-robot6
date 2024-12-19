/**
 * motion3.ino
 * Group 6: Zihan Zhao, Bertrand Juan, Marco Chen
 * Behavior: Have the robot move towards a wall, but stop when the contact point of the wheels with the ground is 300mm from the wall. 
 * When the robot stops take a measurement, or have an indicator on the ground showing where 300mm would be.
 */

#include <rcc.h>
#include <Servo.h>

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
// Structs
struct IRSensorData{
  int l2Value = 1;
  int l1Value = 1;
  int mValue = 1;
  int r1Value = 1;
  int r2Value = 1;
};

struct IMUSensorData{
  // get the acceleration on the x-axis
  float accel_x = 0;

  // get the acceleration on the y-axis
  float accel_y = 0;

  // although we can get the acceleration on the z-axis, the reading is
  // incorrect as we have dicarded the gravity vector while calibrating
  float accel_z = 0;

  // get the angular velocity about the x-axis
  float ang_vel_x = 0;

  // get the angular velocity about the y-axis
  float ang_vel_y = 0;

  // get the angular velocity about the z-axis
  float ang_vel_z = 0;
  
  float theta = 0;
};

struct LIDARData{
  uint16_t dist = 0; // distance in mm (angled 45 degrees counterclockwise from horizontal)
};

struct ULTRASONICData{
  float dist = 0;  // (angled 45 degrees counterclockwise from horizontal)
};

IRSensorData irData;
IMUSensorData imuData;
LIDARData lidarData;
ULTRASONICData ultrasonicData;


// <<<<<<<<<<<<<<<<<<<<< Functions >>>>>>>>>>>>>>>>>>>>
// Setup.ino functions
void setupMotorController();

// Drivetrain.ino functions
void drive(int move_spd);
void turn(int turn_spd);
void turnAngle(float deg);
int sensorDrive();
void updateIMU();
void updateLidar();
void updateUltrasonic();

void setup() {
  setupMotorController(); // initializes all pinModes and GPIO connections
  Serial.begin(115200);
}

void loop() {
  // update IMU, Lidar, and Ultrasonic Sensor readings
  updateIMU();
  updateLidar();
  updateUltrasonic();

  // Have the robot approach 155 mm (calculated distance based on lidar angle and chassis length
  if (lidarData.dist > 156) // if the lidar detects 156 mm, drive forward
  {
    drive(-120); // drive forward (our lidar sensor is on the back of the robot, so we have to technically drive "backward" to drive forward)
  }
  else if (lidarData.dist < 154) // if the lidar detects 154 mm, then the robot overshot, so drive backward
  {
    drive(120); // drive backward (or lidar sensor is on the back of the robot, so we have to technically drive "forward" to drive backward)
  }
  else
  {
    finishProcedure(); // if the lidar detects between 154 and 156 mm, then stop the robot and turn on the LED
  }

}

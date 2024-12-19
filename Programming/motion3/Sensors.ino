
/*
 * Sensors.ino
 * Group 6: Zihan Zhao, Bertrand Juan, Marco Chen
 * This file contains functions that get and process the signals of the robot's sensors.
 */

/*
 * Updates all IR sensors using digitalRead.
 */

#include <Wire.h>
#include <rcc.h>
MPU6050 imu;
HC_SR04 ultrasonic;
VL53L0X lidar; //Instantiate an instance of the lidar class

unsigned long duration_us; // keeps track of ultrasonic sensor's uptime

float dt = 0; // dt changes dynamically as the code goes on; used for IMU calculations
float lastTime = 0;
float currentTime = 0;
float theta = 0;

void updateIR() {
    irData.l2Value = digitalRead(leftIRSensor2);
    irData.l1Value = digitalRead(leftIRSensor1);
    irData.mValue = digitalRead(middleIRSensor);
    irData.r1Value = digitalRead(rightIRSensor1);
    irData.r2Value = digitalRead(rightIRSensor2);
    
    //serial.print lines for debugging
    if (irData.l1Value == 1) {
      Serial.println("Left scanned!");
    }
    if (irData.r1Value == 1) {
      Serial.println("Right scanned!");
    }
    if (irData.mValue == 1) {
      Serial.println("Middle scanned!");
    }
}

/*
 * Identifies junctions based on IR sensor values.
 */
int identifyJunction() {
    int l1Value = irData.l1Value;
    int l2Value = irData.l2Value;
    int mValue = irData.mValue;
    int r1Value = irData.r1Value;
    int r2Value = irData.r2Value;
    
    // Identify Left turn
    if ((l1Value == 0 && l2Value == 0) && (mValue == 0 && (r1Value == 1 || r2Value == 1))) {
      return 0;
    }
    // Identify Right turn
    if ((r1Value == 0 && r2Value == 0) && (mValue == 0 && (l1Value == 1 || l2Value == 1))) {
      return 1;
    }
    // Identify T stop
    if ((r1Value == 0 && r2Value == 0 && l1Value == 0 && l2Value == 0 && mValue == 1)) {
      return 3;  
    }
    // Identify Cross OR full box OR ...
    if ((r1Value == 0 && r2Value == 0 && l1Value == 0 && l2Value == 0 && mValue == 0)) {
      return 4;
    }
    // Identify Offtrack
    if (r1Value && r2Value && l1Value && l2Value && mValue) {
      return 5;
    } 
    // Unidentified
    return 6;
}

// updates IMU using imu.update()
void updateIMU() {
  // gets new readings from sensor
  imu.update();

  // get the acceleration on the x-axis
  imuData.accel_x = imu.getAccelX();

  // get the acceleration on the y-axis
  imuData.accel_y = imu.getAccelY();

  // although we can get the acceleration on the z-axis, the reading is
  // incorrect as we have dicarded the gravity vector while calibrating
  imuData.accel_z = imu.getAccelZ();

  // get the angular velocity about the x-axis
  imuData.ang_vel_x = imu.getAngVelX();

  // get the angular velocity about the y-axis
  imuData.ang_vel_y = imu.getAngVelY();

  // get the angular velocity about the z-axis
  imuData.ang_vel_z = imu.getAngVelZ();

  currentTime = millis(); // current time is the time since the arduino started
  dt = (currentTime - lastTime) / 1000.0; // gets dt, and converts from milliseconds to seconds
  lastTime = currentTime;

  imuData.theta = imuData.theta + ((imuData.ang_vel_z) * (dt));

/**
//  //debugging lines
//  Serial.print("ax, ay: ");
//  Serial.print(imuData.accel_x);
//  Serial.print(", ");
//  Serial.print(imuData.accel_y);
//  Serial.print(" wx, wy, wz: ");
//  Serial.print(imuData.ang_vel_x);
//  Serial.print(", ");
//  Serial.print(imuData.ang_vel_y);
//  Serial.print(", ");
//  Serial.print(imuData.ang_vel_z);
//  Serial.print(" theta: ");
//  Serial.print(imuData.theta);
//  Serial.println();
**/

}

// updates lidar sensor using getFastReading
void updateLidar()
{
  lidarData.dist = getFastReading(&lidar); //Use rcc helper func to get most recent distance reading
  Serial.print("          Lidar Distance: ");
  Serial.print(lidarData.dist);
  Serial.print(" mm");

  Serial.println(" ");
}

// updates ultrasonic sensor using getFastReading
void updateUltrasonic()
{
  // get the reading with the default timeout of 5000 microseconds
  duration_us = ultrasonic.pulse();

  ultrasonicData.dist = duration2centimeters(duration_us);
/**
//  // debugging print statements
//  Serial.print("Ultrasonic Distance: ");
//  Serial.print(ultrasonicData.dist);
//  Serial.print(" cm ");
**/
}

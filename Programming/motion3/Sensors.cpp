#include "Sensors.h"

Sensors::Sensors() {

}

void Sensors::set_IR(int lIR2, int lIR1, int mIR, int rIR1, int rIR2) {
    leftIRSensor2 = lIR2;
    leftIRSensor1 = lIR1;
    middleIRSensor = mIR;
    rightIRSensor1 = rIR1;
    rightIRSensor2 = rIR2;
}

// IR Sensor
void Sensors::updateIR() {
    sensorData.l2Value = digitalRead(leftIRSensor2);
    sensorData.l1Value = digitalRead(leftIRSensor1);
    sensorData.mValue = digitalRead(middleIRSensor);
    sensorData.r1Value = digitalRead(rightIRSensor1);
    sensorData.r2Value = digitalRead(rightIRSensor2);
}

int Sensors::identifyJunction() {
    int l1Value = sensorData.l1Value;
    int l2Value = sensorData.l2Value;
    int mValue = sensorData.mValue;
    int r1Value = sensorData.r1Value;
    int r2Value = sensorData.r2Value;
    
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

// IMU Sensor
// updates IMU using imu.update()
void Sensors::updateIMU() {
  // gets new readings from sensor
  imu.update();

  // get the acceleration on the x-axis
  sensorData.accel_x = imu.getAccelX();

  // get the acceleration on the y-axis
  sensorData.accel_y = imu.getAccelY();

  // although we can get the acceleration on the z-axis, the reading is
  // incorrect as we have dicarded the gravity vector while calibrating
  sensorData.accel_z = imu.getAccelZ();

  // get the angular velocity about the x-axis
  sensorData.ang_vel_x = imu.getAngVelX();

  // get the angular velocity about the y-axis
  sensorData.ang_vel_y = imu.getAngVelY();

  // get the angular velocity about the z-axis
  sensorData.ang_vel_z = imu.getAngVelZ();

  currentTime = millis(); // current time is the time since the arduino started
  dt = (currentTime - lastTime) / 1000.0; // gets dt, and converts from milliseconds to seconds
  lastTime = currentTime;

  sensorData.theta = sensorData.theta + ((sensorData.ang_vel_z) * (dt));
}

void Sensors::updateLidar() {
    sensorData.lidar_dist = getFastReading(&lidar);
}

void Sensors::updateUltrasonic() {
    duration_us = ultrasonic.pulse();

    sensorData.ultrasonic_dist = duration2centimeters(duration_us);
}

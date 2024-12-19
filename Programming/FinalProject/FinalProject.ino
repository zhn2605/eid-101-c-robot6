#include <rcc.h>
#include <Wire.h>
#include <Servo.h>

// Custom sensor library


#define DELAY_TIME 3000/128

// <<<<<<<<<<<<<<<<<<<<<<< Setup >>>>>>>>>>>>>>>>>>>>>>
Servo servo;

MPU6050 IMU;

int led = 13;
int leftIRSensor1 = A1, leftIRSensor2 = A3, rightIRSensor1 = 11, rightIRSensor2 = A4, middleIRSensor = A0;
int in1 = 5, in2 = 6, in3 = 7, in4 = 8;
int enA = 9, enB = 10;
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

  float Kp = 25;
  float Ki = .01;
  float Kd = 10;
  
  while (driving) {
    // Updating necessary sensors
    updateIR();
    int junction = identifyJunction();
    driving = PIDSensorDrive(Kp, Ki, Kd);
  }

  finishProcedure();
}

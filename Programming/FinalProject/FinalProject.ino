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
int clawLift = 11;

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

int junctionCount = 0;

void setup() {
  setupMotorController();
  Serial.begin(115200);
}

void loop() {
  // Driving loop
  int driving = 1;

  // Track specific
  // Track A
  int maxJunctions = 3;

  float Kp = 20;
  float Ki = .01;
  float Kd = 20 ;

  int state = 1; // driving state
  
  while (state > 0) {
    // Updating necessary sensors
    int junction = identifyJunction();
    
    updateIR();
    if (state == 1) {
      state = PIDSensorDrive(Kp, Ki, Kd); 
    } 
    
    else if (state == 2) {
        updateIR();
        junction = identifyJunction();
      
        // Junction type 1: Full white
        if (junction == 5) {
            moveDistance(-.0300);
            updateIR();
            junction = identifyJunction();

            if (junction == 4) {
                state = 0;  
            } else {
                turnAngle(180);  
            }
        } else if (junction != 5){
            moveDistance(.0257);  
            updateIR();
            junction=identifyJunction();

            if (junction != 5) {
                moveDistance(-.0300);
                turnAngle(-90);
            }
        }
        state = 1;
    }
  }
  
  // analogWrite(clawLift, 180);
  // delay(1000);
  
  // analogWrite(clawLift, 0);

  finishProcedure();
}

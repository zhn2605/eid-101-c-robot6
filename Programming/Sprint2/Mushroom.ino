#include <rcc.h>
#include <Servo.h>

#define DELAY_TIME 3000/128

// <<<<<<<<<<<<<<<<<<<<<<< Setup >>>>>>>>>>>>>>>>>>>>>>
Servo servo;
int led = 13;
int leftIRSensor1 = A1, leftIRSensor2 = 2, rightIRSensor1 = 11, rightIRSensor2 = 12, middleIRSensor = A0;
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
  setupMotorController();
  Serial.begin(115200);
}

void loop() {
  // Testing encoder
  // Opposite from library due to opposite orientation when setting up wheels
  int lcount = lodom.getCount();
  int rcount = rodom.getCount();
  
  Serial.print("Value of left encoder: ");
  Serial.println(lcount);
  //Serial.print("Value of right encoder: ");
  //Serial.println(rcount);
  // 1920 pins = 1 rotation
  moveDistance(.1);
  delay(1000);
  turnAngle(270.0);
  delay(1000);
  moveDistance(-.1);
  delay(1000);
  turnAngle(270.0);
  
  /*
  // Driving loop
  int driving = 1;
  
  while (driving) {
    // Updating necessary sensors
    updateIR();
    int junction  identifyJunction();
    driving = sensorDrive();
  }
  */

  finishProcedure();
}

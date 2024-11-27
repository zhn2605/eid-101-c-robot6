/*
 * Simple Sensor Integration Algorithm
 * An IR sensor is placed on the back of the robot
 * The robot will move backward until the IR sensor detects a wall
 * When the robot detects a wall, it will permanently stop
 */

// initialize sensor and motor encoder pins for organization
int backSensor = 3; // the sensor on the back of the robot outputs to D3
int backSensorValue = 0; //0 is detecting, 1 isn't detecting
int in1 = 5; //in1 initalized to D5
int in2 = 6; //in2 initalized to D6
int in3 = 7; //in3 initalized to D7
int in4 = 8; //in4 initalized to D8
int enA = 9; //enA initalized to D9
int enB = 10;//enB initalized to D10

void setup() {
  //initialize pinMode of motor encoder input pins and backSensor
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(backSensor, INPUT); 
  Serial.begin(9600);
}

void loop() {
  backSensorValue = digitalRead(backSensor); // use digitalRead to collect the current value of backSensor

  // if robot does not detect wall, move backward
  if (backSensorValue == 1)
  {
    Serial.println("Motor moving backward");
    digitalWrite(in2, HIGH);
    digitalWrite(in3, HIGH);
    analogWrite(enA, 180);
    analogWrite(enB, 180);
  }
  //if robot detects wall, stop forever
  else if (backSensorValue == 0)
  {
    Serial.println("Stop motor");
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    analogWrite(enA, 0);
    analogWrite(enB, 0);
    // stop forever to eliminate possibility of crashing in the event of a malfunction
    while(true)
    {
      //do nothing
    }
  }
}

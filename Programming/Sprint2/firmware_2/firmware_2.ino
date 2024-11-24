#include <rcc.h>
#include <Servo.h>

#define DELAY_TIME 3000/128

Servo servo;

int enA = 9, enB = 10;
int in1 = 2, in2 = 3, in3 = 4, in4 = 5;
int left_ir = 6, right_ir = 7;

void setup() {
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(left_ir, INPUT);
  pinMode(right_ir, INPUT);
}

// Motor Controller Library
void drive_move(int move_spd) {
  if (move_spd < 0) {
    digitalWrite(in2, HIGH);
    digitalWrite(in3, HIGH);  
  } else {
    digitalWrite(in1, HIGH);
    digitalWrite(in4, HIGH);  
  }

  analogWrite(enA, move_spd);
  analogWrite(enB, move_spd);
}

void drive_turn(int deg, int turn_spd) {
  // Use encoder ticks to verify for better accuracy & future use
  // For now, a estimated fcn will be used from deg -> time.
  // Assume 90 deg = 540 ms

  turn_time = abs(deg) * 6;
  
  if (deg > 0) {
    digitalWrite(in2, HIGH);
    digitalWrite(in4, HIGH);  
  } else {
    digitalWrite(in1, HIGH);
    digitalWrite(in3, HIGH);  
  }

  analogWrite(enA, turn_spd);
  analogWrite(enB, turn_spd);
  delay(turn_time);
}

void drive_stop(int dt) {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  analogWrite(enA, 0);
  analogWrite(enB, 0);
  delay(dt);
}

int sensor_read() {
    ir_left_value = digitalRead(left);
    ir_right_value = digitalRead(right);
    if (!ir_left_value && !ir_right_value) {
      return 0;
    } else if (ir_left_value && !ir_right_value) {
      return 1;  
    } else if (!ir_left_value && !ir_right_value){ 
      return 2; 
    } else {
      return -1;    
    }
}

void ()

void loop() {
  // Move fwd
  drive_move(200);
  delay(2000);
  //Reset
  drive_stop(1000);
  
  // Move back
  drive_move(-200);
  delay(2000);
  drive_stop(1000);
  
  // Turn right
  drive_turn(90, 180);
  drive_stop(1000);
  
  // Turn left
  drive_turn(-90, 180);
  drive_stop(1000);
  
}

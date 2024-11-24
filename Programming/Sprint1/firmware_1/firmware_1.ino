#include <rcc.h>
#include <Servo.h>

#define DELAY_TIME 3000/128

Servo servo;

int enA = 9, enB = 10;
int in1 = 2, in2 = 3, in3 = 4, in4 = 5;

void setup() {
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}


// Functions for LED signal
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
  if (deg > 0) {
    digitalWrite(in2, HIGH);
    digitalWrite(in4, HIGH);  
  } else {
    digitalWrite(in1, HIGH);
    digitalWrite(in3, HIGH);  
  }

  analogWrite(enA, turn_spd);
  analogWrite(enB, turn_spd);
}

void pause(int dt) {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  analogWrite(enA, 0);
  analogWrite(enB, 0);
  delay(dt);
}

void loop() {
  // Move fwd
  drive_move(200);
  delay(2000);
  //Reset
  pause(1000);
  
  // Move back
  drive_move(-200);
  delay(2000);
  pause(1000);
  
  // Turn right
  drive_turn(90, 180);
  delay(1000);
  pause(1000);
  
  // Turn left
  drive_turn(-90, 180);
  delay(1000);
  pause(1000);
  
}

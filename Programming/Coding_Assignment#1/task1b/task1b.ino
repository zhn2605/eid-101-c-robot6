#include <rcc.h>
#include <Servo.h>

#define DELAY_TIME 3000/128

Servo servo;

int motor = 9;

void setup() {
  pinMode(motor, OUTPUT);
  // put your setup code here, to run once:
}

void loop() {
  // Determing dead band
  analogWrite(motor, 100);
  // STOPPED spinning
}

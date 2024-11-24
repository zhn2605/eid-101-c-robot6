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
  for (int i = 0; i < 128; i++) {
      analogWrite(motor, i);
      delay(DELAY_TIME);
  }

  for (int i = 127; i > 0; i--) {
      analogWrite(motor, i);
      delay(DELAY_TIME);
  }
}

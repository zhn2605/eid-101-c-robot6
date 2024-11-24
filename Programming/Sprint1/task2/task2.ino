#include <rcc.h>
#include <Servo.h>

Servo servo;

int motor = 9;
int photoresistor = 3;

void setup() {
  pinMode(motor, OUTPUT);

  Serial.begin(115200);
  // put your setup code here, to run once:
}

void loop() {
  int light = detectLight();
  int caliberatedStartValue = 25;
  
  if (light <= caliberatedStartValue) {
    motorStop();
  } else {
    motorSpin();  
  }

  Serial.println(light);
  delay(250);
}

int detectLight() {
    int lightValue = analogRead(A0);
    return lightValue;
    
}

void motorSpin() {
    analogWrite(motor, 127);
  }

void motorStop() {
    analogWrite(motor, 0);
  }

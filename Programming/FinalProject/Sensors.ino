/*
 * Sensors.ino
 * Group 6: Zihan Zhao, Bertrand Juan, Marco Chen
 * This file contains functions that get and process the signals of the robot's sensors.
 */

/*
 * Updates all IR sensors using digitalRead.
 */
void updateIR() {
    irData.l2Value = digitalRead(leftIRSensor2);
    irData.l1Value = digitalRead(leftIRSensor1);
    irData.mValue = digitalRead(middleIRSensor);
    irData.r1Value = digitalRead(rightIRSensor1);
    irData.r2Value = digitalRead(rightIRSensor2);
    
    //serial.print lines for debugging
    /* if (irData.l1Value == 1) {
      Serial.println("Left scanned!");
    }
    if (irData.r1Value == 1) {
      Serial.println("Right scanned!");
    }
    if (irData.mValue == 1) {
      Serial.println("Middle scanned!");
    }
	*/
}

/*
 * Identifies junctions based on IR sensor values. Not being utilized currently.
 */
int identifyJunction() {
    int l1Value = irData.l1Value;
    int l2Value = irData.l2Value;
    int mValue = irData.mValue;
    int r1Value = irData.r1Value;
    int r2Value = irData.r2Value;
    
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

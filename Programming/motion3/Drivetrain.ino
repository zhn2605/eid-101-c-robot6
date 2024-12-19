/*
 * Drivetrain.ino
 * Group 6: Zihan Zhao, Bertrand Juan, Marco Chen
 * This file contains functions that make the robot move.
 */

/*
 * Makes robot drive in a certain direction at a movement speed passed as a parameter.
 * If move_spd > 0, drive forward.
 * If move_spd <= 0, drive backward.
 */
void drive(int move_spd) {
    //if move_spd is positive, drive forward
    if (move_spd > 0) {
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
        digitalWrite(in3, LOW);
        digitalWrite(in4, HIGH);
    } else {
      //if move_spd is negative, drive backward
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
        digitalWrite(in3, HIGH);
        digitalWrite(in4, LOW);  
    }
    //set enA and enB to move_spd
    analogWrite(enA, abs(move_spd));
    analogWrite(enB, abs(move_spd));
}


/*
 * Makes robot turn in a certain direction at a turn speed passed as a parameter
 * If turn_spd > 0, turn right.
 * If turn_spd <= 0, turn left.
 */
void turn(int turn_spd) {
    //ensure robot is not moving (debugging lines)
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);

    //if turn_spd is positive, turn right
    if (turn_spd > 0) {
        digitalWrite(in2, HIGH);
        digitalWrite(in4, HIGH);
    } else {
      //if turn_spd is negative, turn left
        digitalWrite(in1, HIGH);
        digitalWrite(in3, HIGH);
    }

    //set enA and enB to turn_spd
    turn_spd = abs(turn_spd);
    analogWrite(enA, turn_spd);
    analogWrite(enB, turn_spd);
}

/*
 * 
 */
int sensorDrive() {
    int totalValue = 0;
    
    // Conditionals to change turn
    if (sensors.sensorData.l2Value) {
        totalValue += -2;
    }
    if (sensors.sensorData.l1Value) {
        totalValue += -1;
    }
    if (sensors.sensorData.mValue) {
        totalValue += 0;
    }
    if (sensors.sensorData.r1Value) {
        totalValue += 1;
    }
    if (sensors.sensorData.r2Value) {
      totalValue += 2;  
    }

    // Drive based on conditionals
    if (sensors.sensorData.mValue == 0 && sensors.sensorData.r1Value == 0 
    && sensors.sensorData.l1Value == 0 && sensors.sensorData.l2Value == 0 && sensors.sensorData.r2Value == 0) {
        drive(0);
        turn(0);  
        return 0;
    }
    

    if (totalValue == 0) {
        drive(180);
    } else if (totalValue == -1) {
        drive(50);
        analogWrite(enA, 20);
        analogWrite(enB, 160);
    } else if (totalValue <= -2) {
        digitalWrite(in2, HIGH);
        digitalWrite(in4, HIGH);
        analogWrite(enA, 100);
        analogWrite(enB, 250);
    } else if (totalValue == 1) {
        drive(50);
        analogWrite(enB, 20);
        analogWrite(enA, 160);
    } else if (totalValue >= 2) {
        digitalWrite(in1, HIGH);
        digitalWrite(in3, HIGH);;
        analogWrite(enB, 100);
        analogWrite(enA, 250);  
    }

    return 1;
}

void moveDistance(float meters) {
    // Conversion from meters to ticks
    int encoderCountPerRotation = 1920;
    int dir = (meters < 0 ? -1 : 1);
    int currEncoderCount = lodom.getCount();
    int targetEncoderCount = currEncoderCount + dir * (encoderCountPerRotation * (1000 / (80 * PI)));
    if (meters > 0){
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      digitalWrite(in3, LOW);
      digitalWrite(in4, HIGH);
      while (currEncoderCount < targetEncoderCount) {
        analogWrite(enA, 250);
        analogWrite(enB, 250);
        currEncoderCount = lodom.getCount();
      }
    } else if (meters < 0) {
      digitalWrite(in2, HIGH);
      digitalWrite(in1, LOW);
      digitalWrite(in4, LOW);
      digitalWrite(in3, HIGH);
      while (currEncoderCount > targetEncoderCount) {
        analogWrite(enA, 250);
        analogWrite(enB, 250);
        currEncoderCount = lodom.getCount();
      }
      
    }
   drive(0);
   turn(0);
}


// turns to approach "deg" relative to where the robot started
void turnAngle(float deg) {
    sensors.updateIMU(); // update IMU readings
    // turn left if angle is not yet reached (tolerance of 1 degree)
    if(sensors.sensorData.theta < deg - 1)
    {
      turn(-130);
    }
    // turn right if angle is slightly overshot (tolerance of 1 degree)
    else if (sensors.sensorData.theta > deg + 1) 
    {
      turn(130);
    }
    // stop the robot, and indicate that the robot is no longer turning
    else
    {
      turn(0);
      isTurning = false; // indicate that the robot is no longer turning
    }

}

void finishProcedure() {
  drive(0);
  turn(0);
  digitalWrite(led, HIGH);
  while (1) {
    }
}

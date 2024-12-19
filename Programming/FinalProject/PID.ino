float previousError = 0;
float errorIntegral = 0;
const int MAX_SPEED = 255;
const int BASE_SPEED = 180;

int driveSpeedCalc(int totalValue, float kp, float ki, float kd) {
    float Kp = kp;
    float Ki = ki;
    float Kd = kd;
    
    // Determine how off-track we are, AKA error
    float error = totalValue;

    // Determine P vatermlue, corresponding directly to error. AKA How much force do we put in to correct ourselves?
    float P = Kp * error;

    // Determine I term, corresponding to overall changes throughout the run. AKA how much have we deviated overall?
    errorIntegral += error;
    errorIntegral = constrain(errorIntegral, -100, 100);
    float I = Ki * errorIntegral;

    // Determine D term, corresponding to deltaError. AKA How much did we change from last iteration to current iteration?
    float D = Kd * (error - previousError);
    
    // Calculate motor speed
    float motorSpeed = P + I + D;

    return motorSpeed;
}

int PIDSensorDrive(float kp, float ki, float kd) {
    int totalValue = 0;
    
    // Conditionals to change turn
    if (irData.l2Value) {
        totalValue += -2;
    }
    if (irData.l1Value) {
        totalValue += -1;
    }
    if (irData.mValue) {
        totalValue += 0;
    }
    if (irData.r1Value) {
        totalValue += 1;
    }
    if (irData.r2Value) {
      totalValue += 2;  
    }

    // Drive based on conditionals. Need to include junctions in the future.
    if (irData.mValue == 0 && irData.r1Value == 0 && irData.l1Value == 0 && irData.l2Value == 0 && irData.r2Value == 0) {
        drive(0);
        turn(0);  
        return 0;
    }

    // Calculate motor speed
    float driveSpeed = driveSpeedCalc(totalValue, kp, ki, kd);

    // Calculate motor speed for each wheel
    int leftSpeed = constrain(BASE_SPEED - driveSpeed, 0, MAX_SPEED);
    int rightSpeed = constrain(BASE_SPEED + driveSpeed, 0, MAX_SPEED);

    if (totalValue > 0) {
        // Turning right
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
        digitalWrite(in3, LOW);
        digitalWrite(in4, HIGH);
        
        analogWrite(enA, leftSpeed);
        analogWrite(enB, rightSpeed);
    } else if (totalValue < 0) {
        // Turning left
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
        digitalWrite(in3, LOW);
        digitalWrite(in4, HIGH);
        
        analogWrite(enA, leftSpeed);
        analogWrite(enB, rightSpeed);
    } else {
        // Straight line
        drive(BASE_SPEED);
    }

    Serial.print(leftSpeed);
    Serial.print("     ");
    Serial.println(rightSpeed);
    
    return 1;
}

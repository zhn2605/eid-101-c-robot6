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
        digitalWrite(in1, HIGH);
        digitalWrite(in3, HIGH);
    } else {
      //if turn_spd is negative, turn left
        digitalWrite(in2, HIGH);
        digitalWrite(in4, HIGH);
    }

    //set enA and enB to turn_spd
    turn_spd = abs(turn_spd);
    analogWrite(enA, turn_spd);
    analogWrite(enB, turn_spd);
}

/*
 * Makes robot drive with logic that depends on the values of the IR sensors
 */
int sensorDrive() {
    int totalValue = 0; //initialize totalValue as 0 upon function call

    /**
    Note: totalValue is a value that tells us how far off the track the robot is
    The greater the magnitude of totalValue, the more "off-course" the robot is
    If totalValue is negative, the robot has to prioritize turning left to stay on the line
    If totalValue is positive, the robot has to prioritize turning right to stay on the line
    **/
    
    /*
	By using 5 IR sensors, we have a brief understanding of how "off track" our robot is.
	Using that information, we create different "Levels" of turning to steer the robot back on track.
	With negatives indicating a left turn and positives indicating a right turn, we can assign values
	that relates proportionally to how much force we should use into correcting the path of our robot.
	*/
    if (irData.l2Value) {
        totalValue += -2;
    }
    if (irData.l1Value) { //if the first sensor to the left detects the line, slightly lower totalValue
        totalValue += -1;
    }
    if (irData.mValue) {
        totalValue += 0; //if the middle center detects the line, don't change totalValue
    }
    if (irData.r1Value) { //if the first sensor to the right detects the line, slightly increase totalValue
        totalValue += 1;
    }
    if (irData.r2Value) { //if the rightmost sensor detects the ine, drastically increase totalValue
      totalValue += 2;  
    }

    // Returns 0 & robot stops when all five sensors hit white -> off the course completely or reached the end
    if (irData.mValue == 0 && irData.r1Value == 0 && irData.l1Value == 0 && irData.l2Value == 0 && irData.r2Value == 0) {
        drive(0);
        turn(0);  
        return 0;
    }
    
	// Define different "correctional" movements depending on our "off track status".
    // if totalValue is 0, then just drive forward. No turn needs to be made.
    if (totalValue == 0) {
        drive(180);
    } else if (totalValue == -1) { //if totalValue is negative 1, make a small left
        drive(50);
        analogWrite(enA, 20);
        analogWrite(enB, 160);
    } else if (totalValue <= -2) { //if totalValue is <= negative 2, make a large left
        digitalWrite(in2, HIGH);
        digitalWrite(in4, HIGH);
        analogWrite(enA, 100);
        analogWrite(enB, 250);
    } else if (totalValue == 1) { //if totalValue is 1, make a small right
        drive(50);
        analogWrite(enB, 20);
        analogWrite(enA, 160);
    } else if (totalValue >= 2) { //if totalValue >= 2, make a large right
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

	// Formula to transform linear distance into encoder counts
    int targetEncoderCount = currEncoderCount + dir * (encoderCountPerRotation * (1000 / (80 * PI)));
    
	if (meters > 0){ // Specify how currEncoerCount should compare to targetEncoderCount depending on direction
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

	// Reset drive and turn (Stop all movements)
   	drive(0);
   	turn(0);
}

void turnAngle(float deg) {
    // Robot measurements
    float wheelDiameter = 0.08;  // 80mm in meters
    float wheelbase = 0.15;      // Distance between wheel centers in meters
    int encoderCountsPerRotation = 1920;
    float turnCircumference = wheelbase * PI;
    
    // Calculate wheel rotation needed for desired angle
    float fractionOfFullRotation = deg / 360.0;
    
    // Calculate required encoder counts
    int targetEncoderCount = abs(encoderCountsPerRotation * fractionOfFullRotation);
    
    // Determine turn direction
    int dir = (deg > 0) ? 1 : -1;
    
    int currEncoderCount = lodom.getCount();
    int initialCount = currEncoderCount;
    
    // Set motor directions for turn
    if (dir > 0) {  // Clockwise turn
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
        digitalWrite(in3, HIGH);
        digitalWrite(in4, LOW);
    } else {
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
        digitalWrite(in3, LOW);
        digitalWrite(in4, HIGH);
    }
	
	// Better imeplemented logic in reaching the targetEncoderCount with use of initialCount
    while (abs(lodom.getCount() - initialCount) < targetEncoderCount) {
        analogWrite(enA, 200);
        analogWrite(enB, 200);
    }

	// Reset motors
    drive(0);
    turn(0);
}

void finishProcedure() { 
	// Stop all movements
  	drive(0);
  	turn(0);

	// Light up finish-LED
  	digitalWrite(led, HIGH);

	// Infinite loop to stop all actions
	while (1) {}
}

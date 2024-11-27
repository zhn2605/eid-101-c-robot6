void setupMotorController() {
    // <<<<<<<<<<<<<<<<<<<<<<<  LEDS  >>>>>>>>>>>>>>>>>>>>>
    pinMode(led, OUTPUT);
  
    // <<<<<<<<<<<<<<<<<<<<<< Sensors >>>>>>>>>>>>>>>>>>>>>
    // IR Sensors
    pinMode(middleIRSensor, INPUT);
    pinMode(leftIRSensor1, INPUT);
    pinMode(rightIRSensor1, INPUT);

    // <<<<<<<<<<<<<<<<< Motor Controller >>>>>>>>>>>>>>>>>
    // Right Motor
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(enA, OUTPUT);
    pinMode(leftEncA, INPUT_PULLUP);
    pinMode(leftEncB, INPUT_PULLUP);

    // Left Sensor
    pinMode(in3, OUTPUT);
    pinMode(in4, OUTPUT);
    pinMode(enB, OUTPUT);
    pinMode(rightEncA, INPUT_PULLUP);
    pinMode(rightEncB, INPUT_PULLUP);
}

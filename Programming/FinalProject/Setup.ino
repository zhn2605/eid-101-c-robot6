void setupComponents() {
    // <<<<<<<<<<<<<<<<<<<<<<<  LEDS  >>>>>>>>>>>>>>>>>>>>>
    pinMode(led, OUTPUT);
  
    // <<<<<<<<<<<<<<<<<<<<<< Sensors >>>>>>>>>>>>>>>>>>>>>
    // IR Sensors
    pinMode(middleIRSensor, INPUT);
    pinMode(leftIRSensor1, INPUT);
    pinMode(rightIRSensor1, INPUT);

    // IMU Sensor
    Wire.begin();
    IMU.begin(); // initialize the MPU6050
    IMU.calibrate();

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

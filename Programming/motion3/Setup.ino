/*
 * Setup.ino
 * Group 6: Zihan Zhao, Bertrand Juan, Marco Chen
 * This file contains functions that set up modes of the GPIO connections in the robot.
 */

 /*
  * Initializes all GPIO pinMode connections in the robot.
  */
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
    
    // IMU
    Wire.begin();  // initialize the I2C hardware
    imu.begin();   // initialize the MPU6050
    imu.calibrate(); // calibrate the IMU (make sure robot doesn't move during this time)

    // Ultrasonic / HC-SR04
    ultrasonic.begin();

    // Lidar 
    initLidar(&lidar); //Use the rcc helper func to initialize the lidar
  
  Serial.begin(9600);
}

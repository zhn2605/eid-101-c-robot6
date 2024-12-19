#include <rcc.h>
#include <Wire.h>
MPU6050 imu;
HC_SR04 ultrasonic;
VL53L0X lidar;

struct SensorData {
    // IR Sensor Data
    int l2Value = 1;
    int l1Value = 1;
    int mValue = 1;
    int r1Value = 1;
    int r2Value = 1;

    // IMU Sensor Data
    float accel_x = 0;
    float accel_y = 0;
    float accel_z = 0;
    float ang_vel_x = 0;
    float ang_vel_y = 0;
    float ang_vel_z = 0;
    float theta = 0;

    // LIDAR Sensor Data
    uint16_t lidar_dist = 0;
    
    // Ultra Sonic Sensor Data
    float ultrasonic_dist = 0;
};

class Sensors {
public:
    float dt = 0; // dt changes dynamically as the code goes on; used for IMU calculations
    float lastTime = 0;
    float currentTime = 0;
    float theta = 0;

    unsigned long duration_us;

    SensorData sensorData;
    // Default no param constructor to store the class object in main code
    Sensors();

    // Set pins for IR Sensors
    void set_IR(int lIR2, int lIR1, int mIR, int rIR1, int rIR2);

    // Updates all Inecessary sensor data
    void updateIR();
    void updateIMU();
    void updateLidar();
    void updateUltrasonic();

    int identifyJunction();
private:
    // IR Sensor Port
    int leftIRSensor1, leftIRSensor2, rightIRSensor1, rightIRSensor2, middleIRSensor;
};

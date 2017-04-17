
#ifndef IMU_H
#define IMU_H

#ifndef CONFIG_H
#include "Config.h"                 // Include configurations.
#endif // CONFIG_H


class IMU {
public:
    IMU();                // Constructor
    void initIMU();       // Initialize I2C bus
    
    void updateIMU();     // Update the IMU output data
    void resetIMU();      // Reset and calibrate the IMU

    float acc[3];         // Accelerometer output (x,y,z) [m/s^2]
    float gyro[3];        // Gyroscope output (x,y,z) [raw]

    float angle[3];       // Gyroscope angle (x,y,z) [raw]
    

//private:
    // Used to handle the I2C bus
    void I2Cread(uint8_t Address, uint8_t Register, uint8_t Nbytes, uint8_t* Data);
    void I2CwriteByte(uint8_t Address, uint8_t Register, uint8_t Data);
    uint8_t Buffer[14];    // Buffer used to save I2C data

    // IMU functions
    void updateAcc();     // Read, convert and save raw data from accelerometer in Acc
    void updateGyro();    // Read, convert and save raw data from gyroscope in Acc
    void updateAngle();   // Update angle with new gyroscope data

    // Gyroscope variables
    int gyro_old[3];      // Previous output
    void normalizeGyro(); // Calculate offset
    float gyro_offset[3];   // Offset (when still all axis should have output 0)
    float b0;             // Filter constant (weight of new measured value)
    float b1;             // Filter constant (weight of old measured value)
    float filter_out;     // Filter output
    float h;
    unsigned long timer;
    unsigned long last_timer;
};


#endif //IMU_H


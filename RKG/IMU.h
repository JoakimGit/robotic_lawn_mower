/*
 * Created by Joakim on 2017-03-21.
 */

#ifndef IMU_IMU_H
#define IMU_IMU_H

#include "stdint.h"   // Enables use of uint8_t
#include "Wire.h"     // Used to connect with the IC2 device.

/*
 * Arduino mega 2560 rev3 addresses used by the IMU.
 */

#define    MPU9250_ADDRESS            0x68
#define    MAG_ADDRESS                0x0C

#define    GYRO_FULL_SCALE_2000_DPS   0x18

#define    ACC_FULL_SCALE_16_G        0x18
#define    ACC_SENSITIVITY            2048

#define    GRAVITY                    9.82      // Gravity in Sweden
#define    PERIOD                     0.04     // Period in seconds, 0.002 prev, 0.04 for whole program


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
    int gyro_offset[3];   // Offset (when still all axis should have output 0)
    float b0;             // Filter constant (weight of new measured value)
    float b1;             // Filter constant (weight of old measured value)
    float filter_out;     // Filter output
};


#endif //IMU_IMU_H


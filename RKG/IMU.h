/*
 * Created by Joakim on 2017-03-21.
 */

#ifndef IMU_IMU_H
#define IMU_IMU_H

/*
 * Arduino mega 2560 rev3 addresses used by the IMU.
 */

#define    MPU9250_ADDRESS            0x68
#define    MAG_ADDRESS                0x0C

#define    GYRO_FULL_SCALE_2000_DPS   0x18

#define    ACC_FULL_SCALE_16_G        0x18
#define    ACC_SENSITIVITY            2048
#define    GRAVITY                    9.82


class IMU {
public:
    IMU();              // Constructor
    void updateIMU();   // Update the IMU output data
    

private:
    // Used to handle the I2C
    void I2Cread(uint8_t Address, uint8_t Register, uint8_t Nbytes, uint8_t* Data);
    void I2CwriteByte(uint8_t Address, uint8_t Register, uint8_t Data);
    uint8_t Buffer[14];    // Buffer used to save I2C data

    // IMU functions
    float Acc[3];       // Accelerometer data in x,y,z [m/s^2]
    float Gyro[3];      // Gyroscope data in x,y,z
    void updateAcc();   // Read, convert and save raw data from accelerometer in Acc[3].
    void updateGyro();  // Read, convert and save raw data from gyroscope in Acc[3].
};


#endif //IMU_IMU_H


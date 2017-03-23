//
// Created by Joakim on 2017-03-21.
//

#include "stdint.h"   // Enables use of uint8_t
#include "Wire.h"     // Used to connect with the IC2 device.
#include "IMU.h"


using namespace std;

// Constructor
IMU::IMU()
{
}


/*
 ***** Public methods *****
 */

 // Initialize the I2C bus.
void IMU::initIMU()
{
  Wire.begin();

  // * Configure gyroscope range *
  I2CwriteByte(MPU9250_ADDRESS,27,GYRO_FULL_SCALE_2000_DPS);
  // * Configure accelerometers range *
  I2CwriteByte(MPU9250_ADDRESS,28,ACC_FULL_SCALE_16_G);

  // Set start values to 0.
  IMU::velocity[0] = 0;
  IMU::velocity[1] = 0;
  IMU::velocity[2] = 0;
}


// Update the IMU output data
void IMU::updateIMU()
{
  I2Cread(MPU9250_ADDRESS,0x3B,14,IMU::Buffer); // Read raw data from the IMU
  updateAcc();                                  // Convert & update accelerometer data
  updateGyro();                                 // Update gyroscope data
  updateVel();                                  // Update velocity
}


/*
 ***** Private methods *****
 */

// This function read Nbytes bytes from I2C device at address Address. 
// Put read bytes starting at register Register in the Data array. 
void IMU::I2Cread(uint8_t Address, uint8_t Register, uint8_t Nbytes, uint8_t* Data)
{
  // Set register address
  Wire.beginTransmission(Address);
  Wire.write(Register);
  Wire.endTransmission();
  if(Register == 0x02){
   //Serial.println("Data Not Ready");
 }
  // Read Nbytes
  Wire.requestFrom(Address, Nbytes); 
  uint8_t index=0;
  while (Wire.available())
    Data[index++]=Wire.read();
  //Serial.println("Data: " + *Data); 
}

// Write a byte (Data) in device (Address) at register (Register)
void IMU::I2CwriteByte(uint8_t Address, uint8_t Register, uint8_t Data)
{
  // Set register address
  Wire.beginTransmission(Address);
  Wire.write(Register);
  Wire.write(Data);
  Wire.endTransmission();
}

// Read and convert data from the accelerometer ( m/s^2 )
void IMU::updateAcc()
{
  // Read data from buffer
  int16_t ax=-(IMU::Buffer[0]<<8 | IMU::Buffer[1]);
  int16_t ay=-(IMU::Buffer[2]<<8 | IMU::Buffer[3]);
  int16_t az=IMU::Buffer[4]<<8 | IMU::Buffer[5];

  // Convert 16 bits values to m/s^2
  // Save data in acc{x,y,z}
  float a[3];
  a[0] = ax; a[1] = ay; a[2] = az;
  IMU::acc[0] = a[0]/ACC_SENSITIVITY*GRAVITY;
  IMU::acc[1] = a[1]/ACC_SENSITIVITY*GRAVITY;
  IMU::acc[2] = a[2]/ACC_SENSITIVITY*GRAVITY;
  return;
}

// Reset velocity to zero
void IMU::resetIMU()
{
  // Reset velocity
  IMU::velocity[0] = 0;
  IMU::velocity[1] = 0;
  IMU::velocity[2] = 0;
}

// Read and convert data from the gyroscope
void IMU::updateGyro()
{
  // Read data from buffer
  int16_t gx=-(IMU::Buffer[8]<<8 | IMU::Buffer[9]);
  int16_t gy=-(IMU::Buffer[10]<<8 | IMU::Buffer[11]);
  int16_t gz=IMU::Buffer[12]<<8 | IMU::Buffer[13];

  // Save data in gyro{x,y,z}
  IMU::gyro[0] = gx;
  IMU::gyro[1] = gy;
  IMU::gyro[2] = gz;
  return;
}

// Update velocity data with most recent accelerometer output
void IMU::updateVel()
{
  IMU::velocity[0] = velocity[0] + IMU::acc[0] * PERIOD;
  IMU::velocity[1] = velocity[0] + IMU::acc[1] * PERIOD;
  IMU::velocity[2] = velocity[0] + IMU::acc[2] * PERIOD;
  return;
}


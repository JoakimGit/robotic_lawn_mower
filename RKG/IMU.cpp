//
// Created by Joakim on 2017-03-21.
//

#include "IMU.h"


/*
 ***** Constructor *****
 */
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
  acc[0] = 0; acc[1] = 0; acc[2] = 0;
  angle[0] = 0; angle[1] = 0; angle[2] = 0;
  gyro_old[0] = 0; gyro_old[1] = 0; gyro_old[2] = 0;

  // Gyroscope
  normalizeGyro();  // gy = 20.78  // Calculate offset
  gyro_offset[1] = 20.78;
  b0 = 0.0214;      // Filter constant (weight of new measured value) - Measured in Matlab
  b1 = 0.0214;      // Filter constant (weight of old measured value) - Measured in Matlab
  filter_out = 0;   // Filter output
}

// Update the IMU output data
void IMU::updateIMU()
{
  I2Cread(MPU9250_ADDRESS,0x3B,14,IMU::Buffer); // Read raw data from the IMU
  updateAcc();                                  // Convert & update accelerometer data
  updateGyro();                                 // Update gyroscope data
  updateAngle();
}

// Reset and calibrate the IMU.
void IMU::resetIMU()
{
  acc[0] = 0; acc[1] = 0; acc[2] = 0;                     // Reset current accelerometer data
  gyro[0] = 0; gyro[1] = 0; gyro[2] = 0;                  // Reset current gyroscope data
  gyro_old[0] = 0; gyro_old[1] = 0; gyro_old[2] = 0;      // Reset old gyroscope data
  angle[0] = 0; angle[1] = 0; angle[2] = 0;               // Reset gyroscope angle
  normalizeGyro();                                        // Calculate the new gyroscope offset
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
  int16_t ax=-(Buffer[0]<<8 | Buffer[1]);
  int16_t ay=-(Buffer[2]<<8 | Buffer[3]);
  int16_t az=Buffer[4]<<8 | Buffer[5];

  // Convert raw data to m/s^2
  // Save data in acc{x,y,z}
  float a[3];
  a[0] = ax; a[1] = ay; a[2] = az;
  acc[0] = a[0]/ACC_SENSITIVITY*GRAVITY;
  acc[1] = a[1]/ACC_SENSITIVITY*GRAVITY;
  acc[2] = a[2]/ACC_SENSITIVITY*GRAVITY;
  return;
}



// Read and convert data from the gyroscope
void IMU::updateGyro()
{
  // Read data from buffer
  int16_t gx=-(Buffer[8]<<8 | Buffer[9]);
  int16_t gy=-(Buffer[10]<<8 | Buffer[11]);
  int16_t gz=Buffer[12]<<8 | Buffer[13];

  // Save data in gyro{x,y,z} with 
  gx = gx + gyro_offset[0];
  gy = gy + gyro_offset[1];
  gz = gz + gyro_offset[2];
  
  filter_out = b0*gy + b1*gyro_old[1];
  gyro_old[1] = gy;
  gyro[1] = filter_out;
}


// Update gyroscope angle
void IMU::updateAngle()
{
  angle[1] = angle[1]+gyro[1]*PERIOD;
}


// Calculate gyroscope offset (offset of 1000 samples)
void IMU::normalizeGyro()
{
  int cnt = 0;
  int g_sum[3] = {0,0,0};

  while (cnt < 1000) {
    // Read data from buffer
    I2Cread(MPU9250_ADDRESS,0x3B,14,IMU::Buffer); // Read raw data from the IMU
    int16_t gx=-(Buffer[8]<<8 | Buffer[9]);
    int16_t gy=-(Buffer[10]<<8 | Buffer[11]);
    int16_t gz=Buffer[12]<<8 | Buffer[13];
    // Save the sum of total data
    g_sum[0] += gx;
    g_sum[1] += gy;
    g_sum[2] += gz;
    cnt++;
  }

  gyro_offset[0] = g_sum[0]/cnt;
  gyro_offset[1] = g_sum[0]/cnt;
  gyro_offset[2] = g_sum[0]/cnt;
  
}













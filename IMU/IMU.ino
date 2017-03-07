#include <Wire.h>

#define    MPU9250_ADDRESS            0x68
#define    MAG_ADDRESS                0x0C

#define    GYRO_FULL_SCALE_250_DPS    0x00
#define    GYRO_FULL_SCALE_500_DPS    0x08
#define    GYRO_FULL_SCALE_1000_DPS   0x10
#define    GYRO_FULL_SCALE_2000_DPS   0x18

#define    ACC_FULL_SCALE_2_G        0x00  
#define    ACC_FULL_SCALE_4_G        0x08
#define    ACC_FULL_SCALE_8_G        0x10
#define    ACC_FULL_SCALE_16_G       0x18 // More info at 4.7 in RM-MPU-9225.pdf



// This function read Nbytes bytes from I2C device at address Address. 
// Put read bytes starting at register Register in the Data array. 
void I2Cread(uint8_t Address, uint8_t Register, uint8_t Nbytes, uint8_t* Data)
{
  // Set register address
  Wire.beginTransmission(Address);
  Wire.write(Register);
  Wire.endTransmission();
 if(Register == 0x02){
   Serial.println("Data Not Ready");
 }
  // Read Nbytes
  Wire.requestFrom(Address, Nbytes); 
  uint8_t index=0;
  while (Wire.available())
    Data[index++]=Wire.read();
  Serial.println("Data: " + *Data); 
}


// Write a byte (Data) in device (Address) at register (Register)
void I2CwriteByte(uint8_t Address, uint8_t Register, uint8_t Data)
{
  // Set register address
  Wire.beginTransmission(Address);
  Wire.write(Register);
  Wire.write(Data);
  Wire.endTransmission();
}

// === Acceleration ===
float accX = 0;
float accY = 0;
float accZ = 0;

// Return acceleration
float getAccX() {
  return accX;
}
float getAccY() {
  return accY;
}
float getAccZ() {
  return accZ;
}

// === Velocity ===
float velX = 0;
float velY = 0;
float velZ = 0;

// Return velocity
float getVelX() {
  return velX;
}
float getVelY() {
  return velY;
}
float getVelZ() {
  return velZ;
}

// Update velocity
void setVelX(float v) {
  velX = v;
}
void setVelY(float v) {
  velY = v;
}
void setVelZ(float v) {
  velZ = v;
}


// Initializations
void setup()
{
  // Arduino initializations
  Wire.begin();
  Serial.begin(115200);

  // Configure accelerometers range
    I2CwriteByte(MPU9250_ADDRESS,28,ACC_FULL_SCALE_16_G);
}


long int cpt=0;
// Main loop, read and display data
void loop()
{
  // _______________
  // ::: Counter :::

  // Display data counter
  Serial.println(cpt++,DEC);
  Serial.print ("\t");



  // ____________________________________
  // :::  Accelerometer  ::: 

  // Read accelerometer and gyroscope
  uint8_t Buf[14];
  I2Cread(MPU9250_ADDRESS,0x3B,14,Buf);


  // Create 16 bits values from 8 bits data
  // Accelerometer
  int16_t ax=-(Buf[0]<<8 | Buf[1]);
  int16_t ay=-(Buf[2]<<8 | Buf[3]);
  int16_t az=Buf[4]<<8 | Buf[5];


  // Convert 16 bits values to m/s^2
  
  float axf= ax;
  float ayf = ay;
  float azf = az;
  // Sensitiivy scale factor: 2048, g: 9.82 m/s^2
  accX = axf/2048*9.82;
  accY = ayf/2048*9.82;
  accZ = azf/2048*9.82;

  // ____________________________________
  // ::: Velocity :::

  // Calculate and update velocity
  float tempVelX = velX;
  float tempVelY = velY;
  float tempVelZ = velZ;

  velX = tempVelX + (accX*0.1);
  velY = tempVelY + (accY*0.1);
  velZ = tempVelZ + (accZ*0.1);

  // Display values

  // Accelerometer
  Serial.print (getAccX(),DEC); 
  Serial.print ("\t");
  Serial.print (getAccY(),DEC);
  Serial.print ("\t");
  Serial.print (getAccZ(),DEC);
  Serial.print ("\n");

  // Velocity
  Serial.print (getVelX(),DEC);
  Serial.print ("\t");
  Serial.print (getVelY(),DEC);
  Serial.print ("\t");
  Serial.print (getVelZ(),DEC);

  // End of line
  Serial.println("");
  delay(100);    
}


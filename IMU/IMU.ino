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
float acc[3] = {0,0,0};
float newAcc[3] = {0,0,0};

// Return acceleration
float getAccX() {
  return acc[0];
}
float getAccY() {
  return acc[1];
}
float getAccZ() {
  return acc[2];
}

// === Velocity ===
float vel[3] = {0,0,0};

// Return velocity
float getVelX() {
  return vel[0];
}
float getVelY() {
  return vel[1];
}
float getVelZ() {
  return vel[2];
}

// Update velocity
void setVelX(float v) {
  vel[0] = v;
}
void setVelY(float v) {
  vel[1] = v;
}
void setVelZ(float v) {
  vel[2] = v;
}

float prev[3];
float prevHF[3];
boolean doHPF = false;

// ind - index of three dimensions (x, y, z)
void makeHPFf() {
    for (int ind = 0; ind < 3; ind++) {
        newAcc[ind] = acc[ind] * 0.002 * 9.8;
        if (doHPF)
            acc[ind] = newAcc[ind] - prev[ind] + (prevHF[ind] * 0.8);
        prev[ind] = newAcc[ind];
        prevHF[ind] = acc[ind];
    }

    if (!doHPF)
        doHPF = true;
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
  float af[3] = {ax, ay, az};
  
  // Sensitiivy scale factor: 2048, g: 9.82 m/s^2
  acc[0] = af[0]/2048*9.82;
  acc[1] = af[1]/2048*9.82;
  acc[2] = af[2]/2048*9.82;

  // Run highpass filter
  makeHPFf();

  // ____________________________________
  // ::: Velocity :::

  // Calculate and update velocity
  float tempVel[3] = {vel[0], vel[1], vel[2]};

  vel[0] = tempVel[0] + (acc[0]*0.01);
  vel[1] = tempVel[1] + (acc[1]*0.01);
  vel[2] = tempVel[2] + (acc[2]*0.01);

  // Display values

  // Accelerometer
  Serial.print ("AccX: ");
  Serial.print (getAccX(),DEC); 
  Serial.print ("\t");
  Serial.print ("AccY: ");
  Serial.print (getAccY(),DEC);
  Serial.print ("\t");
  Serial.print ("AccZ: ");
  Serial.print (getAccZ(),DEC);
  Serial.print ("\n");

  // Velocity
  Serial.print ("VelX: ");
  Serial.print (getVelX(),DEC);
  Serial.print ("\t");
  Serial.print ("VelY: ");
  Serial.print (getVelY(),DEC);
  Serial.print ("\t");
  Serial.print ("VelZ: ");
  Serial.print (getVelZ(),DEC);
  Serial.print ("VelZ: ");

  // End of line
  Serial.println("");
  // delay(10);
}


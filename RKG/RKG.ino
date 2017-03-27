// :::  Includes :::
#include "IMU.h"
#include "Motors.h"
//#include "Cutting.h"
//#include "IR.h"
//#include "USS.h"
//#include"Bumper.h"

// ::: Variabler :::
//IMU imu;                    // Class used for IMU functions
Motors rightMotor(8);         // Pin 8 is connected to the right motor
Motors leftMotor(9);          // Pin 9 is connected to the left motor

// :::  Funktioner :::

// TO-DO: Driving motor functions
//void initMotors();        // Initialize the driving motors
//void stopMotors();        // Turn off the driving motors
//void goForward();         // Go foward
//void goBackward();        // Go backwards
//void turnLeft();          // Turn left
//void turnRight();         // Turn right
//void turnAway();          // Turn away from an obstacle in a random direction

// TO-DO: Cutting motor functions
//void initCutting();       // Initialize the cutting motor
//void startCutting();      // Star the cutting motor
//void stopCutting();       // Turn off the cutting motor

// STARTED: Sensor functions
//TO-DO void initIR();            // Initialize infrared sensor
//TO-DO boolean readIR(int);      // Returns true if the cutting unit is too far from the ground (how far is specified with input)
//TO-DO void initUSS();           // Initialize ultrasonic sensor
//TO-DO boolean readUSS(int);     // Returns true if an object is in front off the robot (how far is specified by input)
//TO-DO void initBumper();        // Initialize bumper sensor
//TO-DO boolean readBumper();     // Returns true if the bumper sensor is triggered
//int initIMU();                  // 
//int updateIMU();                // Update data from IMU. Data is saved in imu::acc[3] & imu::gyro[3]

boolean isSet;

// Initializations
  void setup()
{
    Serial.begin(115200);
    //imu.initIMU();
    isSet = false;
    rightMotor.initMotors();
    leftMotor.initMotors();
}


// Main loop, read and display data
void loop()
{   
    if(!isSet) {
        rightMotor.updateMotors();
        leftMotor.updateMotors();
        rightMotor.changeSpeed(150);
        leftMotor.changeSpeed(150);
        isSet = true;
    } else {
        rightMotor.updateMotors();
        leftMotor.updateMotors();
        rightMotor.changeSpeed(90);
        leftMotor.changeSpeed(90);
        isSet = false;
    }
    
    delay(5000);

    //if (isSet) {
    //    isSet = false;
    //    leftMotor.setSpeed(90); 
    //}

    
    // Update IMU data and save in x/y/z [m/s^2]

    /* // Example code for the IMU
     * imu.updateIMU();
     * float ax = imu.acc[0];
     * float vx = imu.velocity[0];
     */
}





















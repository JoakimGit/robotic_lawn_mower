// :::  Includes :::
#include "IMU.h"
#include "Motor.h"
//#include "Cutting.h"
//#include "IR.h"
//#include "USS.h"
//#include"Bumper.h"

// ::: Variabler :::
//IMU imu;                    // Class used for IMU functions
Motor rightMotor(8);         // Pin 8 is connected to the right motor
Motor leftMotor(9);          // Pin 9 is connected to the left motor

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
    //imu.initIMU();              // Initiate the IMU
    rightMotor.initMotor();     // Initiate the right motor
    leftMotor.initMotor();      // Initiate the left motor
}


// Main loop, read and display data
void loop()
{ 
    rightMotor.changeSpeed(90);
    leftMotor.changeSpeed(90);
    //Serial.print(rightMotor.readSpeed());
    delay(5000);
    rightMotor.changeSpeed(130);
    leftMotor.changeSpeed(130);
    delay(5000);
    /* Example code for the motors.
     * rightMotor.updateMotor();
     * rightMotor.changeSpeed(150);
     */

    /* // Example code for the IMU
     * imu.updateIMU();
     * float ax = imu.acc[0];
     * float vx = imu.velocity[0];
     */
}





















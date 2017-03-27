// :::  Includes :::
#include "IMU.h"
#include "Motors.h"
//#include "Cutting.h"
//#include "IR.h"
//#include "USS.h"
//#include"Bumper.h"

// ::: Variabler :::
//IMU imu;                    // Class used for IMU functions
Motors leftMotor(9);           // The motors are connected to pin 8 & 9.
//Motors rightMotor(9);

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
    leftMotor.initMotors();
    isSet = false;
}


// Main loop, read and display data
void loop()
{
    if(!isSet) {
        leftMotor.updateMotors();
        leftMotor.changeSpeed(150);
        isSet = true;
    } else {
        leftMotor.updateMotors();
        leftMotor.changeSpeed(0);
        isSet = false;
    }
    
    delay(5000);

    //if (isSet) {
    //    isSet = false;
    //    leftMotor.setSpeed(90); 
    //}

    
    // Working code for IMU:
    // Update IMU data and save in x/y/z [m/s^2]
    /*
    imu.updateIMU();
    float ax = imu.acc[0];
    float ay = imu.acc[1];
    float az = imu.acc[2];

    float vx = imu.velocity[0];
    float vy = imu.velocity[1];
    float vz = imu.velocity[2];
    
    Serial.print("Acc [X/Y/Z]: ");
    Serial.print(ax); Serial.print("\t");
    Serial.print(ay); Serial.print("\t");
    Serial.print(az); Serial.print("\n");

    Serial.print("Vel {X/Y/Z]: ");
    Serial.print(vx); Serial.print("\t");
    Serial.print(vy); Serial.print("\t");
    Serial.print(vz); Serial.print("\n");

    Serial.print("\n");
    */
}





















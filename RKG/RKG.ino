// :::  Includes :::
#include "IMU.h"

// ::: Variabler :::

// :::  Funktioner :::
void initMotors();        // Initialize the driving motors
void stopMotors();        // Turn off the driving motors
void goForward();         // Go foward
void goBackward();        // Go backwards
void turnLeft();          // Turn left
void turnRight();         // Turn right
void turnAway();          // Turn away from an obstacle in a random direction
void initCutting();       // Initialize the cutting motor
void startCutting();      // Star the cutting motor
void stopCutting();       // Turn off the cutting motor

void initIR();            // Initialize infrared sensor
void initUSS();           // Initialize ultrasonic sensor
void initBumper();        // Initialize bumper sensor

boolean readIR(int);      // Returns true if the cutting unit is too far from the ground (how far is specified with input)
boolean readUSS(int);     // Returns true if an object is in front off the robot (how far is specified by input)
boolean readBumper();     // Returns true if the bumper sensor is triggered
int resetIMU();           // Reset the IMU and set the destination to straight ahead
int readIMU();            // Returns (-1, 0, 1) if the robot goes (left / straight / right) of the destination.

// Initializations
void setup()
{
    IMU imu;                // Initialize the IMU (Inertial Measurement Unit)
    
}


// Main loop, read and display data
void loop()
{

 
}


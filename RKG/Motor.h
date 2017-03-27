/*
 * Created by Joakim on 2017-03-25.
 */

#ifndef MOTOR_H
#define MOTOR_H

/*
 * Defines
 */
 
#include <SPI.h>
#include <Servo.h>
#include "datatypes.h"

class Motor {
public:
    Motor(int);                   // Constructor
    void initMotor();       // Attach the servo to the correct pin and set the pulse range
    void updateMotor();     // Read values from the motors
    void changeSpeed(int);      // Set new speed. Input 0-89 is backwards, 90 is still, 91-180 is foward
    int readSpeed();         // Read speed.
    int currentThrottle;

    
//private:
    // Functions
    void changeThrottle(int);
    int readThrottle();
    int normalizeThrottle(int);

    // Variables
    float current;           //measured battery current
    float motor_current;     //measured motor current
    float voltage;           //measured battery voltage
    float c_speed;           //measured rpm * Pi * wheel diameter [km] * 60 [minutes]
    float c_dist;            //measured odometry tachometer [turns] * Pi * wheel diameter [km] 
    double power;            //calculated power
    int escPin;
    int minPulseRate;
    int maxPulseRate;
    int throttleChangeDelay;
    int Count_error;
    Servo esc;
    mc_values VescMeasuredValues;
};


#endif //MOTORS_H

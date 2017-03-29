/*
 * Created by Joakim on 2017-03-25.
 */

#ifndef MOTOR_H
#define MOTOR_H

/*
 * Defines
 */

#include "vesc_uart.h"
#include <SPI.h>
#include <Servo.h>
#include "datatypes.h"

class Motor {
public:
    Motor(int);             // Constructor, specify which pin the motor is connected to
    void initMotor();       // Attach the servo to the pin and set the pulse range
    void updateMotor();     // Read values from the motor
    void changeSpeed(int);  // Set speed (0-180). Less than 90 is backward, 90 is still, more than 90 is foward
    int readSpeed();        // Read speed.
    int currentThrottle;    // current throttle

private:
    // Functions
    void changeThrottle(int);
    int readThrottle();
    int normalizeThrottle(int);

    // Variables
    int escPin;                     //pin that motor is connected to
    int minPulseRate;
    int maxPulseRate;
    Servo esc;
    // Output data from the hall sensor
    mc_values VescMeasuredValues;   // Contains output from hall sensor
    float voltage;                  //measured battery voltage
    float current;                  //measured battery current
    float motor_current;            //measured motor current
    float c_speed;                  //measured rpm * Pi * wheel diameter [km] * 60 [minutes]
    float c_dist;                   //measured odometry tachometer [turns] * Pi * wheel diameter [km] 
    double power;                   //calculated power
    int Count_error;
};


#endif //MOTORS_H

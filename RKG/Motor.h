
#ifndef MOTOR_H
#define MOTOR_H

#ifndef CONFIG_H
#include "Config.h"                 // Include configurations.
#endif // CONFIG_H

class Motor {
public:
    Motor(int, HardwareSerial*);   // Constructor, specify which pin the motor is connected to
    void initMotor();              // Attach the servo to the pin and set the pulse range
    void updateMotor();            // Read values from the motor
    void setRPM(int);              // Set RPM of motor (From -65 to 65);
    void stopMotor();              // Change speed to still.
    int readSpeed();               // Read speed.
    int currentThrottle;           // current throttle

private:
    // Functions
    void changeThrottle(int);
    int readThrottle();
    int normalizeThrottle(int);

    // Variables
    int escPin;                     //pin that motor is connected to
    HardwareSerial *serialIO;       //serial port for motor output
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

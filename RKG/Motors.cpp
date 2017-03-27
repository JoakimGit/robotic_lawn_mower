//
// Created by Joakim on 2017-03-25.
//

//#include <Servo.h>
//#include "datatypes.h"
#include "vesc_uart.h"
//#include <SPI.h>
#include "Motors.h"


// Constructor
// Input defines which pin the vesc is connected to.
Motors::Motors(int pin)
{
    float current = 0.0;           //measured battery current
    float motor_current = 0.0;     //measured motor current
    float voltage = 0.0;           //measured battery voltage
    float c_speed = 0.0;           //measured rpm * Pi * wheel diameter [km] * 60 [minutes]
    float c_dist = 0.00;           //measured odometry tachometer [turns] * Pi * wheel diameter [km] 
    double power = 0.0;            //calculated power
    int escPin = pin;              //set the pin that is connected to the vesc
    int minPulseRate = 1000;
    int maxPulseRate = 2000;
    int throttleChangeDelay = 0;
    int Count_error;
    Servo esc;
    mc_values VescMeasuredValues;
}


/*
 ***** Public methods *****
 */

// Update the motor output data
void Motors::initMotors()
{
    // Attach the servo to the correct pin and set the pulse range
    Motors::esc.attach(escPin, minPulseRate, maxPulseRate);
    Motors::changeSpeed(90);
}

// Read values from the motors
void Motors::updateMotors()
{
    if (vesc_get_values(VescMeasuredValues)) {
        // Read values from the motors
        Motors::voltage = VescMeasuredValues.v_in;
        Motors::current = VescMeasuredValues.current_in;
        Motors::motor_current = VescMeasuredValues.current_motor;
        Motors::power = current*voltage;
        Motors::c_speed = (VescMeasuredValues.rpm/57.75);
        //c_dist = (VescMeasuredValues.tachometer/57.75)*3.14159265359*0.000083;
        Motors::Count_error = 0;
    }
}

void Motors::changeSpeed(int nspeed)
{
    Motors::changeThrottle(nspeed);
}

int Motors::readSpeed()
{
    return Motors::c_speed;
}

/*
 ***** Private methods *****
 */

void Motors::changeThrottle(int throttle)
{
    int newThrottle = normalizeThrottle(throttle);
    Motors::esc.write(newThrottle);
}

int Motors::readThrottle()
{
    return Motors::esc.read();
}

// Ensure that throttle value is between 0 - 180
int Motors::normalizeThrottle(int value)
{
    if (value < 0)
      return 0;
    if (value > 180)
      return 180;
    return value;
}









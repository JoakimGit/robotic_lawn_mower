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
    currentThrottle = 0;
    current = 0.0;           //measured battery current
    motor_current = 0.0;     //measured motor current
    voltage = 0.0;           //measured battery voltage
    c_speed = 0.0;           //measured rpm * Pi * wheel diameter [km] * 60 [minutes]
    c_dist = 0.00;           //measured odometry tachometer [turns] * Pi * wheel diameter [km] 
    power = 0.0;            //calculated power
    escPin = pin;              //set the pin that is connected to the vesc
    minPulseRate = 1000;
    maxPulseRate = 2000;
    throttleChangeDelay = 0;
    Count_error;
    esc;
    VescMeasuredValues;
}


/*
 ***** Public methods *****
 */

// Update the motor output data
void Motors::initMotors()
{   
    // Attach the servo to the correct pin and set the pulse range
    esc.attach(escPin, minPulseRate, maxPulseRate);
    // Set speed to still.
    changeSpeed(90);
    delay(1000);
}

// Read values from the motors
void Motors::updateMotors()
{
    if (vesc_get_values(VescMeasuredValues)) {
        // Read values from the motors
        voltage = VescMeasuredValues.v_in;
        current = VescMeasuredValues.current_in;
        motor_current = VescMeasuredValues.current_motor;
        power = current*voltage;
        c_speed = (VescMeasuredValues.rpm/57.75);
        //c_dist = (VescMeasuredValues.tachometer/57.75)*3.14159265359*0.000083;
        Count_error = 0;
    }
}

void Motors::changeSpeed(int nspeed)
{
    changeThrottle(nspeed);
}

int Motors::readSpeed()
{
    return c_speed;
}

/*
 ***** Private methods *****
 */

void Motors::changeThrottle(int throttle)
{
    int newThrottle = normalizeThrottle(throttle);
    currentThrottle = newThrottle;
    esc.write(newThrottle);
}

int Motors::readThrottle()
{
    return esc.read();
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









//
// Created by Joakim on 2017-03-25.
//

#include <Servo.h>
//#include "datatypes.h"
//#include "vers_uart.h"
#include <SPI.h>
#include "Motors.h"


// Constructor
Motors::Motors()
{
    float current = 0.0;           //measured battery current
    float motor_current = 0.0;     //measured motor current
    float voltage = 0.0;           //measured battery voltage
    float c_speed = 0.0;           //measured rpm * Pi * wheel diameter [km] * 60 [minutes]
    float c_dist = 0.00;           //measured odometry tachometer [turns] * Pi * wheel diameter [km] 
    double power = 0.0;              //calculated power
    int escPin = 9;
    int minPulseRate = 1000;
    int maxPulseRate = 2000;
    int throttleChangeDelay = 0;
    int Count_error;
}


/*
 ***** Public methods *****
 */

// Update the motor output data
void Motors::initMotors()
{
    // Attach the servo to the correct pin and set the pulse range
    Motors::esc.attach(escPin, minPulseRate, maxPulseRate);
}

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

    /*
     * if (Serial.available() > 0) {                            // Wait for input
     *    int throttle = normalizeThrottle(Serial.parseInt())   // Read new throttle values
     *    
     *    changeThrottle(throttle);                             // Change throttle to new value
     * }
     */
}


/*
 ***** Private methods *****
 */

void changeThrottle(int throttle)
{
    // readThrottle(throttle);
    Motors::esc.write(throttle);
}

int readThrottle(int throttle)
{
    
    return Motors::esc.read();
}

// Ensure that throttle value is between 0 - 180
int normalizeThrottle(int value)
{
    if (value < 0)
      return 0;
    if (value > 180)
      return 180;
    return value;
}









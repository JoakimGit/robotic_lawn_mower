//
// Created by Joakim on 2017-03-25.
//

#include "Motor.h"


// Constructor
// Input defines which pin the vesc is connected to.
Motor::Motor(int pin, HardwareSerial *serialPin)
{
    currentThrottle = 0;     // Throttle from 0-180
    escPin = pin;            //set the pin that is connected to the vesc
    serialIO = serialPin;
    minPulseRate = 1000;
    maxPulseRate = 2000;
    esc;                     // Servo
    
    // Output data from the hall sensor
    VescMeasuredValues;      // Contains output from sensor
    voltage = 0.0;           //measured battery voltage
    current = 0.0;           //measured battery current
    motor_current = 0.0;     //measured motor current
    power = 0.0;             //calculated power
    c_speed = 0.0;           //measured rpm * Pi * wheel diameter [km] * 60 [minutes]
    // c_dist = 0.00;           //measured odometry tachometer [turns] * Pi * wheel diameter [km]
    Count_error = 0;         // Used for debugging
}


/*
 ***** Public methods *****
 */

// Update the motor output data
void Motor::initMotor()
{   
    // Attach the servo to the correct pin and set the pulse range
    esc.attach(escPin, minPulseRate, maxPulseRate);
    // Set speed to still.
    changeSpeed(90);
    delay(1000);
}

// Read values from the motors
void Motor::updateMotor()
{
    if (vesc_get_values(VescMeasuredValues, serialIO)) {
        // Read values from the motors
        voltage = VescMeasuredValues.v_in;
        current = VescMeasuredValues.current_in;
        motor_current = VescMeasuredValues.current_motor;
        power = current*voltage;
        c_speed = (VescMeasuredValues.rpm/57.75);         // 57.5 measured value for gear box and electric poles
        //c_dist = c_speed*3.14159265359*0.000083;
        Count_error = 0;

        if (voltage < 17) {         // Stop motor if battery voltage is too low
          stopMotor();
        }
    }
}

void Motor::changeSpeed(int nspeed)
{
    
    changeThrottle(nspeed);
}

void Motor::stopMotor()
{
  changeSpeed(90);
}

int Motor::readSpeed()
{
    return c_speed;
}

/*
 ***** Private methods *****
 */

void Motor::changeThrottle(int throttle)
{
    int newThrottle = normalizeThrottle(throttle);
    currentThrottle = newThrottle;
    esc.write(newThrottle);
}

int Motor::readThrottle()
{
    return esc.read();
}

// Ensure that throttle value is between 0 - 180
int Motor::normalizeThrottle(int value)
{
    if (value < 0)
      return 0;
    if (value > 180)
      return 180;
    return value;
}









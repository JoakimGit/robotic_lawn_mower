
#include "Motor.h"


// Constructor
// Input defines which pin the vesc is connected to.
Motor::Motor(int pin, HardwareSerial *serialPin)
{
    currentThrottle = 0;     // Throttle from 0-180
    escPin = pin;            // Set the pin that is connected to the vesc
    serialIO = serialPin;
    minPulseRate = 1000;
    maxPulseRate = 2000;
    esc;                     // Servo
    
    // Output data from the hall sensor
    VescMeasuredValues;      // Contains output from sensor
    voltage = 0.0;           // Measured battery voltage
    current = 0.0;           // Measured battery current
    motor_current = 0.0;     // Measured motor current
    power = 0.0;             // Calculated power
    c_speed = 0.0;           // Measured rpm * Pi * wheel diameter [km] * 60 [minutes]
    // c_dist = 0.00;        // Measured odometry tachometer [turns] * Pi * wheel diameter [km]
    Count_error = 0;         // Used for debugging
}


/*
 ***** Public methods *****
 */

// Update the motor output data
void Motor::initMotor()
{   
    esc.attach(escPin, minPulseRate, maxPulseRate);   // Attach the servo to the correct pin and set the pulse range
    setRPM(0);                                        // Set speed to still.
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
        c_speed = (VescMeasuredValues.rpm/HALL2RPM);
        Count_error = 0;

        if (voltage < MIN_VOLTAGE) {         // Stop motor if battery voltage is too low
          stopMotor();
        }
    }
}

//Set RPM of motor (From -65 to 65);
void Motor::setRPM(int RPM)
{
    int new_speed;
    if ( RPM < 0 ) {
      new_speed = 90-abs(RPM)*90/MAX_RPM;
    }
    else if ( RPM > 0 ) {
      new_speed = 90+RPM*90/MAX_RPM;
    }
    else {
      new_speed = 90;   // Set RPM to zero.
    }
    changeThrottle(new_speed);
}

void Motor::stopMotor()
{
  setRPM(0);
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









/////////////////////
// :::  Includes :::
/////////////////////

#include "IMU.h"
#include "Motor.h"
//#include "Cutting.h"
//#include "IR.h"
#include "USS.h"
//#include"Bumper.h"
#include <TimerOne.h>   // Used for interrupts


/////////////////////
// ::: Parameters :::
/////////////////////

#define MOTORRIGHT  8                  // Pin 8 is connected to the right motor
#define MOTORLEFT   9                  // Pin 9 is connected to the left motor

#define SERIALRIGHT Serial3            // Serial ports connected to the hall sensor
#define SERIALLEFT Serial2

#define TIMER_US    50     // Timer is set to 50 uS
#define TICK_COUNTS 4000   // 200 mS worth of timer ticks

#define USS_TRIGGER1 12
#define USS_TRIGGER2 11
#define USS_TRIGGER3 10

#define USS_ECHO1  2
#define USS_ECHO2  3
#define USS_ECHO3  19

#define KP  0.5
#define KI  4
#define KD  0.03
#define TF  0

// PID-regulator variables
unsigned long timer_us;
static uint32_t pidTimer_us = 0;
double h;
// Reference values
float ref_left;
float ref_right;
// Reference error
float e_left;
float e_right;
float e_old_left;
float e_old_right;
// PID variables
float P_left;
float P_right;
float D_left;
float D_right;
float I_left;
float I_right;
// PID output
float u_left;
float u_right;


/////////////////////
// ::: Components :::
/////////////////////

//IMU imu;                    // Class used for IMU functions
//Motor rightMotor(MOTORRIGHT, &SERIALRIGHT);
//Motor leftMotor(MOTORLEFT, &SERIALLEFT);
USS left_USS(USS_TRIGGER1, USS_ECHO1);



/////////////////////
// Interrupt function used to check sensors
/////////////////////

void checkSensors()
{
  Serial.println("It's working!");
  // leftUSS.timerIsr();
  
}


/////////////////////
// Initializations
/////////////////////

void setup()
{
  // imu.initIMU();              // Initialise the IMU
  
  SERIALRIGHT.begin(115200);
  SERIALLEFT.begin(115200);
  //rightMotor.initMotor();     // Initialise the right motor
  //leftMotor.initMotor();      // Initialise the left motor

  left_USS.initUSS();            // Initialise the left USS

  Timer1.initialize(TIMER_US); // Initialise timer 1
  Timer1.attachInterrupt(checkSensors);

  Serial.begin(115200);
}


/////////////////////
// Main loop, control system
/////////////////////

void loop()
{
  delay(1000);
  Serial.println("Left USS value is: ");
  Serial.print(left_USS.readUSS());
  /*
  // Time management - read actual time and calculate the time since last sample time
  timer_us = micros(); // Time of current sample in microseconds
  h = (double)(timer_us - pidTimer_us) / 1000000.0; // Time since last sample in seconds
  pidTimer_us = timer_us;  // Save the time of this sampleTime of last sample

  // Read RPM of left and right motors (reference value)
  float leftRPM = leftMotor.readSpeed();
  float rightRPM = rightMotor.readSpeed();

  // Reference error
  e_left = ref_left - leftRPM;
  e_right = ref_right - rightRPM;

  // PID-regulator
  P_left = KP * e_left;
  P_right = KP * e_right;

  D_left = TF / (TF + h) * D_left + KD / (TF + h) * (e_left - e_old_left);
  D_right = TF / (TF + h) * D_right + KD / (TF + h) * (e_right - e_old_right);

  u_left = P_left + I_left + D_left; // Calculate control output
  u_right = P_right + I_right + D_right;

  I_left = I_left + KI * h * e_left;
  I_right = I_right + KI * h * e_right;

  // Control system
  leftMotor.setRPM(u_left);
  rightMotor.setRPM(u_right);
  */

  /*
  // Example code for the IMU
  imu.updateIMU();
  Serial.println(imu.angle[1]);
  */
}








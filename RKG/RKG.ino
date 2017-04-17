/////////////////////
// :::  Includes :::
/////////////////////

#include "Config.h"
#include "IMU.h"
#include "Motor.h"
//#include "Cutting.h"
#include "IR.h"
#include "USS.h"
#include "ObjectManagement.h"
#include <TimerOne.h>


/////////////////////
// ::: Variables :::
/////////////////////

// PID-regulator variables
unsigned long timer_us;
static uint32_t pidTimer_us = 0;
double h;

// Reference values
float ref_vinkel = 0;
float ref_left;
float ref_right;

// Reference error
float e_vinkel;
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

// Control output
float u1;
float u2;

// Used for communication between USS
bool ussLeftTrig = false;
bool ussMidTrig = false;
bool ussRightTrig = false;


/////////////////////
// ::: Components :::
/////////////////////

IMU imu;                    // Class used for IMU functions
Motor rightMotor(MOTORRIGHT, &SERIALRIGHT);
Motor leftMotor(MOTORLEFT, &SERIALLEFT);
USS left_USS(USS_TRIGGER1, USS_ECHO1,USS_MIN_DISTANCE);
USS mid_USS(USS_TRIGGER2, USS_ECHO2,USS_MIN_DISTANCE);
USS right_USS(USS_TRIGGER3, USS_ECHO3,USS_MIN_DISTANCE);
ObjectManagement obj_management;
IR irSensors;



/////////////////////
// Interrupt function used to check sensors
/////////////////////

/*
 * Send USS pulse from all sensors
 */
void triggerUSS()
{
  left_USS.trigger_pulse();
  mid_USS.trigger_pulse();
  right_USS.trigger_pulse();
}

/*
 * Stop if sensors detects object
 */
void recieveEchoLeft(){
  if(!left_USS.echo_recieve()){
    ussLeftTrig = true;
    Serial.println("left");
    obj_management.setAvgSpeed(15);
  }
  else if(!ussMidTrig && !ussRightTrig){
    ussLeftTrig = false;
    obj_management.setAvgSpeed(30);
  }
  else { ussLeftTrig = false; }
}
void recieveEchomid(){
  if(!mid_USS.echo_recieve()){
    ussMidTrig = true;
    Serial.println("mid");
    obj_management.setAvgSpeed(15);
  }
  else if(!ussLeftTrig && !ussRightTrig){
    ussMidTrig = false;
    obj_management.setAvgSpeed(30);
  }
  else { ussMidTrig = false; }
}
void recieveEchoright(){
  if(!right_USS.echo_recieve()){
    ussRightTrig = true;
    Serial.println("right");
    obj_management.setAvgSpeed(15);
  }
  else if(!ussLeftTrig && !ussMidTrig){
    ussRightTrig = false;
    obj_management.setAvgSpeed(30);
  }
  else { ussRightTrig = false; }
}

/*
 * Stop & turn around when bumper sensor is activated
 */
void bumperChange(){ obj_management.objectDetection(); }

/////////////////////
// Initializations
/////////////////////

void setup()
{
  // Intertial Measurement Unit (IMU)
  imu.initIMU();                         // Initialise the IMU
  
  // Motors
  SERIALRIGHT.begin(115200);            // Serial communication with hall sensors
  SERIALLEFT.begin(115200);             // Serial communication with hall sensors
  rightMotor.initMotor();               // Initialise the right motor
  leftMotor.initMotor();                // Initialise the left motor
  obj_management.setAvgSpeed(AVG_RPM);  // Set average speed for motors

  // Ultrasonic sensor (USS)
  left_USS.initUSS();                   // Initialise the left USS
  mid_USS.initUSS();                    // Initialise the mid USS
  right_USS.initUSS();                  // Initialise the right USS
  Timer1.initialize(TIMER1_US);         // Initialise timer1
  Timer1.attachInterrupt(triggerUSS);   // Trigger USS every timer tick
  attachInterrupt(digitalPinToInterrupt(USS_ECHO1), recieveEchoLeft, CHANGE);     // Recieve echo when echo pin changes
  attachInterrupt(digitalPinToInterrupt(USS_ECHO2), recieveEchomid, CHANGE);      // Recieve echo when echo pin changes
  attachInterrupt(digitalPinToInterrupt(USS_ECHO3), recieveEchoright, CHANGE);    // Recieve echo when echo pin changes
  attachInterrupt(digitalPinToInterrupt(BUMPERPIN), bumperChange, HIGH);          // Recieve echo when echo pin changes
 
  Serial.begin(115200);
}


/////////////////////
// Main loop, control system
/////////////////////

void loop()
{

/*
 * If RKG is done turning reset reference angle,
 * otherwise check current angle offset
 */
  if(obj_management.turningDone(imu.angle[1])){
    imu.resetIMU();
  }
  ref_vinkel = obj_management.getAngleRef();
  u1 = obj_management.getAvgSpeed();

/*
 * Control system part 1
 * Make sure angle offset is small enough
 */
  imu.updateIMU();
  e_vinkel = ref_vinkel - round(imu.angle[1]);
  u2 = KP_F * e_vinkel;

  // Calculate new RPM for both motors
  ref_right = u1 + u2/2;
  ref_left = u1 - u2/2;

/*
 * Control system part 2
 * Make sure both motors have the selected RPM
 */
  // Time management - read actual time and calculate the time since last sample time
  timer_us = micros(); // Time of current sample in microseconds
  h = (double)(timer_us - pidTimer_us) / 1000000.0; // Time since last sample in seconds
  pidTimer_us = timer_us;  // Save the time of this sampleTime of last sample
  
  // Read RPM of left and right motors (reference value)
  leftMotor.updateMotor();
  rightMotor.updateMotor();
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
  

}

/*
 * Comments:
 */
//om antingen IMU-värden fuckar eller om mjukstart inte funkar kan det vara nya implementering av integral.
//Om mjukstart inte tillräckligt mjuk (ska ske efter 1 sek) så dela h med två i obj_maneg.

/*
 * TO-DO
 */
// - Make IR sensors use 2 different classes to enable more / fewer IR sensors without much work
// - Make sure that motors actually stop when voltage is too low

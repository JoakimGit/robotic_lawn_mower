/////////////////////
// :::  Includes :::
/////////////////////
#include "Config.h"
#include "IMU.h"
#include "Motor.h"
#include "Cutting.h"
#include "IR.h"
#include "USS.h"
#include "ObjectManagement.h"
#include <TimerOne.h>


//////////////////////////////
// ::: Regulator Variables :::
//////////////////////////////
// Time
unsigned long timer_us;
static uint32_t pidTimer_us = 0;
double h;

// Reference values
float ref_angle = 0;
float ref_left;
float ref_right;

// Reference error
float e_angle;
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
float kp_f;       // Outer P-reg

// PID output
float u_left;
float u_right;

// Control signal
float u1;         // Angle
float u2;         // Velocity

// Used for communication between USS
bool ussLeftTrig = false;
bool ussMidTrig = false;
bool ussRightTrig = false;
bool ussOn = true;


/////////////////////
// ::: Components :::
/////////////////////
IMU imu;
Motor rightMotor(MOTORRIGHT, &SERIALRIGHT);
Motor leftMotor(MOTORLEFT, &SERIALLEFT);
USS left_USS(USS_TRIGGER1, USS_ECHO1,USS_MIN_DISTANCE);
USS mid_USS(USS_TRIGGER2, USS_ECHO2,USS_MIN_DISTANCE);
USS right_USS(USS_TRIGGER3, USS_ECHO3,USS_MIN_DISTANCE);
ObjectManagement obj_management;
IR irFront(IRPIN_FRONT);
IR irBack(IRPIN_BACK);



//////////////////////////////
// ::: Interrupt functions :::
//////////////////////////////
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
 * slowdown or stop if sensors detects object
 */
void recieveEchoLeft(){
  if(!left_USS.echo_recieve()&&ussOn){
    ussLeftTrig = true;
    obj_management.setAvgSpeed(15);
  }
  else if(!ussMidTrig && !ussRightTrig && ussOn){
    ussLeftTrig = false;
    obj_management.setAvgSpeed(30);
  }
  else { ussLeftTrig = false; }
}
void recieveEchomid(){
  if(!mid_USS.echo_recieve()&&ussOn){
    ussMidTrig = true;
    obj_management.setAvgSpeed(15);
  }
  else if(!ussLeftTrig && !ussRightTrig && ussOn){
    ussMidTrig = false;
    obj_management.setAvgSpeed(30);
  }
  else { ussMidTrig = false; }
}
void recieveEchoright(){
  if(!right_USS.echo_recieve()&&ussOn){
    ussRightTrig = true;
    obj_management.setAvgSpeed(15);
  }
  else if(!ussLeftTrig && !ussMidTrig && ussOn){
    ussRightTrig = false;
    obj_management.setAvgSpeed(30);
  }
  else { ussRightTrig = false; }
}

/*
 * Stop & turn around when bumper sensor is activated
 */
void bumperChange()
{ 
  obj_management.objectDetection(); 
  ussOn = false;
  kp_f = 0.5;
}

/*
 * Check if RKG is close enough to the grind with IR sensors
 * Return true if distance is too far
 */
bool checkIR()
{
  return (irFront.check() || irFront.check());
}

//////////////////////////
// ::: Initializations :::
//////////////////////////
void setup()
{
  Serial.begin(115200);
 
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
  pinMode(LEDPIN,OUTPUT);

  // Bumper sensor
  attachInterrupt(digitalPinToInterrupt(BUMPERPIN), bumperChange, HIGH);          // Recieve echo when echo pin changes
  
  // Intertial Measurement Unit (IMU)
  kp_f = KP_F;
  imu.initIMU();                        // Initialise the IMU
  
}


/////////////////////////
// ::: Control system :::
/////////////////////////
void loop()
{
  // Stop if RKG is lifted or if battery voltage is too low
  if(checkIR() ||leftMotor.voltage < 17){
    leftMotor.stopMotor();
    rightMotor.stopMotor();
    Serial.println(leftMotor.voltage);
    while(1){
      digitalWrite(LEDPIN,HIGH);
      delay(500);
      digitalWrite(LEDPIN,LOW);
      delay(500);
    }
  }

/*
 * If RKG is done turning reset reference angle,
 * otherwise check current angle offset
 */
  if(obj_management.turningDone(imu.angle[1])){
    leftMotor.stopMotor();
    rightMotor.stopMotor();
    imu.resetIMU();
    ussOn = true;
    kp_f = KP_F;
    
  }

/*
 * Outer control system
 * Keep angle offset small
 */
  // Reference value
  ref_angle = obj_management.getAngleRef();
  u1 = obj_management.getAvgSpeed();
  
  // Reference error
  imu.updateIMU();
  e_angle = ref_angle - ((imu.angle[1]));

  // Control signal
  u2 = kp_f * e_angle;

  // Reference value for inner control system
  ref_right = u1 + u2/2;
  ref_left = u1 - u2/2;

/*
 * Inner control system
 * Make sure both motors have the selected RPM
 */
  // Time management
  // h is time since last sample [us]
  timer_us = micros();
  h = (double)(timer_us - pidTimer_us) / 1000000.0;
  pidTimer_us = timer_us;
  
  // Read reference value (RPM from motors)
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

  // Control signal
  u_left = P_left + I_left + D_left;
  u_right = P_right + I_right + D_right;

  // Calculate I-value (Euler forward)
  I_left = I_left + KI * h * e_left;
  I_right = I_right + KI * h * e_right;

  // Control system
  leftMotor.setRPM(u_left);
  rightMotor.setRPM(u_right);
}

/*
 * Configuration file
 * Used to define values of the RKG and all of its components
 */
 
#ifndef CONFIG_H
#define CONFIG_H


/////////////////////
// ::: Parameters :::
/////////////////////

/*
 * Arduino
 * Used by IR, ObjectManagement & IMU.
 */
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

/*
 * Regulator parameters
 */
#define KP_F 1                  // KP value of P-regulator controlling angle offset

#define KP  0.03                // KP value of PID-regualtor controlling RPM offset
#define KI  5                   // KI value of PID-regualtor controlling RPM offset
#define KD  0.03                // KD value of PID-regualtor controlling RPM offset
#define TF  0                   // TF value of PID-regualtor controlling RPM offset


/*
 * Object management
 */
#define PERIOD   0.03           // Period in seconds, whole program 0.04
#define BACKTIME 4              // How long the RKG goes backwards after collision


/*
 * Ultrasonic sensor
 */
#define TIMER1_US    50         // Timer ticks every 50 uS
#define TICK_COUNTS  4000       // 200 mS worth of timer ticks, trigger USS pulse
#define MAX_COUNT    2          // How many time distance is allowed to go past max_distance

#define USS_MIN_DISTANCE 80     // Echo_recieve will return true when distance is below 80 cm
// PINs used to send pulses
#define USS_TRIGGER1 12         // Left sensor
#define USS_TRIGGER2 11         // Mid sensor
#define USS_TRIGGER3 10         // Right sensor
// PINs used to recieve echos
#define USS_ECHO1  2            // Left sensor
#define USS_ECHO2  3            // Mid sensor
#define USS_ECHO3  19           // Right sensor


/*
 * Motor
 */
#define MAX_RPM     65          // Maximum rotations per minute allowed for the motors
#define AVG_RPM     30          // Normal RPM of the motors
#define HALL2RPM    57.75       // Measured value for gear box and electric poles
#define MIN_VOLTAGE 17          // Minimum voltage recommended for battery
#define MOTORRIGHT  8           // Pin 8 is connected to the right motor
#define MOTORLEFT   9           // Pin 9 is connected to the left motor
#define SERIALRIGHT Serial3     // Serial ports connected to the right hall sensor
#define SERIALLEFT  Serial2     // Serial ports connected to the left hall sensor

#include "vesc_uart.h"
#include <SPI.h>
#include <Servo.h>
#include "datatypes.h"

/*
 * Intertial Measurement Unit (IMU)
 */
#include "stdint.h"           // Enables use of uint8_t
#include "Wire.h"             // Used to connect with the IC2 device

// Arduino mega 2560 rev3 addresses used by the IMU.
#define    MPU9250_ADDRESS            0x68    
#define    MAG_ADDRESS                0x0C
#define    GYRO_FULL_SCALE_2000_DPS   0x18    
#define    ACC_FULL_SCALE_16_G        0x18
#define    ACC_SENSITIVITY            2048   
#define    GRAVITY                    9.82    // Gravity in Sweden


/*
 * Bumper sensor
 */
#define BUMPERPIN 18  // PIN used by the bumper sensor





#endif // CONFIG_H

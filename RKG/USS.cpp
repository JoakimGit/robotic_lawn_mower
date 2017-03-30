//
// Created by Joakim on 2017-03-25.
//

#include "USS.h"


// Constructor
// pinOut: trigger output (Pins 10-12)
// pinIn: echo input (Pins 2-4)
// interruptPin: interrupt id (for echo pulsePins 0-2 are interrupt signals)
USS::USS(int pinOut, int pinIn, int interrupt)
{
    trigPin = pinOut;
    echoPin = pinIn;
    interrupt = interrupt;
    echo_start = 0;
    echo_end = 0;
    echo_duration = 0;
    trigger_time_count = 0;
    floatingCounter = 0;
}


/*
 ***** Public methods *****
 */

// Initiate USS
void USS::initUSS()
{
  // pinMode(trigPin, OUTPUT);
  // pinMode(echoPin, INPUT);
  // Timer1.attachInterrupt( timerIsr );                 // Attach interrupt to the timer service routine 
  // attachInterrupt(interruptPin, echo_interrupt(), CHANGE);  // Attach interrupt to the sensor echo input
  // echo_duration = 180;
}

int USS::readUSS()
{
  // return echo_duration/58;   // Print the distance in centimeters
  return 0;
}


/*
 ***** Private methods *****
 */

/*
void echo_interrupt1()
{
  switch (digitalRead(echoPin1))                     // Test to see if the signal is high or low
  {
    case HIGH:                                      // High so must be the start of the echo pulse
      echo_end = 0;                                 // Clear the end time
      echo_start = micros();                        // Save the start time
      break;
      
    case LOW:                                       // Low so must be the end of hte echo pulse
      echo_end = micros();                          // Save the end time
      echo_duration = echo_end - echo_start;        // Calculate the pulse duration
      break;
  }
}
*/


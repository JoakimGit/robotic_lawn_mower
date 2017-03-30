//
// Created by Joakim on 2017-03-25.
//

#include "USS.h"


// Constructor
// pinOut: trigger output (Pins 10-12)
// pinIn: echo input (Pins 2-4)
// interruptPin: interrupt id (for echo pulsePins 0-2 are interrupt signals)
USS::USS(int trigPin, int echoPin)
{
    USS::trigPin = trigPin;
    USS::echoPin = echoPin;
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
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Timer1.attachInterrupt( timerIsr() );                 // Attach interrupt to the timer service routine 
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

// timerIsr() 50uS second interrupt ISR()
// Called every time the hardware timer 1 times out.
// --------------------------
void timerIsr()
{
    trigger_pulse();                                 // Schedule the trigger pulses
}

// trigger_pulse() called every 50 uS to schedule trigger pulses.
// Generates a pulse one timer tick long.
// Minimum trigger pulse width for the HC-SR04 is 10 us. This system
// delivers a 50 uS pulse.
// --------------------------
void trigger_pulse()
{
      static volatile int state = 0;                 // State machine variable

      if (!(--trigger_time_count))                   // Count to 200mS
      {                                              // Time out - Initiate trigger pulse
         trigger_time_count = TICK_COUNTS;           // Reload
         state = 1;                                  // Changing to state 1 initiates a pulse
      }
    
      switch(state)                                  // State machine handles delivery of trigger pulse
      {
        case 0:                                      // Normal state does nothing
            break;
        
        case 1:                                      // Initiate pulse
           digitalWrite(trigPin, HIGH);              // Set the trigger output high
           state = 2;                                // and set state to 2
           break;
        
        case 2:                                      // Complete the pulse
        default:      
           digitalWrite(trigPin, LOW);              // Set the trigger output low
           state = 0;                                // and return state to normal 0
           break;
     }
}

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



#include "USS.h"

// Constructor
// pinOut: trigger output (Pins 10-12)
// pinIn: echo input (Pins 2-4)
// interruptPin: interrupt id (for echo pulsePins 0-2 are interrupt signals)
USS::USS(int trigPin, int echoPin, int minDistance)
{
    USS::trigPin = trigPin;
    USS::echoPin = echoPin;
    min_distance = minDistance;
    echo_start = 0;
    echo_end = 0;
    echo_duration = 2000;
    trigger_time_count = 0;
    state = 0;
    floatingCounter = 0;
    max_counter = 0;
}


/*
 ***** Public methods *****
 */

// Initiate USS
void USS::initUSS()
{
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.println("initUSS...");
  Serial.print("Trigger/Echo pins: ");
  Serial.print(USS::trigPin);
  Serial.print("\t");
  Serial.println(USS::echoPin);
  delay(2000);
}

// Return last measured distance (cm)
int USS::readDistance()
{
  return echo_duration/58;
}

/*
 * trigger_pulse() called every 50 uS to schedule trigger pulses.
 * Generates a pulse one timer tick long.
 */
void USS::trigger_pulse()
{    
      if (((--trigger_time_count) < 0))              // Count to 200mS
      {                                              // Time out - Initiate trigger pulse
         trigger_time_count = TICK_COUNTS;           // Reload (TICK_COUNTS = 4000)
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

// Recieve echo
void USS::echo_interrupt()
{
  switch (digitalRead(echoPin))                     // Test to see if the signal is high or low
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

// Recieve echo and return true if echo distance is less than min_distance.
bool USS::echo_recieve() {
    echo_interrupt();
    
    if (readDistance() < min_distance) {
      max_counter++;
    } else {
      max_counter = 0;
    }
    
    if (max_counter < MAX_COUNT) {
      return true;
    } else {
      return false;
    }
}
 

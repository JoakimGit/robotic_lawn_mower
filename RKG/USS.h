
#ifndef USS_H
#define USS_H

#include <Arduino.h>

#ifndef CONFIG_H
#include "Config.h"            // Include configurations.
#endif // CONFIG_H
 

class USS {
public:
    USS(int pinOut, int pinIn, int minDistance);
    void initUSS();          // Initialise PINs and variables
    int readDistance();      // Return last measured distance (cm)
    void trigger_pulse();    // Send ultrasonic pulse
    void echo_interrupt();   // Recieve echo
    bool echo_recieve();     // Recieve echo & check if an object is within min_distance.
    int echoPin;             // PIN that recieves echo
    
private:
    // Variables
    int trigPin;                            // Triggers output
    volatile long echo_start;               // Records start of echo pulse 
    volatile long echo_end;                 // Records end of echo pulse
    volatile long echo_duration;            // Duration - difference between end and start
    
    volatile long trigger_time_count;       // Count down counter to trigger pulse time
    volatile int floatingCounter;
    volatile int state;

    volatile int min_distance;              // Minimum distance to an object allowed
    volatile int max_counter;               // How many times the distance is below min_distance
};


#endif // USS_H


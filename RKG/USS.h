/*
 * Created by Joakim on 2017-03-25.
 */

#ifndef USS_H
#define USS_H

#include <Arduino.h>

/*
 * Defines
 */

#define TIMER    50        // Timer is set to 50 uS
#define TICK_COUNTS 4000   // 200 mS worth of timer ticks

class USS {
public:
    USS(int pinOut, int pinIn);
    void initUSS();
    int readUSS();
    

private:
    void timerIsr();                      // 50mS interrupt ISR(). Called evert time the hardware timer 1 times out.
    void trigger_pulse();
    void distance_flasher();
    
    // Variables
    int trigPin;                            // Triggers output
    int echoPin;                            // Recieves echo
    volatile long echo_start;               // Records start of echo pulse 
    volatile long echo_end;                 // Records end of echo pulse
    volatile long echo_duration;            // Duration - difference between end and start
    volatile long trigger_time_count;       // Count down counter to trigger pulse time
    volatile int floatingCounter;
};


#endif // USS_H

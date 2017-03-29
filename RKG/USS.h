/*
 * Created by Joakim on 2017-03-25.
 */

#ifndef USS_H
#define USS_H

//#include <TimerOne.h>     // Used for timer

/*
 * Defines
 */

#define TIMER    50        // Timer is set to 50 uS
#define TICK_COUNTS 4000   // 200 mS worth of timer ticks

class USS {
public:
    USS(int pinOut, int pinIn, int interrupt);
    void initUSS();
    int readUSS();
    

private:
    // void privateFunction();
    
    // Variables
    int trigPin;                            // Triggers output
    int echoPin;                            // Recieves echo
    int interruptPin;                          // Interrupt ID for echo pulse
    volatile long echo_start;               // Records start of echo pulse 
    volatile long echo_end;                 // Records end of echo pulse
    volatile long echo_duration;            // Duration - difference between end and start
    volatile long trigger_time_count;       // Count down counter to trigger pulse time
    volatile int floatingCounter;
};


#endif // USS_H

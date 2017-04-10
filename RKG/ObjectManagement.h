/*
 * 
 */

#ifndef OBJECT_MANAGEMENT_H
#define OBJECT_MANAGEMENT_H

/*
 * Defines
 */
#define PERIOD 0.03     // Period in seconds, 0.002 prev, 0.04 for whole program
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

class ObjectManagement {
public:
    ObjectManagement();              // Constructor
    void setAvgSpeed(float Avgspeed);     // 
    float getAvgSpeed();
    void objectDetection();
    float getAngleRef();
    bool turningDone(float angle);
    
    

private:
    // void privateFunction();
    float avgspeedgoal;
    float current_avg = 0;
    unsigned long time4detection;
    double h;
    unsigned long timer;
    unsigned long last_timer;
    float angleref = 0;
    bool detection = false;
    bool turning = false;
};


#endif // OBJECT_MANAGEMENT_H

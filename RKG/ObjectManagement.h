
#ifndef OBJECT_MANAGEMENT_H
#define OBJECT_MANAGEMENT_H

#ifndef CONFIG_H
#include "Config.h"                     // Include configurations.
#endif // CONFIG_H

class ObjectManagement {
public:
    ObjectManagement();                 // Constructor
    void setAvgSpeed(float Avgspeed);   // Set the wanted average speed
    float getAvgSpeed();                // Smoothly change current speed to wanted speed.
    void objectDetection();             // Turn around if bumper sensor is activated
    float getAngleRef();                // Handle reference angle reset
    bool turningDone(float angle);      // Start driving when turning is done
    
    
    

private:
    float avgspeedgoal;                 // Wanted average speed
    float current_avg;                  // Current average speed
    unsigned long time4detection;       // Timer initiated after collision
    double h;
    double obj_timer;
    float angleref;
    bool detection;                     // True from collision until done turning
    bool turning;                       // True when turning
    int dir;                            // Direction which the robot turns
};


#endif // OBJECT_MANAGEMENT_H

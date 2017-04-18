
#include "ObjectManagement.h"


// Constructor
ObjectManagement::ObjectManagement()
{
  current_avg = 0;
  angleref = 0;
  detection = false;
  turning = false;
}


/*
 ***** Public methods *****
 */

// Set the wanted average speed`
void ObjectManagement::setAvgSpeed(float avgspeed)
{
  avgspeedgoal = avgspeed;
}

// Smoothly change current speed to wanted speed.
float ObjectManagement::getAvgSpeed()
{
  if(current_avg < avgspeedgoal || detection){
    current_avg = current_avg + PERIOD*avgspeedgoal/2; // After 1 second speed goal will be met
  }
  else if(current_avg > avgspeedgoal){
    current_avg = current_avg - PERIOD*avgspeedgoal;
  }
  
  return current_avg;
}

// Turn around if bumper sensor is activated
void ObjectManagement::objectDetection()
{
  current_avg = 0;
  avgspeedgoal = -20;
  turning = false;
  angleref = 0;
  time4detection = millis();
  detection = true;
  Serial.println("Back!");
}

// Handle reference angle reset
float ObjectManagement::getAngleRef()
{
  obj_timer = (millis() - time4detection)/1000;
  if(obj_timer > 2*BACKTIME/4 && obj_timer < BACKTIME && detection){
    current_avg = 0;
    avgspeedgoal = 0;
    Serial.println("slowing down!");
  }

  if(obj_timer > BACKTIME && detection){
    detection = false;
    current_avg = 0;
    dir = (int)(random(0,2));
    Serial.println(dir);
    if(dir){
      angleref = random(60,120);
    }
    else{
      angleref = random(-120,-60);
    }
    turning = true;
  }

  return angleref;
}

// Start driving when turning is done
bool ObjectManagement::turningDone(float angle)
{
  if(abs(angleref - angle) < 10 && turning){
    //Serial.println(angle);
    turning = false;
    angleref = 0;
    avgspeedgoal = 30;
    return true;
  }
  else{ 
    return false;
  }
}

/*
 ***** Private methods *****
 */

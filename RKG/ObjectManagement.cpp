//
//
//

#include "ObjectManagement.h"


// Constructor
ObjectManagement::ObjectManagement()
{
}


/*
 ***** Public methods *****
 */

// set the average speed with a filter
void ObjectManagement::setAvgSpeed(float avgspeed)
{
  avgspeedgoal = avgspeed;
}

float ObjectManagement::getAvgSpeed()
{
 
  if(current_avg < avgspeedgoal || detection){
    current_avg = current_avg + PERIOD*avgspeedgoal/2; //filter, efter 1 sekund blir värdet riktigt.
  }
  return current_avg;
}

void ObjectManagement::objectDetection()
{
  current_avg = 0;
  avgspeedgoal = -20;
  turning = false;
  angleref = 0;
  time4detection = millis();
  detection = true;
}

float ObjectManagement::getAngleRef()
{
  if(millis() - time4detection > 4500 && detection){
    detection = false;
    current_avg = 0;
    avgspeedgoal = 0;
    angleref = random(45,195);
    turning = true;
    Serial.print("angleref ");
    Serial.println(angleref);
  }

  return angleref;
}

bool ObjectManagement::turningDone(float angle)
{
  if(abs(angleref - angle) < 15 && turning){
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

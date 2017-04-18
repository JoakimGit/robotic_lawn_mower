
#include "IR.h"

// Constructor
IR::IR(int irpin)
{
  pin = irpin;
  trigger_distance = IR_TRIGGER_DISTANCE;
  ir_count = 0;
  max_count = IR_MAX_COUNT;
}


/*
 ***** Public methods *****
 */

// Return true if distance is too far
bool IR::check(){
   if(analogRead(pin) < trigger_distance){
    ir_count ++;
   }
   else{
    ir_count = 0;
   }
   if(ir_count > max_count){
    return true;
   }
   return false;
}

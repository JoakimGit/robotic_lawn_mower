
#include "IR.h"

// Constructor
IR::IR()
{
}


/*
 ***** Public methods *****
 */

// Return true if distance is too far
bool IR::breakIR(){
   irval1 = analogRead(irpin1);
   irval2 = analogRead(irpin2);
   if(irval1 < 150 || irval2 < 150){
    ir_count ++;
   }
   else{
    ir_count = 0;
   }
   if(ir_count >10){
    return true;
   }
   return false;
}

/*
 ***** Private methods *****
 */

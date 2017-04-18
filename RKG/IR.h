
#ifndef IR_H
#define IR_H

#ifndef CONFIG_H
#include "Config.h"                   // Include configurations.
#endif // CONFIG_H

class IR {
  public:
    IR(int pin);   // Constructor
    bool check();                    //
    

  private:
    int pin;
    int trigger_distance;
    int ir_count;
    int max_count;


};


#endif //IR_H

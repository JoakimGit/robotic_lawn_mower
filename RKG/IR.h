
#ifndef IR_H
#define IR_H

#ifndef CONFIG_H
#include "Config.h"                 // Include configurations.
#endif // CONFIG_H

class IR {
  public:
    IR();              // Constructor
    void initIR();     // 
    bool breakIR();
    

  private:
    // void privateFunction();
    int irpin1 = 5;
    int irval1 = 300;

    int irpin2 = 6;
    int irval2 = 300;

    int ir_count;


};


#endif //IR_H

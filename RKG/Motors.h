/*
 * Created by Joakim on 2017-03-25.
 */

#ifndef MOTORS_H
#define MOTORS_H

/*
 * Defines
 */

#define PERIOD    0.01      // Period in seconds


class Motors {
public:
    Motors();              // Constructor
    void initMotors();     // Initialize I2C bus
    

private:
    // void privateFunction();
};


#endif //MOTORS_H


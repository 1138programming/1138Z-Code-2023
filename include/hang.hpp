#ifndef MAIN_HPP
#define MAIN_HPP

#include "vex.h"

class Hang {
    vex::motor* hangMotor;
    public:
        Hang(vex::motor* hangMotor) {
            this->hangMotor = hangMotor;
        }
        void move(double movement) {
            this->hangMotor->spin(vex::forward, movement, vex::pct);
        }
};

#endif
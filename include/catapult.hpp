#ifndef CATA_HPP
#define CATA_HPP

#include "vex.h"
#include "constants.hpp"

class Catapult {
    vex::motor* catapultMotor;
    public:
        Catapult(vex::motor* catapultMotor) {
            this->catapultMotor = catapultMotor;
        }
        void move() {
            this->catapultMotor->setVelocity(100 * kCatapultSpeedMultiplier, vex::pct);
        }
        void stopMoving() {
            this->catapultMotor->setVelocity(0,vex::pct);
        }
};

#endif
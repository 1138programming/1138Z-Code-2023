#ifndef CATA_HPP
#define CATA_HPP

#include "main.h"
#include "Constants.hpp"


class Catapult {
    pros::Motor* catapultMotor;
    public:
        Catapult(pros::Motor* catapultMotor) {
            this->catapultMotor = catapultMotor;
        }
        void move() {
            this->catapultMotor->move(127*kCatapultSpeedMultiplier);
        }
        void stopMoving() {
            this->catapultMotor->move(0);
        }
};


#endif
#ifndef CATA_HPP
#define CATA_HPP

#include "vex.h"
#include "constants.hpp"

class Catapult {
    vex::motor* catapultMotor;
    bool cataToggle = false;
    public:
        Catapult(vex::motor* catapultMotor) {
            this->catapultMotor = catapultMotor;
        }
        void moveWithActiveCheck() {
            if (this->cataToggle) {
                moveCatapult();
            }
            else {
                stopMoving();
            }
        }
        void moveCatapult() {
            this->catapultMotor->spin(vex::forward, 100 * kCatapultSpeedMultiplier, vex::pct);
        }
        void stopMoving() {
            this->catapultMotor->spin(vex::forward, 0,vex::pct);
        }
        void catapultToggle() {
            this->cataToggle = !cataToggle;
        }
};

#endif
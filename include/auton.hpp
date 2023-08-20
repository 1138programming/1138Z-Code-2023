#ifndef AUTON_HPP
#define AUTON_HPP

#include "vex.h"
#include "base.hpp"
#include "constants.hpp"

class Autons {
    Base* base;
    public:
        void driveForwardForSpecifiedTime(float seconds) {
        float initialTime = vex::timer::systemHighResolution()/1000;

        // while(pros::millis()/1000 - initialTime < seconds/3) {
        //     this->base->moveLeftMotors(100);
        //     this->base->moveRightMotors(-100);
        // }

        while(vex::timer::systemHighResolution()/1000 - initialTime < seconds) {
            //wait
            this->base->driveBothSides(kDriveForwardAutonSpeed);
            vex::wait(10,vex::msec);
        }
        this->base->driveBothSides(0);
    }
};

#endif
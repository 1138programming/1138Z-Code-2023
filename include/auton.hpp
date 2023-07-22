#ifndef AUTON_HPP
#define AUTON_HPP

#include "main.h"
#include "base.h"

class Autons {
    Base* base;
    public:
        //Can't make this const... don't screw anything up.
        Autons(Base* base) {
            this->base = base;
        }
        void driveForwardForSpecifiedTime(float seconds) {
            float initialTime = pros::millis()/1000;

            // while(pros::millis()/1000 - initialTime < seconds/3) {
            //     this->base->moveLeftMotors(100);
            //     this->base->moveRightMotors(-100);
            // }

            while(pros::millis()/1000 - initialTime < seconds) {
                //wait
                this->base->moveLeftMotors(-75);
                this->base->moveRightMotors(75);
                pros::delay(10);
            }
            this->base->driveStraight(0);
        }
};

#endif
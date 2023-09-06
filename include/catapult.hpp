#ifndef CATA_HPP
#define CATA_HPP

#include "vex.h"
#include "constants.hpp"

class Catapult {
    vex::motor* catapultMotor;
    bool cataToggle = false;
    bool lastControllerAButtonState = false;
    int motorPosition = 0;
    public:
        Catapult(vex::motor* catapultMotor) {
            this->catapultMotor = catapultMotor;
        }
        void setStopping(vex::brakeType mode) {
            this->catapultMotor->setStopping(mode);
        }
        // hold the catapult motor so we are more easily able to fit under the bar.
        void initHoldMotor(bool controllerAButtonState) {
            // return if controller not being pressed (do nothing.)
            if (controllerAButtonState == false) {
                // if we stopped pressing the button, reset everything.
                if (this->lastControllerAButtonState) {
                    setStopping(vex::coast);
                }
                // hasn't been pressed for a while
                else {
                    this->lastControllerAButtonState = controllerAButtonState;
                    return;
                }
            }
            // if current state == true and last == false (if we just started pressing button)
            if (this->lastControllerAButtonState == false) {
                //init all cata hold data
                setStopping(vex::hold);
                this->motorPosition = this->catapultMotor->position(vex::rev);
            }
            // if current state == true && last == true. (been pressing the button.)
            else {
                runHoldMotorRoutine();
            }
            this->lastControllerAButtonState = controllerAButtonState;
        }
        void runHoldMotorRoutine() {
            setStopping(vex::coast);
            if (this->catapultMotor->position(vex::rev) - this->motorPosition < 20) {
                moveCatapult();
            }
            else {
                stopMoving();
            }
            setStopping(vex::hold);
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
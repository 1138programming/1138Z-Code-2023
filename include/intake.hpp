#ifndef INTAKE_HPP
#define INTAKE_HPP

#include "vex.h"

class Intake {
    vex::motor* intakeMotor;
    bool movingForwards = true;
    bool thisDisabled = false;
    bool lastVal = false;
    bool lastFlip = false;
    public:
        Intake(vex::motor* intakeMotor) {
            this->intakeMotor = intakeMotor;
        }
        void moveWithController(bool local, bool flip) {
            this->enable();
            // if (local == true && local != this->lastVal) {
            //     this->toggleDisable();
            // }
            // if (flip == true && flip != this->lastFlip) {
            //     this->toggleDirection();
            // }
            move();
            this->lastVal = local;
            this->lastFlip = flip;
        }
        void move() {
            if (this->thisDisabled) {
                this->intakeMotor->spin(vex::forward, 0, vex::pct);
                return;
            }
            if (this->movingForwards) {
                this->intakeMotor->spin(vex::forward, kIntakeSpeed, vex::pct);
            }
            else if (!(this->movingForwards)) {
                this->intakeMotor->spin(vex::forward, -kIntakeSpeed, vex::pct);
            }
        }
        void toggleDirection() {
            this->movingForwards = !this->movingForwards;
        }
        void enable() {
            this->thisDisabled = false;
        }
        void disable() {
            this->thisDisabled = true;
        }
        void toggleDisable() {
            this->thisDisabled = !this->thisDisabled;
        }
};

#endif
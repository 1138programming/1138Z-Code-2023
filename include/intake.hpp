#ifndef INTAKE_HPP
#define INTAKE_HPP

#include "vex.h"

class Intake {
    vex::motor* intakeMotor;
    bool movingForwards = true;
    bool thisDisabled = false;
    bool lastVal = false;
    public:
        Intake(vex::motor* intakeMotor) {
            this->intakeMotor = intakeMotor;
        }
        void moveWithController(bool local) {
            if (local == true && local != this->lastVal) {
                this->toggleDisable();
            }
            this->lastVal = local;
        }
        void move(int speed) {
            if (this->thisDisabled) {
                this->intakeMotor->setVelocity(0, vex::pct);
                return;
            }
            speed = speed > 100 ? 100 : speed;
            speed = speed < 0 ? 0 : speed;
            if (!this->movingForwards) {
                this->intakeMotor->setVelocity(100, vex::pct);
            }
            else if (!this->movingForwards) {
                this->intakeMotor->setVelocity(-100, vex::pct);
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
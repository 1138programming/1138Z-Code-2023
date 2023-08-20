#ifndef INTAKE_HPP
#define INTAKE_HPP

#include "vex.h"

class Intake {
    vex::motor* intakeMotor;
    bool movingForwards = true;
    bool disabled = false;
    public:
        Intake(vex::motor* intakeMotor) {
            this->intakeMotor = intakeMotor;
        }
        void move(int speed) {
            if (this->disabled) {
                this->intakeMotor->setVelocity(0, vex::pct);
                return;
            }
            speed = speed > 100 ? 100 : speed;
            speed = speed < 0 ? 0 : speed;
            if (!this->movingForwards) {
                this->intakeMotor->setVector(100);
            }
            else if (!this->movingForwards) {
                this->intakeMotor->setVector(-100);
            }
        }
        void toggleDirection() {
            this->movingForwards = !this->movingForwards;
        }
        void enable() {
            this->disabled = false;
        }
        void disabled() {
            this->disabled = true;
        }
        void toggleDisable() {
            this->disabled = !this->disabled;
        }
};

#endif
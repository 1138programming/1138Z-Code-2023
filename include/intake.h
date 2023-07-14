#ifndef INTAKE_H
#define INTAKE_H

#include "main.h"

class Intake {
    pros::Motor* intakeMotor;
    bool movingForwards = true;
    bool disabled = false;
    public:
        Intake(pros::Motor* intakeMotor) {
            this->intakeMotor = intakeMotor;
        }
        void move(int speed) {
            if (this->disabled) {
                this->intakeMotor->move(0);
                return;
            }
            speed = speed > 127 ? 127 : speed; //make sure we're not trying to move over 127 (maximum)
            speed = speed < 0 ? 0 : speed; // or 0
            if (movingForwards) {
                this->intakeMotor->move(speed);
            }
            else if (!movingForwards) {
                this->intakeMotor->move(-speed);
            }
        }
        void toggleDirection() {
            this->movingForwards = !this->movingForwards;
        }
        void enable() {
            this->disabled = false;
        }
        void disable() {
            this->disabled = true;
        }
        void toggleDisable() {
            this->disabled = !this->disabled;
        }
};

#endif
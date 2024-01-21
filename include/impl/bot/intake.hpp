#ifndef INTAKE_HPP
#define INTAKE_HPP

#include "../include/lib/resources/controller.hpp"
#include "../include/lib/resources/controller_button.hpp"
#include "../include/vex.h"

class Intake {
    private:
        Controller* vexController;
        vex::motor* intakeMotor;
    public:
        Intake(vex::motor* intakeMotor, Controller* vexControoller) {
            this->vexController = vexController;
            this->intakeMotor = intakeMotor;
        }
        void run() {
            if (this->vexController->getVexObject()->ButtonR1.pressing()) {
                this->intakeMotor->spin(vex::forward, 100, vex::pct);
            }
            else if (this->vexController->getVexObject()->ButtonR2.pressing()) {
                this->intakeMotor->spin(vex::forward, -100, vex::pct);
            }
            else {
                this->intakeMotor->spin(vex::forward, 0, vex::pct);
            }
        }
};

#endif
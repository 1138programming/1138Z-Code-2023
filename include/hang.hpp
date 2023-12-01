#ifndef HANG_HPP
#define HANG_HPP

#include "vex.h"
#include "toggleable.hpp"

class Hang : public Toggleable {
    private:
        vex::digital_out hagPiston = (new vex::brain())->ThreeWirePort.A;
    public:
        void update(bool updateVal) {
            this->lastToggled = toggled;
            this->toggled = updateVal;
            if (this->isPressed()) {
                this->hagPiston.set(!this->hagPiston.value());
            }
        }
};

#endif
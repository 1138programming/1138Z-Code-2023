#ifndef HANG_HPP
#define HANG_HPP

#include "../include/vex.h"
#include "../include/lib/resources/toggleable.hpp"

class Hang : public Toggleable {
    private:
         vex::digital_out hangPiston = (new vex::brain())->ThreeWirePort.A;
    public:
        void update(bool val) {
            this->lastPressed = this->pressed;
            this->pressed = val;
            if (this->isPressed()) {
                this->hangPiston.set(!(this->hangPiston.value()));
            }
        }
};

#endif
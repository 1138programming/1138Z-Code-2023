#ifdef CONTROLLER_HPP
#define CONTROLLER_HPP

#include "vex.h"

class Controller {
    private:
        vex::controller* controller;
    public:
        Controller(vex::controllerType type) {
            this->controller = vex::controller(type);
        }

}

#endif
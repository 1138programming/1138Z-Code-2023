#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include "vex.h"
#include "controller_axis.hpp"
#include "controller_buttons.hpp"

class Controller {
    private:
        vex::controller* internalController;
    public:
        Controller(vex::controllerType type) {
            this->internalController = new vex::controller(type);
        }
        /**
         * @brief Allows users to do whatever they want with the internal controller
        */
        vex::controller* getVexController() {
            return this->internalController;
        }

        //functions
        /**
         * @brief returns a value between -100 and 100 representing the joystick axis position
         * @param axis The vex controller axis to use (as depicted by the buttons on this image): https://www.vexrobotics.com/media/catalog/product/cache/d64bdfbef0647162ce6500508a887a85/2/7/276-4820-v5-controller_home.jpg
         * @return value between -100 and 100 representing the joystick axis position
         * @warning vex controllers have pretty terrible deadzones... don't expect small numbers to be detected
        */
        int getAxis(ControllerAxis axis) {
            switch(axis) {
                case AXIS_1:
                    return this->internalController->Axis1.position();
                break;
                case AXIS_2:
                    return this->internalController->Axis2.position();
                break;
                case AXIS_3:
                break;
                case AXIS_4:
                break;
                default:
                    return -1;
            }
        }
};

#endif
#ifndef MOVEMENT_HPP
#define MOVEMENT_HPP

#include "base.hpp"
#include "motorgroup.hpp"
#include "constants.h"
#include "vex.h"
#include "controller.hpp"

class Movement {
    private:
    Controller internalController;
    float convertRangeToNewRange(int currentMaxMin, int newMaxMin, int val) {
        return ((float)val) * ((float)newMaxMin/(float)currentMaxMin);
    }
    public:
        Base* robotBase;
        Movement(Motor_Group leftMotors, Motor_Group rightMotors) {
            this->robotBase = new Base(leftMotors, rightMotors);
        }
        Movement(Base* robotBase) {
            this->robotBase = robotBase;
        }

        void driveSplitArcade(Controller controller = vex::controller(vex::controllerType::primary)) {
            // using val for slightly more accuracy
            float leftJoystickVertical = convertRangeToNewRange(127, 100, controller.Axis3.value());
            float rightJoystickHorizontal = convertRangeToNewRange(127, 100, controller.Axis1.value());
            // not running motors at full power.
            leftJoystickVertical *= splitArcadeForwardMult;
            rightJoystickHorizontal *= splitArcadeTurningMult;

            // TODO: double check other vex code to make sure this is correct
            int leftControl = (int)(leftJoystickVertical + rightJoystickHorizontal);
            int rightControl = (int)(leftJoystickVertical - rightJoystickHorizontal);
            
            this->robotBase->moveLeftMotors(leftControl);
            this->robotBase->moveRightMotors(rightControl);
        }
        // who prefers this???
        void driveSplitTank(vex::controller controller = vex::controller(vex::controllerType::primary)) {
            float leftJoystickVertical = convertRangeToNewRange(127, 100, controller.Axis3.value());
            float rightJoystickVertical = convertRangeToNewRange(127, 100, controller.Axis2.value());

            leftJoystickVertical *= splitTankLeftMult;
            rightJoystickVertical *= splitTankRightMult;

            this->robotBase->moveLeftMotors(leftJoystickVertical);
            this->robotBase->moveRightMotors(rightJoystickVertical);
        }
};

#endif
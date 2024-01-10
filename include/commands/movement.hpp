#ifndef MOVEMENT_HPP
#define MOVEMENT_HPP

#include "base.hpp"
#include "motorgroup.hpp"
#include "constants.h"
#include "vex.h"

class Movement {
    private:
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

        void driveSplitArcade(vex::controller controller = vex::controller(vex::controllerType::primary)) {
            // using val for slightly more accuracy
            float leftJoystickVertical = convertRangeToNewRange(127, 100, controller.Axis3.value());
            float rightJoystickHorizontal = convertRangeToNewRange(127, 100, controller.Axis1.value());
            // not running motors at full power.
            leftJoystickVertical *= splitArcadeForwardMult;
            rightJoystickHorizontal *= splitArcadeTurningMult;

            int leftControl = (int)(leftJoystickVertical + rightJoystickHorizontal);
            int rightControl = (int)(leftJoystickVertical - rightJoystickHorizontal);
            
            this->robotBase->moveLeftMotors(leftControl);
            this->robotBase->moveRightMotors(rightControl);
        }
        void driveSplitTank(vex::controller controller = vex::controller(vex::controllerType::primary)) {

        }
};

#endif
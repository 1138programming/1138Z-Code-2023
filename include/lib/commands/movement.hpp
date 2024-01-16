#ifndef MOVEMENT_HPP
#define MOVEMENT_HPP

#include "base.hpp"
#include "motorgroup.hpp"
#include "constants.h"
#include "vex.h"
#include "controller.hpp"

class Movement {
    private:
    float convertRangeToNewRange(int currentMaxMin, int newMaxMin, int val) {
        return ((float)val) * ((float)newMaxMin/(float)currentMaxMin);
    }
    public:
        Base* robotBase;
        Movement(MotorGroup leftMotors, MotorGroup rightMotors) {
            this->robotBase = new Base(leftMotors, rightMotors);
        }
        Movement(Base* robotBase) {
            this->robotBase = robotBase;
        }

        void driveSplitArcade(Controller controller = Controller(vex::controllerType::primary)) {
            // using val for slightly more accuracy
            float leftJoystickVertical = convertRangeToNewRange(127, 100, controller.getAxis(AXIS_3));
            float rightJoystickHorizontal = convertRangeToNewRange(127, 100, controller.getAxis(AXIS_1));
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
        void driveSplitTank(Controller controller = Controller(vex::controllerType::primary)) {
            float leftJoystickVertical = convertRangeToNewRange(127, 100, controller.getAxis(AXIS_3));
            float rightJoystickVertical = convertRangeToNewRange(127, 100, controller.getAxis(AXIS_2));

            leftJoystickVertical *= splitTankLeftMult;
            rightJoystickVertical *= splitTankRightMult;

            this->robotBase->moveLeftMotors(leftJoystickVertical);
            this->robotBase->moveRightMotors(rightJoystickVertical);
        }
};

#endif
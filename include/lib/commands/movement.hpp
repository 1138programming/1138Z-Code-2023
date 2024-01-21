#ifndef MOVEMENT_HPP
#define MOVEMENT_HPP

#include "vex.h"
#include "lib/bot/base.hpp"
#include "lib/resources/motorgroup.hpp"
#include "impl/constants.h"
#include "lib/resources/controller.hpp"

class Movement {
    private:
        bool reversed;
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
        Movement(MotorGroup leftMotors, MotorGroup rightMotors, bool reversed) {
            this->robotBase = new Base(leftMotors, rightMotors);
            this->reversed = reversed;
        }
        Movement(Base* robotBase, bool reversed) {
            this->robotBase = robotBase;
            this->reversed = reversed;
        }

        void turn(double turnVal) {
            this->robotBase->moveLeftMotors(-turnVal);
            this->robotBase->moveRightMotors(turnVal);
        }
        void driveSplitArcade(Controller* controller) {
            // using val for slightly more accuracy
            float leftJoystickVertical = convertRangeToNewRange(127, 100, controller->getAxis(AXIS_3));
            float rightJoystickHorizontal = convertRangeToNewRange(127, 100, controller->getAxis(AXIS_1));
            // not running motors at full power.
            leftJoystickVertical *= KSplitArcadeForwardMult;
            rightJoystickHorizontal *= KSplitArcadeTurningMult;
            if (this->reversed) {
                leftJoystickVertical *= -1;
            }

            // TODO: double check other vex code to make sure this is correct
            int leftControl = (int)(leftJoystickVertical + rightJoystickHorizontal);
            int rightControl = (int)(leftJoystickVertical - rightJoystickHorizontal);
            
            this->robotBase->moveLeftMotors(leftControl);
            this->robotBase->moveRightMotors(rightControl);
        }
        // who prefers this???
        void driveSplitTank(Controller* controller) {
            float leftJoystickVertical = convertRangeToNewRange(127, 100, controller->getAxis(AXIS_3));
            float rightJoystickVertical = convertRangeToNewRange(127, 100, controller->getAxis(AXIS_2));

            leftJoystickVertical *= KSplitTankLeftMult;
            rightJoystickVertical *= KSplitTankRightMult;

            this->robotBase->moveLeftMotors(leftJoystickVertical);
            this->robotBase->moveRightMotors(rightJoystickVertical);
        }
};

#endif
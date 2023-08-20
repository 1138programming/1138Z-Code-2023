#ifndef BASE_HPP
#define BASE_HPP

#include "vex.h"
#include "constants.hpp"
//#include "MYPID.h"
//#include "constants.h"

/*
1800 ticks/rev with 36:1 gears
900 ticks/rev with 18:1 gears
300 ticks/rev with 6:1 gears
*/
#define MOTOR_TICKS_PER_ROTATION 300 // check to make sure this is right on v5 pro

class Base {
    vex::motor_group* leftMotors;
    vex::motor_group* rightMotors;
    // ADD PIDs
    float wheelDiam;
    public:
        Base(vex::motor_group* leftMotors, vex::motor_group* rightMotors, float wheelDiam) {
            this->leftMotors = leftMotors;
            this->rightMotors = rightMotors;

            this->wheelDiam = wheelDiam;
        }
        void moveLeftMotors(int movement) {
            if (movement > 100) {
                movement = 100;
            }
            if (movement < -100) {
                movement = -100;
            }
            /*__above = checking to make sure value is not greater than the motors can take (probably handled by lib, but want to make sure.)*/
            this->leftMotors->setVelocity(movement, vex::pct);
        }
        void moveRightMotors(int movement) {
            if (movement > 100) {
                movement = 100;
            }
            if (movement < -100) {
                movement = -100;
            }
            this->rightMotors->setVelocity(movement, vex::pct);
        }
        void driveBothSides(int movement) {
            moveLeftMotors(movement);
            moveRightMotors(movement);
        }
        // double averageArray()
        double convertTicksToRot(double ticks) {
            return ticks/MOTOR_TICKS_PER_ROTATION;
        }
        double getRightRot() {
            this->leftMotors->position(vex::rev);
        }
        double getLeftRot() {
            this->leftMotors->position(vex::rev);
        }
        void driveSplitArcade(int leftJoystickYVal, int rightJoystickXVal) {
            leftJoystickYVal = leftJoystickYVal * kTurningMovementMultiplier;
            int leftControl = (rightJoystickXVal + leftJoystickYVal); // speed + turn
            int rightControl = (rightJoystickXVal - leftJoystickYVal); // speed - turn
            // __above = getting values for controlling split arcade (no clue how it works, google it IG)__
            moveRightMotors(leftControl * kMovementSpeedMultiplier);
            moveLeftMotors(rightControl * kMovementSpeedMultiplier);
        }
        void setBrakeMode(vex::brakeType brakingMode) {
            switch (brakingMode)
            {
            case vex::brakeType::coast:
                this->leftMotors->setStopping(vex::brakeType::coast);
                break;
            case vex::brakeType::brake:
                this->leftMotors->setStopping(vex::brakeType::brake);
                break;
            case vex::brakeType::hold:
                this->leftMotors->setStopping(vex::brakeType::hold);
            default:
                break;
            }
        }

};

#endif
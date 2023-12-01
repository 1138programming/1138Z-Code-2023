#ifndef BASE_HPP
#define BASE_HPP

#include "vex.h"
#include "constants.hpp"
#include "MYPID.hpp"
#include "constants.hpp"

/*
1800 ticks/rev with 36:1 gears
900 ticks/rev with 18:1 gears
300 ticks/rev with 6:1 gears
*/
#define MOTOR_TICKS_PER_ROTATION 300 // check to make sure this is right on v5 pro

class Base {
    vex::motor* leftBackMotor;
    vex::motor* leftCenterMotor;
    vex::motor* leftFrontMotor;
    vex::motor* rightBackMotor;
    vex::motor* rightCenterMotor;
    vex::motor* rightFrontMotor;

    // vex::motor_group* leftMotors;
    // vex::motor_group* rightMotors;
    PID* leftMotorController;
    PID* rightMotorController;
    float wheelDiam;
    //, MYPID* leftMotorController, MYPID* rightMotorController, float wheelDiam
    public:
        Base(vex::motor* leftBackMotor, vex::motor* leftCenterMotor, vex::motor* leftFrontMotor, vex::motor* rightBackMotor, vex::motor* rightCenterMotor, vex::motor* rightFrontMotor) {
            this->leftBackMotor = leftBackMotor;
            this->leftCenterMotor = leftCenterMotor;
            this->leftFrontMotor = leftFrontMotor;
            this->rightBackMotor = rightBackMotor;
            this->rightCenterMotor = rightCenterMotor;
            this->rightFrontMotor = rightFrontMotor;

            // this->leftMotorController = leftMotorController;
            // this->rightMotorController = rightMotorController;
            // this->wheelDiam = wheelDiam;
        }
        void moveLeftMotors(int movement) {
            if (movement > 100) {
                movement = 100;
            }
            if (movement < -100) {
                movement = -100;
            }
            /*__above = checking to make sure value is not greater than the motors can take (probably handled by lib, but want to make sure.)*/
            this->leftBackMotor->spin(vex::forward, movement, vex::pct);
            this->leftCenterMotor->spin(vex::forward, movement, vex::pct);
            this->leftFrontMotor->spin(vex::forward, movement, vex::pct);
        }
        void moveRightMotors(int movement) {
            if (movement > 100) {
                movement = 100;
            }
            if (movement < -100) {
                movement = -100;
            }
            this->rightBackMotor->spin(vex::forward, movement, vex::pct);
            this->rightCenterMotor->spin(vex::forward, movement, vex::pct);
            this->rightFrontMotor->spin(vex::forward, movement, vex::pct);
        }
        void driveBothSides(int movement) {
            moveLeftMotors(movement);
            moveRightMotors(movement);
        }
        void stop() {
            moveLeftMotors(0);
            moveRightMotors(0);
        }
        double convertTicksToRot(double ticks) {
            return ticks/MOTOR_TICKS_PER_ROTATION;
        }
        double getAverageRightRot() {
            return (this->rightBackMotor->position(vex::rev) + this->rightCenterMotor->position(vex::rev) + this->rightFrontMotor->position(vex::rev))/3;
        }
        double getAverageLeftRot() {
            return (this->leftBackMotor->position(vex::rev) + this->leftCenterMotor->position(vex::rev) + this->leftFrontMotor->position(vex::rev))/3;
        }
        double getAverageRotationBothSides() {
            return (getAverageLeftRot() + getAverageRightRot())/2;
        }
        void resetMotorEncoders() {
            this->leftBackMotor->resetPosition();
            this->leftCenterMotor->resetPosition();
            this->leftFrontMotor->resetPosition();
            this->rightBackMotor->resetPosition();
            this->rightCenterMotor->resetPosition();
            this->rightFrontMotor->resetPosition();
        }
        void driveSplitArcade(int leftJoystickYVal, int rightJoystickXVal) {
            //89
            leftJoystickYVal = -(int)(((float)leftJoystickYVal) * kMovementSpeedMultiplier);
            rightJoystickXVal = -(int)(((float)rightJoystickXVal) * kTurningMovementMultiplier);

            int leftControl = (int)(leftJoystickYVal + rightJoystickXVal); // speed - turn
            int rightControl = (int)(leftJoystickYVal - rightJoystickXVal); // speed + turn
            // __above = getting values for controlling split arcade (no clue how it works, google it IG)__
            moveRightMotors(rightControl);
            moveLeftMotors(leftControl);
        }
        void turn(int movement) {
            moveLeftMotors(-movement);
            moveRightMotors(movement);
        }
        bool motorsMoving() {
            return this->leftBackMotor->isSpinning() || this->leftFrontMotor->isSpinning();
        }
        // void setBrakeMode(vex::brakeType brakingMode) {
        //     switch (brakingMode)
        //     {
        //     case vex::brakeType::coast:
        //         this->leftMotors->setStopping(vex::brakeType::coast);
        //         break;
        //     case vex::brakeType::brake:
        //         this->leftMotors->setStopping(vex::brakeType::brake);
        //         break;
        //     case vex::brakeType::hold:
        //         this->leftMotors->setStopping(vex::brakeType::hold);
        //     default:
        //         break;
        //     }
        // }

};

#endif
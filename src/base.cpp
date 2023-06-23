#include "main.h"

class Base {
    pros::Motor* backLeftMotor;
    pros::Motor* middleLeftMotor;
    pros::Motor* frontLeftMotor;
    pros::Motor* backRightMotor;
    pros::Motor* middleRightMotor;
    pros::Motor* frontRightMotor;
    pros::Controller* controller;
    public:
        void setController(pros::Controller* controller) {
            this->controller = controller;
        }
        Base(int backLeftPort, int middleLeftPort, int frontLeftPort, int backRightPort, int middleRightPort, int frontRightPort) {
            this->backLeftMotor = new pros::Motor(backLeftPort);
            this->middleLeftMotor = new pros::Motor(middleLeftPort);
            this->frontLeftMotor = new pros::Motor(frontLeftPort);

            this->backRightMotor = new pros::Motor(backRightPort);
            this->middleRightMotor = new pros::Motor(middleRightPort);
            this->middleRightMotor = new pros::Motor(frontRightPort);
        }

        void moveLeftMotors(int movement) {
            if (movement > 127) {
                movement = 127;
            }
            if (movement < -127) {
                movement = -127;
            }
            (*backLeftMotor).move(movement);
            (*middleLeftMotor).move(movement);
            (*frontLeftMotor).move(movement);
        }
        void moveRightMotors(int movement) {
            if (movement > 127) {
                movement = 127;
            }
            if (movement < -127) {
                movement = -127;
            }
            (*backRightMotor).move(movement);
            (*middleRightMotor).move(movement);
            (*frontRightMotor).move(movement);
        }
        void driveSplitArcade(int leftJoystickYVal, int rightJoystickXVal) {
            int leftControl = (leftJoystickYVal + rightJoystickXVal); //speed + turn
            int rightControl = (leftJoystickYVal - rightJoystickXVal); // speed - turn

            moveLeftMotors(leftControl);
            moveRightMotors(rightControl);
        }
        void setBrakeMode(int motorMode) {
            //refer to https://pros.cs.purdue.edu/v5/api/c/motors.html#motor-brake-mode-e-t
            switch(motorMode) {
                case 0: //coast - motor coasts when stopped
                    (*backLeftMotor).set_brake_mode(MOTOR_BRAKE_COAST);
                    (*middleLeftMotor).set_brake_mode(MOTOR_BRAKE_COAST);
                    (*frontLeftMotor).set_brake_mode(MOTOR_BRAKE_COAST);
                    
                    (*backRightMotor).set_brake_mode(MOTOR_BRAKE_COAST);
                    (*middleRightMotor).set_brake_mode(MOTOR_BRAKE_COAST);
                    (*frontRightMotor).set_brake_mode(MOTOR_BRAKE_COAST);
                break;
                case 1: //brake - motor breaks when stopped (passive holding pos)
                    (*backLeftMotor).set_brake_mode(MOTOR_BRAKE_BRAKE);
                    (*middleLeftMotor).set_brake_mode(MOTOR_BRAKE_BRAKE);
                    (*frontLeftMotor).set_brake_mode(MOTOR_BRAKE_BRAKE);
                    
                    (*backRightMotor).set_brake_mode(MOTOR_BRAKE_BRAKE);
                    (*middleRightMotor).set_brake_mode(MOTOR_BRAKE_BRAKE);
                    (*frontRightMotor).set_brake_mode(MOTOR_BRAKE_BRAKE);
                break;
                case 2: //hold - motor actively holds position when stopped
                    (*backLeftMotor).set_brake_mode(MOTOR_BRAKE_HOLD);
                    (*middleLeftMotor).set_brake_mode(MOTOR_BRAKE_HOLD);
                    (*frontLeftMotor).set_brake_mode(MOTOR_BRAKE_HOLD);
                    
                    (*backRightMotor).set_brake_mode(MOTOR_BRAKE_HOLD);
                    (*middleRightMotor).set_brake_mode(MOTOR_BRAKE_HOLD);
                    (*frontRightMotor).set_brake_mode(MOTOR_BRAKE_HOLD);
                break;
                case INT32_MAX: //invalid, will not change motors
                break;
                default: //will also not change motors
                break;
            }
        }
};
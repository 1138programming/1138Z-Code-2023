#include "main.h"
#include "PID.cpp"
using namespace pros;

#define MOTOR_TICKS_PER_ROTATION 300

class Base {
    Motor_Group* leftMotors;
    Motor_Group* rightMotors;
    PID* leftMotorController;
    PID* rightMotorController;
    public:
        Base(Motor_Group* leftMotors, Motor_Group* rightMotors) {
            this->leftMotors = leftMotors;
            this->rightMotors = rightMotors;
        }
        Base(Motor_Group* leftMotors, Motor_Group* rightMotors, PID* leftMotorController, PID* rightMotorController) {
            this->leftMotors = leftMotors;
            this->rightMotors = rightMotors;
            this-> leftMotorController = leftMotorController;
            this-> rightMotorController = rightMotorController;
        }
        // Base(int backLeftPort, int middleLeftPort, int frontLeftPort, int backRightPort, int middleRightPort, int frontRightPort) {
        //     this->backLeftPort = backLeftPort;
        //     this->middleLeftPort = middleLeftPort;
        //     this->frontLeftPort = frontLeftPort;

        //     this->backRightPort = backRightPort;
        //     this->middleRightPort = middleRightPort;
        //     this->frontRightPort = frontRightPort;
        // }
        int analogToRPM(int analog) {
            return (int)(analog*4.73);
        }
        void moveLeftMotors(int movement) {     
            movement = analogToRPM(movement);    
            if (movement > 600) {
                movement = 600;
            }
            if (movement < -600) {
                movement = -600;
            }
            (*leftMotors).move(movement);
        }
        void moveRightMotors(int movement) {
            movement = analogToRPM(movement);
            if (movement > 600) {
                movement = 600;
            }
            if (movement < -600) {
                movement = -600;
            }
            (*rightMotors).move(movement);
        }
        void driveSplitArcade(int leftJoystickYVal, int rightJoystickXVal) {
            int leftControl = -(leftJoystickYVal + rightJoystickXVal); //speed + turn
            int rightControl = -(leftJoystickYVal - rightJoystickXVal); // speed - turn

            moveLeftMotors(leftControl);
            moveRightMotors(rightControl);
        }
        double averageArray(vector<double> arr) {
            int total = 0;
            // I iterates through the elements in the vector, and the dereferenced value is added to the running total.
            for (std::vector<double>::iterator i = arr.begin(); i < arr.end(); i++) {
                total+=*i;
            }
            return total/*/size*/;
        }
        double convertTicksToRot(double ticks) {
            return ticks/MOTOR_TICKS_PER_ROTATION;
        }
        double getRightRot() {
            return convertTicksToRot(averageArray(this->leftMotors->get_positions()));
        }
        double getLeftRot() {
            return convertTicksToRot(averageArray(this->rightMotors->get_positions()));
        }
};
        // void setBrakeMode(int motorMode) {
        //     //refer to https://pros.cs.purdue.edu/v5/api/c/motors.html#motor-brake-mode-e-t
        //     switch(motorMode) {
        //         case 0: //coast - motor coasts when stopped
        //             (*backLeftMotor).set_brake_mode(MOTOR_BRAKE_COAST);
        //             (*middleLeftMotor).set_brake_mode(MOTOR_BRAKE_COAST);
        //             (*frontLeftMotor).set_brake_mode(MOTOR_BRAKE_COAST);
                    
        //             (*backRightMotor).set_brake_mode(MOTOR_BRAKE_COAST);
        //             (*middleRightMotor).set_brake_mode(MOTOR_BRAKE_COAST);
        //             (*frontRightMotor).set_brake_mode(MOTOR_BRAKE_COAST);
        //         break;
        //         case 1: //brake - motor breaks when stopped (passive holding pos)
        //             (*backLeftMotor).set_brake_mode(MOTOR_BRAKE_BRAKE);
        //             (*middleLeftMotor).set_brake_mode(MOTOR_BRAKE_BRAKE);
        //             (*frontLeftMotor).set_brake_mode(MOTOR_BRAKE_BRAKE);
                    
        //             (*backRightMotor).set_brake_mode(MOTOR_BRAKE_BRAKE);
        //             (*middleRightMotor).set_brake_mode(MOTOR_BRAKE_BRAKE);
        //             (*frontRightMotor).set_brake_mode(MOTOR_BRAKE_BRAKE);
        //         break;
        //         case 2: //hold - motor actively holds position when stopped
        //             (*backLeftMotor).set_brake_mode(MOTOR_BRAKE_HOLD);
        //             (*middleLeftMotor).set_brake_mode(MOTOR_BRAKE_HOLD);
        //             (*frontLeftMotor).set_brake_mode(MOTOR_BRAKE_HOLD);
                    
        //             (*backRightMotor).set_brake_mode(MOTOR_BRAKE_HOLD);
        //             (*middleRightMotor).set_brake_mode(MOTOR_BRAKE_HOLD);
        //             (*frontRightMotor).set_brake_mode(MOTOR_BRAKE_HOLD);
        //         break;
        //         case INT32_MAX: //invalid, will not change motors
        //         break;
        //         default: //will also not change motors
        //         break;
        //     }
        // }
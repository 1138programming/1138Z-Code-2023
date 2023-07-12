#ifndef BASE_H
#define BASE_H

#include "main.h"
#include "MYPID.h"

#define MOTOR_TICKS_PER_ROTATION 300

using namespace pros;

class Base {
    Motor_Group* leftMotors;
    Motor_Group* rightMotors;
    MYPID* leftMotorController;
    MYPID* rightMotorController;
    float wheelDiam;
    public:
        Base(Motor_Group* leftMotors, Motor_Group* rightMotors, MYPID* leftMotorController, MYPID* rightMotorController, float wheelDiam) {
            this->leftMotors = leftMotors;
            this->rightMotors = rightMotors;
            this-> leftMotorController = leftMotorController;
            this-> rightMotorController = rightMotorController;
            this->wheelDiam = wheelDiam;
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
        double averageArray(vector<double> arr) {
            int total = 0;
            // "i" iterates through the elements in the vector, and the dereferenced value is added to the running total.
            for (std::vector<double>::iterator i = arr.begin(); i < arr.end(); i++) {
                total+=*i;
            }
            return total/arr.size();/*/size*/
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
        void driveSplitArcade(int leftJoystickYVal, int rightJoystickXVal) {
            int leftControl = -(leftJoystickYVal + rightJoystickXVal); //speed + turn
            int rightControl = -(leftJoystickYVal - rightJoystickXVal); // speed - turn
            // this->leftMotorController->setSetpoint(leftControl);
            // this->rightMotorController->setSetpoint(rightControl);

            // moveLeftMotors(this->leftMotorController->calculate(averageArray(this->leftMotors->get_actual_velocities())));
            // moveRightMotors(this->rightMotorController->calculate(averageArray(this->rightMotors->get_actual_velocities())));

            moveLeftMotors((int)leftControl * 0.8);
            moveRightMotors((int)rightControl * 0.8);
        }
        void setBrakeMode(pros::motor_brake_mode_e motorMode) {
            //refer to https://pros.cs.purdue.edu/v5/api/c/motors.html#motor-brake-mode-e-t
            E_MOTOR_BRAKE_BRAKE;
            switch(motorMode) {
                case MOTOR_BRAKE_COAST: //coast - motor coasts when stopped
                    this->leftMotors->set_brake_modes(MOTOR_BRAKE_COAST);
                    
                    this->rightMotors->set_brake_modes(MOTOR_BRAKE_COAST);
                break;
                case MOTOR_BRAKE_BRAKE: //brake - motor breaks when stopped (passive holding pos)
                    this->leftMotors->set_brake_modes(MOTOR_BRAKE_BRAKE);

                    this->rightMotors->set_brake_modes(MOTOR_BRAKE_BRAKE);
                break;
                case MOTOR_BRAKE_HOLD: //hold - motor actively holds position when stopped
                    this->leftMotors->set_brake_modes(MOTOR_BRAKE_HOLD);

                    this->rightMotors->set_brake_modes(MOTOR_BRAKE_HOLD);
                break;
                case INT32_MAX: //invalid, will not change motors
                break;
                default: //will also not change motors
                break;
            }
        }
};

#endif
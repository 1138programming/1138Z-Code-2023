#ifndef BASE_HPP
#define BASE_HPP

#include "motorgroup.hpp"
#include "vex.h"

class Base {
    private:
        Motor_Group left;
        Motor_Group right;
    public:
        // ___ Constructor ___
        /**
         * @brief Creates new base and sets motors to brake (trust)
        */
        Base(Motor_Group leftSide, Motor_Group rightSide) {
            this->left = leftSide;
            this->right = rightSide;
            this->left.setBrakeMode(vex::brakeType::brake);
            this->right.setBrakeMode(vex::brakeType::brake);
        }
        // ___ Useful Functions ___
        void driveBothSides(int movement) {
            this->left.move(movement);
            this->right.move(movement);
        }
        void moveLeftMotors(int movement) {
            this->left.move(movement);
        }
        void moveRightMotors(int movement) {
            this->right.move(movement);
        }
        void stop() {
            this->left.stop();
            this->right.stop();
        }

        void resetAllEncoders() {
            this->left.resetEncoders();
            this->right.resetEncoders();
        }
        double getAverageRotationBothSides() {
            return (this->left->averageRot() + this->right->averageRot())/2.0;
        }
        
};

#endif
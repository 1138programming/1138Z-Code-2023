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
        Base(Motor_Group leftSide, Motor_Group rightSide) {
            this->left = leftSide;
            this->right = rightSide;
        }
        // ___ Useful Functions ___
        void driveBothSides(int movement) {
            this->left.move(movement);
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
        
};

#endif
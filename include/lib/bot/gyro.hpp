#ifndef GYRO_HPP
#define GYRO_HPP

#include "vex.h"

class Gyro {
    vex::inertial* gyro;
    public:
        Gyro(vex::inertial* gyro) {
            this->gyro = gyro;
        }
        /**
         * @brief Need to make sure you are not attempting to use gyro while still resetting 
         * (use isResetFinished) command
        */
        void resetGyro() {
            this->gyro->calibrate();
        }
        bool isResetFinished() {
            return (!this->gyro->isCalibrating());
        }
        void resetGyroWithWait() {
            this->gyro->calibrate();
            while (!isResetFinished()) {
                vex::wait(10, vex::msec);
            }
        }

        /**
         * @brief gets the rotation of the current sensor (value from -infinity -> infinity)
         */
        double getRot() {
            return this->gyro->rotation();
        }
        /**
         * @brief gets the rotation of the current sensor locked to 360deg (value from 0.0 -> 360.0)
        */
        double getHeading() {
            return this->gyro->heading();
        }
};

#endif
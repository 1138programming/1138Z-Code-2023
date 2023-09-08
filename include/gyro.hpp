#ifndef GYRO_HPP
#define GYRO_HPP

#include "vex.h"

class Gyro {
    vex::inertial* gyro;
    public:
        Gyro(vex::inertial* gyro) {
            this->gyro = gyro;
        }
        void reset() {
            this->gyro->resetHeading();
            this->gyro->resetRotation();
        }
        double getHeading() {
            return this->gyro->heading();
        }
        double getRot() {
            return this->gyro->angle();
        }
        void resetGyro() {
            this->gyro->startCalibration(0);
            while (this->gyro->isCalibrating()) {
                vex::wait(10,vex::msec);
            }
        }
};

#endif
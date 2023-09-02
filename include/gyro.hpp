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
};

#endif
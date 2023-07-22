#ifndef GYRO_HPP
#define GYRO_HPP

#include "main.h"

class Gyro {
    pros::IMU gyro;
    public:
        Gyro(int gyroPort) {
            this->gyro = pros::IMU(gyroPort);
        }
        void reset() {
            this->gyro.reset();
        }
};

#endif
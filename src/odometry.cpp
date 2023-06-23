#include "main.h"

class Odometry {
    int gyroPort = 0;
    float wheelDiameter = 0.0;

    Odometry(int gyroPort) {
        this->gyroPort = gyroPort;
    }
};
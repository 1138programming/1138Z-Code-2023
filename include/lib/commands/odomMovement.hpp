#ifndef ODOMMOVEMENT_HPP
#define ODOMMOVEMENT_HPP

#include "odometry.hpp"
#include "movement.hpp"

class OdomMovement {
    private:
        Odometry* odom;
        Movement* robotMovement;
        Gyro* gyro;
    public:
        OdomMovement(Odometry* odom, Movement* robotMovement, Gyro* gyro) {
            this->odom = odom;
            this->robotMovement = robotMovement;
            this->gyro = gyro;
        }

        void turnToPosPID(double targetPos, double allowedError) {
            double actualTarget = this->gyro->getRot();
        }
};

#endif
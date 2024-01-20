#ifndef ODOMMOVEMENT_HPP
#define ODOMMOVEMENT_HPP

#include "odometry.hpp"
#include "movement.hpp"

class OdomMovement {
    private:
        Odometry* odom;
        Movement* robotMovement;
        Gyro* gyro;

        PID* odomTurningPID;
        PID* odomMovementPID;

        double convertNumToDeg(double num) {
            return fmod(num, 360.0);
        }
    public:
        OdomMovement(Odometry* odom, Movement* robotMovement, Gyro* gyro, PID* odomMovementPID, PID* odomTurningPID) {
            this->odom = odom;
            this->robotMovement = robotMovement;
            this->gyro = gyro;

            this->odomMovementPID = odomMovementPID;
            this->odomTurningPID = odomTurningPID;
        }

        void turnToPosPID(double targetPos, double allowedError) {
            // make 0s
            double actualTarget = this->gyro->getRot() + targetPos;
            actualTarget = convertNumToDeg(actualTarget);

            this->odomTurningPID->setAllowedError(allowedError);

            while(this->odomTurningPID->isPidFinished() == false) {
                this->odom->pollAndUpdateOdom();
                double PIDVal = this->odomTurningPID->calculate(this->gyro->getHeading());
                // wait for bot to move
                vex::wait(5, vex::msec);
            }
        }
};

#endif
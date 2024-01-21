#ifndef ODOMMOVEMENT_HPP
#define ODOMMOVEMENT_HPP

#include "lib/resources/odometry.hpp"
#include "movement.hpp"

class OdomMovement {
    private:
        Odometry* odom;
        Movement* robotMovement;
        Gyro* gyro;

        PID* odomTurningPID;
        PID* odomMovementPID;

        double inchesMult = 1.0;

        double convertNumToDeg(double num) {
            return fmod(num, 360.0);
        }

        double getDistBetweenDeg(double botDeg, double targetDeg) {
            // quite unreadable, but: https://stackoverflow.com/questions/9505862/shortest-distance-between-two-degree-marks-on-a-circle
            return ((botDeg - targetDeg) > 180 ? -360 + (botDeg - targetDeg) : (botDeg - targetDeg));
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
            this->odomTurningPID->setSetpoint(0.0);
            this->odomTurningPID->setAllowedError(allowedError);

            while(this->odomTurningPID->isPidFinished() == false) {
                this->odom->pollAndUpdateOdom();
                double PIDVal = this->odomTurningPID->calculate(getDistBetweenDeg(this->gyro->getHeading(), targetPos));
                this->robotMovement->turn(PIDVal);
                // wait for bot to move
                vex::wait(5, vex::msec);
            }
        }
        void moveInInchesOdomPID(double inches) {
            bool rev = false;
            if (inches < 0) {
                rev = true;
            }
            inches *= this->inchesMult;
            double initialGyroHeader = this->gyro->getHeading();

            double xMult = this->odom->xMult(initialGyroHeader);
            double yMult = this->odom->xMult(initialGyroHeader);

            double posToMoveToX = (this->odom->getX() + (inches * xMult));
            double posToMoveToY = (this->odom->getY() + (inches * yMult));

            double initialPosX = this->odom->getX();
            double initialPosY = this->odom->getY();

            double initialDisplacement = this->odom->pythagoreanThrmBetweenTwoPoints((Vector2){initialPosX, initialPosY}, (Vector2){posToMoveToX, posToMoveToY});
            double movement = 20;

            this->odomMovementPID->setSetpoint(0.0);
            if (inches < 0) {
                this->robotMovement->robotBase->driveBothSides(movement);
            }
            else {
                this->robotMovement->robotBase->driveBothSides(-movement);
            }
            do {
                vex::wait(5, vex::msec);
                this->odom->pollAndUpdateOdom();
                double difference = (this->odom->pythagoreanThrmBetweenTwoPoints((Vector2) {this->odom->getX(), this->odom->getY()}, (Vector2) {initialPosX, initialPosY}));
                movement = this->odomMovementPID->calculate(inches - difference);
                if (rev) {
                    this->robotMovement->robotBase->driveBothSides((int)-movement);
                }
                else {
                    this->robotMovement->robotBase->driveBothSides((int)movement);
                }
            }
            while (this->odomMovementPID->isPidFinished() == false);
        }
};

#endif
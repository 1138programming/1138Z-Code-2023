#ifndef ODOMETRY_HPP
#define ODOMETRY_HPP

#include "vector2.hpp"
#include "gyro.hpp"
#include "base.hpp"
#include "PID.hpp"

#define PI 3.14159265358979343846

class Odometry {
    private:
        Gyro* gyro;
        Base* robotBase;

        Vector2 pos;
        float wheelDiam;
        float gearRatio;

        PID* odomTurningPID;
        PID* odomMovementPID;

        double lastOdomPos;

        double getActualPosFromWheelRot(double rot) {
            return rot * this->wheelDiam * this->gearRatio;
        }

        double convertDegToRad(double degrees) {
            return degrees * (PI/180.0);
        }
        double convertRadToDeg(double rad) {
            return rad * (180.0/PI);
        }

        double pythagoreanThrmBetweenTwoPoints(Vector2 pos1, Vector2 pos2) {
            double xChange = (pos1.x - pos2.x);
            double yChange = (pos1.y - pos2.y);

            double cSquared = (xChange * xChange) + (yChange * yChange);
            return sqrt(cSquared);
        }

        double xMult(double deg) {
            return cos(this->convertDegToRad(deg));
        }
        double yMult(double deg) {
            return sin(this->convertDegToRad(deg));
        }
    public:
        Odometry(float wheelDiameter, Base* robotBase, Gyro* gyro, PID* odomMovementPID, PID* odomTurningPID) {
            this->robotBase = robotBase;
            this->wheelDiam = wheelDiameter;
            this->gyro = gyro;

            this->odomMovementPID = odomMovementPID;
            this->odomTurningPID = odomTurningPID;
        }

        //getters
            double getX() {
                return this->pos.x;
            }
            double getY() {
                return this->pos.y;
            }
            Vector2 getPos() {
                return this->pos;
            }

        //setters
            void setX(double x) {
                this->pos.x = x;
            }
            void setY(double y) {
                this->pos.y = y;
            }
            void setPos(Vector2 pos) {
                this->pos = pos;
            }

        //useful funcs.
        void pollAndUpdateOdom() {
            // find averaged movement + convert to inches
            double averagedMovementDistance = this->robotBase->getAverageRotationBothSides() - this->lastOdomPos;
            averagedMovementDistance = getActualPosFromWheelRot(averagedMovementDistance);

            // get heading + calculate values (in inches) from that
            double gyroHeading = this->gyro->getHeading();

            double xChange = this->xMult(gyroHeading);
            xChange *= averagedMovementDistance;

            double yChange = this->yMult(gyroHeading);
            yChange *= averagedMovementDistance;

            //--h+-+ello my name is noah bronsion
            // set last pos to use in next update
            this->lastOdomPos = this->robotBase->getAverageRotationBothSides();
        }
};

#endif
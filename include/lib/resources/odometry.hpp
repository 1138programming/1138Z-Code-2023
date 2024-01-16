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
        PID odomMovementPID;

        double getActualPosFromWheelRot(double rot) {
            return rot * this->wheelDiam * this->gearRatio;
        }
    public:
        Odometry(float wheelDiameter, Base* robotBase, Gyro* gyro) {
            this->robotBase = robotBase;
            this->wheelDiam = wheelDiameter;
            this->gyro = gyro;
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
            double averagedMovementDistance = this->robotBase->getAverageRotationBothSides();
        }
};

#endif
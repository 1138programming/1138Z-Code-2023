#ifndef ODOMETRY_HPP
#define ODOMETRY_HPP

#include "vex.h"
#include "gyro.hpp"
#include "base.hpp"

#define PI 3.14159265358979323846

class Odometry {
    int gyroPort = 0;
    float wheelDiameter = 0.0;
    float gearRatio = 1.0;
    Base* robotBase;
    Gyro* gyro;
    //const Base* == the base is const; Base* const == the pointer is const; const Base* const == both.
    // the odometry class should NEVER change Base, but we can't garuentee that, as we have to access the functions in base. BE CAREFUL!
    private:
        double absD(double num) {
            return num < 0;
        }
        double convertDegToRad(double degrees) {
            return degrees * (PI/180);
        }
        double convertRadToDeg(double radians) {
            return radians * (180/PI);
        }
        bool doubleIsWithinMarginOfError(double num, double comparison, double marginOfError) {
            // if (num > comparison - marginOfError && num < comparison + marginOfError) {
            //     return true;
            // }
            // return false;
            return true;
        }
    public:
        Odometry(int gyroPort, float wheelDiameter, Base* robotBase, Gyro* gyro) {
            this->gyroPort = gyroPort;
            this->robotBase = robotBase;
            this->wheelDiameter = wheelDiameter;
            this->gyro = gyro;
        }
        Odometry(int gyroPort, float wheelDiameter, float gearRatio, Base* robotBase, Gyro* gyro) {
            this->gyroPort = gyroPort;
            this->robotBase = robotBase;
            this->wheelDiameter = wheelDiameter;
            this->gearRatio = gearRatio;
            this->gyro = gyro;
        }
        double getXPosMultFromDegrees(double gyroDegrees) {
            double degreesNormalized = absD(fmod(gyroDegrees, 360));
            if (degreesNormalized < 0) {
                degreesNormalized = 360 + degreesNormalized; // Convert the number to positive degrees so that -1 is actually equal to 359 (considering we're using cos now, this is probably an unnessacary step.)
            }
            // cos() takes a value in radians, so we have to convert to and from them.
            return convertRadToDeg(cos(convertDegToRad(degreesNormalized)));
        }
        double getYPosMultFromDeg(double gyroDegrees) {
            double degreesNormalized = absD(fmod(gyroDegrees,360)); // fmod = % operator
            if (degreesNormalized < 0) {
                degreesNormalized = 360 + degreesNormalized; // again, probably unnessacary but idc
            }
            return convertRadToDeg(sin(convertDegToRad(degreesNormalized)));
        }
        double getActualPosFromRot(double rot) {
            return rot * this->wheelDiameter * this->gearRatio;
        }
        void moveForwardToPosInInches(double pos, int speed) {
            float totalAverageRotationInches = getActualPosFromRot(this->robotBase->getAverageRightRot());
            float startRot = totalAverageRotationInches;

            while (totalAverageRotationInches - startRot != pos) {
                this->robotBase->driveBothSides(speed);
                vex::wait(10,vex::msec);
                totalAverageRotationInches = getActualPosFromRot(this->robotBase->getAverageRightRot());
            }
            this->robotBase->driveBothSides(0);
        }
        void turnToPos(double targetPosition) {
            this->gyro->resetGyro();
            double initialGyroPos = this->gyro->getHeading();
            while (!(this->doubleIsWithinMarginOfError(this->gyro->getHeading(),targetPosition,100))) {
                if (initialGyroPos > targetPosition) {
                    this->robotBase->turn(1);
                }
                else {
                    this->robotBase->turn(-1);
                }
            }
        }
};

#endif
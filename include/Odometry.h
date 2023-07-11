#ifndef ODOMETRY_H
#define ODOMETRY_H

#include "main.h"
#include "Base.h"

#define PI 3.14159265358979323846

class Odometry
{
    int gyroPort = 0;
    float wheelDiameter = 0.0;
    const Base* robotBase;
    //const Base* == the base is const; Base* const == the pointer is const; const Base* const == both.

    // the odometry class should NEVER change Base
    Odometry(int gyroPort, float wheelDiameter, const Base* robotBase)
    {
        this->gyroPort = gyroPort;
        this->wheelDiameter = wheelDiameter;
        this->robotBase = robotBase;
    }

    double absD(double num)
    {
        return num < 0 ? -num : num;
    }

    double convertDegreesToRadians(double degrees) {
        return degrees * (PI/180);
    }

    double convertRadiansToDegrees(double radians) {
        return radians * (180/PI);
    }

    double getXPosMultiplierFromDegrees(double gyroDegrees)
    {
        double degreesNormalized = absD(fmod(gyroDegrees, 360)); // apparently this is how you use the modulo operator????
        if (degreesNormalized < 0) {
            degreesNormalized = 360 + degreesNormalized; // Convert num to positive degrees (-1 is actually equal to 359 deg)
        }
        // cos() takes a value in radians, so we have to convert to and from them.
        return convertRadiansToDegrees(cos(convertDegreesToRadians(degreesNormalized)));
    }

    double getYPosMultiplierFromDegrees(double gyroDegrees)
    {
        double degreesNormalized = absD(fmod(gyroDegrees, 360)); // apparently this is how you use the modulo operator????
        if (degreesNormalized < 0) {
            degreesNormalized = 360 + degreesNormalized;
        }
        return convertRadiansToDegrees(sin(convertDegreesToRadians(degreesNormalized)));
    }
    void moveForwardToPos(double pos) {
        
    }
};
#endif
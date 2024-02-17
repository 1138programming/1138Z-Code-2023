#ifndef CONSTANTS_H
#define CONSTANTS_H

// driving
const float KSplitArcadeForwardMult = 1.0;
const float KSplitArcadeTurningMult = 0.6;

const float KSplitTankLeftMult = 1.0;
const float KSplitTankRightMult = 1.0;

// drive base
const int KBackRightMotorPort = 0;
const int KMiddleRightMotorPort = 1;
const int KFrontRightMotorPort = 2;

const int KBackLeftMotorPort = 10; // rev
const int KMiddleLeftMotorPort = 11; // rev
const int KFrontLeftMotorPort = 12; // rev

// intake
const int KIntakeMotorPort = 8;


// odom
const int KInertialSensorPort = 6;
const float KOdomWheelSize = 4.125;
#endif
#ifndef CONSTANTS_H
#define CONSTANTS_H

// driving
const float KSplitArcadeForwardMult = 0.8;
const float KSplitArcadeTurningMult = 0.9;

const float KSplitTankLeftMult = 1.0;
const float KSplitTankRightMult = 1.0;

// drive base
const int KBackRightMotorPort = 0;
const int KMiddleRightMotorPort = 1;
const int KFrontRightMotorPort = 2; // rev

const int KBackLeftMotorPort = 12; 
const int KMiddleLeftMotorPort = 13; // rev
const int KFrontLeftMotorPort = 14; // rev

// intake
const int KIntakeMotorPort = 8;


// odom
const int KInertialSensorPort = 3;
const float KOdomWheelSize = 4.125;
#endif
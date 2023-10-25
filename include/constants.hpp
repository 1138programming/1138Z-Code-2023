#ifndef Constants_HPP
#define Constants_HPP

// const int kLeftDrivebaseBackPort = 0;
// const int kLeftDrivebaseCenterPort = 0;
// const int kLeftDrivebaseFrontPort = 0;

// const int kRightDrivebaseBackPort = 0;
// const int kRightDrivebaseCenterPort = 0;
// const int kRightDrivebaseFrontPort = 0;

//Intake
const int kIntakePort = 8;
const int kIntakeSpeed = 100;



//Base
// const int kBackLeftMotorPort = 10;
// const int kCenterLeftPort = 11;
// const int kFrontLeftPort = 12;
// const int kBackRightMotorPort = 17;
// const int kCenterRightPort = 18;
// const int kFrontRightPort = 19;

const int kBackLeftMotorPort = 0;
const int kCenterLeftPort = 1;
const int kFrontLeftPort = 2;
const int kBackRightMotorPort = 10;
const int kCenterRightPort = 11;
const int kFrontRightPort = 12;

//How fast we turn vs. max speed
const float kTurningMovementMultiplier = 0.9501;
// How fast of max speed we actually move
const float kMovementSpeedMultiplier = 0.9501;

const double kRotationAllowedError = 0.001;
const double kMovementAllowedError = 0.001;

//Catapult
const int kCatapultPort = 4;

const float kCatapultSpeedMultiplier = 0.75;

//Auton
const int kDriveForwardAutonSpeed = 20;

//Odometry
const float kOdomGearRatio = 1;//36.0/60.0;
const float kWheelDiamInches = 4.125;
const float kOdomSpeedMultiplier = 0.5;

//Gyro
const int kInertialSensorPort = 10;
#endif
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

const int kBackLeftMotorPort = 2;
const int kCenterLeftPort = 1;
const int kFrontLeftPort = 0;
const int kBackRightMotorPort = 14;
const int kCenterRightPort = 13;
const int kFrontRightPort = 12;
const int kHangMotor = 0;

//How fast we turn vs. max speed
const float kTurningMovementMultiplier = 0.8001;
// How fast of max speed we actually move
const float kMovementSpeedMultiplier = 0.8001;

const double kRotationAllowedError = 0.001;
const double kMovementAllowedError = 0.001;

//Catapult
const int kCatapultPort = 9;

const float kCatapultSpeedMultiplier = 0.3750f;

//Auton
const int kDriveForwardAutonSpeed = 20;

//Odometry
const float kOdomGearRatio = 1;//36.0/60.0;
const float kWheelDiamInches = 4.125;
const float kOdomSpeedMultiplier = 0.5;

//Gyro
const int kInertialSensorPort = 3;
#endif
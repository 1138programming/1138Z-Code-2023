#ifndef Constants_HPP
#define Constants_HPP

// const int kLeftDrivebaseBackPort = 0;
// const int kLeftDrivebaseCenterPort = 0;
// const int kLeftDrivebaseFrontPort = 0;

// const int kRightDrivebaseBackPort = 0;
// const int kRightDrivebaseCenterPort = 0;
// const int kRightDrivebaseFrontPort = 0;

//Intake
const int kIntakePort = 18;
const int kIntakeSpeed = 127;

//Base
//How fast we turn vs. max speed
const float kTurningMovementMultiplier = 0;
// How fast of max speed we actually move
const float kMovementSpeedMultiplier = 0.05;

const double kRotationAllowedError = 0.001;
const double kMovementAllowedError = 0.001;


//Catapult
const int kCatapultPort = 6;
const float kCatapultSpeedMultiplier = 1;

//Auton
const int kDriveForwardAutonSpeed = 20;

//Odometry
const float kOdomGearRatio = 36.0/60.0;
const float kWheelDiamInches = 3.25;
#endif
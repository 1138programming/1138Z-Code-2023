#ifndef Constants_HPP
#define Constants_HPP

#include <functional>


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
const float kTurningMovementMultiplier = 0.9;
// How fast of max speed we actually move
const float kMovementSpeedMultiplier = 1.0;

const double kRotationAllowedError = 0.001;
const double kMovementAllowedError = 0.001;


//Catapult
const int kCatapultPort = 7;
const float kCatapultSpeedMultiplier = 1;
#endif
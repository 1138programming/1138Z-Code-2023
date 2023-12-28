#ifndef AUTON_HPP
#define AUTON_HPP

#include "vex.h"
#include "base.hpp"
#include "constants.hpp"
#include "odometry.hpp"

class Autons {
    Base* base;
    public:
        Autons(Base* base) {
            this->base = base;
        }
        void driveForwardForSpecifiedTime(float seconds) {
            float initialTime = vex::timer::system()/1000;

            // while(pros::millis()/1000 - initialTime < seconds/3) {
            //     this->base->moveLeftMotors(100);
            //     this->base->moveRightMotors(-100);
            // }

            while(vex::timer::system()/1000 - initialTime < seconds) {
                this->base->driveBothSides(kDriveForwardAutonSpeed);
                //wait, so that the scheduler has some time to do stuff
                vex::wait(10, vex::msec);
            }
            this->base->driveBothSides(0);
        }

        void driveForwardForSpecifiedTimeAndPercent(float seconds, float percent, Odometry* odom) {
            float initialTime = vex::timer::system()/1000; // we divide by 1000 to convert to seconds instead of MS
            while((float)(vex::timer::system()/1000) - initialTime < seconds) {
                this->base->driveBothSides(100 * percent);
                vex::wait(10, vex::msec);
                odom->pollAndUpdateOdom();
            }
            this->base->driveBothSides(0);
        }
        void driveBackwardForSpecifiedTimeAndPercent(float seconds, float percent) {
            float initialTime = vex::timer::system()/1000; // we divide by 1000 to convert to seconds instead of MS
            while((float)(vex::timer::system()/1000) - initialTime < seconds) {
                this->base->driveBothSides(((float)(-100) * percent));
                vex::wait(10, vex::msec);
            }
            this->base->driveBothSides(0);
        }
};

#endif
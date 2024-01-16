#ifndef MOTORGROUP_HPP
#define MOTORGROUP_HPP

#include "vex.h"
#include <vector>

class MotorGroup {
    private:
        std::vector<vex::motor*> motors;
    public:
        // default contructor not reccomended
        MotorGroup() {
            this->motors = std::vector<vex::motor*>();
        }
        MotorGroup(std::vector<vex::motor*> motors) {
            this->motors = motors;
        }
        // just incase user wants to do whatever they want w/ motors
        vex::motor* index(unsigned int index) {
            if (index > this->motors.size() || index < 0) {
                return NULL;
            }
            return this->motors.at(index);
        }

        // ____ useful functions ____
        void resetEncoders() {
            for (int i = 0; this->motors.size(); i++) {
                this->motors.at(i)->resetPosition();
            }
        }
        double averageRot(vex::rotationUnits units) {
            double total = 0.0;
            for (unsigned int i = 0 ; i < this->motors.size(); i++) {
                total += this->motors.at(i)->position(units);
            }
            return (total / (double)this->motors.size());
        }
        void setBrakeMode(vex::brakeType brakeMode) {
            for (int i = 0; i < this->motors.size(); i++) {
                this->motors.at(i)->setBrake(brakeMode);
            }
        }
        void move(int movement) {
            if (movement > 100) {
                movement = 100;
            }
            if (movement < -100) {
                movement = -100;
            }
            for (int i = 0; i < this->motors.size(); i++) {
                this->motors.at(i)->spin(vex::forward, movement, vex::pct);
            }
        }
        void stop() {
            for (int i = 0; i < this->motors.size(); i++) {
                this->motors.at(i)->spin(vex::forward, 0, vex::pct);
            }
        }
        bool allInstalled() {
            bool installed = true;
            for (int i = 0; i < this->motors.size(); i++) {
                installed = installed && this->motors.at(i)->installed();
            }
            return installed;
        }
};

#endif
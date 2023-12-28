#ifndef TIMER_HPP
#define TIMER_HPP

#include "vex.h"

class Timer {
    unsigned long timeToFinish = 0;
    public:
        void setTime(unsigned long time, vex::timeUnits units) {
            switch(units) {
                case vex::timeUnits::msec:
                    this->timeToFinish = vex::timer::systemHighResolution() + (time*1000);
                break;

                case vex::timeUnits::sec:
                    this->timeToFinish = vex::timer::systemHighResolution() + (time*1000000);
                break;
            }
        }
        bool shouldRun() {
            return vex::timer::systemHighResolution() >= this->timeToFinish;
        }
};

#endif
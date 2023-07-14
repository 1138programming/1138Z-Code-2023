#ifndef SHUFFLEBOARD_HPP
#define SHUFFLEBOARD_HPP

#include "main.h"



enum dataType {
    INT,
    LONG,
    FLOAT,
    DOUBLE,
    STRING
};

struct shuffleboardObject
{
    string name;
    void* data;
    dataType type;
};


class Shuffleboard {
    vector<shuffleboardObject>* objectsToDraw;
    public:
        void pushInt(int num, string name) {
            shuffleboardObject intObject = {
                name,

            }
            this->objectsToDraw->push_back(intObject);
        }
        void pushLong() {

        }
        void pushFloat() {

        }
        void pushDouble() {

        }
        void pushString() {

        }
}

#endif
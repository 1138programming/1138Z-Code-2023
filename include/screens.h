#ifndef SCREENS_H
#define SCREENS_H

#include "main.h"

typedef void (*screenFunction)();

enum screenEnum {
    MENU,
    SHUFFLEBOARD
};

struct screenStruct {
    screenEnum screenType;
    screenFunction screenDrawFunction;
};

class Display {
    public:
        Display(std::vector<screenStruct> screens) {
            //Sorts the screen types, making sure that they are in order before we attempt to do anything with them. In my implementation, I believe I am going to have to make sure that "MENU" is always at zero. I'm not entirely sure what I'm going to be doing, though
            sort(screens.begin(), screens.end(), [](const screenStruct& lhs, const screenStruct& rhs) {return lhs.screenType < rhs.screenType;});
            
        }
};

#endif
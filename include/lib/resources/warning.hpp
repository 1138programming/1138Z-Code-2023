#ifndef WARNING_HPP
#define WARNING_HPP

#include "warning_type.hpp"

#define MAX_WARNINGS 10

#include <string>

class Warning {
    private:
        WarningType type;
        char errorNum;

};

#endif
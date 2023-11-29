#ifndef TOGGLEABLE_HPP
#define TOGGLEABLE_HPP

class Toggleable {
    protected:
        bool toggled = false;
        bool lastToggled = false;
    public:
        void toggle() {
            this->toggled = !(this->toggled);
        }
        void setFalse() {
            this->toggled = false;
        }
        void setTrue() {
            this->toggled = true;
        }
        void update(bool updateVal) {
            this->lastToggled = toggled;
            this->toggled = updateVal;
        }
        bool isPressed() {
            return (this->lastToggled == false && this->toggled == true);
        }
}

#endif
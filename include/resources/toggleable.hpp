#ifndef TOGGLEABLE_HPP
#define TOGGLEABLE_HPP

class Toggleable {
    protected:
        bool enabled;
        bool pressed;
        bool lastPressed;
    public:
        void setEnabled() {
            this->enabled = true;
        }
        void setDisabled() {
            this->enabled = false;
        }
        void toggle() {
            this->enabled = !(this->enabled);
        }

        void update(bool updateVal) {
            this->lastPressed = this->pressed;
            this-> pressed = updateVal;
            this->enabled = isPressed();
        }

        bool isPressed() {
            return (this->lastPressed == false && this->pressed == true);
        }
};

#endif
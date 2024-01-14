#ifndef TOGGLEABLE_HPP
#define TOGGLEABLE_HPP

class Toggleable {
    private:
        bool pressed;
        bool lastPressed;
    protected:
        bool enabled;
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
            if (this->isPressed()) {
                this->toggle();
            }
        }

        bool isPressed() {
            return (this->lastPressed == false && this->pressed == true);
        }
};

#endif
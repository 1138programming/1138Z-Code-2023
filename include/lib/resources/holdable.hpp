#ifndef HOLDABLE_HPP
#define HOLDABLE_HPP

class Holdable {
    protected:
        bool enabled;
    public: 
        void setEnabled() {
            this-> enabled = true;
        }
        void setDisabled() {
            this->enabled = false;
        }
};

#endif
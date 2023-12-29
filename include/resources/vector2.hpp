#ifndef VECTOR2_HPP
#define VECTOR2_HPP

class Vector2 {
    public:
        float x;
        float y;
        Vector2() {
            this->x = 0.0;
            this->y = 0.0;
        }
        Vector2(float x, float y) {
            this->x = x;
            this->y = y;
        }
};

#endif
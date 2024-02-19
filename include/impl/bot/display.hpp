#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include "vex.h"

#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 272

const static vex::color BLACK(0, 0, 0);
const static vex::color WHITE(255, 255, 255);
const static vex::color RED(255, 0, 0);
const static vex::color GREEN(0, 255, 0);
const static vex::color BLUE(0, 0, 255);

class Display {
    private:
        vex::brain* botBrain;
        uint32_t* fullScreenBuffer;
        bool valid = true;
    public:
        Display(vex::brain* botBrain) {
            this->botBrain = botBrain;
            void* ptr = malloc(sizeof(uint32_t) * SCREEN_HEIGHT * SCREEN_WIDTH);
            if (ptr == nullptr) {
                this->valid = false;
            }
            else {
                this->valid = true;
            }
            this->fullScreenBuffer = (uint32_t*)ptr;
        }

        bool isValid() {
            return this->valid;
        }

        void setPixelUnsafe(uint16_t x, uint16_t y, vex::color color) {
            this->fullScreenBuffer[(y * SCREEN_WIDTH) + x] = color.rgb();
        }
        void clear(vex::color color) {
            uint32_t intColor = color.rgb();
            for (uint16_t i = 0; i < SCREEN_HEIGHT * SCREEN_WIDTH; i++) {
                this->fullScreenBuffer[i] = intColor;
            }
        }
        void drawHorizontalLineUnsafe(uint16_t x, uint16_t y, uint16_t width, vex::color color) {
            uint16_t yPreCalc = y*SCREEN_WIDTH;
            uint32_t intColor = color.rgb();
            for (uint16_t i = x; i < (x+width); i++) {
                this->fullScreenBuffer[yPreCalc+i] = intColor;
            }
        }
        void drawRectangleLinesUnsafe(uint16_t x, uint16_t y, uint16_t width, uint16_t height, vex::color color) {
            drawHorizontalLineUnsafe(x, y, width, color);
            drawHorizontalLineUnsafe(x, y+height, width, color);
            for (uint16_t i = (y+1); i < (height-1); i++) {
                setPixelUnsafe(x, i, color);
            }
            for (uint16_t i = (y+1); i < (height-1); i++) {
                setPixelUnsafe(x+width, i, color);
            }
        }
        void drawRectangleUnsafe(uint16_t x, uint16_t y, uint16_t width, uint16_t height, vex::color color) {
            for(uint16_t i = y; i < (y+width); i++) {
                drawHorizontalLineUnsafe(x,i,width,color);
            }
        }

        void update() {
            this->botBrain->Screen.drawImageFromBuffer(this->fullScreenBuffer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        }
        void red() {
            vex::color red(255,0,0);
            this->botBrain->Screen.clearScreen(red);
        }
        

        // no memory leak :D
        ~Display() {
            free(this->fullScreenBuffer);
        }
};

#endif
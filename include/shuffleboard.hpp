#ifndef SHUFFLEBOARD_HPP
#define SHUFFLEBOARD_HPP

#include "main.h"
#include <string>


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
    vector<shuffleboardObject> objectsToDraw;
    public:
        void createLabel(string text, const lv_obj_t *base, lv_align_t align, lv_coord_t x_mod, lv_coord_t y_mod) {
            lv_obj_t * myLabel;
            myLabel = lv_label_create(lv_scr_act(), NULL); //create label and puts it on the screen
            lv_label_set_text(myLabel, text.c_str()); //sets label text
            lv_obj_align(myLabel, base, align, x_mod, y_mod); //set the position to center
        }
        void draw() {
            //lv_obj_align(myLabel, NULL, LV_LABEL_ALIGN_CENTER, 10, 0); //set the position to center
            for(shuffleboardObject i:this->objectsToDraw) {
                switch (i.type)
                {
                case INT:
                    createLabel(i.name + ": " + std::to_string(*(int*)i.data), NULL, LV_LABEL_ALIGN_CENTER, 0, 0);
                    break;
                default:
                    createLabel(i.name, NULL, LV_LABEL_ALIGN_CENTER, 0, 0);
                    break;
                }
            }
        }
        void clear() {
            lv_obj_clean(lv_scr_act());
        }
        void pushInt(int* num, string name) {
            shuffleboardObject intObject = {
                name,
                (void*)num,
                INT
            };
            this->objectsToDraw.push_back(intObject);
        }
        void pushLong() {

        }
        void pushFloat() {

        }
        void pushDouble() {

        }
        void pushString() {

        }
};

#endif
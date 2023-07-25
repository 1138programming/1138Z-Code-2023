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
        lv_coord_t getScreenWidth() {
            return lv_obj_get_width(lv_scr_act());
        } 
        lv_coord_t getScreenHeight() {
            return lv_obj_get_height(lv_scr_act());
        } 
        lv_obj_t* createLabel(string text, const lv_obj_t *base, lv_align_t align, lv_coord_t x_mod, lv_coord_t y_mod) {
            lv_obj_t * myLabel;
            myLabel = lv_label_create(lv_scr_act(), NULL); //create label and puts it on the screen
            lv_label_set_text(myLabel, text.c_str()); //sets label text
            lv_obj_align(myLabel, base, align, x_mod, y_mod); //set the position to center
            return myLabel;
        }
        lv_obj_t* createLabelCenteredX(string text, const lv_obj_t *base, lv_align_t align, lv_coord_t y_mod) {
            lv_obj_t * myLabel;
            myLabel = lv_label_create(lv_scr_act(), NULL); //create label and puts it on the screen
            lv_label_set_text(myLabel, text.c_str()); //sets label text
            lv_coord_t objWidth = lv_obj_get_width(myLabel);
            lv_obj_align(myLabel, base, align, getScreenWidth()/2-(objWidth/2), y_mod); //set the position to center
            return myLabel;
        }
        void draw() {
            //lv_obj_align(myLabel, NULL, LV_LABEL_ALIGN_CENTER, 10, 0); //set the position to center
            for(int i = 0; i < this->objectsToDraw.size(); i++) {
                switch (this->objectsToDraw.at(i).type)
                {
                case INT:
                    createLabelCenteredX(objectsToDraw.at(i).name + ": " + std::to_string(*(int*)objectsToDraw.at(i).data), NULL, LV_LABEL_ALIGN_CENTER, 20*i);
                    break;
                default:
                    createLabel(objectsToDraw.at(i).name, NULL, LV_LABEL_ALIGN_CENTER, 0, 0);
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
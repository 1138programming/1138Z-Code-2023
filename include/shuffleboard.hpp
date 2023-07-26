#ifndef SHUFFLEBOARD_HPP
#define SHUFFLEBOARD_HPP

#include "main.h"
#include <string>
#include "screens.hpp"


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


lv_obj_t* buttonContainer = lv_obj_create(NULL, NULL);

class Shuffleboard {
    vector<shuffleboardObject> objectsToDraw;
    bool drawbool = true;
    lv_obj_t* WHY;

    public:
        Shuffleboard() {
            this->WHY = lv_obj_create(NULL,NULL);
        }
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

        // static lv_res_t btn_click_action(lv_obj_t * btn)
        // {
        //     char buffer[100];
        //     uint8_t id = lv_obj_get_free_num(btn); //id usefull when there are multiple buttons
        //     drawbool = false;
        //     return LV_RES_OK;
        // }

        bool buttonIsPressed(lv_obj_t* btn) {
            return lv_btn_get_state(btn) == LV_BTN_STATE_PR || lv_btn_get_state(btn) == LV_BTN_STATE_TGL_PR;
        }

        lv_obj_t* createButtonPlain(int width, int height, lv_obj_t* base, lv_align_t align, lv_coord_t x_mod, lv_coord_t y_mod, int id) {

            // lv_style_copy(&myButtonStyleREL, &lv_style_plain);
            // myButtonStyleREL.body.main_color = LV_COLOR_MAKE(150, 0, 0);
            // myButtonStyleREL.body.grad_color = LV_COLOR_MAKE(0, 0, 150);
            // myButtonStyleREL.body.radius = 0;
            // myButtonStyleREL.text.color = LV_COLOR_MAKE(255, 255, 255);

            // lv_style_copy(&myButtonStylePR, &lv_style_plain);
            // myButtonStylePR.body.main_color = LV_COLOR_MAKE(255, 0, 0);
            // myButtonStylePR.body.grad_color = LV_COLOR_MAKE(0, 0, 255);
            // myButtonStylePR.body.radius = 0;
            // myButtonStylePR.text.color = LV_COLOR_MAKE(255, 255, 255);

            // myButton = lv_btn_create(lv_scr_act(), NULL); //create button, lv_scr_act() is deafult screen object
            // lv_obj_set_free_num(myButton, 0); //set button is to 0
            // lv_btn_set_action(myButton, LV_BTN_ACTION_CLICK, btn_click_action); //set function to be called on button click
            // lv_btn_set_style(myButton, LV_BTN_STYLE_REL, &myButtonStyleREL); //set the relesed style
            // lv_btn_set_style(myButton, LV_BTN_STYLE_PR, &myButtonStylePR); //set the pressed style
            // lv_obj_set_size(myButton, 200, 50); //set the button size
            // lv_obj_align(myButton, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 10); //set the position to top mid

            lv_style_t myButtonStyleREL; //relesed style
            lv_style_t myButtonStylePR; //pressed style
            lv_obj_t* myButton;

            
            lv_style_copy(&myButtonStyleREL, &lv_style_plain);
            //myButtonStyleREL.text.color = LV_COLOR_MAKE(0, 0, 0);
            // myButtonStyleREL.body.main_color = LV_COLOR_MAKE(150, 0, 0);
            // myButtonStyleREL.body.grad_color = LV_COLOR_MAKE(0, 0, 150);
            // myButtonStyleREL.body.radius = 0;
            // myButtonStyleREL.text.color = LV_COLOR_MAKE(255, 255, 255);


            lv_style_copy(&myButtonStylePR, &lv_style_plain);
            // myButtonStylePR.body.main_color = LV_COLOR_MAKE(255, 0, 0);
            // myButtonStylePR.body.grad_color = LV_COLOR_MAKE(0, 0, 255);
            // myButtonStylePR.body.radius = 0;
            // myButtonStylePR.text.color = LV_COLOR_MAKE(255, 255, 255);


            myButton = lv_btn_create(lv_scr_act(), NULL); //create button, lv_scr_act() is deafult screen object

            lv_obj_set_free_num(myButton, id); //set button is to 0

            // lv_btn_set_style(myButton, LV_BTN_STYLE_REL, &myButtonStyleREL); //set the released style
            //lv_btn_set_style(myButton, LV_BTN_STYLE_PR, &myButtonStylePR); //set the pressed style

            lv_obj_set_size(myButton, width, height); //set the button size
            lv_obj_align(myButton, base, align, x_mod, y_mod); //set the position to top mid


            return myButton;
        }
        void draw() {
            //this->WHY = lv_obj_create(NULL,NULL);
            //lv_obj_align(myLabel, NULL, LV_LABEL_ALIGN_CENTER, 10, 0); //set the position to center
            lv_obj_t* btn = createButtonPlain(100, 50, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 50, 0);
            if (buttonIsPressed(btn)) {
                this->drawbool = !drawbool;
            }
            if(drawbool) {
                for(int i = 0; i < this->objectsToDraw.size(); i++) {
                    switch (this->objectsToDraw.at(i).type)
                    {
                    case INT:
                        createLabelCenteredX(objectsToDraw.at(i).name + ": " + std::to_string(*(int*)objectsToDraw.at(i).data), this->WHY, LV_LABEL_ALIGN_CENTER, 20*i);
                        break;
                    default:
                        createLabel(objectsToDraw.at(i).name, this->WHY, LV_LABEL_ALIGN_CENTER, 0, 0);
                        break;
                    }
                }
            }
        }
        void clear() {
            //lv_obj_clean(lv_scr_act());
            lv_obj_clean(this->WHY);
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
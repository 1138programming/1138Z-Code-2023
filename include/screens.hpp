#ifndef SCREENS_HPP
#define SCREENS_HPP

#include "shuffleboard.hpp"
class screens {
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
        lv_obj_t* createButtonPlain(int width, int height, lv_obj_t* base, lv_align_t align, lv_coord_t x_mod, lv_coord_t y_mod) {

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

            lv_style_t myButtonStyleREL; //relesed style
            lv_style_t myButtonStylePR; //pressed style
            lv_obj_t* myButton;
            
            lv_style_copy(&myButtonStyleREL, &lv_style_plain);
            myButtonStyleREL.text.color = LV_COLOR_MAKE(0, 0, 0);

            lv_style_copy(&myButtonStylePR, &lv_style_plain);
            myButtonStylePR.body.main_color = LV_COLOR_MAKE(115, 122, 116);
            myButtonStylePR.body.shadow.color = LV_COLOR_MAKE(72, 75, 72);
            myButtonStylePR.body.shadow.width = 2;
            myButtonStylePR.body.shadow.type = LV_SHADOW_BOTTOM;
            myButtonStylePR.text.color = LV_COLOR_MAKE(0, 0, 0);

            lv_btn_set_style(myButton, LV_BTN_STYLE_REL, &myButtonStyleREL); //set the released style
            lv_btn_set_style(myButton, LV_BTN_STYLE_PR, &myButtonStylePR); //set the pressed style

            lv_obj_set_size(myButton, width, height); //set the button size
            lv_obj_align(myButton, base, align, x_mod, y_mod); //set the position to top mid
        }
};

#endif
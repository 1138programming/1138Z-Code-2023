#include "main.h"
#include "Constants.hpp"
#include "Base.h"
#include "MYPID.h"
#include "intake.h"
#include "shuffleboard.hpp"

//Base botBase(1,2,3,11,12,13);

struct Pos
{
  /* data */
  double x = 0.0;
  double y = 0.0;
  double rotation = 0.0;
} odomRobotPos;


/*
    def pickUpBlock() {
      moveArmDown();???
      openArm(); //if closed
      driveForwards(0.05, meters);
      closeArm();
    }
  br:
    rotateUntil(45);
    roateUntil(90);
    driveBackwards(0.7,meters);
    rotateUntil(0);
    pickUpBlock();
    rotateUntil(135);

  bl:
  
  tr:
  
  tl:


*/


/*
y mult = \operatorname{abs}\left(\left(\frac{\operatorname{mod}\left(x,180\right)}{90}\right)-1\right)

x mult = \operatorname{abs}\left(-\left(\frac{\operatorname{mod}\left(x,180\right)}{90}\right)+1\right)
*/

/////
// For instalattion, upgrading, documentations and tutorials, check out website!
// https://ez-robotics.github.io/EZ-Template/
/////
Base robotBase(new Motor_Group({1,2,3}), new Motor_Group({11,12,13}), new MYPID(0,2,0.5,2,600,-600,0.5), new MYPID(0,2,0.5,2,600,-600,0.5), 4.125);
Intake intake(new Motor(kIntakePort));
/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */

lv_obj_t * myButton;
lv_obj_t * myButtonLabel;
lv_obj_t * myLabel;

lv_style_t myButtonStyleREL; //relesed style
lv_style_t myButtonStylePR; //pressed style

static lv_res_t btn_click_action(lv_obj_t * btn)
{
    uint8_t id = lv_obj_get_free_num(btn); //id usefull when there are multiple buttons

    if(id == 0)
    {
        char buffer[100];
		sprintf(buffer, "button was clicked %i milliseconds from start", pros::millis());
		lv_label_set_text(myLabel, buffer);
    }

    return LV_RES_OK;
}

void initialize() {
      lv_style_copy(&myButtonStyleREL, &lv_style_plain);
    myButtonStyleREL.body.main_color = LV_COLOR_MAKE(150, 0, 0);
    myButtonStyleREL.body.grad_color = LV_COLOR_MAKE(0, 0, 150);
    myButtonStyleREL.body.radius = 0;
    myButtonStyleREL.text.color = LV_COLOR_MAKE(255, 255, 255);

    lv_style_copy(&myButtonStylePR, &lv_style_plain);
    myButtonStylePR.body.main_color = LV_COLOR_MAKE(255, 0, 0);
    myButtonStylePR.body.grad_color = LV_COLOR_MAKE(0, 0, 255);
    myButtonStylePR.body.radius = 0;
    myButtonStylePR.text.color = LV_COLOR_MAKE(255, 255, 255);

    myButton = lv_btn_create(lv_scr_act(), NULL); //create button, lv_scr_act() is deafult screen object
    lv_obj_set_free_num(myButton, 0); //set button is to 0
    lv_btn_set_action(myButton, LV_BTN_ACTION_CLICK, btn_click_action); //set function to be called on button click
    lv_btn_set_style(myButton, LV_BTN_STYLE_REL, &myButtonStyleREL); //set the relesed style
    lv_btn_set_style(myButton, LV_BTN_STYLE_PR, &myButtonStylePR); //set the pressed style
    lv_obj_set_size(myButton, 200, 50); //set the button size
    lv_obj_align(myButton, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 10); //set the position to top mid

    myButtonLabel = lv_label_create(myButton, NULL); //create label and puts it inside of the button
    lv_label_set_text(myButtonLabel, "Click the Button"); //sets label text

    myLabel = lv_label_create(lv_scr_act(), NULL); //create label and puts it on the screen
    lv_label_set_text(myLabel, "Button has not been clicked yet"); //sets label text
    lv_obj_align(myLabel, NULL, LV_LABEL_ALIGN_CENTER, 10, 0); //set the position to center
  // Print our branding over your terminal :D

  // Initialize chassis and auton selector
}



/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
  // . . .
}



/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
  // . . .
}



/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
  // chassis.reset_pid_targets(); // Resets PID targets to 0
  // chassis.reset_gyro(); // Reset gyro position to 0
  // chassis.reset_drive_sensor(); // Reset drive sensors to 0
  // chassis.set_drive_brake(MOTOR_BRAKE_HOLD); // Set motors to hold.  This helps autonomous consistency.

  // ez::as::auton_selector.call_selected_auton(); // Calls selected auton from autonomous selector.
}



/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
  // bool R1LastPressed = false;
  // bool L1LastPressed = false;
  // // This is preference to what you like to drive on.
  // pros::Controller master(CONTROLLER_MASTER);
  // while (true) {
  //   robotBase.driveSplitArcade(master.get_analog(ANALOG_RIGHT_X), master.get_analog(ANALOG_LEFT_Y));
  //   //Code to get the intake to move on R1 or L1 input.

  //   if (master.get_digital(DIGITAL_R1)) {
  //     if (!R1LastPressed) {
  //       intake.toggleDirection();
  //     }
  //     R1LastPressed = true;
  //   }
  //   else {
  //     R1LastPressed = false;
  //   }
  //   intake.move(kIntakeSpeed);

  //   if (master.get_digital(DIGITAL_L1)) {
  //     if(!L1LastPressed) {
  //       intake.toggleDisable();
  //     }
  //     L1LastPressed = true;
  //   }
  //   else {
  //     L1LastPressed = false;
  //   }
  //   //chassis.tank(); // Tank control    //chassis.arcade_standard(ez::SPLIT); // Standard split arcade
  //   // chassis.arcade_standard(ez::SINGLE); // Standard single arcade
  //   // chassis.arcade_flipped(ez::SPLIT); // Flipped split arcade
  //   // chassis.arcade_flipped(ez::SINGLE); // Flipped single arcade
  //   // . . .
  //   // Put more user control code here!
  //   // . . .

  //   pros::delay(ez::util::DELAY_TIME); // This is used for timer calculations!  Keep this ez::util::DELAY_TIME
  // }
}

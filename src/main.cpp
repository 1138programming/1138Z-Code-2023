#include "main.h"
#include "Constants.hpp"
#include "Base.h"
#include "MYPID.h"

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

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
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
  // This is preference to what you like to drive on.
  pros::Controller master(CONTROLLER_MASTER);
  pros::Motor intake(19);
  while (true) {
    robotBase.driveSplitArcade(master.get_analog(ANALOG_RIGHT_X), master.get_analog(ANALOG_LEFT_Y));
    //Code to get the intake to move on R1 or L1 input.
    if (master.get_digital(DIGITAL_R1)) {
      intake.move(127);
    }
    else if (master.get_digital(DIGITAL_L1)) {
      intake.move(-127);
    }
    else {
      intake.move(0);
    }
    //chassis.tank(); // Tank control    //chassis.arcade_standard(ez::SPLIT); // Standard split arcade
    // chassis.arcade_standard(ez::SINGLE); // Standard single arcade
    // chassis.arcade_flipped(ez::SPLIT); // Flipped split arcade
    // chassis.arcade_flipped(ez::SINGLE); // Flipped single arcade
    // . . .
    // Put more user control code here!
    // . . .

    pros::delay(ez::util::DELAY_TIME); // This is used for timer calculations!  Keep this ez::util::DELAY_TIME
  }
}

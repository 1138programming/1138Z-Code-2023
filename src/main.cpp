/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       {file}                                                    */
/*    Author:       {author}                                                  */
/*    Created:      {date}                                                    */
/*    Description:  {description}                                             */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"
#include "constants.hpp"
#include "catapult.hpp"
#include "base.hpp"
#include "MYPID.hpp"
#include "auton.hpp"
#include "intake.hpp"
#include "odometry.hpp"
#include "gyro.hpp"
//pleaseplease show up on github

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here
PID odomTurningPID(0.0, -0.75, 0.0, 0.0, 100.0, -100.0, 0.1);
vex::inertial inertialSensor(kInertialSensorPort);
vex::motor bl(kBackLeftMotorPort);
vex::motor cl(kCenterLeftPort);
vex::motor fl(kFrontLeftPort);
vex::motor br(kBackRightMotorPort, true);
vex::motor cr(kCenterRightPort, true);
vex::motor fr(kFrontRightPort, true);
// user-defined classes
Base robotBase(&bl, &cl, &fl, &br, &cr, &fr);
Intake intake(new vex::motor(kIntakePort));
Catapult catapult(new vex::motor(kCatapultPort));
Autons autons(&robotBase);
Gyro gyroClass(&inertialSensor);
Odometry odom(3, kWheelDiamInches, kOdomGearRatio, &robotBase, &gyroClass, &odomTurningPID);
vex::brain::lcd BRAINSCREEN;


/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
  //autons.driveForwardForSpecifiedTimeAndPercent(2.0, 0.5);
  
  //odom.turnToPosPID(180.0);
  //robotBase.turn(20);
  //odom.moveForwardToPosInInches(6.0, 20);
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop
  // bool R1LastPressed = false;
  // bool L1LastPressed = false;
  // bool L2LastPressed = false;
  // bool pistonVal = false;
  BRAINSCREEN.clearScreen();
  BRAINSCREEN.printAt(50,50,"help: %d",counter);

  vex::controller controllerMain = vex::controller(vex::primary);
  bool mainControllerR1LastPressed = false;
  while (1) {
  //driver preference.
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    // code to get the catapult working...
    catapult.moveWithActiveCheck();
    if (controllerMain.ButtonR1.pressing() && !mainControllerR1LastPressed) {
      catapult.catapultToggle();
    }
    catapult.initHoldMotor(controllerMain.ButtonA.pressing());
    //LCD.clearScreen();
    //LCD.print(controllerMain.ButtonA.pressing());
    //LCD.printAt(0,50,"%f",(robotBase.getAverageRightRot() * kWheelDiamInches)/kOdomGearRatio);
    //LCD.printAt(0,50,"%f",gyroClass.getHeading());
    // drive code... TODO: reverse dive base in base.hpp - complete?
    robotBase.driveSplitArcade(controllerMain.Axis1.position(), controllerMain.Axis3.position());

    mainControllerR1LastPressed = controllerMain.ButtonR1.pressing();
    
    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}

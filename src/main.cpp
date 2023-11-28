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
#include "hang.hpp"
//pleaseplease show up on github

using namespace vex;

// A global instance of competition
competition Competition;
vex::brain Brain = vex::brain();
// define your global instances of motors and other devices here
PID odomTurningPID(0.0, -0.75, 0.0, 0.0, 100.0, -100.0, 0.1);
PID odomMovementPID(0.0, 80, 0.0, 0.0, 100.0, -100.0, 0.1);
vex::inertial inertialSensor(kInertialSensorPort);
vex::motor bl(kBackLeftMotorPort, true);
vex::motor cl(kCenterLeftPort);
vex::motor fl(kFrontLeftPort);
vex::motor br(kBackRightMotorPort, true);
vex::motor cr(kCenterRightPort);
vex::motor fr(kFrontRightPort);
// vex::motor bl(kBackLeftMotorPort);
// vex::motor cl(kCenterLeftPort, true);
// vex::motor fl(kFrontLeftPort, true);
// vex::motor br(kBackRightMotorPort);
// vex::motor cr(kCenterRightPort, true);
// vex::motor fr(kFrontRightPort, true);
// user-defined classes
Base robotBase(&bl, &cl, &fl, &br, &cr, &fr);
//Intake intake(new vex::motor(kIntakePort));
vex::motor intake(kIntakePort);
vex::motor hangMotor(kHangMotor);
Catapult catapult(new vex::motor(kCatapultPort));
Hang hang();
Autons autons(&robotBase);
Gyro gyroClass(&inertialSensor);
vex::brain::lcd BRAINSCREEN;
Odometry odom(kWheelDiamInches, kOdomGearRatio, &robotBase, &gyroClass, &odomTurningPID, &odomMovementPID, 0.56912f);
vex::digital_out driveBaseWings = vex::digital_out(Brain.ThreeWirePort.A);

// MULTITASKING
//this should run the task
//vex::task odomUpdate(&(odom.pollAndUpdateOdom), (void*)&odom);

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
  driveBaseWings.set(true);
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
  robotBase.resetMotorEncoders();
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
  //autons.driveForwardForSpecifiedTimeAndPercent(2.0, 0.5);
  // gyroClass.resetGyro();
  // odom.setX(0.0);
  // odom.setY(0.0);
  //odom.turnToPosPID(180.0);
  //robotBase.turn(20);
  //odom.moveInInchesOdomPID(2.0);
  odom.moveInFeetOdomPIDWithTurn(2.0f);
  odom.turnToPosPID(270.0, 0.5);
  odom.moveInFeetOdomPIDWithTurn(1.5f);
  //odom.moveInInchesOdom(1.0, 0.1);
  //odom.turnToPosPID(180, 5.0);
  // vex::wait(100, vex::msec);
  // odom.turnToPosPID(90, 5.0);
  // vex::wait(100, vex::msec);
  // odom.turnToPosPID(270, 5.0);
  //odom.moveInInchesOdom(1.0, 1.1);
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
  gyroClass.resetGyro();
  // not nearly as necessary in driverControl.
  // User control code here, inside the loop
  // bool R1LastPressed = false;
  // bool L1LastPressed = false;
  // bool L2LastPressed = false;
  // bool pistonVal = false;

  vex::controller controllerMain = vex::controller(vex::primary);

  bool mainControllerR1LastPressed = false;
  bool mainControllerL1LastPressed = false;

  bool intakeReverse = false;
  bool intakeEnabled = true;
  
  bool buttonBLastPressed = false;
  bool buttonR2LastPressed = false;
  // cata 30, 

  while (1) {
    // BRAINSCREEN.clearScreen();
    // odom.pollAndUpdateOdom();
    BRAINSCREEN.printAt(50,50,"X: %lf Y: %lf; ROT: %lf", odom.getX(), odom.getY(), gyroClass.getHeading());
    BRAINSCREEN.printAt(50,100,"lastX: %lf, lastY: %lf", odom.getLastXChange(), odom.getLastYChange());
    BRAINSCREEN.printAt(50,150,"Inches: %lf, thrm: %lf", 5.0, odom.getDisplacement(5.0));

    if (controllerMain.ButtonL1.pressing() && !mainControllerL1LastPressed) {
      driveBaseWings.set(!(driveBaseWings.value()));
    }

    if (controllerMain.ButtonB.pressing() && !buttonBLastPressed) {
      intakeEnabled = !intakeEnabled;
    }
    if (controllerMain.ButtonR2.pressing() && !buttonR2LastPressed) {
      intakeReverse = !intakeReverse;
    }
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    //intake
    //intake.moveWithController(controllerMain.ButtonB.pressing(), controllerMain.ButtonR2.pressing());
    if (intakeEnabled) {
      if (intakeReverse) {
        intake.spin(vex::forward, -kIntakeSpeed, vex::pct);
      }
      else {
        intake.spin(vex::forward, kIntakeSpeed, vex::pct);
      }
    }
    else {
      intake.spin(vex::forward, 0, vex::pct);
    }
    // code to get the catapult working...
    catapult.moveWithActiveCheck();
    if (controllerMain.ButtonR1.pressing() && !mainControllerR1LastPressed) {
      catapult.catapultToggle();
    }
    catapult.initHoldMotor(controllerMain.ButtonA.pressing());
    
    //driver preference.
    robotBase.driveSplitArcade(controllerMain.Axis1.position(), controllerMain.Axis3.position());

    // set controller vars. TODO: make these into a class, priority low.
    mainControllerR1LastPressed = controllerMain.ButtonR1.pressing();
    mainControllerL1LastPressed = controllerMain.ButtonL1.pressing();

    buttonBLastPressed = controllerMain.ButtonB.pressing();
    buttonR2LastPressed = controllerMain.ButtonR2.pressing();
    vex::wait(20, vex::msec); // Sleep the task for a short amount of time to
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

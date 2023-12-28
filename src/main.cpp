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
#include "timer.hpp"
//pleaseplease show up on github

using namespace vex;

// A global instance of competition
competition Competition;
vex::brain Brain = vex::brain();
// define your global instances of motors and other devices here
PID odomTurningPID(0.0, 0.5, 0.0, 0.0, 100.0, -100.0, 0.1);
PID odomMovementPID(0.0, 20, 0.0, 0.0, 100.0, -100.0, 0.1);
vex::inertial inertialSensor(kInertialSensorPort);
vex::motor bl(kBackLeftMotorPort);
vex::motor cl(kCenterLeftPort);
vex::motor fl(kFrontLeftPort, true);
vex::motor br(kBackRightMotorPort, true);
vex::motor cr(kCenterRightPort, true);
vex::motor fr(kFrontRightPort);
// user-defined classes
Base robotBase(&bl, &cl, &fl, &br, &cr, &fr);
//Intake intake(new vex::motor(kIntakePort));
vex::motor intake(kIntakePort, true);
vex::motor hangMotor(kHangMotor);
Catapult catapult(new vex::motor(kCatapultPort, true));
Hang hang();
Autons autons(&robotBase);
Gyro gyroClass(&inertialSensor);
vex::brain::lcd BRAINSCREEN;
Odometry odom(kWheelDiamInches, kOdomGearRatio, &robotBase, &gyroClass, &odomTurningPID, &odomMovementPID, 1.213369);
vex::digital_out driveBaseWings = vex::digital_out(Brain.ThreeWirePort.G);
Hang* robotHang = new Hang();
double final = 0.0;
double goal = 0.0;
Timer* vexSkillsCataTimer = new Timer();

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
  gyroClass.resetGyro();
  robotBase.resetMotorEncoders();

  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................

// timing test

  //  vexSkillsCataTimer->setTime(10.0, vex::sec);
  //  while ((vexSkillsCataTimer->shouldRun())) {
  //    catapult.moveCatapult();
  //  }
  //  catapult.stopMoving();

// odom functions

  odom.moveInFeetOdomPID(3.0f);
  // unsigned long setTime = (vex::timer::system() + 250);
  // while (vex::timer::system() < setTime) {
  //   robotBase.turn(20);
  //   odom.pollAndUpdateOdom();
  // }
  // while (!(gyroClass.getRot() >= 1.0) && !(gyroClass.getRot() <= 20.0)) {
  //   robotBase.turn(40);
  //   odom.pollAndUpdateOdom();
  // }
  // odom.turnToPosPIDWithIntake(35, 0.5, &intake);
  //autons.driveForwardForSpecifiedTimeAndPercent(1.0, 0.5, &odom);
  // odom.moveInFeetOdomPID(3.1f);
  // intake.spin(vex::forward, 0, vex::pct);


  //odom.moveInFeetOdomPID(-(3.1f));
  driveBaseWings.set(true);

  unsigned long time73 = vex::timer::system() + 300;
  while(vex::timer::system() < time73) {
    // wait 300ms
  }

  autons.driveBackwardForSpecifiedTimeAndPercent(1.01, -0.325);
  driveBaseWings.set(false);

  unsigned long time7 = vex::timer::system() + 300;
  while(vex::timer::system() < time7) {
    // wait 300ms
  }

  odom.turnToPosPID(320, 0.5);

  unsigned long time = vex::timer::system() + 100;
  while(vex::timer::system() < time) {
    // wait 100ms
  }

  autons.driveBackwardForSpecifiedTimeAndPercent(1.5, -0.27);



  // unsigned long time2 = (vex::timer::system() + 250);
  // while (vex::timer::system() < time2) {
  //   robotBase.turn(-30);
  //   odom.pollAndUpdateOdom();
  // }
  // robotBase.stop();

  // odom.turnToPosPID(320, 0.5);
  // autons.driveBackwardForSpecifiedTimeAndPercent(1.07, -0.362);
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
  // not nearly as necessary in driverControl.
  // User control code here, inside the loop
  // bool R1LastPressed = false;
  // bool L1LastPressed = false;
  // bool L2LastPressed = false;
  // bool pistonVal = false;

  vex::controller controllerMain = vex::controller(vex::primary);

  bool mainControllerR1LastPressed = false;

  bool intakeReverse = false;
  bool intakeEnabled = true;
  
  bool buttonL1LastPressed = false;
  bool buttonL2LastPressed = false;

  bool buttonUpLastPressed = false;
  bool buttonDownLastPressed = false;
  // cata 30, 

  while (1) {
    BRAINSCREEN.clearScreen();
    // odom.pollAndUpdateOdom();
    BRAINSCREEN.printAt(50,50,"X: %lf Y: %lf; ROT: %lf", odom.getX(), odom.getY(), gyroClass.getHeading());
    BRAINSCREEN.printAt(50,100,"lastX: %lf, lastY: %lf", odom.getLastXChange(), odom.getLastYChange());
    BRAINSCREEN.printAt(50,150,"Final: %lf", final);

    if (controllerMain.ButtonUp.pressing() && !buttonUpLastPressed) {
      driveBaseWings.set(true);
    }
    if (controllerMain.ButtonDown.pressing() && !buttonDownLastPressed) {
      driveBaseWings.set(false);
    }

    if (controllerMain.ButtonL1.pressing() && !buttonL1LastPressed) {
      intakeEnabled = !intakeEnabled;
    }
    if (controllerMain.ButtonL2.pressing() && !buttonL2LastPressed) {
      intakeReverse = !intakeReverse;
    }
    robotHang->update(controllerMain.ButtonB.pressing());
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
    robotBase.driveSplitArcade(controllerMain.Axis3.position(), controllerMain.Axis1.position());

    // set controller vars. TODO: make these into a class, priority low.
    mainControllerR1LastPressed = controllerMain.ButtonR1.pressing();

    buttonL1LastPressed = controllerMain.ButtonL1.pressing();
    buttonL2LastPressed = controllerMain.ButtonL2.pressing();
    buttonDownLastPressed = controllerMain.ButtonDown.pressing();
    buttonUpLastPressed = controllerMain.ButtonUp.pressing();
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

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       josh-duross                                               */
/*    Created:      12/28/2023, 1:38:47 PM                                    */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"
#include "impl/constants.h"
#include "lib/bot/gyro.hpp"
#include "lib/commands/movement.hpp"
#include "lib/resources/controller.hpp"
#include "lib/resources/PID.hpp"
#include "lib/resources/holdable.hpp"
#include "impl/bot/intake.hpp"
#include "impl/bot/hang.hpp"
#include "lib/commands/odomMovement.hpp"


using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here
std::vector<vex::motor*> leftMotors{new vex::motor(KBackLeftMotorPort), new vex::motor(KMiddleLeftMotorPort, true), new vex::motor(KFrontLeftMotorPort, true)};
std::vector<vex::motor*> rightMotors{new vex::motor(KBackRightMotorPort, true), new vex::motor(KMiddleRightMotorPort), new vex::motor(KFrontRightMotorPort)};
Base robotBase(leftMotors, rightMotors);
PID turningPID(0.0, 0.58, 0.0, 0.0, 100, -100, 0.4);
PID movementPID(0.0, 20.0, 0.0, 0.0, 100, -100, 0.1);
Movement botMovement(&robotBase, true);
Controller mainController(vex::controllerType::primary);
vex::motor intakeMotor(KIntakeMotorPort);
Hang botHangPneumatics;
vex::inertial* internalGyro = new vex::inertial(KInertialSensorPort);
Gyro* botGyro = new Gyro(internalGyro);
Odometry* botOdom = new Odometry(KOdomWheelSize, &robotBase, botGyro);
OdomMovement* gamer = new OdomMovement(botOdom, &botMovement, botGyro, &movementPID, &turningPID);


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
  botGyro->resetGyroWithWait();

  gamer->moveInInchesOdomPID(5.0);
  gamer->turnToPosPID(180.0, 0.5);

  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
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
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................
    
      botMovement.driveSplitArcade(&mainController);
      botHangPneumatics.update(mainController.getButton(BUTTON_B));

      if (mainController.getButton(BUTTON_R1)) {
        intakeMotor.spin(vex::forward, 80, vex::pct);
      }
      else if (mainController.getButton(BUTTON_R2)) {
        intakeMotor.spin(vex::forward, -80, vex::pct);
      }
      else {
        intakeMotor.spin(vex::forward, 0, vex::pct);
      }

    wait(5, msec); // Sleep the task for a short amount of time to
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
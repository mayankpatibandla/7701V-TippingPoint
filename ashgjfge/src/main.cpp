/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
 
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                   
// Drivetrain           drivetrain    1, 11, 14, 2   
// Motor18              motor         18             
// Motor19              motor         19             
// BumperB              bumper        B              
// LightC               light         C              
// ---- END VEXCODE CONFIGURED DEVICES ----
 
#include "vex.h"
 
using namespace vex;
 
// A global instance of competition
competition Competition;
 
// define your global instances of motors and other devices here
controller Controller1 = controller(primary);
motor leftfront = motor(PORT1, ratio18_1, false);
motor leftback = motor(PORT11, ratio18_1, false);
motor_group LeftDriveSmart = motor_group(leftfront, leftback);
motor rightfront = motor(PORT14, ratio18_1, true);
motor rightback = motor(PORT2, ratio18_1, true);
motor_group RightDriveSmart = motor_group(rightfront, rightback);
drivetrain Drive = drivetrain(LeftDriveSmart, RightDriveSmart, 319.19, 295, 40, mm, 1);
motor Motor18 = motor(PORT18, ratio18_1, false);
motor Motor19 = motor(PORT19, ratio18_1, false);
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
 // Initializing Robot Configuration. DO NOT REMOVE!
 vexcodeInit();
 
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
/* set velocity */
leftfront.setVelocity(80, percent);
leftback.setVelocity(80, percent);
rightfront.setVelocity(80, percent);
rightback.setVelocity(80, percent);
/*forward*/
leftfront.startRotateFor(vex::directionType::fwd, 100, vex::rotationUnits::deg);
leftback.startRotateFor(vex::directionType::fwd, 100, vex::rotationUnits::deg);
rightfront.startRotateFor(vex::directionType::fwd, 100, vex::rotationUnits::deg);
rightback.rotateFor(vex::directionType::fwd, 100, vex::rotationUnits::deg);
/*pick up*/
 
/*turn left and right*/
leftfront.startRotateFor(vex::directionType::rev, 90, vex::rotationUnits::deg);
leftback.startRotateFor(vex::directionType::rev, 90, vex::rotationUnits::deg);
rightfront.startRotateFor(vex::directionType::fwd, 90, vex::rotationUnits::deg);
rightback.rotateFor(vex::directionType::fwd, 90, vex::rotationUnits::deg);
/*forward and reverse*/
leftfront.startRotateFor(vex::directionType::rev, 100, vex::rotationUnits::deg);
leftback.startRotateFor(vex::directionType::rev, 100, vex::rotationUnits::deg);
rightfront.startRotateFor(vex::directionType::rev, 100, vex::rotationUnits::deg);
rightback.rotateFor(vex::directionType::rev, 100, vex::rotationUnits::deg);
leftfront.startRotateFor(vex::directionType::rev, 100, vex::rotationUnits::deg);
 
vex::motor(leftfront).stop();
vex::motor(leftback).stop();
vex::motor(rightfront).stop();
vex::motor(rightback).stop();
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
 while (1) {
   motor_group(LeftDriveSmart).spin(forward, Controller1.Axis3.position() + Controller1.Axis4.position() / 4, pct);
   motor_group(RightDriveSmart).spin(forward, Controller1.Axis3.position() - Controller1.Axis4.position() / 4, pct);
//control arm with R1 and R2 buttons   
   if(Controller1.ButtonR1.pressing()) {
   Motor18.spin(vex::directionType::fwd, 100,vex::velocityUnits::pct);
   }
   else if(Controller1.ButtonR2.pressing()) {
   Motor18.spin(vex::directionType::rev, 100,vex::velocityUnits::pct);
   }
   else {
     Motor18.stop(vex::brakeType::brake);
   }
// control claw with L1 and L2 buttons
   if(Controller1.ButtonL1.pressing()) {
   Motor19.spin(vex::directionType::fwd, 100,vex::velocityUnits::pct);
   }
   else if(Controller1.ButtonL2.pressing()) {
   Motor19.spin(vex::directionType::rev, 100,vex::velocityUnits::pct);
   }
   else {
     Motor18.stop(vex::brakeType::brake);
   }
   wait(20, msec); // Sleep the task for a short amount of time
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
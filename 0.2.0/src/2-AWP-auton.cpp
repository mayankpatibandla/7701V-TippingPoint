#include "vex.h"
#include "auton-functions.h"

//LEFT AWP OTHER
//left get 1 yellow
void twoAWPAuton(){
  toggleClaw();
  driveMotors.spin(fwd, 12, volt);
  waitUntil(pt::x() > 60);
  driveMotors.stop();
  this_thread::sleep_for(50);
  toggleClaw();
  this_thread::sleep_for(50);
  driveMotors.spin(fwd, -12, volt);
  this_thread::sleep_for(2500);
  driveMotors.stop();
}

//RIGHT NEUTRAL MAIN or OTHER
void rightMidFirstAuton(){
  driveMotors.spin(fwd, 12, volt);
  toggleClaw();
  waitUntil(pt::x() > 54);
  driveMotors.stop();
  this_thread::sleep_for(25);
  toggleClaw();
  this_thread::sleep_for(25);
  fourBarMotor.spin(fwd, 12, volt);
  driveMotors.spin(fwd, -12, volt);
  this_thread::sleep_for(100);
  fourBarMotor.stop(hold);
  waitUntil(pt::x() < 5);
  driveMotors.stop();
}

//LEFT NEUTRAL MAIN or OTHER
void leftMidFirstAuton(){
  driveMotors.spin(fwd, 12, volt);
  toggleClaw();
  waitUntil(pt::x() > 60);
  driveMotors.stop();
  this_thread::sleep_for(25);
  toggleClaw();
  this_thread::sleep_for(25);
  fourBarMotor.spin(fwd, 12, volt);
  driveMotors.spin(fwd, -12, volt);
  this_thread::sleep_for(100);
  fourBarMotor.stop(hold);
  waitUntil(pt::x() < 5);
  driveMotors.stop();
}
#include "vex.h"
#include "auton-functions.h"

//RIGHT AWP MAIN
void rightSideAWP2NeutralAuton(){
  //get yellow
  driveMotors.spin(fwd, 12, volt);
  toggleClaw();
  waitUntil(pt::x() > 45);
  driveMotors.stop();
  this_thread::sleep_for(25);
  toggleClaw();
  this_thread::sleep_for(25);
  fourBarMotor.spin(fwd, 12, volt);
  driveMotors.spin(fwd, -12, volt);
  waitUntil(pt::x() < 5);
  driveMotors.stop();

  //get alliance goal
  driveMotors.spin(fwd, 50, pct);
  fourBarMotor.stop();
  waitUntil(pt::x() > 10.25);
  driveMotors.stop();
  turnToAngle(M_PI_2);
  toggleBackLift();
  driveRelative(-16, 1200, slowFwd);
  toggleBackLift();
  this_thread::sleep_for(50);
  driveRelative(5, 1000);

  //get rings
  turnToAngle(0);
  ringLiftMotor.spin(fwd, 7.5, volt);
  driveMotors.spin(fwd, 25, pct);
  waitUntil(pt::x() > 51);
  driveMotors.stop();
  this_thread::sleep_for(500);
  driveMotors.spin(fwd, -100, pct);
  waitUntil(pt::x() < 0);
  driveMotors.stop();
  toggleBackLift();
  this_thread::sleep_for(100);
  driveRelative(6, 1000);
}

//RIGHT AWP OTHER
void rightSideAWP1NeutralAuton(){
  toggleBackLift();
  driveMotors.spin(fwd, -7.5, volt);
  this_thread::sleep_for(1200);
  driveMotors.stop();
  this_thread::sleep_for(75);
  toggleBackLift();
  this_thread::sleep_for(200);
  driveMotors.spin(fwd, 6, volt);
  this_thread::sleep_for(2000);
  driveMotors.stop();
  ringLiftMotor.spin(fwd, 100, pct);
  this_thread::sleep_for(5000);
  toggleBackLift();
}
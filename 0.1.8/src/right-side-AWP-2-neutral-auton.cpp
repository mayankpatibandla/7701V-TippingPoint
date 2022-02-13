#include "vex.h"
#include "auton-functions.h"

//RIGHT AWP MAIN
void rightSideAWP2NeutralAuton(){
  fourBarMotors.setStopping(hold);
  //get yellow
  driveMotors.spin(fwd, 100, pct);
  toggleClaw();
  waitUntil(pt::x() > 43);
  toggleClaw();
  this_thread::sleep_for(20);
  leftMotors.spin(fwd, -85, pct);
  rightMotors.spin(fwd, -100, pct);
  fourBarMotors.spinFor(0.5, rev, 100, velocityUnits::pct, false);
  this_thread::sleep_for(50);
  driveMotors.spin(fwd, -100, pct);
  waitUntil(pt::x() < 28);
  fourBarMotors.stop(hold);
  driveMotors.stop(brake);
  driveMotors.setStopping(coast);

  //drop yellow
  timer waitTimer;
  turnToAngle(-M_PI_2-0.15, 800);
  driveRelative(11.5, 1400);
  toggleClaw();
  driveRelative(-12.5, 700);
  fourBarMotors.spin(fwd, -100, pct);
  waitTimer.reset();
  waitUntil(fourBarBottomLimit.pressing() || waitTimer.time(msec) > 500);

  //middle yellow
  turnToAngle(-0.58, 1000);
  driveRelative(49.5, 2250);
  toggleClaw();
  this_thread::sleep_for(15);
  fourBarMotors.spinFor(0.5, rev, 100, velocityUnits::pct, false);

  //alliance mogo
  turnToAngle(-0.95, 1200);
  backLiftMotor.spin(fwd, -100, pct);
  driveRelative(-62.5, 2500);
  backLiftMotor.spin(fwd, 100, pct);
  this_thread::sleep_for(300);
  ringLiftMotor.spin(fwd, 100, pct);
  turnToAngle(0.2, 500);
  driveRelative(-30, 1500);
  backLiftMotor.stop(hold);
  driveRelative(8, 500);
  ringLiftMotor.stop();
}

//RIGHT AWP OTHER
void rightSideAWP1NeutralAuton(){
  fourBarMotors.setStopping(hold);
  //get yellow
  driveMotors.spin(fwd, 100, pct);
  toggleClaw();
  waitUntil(pt::x() > 43);
  toggleClaw();
  this_thread::sleep_for(20);
  leftMotors.spin(fwd, -85, pct);
  rightMotors.spin(fwd, -100, pct);
  fourBarMotors.spinFor(0.5, rev, 100, velocityUnits::pct, false);
  this_thread::sleep_for(50);
  driveMotors.spin(fwd, -100, pct);
  waitUntil(pt::x() < 28);
  fourBarMotors.stop(hold);
  driveMotors.stop(brake);
  driveMotors.setStopping(coast);

  //alliance mogo
  backLiftMotor.spinFor(-0.7, rev, 100, velocityUnits::pct, false);
  turnToAngle(-M_PI_2-0.09, 1750);
  timer liftTimer;
  liftTimer.reset();
  waitUntil(backLiftMotor.position(deg) < -130 || liftTimer.time(msec) > 1750);
  driveRelative(-20, 1300);
  backLiftMotor.spin(fwd, 100, pct);
  this_thread::sleep_for(200);
  driveRelative(30, 1400);
  
  //drop yellow
  turnToAngle(-M_PI_2+1.05, 500);
  driveRelative(-25, 3000);
  ringLiftMotor.spin(fwd, 100, pct);
  fourBarMotors.spin(fwd, -100, pct);
  liftTimer.reset();
  waitUntil(fourBarBottomLimit.pressing() || liftTimer > 500);
  backLiftMotor.stop(hold);
  fourBarMotors.stop(coast);
  toggleClaw();
  this_thread::sleep_for(3000);
}
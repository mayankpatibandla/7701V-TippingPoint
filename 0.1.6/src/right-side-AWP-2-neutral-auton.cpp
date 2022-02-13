#include "vex.h"
#include "auton-functions.h"

void rightSideAWP2NeutralAuton(){
  fourBarLimit_task.resume();
  backLiftLimit_task.resume();

  //get yellow mogo
  toggleClaw();
  driveMotors.spin(fwd, 100, pct);
  waitUntil(pt::x() > 40);
  toggleClaw();
  driveMotors.stop();
  this_thread::sleep_for(15);
  fourBarMotors.spinFor(0.5, rev, 100, velocityUnits::pct, false);
  driveRelative(-26.25);

  //drop yellow mogo
  turnToAngle(-M_PI_2);
  driveRelative(17);
  toggleClaw();

  //get alliance mogo
  backLiftMotor.spin(fwd, -100, pct);
  driveRelative(-30, 1200);
  fourBarMotors.spinFor(-1, rev, 100, velocityUnits::pct, false);
  backLiftLimit_task.suspend();
  backLiftMotor.stop();
  backLiftMotor.spin(fwd, 100, pct);
  this_thread::sleep_for(250);

  //get other neutral mogo
  turnToPoint(55, -36);
  //put rings on
  ringLiftMotor.spin(fwd, 80, pct);
  goToPoint(55, -36, 3000);
  toggleClaw();
  ringLiftMotor.stop();
  this_thread::sleep_for(15);
  
  //go back
  turnToAngle(-1, 700);
  driveMotors.spin(fwd, -100, pct);
  this_thread::sleep_for(3000);
  driveMotors.stop();
}

void rightSideAWP1NeutralAuton(){
  fourBarLimit_task.resume();
  backLiftLimit_task.resume();

  //get yellow mogo
  toggleClaw();
  driveMotors.spin(fwd, 100, pct);
  waitUntil(pt::x() > 40);
  toggleClaw();
  driveMotors.stop();
  this_thread::sleep_for(15);
  fourBarMotors.spinFor(0.5, rev, 100, velocityUnits::pct, false);
  driveRelative(-26.25);

  //drop yellow mogo
  turnToAngle(-M_PI_2);
  driveRelative(17);
  toggleClaw();

  //get alliance mogo
  backLiftMotor.spin(fwd, -100, pct);
  driveRelative(-30, 1200);
  fourBarMotors.spinFor(-1, rev, 100, velocityUnits::pct, false);
  backLiftLimit_task.suspend();
  backLiftMotor.stop();
  backLiftMotor.spin(fwd, 100, pct);
  this_thread::sleep_for(250);

  driveRelative(12);
  ringLiftMotor.spin(fwd, 80, pct);
  this_thread::sleep_for(5000);
}
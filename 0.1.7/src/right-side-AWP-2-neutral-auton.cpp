#include "vex.h"
#include "auton-functions.h"

//RIGHT AWP MAIN
/*void rightSideAWP2NeutralAuton(){
  fourBarLimit_task.resume();
  backLiftLimit_task.resume();

  //get yellow mogo
  toggleClaw();
  driveMotors.spin(fwd, 100, pct);
  waitUntil(pt::x() > 45);
  toggleClaw();
  this_thread::sleep_for(15);
  fourBarMotors.spinFor(0.5, rev, 100, velocityUnits::pct, false);
  driveRelative(-29, 0, fwdPID_DEG_N, true);

  //drop yellow mogo
  turnToAngle(-1.15, 2200);
  driveRelative(15, 1500);
  toggleClaw();

  //dont get alliance mogo
  fourBarMotors.spin(fwd, -100, pct);
  this_thread::sleep_for(200);
  driveRelative(-15, 1200);

  //get other yellow mogo
  turnToPoint(40, -34);
  goToPoint(43.5, -37);
  //turnToAngle(-1.1, 1500);
  toggleClaw();
  this_thread::sleep_for(15);
  fourBarMotors.spinFor(0.5, rev, 100, velocityUnits::pct, false);
  turnToAngle(-0.9, 3000);
  driveRelative(-62, 6000);
  turnToAngle(2.5);
  fourBarMotors.spin(fwd, -100, pct);

  this_thread::sleep_for(2500);
}*/

void rightSideAWP2NeutralAuton(){
  fourBarMotors.setStopping(hold);
  //get yellow
  driveMotors.spin(fwd, 100, pct);
  toggleClaw();
  waitUntil(pt::x() > 45);
  toggleClaw();
  this_thread::sleep_for(20);
  driveMotors.spin(fwd, -100, pct);
  fourBarMotors.spinFor(1.25, rev, 100, velocityUnits::pct, false);
  waitUntil(pt::x() < 19.5);
  fourBarMotors.stop();
  driveMotors.stop();

  //alliance mogo
  turnToAngle(-M_PI_2, 2000);
  driveRelative(5, 1500);
  backLiftMotor.spin(fwd, -100, pct);
  timer ttTimer;
  ttTimer.reset();
  waitUntil(ttTimer.time(msec) > 2000 || backLiftMotor.position(deg) < -360);
  backLiftMotor.stop();
  driveRelative(-25, 2500);
  backLiftMotor.spin(fwd, 100, pct);
  ttTimer.reset();
  this_thread::sleep_for(300);
  driveRelative(2.5, 2000);
  waitUntil(ttTimer.time(msec) > 3500 || backLiftMotor.position(deg) > 0);
  backLiftMotor.stop();

  //rings
  ringLiftMotor.spin(fwd, 100, pct);
  turnToAngle(-M_PI_2 - 0.2, 2500);
  driveRelative(24, 3000);
  this_thread::sleep_for(5000);
  ringLiftMotor.stop();
}

//RIGHT AWP OTHER
void rightSideAWP1NeutralAuton(){
  fourBarLimit_task.resume();
  backLiftLimit_task.resume();

  //get yellow mogo
  toggleClaw();
  driveMotors.spin(fwd, 100, pct);
  waitUntil(pt::x() > 45);
  toggleClaw();
  this_thread::sleep_for(15);
  fourBarMotors.spinFor(0.5, rev, 100, velocityUnits::pct, false);
  driveRelative(-29, 2000);

  //drop yellow mogo
  turnToAngle(-1.15, 2200);
  driveRelative(15, 1500);
  toggleClaw();

  //get alliance mogo
  backLiftMotor.spin(fwd, -100, pct);
  fourBarMotors.spin(fwd, -100, pct);
  this_thread::sleep_for(200);
  driveRelative(-28, 1200);
  backLiftMotor.spin(fwd, 100, pct);
  timer backLiftTimer;
  backLiftTimer.reset();
  waitUntil(backLiftTopLimit.pressing() || backLiftTimer.time(msec) > 1500);
  backLiftMotor.stop();

  //put rings on
  ringLiftMotor.spin(fwd, 100, pct);
  this_thread::sleep_for(5000);
  ringLiftMotor.stop();

  this_thread::sleep_for(2500);
}
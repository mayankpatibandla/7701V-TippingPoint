#include "vex.h"
#include "auton-functions.h"

void twoAWPAuton(){
  timer autonTimer;
  autonTimer.reset();
  fourBarLimit_task.resume();
  backLiftLimit_task.resume();

  //drop rings in alliance mogo
  fourBarMotors.spin(fwd, 100, pct);
  this_thread::sleep_for(250);
  driveMotors.spinFor(0.2, sec, 100, velocityUnits::pct);
  toggleClaw();
  fourBarMotors.stop();

  /*//go back and turn
  driveMotors.spinFor(0.5, sec, -100, velocityUnits::pct);
  turnToAngle(-M_PI_2);
  driveRelative(19.35);
  turnToAngle(M_PI);

  //go to other mogo
  backLiftMotor.spinFor(-0.5, rev, 100, velocityUnits::pct, false);
  driveRelative(-100);
  backLiftLimit_task.suspend();
  backLiftMotor.spin(fwd, 100, pct);
  waitUntil(backLiftTopLimit.pressing());
  backLiftMotor.stop();
  driveMotors.spin(fwd, 100, pct);
  this_thread::sleep_for(300);
  driveMotors.stop();
  ringLiftMotor.spin(fwd, 80, pct);
  this_thread::sleep_for(2500);
  ringLiftMotor.stop();*/

  /*//pick up alliance mogo
  backLiftMotor.spin(fwd, -100, pct);
  waitUntil(backLiftMotor.position(deg) < - 275);
  driveMotors.spinFor(400, msec, -100, velocityUnits::pct);
  backLiftMotor.spin(fwd, 100, pct);
  this_thread::sleep_for(500);

  //turn
  goToPoint(4, pt::y(), 650);
  turnToAngle(M_PI_2);
  goToPoint(pt::x(), 28, 2000);
  turnToAngle(M_PI);

  //get second mogo
  fourBarMotors.spinFor(0.7, rotationUnits::rev, 100, velocityUnits::pct, false);
  ringLiftMotor.spin(fwd, 80, pct);
  goToPoint(-96, pt::y(), 6000);
  toggleClaw();
  driveMotors.spin(fwd, -100, pct);
  waitUntil(pt::x() > -93);
  fourBarMotors.spin(fwd, -100, pct);
  driveRelative(-3);
  waitUntil(fourBarBottomLimit.pressing());
  driveMotors.spin(forward, 100, pct);
  this_thread::sleep_for(750);
  toggleClaw();
  ringLiftMotor.stop();
  Controller.Screen.clearLine(3);
  Controller.Screen.print(autonTimer.time(msec));
  driveRelative(-15);*/
}
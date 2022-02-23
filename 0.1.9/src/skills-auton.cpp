#include "vex.h"
#include "auton-functions.h"

void skillsAuton(){
  PID slowFWD(0.13);

  //alliance goal 1
  fourBarMotors.setStopping(hold);
  backLiftMotor.spin(fwd, -100, pct);
  waitUntil(backLiftMotor.position(deg) < -135);
  driveMotors.spinFor(880, msec, -65, velocityUnits::pct);

  backLiftMotor.spin(fwd, 100, pct);
  this_thread::sleep_for(600);
  driveMotors.setTimeout(1700, msec);
  driveMotors.spinFor(1, rev, 30, velocityUnits::pct);
  ringLiftMotor.spin(fwd, 100, pct);
  driveMotors.setTimeout(0, sec);

  turnToAngle(M_PI_2 + 0.3, 3000);
  toggleClaw();
  ringLiftMotor.stop();

  //yellow 1
  driveRelative(56, 3000, slowFWD);
  toggleClaw();

  fourBarMotors.spin(fwd, 100, pct);
  turnToAngle(2.6, 2000);
  driveMotors.setTimeout(2250, msec);
  driveRelative(42, 2250, slowFWD);
  waitUntil(fourBarTopLimit.pressing());
  fourBarMotors.stop(hold);
  turnToAngle(M_PI_2);

  //stack yellow 1
  driveRelative(12, 900);
  fourBarMotors.spinFor(-1, rev, -100, velocityUnits::pct, false);
  timer waitTimer;
  waitTimer.reset();
  waitUntil(fourBarMotors.isDone() || waitTimer.time(msec) > 1500);
  fourBarMotors.stop();
  toggleClaw();
  this_thread::sleep_for(300);
  fourBarMotors.spin(fwd, 100, pct);
  waitUntil(fourBarTopLimit.pressing());

  //get alliance 1 in front
  driveRelative(-12, 1500, slowFWD);
  turnToAngle(3.08);
  fourBarMotors.spin(fwd, -100, pct);
  backLiftMotor.spinFor(1500, msec, -100, velocityUnits::pct);
  driveRelative(18, 1500, slowFWD);
  backLiftMotor.spin(fwd, 75, pct);
  fourBarMotors.stop();
  turnToAngle(-0.125, 1500);
  backLiftMotor.stop();
  driveRelative(23.5, 1500, slowFWD);
  toggleClaw();

  //stack alliance 1
  fourBarMotors.spin(fwd, 100, pct);
  driveRelative(-6, 800);
  waitUntil(fourBarTopLimit.pressing());
  turnToAngle(M_PI_2 + 0.15);
  driveRelative(15, 1800, slowFWD);
  toggleClaw();

  //tall yellow
  driveRelative(-12, 1500, slowFWD);
  fourBarMotors.spin(fwd, -100, pct);
  turnToAngle(-M_PI_2 +0.15);
  waitUntil(fourBarBottomLimit.pressing());
  fourBarMotors.stop();
  driveRelative(30, 2000, slowFWD);
  toggleClaw();
  fourBarMotors.spin(fwd, 100, pct);
  waitUntil(fourBarTopLimit.pressing());
  fourBarMotors.stop(hold);
  turnToAngle(-M_PI_2);
  driveRelative(65, 3000, slowFWD);

  //stack tall yellow
  fourBarMotors.spinFor(-0.5, rev, -100, velocityUnits::pct, false);
  waitTimer.reset();
  waitUntil(waitTimer.time(msec) > 1500);
  toggleClaw();
  this_thread::sleep_for(500);
  driveRelative(-24, 3000, slowFWD);

  //yellow 3
  turnToAngle(M_PI_2+0.875);
  fourBarMotors.spin(fwd, -100, pct);
  backLiftMotor.spin(fwd, -100, pct);
  waitUntil(fourBarBottomLimit.pressing());
  fourBarMotors.stop();
  backLiftMotor.stop();
  driveRelative(40, 2600, slowFWD);
  toggleClaw();
  fourBarMotors.spin(fwd, 100, pct);
  this_thread::sleep_for(25);

  //stack yellow 3
  turnToAngle(1.25);
  driveRelative(52, 2500);
  toggleClaw();
  driveRelative(-6, 500);

  this_thread::sleep_for(2500);
}
#include "vex.h"
#include "auton-functions.h"

void skillsAuton(){
  PID slowFWD(0.1);

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

  turnToAngle(M_PI_2 + 0.2, 3000);
  toggleClaw();

  driveRelative(60, 3000, slowFWD);
  toggleClaw();
  ringLiftMotor.stop();

  fourBarMotors.spin(fwd, 100, pct);
  turnToAngle(2.185, 2000);
  driveMotors.setTimeout(2250, msec);
  driveMotors.spinFor(5, rev, 50, velocityUnits::pct, false);
  waitUntil(fourBarTopLimit.pressing());
  fourBarMotors.stop(hold);

  timer waitTimer;
  waitTimer.reset();
  waitUntil(driveMotors.isDone() || waitTimer.time(msec) > 2000);
  driveMotors.setTimeout(0, sec);
  fourBarMotors.spinFor(-1, rev, -100, velocityUnits::pct, false);
  waitTimer.reset();
  waitUntil(fourBarMotors.isDone() || waitTimer.time(msec) > 1500);
  fourBarMotors.stop();
  toggleClaw();
  this_thread::sleep_for(300);
  fourBarMotors.spin(fwd, 100, pct);
  waitUntil(fourBarTopLimit.pressing());

  driveRelative(-12, 1500, slowFWD);
  turnToAngle(3.08);
  fourBarMotors.spin(fwd, -100, pct);
  backLiftMotor.spinFor(1500, msec, -100, velocityUnits::pct);
  driveRelative(25, 1500, slowFWD);
  backLiftMotor.spin(fwd, 75, pct);
  fourBarMotors.stop();
  turnToAngle(-0.125, 1500);
  backLiftMotor.stop();
  driveRelative(30, 1500, slowFWD);
  toggleClaw();

  fourBarMotors.spin(fwd, 100, pct);
  waitUntil(fourBarTopLimit.pressing());
  turnToAngle(M_PI_2 + 0.15);
  driveRelative(15, 2000, slowFWD);
  toggleClaw();

  driveRelative(-12, 1500, slowFWD);
  fourBarMotors.spin(fwd, -100, pct);
  turnToAngle(-M_PI_2 - 0.4);
  driveRelative(30, 2000, slowFWD);
  fourBarMotors.stop();
  toggleClaw();
  fourBarMotors.spin(fwd, 100, pct);
  waitUntil(fourBarTopLimit.pressing());
  fourBarMotors.stop(hold);
  turnToAngle(-M_PI_2);
  driveRelative(65, 5000, slowFWD);

  fourBarMotors.spinFor(-0.5, rev, -100, velocityUnits::pct, false);
  waitTimer.reset();
  waitUntil(waitTimer.time(msec) > 1500);
  toggleClaw();
  this_thread::sleep_for(500);
  driveRelative(-24, 5000, slowFWD);
  


  this_thread::sleep_for(2500);
}
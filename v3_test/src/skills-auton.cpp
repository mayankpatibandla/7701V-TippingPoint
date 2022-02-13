#include "vex.h"
#include "auton-functions.h"
/*
void skillsAuton(){
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
  turnToAngle(-M_PI_2, 500);
  ringLiftMotor.spin(fwd, 100, pct);
  fourBarMotors.spin(fwd, -100, pct);
  liftTimer.reset();
  waitUntil(fourBarBottomLimit.pressing() || liftTimer > 500);
  backLiftMotor.stop(hold);
  fourBarMotors.stop(coast);
  toggleClaw();

  //middle yellow
  driveRelative(-26, 1500);
  turnToAngle(-0.52375, 750);
  driveRelative(49.5, 2250);
  toggleClaw();
  this_thread::sleep_for(15);
  fourBarMotors.spinFor(0.5, rev, 100, velocityUnits::pct, false);
  driveMotors.spin(fwd, 100, pct);
  timer aTimer;
  aTimer.reset();
  waitUntil(std::hypot(pt::x(), pt::y()) > 150 || aTimer.time(msec) > 4500);
  driveMotors.stop();
}*/
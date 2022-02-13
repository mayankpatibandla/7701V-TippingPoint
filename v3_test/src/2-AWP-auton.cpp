#include "vex.h"
#include "auton-functions.h"
/*
//LEFT AWP OTHER
void twoAWPAuton(){
  fourBarMotors.setStopping(hold);
  //drop rings in alliance mogo
  fourBarMotors.spin(fwd, 100, pct);
  this_thread::sleep_for(250);
  driveMotors.spinFor(0.275, sec, 100, velocityUnits::pct);
  toggleClaw();
  fourBarMotors.stop();
  driveMotors.spin(fwd, -50, pct);
  waitUntil(pt::x() < -4);
  driveMotors.stop();

  //get yellow
  fourBarMotors.spin(fwd, -100, pct);
  timer fourBarTimer;
  fourBarTimer.reset();
  if(fourBarBottomLimit.pressing())fourBarMotors.stop();
  turnToAngle(-M_PI_2 + 0.275);
  if(fourBarBottomLimit.pressing())fourBarMotors.stop();
  driveMotors.spin(fwd, 100, pct);
  waitUntil(fourBarBottomLimit.pressing() || fourBarTimer.time(msec) > 900);
  fourBarMotors.stop();
  waitUntil(pt::y() < - 50);
  toggleClaw();
  driveMotors.stop();
  this_thread::sleep_for(15);
  fourBarMotors.spinFor(0.5, rev, 100, velocityUnits::pct, false);
  driveMotors.spin(fwd, -100, pct);
  timer driveTimer;
  driveTimer.reset();
  waitUntil(pt::y() > -5 || driveTimer.time(msec) > 3000);
  driveMotors.stop();
}*/
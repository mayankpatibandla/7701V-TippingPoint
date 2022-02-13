#include "vex.h"
#include "auton-functions.h"

void skillsAuton(){
  fourBarLimit_task.resume();
  //yellow 1
  toggleClaw();
  goToPoint(51, 0, 3000);
  toggleClaw();
  this_thread::sleep_for(150);
  fourBarMotors.spinFor(3, rev, 100, velocityUnits::pct, false);

  //alliance mogo
  turnToAngle(-0.44, 2000);
  /*backLiftMotor.setTimeout(5, sec);
  backLiftMotor.spinFor(-1.25, rev, 100, velocityUnits::pct, false);
  driveRelative(-30, 5000);
  backLiftMotor.setTimeout(5, sec);
  backLiftMotor.spinFor(1.3, rev, 100, velocityUnits::pct, false);*/

  //stack yellow 1
  driveRelative(50, 4000);
  fourBarLimit_task.suspend();
  fourBarMotors.spinFor(700, msec, -100, velocityUnits::pct);
  toggleClaw();
  fourBarMotors.spinFor(700, msec, 100, velocityUnits::pct);
  driveRelative(-5, 2000);

  //get yellow 2
  turnToPoint(49, -74, 6000);
  fourBarMotors.spin(fwd, -100, pct);
  timer tTTtimer;
  tTTtimer.reset();
  waitUntil(fourBarBottomLimit.pressing() || tTTtimer.time() > 5000);
  turnToPoint(49, -74, 6000);
  driveRelative(45, 4000);
  toggleClaw();

  this_thread::sleep_for(5000);
}
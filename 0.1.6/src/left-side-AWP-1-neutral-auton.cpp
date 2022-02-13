#include "vex.h"
#include "auton-functions.h"

void leftSideAWP1NeutralAuton(){
  //get yellow mogo
  toggleClaw();
  driveMotors.spin(fwd, 100, pct);
  waitUntil(pt::x() > 44);
  toggleClaw();
  driveMotors.stop();
  this_thread::sleep_for(15);
  //driveRelative(-7, 750);
  fourBarMotors.spinFor(0.45, rev, 100, velocityUnits::pct, false);
  driveRelative(-35);
  /*turnToAngle(0.3);
  driveRelative(-26);

  //get alliance mogo
  backLiftMotor.spin(fwd, -100, pct);
  turnToAngle(-0.838);
  waitUntil(backLiftBottomLimit.pressing());
  driveRelative(-11);
  backLiftMotor.spin(fwd, 100, pct);
  waitUntil(backLiftTopLimit.pressing());

  //put rigns on
  ringLiftMotor.spin(fwd, 80, pct);
  this_thread::sleep_for(6500);*/
}
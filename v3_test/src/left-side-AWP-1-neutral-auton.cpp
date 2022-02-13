#include "vex.h"
#include "auton-functions.h"
/*
//LEFT AWP MAIN
void leftSideAWP1NeutralAuton(){
  //get yellow mogo
  toggleClaw();
  driveMotors.spin(fwd, 100, pct);
  waitUntil(pt::x() > 47);
  toggleClaw();
  driveMotors.stop();
  this_thread::sleep_for(15);
  fourBarMotors.spinFor(0.5, rev, 100, velocityUnits::pct, false);
  driveRelative(-48, 3000);
}*/
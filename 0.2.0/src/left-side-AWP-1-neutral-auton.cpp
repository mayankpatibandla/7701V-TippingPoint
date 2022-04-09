#include "vex.h"
#include "auton-functions.h"

//LEFT AWP MAIN
void leftSideAWP1NeutralAuton(){
  //get alliance mogo in back
  toggleBackLift();
  driveMotors.spin(fwd, -40, pct);
  this_thread::sleep_for(950);
  toggleBackLift();
  this_thread::sleep_for(100);
  driveRelative(28, 1100, slowFwd);

  //get first short yellow
  turnToAngle(-M_PI_2-M_PI_4 + 0.35); //+0.45
  ringLiftMotor.spin(fwd, 12, volt);
  toggleClaw();
  driveRelative(51, 1800, slowFwd);
  driveMotors.stop();
  toggleClaw();
  this_thread::sleep_for(50);
  fourBarMotor.spin(fwd, 100, pct);
  driveMotors.spin(fwd, -50, pct);
  this_thread::sleep_for(100);
  fourBarMotor.stop();
  driveRelative(-40, 3000);
  toggleBackLift();
}
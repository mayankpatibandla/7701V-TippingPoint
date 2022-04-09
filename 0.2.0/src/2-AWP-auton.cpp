#include "vex.h"
#include "auton-functions.h"

//LEFT AWP OTHER
void twoAWPAuton(){
  toggleClaw();
  driveMotors.spin(fwd, 12, volt);
  waitUntil(pt::x() > 52);
  driveMotors.stop();
  this_thread::sleep_for(50);
  toggleClaw();
  this_thread::sleep_for(50);
  driveMotors.spin(fwd, -12, volt);
  this_thread::sleep_for(2500);
  driveMotors.stop();
}
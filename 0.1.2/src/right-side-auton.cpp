#include "robot-config.h"
#include "position-tracking.h"
#include "auton-functions.h"

using namespace vex;

void rightSideAuton(){
  double fourBarHeight = 0.45;
  //raise 4 bar
  fourBarMotors.spinFor(fwd, fourBarHeight, rev, 100, velocityUnits::pct, false);
  //go to mogo
  driveMotors.spin(fwd, 30, pct);
  while(positionTracking::getX() < 15){
    wait(10, msec);
  }
  driveMotors.stop();
  wait(50, msec);
  //drop rings
  toggleClaw();
  wait(0.5, sec);
  //go back and drop 4 bar
  driveMotors.spin(reverse, 30, pct);
  while(positionTracking::getX() > 8.5){
    wait(10, msec);
  }
  driveMotors.stop();
  fourBarMotors.setTimeout(3000, msec);
  fourBarMotors.spinFor(reverse, fourBarHeight + 0.1, rev, 100, velocityUnits::pct);
  fourBarMotors.setTimeout(0, msec);
  //go forward and grab mogo
  driveMotors.spin(fwd, 30, pct);
  while(positionTracking::getX() < 15){
    wait(10, msec);
  }
  driveMotors.stop();
  toggleClaw();
  //go back
  //if(av == AWP){
    driveMotors.spin(reverse, 30, pct);
    while(positionTracking::getX() > 3){
      wait(10, msec);
    }
    driveMotors.stop();
  //}
}
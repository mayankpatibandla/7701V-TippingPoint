#include "robot-config.h"
#include "position-tracking.h"
#include "auton-functions.h"

using namespace vex;

namespace pt = positionTracking;

void leftSideAWPAuton(){
  //move 4bar up and drop rings
  fourBarMotors.spinFor(fwd, 0.75, rev, 100, velocityUnits::pct);
  driveMotors.spinFor(fwd, 0.5, sec, 50, velocityUnits::pct);
  toggleClaw();

  //go back and face the mogo
  driveMotors.spinFor(fwd, 0.5, sec, -100, velocityUnits::pct);
  fourBarMotors.spin(fwd, -50, pct);
  turnToPoint(17.5, -56);
  fourBarMotors.stop();

  //go to and grab the mogo
  double target = -56;
  while(pt::getY() > target){
    double kP = 6;
    double error = target - pt::getY();
    double pow = error * kP;
    if(pow > -15) break;
    driveMotors.spin(fwd, -pow, pct);
  }
  driveMotors.stop();
  toggleClaw();

  //go back
  driveMotors.spin(fwd, -100, pct);
  wait(3.5, sec);
  driveMotors.stop();
}

void leftSideNeutralAuton(){
  //go to yellow mogo and open claw on the way
  double target = 58;
  bool clawNotOpened = true;
  while(pt::getX() < target){
    double kP = 6;
    double error = target - pt::getX();
    double pow = error * kP;
    if(pow < 15) break;
    driveMotors.spin(fwd, pow, pct);
    
    if(clawNotOpened){
      toggleClaw();
      clawNotOpened = false;
    }
  }
  driveMotors.stop();

  //grab mogo
  toggleClaw();
  wait(0.5, sec);

  //go back
  driveMotors.spin(fwd, -100, pct);
  wait(3, sec);
  driveMotors.stop();
}
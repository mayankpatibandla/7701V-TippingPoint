#include "robot-config.h"
#include "position-tracking.h"
#include "auton-functions.h"

using namespace vex;

void leftSideAuton(){
  double fourBarHeight = 0.55;
  //raise 4 bar
  fourBarMotors.spinFor(fwd, fourBarHeight, rev, 100, velocityUnits::pct);
  //go to mogo
  driveMotors.spin(fwd, 30, pct);
  while(positionTracking::getX() < 5.75){
    wait(10, msec);
  }
  driveMotors.stop();
  wait(1000, msec);
  //drop rings
  toggleClaw();
  wait(0.25, sec);
  //go back
  driveMotors.spin(reverse, 40, pct);
  while(positionTracking::getX() > 0){
    wait(10, msec);
  }
  driveMotors.stop();
  wait(0.1, sec);
  //drop 4 bar
  fourBarMotors.setTimeout(1500, msec);
  fourBarMotors.spinFor(reverse, fourBarHeight + 0.1, rev, 100, velocityUnits::pct);
  fourBarMotors.setTimeout(0, msec);
  wait(0.1, sec);

  //if(av == PLATFORM){
    //grab mogo
    driveMotors.spin(fwd, 30, pct);
    while(positionTracking::getX() < 6.75){
      wait(10, msec);
    }
    driveMotors.stop();
    wait(0.1, sec);
    toggleClaw();
    wait(0.25, sec);
    //raise 4 bar
    fourBarMotors.setTimeout(5000, msec);
    fourBarMotors.spinFor(fwd, 1, rev, 100, velocityUnits::pct, false);
    fourBarMotors.setTimeout(0, msec);
    wait(1, sec);
    //drive forward
    driveMotors.spin(fwd, 100, pct);
    wait(550, msec);
    toggleClaw();
    wait(0.25, sec);
    //go back
    driveMotors.spin(reverse, 50, pct);
    while(positionTracking::getX() > 4.5){
      wait(10, msec);
    }
    driveMotors.stop();
    wait(0.1, sec);
    //drop 4 bar and tilter
    fourBarMotors.spinFor(fwd, 1.5, sec, -100, velocityUnits::pct);
    //tilterMotors.spin(fwd, -10, pct);
    fourBarMotors.stop();
    //tilterMotors.stop();
  //}


/*
  driveMotors.spin(fwd, 100, pct);
  wait(0.3, sec);
  driveMotors.stop();

  while(inertialSensor.rotation(deg) > -55){
    rightMotors.spin(fwd, 30, pct);
    leftMotors.spin(fwd, -30, pct);
  }
  driveMotors.stop();

  driveMotors.spin(fwd, 100, pct);
  wait(1.3, sec);
  driveMotors.stop();

  toggleClaw();
  driveMotors.spin(fwd, -100, pct);
  wait(5, sec);
  driveMotors.stop();*/
}
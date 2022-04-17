#include "vex.h"
#include "auton-functions.h"

//RIGHT AWP MAIN
void rightSideAWP2NeutralAuton(){
  //get yellow
  driveMotors.spin(fwd, 12, volt);
  toggleClaw();
  waitUntil(pt::x() > 45);
  driveMotors.stop();
  this_thread::sleep_for(25);
  toggleClaw();
  this_thread::sleep_for(25);
  fourBarMotor.spin(fwd, 12, volt);
  driveMotors.spin(fwd, -12, volt);
  this_thread::sleep_for(100);
  fourBarMotor.stop(hold);
  waitUntil(pt::x() < 5);
  driveMotors.stop();

  //get alliance goal
  fourBarMotor.spin(fwd, 12, volt);
  driveMotors.spin(fwd, 50, pct);
  waitUntil(pt::x() > 10.25);
  driveMotors.stop();
  waitUntil(fourBarRotationSensor.angle() > fourBarMaxPos - 10);
  fourBarMotor.stop();
  turnToAngle(M_PI_2);
  toggleBackLift();
  driveMotors.spinFor(2, sec, -35, velocityUnits::pct);
  toggleBackLift();
  this_thread::sleep_for(50);
  driveRelative(5, 1000);

  //get rings
  turnToAngle(0);
  ringLiftMotor.spin(fwd, 12 * 0.925, volt);
  driveMotors.spin(fwd, 30, pct);
  waitUntil(pt::x() > 51);
  driveMotors.stop();
  this_thread::sleep_for(10);
  driveMotors.spin(fwd, -100, pct);
  waitUntil(pt::x() < 5);
  driveMotors.stop();
  this_thread::sleep_for(300);
  
  //match loads
  /*turnToAngle(M_PI);

  for(int i = 0; i < 3; i++){
    driveMotors.spinFor(2750, msec, 40, velocityUnits::pct);
    driveMotors.spinFor(2200, msec, -35, velocityUnits::pct);
  }

  driveRelative(20, 2000);
  toggleBackLift();*/

  toggleBackLift();
  this_thread::sleep_for(100);
  driveRelative(6, 1000);
}

//RIGHT AWP OTHER
void rightSideAWP1NeutralAuton(){
  toggleBackLift();
  driveMotors.spin(fwd, -7.5, volt);
  this_thread::sleep_for(1200);
  driveMotors.stop();
  this_thread::sleep_for(75);
  toggleBackLift();
  this_thread::sleep_for(200);
  driveMotors.spin(fwd, 6, volt);
  this_thread::sleep_for(2000);
  driveMotors.stop();
  ringLiftMotor.spin(fwd, 100, pct);
  this_thread::sleep_for(5000);
  toggleBackLift();
}
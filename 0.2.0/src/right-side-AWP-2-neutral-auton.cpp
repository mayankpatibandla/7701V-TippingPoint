#include "vex.h"
#include "auton-functions.h"

//RIGHT AWP MAIN
//RIGHT 1 Yellow + line of rings
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
  turnToAngle(M_PI_2, 900);
  //visionTurn();
  waitUntil(fourBarRotationSensor.angle() > fourBarMaxPos - 25);
  fourBarMotor.stop();
  toggleBackLift();
  driveMotors.spinFor(2, sec, -50, velocityUnits::pct);
  toggleBackLift();
  this_thread::sleep_for(50);
  driveRelative(4, 800);

  //get rings
  turnToAngle(0, 800);
  ringLiftMotor.spin(fwd, 12 * 0.925, volt);
  driveMotors.spin(fwd, 45, pct);
  waitUntil(pt::x() > 51);
  driveMotors.stop();
  this_thread::sleep_for(10);
  driveMotors.spin(fwd, -100, pct);
  waitUntil(pt::x() < 8);
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
//3 goal
void rightSideAWP1NeutralAuton(){
  //get first yellow
  driveMotors.spin(fwd, 12, volt);
  toggleClaw();
  this_thread::sleep_for(300);
  waitUntil(pt::x() > 45 || 
    (distanceSensor.isObjectDetected() && 
    (
      distanceSensor.objectDistance(inches)) <= 7.25 &&
      distanceSensor.objectDistance(inches) > 0
    )
  );
  driveMotors.stop();
  this_thread::sleep_for(25);
  toggleClaw();
  this_thread::sleep_for(25);
  fourBarMotor.spin(fwd, 12, volt);
  driveMotors.spin(fwd, -12, volt);
  this_thread::sleep_for(100);
  fourBarMotor.stop(hold);
  waitUntil(pt::x() < 15);
  driveMotors.stop();
  turnToAngle(-M_PI_2-1, 900);
  toggleClaw();

  //drop first yellow
  /*driveMotors.spin(fwd, 50, pct);
  waitUntil(pt::x() > 10.25);
  driveMotors.stop();
  turnToAngle(M_PI_2, 1000);
  fourBarMotor.spin(fwd, -12, volt);
  waitUntil(fourBarRotationSensor.angle(deg) < fourBarMinPos + 3.5);
  fourBarMotor.stop(hold);
  driveRelative(15, 1000);
  toggleClaw();
  this_thread::sleep_for(75);
  driveRelative(-14, 1000);*/

  //get tall yellow
  driveRelative(-5, 300);
  turnToAngle(M_PI_4, 700);
  driveRelative(12, 700);
  visionTurn(FRONTVISION, FRONT_YELLOWMOGO, 1150);
  driveRelative(38, 2000, verySlowFwd);
  toggleClaw();
  fourBarMotor.spin(fwd, 12, volt);
  this_thread::sleep_for(25);
  driveMotors.spin(fwd, -12, volt);
  this_thread::sleep_for(75);
  fourBarMotor.stop(hold);
  toggleBackLift();
  turnToAngle(M_PI_4 + 0.09, 2000);
  driveRelative(-50, 2750);
  visionTurn(BACKVISION, BACK_BLUEMOGO, 1000);
  driveRelative(-24, 1200);
  toggleBackLift();
  this_thread::sleep_for(50);
  ringLiftMotor.spin(fwd, 12, volt);
  turnToAngle(0, 1250);
  driveRelative(-10, 1000);
  toggleBackLift();
}
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
  timer autonTimer;
  autonTimer.reset();
  //get first yellow
  driveMotors.spin(fwd, 12, volt);
  toggleClaw();
  this_thread::sleep_for(300);
  waitUntil(pt::x() > 45 || 
    (distanceSensor.isObjectDetected() && 
    (
      distanceSensor.objectDistance(inches)) <= 3.75 &&
      distanceSensor.objectDistance(inches) > 0
    )
  );
  this_thread::sleep_for(25);
  toggleClaw();
  this_thread::sleep_for(25);
  driveMotors.stop();
  fourBarMotor.spin(fwd, 12, volt);
  driveMotors.spin(fwd, -12, volt);
  this_thread::sleep_for(100);
  fourBarMotor.stop(hold);
  waitUntil(pt::x() < 15);
  driveMotors.stop();
  turnToAngle(M_PI_2+1.2, 900);
  toggleClaw();

  //get tall yellow
  driveRelative(-5, 300);
  turnToAngle(M_PI_4+0.05, 700);
  fourBarMotor.spin(fwd, -12, volt);
  driveRelative(12, 700);
  rightMotors.spin(fwd, -9, volt);
  leftMotors.spin(fwd, 9, volt);
  this_thread::sleep_for(200);
  visionTurn(FRONTVISION, FRONT_YELLOWMOGO, 1500);
  fourBarMotor.stop(hold);
  //driveRelative(34, 2000, verySlowFwd);
  driveRelative(20, 1200);
  visionTurn(FRONTVISION, FRONT_YELLOWMOGO, 400);
  driveRelative(15, 1000, verySlowFwd);
  rightMotors.spin(fwd, 6, volt);
  this_thread::sleep_for(75);
  toggleClaw();
  driveMotors.stop(coast);
  this_thread::sleep_for(25);
  driveMotors.spin(fwd, -12, volt);
  this_thread::sleep_for(75);
  toggleBackLift();
  //turnToAngle(M_PI_4 + 0.09, 2000);
  driveRelative(-45, 2500);
  fourBarMotor.spin(fwd, 12, volt);
  turnToAngle(M_PI_2, 600);
  if(tc == BLUE)
    visionTurn(BACKVISION, BACK_BLUEMOGO, 1500);
  else if(tc == RED)
    visionTurn(BACKVISION, BACK_REDMOGO, 1500);
  fourBarMotor.stop(hold);
  driveRelative(-24, 1500);
  toggleBackLift();
  this_thread::sleep_for(50);
  ringLiftMotor.spin(fwd, 12, volt);
  if(autonTimer.time(msec) < 12000){
    driveRelative(8, 500);
    turnToAngle(0, 1250);
    driveMotors.spin(fwd, 7.5, volt);
    waitUntil(pt::x() > 45 || autonTimer.time(msec) > 14000);
    driveMotors.spin(fwd, -12, volt);
    waitUntil(pt::x() < 8 || autonTimer.time(msec) > 14800);
    driveMotors.stop();
    toggleBackLift();
  }
  else{
    if(pt::thetaWrapped() > 0 && pt::x() > 8)
      driveRelative(24, 2500);
    else if(pt::x() >= 8)
      driveRelative(24, 2500);
    waitUntil(autonTimer.time(msec) > 14700);
    toggleBackLift();
  }
}
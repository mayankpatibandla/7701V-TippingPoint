#include "vex.h"
#include "auton-functions.h"

//RIGHT AWP MAIN
//RIGHT 1 Yellow + line of rings
void rightSideAWP2NeutralAuton(){
  timer autonTimer;
  //const double goalDistance = 4;
  //get first yellow
  driveMotors.spin(fwd, 12, volt);
  toggleClaw();
  //this_thread::sleep_for(400);
  /*waitUntil(pt::x() > 45 || 
    ((
      distanceSensor.isObjectDetected() && 
      distanceSensor.objectDistance(inches) <= goalDistance &&
      distanceSensor.objectDistance(inches) > 0
    ) && pt::x() > 43)
  );*/
  waitUntil(pt::x() > 36);
  toggleClaw();
  this_thread::sleep_for(15);
  fourBarMotor.spin(fwd, 12, volt);
  driveMotors.spin(fwd, -12, volt);
  this_thread::sleep_for(100);
  fourBarMotor.stop(hold);
  waitUntil(pt::x() < 5);
  driveMotors.stop();
  //get yellow
  /*driveMotors.spin(fwd, 12, volt);
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
  driveMotors.stop();*/

  //get alliance goal
  fourBarMotor.spin(fwd, 12, volt);
  driveMotors.spin(fwd, 50, pct);
  waitUntil(pt::x() > 10.25);
  driveMotors.stop();
  fourBarMotor.stop(hold);
  turnToAngle(M_PI_2, 900);
  //visionTurn();
  toggleBackLift();
  driveMotors.spinFor(2, sec, -50, velocityUnits::pct);
  toggleBackLift();
  this_thread::sleep_for(50);
  driveRelative(4, 800);

  //get rings
  turnToAngle(0, 1200);
  ringLiftMotor.spin(fwd, 12 * 0.925, volt);
  driveMotors.spin(fwd, 45, pct);
  waitUntil(pt::x() > 51 || autonTimer.time(msec) > 13500);
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
  fourBarMotor.spin(fwd, -12, volt);
  driveRelative(3, 1000);
}

//RIGHT AWP OTHER
//3 goal
void rightSideAWP1NeutralAuton(){
  timer autonTimer;
  //const double goalDistance = 4;
  //get first yellow
  driveMotors.spin(fwd, 12, volt);
  toggleClaw();
  //this_thread::sleep_for(400);
  /*waitUntil(pt::x() > 45 || 
    ((
      distanceSensor.isObjectDetected() && 
      distanceSensor.objectDistance(inches) <= goalDistance &&
      distanceSensor.objectDistance(inches) > 0
    ) && pt::x() > 43)
  );*/
  waitUntil(pt::x() > 36);
  toggleClaw();
  this_thread::sleep_for(15);
  fourBarMotor.spin(fwd, 12, volt);
  driveMotors.spin(fwd, -12, volt);
  this_thread::sleep_for(100);
  fourBarMotor.stop(hold);
  waitUntil(pt::x() < 15);
  driveMotors.stop();
  turnToAngle(M_PI_2+1, 900);
  toggleClaw();

  //get tall yellow
  fourBarMotor.spin(fwd, -12, volt);
  driveRelative(-5, 300);
  turnToAngle(M_PI_4, 700);
  driveRelative(12, 700);
  fourBarMotor.stop();
  turnToAngle(M_PI_4-0.15, 800);
  visionTurn(FRONTVISION, FRONT_YELLOWMOGO, 1300);
  /*driveRelative(20, 1500);
  visionTurn(FRONTVISION, FRONT_YELLOWMOGO, 400);
  driveRelative(20.5, 1100, verySlowFwd);*/
  driveRelative(41, 2000, verySlowFwd);
  leftMotors.spin(fwd, 4.5, volt);
  rightMotors.spin(fwd, 6, volt);
  this_thread::sleep_for(150);
  toggleClaw();
  driveMotors.stop();
  this_thread::sleep_for(25);
  fourBarMotor.spin(fwd, 12, volt);
  this_thread::sleep_for(25);
  driveMotors.spin(fwd, -12, volt);
  this_thread::sleep_for(75);
  toggleBackLift();
  turnToAngle(0, 1200);
  fourBarMotor.stop(hold);

  driveMotors.spin(fwd, -6, volt);
  waitUntil(pt::x() < 19);
  driveMotors.stop();
  turnToAngle(M_PI_2, 1100);
  driveRelative(-20, 1250);

  //driveRelative(-45, 2750, slowFwd);
  //turnToAngle(M_PI_4+0.15, 200);
  if(tc == BLUE){
    visionTurn(BACKVISION, BACK_BLUEMOGO, 1200);
  }
  else if(tc == RED){
    visionTurn(BACKVISION, BACK_REDMOGO, 1200);
  }
  this_thread::sleep_for(150);
  driveRelative(-25, 800);
  this_thread::sleep_for(150);
  toggleBackLift();
  this_thread::sleep_for(50);
  fourBarMotor.stop(hold);
  ringLiftMotor.spin(fwd, 12, volt);

  //if(autonTimer.time(msec) > 13500){
    turnToAngle(0, 700);
    fourBarMotor.spin(fwd, -12, volt);
    driveMotors.spin(fwd, -6, volt);
    waitUntil(pt::x() < 3);
    toggleBackLift();
  /*}
  else{
    turnToAngle(M_PI_2, 500);
    this_thread::sleep_for(150);
    driveRelative(4, 300, verySlowFwd);
    this_thread::sleep_for(150);
    turnToAngle(0, 1100);
    driveMotors.spin(fwd, 7.5, volt);
    waitUntil(autonTimer.time(msec) > 14000 || pt::x() > 45);
    driveMotors.spin(fwd, -12, volt);
    waitUntil(autonTimer.time(msec) > 14930);
    driveMotors.stop();
    this_thread::sleep_for(30);
    toggleBackLift();
  }*/
}
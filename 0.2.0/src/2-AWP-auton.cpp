#include "vex.h"
#include "auton-functions.h"

//LEFT AWP OTHER
//left get 1 yellow
void twoAWPAuton(){
  timer autonTimer;
  toggleClaw();
  driveMotors.spin(fwd, 12, volt);
  this_thread::sleep_for(25);
  togglePreload();
  driveRelative(47, 1000);
  this_thread::sleep_for(50);
  toggleClaw();
  fourBarMotor.spin(fwd, 12, volt);
  this_thread::sleep_for(25);
  fourBarMotor.stop(hold);
  driveRelative(-40);
  fourBarMotor.spin(fwd, 12, volt);
  turnToAngle(-0.2, 600);
  driveRelative(-6, 500);

  toggleBackLift();
  turnToAngle(M_PI_2);
  if(tc == BLUE)
    visionTurn(BACKVISION, BACK_BLUEMOGO, 900);
  else if(tc == RED)
    visionTurn(BACKVISION, BACK_REDMOGO, 900);
  driveRelative(-12, 1000);
  toggleBackLift();
  ringLiftMotor.spin(fwd, 12, volt);
  
  while(true){
    driveMotors.spin(fwd, 7.5, volt);
    this_thread::sleep_for(1600);
    if(autonTimer.time(msec) > 12000){
      break;
    }
    driveMotors.spin(fwd, -9, volt);
    this_thread::sleep_for(1000);
    if(autonTimer.time(msec) > 13000){
      break;
    }
    fourBarMotor.stop();
  }

  driveMotors.stop();
  turnToAngle(0, 1000);
  this_thread::sleep_for(75);
  driveRelative(3, 200);
  toggleBackLift();
}

//RIGHT NEUTRAL MAIN or OTHER
void rightMidFirstAuton(){
  driveMotors.spin(fwd, 12, volt);
  toggleClaw();
  waitUntil(pt::x() > 54);
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

  turnToAngle(M_PI_2, 1000);
  if(tc == BLUE)
    visionTurn(BACKVISION, BACK_BLUEMOGO, 1200);
  else if(tc == RED)
    visionTurn(BACKVISION, BACK_REDMOGO, 1200);
  toggleBackLift();
  driveRelative(-36, 1000);
  toggleBackLift();
  driveRelative(5, 500);
}

//LEFT NEUTRAL MAIN or OTHER
void leftMidFirstAuton(){
  driveMotors.spin(fwd, 12, volt);
  toggleClaw();
  waitUntil(pt::x() > 60);
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
}
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

//RIGHT NEUTRAL MAIN
void rightMidFirstAuton(){
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
  driveRelative(53, 0, slowFwd);
  this_thread::sleep_for(50);
  toggleClaw();
  this_thread::sleep_for(25);
  fourBarMotor.spin(fwd, 12, volt);
  driveMotors.spin(fwd, -12, volt);
  this_thread::sleep_for(100);
  fourBarMotor.stop(hold);
  waitUntil(pt::x() < 15);

  turnToAngle(M_PI_2, 1000);
  fourBarMotor.spin(fwd, 12, volt);
  if(tc == BLUE){
    visionTurn(BACKVISION, BACK_BLUEMOGO, 1200);
    visionTurn(BACKVISION, BACK_BLUEMOGO, 600);
    visionTurn(BACKVISION, BACK_BLUEMOGO, 300);
  }
  else if(tc == RED){
    visionTurn(BACKVISION, BACK_REDMOGO, 1200);
    visionTurn(BACKVISION, BACK_REDMOGO, 600);
    visionTurn(BACKVISION, BACK_REDMOGO, 300);
  }
  this_thread::sleep_for(150);
  fourBarMotor.stop(hold);
  driveRelative(-30, 1000);
  this_thread::sleep_for(150);
  toggleBackLift();
  this_thread::sleep_for(50);
  ringLiftMotor.spin(fwd, 12, volt);

  if(autonTimer.time(msec) > 13500){
    turnToAngle(0, 700);
    driveMotors.spin(fwd, -7.5, volt);
    waitUntil(pt::x() < -2);
    toggleBackLift();
  }
  else{
    turnToAngle(M_PI_2, 500);
    this_thread::sleep_for(150);
    driveRelative(6.5, 400, verySlowFwd);
    this_thread::sleep_for(150);
    turnToAngle(0, 1100);
    driveMotors.spin(fwd, 7.5, volt);
    waitUntil(autonTimer.time(msec) > 14000 || pt::x() > 45);
    driveMotors.spin(fwd, -12, volt);
    waitUntil(autonTimer.time(msec) > 14930);
    driveMotors.stop();
    this_thread::sleep_for(30);
    toggleBackLift();
  }
}

void rightMidJuke(){

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
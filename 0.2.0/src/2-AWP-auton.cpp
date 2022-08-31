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
  driveRelative(53, 2000, verySlowFwd);
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
  waitUntil(pt::x() < 24);
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

  turnToAngle(M_PI_2, 500);
  this_thread::sleep_for(150);
  driveRelative(4, 300, verySlowFwd);
  this_thread::sleep_for(150);
  turnToAngle(0, 1100);
  driveMotors.spin(fwd, 7.5, volt);
  waitUntil(autonTimer.time(msec) > 13750 || pt::x() > 45);
  driveMotors.spin(fwd, -12, volt);
  waitUntil(autonTimer.time(msec) > 14600 || pt::x() < 0);
  driveMotors.stop();
  this_thread::sleep_for(30);
  toggleBackLift();
}

//RIGHT NEUTRAL OTHER
void rightMidJuke(){

}

//LEFT NEUTRAL MAIN
void leftMidFirstAuton(){
  timer autonTimer;
  driveMotors.spin(fwd, 12, volt);
  toggleClaw();
  fourBarMotor.spin(fwd, 12, volt);
  ringLiftMotor.spin(fwd, 12, volt);
  waitUntil(pt::x() > 12);
  fourBarMotor.stop();
  waitUntil(pt::x() > 25);
  fourBarMotor.spin(fwd, -12, volt);
  waitUntil(pt::x() > 40);
  driveMotors.stop();
  visionTurn(FRONTVISION, FRONT_YELLOWMOGO, 1000);
  ringLiftMotor.stop();
  driveRelative(25, 875, verySlowFwd);
  fourBarMotor.stop();
  toggleClaw();
  this_thread::sleep_for(250);
  fourBarMotor.spin(fwd, 12, volt);
  driveMotors.spin(fwd, -12, volt);
  this_thread::sleep_for(100);
  fourBarMotor.stop(hold);
  waitUntil(pt::x() < 35);
  driveMotors.stop();

  fourBarMotor.spin(fwd, 12, volt);
  turnToAngle(-M_PI_2 + 0.35, 1000);
  fourBarMotor.stop();
  toggleBackLift();
  driveRelative(-18, 1000);
  turnToAngle(0.5, 700);
  driveRelative(-55, 1200);
  driveRelative(5, 500);
  turnToAngle(M_PI_2);
  if(tc == BLUE)
    visionTurn(BACKVISION, BACK_BLUEMOGO, 900);
  else if(tc == RED)
    visionTurn(BACKVISION, BACK_REDMOGO, 900);
  driveRelative(-16, 1000);
  toggleBackLift();
  ringLiftMotor.spin(fwd, 12, volt);
  
  while(true){
    driveMotors.spin(fwd, 6, volt);
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


//LEFT NEUTRAL OTHER
void leftMidJuke(){

}
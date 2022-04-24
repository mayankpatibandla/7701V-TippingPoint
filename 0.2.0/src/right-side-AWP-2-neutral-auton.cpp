#include "vex.h"
#include "auton-functions.h"

void visionTurn(double timeout = 0){
  const double kP = 0.13;
  const double target = 158;

  timer dTimer;

  while(true){
    if(dTimer.time(msec) > timeout && timeout != 0) break;
    frontVisionSensor.takeSnapshot(tc == RED ? BACK_REDMOGO : BACK_BLUEMOGO);
    vision::object &obj = frontVisionSensor.largestObject;

    double currentPos = obj.centerX;
    
    if(!obj.exists){
      Brain.Screen.clearScreen();
      Brain.Screen.setCursor(1, 1);
      Brain.Screen.print("OBJECT NOT FOUND");
      Brain.Screen.render();
    }
    
    double error = target - currentPos;
    double pow = error * kP;

    leftMotors.spin(fwd, -pow, pct);
    rightMotors.spin(fwd, pow, pct);

    if(error < 2.5) break;
    wait(10, msec);
  }
  driveMotors.stop();
}

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

  //drop first yellow
  driveMotors.spin(fwd, 50, pct);
  waitUntil(pt::x() > 10.25);
  driveMotors.stop();
  turnToAngle(M_PI_2, 1000);
  fourBarMotor.spin(fwd, -12, volt);
  waitUntil(fourBarRotationSensor.angle(deg) < fourBarMinPos + 3.5);
  fourBarMotor.stop(hold);
  driveRelative(15, 1000);
  toggleClaw();
  this_thread::sleep_for(75);
  driveRelative(-14, 1000);

  //get tall yellow
  turnToAngle(M_PI_4 + 0.06125, 3000);
  /*timer visionTimeout;
  const double kP = 0.13;
  const double target = 158;
  while(visionTimeout.time(msec) < 2000){
    frontVisionSensor.takeSnapshot(FRONT_YELLOWMOGO);
    vision::object &obj = frontVisionSensor.largestObject;

    double currentPos = obj.centerX;
    
    if(!obj.exists){
      Brain.Screen.clearScreen();
      Brain.Screen.setCursor(1, 1);
      Brain.Screen.print("OBJECT NOT FOUND");
      Brain.Screen.render();
    }
    
    double error = target - currentPos;
    double pow = error * kP;

    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1, 1);
    Brain.Screen.print("%d", currentPos);
    Brain.Screen.setCursor(2, 1);
    Brain.Screen.print("%d", error);
    Brain.Screen.render();

    leftMotors.spin(fwd, -pow, pct);
    rightMotors.spin(fwd, pow, pct);

    if(error < 7) break;
    wait(10, msec);
  }
  driveMotors.stop();*/
  driveRelative(50, 2000, verySlowFwd);
  toggleClaw();
  fourBarMotor.spin(fwd, 12, volt);
  this_thread::sleep_for(25);
  driveMotors.spin(fwd, -12, volt);
  this_thread::sleep_for(75);
  fourBarMotor.stop(hold);
  toggleBackLift();
  turnToAngle(M_PI_4 + 0.09, 2000);
  driveRelative(-60, 2750);
  toggleBackLift();
  this_thread::sleep_for(50);
  ringLiftMotor.spin(fwd, 12, volt);
  turnToAngle(0, 1250);
  driveRelative(-18, 2000);
}
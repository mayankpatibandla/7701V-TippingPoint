#include "vex.h"
#include "auton-functions.h"

void skillsAuton(){
  timer fourBarTimer;
  const double fourBarBottomOffset = 7;

  //get alliance mogo in back
  toggleBackLift();
  driveMotors.spin(fwd, -40, pct);
  this_thread::sleep_for(950);
  toggleBackLift();
  this_thread::sleep_for(100);
  driveRelative(28, 1100, slowFwd);

  //get first short yellow
  turnToAngle(-M_PI_2-M_PI_4 + 0.35); //+0.45
  ringLiftMotor.spin(fwd, 12, volt);
  toggleClaw();
  driveRelative(51, 1800, slowFwd);
  driveMotors.stop();
  toggleClaw();
  this_thread::sleep_for(50);
  fourBarMotor.spin(fwd, 100, pct);
  fourBarTimer.reset();

  //stack short yellow
  turnToAngle(-M_PI_2-M_PI_4);
  waitUntil(fourBarRotationSensor.angle(deg) > fourBarMaxPos - 2 || fourBarTimer.time(msec) > 1500);
  fourBarMotor.stop();
  driveRelative(55, 2500, slowFwd);
  turnToAngle(-M_PI_2);
  driveMotors.spinFor(1300, msec, 35, velocityUnits::pct);
  driveRelative(-0.75, 500);
  fourBarMotor.spin(fwd, -100, pct);
  this_thread::sleep_for(800);
  fourBarMotor.stop();
  toggleClaw();
  this_thread::sleep_for(50);
  fourBarMotor.spin(fwd, 100, pct);
  fourBarTimer.reset();
  waitUntil(fourBarRotationSensor.angle(deg) > fourBarMaxPos - 15 || fourBarTimer.time(msec) > 750);
  fourBarMotor.stop();
  driveRelative(-12, 2000);

  //stack alliance goal
  turnToAngle(M_PI);
  toggleBackLift();
  fourBarMotor.spin(fwd, -100, pct);
  fourBarTimer.reset();
  waitUntil(fourBarRotationSensor.angle(deg) < fourBarMinPos + fourBarBottomOffset*2 || fourBarTimer.time(msec) > 1300);
  fourBarMotor.stop();
  driveRelative(12, 1000, slowFwd);
  turnToAngle(0);
  fourBarMotor.spin(fwd, -100, pct);
  fourBarTimer.reset();
  waitUntil(fourBarRotationSensor.angle(deg) < fourBarMinPos + fourBarBottomOffset - 6 || fourBarTimer.time(msec) > 900);
  fourBarMotor.stop();
  driveRelative(32.5, 1400, slowFwd);
  toggleClaw();
  this_thread::sleep_for(250);
  fourBarMotor.spin(fwd, 100, pct);
  fourBarTimer.reset();
  //driveRelative(-21.5, 1500, slowFwd);
  driveMotors.spin(fwd, -50, pct);
  waitUntil(pt::x() < -43.5);
  driveMotors.stop();
  waitUntil(fourBarRotationSensor.angle(deg) > fourBarMaxPos - 2 || fourBarTimer.time(msec) > 1500);
  fourBarMotor.stop(hold);
  turnToAngle(-M_PI_2);
  driveMotors.spinFor(1200, msec, 50, velocityUnits::pct);
  driveMotors.spinFor(125, msec, -50, velocityUnits::pct);
  toggleClaw();
  fourBarMotor.spin(fwd, 100, pct);
  this_thread::sleep_for(100);
  fourBarMotor.stop();
  driveRelative(-12.5, 1000);

  //get alliance goal 2
  driveRelative(9.5, 3000, slowFwd);
  turnToAngle(0);
  fourBarMotor.spin(fwd, -100, pct);
  fourBarTimer.reset();
  driveMotors.spin(fwd, 50, pct);
  waitUntil(fourBarRotationSensor.angle(deg) < fourBarMinPos + fourBarBottomOffset-4 || fourBarTimer.time(msec) > 2000);
  fourBarMotor.stop(hold);
  driveRelative(37, 1200, slowFwd);
  toggleClaw();
  this_thread::sleep_for(300);
  driveMotors.stop();
  this_thread::sleep_for(50);
  driveRelative(-12, 2000, slowFwd);

  //stack alliance goal 2
  fourBarMotor.spin(fwd, 100, pct);
  fourBarTimer.reset();
  turnToAngle(M_PI_2+M_PI_4-0.175);
  waitUntil(fourBarRotationSensor.angle(deg) > fourBarMaxPos - 2 || fourBarTimer.time(msec) > 1500);
  fourBarMotor.stop();
  driveRelative(87, 2700, slowFwd);
  turnToAngle(M_PI_2);
  driveRelative(16, 750);
  toggleClaw();
  this_thread::sleep_for(300);
  driveMotors.spin(fwd, -50, pct);
  this_thread::sleep_for(150);
  //turnToAngle(M_PI_2-0.05, 750);
  turnToAngle(atan2(pt::y() + 63, pt::x() + 46) + 0.15, 800);
  driveRelative(-60);

  //get and stack short yellow 2
  fourBarMotor.spin(fwd, -12, volt);
  fourBarTimer.reset();
  turnToAngle(M_PI_2 + 1);
  waitUntil(fourBarRotationSensor.angle(deg) < fourBarMinPos + fourBarBottomOffset || fourBarTimer.time(msec) > 2000);
  fourBarMotor.stop(hold);
  driveRelative(43, 1500, slowFwd);
  toggleClaw();
  this_thread::sleep_for(50);
  fourBarMotor.spin(fwd, 12, volt);
  fourBarTimer.reset();
  turnToAngle(M_PI_2 - 0.825);
  waitUntil(fourBarRotationSensor.angle(deg) > fourBarMaxPos - 2 || fourBarTimer.time(msec) > 1500);
  fourBarMotor.stop();
  driveRelative(65, 2300);
  toggleClaw();
  driveRelative(-18, 3000);

  Controller.rumble(".");
}
#include "vex.h"
#include "auton-config.h"

using namespace vex;

brain Brain;
controller Controller;

competition Competition;
color Color;

inertial inertialSensor(PORT1);

rotation leftRotationSensor(PORT11);
rotation rightRotationSensor(PORT16);
rotation backRotationSensor(PORT17);

motor frontLeftMotor(PORT13, true);
motor frontRightMotor(PORT12);
motor backLeftMotor(PORT10, true);
motor backRightMotor(PORT2);

motor fourBarMotor(PORT9, gearSetting::ratio36_1);
motor ringLiftMotor(PORT6);

motor leftTilterMotor(PORT15, gearSetting::ratio36_1);
motor rightTilterMotor(PORT18, gearSetting::ratio36_1, true);

digital_out leftClawSolenoid(Brain.ThreeWirePort.A);
digital_out rightClawSolenoid(Brain.ThreeWirePort.B);

motor_group tilterMotors(leftTilterMotor, rightTilterMotor);

motor_group leftMotors(frontLeftMotor, backLeftMotor);
motor_group rightMotors(frontRightMotor, backRightMotor);
motor_group driveMotors(frontLeftMotor, frontRightMotor, backLeftMotor, backRightMotor);

//calibrate inertial and reset rotation sensors
void sensorInit(){
  Brain.Screen.clearScreen();
  Brain.Screen.printAt(0, 20, "Calibrating Inertial Sensor");
  Brain.Screen.render();
  inertialSensor.calibrate();
  waitUntil(!inertialSensor.isCalibrating());
  Brain.Screen.clearScreen();
  Brain.Screen.render();
  leftRotationSensor.resetPosition();
  rightRotationSensor.resetPosition();
  backRotationSensor.resetPosition();
}

//init auton configs with default values, will be overridden
teamColor tc = RED;
teamSide ts = LEFT;

//read auton config from file
void autonInit(){
  tc = RED;
  ts = LEFT;
}
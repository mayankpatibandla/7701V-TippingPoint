#include "vex.h"
#include "auton-config.h"
#include <fstream>

using namespace vex;

brain Brain;
controller Controller;

competition Competition;
color Color;

inertial inertialSensor(PORT1);

rotation leftRotationSensor(PORT11);
rotation rightRotationSensor(PORT16, true);
rotation backRotationSensor(PORT20);

motor frontLeftMotor(PORT1, false);//
motor frontRightMotor(PORT10, true);//
motor backLeftMotor(PORT20, true);//
motor backRightMotor(PORT9, false);//

motor leftFourBarMotor(PORT2, gearSetting::ratio36_1, true);//
motor rightFourBarMotor(PORT8, gearSetting::ratio36_1);//

motor backLiftMotor(PORT3, gearSetting::ratio36_1, true);//

digital_out leftClawSolenoid(Brain.ThreeWirePort.A);
digital_out rightClawSolenoid(Brain.ThreeWirePort.B);

motor_group fourBarMotors(leftFourBarMotor, rightFourBarMotor);

motor_group leftMotors(frontLeftMotor, backLeftMotor);
motor_group rightMotors(frontRightMotor, backRightMotor);
motor_group driveMotors(frontLeftMotor, frontRightMotor, backLeftMotor, backRightMotor);

//calibrate inertial and reset rotation sensors
void sensorInit(){
  Brain.Screen.clearScreen();
  Brain.Screen.printAt(0, 20, "Calibrating Sensors");
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
autonVersion av = AWP;

//read auton config from file
void autonInit(){
  if(!Brain.SDcard.isInserted()){
    Brain.Screen.setFont(mono60);
    Brain.Screen.printAt(0, 40, "No SD Card!");
    Brain.Screen.setFont(mono20);
    while(!Brain.SDcard.isInserted())Controller.rumble("-.");
  }
  std::ifstream ifs;
  int int_tc, int_ts;

  ifs.open("config/color.txt");
  ifs >> int_tc;
  ifs.close();
  ifs.open("config/side.txt");
  ifs >> int_ts;
  ifs.close();
  tc = int_tc == 0 ? RED : BLUE;
  ts = int_ts == 0 ? LEFT : RIGHT;

  Controller.Screen.print("%s___%s", int_tc == 0 ? "RED" : "BLUE", int_ts == 0 ? "LEFT" : "RIGHT");
}

//set motor brake
void motorInit(){
  fourBarMotors.setStopping(brake);

  backLiftMotor.setBrake(hold);

  driveMotors.setStopping(brake);
}
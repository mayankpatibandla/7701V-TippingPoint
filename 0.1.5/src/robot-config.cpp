#include "vex.h"
#include "auton-config.h"
#include <fstream>

using namespace vex;

brain Brain;
controller Controller;

competition Competition;
color Color;

inertial inertialSensor(PORT4);

rotation leftRotationSensor(PORT5, true);
rotation rightRotationSensor(PORT6, true);
rotation backRotationSensor(PORT7);

motor frontLeftMotor(PORT1, false);
motor frontRightMotor(PORT10, true);
motor backLeftMotor(PORT20, true);
motor backRightMotor(PORT9, false);

motor leftFourBarMotor(PORT2, gearSetting::ratio36_1, true);
motor rightFourBarMotor(PORT8, gearSetting::ratio36_1);

motor backLiftMotor(PORT3, gearSetting::ratio36_1, true);

digital_out leftClawSolenoid(Brain.ThreeWirePort.A);
digital_out rightClawSolenoid(Brain.ThreeWirePort.B);

limit fourBarBottomLimit(Brain.ThreeWirePort.C);

motor_group fourBarMotors(leftFourBarMotor, rightFourBarMotor);

motor_group leftMotors(frontLeftMotor, backLeftMotor);
motor_group rightMotors(frontRightMotor, backRightMotor);
motor_group driveMotors(frontLeftMotor, frontRightMotor, backLeftMotor, backRightMotor);

//calibrate inertial and reset rotation sensors
void sensorInit(){
  Brain.Screen.clearScreen();
  Brain.Screen.setPenColor(white);
  Brain.Screen.setFillColor(black);
  Brain.Screen.setFont(mono40);
  Brain.Screen.render();
  Brain.Screen.printAt(0, 40, "Initializing Sensors");
  Brain.Screen.render();

  inertialSensor.calibrate();
  waitUntil(!inertialSensor.isCalibrating());

  leftRotationSensor.resetPosition();
  rightRotationSensor.resetPosition();
  backRotationSensor.resetPosition();

  Brain.Screen.clearScreen();
  Brain.Screen.render();
  Brain.Screen.setFont(mono20);
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
  int int_tc, int_ts, int_av;

  ifs.open("config/color.txt");
  ifs >> int_tc;
  ifs.close();
  ifs.open("config/side.txt");
  ifs >> int_ts;
  ifs.close();
  ifs.open("config/version.txt");
  ifs >> int_av;
  ifs.close();

  tc = static_cast<teamColor>(int_tc);
  ts = static_cast<teamSide>(int_ts);
  av = static_cast<autonVersion>(int_av);

  std::string teamColorStrings[] = {"RED", "BLUE", "SKILLS", "TEST", "NONE"};
  std::string teamSideStrings[] = {"LEFT", "RIGHT"};
  std::string autonVersionStrings[] = {"AWP", "NEUTRAL"};
  Controller.Screen.print("%s %s %s", teamColorStrings[int_tc].c_str(), teamSideStrings[int_ts].c_str(), autonVersionStrings[int_av].c_str());
}

//set motor brake
void motorInit(){
  fourBarMotors.setStopping(brake);

  backLiftMotor.setStopping(hold);

  driveMotors.setStopping(brake);
}
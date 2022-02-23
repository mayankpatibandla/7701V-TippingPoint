#include "vex.h"
#include "auton-config.h"
#include <fstream>
#include <sstream>

using namespace vex;

brain Brain;
controller Controller;

competition Competition;
color Color;

/*rotation leftRotationSensor(PORT5, true);
rotation rightRotationSensor(PORT6, false);
rotation backRotationSensor(PORT14, false);*/

motor frontLeftMotor(PORT8, ratio18_1, false);
motor middleLeftMotor(PORT9, ratio18_1, false);
motor backLeftMotor(PORT10, ratio18_1, false);

motor frontRightMotor(PORT18, ratio18_1, true);
motor middleRightMotor(PORT19, ratio18_1, true);
motor backRightMotor(PORT20, ratio18_1, true);

motor fourBarMotor(PORT1, ratio36_1, false);

motor ringLiftMotor(PORT11, ratio6_1, true);

//inertial inertialSensor(PORT13);

/*distance clawDistanceSensor(PORT12);
optical clawOpticalSensor(PORT15, false);*/

digital_out clawSolenoid(Brain.ThreeWirePort.A);
digital_out backLiftSolenoid(Brain.ThreeWirePort.B);

/*limit fourBarBottomLimit(Brain.ThreeWirePort.C);
limit fourBarTopLimit(Brain.ThreeWirePort.D);*/

motor_group leftMotors(frontLeftMotor, middleLeftMotor, backLeftMotor);
motor_group rightMotors(frontRightMotor, middleRightMotor, backRightMotor);
motor_group driveMotors(frontLeftMotor, middleLeftMotor, backLeftMotor, frontRightMotor, middleRightMotor, backRightMotor);

//calibrate inertial and reset rotation sensors
/*void sensorInit(){
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
autonType at = MAIN;

//read auton config from file
void autonInit(){
  if(!Brain.SDcard.isInserted()){
    Brain.Screen.setFont(mono60);
    Brain.Screen.printAt(0, 60, "No SD Card!");
    Brain.Screen.setFont(mono20);
    while(!Brain.SDcard.isInserted())Controller.rumble("-.");
  }
  std::ifstream ifs;
  int int_tc, int_ts, int_av, int_at;

  ifs.open("config/color.txt");
  ifs >> int_tc;
  ifs.close();
  ifs.open("config/side.txt");
  ifs >> int_ts;
  ifs.close();
  ifs.open("config/version.txt");
  ifs >> int_av;
  ifs.close();
  ifs.open("config/type.txt");
  ifs >> int_at;
  ifs.close();

  tc = static_cast<teamColor>(int_tc);
  ts = static_cast<teamSide>(int_ts);
  av = static_cast<autonVersion>(int_av);
  at = static_cast<autonType>(int_at);

  std::string teamColorStrings[] = {"RED", "BLUE", "SKILLS", "TEST", "NONE"};
  std::string teamSideStrings[] = {"LEFT", "RIGHT"};
  std::string autonVersionStrings[] = {"AWP", "NEUTRAL"};
  std::string autonTypeStrings[] = {"MAIN", "OTHER"};
  Controller.Screen.print(
    "%s %s %s %s",
    teamColorStrings[int_tc].c_str(),
    teamSideStrings[int_ts].c_str(),
    autonVersionStrings[int_av].c_str(),
    autonTypeStrings[int_at].c_str()
  );
}*/

//set motor brake
void motorInit(){
  fourBarMotors.setStopping(hold);
  ringLiftMotor.setStopping(coast);
  backLiftMotor.setStopping(hold);
  driveMotors.setStopping(brake);

  fourBarMotors.setMaxTorque(100, pct);
  backLiftMotor.setMaxTorque(100, pct);

  driveMotors.resetPosition();
  driveMotors.resetRotation();

  fourBarMotors.resetPosition();
  fourBarMotors.resetRotation();

  ringLiftMotor.resetPosition();
  ringLiftMotor.resetRotation();

  backLiftMotor.resetPosition();
  backLiftMotor.resetRotation();
}
/*
bool cancel;
int error(std::string str1, std::string str2, bool cond)
{
  Brain.Screen.setFont(mono20);
  Brain.Screen.setPenColor(white);
  Brain.Screen.clearScreen();
  Brain.Screen.printAt(20, 20, str1.c_str());
  Brain.Screen.printAt(20, 60, str2.c_str()); 
  Brain.Screen.render();
  while(cond && !cancel) 
  {
    Controller.rumble("-");
    if(Controller.ButtonA.pressing() || Controller.ButtonB.pressing() || Controller.ButtonX.pressing() || Controller.ButtonY.pressing() ||
    Controller.ButtonUp.pressing() || Controller.ButtonDown.pressing() || Controller.ButtonLeft.pressing() || Controller.ButtonRight.pressing() || 
    Controller.ButtonL1.pressing()  || Controller.ButtonL2.pressing()  || Controller.ButtonR1.pressing()  || Controller.ButtonR2.pressing() || 
    Controller.Axis3.position() < -50 || Controller.Axis4.position() < -50 || Controller.Axis3.position() > 50 || Controller.Axis4.position() > 50 ||
    Controller.Axis1.position() < -50 || Controller.Axis2.position() < -50 || Controller.Axis1.position() > 50 || Controller.Axis2.position() > 50 ||
    Brain.Screen.pressing())
    {
      cancel= true;
      cond = false;
    }
    else wait(0.1, seconds);
  }
  Brain.Screen.clearScreen();
  Brain.Screen.render();

  return 0;
}

bool errors = true; //enable
bool checkDevices(bool p_cancel)
{
  if(p_cancel) cancel = false;
  if(errors)
  {
    std::ostringstream ss;
    std::ostringstream ss2;
    std::string s = "MOTOR NOT INSTALLED | NAME: ";
    std::string ses = "SENSOR NOT INSTALLED | NAME: ";
    std::string s2 = "PORT: ";

    if(!frontLeftMotor.installed())
    {
      ss << s << "FRONT LEFT"; ss2 << s2 << frontLeftMotor.index() + 1;
      error(ss.str(), ss2.str(), !frontLeftMotor.installed());
      return false;
    }
    else if(!frontRightMotor.installed())
    {
      ss << s << "FRONT RIGHT"; ss2  << s2 << frontRightMotor.index() + 1;
      error(ss.str(), ss2.str(), !frontRightMotor.installed());
      return false;
    }
    else if(!backLeftMotor.installed())
    {
      ss << s << "BACK LEFT"; ss2 << s2 << backLeftMotor.index() + 1;
      error(ss.str(), ss2.str(), !backLeftMotor.installed());
      return false;
    }
    else if(!backRightMotor.installed())
    {
      ss << s << "BACK RIGHT"; ss2 << s2 << backRightMotor.index() + 1;
      error(ss.str(), ss2.str(), !backRightMotor.installed());
      return false;
    }
    else if(!backLiftMotor.installed())
    {
      ss << s << "BACK LIFT"; ss2 << s2 << backLiftMotor.index() + 1;
      error(ss.str(), ss2.str(), !backLiftMotor.installed());
      return false;
    }
    else if(!ringLiftMotor.installed())
    {
      ss << s << "RING LIFT"; ss2 << s2 << ringLiftMotor.index() + 1;
      error(ss.str(), ss2.str(), !ringLiftMotor.installed());
      return false;
    }
    else if(!leftFourBarMotor.installed())
    {
      ss << s << "LEFT FOURBAR"; ss2 << s2 << leftFourBarMotor.index() + 1;
      error(ss.str(), ss2.str(), !leftFourBarMotor.installed());
      return false;
    }
    else if(!rightFourBarMotor.installed())
    {
      ss << s << "RIGHT FOURBAR"; ss2 << s2 << rightFourBarMotor.index() + 1;
      error(ss.str(), ss2.str(), !rightFourBarMotor.installed());
      return false;
    }
    else if(!inertialSensor.installed())
    {
      ss << ses << "INERTIAL"; ss2 << s2 << inertialSensor.index() + 1;
      error(ss.str(), ss2.str(), !inertialSensor.installed());
      return false;
    }
    else if(!leftRotationSensor.installed())
    {
      ss << ses << "LEFT ROTATION"; ss2 << s2 << leftRotationSensor.index() + 1;
      error(ss.str(), ss2.str(), !leftRotationSensor.installed());
      return false;
    }
    else if(!rightRotationSensor.installed())
    {
      ss << ses << "RIGHT ROTATION"; ss2 << s2 << rightRotationSensor.index() + 1;
      error(ss.str(), ss2.str(), !rightRotationSensor.installed());
      return false;
    }
    else if(!backRotationSensor.installed())
    {
      ss << ses << "BACK ROTATION"; ss2 << s2 << backRotationSensor.index() + 1;
      error(ss.str(), ss2.str(), !backRotationSensor.installed());
      return false;
    }
    else return true;
  }
  else return true;
}*/
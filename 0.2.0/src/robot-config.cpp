#include "vex.h"
#include "auton-config.h"
#include <fstream>
#include <sstream>

using namespace vex;

brain Brain;
controller Controller(primary);
controller partnerController(partner);

competition Competition;
color Color;

rotation leftRotationSensor(PORT7, false);
rotation rightRotationSensor(PORT14, false);//unused
rotation backRotationSensor(PORT17, true);

motor frontLeftMotor(PORT8, ratio18_1, false);
motor middleLeftMotor(PORT9, ratio18_1, false);
motor backLeftMotor(PORT10, ratio18_1, false);

motor frontRightMotor(PORT18, ratio18_1, true);
motor middleRightMotor(PORT19, ratio18_1, true);
motor backRightMotor(PORT20, ratio18_1, true);

motor fourBarMotor(PORT1, ratio36_1, true);

const double fourBarRotationOffset = 15;
const double fourBarMinPos = 18.5;
const double fourBarMaxPos = 120;
rotation_x fourBarRotationSensor(PORT12, true, fourBarRotationOffset);

motor ringLiftMotor(PORT14, ratio6_1, false);

inertial inertialSensor(PORT13);

digital_out leftClawSolenoid(Brain.ThreeWirePort.A);
digital_out rightClawSolenoid(Brain.ThreeWirePort.B);
digital_out backLiftSolenoid(Brain.ThreeWirePort.C);

motor_group leftMotors(frontLeftMotor, middleLeftMotor, backLeftMotor);
motor_group rightMotors(frontRightMotor, middleRightMotor, backRightMotor);
motor_group driveMotors(frontLeftMotor, middleLeftMotor, backLeftMotor, frontRightMotor, middleRightMotor, backRightMotor);
motor_group allMotors(frontLeftMotor, middleLeftMotor, backLeftMotor, frontRightMotor, middleRightMotor, backRightMotor, fourBarMotor, ringLiftMotor);

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

  fourBarRotationSensor.resetPosition();
  fourBarRotationSensor.setPosition(fourBarRotationOffset, deg);

  leftRotationSensor.resetPosition();
  rightRotationSensor.resetPosition();
  backRotationSensor.resetPosition();

  Brain.Screen.clearScreen();
  Brain.Screen.render();
  Brain.Screen.setFont(mono20);
}

//init auton configs with default values, will be overridden
teamColor tc = RED;
teamSide ts = RIGHT;
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
}

//set motor brake
void motorInit(){
  allMotors.resetPosition();
  allMotors.resetRotation();

  driveMotors.setStopping(brake);
  fourBarMotor.setStopping(hold);
  ringLiftMotor.setStopping(coast);
}

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
    else if(!middleLeftMotor.installed())
    {
      ss << s << "MIDDLE LEFT"; ss2 << s2 << middleLeftMotor.index() + 1;
      error(ss.str(), ss2.str(), !middleLeftMotor.installed());
      return false;
    }
    else if(!backLeftMotor.installed())
    {
      ss << s << "BACK LEFT"; ss2 << s2 << backLeftMotor.index() + 1;
      error(ss.str(), ss2.str(), !backLeftMotor.installed());
      return false;
    }
    else if(!frontRightMotor.installed())
    {
      ss << s << "FRONT RIGHT"; ss2 << s2 << frontRightMotor.index() + 1;
      error(ss.str(), ss2.str(), !frontRightMotor.installed());
      return false;
    }
    else if(!middleRightMotor.installed())
    {
      ss << s << "MIDDLE RIGHT"; ss2 << s2 << middleRightMotor.index() + 1;
      error(ss.str(), ss2.str(), !middleRightMotor.installed());
      return false;
    }
    else if(!backRightMotor.installed())
    {
      ss << s << "BACK RIGHT"; ss2 << s2 << backRightMotor.index() + 1;
      error(ss.str(), ss2.str(), !backRightMotor.installed());
      return false;
    }
    else if(!fourBarMotor.installed())
    {
      ss << s << "FOUR BAR"; ss2 << s2 << fourBarMotor.index() + 1;
      error(ss.str(), ss2.str(), !fourBarMotor.installed());
      return false;
    }
    else if(!fourBarRotationSensor.installed())
    {
      ss << ses << "FOURBAR ROTATION"; ss2 << s2 << fourBarRotationSensor.index() + 1;
      error(ss.str(), ss2.str(), !fourBarRotationSensor.installed());
      return false;
    }
    else if(!ringLiftMotor.installed())
    {
      ss << s << "RING LIFT"; ss2 << s2 << ringLiftMotor.index() + 1;
      error(ss.str(), ss2.str(), !ringLiftMotor.installed());
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
      ss << ses << "LEFT TRACKER"; ss2 << s2 << leftRotationSensor.index() + 1;
      error(ss.str(), ss2.str(), !leftRotationSensor.installed());
      return false;
    }
    else if(!backRotationSensor.installed())
    {
      ss << ses << "BACK TRACKER"; ss2 << s2 << backRotationSensor.index() + 1;
      error(ss.str(), ss2.str(), !backRotationSensor.installed());
      return false;
    }
    else return true;
  }
  else return true;
}

vex::vision::signature REDMOGO = vex::vision::signature (1, 7761, 9363, 8562, -1281, 161, -560, 4.9, 0);
vex::vision::signature BLUEMOGO = vex::vision::signature (2, -2011, -1145, -1578, 5387, 7453, 6420, 5.5, 0);
vex::vision::signature YELLOWMOGO = vex::vision::signature (3, 1875, 3257, 2566, -4225, -2971, -3598, 3.3, 0);
vex::vision::signature SIG_4 = vex::vision::signature (4, 0, 0, 0, 0, 0, 0, 2.5, 0);
vex::vision::signature SIG_5 = vex::vision::signature (5, 0, 0, 0, 0, 0, 0, 2.5, 0);
vex::vision::signature SIG_6 = vex::vision::signature (6, 0, 0, 0, 0, 0, 0, 2.5, 0);
vex::vision::signature SIG_7 = vex::vision::signature (7, 0, 0, 0, 0, 0, 0, 2.5, 0);
vex::vision frontVisionSensor = vex::vision (vex::PORT15, 50, REDMOGO, BLUEMOGO, YELLOWMOGO, SIG_4, SIG_5, SIG_6, SIG_7);
#include "vex.h"
#include "auton-config.h"
#include <fstream>
#include <sstream>

using namespace vex;

brain Brain;
controller Controller;

competition Competition;
color Color;

motor frontLeftMotor(PORT1, ratio18_1, true);
motor frontRightMotor(PORT2, ratio18_1, false);
motor backLeftMotor(PORT3, ratio18_1, true);
motor backRightMotor(PORT4, ratio18_1, false);

digital_out backLiftSolenoid(Brain.ThreeWirePort.A);

motor_group leftMotors(frontLeftMotor, backLeftMotor);
motor_group rightMotors(frontRightMotor, backRightMotor);
motor_group driveMotors(frontLeftMotor, frontRightMotor, backLeftMotor, backRightMotor);

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
}

//set motor brake
void motorInit(){
  driveMotors.setStopping(brake);

  driveMotors.resetPosition();
  driveMotors.resetRotation();
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
    else return true;
  }
  else return true;
}
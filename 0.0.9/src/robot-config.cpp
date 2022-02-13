#include "vex.h"
#include "configvalues.h"
#include "enums.h"
#include <cstdio>
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace vex;

std::ifstream ifs;
int data;

const double pi = 3.1415926535897932;

int threshold1 = deadbands[0];
int threshold2 = deadbands[1];
int threshold3 = deadbands[2];
int threshold4 = deadbands[3];

brain Brain;
brain::lcd LCD;
controller::lcd ControllerLCD;

competition Competition;
color Color;

controller Controller = controller(primary);

motor frontLeftMotor = motor(PORT6, ratio36_1, false);
motor frontRightMotor = motor(PORT8, ratio36_1, true);
motor backLeftMotor = motor(PORT4, ratio36_1, false);
motor backRightMotor = motor(PORT5, ratio36_1, true);
motor backLiftMotor = motor(PORT9, ratio6_1, false);
motor frontLiftMotor = motor(PORT11, ratio6_1, false);
motor leftIntakeMotor = motor(PORT1, ratio6_1, false);
motor rightIntakeMotor = motor(PORT7, ratio6_1, true);

motor_group leftMotors = motor_group(frontLeftMotor, backLeftMotor);
motor_group rightMotors = motor_group(frontRightMotor, backRightMotor);
motor_group driveMotors = motor_group(frontLeftMotor, frontRightMotor, backLeftMotor, backRightMotor);
motor_group liftMotors = motor_group(backLiftMotor, frontLiftMotor);
motor_group intakeMotors = motor_group(leftIntakeMotor, rightIntakeMotor);

inertial inertialSensor = inertial(PORT2);
optical opticalSensor = optical(PORT16);
distance distanceSensor = distance(PORT6);

rotation leftRotationSensor = rotation(PORT10, false);
rotation rightRotationSensor = rotation(PORT20, true);
rotation backRotationSensor = rotation(PORT6, false);

drivetrain mainDrivetrain = drivetrain(leftMotors, rightMotors);

timer t1;

/*vex-vision-config:begin*/
vision::signature SIG_1 = vision::signature(1, -2763, 1, -1381, -1, 9455, 4727, 0.7, 0); //blue rr
vision::signature SIG_2 = vision::signature(2, 819, 6199, 3509, -873, 851, -11, 1, 0); //red h
vision::signature SIG_3 = vision::signature(3, 8099, 8893, 8496, -1505, -949, -1227, 2.5, 0); //red ex
vision::signature SIG_4 = vision::signature(4, -3441, -2785, -3113, 8975, 10355, 9665, 2.5, 0); //blue ex
vision::signature SIG_5 = vision::signature(5, 6425, 11257, 8841, -3439, -1919, -2679, 2.7, 0); //red h t
vision::signature SIG_6 = vision::signature(6, 0, 0, 0, 0, 0, 0, 2.5, 0);
vision::signature SIG_7 = vision::signature(7, 0, 0, 0, 0, 0, 0, 2.5, 0);
vision visionSensor = vision(PORT17, 50, SIG_1, SIG_2, SIG_3, SIG_4, SIG_5, SIG_6, SIG_7); 
/*vex-vision-config:end*/

bool cancel = false;
int error(std::string str1, std::string str2, bool cond)
{
  LCD.setFont(mono20);
  LCD.setPenColor(white);
  LCD.clearScreen();
  LCD.printAt(20, 20, str1.c_str());
  LCD.printAt(20, 60, str2.c_str());
  LCD.render();
  while(cond && !cancel) 
  {
    Controller.rumble("-");
    if(Controller.ButtonA.pressing() || Controller.ButtonB.pressing() || Controller.ButtonX.pressing() || Controller.ButtonY.pressing() ||
    Controller.ButtonUp.pressing() || Controller.ButtonDown.pressing() || Controller.ButtonLeft.pressing() || Controller.ButtonRight.pressing() || 
    Controller.ButtonL1.pressing()  || Controller.ButtonL2.pressing()  || Controller.ButtonR1.pressing()  || Controller.ButtonR2.pressing() || 
    Controller.Axis3.position() < -threshold3 || Controller.Axis4.position() < -threshold4 || Controller.Axis3.position() > threshold3 || Controller.Axis4.position() > threshold4 ||
    Controller.Axis1.position() < -threshold1 || Controller.Axis2.position() < -threshold2 || Controller.Axis1.position() > threshold1|| Controller.Axis2.position() > threshold2 ||
    LCD.pressing())
    {
      cancel= true;
      cond = false;
    }
    else wait(0.1, seconds);
  }
  LCD.clearScreen();
  LCD.render();

  LCD.setFont(mono60);

  return 0;
}

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
    else if(!frontLiftMotor.installed())
    {
      ss << s << "FRONT LIFT"; ss2 << s2 << frontLiftMotor.index() + 1;
      error(ss.str(), ss2.str(), !frontLiftMotor.installed());
      return false;
    }
    else if(!leftIntakeMotor.installed())
    {
      ss << s << "LEFT INTAKE"; ss2 << s2 << leftIntakeMotor.index() + 1;
      error(ss.str(), ss2.str(), !leftIntakeMotor.installed());
      return false;
    }
    else if(!rightIntakeMotor.installed())
    {
      ss << s << "RIGHT INTAKE"; ss2 << s2 << rightIntakeMotor.index() + 1;
      error(ss.str(), ss2.str(), !rightIntakeMotor.installed());
      return false;
    }
    else if(!inertialSensor.installed())
    {
      ss << ses << "INERTIAL"; ss2 << s2 << inertialSensor.index() + 1;
      error(ss.str(), ss2.str(), !inertialSensor.installed());
      return false;
    }
    /*else if(!visionSensor.installed())
    {
      ss << ses << "VISION"; ss2 << s2 << visionSensor.index() + 1;
      error(ss.str(), ss2.str(), !visionSensor.installed());
      return false;
    }*/
    else if(!opticalSensor.installed())
    {
      ss << ses << "OPTICAL"; ss2 << s2 << opticalSensor.index() + 1;
      error(ss.str(), ss2.str(), !opticalSensor.installed());
      return false;
    }
    else return true;
  }
  else return true;
}

void vexcodeInit(void)
{
  LCD.clearScreen();
  LCD.render();
  LCD.setFont(mono60);
  LCD.setPenColor(white);

  if(!Brain.SDcard.isInserted())
  {
    error("NO SD CARD");
  }

  ifs.open("matchsettings.txt", ifs.in);
  ifs >> data;
  teamColor = data;
  ifs >> data;
  side = data;
  ifs.close();

  ifs.open("autonsettings.txt", ifs.in);
  ifs >> data;
  auton = data;
  ifs.close();

  ifs.open("keybinds.txt", ifs.in);
  for(int i = 0; i < 12; i++)
  {
    ifs >> data;
    funcs[i] = data;
  }
  ifs.close();

  ifs.open("joysticks.txt", ifs.in);
  ifs >> data;
  dType = data;
  ifs.close();

  ifs.open("deadbands.txt", ifs.in);
  for(int i = 0; i < 4; i++)
  {
    ifs >> data;
    deadbands[i] = data;
  }
  ifs.close();
  int dbands[10];
  for(int i = 0; i < 10; i++)
  {
    dbands[i] = 5 * (i + 1);
  }
  threshold1 = dbands[deadbands[0]];
  threshold2 = dbands[deadbands[1]];
  threshold3 = dbands[deadbands[2]];
  threshold4 = dbands[deadbands[3]];

  ifs.open("settings.txt", ifs.in);
  ifs >> data;
  wTurn = data;
  ifs >> data;
  errors = data;
  ifs.close();

  ifs.open("ports.txt", ifs.in);
  for(int i = 0; i < 11; i++)
  {
    ifs >> data;
    ports[i] = data;
  }
  ifs.close();

  ifs.open("reverse.txt", ifs.in);
  for(int i = 0; i < 8; i++)
  {
    ifs >> data;
    reverses[i] = data;
  }
  ifs.close();

  ifs.open("gears.txt", ifs.in);
  for(int i = 0; i < 8; i++)
  {
    ifs >> data;
    gearSettings[i] = data;
  }
  ifs.close();

  gearSetting gears[3] = {ratio36_1, ratio18_1, ratio6_1};
  int32_t t_ports[21] = {PORT1, PORT2, PORT3, PORT4, PORT5, PORT6, PORT7, PORT8, PORT9, PORT10, PORT11, PORT12, PORT13, PORT14, PORT15, PORT16, PORT17, PORT18, PORT19, PORT20, PORT21};
  inertialSensor = inertial(t_ports[ports[0]]);
  visionSensor = vision(t_ports[ports[1]], 50, SIG_1, SIG_2, SIG_3, SIG_4, SIG_5, SIG_6, SIG_7);
  opticalSensor = optical(t_ports[ports[2]]);
  frontLeftMotor = motor(t_ports[ports[3]], gears[gearSettings[0]], reverses[0]);
  frontRightMotor = motor(t_ports[ports[4]], gears[gearSettings[1]], reverses[1]);
  backLeftMotor = motor(t_ports[ports[5]], gears[gearSettings[2]], reverses[2]);
  backRightMotor = motor(t_ports[ports[6]], gears[gearSettings[3]], reverses[3]);
  frontLiftMotor = motor(t_ports[ports[7]], gears[gearSettings[4]], reverses[4]);
  backLiftMotor = motor(t_ports[ports[8]], gears[gearSettings[5]], reverses[5]);
  leftIntakeMotor = motor(t_ports[ports[9]], gears[gearSettings[6]], reverses[6]);
  rightIntakeMotor = motor(t_ports[ports[10]], gears[gearSettings[7]], reverses[7]);

  checkDevices(true);

  backLiftMotor.setBrake(brake);
  frontLiftMotor.setBrake(brake);
  leftIntakeMotor.setBrake(brake);
  rightIntakeMotor.setBrake(brake);
  frontLeftMotor.setBrake(brake);
  frontRightMotor.setBrake(brake);
  backLeftMotor.setBrake(brake);
  backRightMotor.setBrake(brake);

  backLiftMotor.setTimeout(0, msec);
  frontLiftMotor.setTimeout(0, msec);
  leftIntakeMotor.setTimeout(0, msec);
  rightIntakeMotor.setTimeout(0, msec);
  frontLeftMotor.setTimeout(0, msec);
  frontRightMotor.setTimeout(0, msec);
  backLeftMotor.setTimeout(0, msec);
  backRightMotor.setTimeout(0, msec);

  opticalSensor.setLight(ledState::on);
  opticalSensor.setLightPower(25, pct);

  inertialSensor.calibrate();
  LCD.clearScreen();
  LCD.setCursor(1, 1);
  LCD.print("CALIBRATING");
  LCD.newLine();
  LCD.print("INERTIAL");
  LCD.newLine();
  LCD.print("SENSOR");
  LCD.render();
  while(inertialSensor.isCalibrating()) wait(5, msec);

  visionSensor.setMode(vision::detectionMode::objectDetect);
  visionSensor.setWifiMode(vision::wifiMode::off);
  visionSensor.setLedMode(vision::ledMode::manual);
  visionSensor.setLedColor(128, 28, 59);
  visionSensor.setLedBrightness(100);

  leftRotationSensor.resetPosition();
  rightRotationSensor.resetPosition();
  backRotationSensor.resetPosition();

  checkDevices(true);

  LCD.clearScreen();
  LCD.render();
}
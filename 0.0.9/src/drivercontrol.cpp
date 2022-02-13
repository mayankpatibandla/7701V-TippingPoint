#include "vex.h"
#include "configvalues.h"
#include "functions.h"
#include <cstdio>
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace vex;

typedef int (*f)();

std::ofstream ofs;

int F1() //LIFT IN
{
  liftMotors.spin(fwd, 80, pct);

  return 0;
}

int F2() //LIFT OUT
{
  liftMotors.spin(fwd, -100, pct);

  return 0;
}

int F3() //INTAKES IN
{
  intakeMotors.spin(fwd, 100, pct);

  return 0;
}

int F4() //INTAKES OUT
{
  intakeMotors.spin(fwd, -100, pct);

  return 0;
}

int F5() //LIFT SAME DIRECTION IN
{
  frontLiftMotor.spin(fwd, -100, pct);
  backLiftMotor.spin(fwd, 100, pct);

  return 0;
}

int F6() //LIFT SAME DIRECTION OUT
{
  frontLiftMotor.spin(fwd, 100, pct);
  backLiftMotor.spin(fwd, -100, pct);

  return 0;
}

int F7() //INTAKES AND LIFT OUT
{
  intakeMotors.spin(fwd, -100, pct);
  liftMotors.spin(fwd, 100, pct);

  return 0;
}

int F8() //INTAKES AND LIFT IN
{
  intakeMotors.spin(fwd, 100, pct);
  liftMotors.spin(fwd, -100, pct);

  return 0;
}

int F9() //LIFT IN SLOW
{
  liftMotors.spin(fwd, 75, pct);
  return 0;
}

int F10() //LIFT OUT SLOW
{
  liftMotors.spin(fwd, -75, pct);
  return 0;
}

int F11() // SHOOT BALL
{
  liftMotors.rotateFor(fwd, 360, deg);

  return 0;
}

int F12() //AUTONOMOUS
{
  f_autonomous();

  return 0;
}

f functions[12] =
{
  F1,
  F2,
  F3,
  F4,
  F5,
  F6,
  F7,
  F8,
  F9,
  F10,
  F11,
  F12
};

void f_drivercontrol()
{ 
  int F1F2F5F6[12];
  bool bF1F2F5F6 = true;
  for(int i = 0; i < 12; i++)
  {
    if(funcs[i] == 0 || funcs[i] == 1 || funcs[i] == 4 || funcs[i] == 5)
    {
      F1F2F5F6[i] = 1;
    }
    else F1F2F5F6[i] = 0;
  }

  int F7F8[12];
  bool bF7F8 = true;
  for(int i = 0; i < 12; i++)
  {
    if(funcs[i] == 6 || funcs[i] == 7)
    {
      F7F8[i] = 1;
    }
    else F7F8[i] = 0;
  }

  int F3F4[12];
  bool bF3F4 = true;
  for(int i = 0; i < 12; i++)
  {
    if(funcs[i] == 2 || funcs[i] == 3)
    {
      F3F4[i] = 1;
    }
    else F3F4[i] = 0;
  }

  int F11[12];
  bool bF11 = true;
  for(int i = 0; i < 12; i++)
  {
    if(funcs[i] == 10)
    {
      F11[i] = 1;
    }
    else F11[i] = 0;
  }

  /*ofs.open("debug.txt", ofs.out);
  for(int i = 0; i < 12; i++)
  {
    ofs << F1F2F5F6[i] << "\n";
  }
  ofs.close();*/

  int q = 0;

  while(true)
  {
    //inertialDebug();
    //opticalDebug();

    if(Controller.ButtonL1.pressing())
    {
      q = 0;

      if(F1F2F5F6[q] == 1) bF1F2F5F6 = false;
      if(F3F4[q] == 1) bF3F4 = false;
      if(F7F8[q] == 1) bF7F8 = false;
      if(F11[q] == 1) bF11 = false;

      functions[funcs[q]]();
    } 
    if(Controller.ButtonL2.pressing())
    { 
      q = 1;

      if(F1F2F5F6[q] == 1) bF1F2F5F6 = false;
      if(F3F4[q] == 1) bF3F4 = false;
      if(F7F8[q] == 1) bF7F8 = false;
      if(F11[q] == 1) bF11 = false;

      functions[funcs[q]]();
    }
    if(Controller.ButtonR1.pressing()) 
    {
      q = 2;

      if(F1F2F5F6[q] == 1) bF1F2F5F6 = false;
      if(F3F4[q] == 1) bF3F4 = false;
      if(F7F8[q] == 1) bF7F8 = false;
      if(F11[q] == 1) bF11 = false;

      functions[funcs[q]]();
    }
    if(Controller.ButtonR2.pressing()) 
    {
      q = 3;

      if(F1F2F5F6[q] == 1) bF1F2F5F6 = false;
      if(F3F4[q] == 1) bF3F4 = false;
      if(F7F8[q] == 1) bF7F8 = false;
      if(F11[q] == 1) bF11 = false;

      functions[funcs[q]]();
    }
    if(Controller.ButtonX.pressing()) 
    {
      q = 4;

      if(F1F2F5F6[q] == 1) bF1F2F5F6 = false;
      if(F3F4[q] == 1) bF3F4 = false;
      if(F7F8[q] == 1) bF7F8 = false;
      if(F11[q] == 1) bF11 = false;

      functions[funcs[q]]();
    }
    if(Controller.ButtonY.pressing())
    {
      q = 5;

      if(F1F2F5F6[q] == 1) bF1F2F5F6 = false;
      if(F3F4[q] == 1) bF3F4 = false;
      if(F7F8[q] == 1) bF7F8 = false;
      if(F11[q] == 1) bF11 = false;

      functions[funcs[q]]();
    }
    if(Controller.ButtonA.pressing()) 
    {
      q = 6;

      if(F1F2F5F6[q] == 1) bF1F2F5F6 = false;
      if(F3F4[q] == 1) bF3F4 = false;
      if(F7F8[q] == 1) bF7F8 = false;
      if(F11[q] == 1) bF11 = false;

      functions[funcs[q]]();
    }
    if(Controller.ButtonB.pressing()) 
    {
      q = 7;

      if(F1F2F5F6[q] == 1) bF1F2F5F6 = false;
      if(F3F4[q] == 1) bF3F4 = false;
      if(F7F8[q] == 1) bF7F8 = false;
      if(F11[q] == 1) bF11 = false;

      functions[funcs[q]]();
    }
    if(Controller.ButtonUp.pressing()) 
    {
      q = 8;

      if(F1F2F5F6[q] == 1) bF1F2F5F6 = false;
      if(F3F4[q] == 1) bF3F4 = false;
      if(F7F8[q] == 1) bF7F8 = false;
      if(F11[q] == 1) bF11 = false;

      functions[funcs[q]]();
    }
    if(Controller.ButtonDown.pressing()) 
    {
      q = 9;

      if(F1F2F5F6[q] == 1) bF1F2F5F6 = false;
      if(F3F4[q] == 1) bF3F4 = false;
      if(F7F8[q] == 1) bF7F8 = false;
      if(F11[q] == 1) bF11 = false;

      functions[funcs[q]]();
    }
    if(Controller.ButtonLeft.pressing()) 
    {
      q = 10;

      if(F1F2F5F6[q] == 1) bF1F2F5F6 = false;
      if(F3F4[q] == 1) bF3F4 = false;
      if(F7F8[q] == 1) bF7F8 = false;
      if(F11[q] == 1) bF11 = false;

      functions[funcs[q]]();
    }
    if(Controller.ButtonRight.pressing()) 
    {
      q = 11;

      if(F1F2F5F6[q] == 1) bF1F2F5F6 = false;
      if(F3F4[q] == 1) bF3F4 = false;
      if(F7F8[q] == 1) bF7F8 = false;
      if(F11[q] == 1) bF11 = false;

      functions[funcs[q]]();
    }

    if(bF1F2F5F6 && bF7F8 && bF11) liftMotors.stop();
    if(bF3F4 && bF7F8) intakeMotors.stop();
    
    if(!bF1F2F5F6) bF1F2F5F6 = true;
    if(!bF3F4) bF3F4 = true;
    if(!bF7F8) bF7F8 = true;
    if(!bF11) bF11 = true;

    bool c = true;

    if(dType == 0) //tank
    {
      if(abs(Controller.Axis3.position()) > threshold3) leftMotors.spin(fwd, Controller.Axis3.position(), pct);
      else if(abs(Controller.Axis3.position()) <= threshold3) leftMotors.stop();
      if(abs(Controller.Axis2.position()) > threshold2) rightMotors.spin(fwd, Controller.Axis2.position(), pct);
      else if(abs(Controller.Axis2.position()) <= threshold2) rightMotors.stop();
    }
    // (x/21.5)^3
    else if(dType == 1) //1 stick arcade
    {
      int leftSpeed = Controller.Axis3.position() + Controller.Axis4.position();
      int rightSpeed = Controller.Axis3.position() - Controller.Axis4.position();
      if(!wTurn)
      {  
        if(abs(Controller.Axis4.position()) > threshold4 || abs(Controller.Axis3.position()) > threshold3)
        {
          leftMotors.spin(fwd, leftSpeed, pct);
          rightMotors.spin(fwd, rightSpeed, pct);
        }
        else if(abs(Controller.Axis4.position()) < 5 && abs(Controller.Axis3.position()) < 5)
        {
          driveMotors.stop();
        }
        else if(abs(Controller.Axis4.position()) < threshold4 || abs(Controller.Axis3.position()) < threshold3)
        {
          leftMotors.spin(fwd, leftSpeed - ((threshold3 + threshold4) / 4), pct);
          rightMotors.spin(fwd, rightSpeed - ((threshold3 + threshold4) / 4), pct);
        }
      }
      else
      {
        if(abs(Controller.Axis4.position()) > threshold4 || abs(Controller.Axis3.position()) > threshold3)
        {
          leftMotors.spin(fwd, leftSpeed / 2, pct);
          rightMotors.spin(fwd, rightSpeed / 2, pct);
        }
        else
        {
          driveMotors.stop();
        }
      }
    }
    else if(dType == 2) //2 stick arcade
    {
      int leftSpeed = Controller.Axis3.position() + Controller.Axis1.position();
      int rightSpeed = Controller.Axis3.position() - Controller.Axis1.position();
      if(!wTurn)
      {
        if(abs(Controller.Axis1.position()) > threshold1 || abs(Controller.Axis3.position()) > threshold3)
        {
          if(!c)
          {
            leftMotors.spin(fwd, leftSpeed, pct);
            rightMotors.spin(fwd, rightSpeed, pct);
          }
          else
          {
            leftMotors.spin(fwd, pow(leftSpeed / (2 * 21.5), 3), pct);
            rightMotors.spin(fwd, pow(rightSpeed / (2 * 21.5), 3), pct);
          }
        }
        else
        {
          driveMotors.stop();
        }
      }
      else
      {
        if(abs(Controller.Axis1.position()) > threshold4 || abs(Controller.Axis3.position()) > threshold3)
        {
          if(!c)
          {
            leftMotors.spin(fwd, leftSpeed / 2, pct);
            rightMotors.spin(fwd, rightSpeed / 2, pct);
          }
          else
          {
            leftMotors.spin(fwd, pow((leftSpeed / 2) / 21.5, 3), pct);
            rightMotors.spin(fwd, pow((rightSpeed / 2) / 21.5, 3), pct);
          }
        }
        else
        {
          driveMotors.stop();
        }
      }
    }

    wait(5, msec);
  }
}
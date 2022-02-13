#include "vex.h"
#include "functions.h"
#include "configvalues.h"
#include <cmath>

using namespace vex;

void auton_CycleTower(e_teamColor p_teamColor, e_teamSide p_teamSide)
{
  timer autonTimer;
  autonTimer.reset();
  //launch ball with hood
  liftMotors.spin(fwd, -100, pct);
  wait(500, msec);
  liftMotors.stop();

  PIDForward(523.5, 0, 540, 0.3);
  if(p_teamSide == sideLeft) PIDTurn(-47);
  else if(p_teamSide == sideRight) PIDTurn(51.825);
  
  intakeMotors.spin(fwd, 100, pct);
  f_forward(500, 65, 2000);
  liftMotors.spin(fwd, -85, pct);

  t1.reset();
  if(p_teamColor == Red)
  {
    while(!(blueMin < opticalSensor.hue() && opticalSensor.hue() < blueMax)) 
    {
      if(t1.time(msec) > 5000) break;
      wait(5, msec);
    }

    if(t1.time(msec) < 8000)
    {
      if(p_teamSide == sideLeft)
      {
        rightMotors.spin(fwd, 100, pct);
        leftMotors.spin(fwd, -15, pct);
      }
      else if(p_teamSide == sideRight)
      {
        rightMotors.spin(fwd, -15, pct);
        leftMotors.spin(fwd, 100, pct);
      }
      waitUntil(blueMin < opticalSensor.hue() && opticalSensor.hue() < blueMax);
      driveMotors.stop();
    }
  }
  else if(p_teamColor == Blue)
  {
    while(!((redMin < opticalSensor.hue() && opticalSensor.hue() < redMax) || (redMin1 < opticalSensor.hue() && opticalSensor.hue() < redMax1)))
    {
      if(t1.time(msec) > 3500) break;
      wait(5, msec);
    }

    if(t1.time(msec) < 8000)
    {
      if(p_teamSide == sideLeft)
      {
        rightMotors.spin(fwd, 100, pct);
        leftMotors.spin(fwd, -15, pct);
      }
      else if(p_teamSide == sideRight)
      {
        rightMotors.spin(fwd, -15, pct);
        leftMotors.spin(fwd, 100, pct);
      }
      waitUntil((redMin < opticalSensor.hue() && opticalSensor.hue() < redMax) || (redMin1 < opticalSensor.hue() && opticalSensor.hue() < redMax1));
      driveMotors.stop();
    }
  }

  intakeMotors.stop();
  wait(0.235, sec);
  liftMotors.stop();

  f_forward(-300);

  if(p_teamSide == sideLeft) PIDTurn(-179);
  else if(p_teamSide == sideRight) PIDTurn(179);

  f_forward(-300, 70, 2000);

  waitUntil(autonTimer.time(msec) > 14000);

  intakeMotors.spin(fwd, 100, pct);
  liftMotors.spin(fwd, -100, pct);
  wait(5, sec);
}
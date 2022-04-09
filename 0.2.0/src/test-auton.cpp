#include "vex.h"
#include "odom.h"
#include "auton-functions.h"
#include <vector>

int findVTurnDir(int currentPos)
{
  if(currentPos < 158) return -1;
  return 1;
}

void testAuton(){

  PID slow(0.15);
  driveRelative(-36, 0, slow);

  /*
  frontVisionSensor.setSignature(REDMOGO);
  Brain.Screen.setFont(mono60);

  while(true)
  {
    frontVisionSensor.takeSnapshot(REDMOGO);

    double currentPos = frontVisionSensor.largestObject.centerX;

    if((!obj.exists))
    {
      Brain.Screen.clearScreen();
      Brain.Screen.setCursor(1, 1);
      Brain.Screen.print("OBJECT NOT FOUND");
      Brain.Screen.render();
    }
    double error = 158 - currentPos;
    double pow = error * 0.125;

    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1, 1);
    Brain.Screen.print("%d", currentPos);
    Brain.Screen.setCursor(2, 1);
    Brain.Screen.print("%d", error);
    Brain.Screen.render();

    leftMotors.spin(fwd, -pow, pct);
    rightMotors.spin(fwd, pow, pct);

    wait(1, msec);
    if(error < 1) break;
  }
  driveMotors.stop();*/
}
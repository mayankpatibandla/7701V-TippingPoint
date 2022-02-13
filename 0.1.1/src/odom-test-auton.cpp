#include "vex.h"
#include "position-tracking.h"
#include "auton-functions.h"

using namespace vex;

void odomTestAuton(){
  Controller.Screen.clearLine(3);
  Controller.Screen.print("1");
  turnToAngle(M_PI_2);
  wait(5000, msec);
  turnToAngle(M_PI);
  turnToAngle(45 * M_PI/180);
  turnToAngle(225 * M_PI/180);
  goToX(0);
  goTo(0, 2);
  Controller.Screen.clearLine(3);
  Controller.Screen.print("2");
  wait(5000, msec);
  turnToPoint(1, 1);
  Controller.Screen.clearLine(3);
  Controller.Screen.print("3");
  wait(5000, msec);
  turnToPoint(100, 100);
  Controller.Screen.clearLine(3);
  Controller.Screen.print("4");
}
#include "vex.h"
#include "position-tracking.h"
#include "auton-functions.h"

using namespace vex;

void odomTestAuton(){
  Controller.Screen.clearLine(3);
  Controller.Screen.print("1");
  turnTo(M_PI_2);
  Controller.Screen.clearLine(3);
  Controller.Screen.print("2");
  wait(5000, msec);
  Controller.Screen.clearLine(3);
  Controller.Screen.print("3");
  turnTo(0, 0);
  Controller.Screen.clearLine(3);
  Controller.Screen.print("4");
}
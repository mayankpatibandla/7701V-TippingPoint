#include "vex.h"
#include "odom.h"
#include "auton-functions.h"
#include <vector>

void testAuton(){
  /*PID testPID(0.165, 0.01, 0, 6);
  PID turnTestPID(43.5, 0, 10*0);*/
  //goToPoint(24, 0, 0, turnTestPID, testPID);
  //driveRelative(48, 0, testPID);
  turnToAngle(M_PI - 0.0001);
  wait(250, msec);
  turnToAngle(M_PI_2 -0.0001);
  wait(250, msec);
  turnToAngle(M_PI * 3/2);
}
#include "vex.h"
#include "functions.h"
#include "odom.h"

using namespace vex;

void auton_Catapult()
{
  //TURN TO ANGLE
  /*odom::turnToAngle(45);
  wait(1.5, sec);
  odom::turnToAngle(-90);
  wait(1.5, sec);
  odom::turnToAngle(180);
  

  wait(5, sec);


  //TURN TO POINT
  odom::turnToPoint(20, 20);
  wait(1.5, sec);
  odom::turnToPoint(-15, 0);
  wait(1.5, sec);
  odom::turnToPoint(0, -20);


  wait(5, sec);*/


  //GO TO POINT
  odom::goToPoint(20, 20);
  wait(1.5, sec);
  odom::goToPoint(-15, 0);
  wait(1.5, sec);
  odom::goToPoint(0, -20);
  wait(1.5, sec);
}
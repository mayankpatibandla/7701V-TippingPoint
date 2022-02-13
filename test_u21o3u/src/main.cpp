/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\mayan                                            */
/*    Created:      Mon Jan 24 2022                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

rotation Potentiometer(PORT2);
motor backlift(PORT1);

thread backLiftThread;
void moveBacklift(double target, bool direction){
  if(direction){
    waitUntil(Potentiometer.angle(deg) > target);
  }
  else{
    waitUntil(Potentiometer.angle(deg) < target);
  }
  backlift.stop(hold);
}

void auton(){
  backlift.spin(reverse);
  backLiftThread = thread([]{moveBacklift(36, true);});

  backlift.spin(forward);
  backLiftThread = thread([]{moveBacklift(90, false);});
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  
}

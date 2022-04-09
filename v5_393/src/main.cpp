/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Using 393s                                                */
/*                                                                            */
/*    The Motor 393 isn't a normal V5 Motor, it is a 393 motor connected      */
/*    to a motor controller 29. This program spins the Motor at different     */
/*    velocities for fixed periods.                                           */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Motor393G            motor29       G
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  wait(1, seconds);
  Motor393G.spin(forward);
  wait(1, seconds);
  Motor393G.spin(reverse);
  Motor393G.setVelocity(10, percent);
  wait(3, seconds);
  Motor393G.setVelocity(65, percent);
  Motor393G.spin(forward);
  wait(4, seconds);
  Motor393G.setVelocity(100, percent);
  Motor393G.spin(reverse);
  wait(5, seconds);
  Motor393G.setVelocity(0, percent);

}

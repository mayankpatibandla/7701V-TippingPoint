/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Using Quad Encoders                                       */
/*                                                                            */
/*    This program will spin the Arm motor and print out the position         */
/*    in degrees until it reaches 100 degrees and then the Arm Motor          */
/*    will stop moving.                                                       */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// EncoderA             encoder       A, B
// ArmMotor             motor         8
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  EncoderA.setPosition(0, degrees);
  ArmMotor.setVelocity(20, percent);
  ArmMotor.spin(forward);
  while (!(EncoderA.position(degrees) > 100)) {
    Brain.Screen.clearScreen();
    Brain.Screen.print("%.2f", EncoderA.position(degrees));
    Brain.Screen.setCursor(1, 1);
    wait(100, msec);
  }
  ArmMotor.stop();
}

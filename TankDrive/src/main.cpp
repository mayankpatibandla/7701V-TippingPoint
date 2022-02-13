/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\mayan                                            */
/*    Created:      Tue Sep 14 2021                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Motor1               motor         1               
// Motor2               motor         2               
// Motor3               motor         3               
// Motor4               motor         4               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

motor_group leftMotors = motor_group(Motor1, Motor2);
motor_group rightMotors = motor_group(Motor3, Motor4);

controller mainController;

int main(){
  while(true){
    int leftSpeed = mainController.Axis3.position();
    int rightSpeed = mainController.Axis2.position();

    leftMotors.setVelocity(leftSpeed, pct);
    rightMotors.setVelocity(rightSpeed, pct);

    leftMotors.spin(fwd);
    rightMotors.spin(fwd);
  }
}

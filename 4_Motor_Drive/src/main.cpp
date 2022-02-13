/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\mayan                                            */
/*    Created:      Tue Sep 07 2021                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

controller Controller = controller(primary);
motor frontLeftMotor = motor(PORT13, false);
motor frontRightMotor = motor(PORT12, true);
motor backLeftMotor = motor(PORT1, false);
motor backRightMotor = motor(PORT2, true);

motor_group rightMotors = motor_group(frontRightMotor, backRightMotor);
motor_group leftMotors = motor_group(frontLeftMotor, backLeftMotor);
motor_group driveMotors = motor_group(frontLeftMotor, frontRightMotor, backLeftMotor, backRightMotor);

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
int threshold3 = 20, threshold4 = 20;

bool wTurn = false;
while(true){
int leftSpeed = Controller.Axis3.position() - Controller.Axis1.position();
int rightSpeed = Controller.Axis3.position() + Controller.Axis1.position();
if(!wTurn)
{  
  if(abs(Controller.Axis1.position()) > threshold4 || abs(Controller.Axis3.position()) > threshold3)
  {
    leftMotors.spin(fwd, leftSpeed, pct);
    rightMotors.spin(fwd, rightSpeed, pct);
  }
  else if(abs(Controller.Axis1.position()) < 5 && abs(Controller.Axis3.position()) < 5)
  {
    driveMotors.stop();
  }
  else if(abs(Controller.Axis1.position()) < threshold4 || abs(Controller.Axis3.position()) < threshold3)
  {
    leftMotors.spin(fwd, leftSpeed - ((threshold3 + threshold4) / 4), pct);
    rightMotors.spin(fwd, rightSpeed - ((threshold3 + threshold4) / 4), pct);
  }
}
else
{
  if(abs(Controller.Axis1.position()) > threshold4 || abs(Controller.Axis3.position()) > threshold3)
  {
    leftMotors.spin(fwd, leftSpeed / 2, pct);
    rightMotors.spin(fwd, rightSpeed / 2, pct);
  }
  else
  {
    driveMotors.stop();
  }
}
}
  
}

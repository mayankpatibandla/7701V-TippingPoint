#include "vex.h"
#include "autons.h"

using namespace vex;

void driver(){
fourBarMotor.setBrake(hold);
leftTilterMotor.setBrake(hold);
rightTilterMotor.setBrake(hold);

int threshold3 = 20, threshold4 = 20;

bool clawPistons = false, clawWasPressed = false;

while(true){
//auton test
if(Controller.ButtonLeft.pressing())odomTestAuton();


if(Controller.ButtonA.pressing()){
  if(!clawWasPressed)
    clawPistons = !clawPistons;
  clawWasPressed = true;
}
else{
  clawWasPressed = false;
}
leftClawSolenoid.set(clawPistons);
rightClawSolenoid.set(clawPistons);

if(Controller.ButtonL1.pressing()){
  fourBarMotor.spin(fwd, 100, pct);
}
else if(Controller.ButtonL2.pressing()){
  fourBarMotor.spin(fwd, -100, pct);
}
else{
  fourBarMotor.stop();
}

if(Controller.ButtonR1.pressing()){
  tilterMotors.spin(fwd, 100, pct);
}
else if(Controller.ButtonR2.pressing()){
  tilterMotors.spin(fwd, -10, pct);
}
else{
  tilterMotors.stop();
}

if(Controller.ButtonX.pressing()){
  ringLiftMotor.spin(fwd, 100, pct);
}
else if(Controller.ButtonY.pressing()){
  ringLiftMotor.spin(fwd, -100, pct);
}
else{
  ringLiftMotor.stop();
}

int leftSpeed = Controller.Axis3.position() + Controller.Axis1.position();
int rightSpeed = Controller.Axis3.position() - Controller.Axis1.position();
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
wait(1, msec);}
}
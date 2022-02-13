#include "vex.h"
#include "autons.h"

using namespace vex;

bool secondstart = false;

void driver(){
int threshold3 = 20, threshold1 = 20;

bool clawPistons;
if(!secondstart){
  clawPistons = true;
}
else{
  clawPistons = leftClawSolenoid.value();
}

secondstart = true;

bool clawWasPressed = false;

while(true){
//auton test
if(Controller.ButtonLeft.pressing())auton();

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

if(fourBarBottomLimit.pressing()){
  fourBarMotors.setStopping(hold);
}
else{
  fourBarMotors.setStopping(coast);
}

if(Controller.ButtonL1.pressing()){
  fourBarMotors.spin(fwd, 100, pct);
}
else if(Controller.ButtonL2.pressing() && !fourBarBottomLimit.pressing()){
  fourBarMotors.spin(fwd, -100, pct);
}
else{
  fourBarMotors.stop();
}

if(Controller.ButtonR1.pressing()){
  backLiftMotor.spin(fwd, 100, pct);
}
else if(Controller.ButtonR2.pressing()){
  backLiftMotor.spin(fwd, -100, pct);
}
else{
  backLiftMotor.stop();
}

/*if(Controller.ButtonX.pressing()){
  ringLiftMotor.spin(fwd, 100, pct);
}
else if(Controller.ButtonY.pressing()){
  ringLiftMotor.spin(fwd, -100, pct);
}
else{
  ringLiftMotor.stop();
}*/

int leftSpeed = Controller.Axis3.position() + Controller.Axis1.position();
int rightSpeed = Controller.Axis3.position() - Controller.Axis1.position();
if(abs(Controller.Axis1.position()) > threshold1 || abs(Controller.Axis3.position()) > threshold3)
{
  leftMotors.spin(fwd, leftSpeed * 1, pct);
  rightMotors.spin(fwd, rightSpeed * 1, pct);
}
else if(abs(Controller.Axis1.position()) < threshold1 && abs(Controller.Axis3.position()) < threshold3)
{
  driveMotors.stop();
}
wait(1, msec);}
}
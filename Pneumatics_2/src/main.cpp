#include "vex.h"

using namespace vex;
brain Brain = brain();
controller Controller = controller(primary);

motor frontLeftMotor = motor(PORT13, true);
motor frontRightMotor = motor(PORT12, false);
motor backLeftMotor = motor(PORT10, true);
motor backRightMotor = motor(PORT2, false);

motor fourBarMotor = motor(PORT9, gearSetting::ratio36_1);
motor ringLiftMotor = motor(PORT6);

motor leftTilterMotor = motor(PORT15, gearSetting::ratio36_1);
motor rightTilterMotor = motor(PORT18, gearSetting::ratio36_1, true);

motor_group rightMotors = motor_group(frontRightMotor, backRightMotor);
motor_group leftMotors = motor_group(frontLeftMotor, backLeftMotor);
motor_group driveMotors = motor_group(frontLeftMotor, frontRightMotor, backLeftMotor, backRightMotor);

motor_group tilterMotors = motor_group(leftTilterMotor, rightTilterMotor);

digital_out leftClawPiston = digital_out(Brain.ThreeWirePort.A);
digital_out rightClawPiston = digital_out(Brain.ThreeWirePort.B);

int main() {
fourBarMotor.setBrake(hold);
leftTilterMotor.setBrake(hold);
rightTilterMotor.setBrake(hold);

int threshold3 = 20, threshold4 = 20;

bool wTurn = false;

bool clawPistons = false, clawWasPressed = false;

while(true){
if(Controller.ButtonA.pressing()){
  if(!clawWasPressed)
    clawPistons = !clawPistons;
  clawWasPressed = true;
}
else{
  clawWasPressed = false;
}
leftClawPiston.set(clawPistons);
rightClawPiston.set(clawPistons);

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
wait(1, msec);}
return 0;}
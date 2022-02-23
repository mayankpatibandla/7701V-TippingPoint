#include "vex.h"
#include "autons.h"

using namespace vex;

void driver(){
  motorInit();

  const int threshold3 = 20, threshold1 = 20;

  bool backLiftWasPressed = false;
  bool backLift = false;

  bool clawWasPressed = false;
  bool claw = false;

  bool ringLiftWasPressed = false;
  bool ringLift = false;

  while(true){
    //auton test

    if(Controller.ButtonY.pressing()){
      if(!backLiftWasPressed)
        backLift = !backLift;
      backLiftWasPressed = true;
    }
    else{
      backLiftWasPressed = false;
    }
    backLiftSolenoid.set(backLift);

    if(Controller.ButtonA.pressing()){
      if(!clawWasPressed)
        claw = !claw;
      clawWasPressed = true;
    }
    else{
      clawWasPressed = false;
    }
    leftClawSolenoid.set(claw);
    rightClawSolenoid.set(claw);

    if(Controller.ButtonL1.pressing()){
      fourBarMotor.spin(fwd, 100, pct);
    }
    else if(Controller.ButtonL2.pressing()){
      fourBarMotor.spin(fwd, -100, pct);
    }
    else{
      fourBarMotor.stop();
    }

    if(Controller.ButtonX.pressing()){
      if(!ringLiftWasPressed)
        ringLift = !ringLift;
      ringLiftWasPressed = true;
    }
    else{
      ringLiftWasPressed = false;
    }

    if((Controller.ButtonUp.pressing() || ringLift)){
      ringLiftMotor.spin(fwd, 100, pct);
    }
    else if(Controller.ButtonDown.pressing()){
      ringLiftMotor.spin(fwd, -100, pct);
    }
    else{
      ringLiftMotor.stop();
    }

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
    wait(1, msec);
  }
}
#include "vex.h"
#include "autons.h"

using namespace vex;

bool secondstart = false;

void driver(){
  motorInit();

  const int threshold3 = 20, threshold1 = 20;

  secondstart = true;

  bool backLiftWasPressed;
  bool backLift;

  while(true){
    //auton test

    if(Controller.ButtonA.pressing()){
      if(!backLiftWasPressed)
        backLift = !backLift;
      backLiftWasPressed = true;
    }
    else{
      backLiftWasPressed = false;
    }
    backLiftSolenoid.set(backLift);

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
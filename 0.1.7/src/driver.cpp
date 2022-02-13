#include "vex.h"
#include "autons.h"

using namespace vex;

bool secondstart = false;

void driver(){
  fourBarLimit_task.suspend();
  backLiftLimit_task.suspend();

  const int threshold3 = 20, threshold1 = 20;

  bool clawPistons;
  if(!secondstart){
    clawPistons = true;
  }
  else{
    clawPistons = leftClawSolenoid.value();
  }

  secondstart = true;

  bool clawWasPressed = false;

  bool ringLift = false;
  bool ringLiftWasPressed = false;

  bool backLift = false;
  bool backLiftWasPressed = false;

  bool manualOverride = false;
  bool manualOverrideWasPressed = false;

  while(true){
    //auton test
    if(Controller.ButtonRight.pressing()){
      if(!Competition.isCompetitionSwitch() && !Competition.isFieldControl()){
        auton();
      }
      else{
        if(!manualOverrideWasPressed)
          manualOverride = !manualOverride;
        manualOverrideWasPressed = true;
      }
    }
    else{
      manualOverrideWasPressed = false;
    }

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

    if(!fourBarBottomLimit.pressing()){
      fourBarMotors.setStopping(hold);
    }
    else{
      fourBarMotors.setStopping(coast);
    }

    if(Controller.ButtonL1.pressing() && (!fourBarTopLimit.pressing() || manualOverride)){
      fourBarMotors.spin(fwd, 100, pct);
    }
    else if(Controller.ButtonL2.pressing() && (!fourBarBottomLimit.pressing() || manualOverride)){
      fourBarMotors.spin(fwd, -100, pct);
    }
    else{
      fourBarMotors.stop();
    }

    const double backLiftTarget = -300;
    const double backLiftKp = 0.1;
    if(Controller.ButtonLeft.pressing()){
      if(!backLiftWasPressed)
        backLift = !backLift;
      backLiftWasPressed = true;
    }
    else{
      backLiftWasPressed = false;
    }
    Controller.Screen.clearLine(3);
    Controller.Screen.print(backLiftTopLimit.pressing());
    if(Controller.ButtonR1.pressing() && (!backLiftTopLimit.pressing() || manualOverride)){
      backLiftMotor.spin(fwd, 100, pct);
      backLift = false;
    }
    else if(Controller.ButtonR2.pressing()){
      backLiftMotor.spin(fwd, -100, pct);
      backLift = false;
    }
    else if(backLift){
      double error = backLiftTarget - backLiftMotor.position(deg);
      double pow = error * backLiftKp;
      backLiftMotor.spin(fwd, pow, pct);
    }
    else{
      backLiftMotor.stop();
    }

    if(Controller.ButtonX.pressing()){
      if(!ringLiftWasPressed)
        ringLift = !ringLift;
      ringLiftWasPressed = true;
    }
    else{
      ringLiftWasPressed = false;
    }

    if(Controller.ButtonB.pressing() || ringLift){
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
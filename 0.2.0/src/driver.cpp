#include "vex.h"
#include "autons.h"
#include "auton-functions.h"

using namespace vex;

double curveJoystick(double input, const double t){
  return std::exp(t * (std::abs(input) - 100) / 1000) * input;
}

void driver(){
  motorInit();

  const double deadband = 20;

  const double forwardCurve = 15*0;
  const double turnCurve = 30*0;

  bool ringLift = false;
  bool ringLiftWasPressed = false;
  bool ringLiftJam = false;
  bool ringLiftWasJammed = false;
  const double ringLiftJamWait = 1000;
  const double ringLiftResetWait = 1500;
  timer ringLiftJamTimer;
  timer ringLiftJamCooldownTimer;

  timer dumpAirTimer;

  bool manualOverride = false;
  bool manualOverrideWasPressed = false;

  Controller.ButtonA.pressed(toggleClaw);
  Controller.ButtonY.pressed(toggleBackLift);

  while(true){
    //auton test
    if(Controller.ButtonRight.pressing()){
      if(!Competition.isCompetitionSwitch() && !Competition.isFieldControl()){
        uint32_t autonStart = Brain.Timer.system();
        auton();
        double autonTime = (Brain.Timer.system() - autonStart) / 1000.;
        Controller.Screen.clearLine(3);
        Controller.Screen.print("Auton Time %.3f sec", autonTime);
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

    if(Controller.ButtonLeft.pressing() && Controller.ButtonUp.pressing() && Controller.ButtonR1.pressing() && Controller.ButtonR2.pressing() && dumpAirTimer.time(msec) > 9){
      toggleClaw();
      dumpAirTimer.reset();
    }

    //fourbar
    if(Controller.ButtonL1.pressing() && (fourBarRotationSensor.angle(deg) < fourBarMaxPos) && !manualOverride){
      fourBarMotor.spin(fwd, 12, volt);
    }
    else if(Controller.ButtonL2.pressing() && (fourBarRotationSensor.angle(deg) > fourBarMinPos) && !manualOverride){
      fourBarMotor.spin(fwd, -12, volt);
    }
    else{
      if(fourBarRotationSensor.angle(deg) < fourBarMaxPos || fourBarRotationSensor.angle(deg) > fourBarMinPos)
        fourBarMotor.stop(hold);
      else
        fourBarMotor.stop(coast);
    }

    //ring lift
    if(Controller.ButtonX.pressing()){
      if(!ringLiftWasPressed){
        ringLift = !ringLift;
        ringLiftJamCooldownTimer.reset();
      }
      ringLiftWasPressed = true;
    }
    else{
      ringLiftWasPressed = false;
    }

    if(Controller.ButtonB.pressing() || ringLiftJam){
      ringLiftMotor.spin(fwd, -12, volt);
    }
    else if(Controller.ButtonX.pressing() || ringLift){
      ringLiftMotor.spin(fwd, 12 * 0.925, volt);
      ringLiftJam = false;
    }
    else{
      ringLiftMotor.stop();
    }

    if(ringLift && std::abs(ringLiftMotor.velocity(pct)) < 20 && ringLiftJamCooldownTimer.time(msec) > ringLiftResetWait){
      if(!ringLiftWasJammed)
        ringLiftJamTimer.reset();
      ringLiftJam = true;  
      ringLiftWasJammed = true;
    }

    if(ringLiftJam && ringLiftJamTimer.time(msec) > ringLiftJamWait && std::abs(ringLiftMotor.velocity(pct)) > 20){
      ringLiftJamCooldownTimer.reset();
      ringLiftJam = false;
    }

    /*Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1, 1);
    Brain.Screen.print("ringLift: %s", ringLift ? "true" : "false");
    Brain.Screen.setCursor(2, 1);
    Brain.Screen.print("isJam: %s", ringLiftJam ? "true" : "false");
    Brain.Screen.setCursor(3, 1);
    Brain.Screen.print("wasJam: %s", ringLiftWasJammed ? "true" : "false");
    Brain.Screen.setCursor(4, 1);
    Brain.Screen.print("jamTime: %f", ringLiftJamTimer.time(msec));
    Brain.Screen.setCursor(5, 1);
    Brain.Screen.print("coolTime: %f", ringLiftJamCooldownTimer.time(msec));
    Brain.Screen.render();*/

    //drive
    int leftSpeed = curveJoystick(Controller.Axis3.position(), forwardCurve) + curveJoystick(Controller.Axis1.position(), turnCurve);
    int rightSpeed = curveJoystick(Controller.Axis3.position(), forwardCurve) - curveJoystick(Controller.Axis1.position(), turnCurve);
    if(abs(Controller.Axis1.position()) > deadband || abs(Controller.Axis3.position()) > deadband)
    {
      leftMotors.spin(fwd, leftSpeed * 0.12, volt);
      rightMotors.spin(fwd, rightSpeed * 0.12, volt);
    }
    else driveMotors.stop();

    wait(5, msec);
  }
}
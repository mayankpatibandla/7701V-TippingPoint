#include "vex.h"
#include "position-tracking.h"
#include "auton-config.h"
#include "autons.h"

using namespace vex;

void auton(){
  switch(tc){
    case RED:{
      switch(ts){
        case LEFT:{
          //RED LEFT
          leftSideAuton();
          //odomTestAuton();
        }break;
        case RIGHT:{
          //RED RIGHT
          rightSideAuton();
        }break;
      }
    }break;
    case BLUE:{
      switch(ts){
        case LEFT:{
          //BLUE LEFT
          leftSideAuton();
        }break;
        case RIGHT:{
          //BLUE RIGHT
          rightSideAuton();
        }break;
      }
    }
    case NONE:{
      
    }
    case SKILLS:{
      //skills auton
      skillsAuton();
    }
  }
}

void PIDTurn(double target, int timeout, PID pid){
  timer PIDtimer;
  PIDtimer.reset();

  double currentPos = positionTracking::getTheta();
  double pow = 100;
  
  double error = target - currentPos;
  double integral = 0;
  double derivative = 0;

  double prevError = error;

  const double errorAcc = 0.05, powAcc = 5;

  while(std::abs(error) > errorAcc || std::abs(pow) > powAcc){
    //Controller.Screen.print(" __ %f __ %f __ %f", error, currentPos, target);
    //timeout
    if(timeout != 0 && PIDtimer.time(msec) > timeout) break;

    //update current pos
    currentPos = positionTracking::getTheta();
    //calculate error
    error = target - currentPos;

    //add error to integral
    integral += error;

    //calculate derivative and update previous error
    derivative = error - prevError;
    prevError = error;

    //calculate output power
    pow = error * pid.kP + integral * pid.kI + derivative * pid.kD;

    //assign output power to motors
    leftMotors.spin(forward, pow, pct);
    rightMotors.spin(reverse, pow, pct);

    //sleep for dT
    this_thread::sleep_for(pid.dT);
  }
  driveMotors.stop();
}

void turnPos(double target, int timeout){
  double currentPos = positionTracking::getTheta();
  while(std::abs(target - currentPos) > 0.087){
    currentPos = positionTracking::getTheta();
    if(currentPos < target){
      leftMotors.spin(fwd, 10, pct);
      rightMotors.spin(fwd, -10, pct);
    }
    else if(currentPos > target){
      leftMotors.spin(fwd, -10, pct);
      rightMotors.spin(fwd, 10, pct);
    }
  }
  driveMotors.stop();
}

//turns to theta (radians)
void turnToAngle(double theta, int timeout){
  PIDTurn(theta, timeout, turnPID_R);
  //turnPos(theta, timeout);
}

//turns to face point (x, y)
void turnToPoint(double x, double y, int timeout){
  double theta = (atan2(positionTracking::getY(), positionTracking::getX()) + M_PI) -
  acos(
    (
      (x*x + y*y) - (positionTracking::getX()*positionTracking::getX() + positionTracking::getY()*positionTracking::getY()) -
      ((positionTracking::getX() - x)*(positionTracking::getX() - x) + (positionTracking::getY() - y)*(positionTracking::getY() - y))
    ) /
    (
      -2 * 
      std::sqrt(
        positionTracking::getX()*positionTracking::getX() + positionTracking::getY()*positionTracking::getY()
      ) *
      std::sqrt(
        (positionTracking::getX() - x)*(positionTracking::getX() - x) + (positionTracking::getY() - y)*(positionTracking::getY() - y)
      )
    )
  );

  Controller.Screen.clearLine(3);
  Controller.Screen.print("%f", theta);
  wait(1, sec);
  //call turnTo(double theta)
  turnToAngle(theta, timeout);
}

void goToX(double x, int timeout){
  turnToAngle(0, timeout);
  while(std::abs(x - positionTracking::getX()) > 0.125){
    if(x > positionTracking::getX()){
      driveMotors.spin(forward, 25, pct);
    }
    else{
      driveMotors.spin(reverse, 25, pct);
    }
  }
  driveMotors.stop();
}

void goToY(double y, int timeout){
  turnToAngle(-M_PI_2, timeout);
  while(std::abs(y - positionTracking::getY()) > 0.125){
    if(y > positionTracking::getY()){
      driveMotors.spin(forward, 25, pct);
    }
    else{
      driveMotors.spin(reverse, 25, pct);
    }
  }
  driveMotors.stop();
}

void goToXY(double x, double y, int timeout){
  goToX(x, timeout);
  goToY(y, timeout);
}

void toggleClaw(){
  leftClawSolenoid.set(!leftClawSolenoid.value());
  rightClawSolenoid.set(!rightClawSolenoid.value());
}

void setClaw(bool value){
  leftClawSolenoid.set(value);
  rightClawSolenoid.set(value);
}
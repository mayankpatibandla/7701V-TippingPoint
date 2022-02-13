#include "vex.h"
#include "position-tracking.h"
#include "auton-config.h"
#include "autons.h"

using namespace vex;

void fourBarLimit(){
  while(true){
    if(fourBarBottomLimit.pressing()){
      if(fourBarMotors.velocity(pct) < 0){
        fourBarMotors.stop();
      }
    }
  }
}

void auton(){
  switch(tc){
    case RED:{
      switch(ts){
        case LEFT:{
          switch(av){
            case AWP:{
              //RED LEFT AWP
              leftSideAWPAuton();
            }break;
            case NEUTRAL:{
              //RED LEFT NETURAL
              leftSideNeutralAuton();
            }break;
          }
        }break;
        case RIGHT:{
          switch(av){
            case AWP:{
              //RED RIGHT AWP
              rightSideAWPAuton();
            }break;
            case NEUTRAL:{
              //RED RIGHT NETURAL
              rightSideNeutralAuton();
            }break;
          }
        }break;
      }
    }break;
    case BLUE:{
      switch(ts){
        case LEFT:{
          switch(av){
            case AWP:{
              //BLUE LEFT AWP
              leftSideAWPAuton();
            }break;
            case NEUTRAL:{
              //BLUE LEFT NETURAL
              leftSideNeutralAuton();
            }break;
          }
        }break;
        case RIGHT:{
          switch(av){
            case AWP:{
              //BLUE RIGHT AWP
              rightSideAWPAuton();
            }break;
            case NEUTRAL:{
              //BLUE RIGHT NETURAL
              rightSideNeutralAuton();
            }break;
          }
        }break;
      }
    }break;
    case SKILLS:{
      //skills auton
      skillsAuton();
    }break;
    case TEST:{
      //test auton
      odomTestAuton();
    }break;
    case NONE:{
      
    }break;
  }
}

void PIDTurn(double target, int timeout, PID pid){
  timer PIDtimer;
  PIDtimer.reset();

  double currentPos = positionTracking::getThetaWrapped();
  double pow = 100;
  
  double error = target - currentPos;
  double integral = 0;
  double derivative = 0;

  double prevError = error;

  const double errorAcc = 0.075, powAcc = 5;

  while(std::abs(error) > errorAcc || std::abs(pow) > powAcc){
    //Controller.Screen.print(" __ %f __ %f __ %f", error, currentPos, target);
    //timeout
    if(timeout != 0 && PIDtimer.time(msec) > timeout) break;

    //update current pos
    currentPos = positionTracking::getThetaWrapped();
    //calculate error
    double absError = target - currentPos;

    //angle wrap fix
    if(absError < M_PI) error = absError;
    else error = absError - M_TWOPI;

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
  /*double theta = (atan2(positionTracking::getY(), positionTracking::getX()) + M_PI) -
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
  );*/

  double theta = atan2(positionTracking::getY() - y, positionTracking::getX() - x) + M_PI;

  //call turnTo(double theta)
  turnToAngle(theta, timeout);
}

void goToPoint(double x, double y, int timeout){
  while(true /*not at target*/){
    double theta = atan2(positionTracking::getY() - y, positionTracking::getX() - x) + M_PI;
    if(std::abs(theta - positionTracking::getThetaWrapped()) > 0.02) turnToAngle(theta, timeout);
    driveMotors.spin(fwd, 50, pct);
  }
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
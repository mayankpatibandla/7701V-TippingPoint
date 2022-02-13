#include "vex.h"
#include "auton-functions.h"
#include "autons.h"

using namespace vex;

PID::PID(double kP, double kI, double kD, double maxError, double dT):
  kP(kP), kI(kI), kD(kD), maxError(maxError), dT(dT)
{}

PID emptyPID;
PID tempPID;
PID turnPID_R(67.5, 0, 8.3);
PID fwdPID_IN(3.1, 0.05, 0);
PID turnPID_R_N(43.5, 0, 7.5);
PID fwdPID_DEG_N(0.165, 0.01, 0, 6);

void auton(){
  switch(tc){
    case RED:{
      switch(ts){
        case LEFT:{
          switch(av){
            case AWP:{
              switch(at){
                case MAIN:{
                  //RED LEFT AWP MAIN
                  leftSideAWP1NeutralAuton();
                }break;
                case OTHER:{
                  //RED LEFT AWP OTHER
                  twoAWPAuton();
                }break;
              }
            }break;
            case NEUTRAL:{
              switch(at){
                case MAIN:{
                  //RED LEFT NEUTRAL MAIN
                  
                }break;
                case OTHER:{
                  //RED LEFT NEUTRAL OTHER
                  
                }break;
              }
            }break;
          }
        }break;
        case RIGHT:{
          switch(av){
            case AWP:{
              switch(at){
                case MAIN:{
                  //RED RIGHT AWP MAIN
                  rightSideAWP2NeutralAuton();
                }break;
                case OTHER:{
                  //RED RIGHT AWP OTHER
                  rightSideAWP1NeutralAuton();
                }break;
              }         
            }break;
            case NEUTRAL:{
              switch(at){
                case MAIN:{
                  //RED RIGHT NEUTRAL MAIN
                  
                }break;
                case OTHER:{
                  //RED RIGHT NEUTRAL OTHER

                }break;
              }
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
              switch(at){
                case MAIN:{
                  //BLUE LEFT AWP MAIN
                  leftSideAWP1NeutralAuton();
                }break;
                case OTHER:{
                  //BLUE LEFT AWP OTHER
                  twoAWPAuton();
                }break;
              }
            }break;
            case NEUTRAL:{
              switch(at){
                case MAIN:{
                  //BLUE LEFT NEUTRAL MAIN
                  
                }break;
                case OTHER:{
                  //BLUE LEFT NEUTRAL OTHER
                  
                }break;
              }
            }break;
          }
        }break;
        case RIGHT:{
          switch(av){
            case AWP:{
              switch(at){
                case MAIN:{
                  //BLUE RIGHT AWP MAIN
                  rightSideAWP2NeutralAuton();
                }break;
                case OTHER:{
                  //BLUE RIGHT AWP OTHER
                  rightSideAWP1NeutralAuton();
                }break;
              }         
            }break;
            case NEUTRAL:{
              switch(at){
                case MAIN:{
                  //BLUE RIGHT NEUTRAL MAIN
                  
                }break;
                case OTHER:{
                  //BLUE RIGHT NEUTRAL OTHER

                }break;
              }
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
      //odomTestAuton();
      testAuton();
    }break;
    case NONE:{
      
    }break;
  }
}
#if 0 //temporarily disabled
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
#endif

void goToPoint(double x, double y, int timeout, PID& turnPID, PID& fwdPID){
  timer goToTimer;
  goToTimer.reset();

  double powTurn = 100;

  double errorTurn = 1/0.;
  double integralTurn = 0;
  double derivativeTurn = 0;

  double prevErrorTurn = errorTurn;

  double powFwd = 100;

  double errorFwd = 1/0.;
  double integralFwd = 0;
  double derivativeFwd;

  double prevErrorFwd = errorFwd;

  const double errorAccFwd = 1, powAccFwd = 5;

  while(std::abs(errorFwd) > errorAccFwd || std::abs(powFwd) > powAccFwd){
    uint32_t timeStart = Brain.Timer.system();
    //timeout
    if(timeout != 0 && goToTimer.time(msec) > timeout) break;

    //update current pos
    double currentPosTurn = pt::thetaWrapped();
    //calculate error
    double targetTurn = atan2(pt::y() - y, pt::x() - x) + M_PI;
    double absErrorTurn = targetTurn - currentPosTurn;

    //angle wrap fix
    if(absErrorTurn < M_PI) errorTurn = absErrorTurn;
    else errorTurn = absErrorTurn - M_TWOPI;

    //add error to integral
    integralTurn += errorTurn;

    //integral windup
    if(errorTurn == 0 || std::abs(currentPosTurn) > std::abs(targetTurn)){
      integralTurn = 0;
    }
    if(errorTurn > turnPID.maxError){
      integralTurn = 0;
    }

    //calculate derivative and update previous error
    derivativeTurn = errorTurn - prevErrorTurn;
    prevErrorTurn = errorTurn;

    //calculate output power
    powTurn = errorTurn * turnPID.kP + integralTurn * turnPID.kI + derivativeTurn * turnPID.kD;

    //repeat above for fwd
    double currentPosFwd = std::hypot(pt::x(), pt::y());
    double targetFwd = std::hypot(x, y);
    errorFwd = std::hypot(x - pt::x(), y - pt::y()); //* pt::y() / std::abs(pt::y());//std::abs(targetFwd - currentPosFwd);

    integralFwd += errorFwd;

    if(errorFwd == 0 || std::abs(currentPosFwd) > std::abs(targetFwd)){
      integralFwd = 0;
    }
    if(errorFwd > fwdPID.maxError){
      integralFwd = 0;
    }

    derivativeFwd = errorFwd - prevErrorFwd;
    prevErrorFwd = errorFwd;

    //direction test
    //if(x < pt::x()) errorFwd *= -1;

    powFwd = errorFwd * fwdPID.kP + integralFwd * fwdPID.kI + derivativeFwd * fwdPID.kD;
    /*Controller.Screen.clearLine(3);
    Controller.Screen.print(errorFwd);
    Controller.Screen.print(" ");
    Controller.Screen.print(errorTurn);*/
    /*Controller.Screen.print(powFwd);
    Controller.Screen.print(" ");
    Controller.Screen.print(currentPosFwd);
    Controller.Screen.print(" ");
    Controller.Screen.print(targetFwd);*/

    //prevent turning correction when close to target
    if(errorFwd < 2) powTurn = 0;

    double leftSpeed = powFwd + powTurn;
    double rightSpeed = powFwd - powTurn;

    //assign output power to motors
    leftMotors.spin(fwd, leftSpeed, pct);
    rightMotors.spin(fwd, rightSpeed, pct);

    //sleep for dT
    this_thread::sleep_until(timeStart + fwdPID.dT);
  }
  driveMotors.stop();
}

void turnToAngle(double theta, int timeout, PID& pid){
  timer turnTimer;
  turnTimer.reset();

  double pow = 100;
  
  double error = 1/0.;
  double integral = 0;
  double derivative = 0;

  double prevError = error;

  const double errorAcc = 0.007, powAcc = 2.5;

  while(std::abs(error) > errorAcc || std::abs(pow) > powAcc){
    uint32_t timeStart = Brain.Timer.system();
    //timeout
    if(timeout != 0 && turnTimer.time(msec) > timeout) break;

    //update current pos
    double currentPos = pt::thetaWrapped();
    //calculate error
    double absError = theta - currentPos;

    //angle wrap fix
    if(absError < M_PI) error = absError;
    else error = absError - M_TWOPI;

    //add error to integral
    integral += error;

    //integral windup
    if(error == 0 || std::abs(currentPos) > std::abs(theta)){
      integral = 0;
    }
    if(error > pid.maxError){
      integral = 0;
    }

    //calculate derivative and update previous error
    derivative = error - prevError;
    prevError = error;

    //output powers
    pow = error * pid.kP + integral * pid.kI + derivative * pid.kD;

    leftMotors.spin(fwd, pow, pct);
    rightMotors.spin(fwd, -pow, pct);

    //sleep for dT
    this_thread::sleep_until(timeStart + pid.dT);
  }
  driveMotors.stop();
}

void turnToPoint(double x, double y, int timeout, PID& pid){
  timer turnTimer;
  turnTimer.reset();

  double pow = 100;
  
  double error = 1/0.;
  double integral = 0;
  double derivative = 0;

  double prevError = error;

  const double errorAcc = 0.05, powAcc = 5;

  while(std::abs(error) > errorAcc || std::abs(pow) > powAcc){
    uint32_t timeStart = Brain.Timer.system();
    //timeout
    if(timeout != 0 && turnTimer.time(msec) > timeout) break;

    double theta = atan2(pt::y() - y, pt::x() - x) + M_PI;

    //update current pos
    double currentPos = pt::thetaWrapped();
    //calculate error
    double absError = theta - currentPos;

    //angle wrap fix
    if(absError < M_PI) error = absError;
    else error = absError - M_TWOPI;

    //add error to integral
    integral += error;

    //integral windup
    if(error == 0 || std::abs(currentPos) > std::abs(theta)){
      integral = 0;
    }
    if(error > pid.maxError){
      integral = 0;
    }

    //calculate derivative and update previous error
    derivative = error - prevError;
    prevError = error;

    //output powers
    pow = error * pid.kP + integral * pid.kI + derivative * pid.kD;

    leftMotors.spin(fwd, pow, pct);
    rightMotors.spin(fwd, -pow, pct);

    //sleep for dT
    this_thread::sleep_until(timeStart + pid.dT);
  }
  driveMotors.stop();
}

void driveRelative(double target, int timeout, PID& pid){
  timer driveTimer;
  driveTimer.reset();

  target = (target / (M_TWOPI * pt::WHEEL_RADIUS)) * 360 + rightRotationSensor.position(deg);

  double pow = 100;

  double error = 1/0.;
  double integral = 0;
  double derivative = 0;

  double prevError = error;

  const double errorAcc = 0.25, powAcc = 5;

  while(std::abs(error) > errorAcc || std::abs(pow) > powAcc){
    uint32_t timeStart = Brain.Timer.system();
    //timeout
    if(timeout != 0 && driveTimer.time(msec) > timeout) break;

    //update current pos
    double currentPos = rightRotationSensor.position(deg);
    //calculate error
    error = target - currentPos;

    //add error to integral
    integral += error;

    //integral windup
    if(error == 0 || std::abs(currentPos) > std::abs(target)){
      integral = 0;
    }
    if(error > pid.maxError){
      integral = 0;
    }

    //calculate derivative and update previous error
    derivative = error - prevError;
    prevError = error;

    //output powers
    pow = error * pid.kP + integral * pid.kI + derivative * pid.kD;

    driveMotors.spin(fwd, pow, pct);

    //sleep for dT
    this_thread::sleep_until(timeStart + pid.dT);
  }
  driveMotors.stop();
}

void toggleClaw(){
  leftClawSolenoid.set(!leftClawSolenoid.value());
  rightClawSolenoid.set(!rightClawSolenoid.value());
}

void setClaw(bool value){
  leftClawSolenoid.set(value);
  rightClawSolenoid.set(value);
}
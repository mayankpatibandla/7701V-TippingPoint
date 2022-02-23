#include "vex.h"
#include "auton-functions.h"
#include "autons.h"

using namespace vex;

PID::PID(double kP, double kI, double kD, double maxError, double dT):
  kP(kP), kI(kI), kD(kD), maxError(maxError), dT(dT)
{}

PID emptyPID;
PID tempPID;
//PID turnPID_R(2, 0, 0);
PID turnPID_R(0, 0, 0);
//PID fwdPID_IN(2.5, 0.01, 0.75, 7.5);
PID fwdPID_IN(3, 0.05, 0.75, 12);
PID turnPID_R_N(25, 0, 5, 0.2);
PID fwdPID_DEG_N(0.19, 0.007, 0.02, 4);

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

void goToPose(double x, double y, bool reverse, int timeout, double speed){
  timer goToTimer;
  goToTimer.reset();

  double errorFwd = 1/0.;
  double errorTurn = 1/0.;

  const double accFwd = 1, accTurn = 0.1, turnErrorLim = 3;

  while(std::abs(errorFwd) > accFwd || (errorTurn > accTurn && std::abs(errorFwd) > turnErrorLim)){
    uint32_t timeStart = Brain.Timer.system();
    //timeout
    if(timeout != 0 && goToTimer.time(msec) > timeout) break;

    //turn error
    double currentPosTurn = pt::thetaWrapped();
    double targetTurn = atan2(pt::y() - y, pt::x() - x) + (reverse ? M_PI : 0);
    double absErrorTurn = targetTurn - currentPosTurn;

    //angle wrap fix
    if(absErrorTurn < M_PI) errorTurn = absErrorTurn;
    else errorTurn = absErrorTurn - M_TWOPI;

    errorFwd = std::hypot(pt::x() - x, pt::y() - y);

    const double turnKP = 30;

    double leftSpeed = speed * (reverse ? -1 : 1) + errorTurn * turnKP;
    double rightSpeed = speed * (reverse ? -1 : 1) - errorTurn * turnKP;

    leftMotors.spin(fwd, leftSpeed, pct);
    rightMotors.spin(fwd, rightSpeed, pct);

    this_thread::sleep_until(timeStart + 15);
  }
  driveMotors.stop();
}

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
    if(errorFwd < 5) powTurn = 0;

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

void goToPointW(double x, double y, int timeout, PID& turnPID, PID& fwdPID){
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
    double targetTurn = atan2(pt::y() - y, pt::x() - x);
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
    leftMotors.spin(fwd, -leftSpeed, pct);
    rightMotors.spin(fwd, -rightSpeed, pct);

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

  const double errorAcc = 0.05, powAcc = 5;

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
  turnToAngle(atan2(pt::y() - y, pt::x() - x) + M_PI, timeout, pid);
  /*timer turnTimer;
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
  driveMotors.stop();*/
}

void driveRelative(double target, int timeout, PID& pid, bool ttT){
  timer driveTimer;
  driveTimer.reset();

  target = (target / (M_TWOPI * pt::WHEEL_RADIUS)) * 360 + rightRotationSensor.position(deg);

  double pow = 100;

  double error = 1/0.;
  double integral = 0;
  double derivative = 0;

  double prevError = error;

  const double errorAcc = 0.5, powAcc = 5;

  while(std::abs(error) > errorAcc || std::abs(pow) > powAcc){
    uint32_t timeStart = Brain.Timer.system();
    if(ttT && driveTimer > 3000 && pt::x() < 22) break;

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
#include "auton-functions.h"
#include "autons.h"

using namespace vex;

void visionTurn(enum visionSensors sensor, vision::signature &sig, int timeout, double kP){
  double error = 1/0.;
  double pow = 1/0.;

  timer visionTimer;

  switch(sensor){
    case FRONTVISION:{
      while(std::abs(error) > 5 && std::abs(pow) > 5){
        if(timeout != 0 && visionTimer.time(msec) > timeout) break;

        frontVisionSensor.takeSnapshot(sig);

        if(!frontVisionSensor.largestObject.exists) Controller.rumble(rumblePulse);

        error = 158 - frontVisionSensor.largestObject.centerX;
        pow = error * kP;

        leftMotors.spin(fwd, -pow, pct);
        rightMotors.spin(fwd, pow, pct);

        this_thread::sleep_for(15);
      }
      driveMotors.stop();
    } break;
    case BACKVISION:{
      while(std::abs(error) > 5 && std::abs(pow) > 5){
        if(timeout != 0 && visionTimer.time(msec) > timeout) break;

        backVisionSensor.takeSnapshot(sig);

        error = 158 - backVisionSensor.largestObject.centerX;
        pow = error * kP;

        leftMotors.spin(fwd, -pow, pct);
        rightMotors.spin(fwd, pow, pct);

        this_thread::sleep_for(15);
      }
      driveMotors.stop();
    } break;
  }
  driveMotors.stop();
}

PID::PID(double kP, double kI, double kD, double maxError, double dT):
  kP(kP), kI(kI), kD(kD), maxError(maxError), dT(dT)
{}

PID emptyPID;
PID tempPID;
//PID turnPID_R(2, 0, 0);
PID turnPID_R(0, 0, 0);
//PID fwdPID_IN(2.5, 0.01, 0.75, 7.5);
PID fwdPID_IN(3, 0.05, 0.75, 12);
PID turnPID_R_N(25, 0, 3);
PID fwdPID_DEG_N(0.2);
PID fastFwd(0.225);
PID slowFwd(0.15);
PID verySlowFwd(0.075);

template <typename T> int sgn(T val){
  return (T(0) < val) - (val < T(0));
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

    leftMotors.spin(fwd, -pow, pct);
    rightMotors.spin(fwd, pow, pct);

    //sleep for dT
    this_thread::sleep_until(timeStart + pid.dT);
  }
  driveMotors.stop();
}

void turnToPoint(double x, double y, int timeout, PID& pid){
  turnToAngle(atan2(pt::y() - y, pt::x() - x) + M_PI, timeout, pid);
}

void driveRelative(double target, int timeout, PID& pid){
  timer driveTimer;
  driveTimer.reset();

  target = (target / (M_TWOPI * pt::WHEEL_RADIUS)) * 360 + leftRotationSensor.position(deg);

  double pow = 100;

  double error = 1/0.;
  double integral = 0;
  double derivative = 0;

  double prevError = error;

  const double errorAcc = 5, powAcc = 5;

  while(std::abs(error) > errorAcc || std::abs(pow) > powAcc){
    uint32_t timeStart = Brain.Timer.system();

    //timeout
    if(timeout != 0 && driveTimer.time(msec) > timeout) break;

    //update current pos
    double currentPos = leftRotationSensor.position(deg);
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

    /*Brain.Screen.clearLine(1);
    Brain.Screen.setCursor(1, 1);
    Brain.Screen.print("error %8f", error);
    Brain.Screen.clearLine(2);
    Brain.Screen.setCursor(2, 1);
    Brain.Screen.print("pos %8f", currentPos);
    Brain.Screen.clearLine(3);
    Brain.Screen.setCursor(3, 1);
    Brain.Screen.print("target %8f", target);
    Brain.Screen.render();*/

    //sleep for dT
    this_thread::sleep_until(timeStart + pid.dT);
  }
  driveMotors.stop();
}
/*
void driveRelative(double target, int timeout, PID& pid){
  timer driveTimer;
  driveTimer.reset();

  target += std::hypot(pt::x(), pt::y()) * sgn(target);

  double pow = 100;

  double error = 1/0.;
  double integral = 0;
  double derivative = 0;

  double prevError = error;

  const double errorAcc = 0.67, powAcc = 5;

  while(std::abs(error) > errorAcc || std::abs(pow) > powAcc){
    uint32_t timeStart = Brain.Timer.system();

    //timeout
    if(timeout != 0 && driveTimer.time(msec) > timeout) break;

    //update current pos
    double currentPos = std::hypot(pt::x(), pt::y()) * sgn(target);
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

    Brain.Screen.clearLine(1);
    Brain.Screen.setCursor(1, 1);
    Brain.Screen.print("error %8f", error);
    Brain.Screen.clearLine(2);
    Brain.Screen.setCursor(2, 1);
    Brain.Screen.print("pos %8f", currentPos);
    Brain.Screen.clearLine(3);
    Brain.Screen.setCursor(3, 1);
    Brain.Screen.print("target %8f", target);
    Brain.Screen.render();

    //sleep for dT
    this_thread::sleep_until(timeStart + pid.dT);
  }
  driveMotors.stop();
}*/

void toggleClaw(){
  leftClawSolenoid.set(!leftClawSolenoid.value());
  rightClawSolenoid.set(!rightClawSolenoid.value());
}
void setClaw(bool value){
  leftClawSolenoid.set(value);
  rightClawSolenoid.set(value);
}

void toggleBackLift(){
  backLiftSolenoid.set(!backLiftSolenoid.value());
}
void setBackLift(bool value){
  backLiftSolenoid.set(value);
}

void togglePreload(){
  preloadSolenoid.set(!preloadSolenoid.value());
}
void setPreload(bool value){
  preloadSolenoid.set(value);
}

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
                  leftMidFirstAuton();
                }break;
                case OTHER:{
                  //RED LEFT NEUTRAL OTHER
                  leftMidFirstAuton();
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
                  rightMidFirstAuton();
                }break;
                case OTHER:{
                  //RED RIGHT NEUTRAL OTHER
                  rightMidJuke();
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
                  leftMidFirstAuton();
                }break;
                case OTHER:{
                  //BLUE LEFT NEUTRAL OTHER
                  leftMidFirstAuton();
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
                  rightMidFirstAuton();
                }break;
                case OTHER:{
                  //BLUE RIGHT NEUTRAL OTHER
                  rightMidFirstAuton();
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
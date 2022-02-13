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
          odomTestAuton();
        }break;
        case RIGHT:{
          //RED RIGHT
        }break;
      }
    }break;
    case BLUE:{
      switch(ts){
        case LEFT:{
          //BLUE LEFT
        }break;
        case RIGHT:{
          //BLUE RIGHT
        }break;
      }
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

  const double errorAcc = 0.05, powAcc = 2;

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
  //call turnTo(double theta)
  //theta = atan(delta y, delta x)
  double theta = std::atan2(y - positionTracking::getY(), x - positionTracking::getX());
  Controller.Screen.clearLine(3);
  Controller.Screen.print("%f", theta);
  wait(1, sec);
  //turnTo(std::atan2(y - positionTracking::getY(), x - positionTracking::getX()), timeout);
  turnToAngle(x == 0 && y == 0 ? theta + M_PI : theta, timeout); //DOES NOT WORK; NEEDS TO BE FIXED

}

void goToX(double x){
  turnToAngle(M_PI_2, 0);
  while(std::abs(x - positionTracking::getX()) > 0.5){
    if(x > positionTracking::getX()){
      driveMotors.spin(forward, 25, pct);
    }
    else{
      driveMotors.spin(reverse, 25, pct);
    }
  }
  driveMotors.stop();
}

void goToY(double y){
  turnToAngle(0, 0);
  while(std::abs(y - positionTracking::getY()) > 0.5){
    if(y > positionTracking::getY()){
      driveMotors.spin(forward, 25, pct);
    }
    else{
      driveMotors.spin(reverse, 25, pct);
    }
  }
  driveMotors.stop();
}

void goTo(double x, double y){
  goToX(x);
  goToY(y);
}
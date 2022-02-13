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

  const double errorAcc = 0.15, powAcc = 2;

  while(std::abs(error) > errorAcc || std::abs(pow) > powAcc){
    Controller.Screen.print(" __ %f __ %f __ %f", error, currentPos, target);
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
    leftMotors.spin(directionType::fwd, pow, pct);
    rightMotors.spin(directionType::rev, pow, pct);

    //sleep for dT
    this_thread::sleep_for(pid.dT);
  }
  driveMotors.stop();
}

//turns to theta (radians)
void turnTo(double theta, int timeout){
  PIDTurn(theta, timeout, turnPID_R);
}

//turns to face point (x, y)
void turnTo(double x, double y, int timeout){
  //call turnTo(double theta)
  //theta = atan(delta y, delta x)
  turnTo(std::atan2(y - positionTracking::getY(), x - positionTracking::getX()), timeout);
}

void goTo(double x, double y){

}
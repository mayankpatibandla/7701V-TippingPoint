#include "vex.h"
#include "auton-functions.h"

/*
void testAuton(){
  Brain.Screen.setFont(mono60);

  const double kP = 0.13;
  const double target = 158;

  while(true){
    frontVisionSensor.takeSnapshot(FRONT_REDMOGO);
    vision::object &obj = frontVisionSensor.largestObject;

    double currentPos = obj.centerX;
    
    if(!obj.exists){
      Brain.Screen.clearScreen();
      Brain.Screen.setCursor(1, 1);
      Brain.Screen.print("OBJECT NOT FOUND");
      Brain.Screen.render();
    }
    
    double error = target - currentPos;
    double pow = error * kP;

    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1, 1);
    Brain.Screen.print("%d", currentPos);
    Brain.Screen.setCursor(2, 1);
    Brain.Screen.print("%d", error);
    Brain.Screen.render();

    leftMotors.spin(fwd, -pow, pct);
    rightMotors.spin(fwd, pow, pct);

    if(error < 2.5) break;
    wait(10, msec);
  }
  driveMotors.stop();
}*/

void testAuton(){
  Brain.Screen.setFont(mono60);
  /*while(true){
    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1, 1);
    frontVisionSensor.takeSnapshot(FRONT_YELLOWMOGO);
    Brain.Screen.print(frontVisionSensor.largestObject.centerX);
    if(frontVisionSensor.largestObject.centerX > 164){
      rightMotors.spin(fwd, -20, pct);
      leftMotors.spin(fwd, 20, pct);
    }
    else if(frontVisionSensor.largestObject.centerX < 150){
      rightMotors.spin(fwd, 20, pct);
      leftMotors.spin(fwd, -20, pct);
    }
    else{
      driveMotors.stop();
    }
    Brain.Screen.render();
    this_thread::sleep_for(10);
  }*/

  const double kP = 0.2;

  while(true){
    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1, 1);
    frontVisionSensor.takeSnapshot(FRONT_YELLOWMOGO);
    Brain.Screen.print(frontVisionSensor.largestObject.centerX);
    double error = 158 - frontVisionSensor.largestObject.centerX;
    double pow = error * kP;

    rightMotors.spin(fwd, pow, pct);
    leftMotors.spin(fwd, -pow, pct);

    Brain.Screen.render();
    this_thread::sleep_for(10);
  }
}
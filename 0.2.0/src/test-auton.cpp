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
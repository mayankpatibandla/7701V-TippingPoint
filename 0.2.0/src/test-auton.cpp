#include "vex.h"
#include "odom.h"
#include "auton-functions.h"
#include <vector>

void testAuton(){
  Brain.Screen.setFont(mono60);

  const double kP = 0.13;

  while(true){
    frontVisionSensor.takeSnapshot(REDMOGO);
    vision::object &obj = frontVisionSensor.largestObject;

    double currentPos = obj.centerX;
    
    if(!obj.exists){
      Brain.Screen.clearScreen();
      Brain.Screen.setCursor(1, 1);
      Brain.Screen.print("OBJECT NOT FOUND");
      Brain.Screen.render();
    }
    
    double error = 158 - currentPos;
    double pow = error * kP;

    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1, 1);
    Brain.Screen.print("%d", currentPos);
    Brain.Screen.setCursor(2, 1);
    Brain.Screen.print("%d", error);
    Brain.Screen.render();

    leftMotors.spin(fwd, -pow, pct);
    rightMotors.spin(fwd, pow, pct);

    if(error < 5) break;
    wait(10, msec);
  }
  driveMotors.stop();
}
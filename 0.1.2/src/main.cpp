#include "vex.h"
#include "position-tracking.h"

using namespace vex;

int main(){
  motorInit();
  autonInit();
  sensorInit();

  Competition.drivercontrol(driver);
  Competition.autonomous(auton);

  thread positionTracking_thread(positionTracking::positionTracking);

  while(true){
    Brain.Screen.clearScreen();
    Brain.Screen.printAt(0, 20 , "X . . . . . . . . . %8f", positionTracking::getX());
    Brain.Screen.printAt(0, 50 , "Y . . . . . . . . . %8f", positionTracking::getY());
    Brain.Screen.printAt(0, 80 , "Theta (-inf, +inf)  %8f", positionTracking::getTheta());
    Brain.Screen.printAt(0, 110, "Theta [0Pi, 2Pi]  . %8f", positionTracking::getThetaWrapped());
    Brain.Screen.printAt(0, 140, "Theta [-Pi, +Pi]  . %8f", positionTracking::getThetaWrapped(true));
    Brain.Screen.render();
    this_thread::sleep_for(15);
  }
}
#include "vex.h"
#include "position-tracking.h"
#include "auton-functions.h"

using namespace vex;

int main(){
  motorInit();
  autonInit();
  sensorInit();

  Competition.drivercontrol(driver);
  Competition.autonomous(auton);

  thread positionTracking_thread(positionTracking::positionTracking);
  thread fourBarLimit_thread(fourBarLimit);

  while(true){
    Brain.Screen.clearScreen();
    Brain.Screen.printAt(0, 20 , "Position X  . . . . %8f (in)", positionTracking::getX());
    Brain.Screen.printAt(0, 50 , "Position Y  . . . . %8f (in)", positionTracking::getY());
    Brain.Screen.printAt(0, 80 , "Theta (-inf, inf) . %8f (rad)", positionTracking::getTheta());
    Brain.Screen.printAt(0, 110, "Theta [0, 2Pi)  . . %8f (rad)", positionTracking::getThetaWrapped(false));
    Brain.Screen.printAt(0, 140, "Theta [-Pi, Pi) . . %8f (rad)", positionTracking::getThetaWrapped(true));
    Brain.Screen.printAt(0, 170, "Theta (-inf, inf) . %8f (deg)", positionTracking::getTheta() * 180 / M_PI);
    Brain.Screen.printAt(0, 200, "Theta [0, 360)  . . %8f (deg)", positionTracking::getThetaWrapped(false) * 180 / M_PI);
    Brain.Screen.printAt(0, 230, "Theta [-180, 180) . %8f (deg)", positionTracking::getThetaWrapped(true) * 180 /  M_PI);
    Brain.Screen.render();
    this_thread::sleep_for(15);
  }
}
#include "vex.h"
#include "auton-functions.h"

using namespace vex;

int main(){
  motorInit();
  autonInit();
  sensorInit();

  Competition.drivercontrol(driver);
  Competition.autonomous(auton);

  thread positionTracking_thread(pt::positionTracking);

  while(true){
    uint32_t timeStart = Brain.Timer.system();
    Brain.Screen.clearScreen();
    Brain.Screen.printAt(0, 20 , "Position X  . . . . %8f (in)", pt::x());
    Brain.Screen.printAt(0, 50 , "Position Y  . . . . %8f (in)", pt::y());
    Brain.Screen.printAt(0, 80 , "Theta (-inf, inf) . %8f (rad)", pt::theta());
    Brain.Screen.printAt(0, 110, "Theta [-Pi, Pi) . . %8f (rad)", pt::thetaWrapped(true));
    Brain.Screen.printAt(0, 140, "Theta [0, 2Pi)  . . %8f (rad)", pt::thetaWrapped(false));
    Brain.Screen.printAt(0, 170, "Theta (-inf, inf) . %8f (deg)", pt::theta() * 180 / M_PI);
    Brain.Screen.printAt(0, 200, "Theta [-180, 180) . %8f (deg)", pt::thetaWrapped(true) * 180 / M_PI);
    Brain.Screen.printAt(0, 230, "Theta [0, 360)  . . %8f (deg)", pt::thetaWrapped(false) * 180 / M_PI);
    Brain.Screen.render();
    this_thread::sleep_until(timeStart + 15);
  }
}
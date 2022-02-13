#include "vex.h"
#include "functions.h"
#include "odom.h"

using namespace vex;

int main() 
{
  vexcodeInit();

  Competition.autonomous(f_autonomous);
  Competition.drivercontrol(f_drivercontrol);

  ControllerLCD.clearScreen();

  LCD.setFont(mono20);

  thread odomThread = thread(odom::odometry);

  while(true)
  {
    //checkDevices(false);

    LCD.printAt(20 , 20, "X:   %3.3f  ", odom::getCurrentPosX());
    LCD.printAt(160, 20, "Y:   %3.3f  ", odom::getCurrentPosY());
    LCD.printAt(300, 20, "θ:   %3.3f  ", odom::getCurrentPosθ(Deg));

    

    /*ControllerLCD.clearScreen();
    ControllerLCD.setCursor(1, 1);
    ControllerLCD.print("%3.3f", distanceSensor.objectDistance(distanceUnits::in));
    ControllerLCD.print("%3.3f", inertialSensor.rotation(deg));*/
    wait(15, msec);
  }
}
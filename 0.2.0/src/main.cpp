#include "vex.h"
#include "auton-functions.h"
#include "color-util.h"

using namespace vex;

ColorUtil::rgb randomColor(){
  int rgb[3];
  for(int i = 0; i < 3; i++)
    rgb[i] = rand() % 256;

  ColorUtil::rgb x = {(float)rgb[0], (float)rgb[1], (float)rgb[2]};

  return x;
}

const unsigned short int visionColorCooldown = 25;
uint32_t prevVisionColorTime = Brain.Timer.system();

ColorUtil::hsl hsl_ledColor = {0, 1, 0.5};
const double deltaFade = 0.00980392156;

void updateVisionLeds(){
  ColorUtil::rgb ledColor;

  hsl_ledColor.h += deltaFade;
  ledColor = ColorUtil::hsl2rgb(
    hsl_ledColor.h, hsl_ledColor.s, hsl_ledColor.l
  );
  if(hsl_ledColor.h > 1) hsl_ledColor.h = 0;

  frontVisionSensor.setLedColor(ledColor.r, ledColor.g, ledColor.b);
  backVisionSensor.setLedColor(ledColor.r, ledColor.g, ledColor.b);

  prevVisionColorTime = Brain.Timer.system();
}

const unsigned short int renderCooldown = 25;
uint32_t prevRenderTime = Brain.Timer.system();

void printOdomDebug(){
  Brain.Screen.clearScreen();
  Brain.Screen.printAt(0, 20 , "Position X  . . . . %8f (in)", pt::x());
  Brain.Screen.printAt(0, 50 , "Position Y  . . . . %8f (in)", pt::y());
  Brain.Screen.printAt(0, 80 , "Theta (-inf, inf) . %8f (rad)", pt::theta());
  Brain.Screen.printAt(0, 110, "Theta [-Pi, Pi) . . %8f (rad)", pt::thetaWrapped(true));
  Brain.Screen.printAt(0, 140, "Theta [0, 2Pi)  . . %8f (rad)", pt::thetaWrapped(false));
  Brain.Screen.printAt(0, 170, "Theta (-inf, inf) . %8f (deg)", pt::theta() * 180 / M_PI);
  Brain.Screen.printAt(0, 200, "Theta [-180, 180) . %8f (deg)", pt::thetaWrapped(true) * 180 / M_PI);
  Brain.Screen.printAt(0, 230, "Theta [0, 360)  . . %8f (deg)", pt::thetaWrapped(false) * 180 / M_PI);
}

int main(){
  srand(Brain.Timer.system() * Brain.Battery.temperature() * Brain.Battery.current() * Brain.Battery.voltage());
  checkDevices(true);
  motorInit();
  autonInit();
  sensorInit();

  Competition.drivercontrol(driver);
  Competition.autonomous(auton);

  //Brain.Screen.pressed(auton);

  toggleBackLift();
  toggleClaw();

  thread positionTracking_thread(pt::positionTracking);

  const bool odomDebug = false;

  while(true){
    uint32_t timeStart = Brain.Timer.system();
    if(odomDebug){
      printOdomDebug();
    }

    /*Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1,1);
    Brain.Screen.print(leftRotationSensor.position(deg));
    Brain.Screen.render();*/
    /*Controller.Screen.clearLine(3);
    Controller.Screen.print(distanceSensor.isObjectDetected());
    Controller.Screen.print("   ");
    Controller.Screen.print(distanceSensor.objectDistance(inches));*/

    checkDevices(false);

    if(timeStart - prevVisionColorTime > visionColorCooldown){
      updateVisionLeds();
    }
    if(timeStart - prevRenderTime > renderCooldown){
      Brain.Screen.render();
      prevRenderTime = Brain.Timer.system();
    }

    this_thread::sleep_until(timeStart + 10);
  }
}
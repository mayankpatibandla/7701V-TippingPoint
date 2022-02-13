#include "vex.h"

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// DigitalOutA          digital_out   A               
// ---- END VEXCODE CONFIGURED DEVICES ----

using namespace vex;

int main() {
  while(true){
    if(Controller.ButtonY.pressing())
      DigitalOutA.set(true);
    else
      cylinder1.set(false);

    wait(5, msec);
  }
}

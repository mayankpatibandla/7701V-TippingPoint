#include "vex.h"
#include "odom/simulator.h"

using namespace vex;

int main() {
  Brain.Screen.clearScreen("#FFFFFF");
  Brain.Screen.render();

  PurePursuit_ns::main();
}

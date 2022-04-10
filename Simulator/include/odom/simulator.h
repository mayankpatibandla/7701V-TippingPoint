#pragma once
#include "odom/pure-pursuit.h"

namespace PurePursuit{
  //Pursuit constants
  extern const double
    minVel, maxVel,
    maxAccel,
    turnK;

  //starting points
  extern std::vector<WayPoint> points;
  extern std::vector<Bot> bots;
  extern std::vector<WayPoint> path_WP;
  extern std::vector<PathPoint> path;

  extern void main();
  extern void animate();
}

extern void test();
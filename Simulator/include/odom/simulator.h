#pragma once
#include "odom/pure-pursuit.h"
#include "odom/spline.h"
#include "odom/canvas.h"
#include "odom/path-gen.h"

namespace PurePursuit_ns{
  //starting points
  extern std::vector<WayPoint> points;
  extern std::vector<PurePursuit_ns::PurePursuit> bots;
  extern std::vector<PathPoint> path;

  extern void main();
  extern void animate();
}
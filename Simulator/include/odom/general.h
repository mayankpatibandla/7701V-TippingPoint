#pragma once
#include "odom/waypoint.h"

namespace PurePursuit{
  template<typename T> extern int sgn(T value);

  extern double rollAngle360(double angle);
  extern double rollAngle180(double angle);

  extern double angleBetweenPointsSpline(WayPoint &current, WayPoint &target);

  extern std::vector<WayPoint> calculateAngles(std::vector<WayPoint> &path);
}
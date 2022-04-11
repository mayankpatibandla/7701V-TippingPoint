#pragma once
#include "odom/waypoint.h"

namespace PurePursuit_ns{
  template<typename T> extern int sgn(const T &value);

  extern double rollAngle360(double angle);
  extern double rollAngle180(double angle);

  extern double angleBetweenPointsSpline(WayPoint &current, WayPoint &target);

  extern std::vector<WayPoint> calculateAngles(std::vector<WayPoint> &path);
}

template<typename T> int PurePursuit_ns::sgn(const T &value){
  return (T(0) < value) - (value < T(0));
}
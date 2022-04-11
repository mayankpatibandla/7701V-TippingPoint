#pragma once
#include "odom/vector.h"
//[]
namespace PurePursuit_ns{
  class WayPoint{
  public:
    double x, y, theta, vel;

    WayPoint(double x, double y, double theta);

    Vector vector();
  };
}
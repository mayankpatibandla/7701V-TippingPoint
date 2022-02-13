#pragma once
#include <cmath>

namespace coords{
  class Pose{
  private:
    double x_, y_, theta_;
  public:
    Pose(double x = 0, double y = 0, double theta = 0);

    double x();
    double y();

    double theta();
    double theta0();
    double thetaInf();
  };
}
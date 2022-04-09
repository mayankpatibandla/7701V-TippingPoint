#pragma once
#include "odom/path-point.h"
#include "odom/waypoint.h"

namespace PurePursuit{
  class QuinticPolynomial{
  private:
    double coeffs[6];

  public:
    QuinticPolynomial(double xstart, double vstart, double xend, double vend);

    double calcPoint(double t);
  };

  class QuinticSegmentPlanner{
  private:
    std::vector<double> rx, ry;

  public:
    QuinticSegmentPlanner(WayPoint &s, WayPoint &g, int steps, bool end);

    std::vector<PathPoint> getPath();
  };

  class QuinticPathPlanner{
  private:
    std::vector<WayPoint> points;
    int steps;
    double slopeScalar;

    std::vector<PathPoint> path;

    void generateVelocities();
    void generatePath();

  public:
    QuinticPathPlanner(std::vector<WayPoint> &points, int steps, double slopeScalar = 0.8);
    std::vector<WayPoint> getPath();
  };
}
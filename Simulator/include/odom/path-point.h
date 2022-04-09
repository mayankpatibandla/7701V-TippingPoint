#pragma once
#include "odom/vector.h"
//{}
namespace PurePursuit{
  class PathPoint{
  public:
    double loc[2];
    double distance;
    double velocity;
    double curvature;
    double segmentIndex;

    PathPoint(double x, double y);

    double x();
    double y();

    Vector vector();

    void setDistance(double distance);
    void setVelocity(double velocity);
    void setCurvature(double curvature);
    void setSegmentIndex(double segmentIndex);
  };
}
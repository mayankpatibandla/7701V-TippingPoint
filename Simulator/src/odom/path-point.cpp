#include "vex.h"
#include "odom/path-point.h"
//{}
namespace PurePursuit_ns{
  PathPoint::PathPoint(double x, double y){
    loc[0] = x; loc[1] = y;
    distance = 0;
    velocity = 0;
    curvature = 0;
    segmentIndex = 0;
  }

  double PathPoint::x(){
    return loc[0];
  }
  double PathPoint::y(){
    return loc[1];
  }

  Vector PathPoint::vector(){
    return Vector(x(), y());
  }

  void PathPoint::setDistance(double distance){
    this->distance = distance;
  }

  void PathPoint::setVelocity(double velocity){
    this->velocity = velocity;
  }

  void PathPoint::setCurvature(double curvature){
    this->curvature = curvature;
  }

  void PathPoint::setSegmentIndex(double segmentIndex){
    this->segmentIndex = segmentIndex;
  }
}
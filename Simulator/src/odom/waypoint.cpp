#include "odom/waypoint.h"
//{}
namespace PurePursuit{
  WayPoint::WayPoint(double x, double y, double theta):
    x(x), y(y), theta(theta)
  {}

  Vector WayPoint::vector(){
    return Vector(x, y);
  }
}
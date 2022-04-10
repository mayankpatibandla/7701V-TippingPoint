#include "odom/general.h"

namespace PurePursuit{
  template<typename T> int sgn(const T &value){
    return (T(0) < value) - (value < T(0));
  }

  double rollAngle360(double angle){
    return angle - M_TWOPI * std::floor(angle / M_TWOPI);
  }

  double rollAngle180(double angle){
    return angle - M_TWOPI * std::floor((angle + M_PI) / M_TWOPI);
  }

  double angleBetweenPointsSpline(WayPoint &current, WayPoint &target){
    return rollAngle180(std::atan2(target.x - current.x, target.y - current.y));
  }

  std::vector<WayPoint> calculateAngles(std::vector<WayPoint> &path){
    path[0].theta = angleBetweenPointsSpline(path[0], path[1]);
    for(int i = 1; i < path.size() - 1; i++){
      path[i].theta = angleBetweenPointsSpline(path[i-1], path[i+1]);
    }
    path[path.size()-1].theta = angleBetweenPointsSpline(path[path.size()-2], path[path.size()-1]);
    return path;
  }
}
#include "coords.h"

namespace coords{
  //Pose Class

  //creates a pose object with x, y, and theta
  Pose::Pose(double x, double y, double theta):
    x_(x), y_(y), theta_(theta)
  {}

  //returns x
  double Pose::x(){
    return x_;
  }
  //returns y
  double Pose::y(){
    return y_;
  }

  //returns theta wrapped between [-pi, pi)
  double Pose::theta(){
    double temp_theta = fmod(thetaInf() + M_PI, M_TWOPI);
    if(temp_theta < 0) temp_theta += M_TWOPI;
    return temp_theta - M_PI;
  }
  //returns theta wrapped between [0, 2pi)
  double Pose::theta0(){
    double temp_theta = fmod(thetaInf(), M_TWOPI);
    if(temp_theta < 0) temp_theta += M_TWOPI;
    return temp_theta;
  }
  //returns theta without any wrapping
  double Pose::thetaInf(){
    return theta_;
  }
}
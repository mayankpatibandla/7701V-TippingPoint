#include "odom/bot.h"

namespace PurePursuit{
  const double SPEEDLIM = 2;

  template<typename T> T clamp(const T &n, const T &lower, const T &upper){
    return std::max(lower, std::min(n, upper));
  }

  double slew(double input, double last, double slewRate){
    return clamp(input, last - slewRate, last + slewRate);
  }

  Bot::Bot(Vector v, double a){
    pos = {v.x(), v.y(), a};
  }

  void Bot::tank(double left, double right){
    double maxMag;
    if(std::abs(left) > std::abs(right)){
      maxMag = left;
    }
    else{
      maxMag = right;
    }
    if(std::abs(maxMag) > 1){
      left -= (std::abs(maxMag) - 1) * sgn(maxMag);
      right -= (std::abs(maxMag) - 1) * sgn(maxMag);
    }

    spd = {left, right};
  }

  Vector Bot::getLocalPos(){
    Vector v(pos.x, pos.y);
    return canvasToLocal(v);
  }

  Vector Bot::getCanvasPos(){
    return Vector(pos.x, pos.y);
  }

  double Bot::getHeading(){
    return -pos.a;
  }

  void Bot::update(){
    //only for sim, get actual values from tracking wheels (I think)
    double dA = (spd.r - spd.l) * SPEEDLIM / M_PI;
    pos.a -= dA;
    pos.a = rollAngle360(pos.a);

    double xVel = std::cos(pos.a) * (spd.r + spd.l) * SPEEDLIM;
    double yVel = std::sin(pos.a) * (spd.r + spd.l) * SPEEDLIM;

    vel.x = slew(xVel, vel.x, 0.2);
    vel.y = slew(yVel, vel.y, 0.2);

    pos.x += vel.x;
    pos.y += vel.y;
  }

  void Bot::draw(){
    //TODO: implement draw function
  }
}
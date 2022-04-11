#include "odom/bot.h"

const double PurePursuit_ns::SPEEDLIM = 2;

template<typename T> T PurePursuit_ns::clamp(const T &n, const T &lower, const T &upper){
  return std::max(lower, std::min(n, upper));
}

double PurePursuit_ns::slew(double input, double last, double slewRate){
  return clamp(input, last - slewRate, last + slewRate);
}

PurePursuit_ns::Bot::Bot(Vector v, double a){
  pos = {v.x(), v.y(), a};
  vel = {0, 0};
  spd = {0, 0};
}

void PurePursuit_ns::Bot::tank(double left, double right){
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

PurePursuit_ns::Vector PurePursuit_ns::Bot::getLocalPos(){
  Vector v(pos.x, pos.y);
  return canvasToLocal(v);
}

PurePursuit_ns::Vector PurePursuit_ns::Bot::getCanvasPos(){
  return Vector(pos.x, pos.y);
}

double PurePursuit_ns::Bot::getHeading(){
  return -pos.a;
}

void PurePursuit_ns::Bot::update(){
  //only for sim, get actual values from tracking wheels (I think)
  double dA = (spd.r - spd.l) * SPEEDLIM / M_PI;
  pos.a -= dA;
  pos.a = rollAngle180(pos.a);

  double xVel = std::cos(pos.a) * (spd.r + spd.l) * SPEEDLIM;
  double yVel = std::sin(pos.a) * (spd.r + spd.l) * SPEEDLIM;

  vel.x = slew(xVel, vel.x, 0.2);
  vel.y = slew(yVel, vel.y, 0.2);

  pos.x += vel.x;
  pos.y += vel.y;
}

void PurePursuit_ns::Bot::draw(){
  Brain.Screen.setPenColor("#000000");
  Brain.Screen.setFillColor("#000000");
  Brain.Screen.setPenWidth(1);

  Brain.Screen.drawCircle(pos.x, pos.y, 2);

  Brain.Screen.drawLine(pos.x, pos.y, pos.x + std::cos(pos.a) * 15, pos.y + std::sin(pos.a) * 15);

  Brain.Screen.setPenWidth(2);
  Brain.Screen.setPenColor("#00FF00");

  Brain.Screen.drawLine(
    pos.x + std::cos(pos.a + M_PI_2) * 10,
    pos.y + std::sin(pos.a + M_PI_2) * 10,
    pos.x + std::cos(pos.a + M_PI_2) * 10 + spd.r * 20 * std::cos(pos.a),
    pos.y + std::sin(pos.a + M_PI_2) * 10 + spd.r * 20 * std::sin(pos.a)
  );

  Brain.Screen.drawLine(
    pos.x + std::cos(pos.a - M_PI_2) * 10,
    pos.y + std::sin(pos.a - M_PI_2) * 10,
    pos.x + std::cos(pos.a - M_PI_2) * 10 + spd.l * 20 * std::cos(pos.a),
    pos.y + std::sin(pos.a - M_PI_2) * 10 + spd.l * 20 * std::sin(pos.a)
  );
}
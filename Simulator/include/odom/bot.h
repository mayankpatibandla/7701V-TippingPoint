#pragma once
#include "odom/general.h"
#include "odom/canvas.h"

namespace PurePursuit_ns{
  extern const double SPEEDLIM;

  template<typename T> extern T clamp(const T &n, const T &lower, const T &upper);
  extern double slew(double input, double last, double slewRate);

  class Bot{
  public:
    struct pos_{
      double x, y, a;
    };
    
    struct vel_{
      double x, y;
    };

    struct spd_{
      double l, r;
    };
  
  private:
    pos_ pos;
    vel_ vel;
    spd_ spd;

  public:
    Bot(Vector v, double a);

    void tank(double left, double right);

    Vector getLocalPos();
    Vector getCanvasPos();

    double getHeading();

    void update();

    void draw();
  };
}
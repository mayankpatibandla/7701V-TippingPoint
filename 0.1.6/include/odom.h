#pragma once
#include <cmath>

namespace PositionTracking{
  extern void positionTracking();

  extern double x();
  extern double y();
  extern double theta();

  extern double thetaWrapped(bool range = true);

  extern const double WHEEL_RADIUS;
}

namespace PurePursuit{
  
}

namespace pt = PositionTracking;
namespace pp = PurePursuit;
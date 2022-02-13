#include "vex.h"
#include "enums.h"

namespace odom
{
  extern int odometry();

  extern double getCurrentPosX();
  extern double getCurrentPosY();
  extern double getCurrentPosθ(angleUnits u = Rad);

  extern int turnToAngle(double θ, angleUnits u = Deg);
  extern int turnToPoint(double x, double y);
  
  extern int goToPoint(double x, double y);

  extern void PIDTurnOdom(const double target, angleUnits u = Deg, const int timeout = 0, const double maxError = 360, const double kP = 0.3333333333333333, const double kI  = 0.001030097087, const double kD = 0.09115200003,  const int dT = 15);
}

/*
_______________________________________________________________________________________________________________________________________________________
|                        |                        |                        |                        |                        |                        |
|       PARAMETER        |       RISE TIME        |       OVERSHOOT        |     SETTLING TIME      |   STEADY-STATE ERROR   |       STABILITY        |
|________________________|________________________|________________________|________________________|________________________|________________________|
|                        |                        |                        |                        |                        |                        |
|           kP           |        DECREASE        |        INCREASE        |          N/A           |        DECREASE        |        WORSENS         |
|________________________|________________________|________________________|________________________|________________________|________________________|
|                        |                        |                        |                        |                        |                        |
|           kI           |        DECREASE        |        INCREASE        |        INCREASE        |        DECREASE        |        WORSENS         |
|________________________|________________________|________________________|________________________|________________________|________________________|
|                        |                        |                        |                        |                        |                        |
|           kD           |          N/A           |        DECREASE        |        DECREASE        |          N/A           |        IMPROVES        |
|________________________|________________________|________________________|________________________|________________________|________________________|

*/
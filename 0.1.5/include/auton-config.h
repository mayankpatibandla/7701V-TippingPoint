#pragma once

enum teamColor{
  RED = 0, BLUE = 1, SKILLS = 2, TEST = 3, NONE = 4
};

enum teamSide{
  LEFT = 0, RIGHT = 1
};

enum autonVersion{
  AWP = 0, NEUTRAL = 1
};

extern teamColor tc;
extern teamSide ts;
extern autonVersion av;
extern int autonType;

class PID{
public:
  double kP, kI, kD, maxError, dT;
  PID(double kP = 0, double kI = 0, double kD = 0, double maxError = 0, double dT = 15);
};

extern PID emptyPID;
extern PID turnPID_R;
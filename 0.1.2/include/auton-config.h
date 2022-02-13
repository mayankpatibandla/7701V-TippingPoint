#pragma once

enum teamColor{
  RED, BLUE, NONE, SKILLS
};

enum teamSide{
  LEFT, RIGHT
};

enum autonVersion{
  AWP, PLATFORM
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
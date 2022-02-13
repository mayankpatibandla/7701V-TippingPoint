#include "auton-config.h"

PID::PID(double kP, double kI, double kD, double maxError, double dT):
  kP(kP), kI(kI), kD(kD), maxError(maxError), dT(dT)
{}

PID emptyPID;
PID turnPID_R(9);
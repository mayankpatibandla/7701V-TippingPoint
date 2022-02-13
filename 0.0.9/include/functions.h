#pragma once

#include "vex.h"
#include "enums.h"

using namespace vex;

void inertialDebug();
void opticalDebug();

void f_forward(double rots = 360, int speed = 50, int timeout = 0, bool wait = true);

int P(int currentPos, int target = 158, double kP = 0.55f);

//0.35, 0.005, 0.45
void PIDTurn(const double target, const int timeout = 0, const double maxError = 360, const double kP = 0.33333333, const double kI  = 0.0002330097087, const double kD = 0.09115200003,  const int dT = 15);

void PIDForward(double target, const int timeout = 0, const double maxError = 540, const double kP = 0.45, const double kI = 0.0003829787235, const double kD = 0.2449323333,  const int dT = 15);

void PDistanceForward(const double target, const double kP = 4);
void PIDDistanceForward(const double target, const int timeout = 0, const double maxError = 360, const double kP = 0.75, const double kI = 0.0002330097087, const double kD = 0.09115200003,  const int dT = 15);

void f_drivercontrol();
void f_autonomous();
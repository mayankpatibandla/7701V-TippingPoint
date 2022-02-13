#pragma once
#include "auton-config.h"
#include "odom.h"

class PID{
public:
  double kP, kI, kD, maxError, dT;

  PID(double kP = 0, double kI = 0, double kD = 0, double maxError = 0, double dT = 15);
};

extern PID emptyPID;
extern PID tempPID;
extern PID turnPID_R;
extern PID fwdPID_IN;
extern PID turnPID_R_N;
extern PID fwdPID_DEG_N;

extern int fourBarLimit();
extern int backLiftLimit();

extern void goToPoint(double x, double y, int timeout = 0, PID& turnPID = turnPID_R, PID& movePID = fwdPID_IN);

extern void turnToAngle(double theta, int timeout = 0, PID& pid = turnPID_R_N);
extern void turnToPoint(double x, double y, int timeout = 0, PID& pid = turnPID_R_N);

extern void driveRelative(double target, int timeout = 0, PID& pid = fwdPID_DEG_N);

extern void toggleClaw();
extern void setClaw(bool value);
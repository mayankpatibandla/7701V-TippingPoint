#pragma once
#include "vex.h"
#include "auton-config.h"
#include "odom.h"

enum visionSensors{
  FRONTVISION, BACKVISION
};

extern void visionTurn(enum visionSensors sensor, vision::signature &sig, int timeout = 0, double kP = 0.175);

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
extern PID fastFwd;
extern PID slowFwd;
extern PID verySlowFwd;

extern void turnToAngle(double theta, int timeout = 0, PID& pid = turnPID_R_N);
extern void turnToPoint(double x, double y, int timeout = 0, PID& pid = turnPID_R_N);

extern void driveRelative(double target, int timeout = 0, PID& pid = fastFwd);

extern void toggleClaw();
extern void setClaw(bool value);

extern void toggleBackLift();
extern void setBackLift(bool value);

extern void togglePreload();
extern void setPreload(bool value);
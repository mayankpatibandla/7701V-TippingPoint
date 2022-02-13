#include "auton-config.h"

extern void PIDTurn(double target, int timeout = 0, PID& pid = turnPID_R);

extern void turnToAngle(double theta, int timeout = 0);
extern void turnToPoint(double x, double y, int timeout = 0);

extern void goToX(double x, int timeout = 0);
extern void goToY(double y, int timeout = 0);
extern void goToXY(double x, double y, int timeout = 0);

extern void toggleClaw();
extern void setClaw(bool value);
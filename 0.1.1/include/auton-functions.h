#include "auton-config.h"

void PIDTurn(double target, int timeout = 0, PID& pid = turnPID_R);

void turnToAngle(double theta, int timeout = 0);
void turnToPoint(double x, double y, int timeout = 0);
void goTo(double x, double y);

void goToX(double x);
void goToY(double y);
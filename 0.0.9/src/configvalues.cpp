#include "vex.h"

using namespace vex;

bool teamColor, side, wTurn, errors;
int funcs[12], deadbands[4], ports[11], reverses[8], gearSettings[8], dType, tType, auton;
int redMin = 0, redMax = 30, redMin1 = 300, redMax1 = 360, blueMin = 180, blueMax = 280;
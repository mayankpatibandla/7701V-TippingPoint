#pragma once
#include "vex.h"

using namespace vex;

void driver();
void auton();

extern brain Brain;
extern controller Controller;

extern competition Competition;
extern color Color;

extern digital_out leftClawSolenoid;
extern digital_out rightClawSolenoid;
extern digital_out backLiftSolenoid;

extern motor_group leftMotors;
extern motor_group rightMotors;
extern motor_group driveMotors;

extern motor fourBarMotor;

extern motor ringLiftMotor;

extern void sensorInit();
extern void autonInit();
extern void motorInit();

extern bool checkDevices(bool p_cancel = false);
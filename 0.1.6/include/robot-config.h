#pragma once
#include "vex.h"

using namespace vex;

void driver();
void auton();

extern brain Brain;
extern controller Controller;

extern competition Competition;
extern color Color;

extern inertial inertialSensor;

extern rotation leftRotationSensor;
extern rotation rightRotationSensor;
extern rotation backRotationSensor;

extern motor frontLeftMotor;
extern motor frontRightMotor;
extern motor backLeftMotor;
extern motor backRightMotor;

extern motor leftFourBarMotor;
extern motor rightFourBarMotor;

extern motor backLiftMotor;

extern motor ringLiftMotor;

extern distance clawDistanceSensor;
extern optical clawOpticalSensor;

extern digital_out leftClawSolenoid;
extern digital_out rightClawSolenoid;

extern limit fourBarBottomLimit;
extern limit fourBarTopLimit;

extern limit backLiftBottomLimit;
extern limit backLiftTopLimit;

extern motor_group fourBarMotors;

extern motor_group leftMotors;
extern motor_group rightMotors;
extern motor_group driveMotors;

extern task fourBarLimit_task;
extern task backLiftLimit_task;

extern void sensorInit();
extern void autonInit();
extern void motorInit();
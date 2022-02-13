#pragma once
#include "vex.h"
#include <cmath>

using namespace vex;

extern void driver();
extern void auton();

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

extern digital_out leftClawSolenoid;
extern digital_out rightClawSolenoid;

extern limit fourBarBottomLimit;

extern motor_group fourBarMotors;

extern motor_group leftMotors;
extern motor_group rightMotors;
extern motor_group driveMotors;

extern void sensorInit();
extern void autonInit();
extern void motorInit();
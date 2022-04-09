#pragma once
#include "vex.h"

using namespace vex;

extern void driver();
extern void auton();

extern brain Brain;
extern controller Controller;
extern controller partnerController;

extern competition Competition;
extern color Color;

extern rotation leftRotationSensor;
extern rotation rightRotationSensor;
extern rotation backRotationSensor;

extern motor frontLeftMotor;
extern motor middleLeftMotor;
extern motor backLeftMotor;

extern motor frontRightMotor;
extern motor middleRightMotor;
extern motor backRightMotor;

extern motor fourBarMotor;
extern rotation fourBarRotationSensor;
extern const double fourBarMinPos, fourBarMaxPos;

extern motor ringLiftMotor;

extern inertial inertialSensor;

extern digital_out leftClawSolenoid;
extern digital_out rightClawSolenoid;
extern digital_out backLiftSolenoid;

extern motor_group leftMotors;
extern motor_group rightMotors;
extern motor_group driveMotors;
extern motor_group allMotors;

extern void sensorInit();
extern void autonInit();
extern void motorInit();

extern bool checkDevices(bool p_cancel = false);

extern vision frontVisionSensor;
extern vision::signature REDMOGO;
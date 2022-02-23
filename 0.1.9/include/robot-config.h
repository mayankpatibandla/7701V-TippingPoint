#pragma once
#include "vex.h"

using namespace vex;

void driver();
void auton();

extern brain Brain;
extern controller Controller;

extern competition Competition;
extern color Color;

/*extern inertial inertialSensor;

extern rotation leftRotationSensor;
extern rotation rightRotationSensor;
extern rotation backRotationSensor;*/

extern motor frontLeftMotor;
extern motor middleLeftMotor;
extern motor backLeftMotor;

extern motor frontRightMotor;
extern motor middleRightMotor;
extern motor backRightMotor;

extern motor fourBarMotor;

extern motor ringLiftMotor;

/*lextern distance clawDistanceSensor;
extern optical clawOpticalSensor;*/

extern digital_out leftClawSolenoid;
extern digital_out rightClawSolenoid;

extern motor_group leftMotors;
extern motor_group rightMotors;
extern motor_group driveMotors;
/*
extern void sensorInit();
extern void autonInit();*/
extern void motorInit();

//extern bool checkDevices(bool p_cancel = false);
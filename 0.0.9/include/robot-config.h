#pragma once

using namespace vex;

extern const double pi;

extern int threshold1;
extern int threshold2;
extern int threshold3;
extern int threshold4;

extern brain Brain;
extern brain::lcd LCD;
extern controller::lcd ControllerLCD;

extern competition Competition;
extern color Color;

extern controller Controller;

extern motor frontLeftMotor;
extern motor frontRightMotor;
extern motor backLeftMotor;
extern motor backRightMotor;
extern motor backLiftMotor;
extern motor frontLiftMotor;
extern motor leftIntakeMotor;
extern motor rightIntakeMotor;

extern motor_group leftMotors;
extern motor_group rightMotors;
extern motor_group driveMotors;
extern motor_group liftMotors;
extern motor_group intakeMotors;

extern inertial inertialSensor;
extern optical opticalSensor;
extern distance distanceSensor;

extern rotation leftRotationSensor;
extern rotation rightRotationSensor;
extern rotation backRotationSensor;

extern drivetrain mainDrivetrain;

extern timer t1;

extern vision::signature SIG_1;
extern vision::signature SIG_2;
extern vision::signature SIG_3;
extern vision::signature SIG_4;
extern vision::signature SIG_5;
extern vision::signature SIG_6;
extern vision::signature SIG_7;
extern vision visionSensor;

bool checkDevices(bool p_cancel = false);

int error(std::string str = "", std::string str2 = "", bool cond = true);

void vexcodeInit(void);
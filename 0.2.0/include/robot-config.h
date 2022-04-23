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

class rotation_x : public vex::rotation{
private:
  double wrapAngle(double theta){
    double temp_theta = fmod(theta, 2 * M_PI);
    if(temp_theta < 0) temp_theta += 2 * M_PI;
    return temp_theta * 180 / M_PI;
  }
public:
  double offset;
  rotation_x(uint32_t index, bool reverse = false, double offset = 0) : 
    vex::rotation(index, reverse), offset(offset)
  {}

  ~rotation_x(){}

  double angle(rotationUnits units = rotationUnits::deg){
    if(units == rotationUnits::deg) 
      return wrapAngle(M_PI / 180 * (rotation::angle(units) + offset));
    else
      return rotation::angle(units);
  }
};
extern rotation_x fourBarRotationSensor;
extern const double fourBarMinPos;
extern const double fourBarMaxPos;

extern motor ringLiftMotor;

extern inertial inertialSensor;

extern digital_out leftClawSolenoid;
extern digital_out rightClawSolenoid;
extern digital_out backLiftSolenoid;

extern motor_group leftMotors;
extern motor_group rightMotors;
extern motor_group driveMotors;
extern motor_group allMotors;

extern vision::signature FRONT_REDMOGO;
extern vision::signature FRONT_BLUEMOGO;
extern vision::signature FRONT_YELLOWMOGO;
extern vision frontVisionSensor;

extern vision::signature BACK_REDMOGO;
extern vision::signature BACK_BLUEMOGO;
extern vision::signature BACK_YELLOWMOGO;
extern vision backVisionSensor;

extern void sensorInit();
extern void autonInit();
extern void motorInit();

extern bool checkDevices(bool p_cancel = false);
#include "vex.h"
#include "enums.h"
#include "configvalues.h"
#include <cmath>
#include "odom.h"

using namespace vex;

void inertialDebug()
{  
  inertial::quaternion inertialSensor_quaternion;
  inertialSensor_quaternion = inertialSensor.orientation();
  Brain.Screen.clearScreen();

  Brain.Screen.setFont(mono15);
  Brain.Screen.setPenColor(white);
  Brain.Screen.setFillColor(black);
  
  Brain.Screen.printAt(20, 30, "GX  %8.3f", inertialSensor.gyroRate(xaxis, dps));
  Brain.Screen.printAt(20, 45, "GY  %8.3f", inertialSensor.gyroRate(yaxis, dps));
  Brain.Screen.printAt(20, 60, "GZ  %8.3f", inertialSensor.gyroRate(zaxis, dps));

  Brain.Screen.printAt(20, 90, "AX  %8.3f", inertialSensor.acceleration(xaxis));
  Brain.Screen.printAt(20, 105, "AY  %8.3f", inertialSensor.acceleration(yaxis));
  Brain.Screen.printAt(20, 120, "AZ  %8.3f", inertialSensor.acceleration(zaxis));

  Brain.Screen.printAt(20, 150, "A   %8.3f", inertialSensor_quaternion.a);
  Brain.Screen.printAt(20, 165, "B   %8.3f", inertialSensor_quaternion.b);
  Brain.Screen.printAt(20, 180, "C   %8.3f", inertialSensor_quaternion.c);
  Brain.Screen.printAt(20, 195, "D   %8.3f", inertialSensor_quaternion.d);

  Brain.Screen.printAt(150, 30, "Roll     %7.2f", inertialSensor.roll());
  Brain.Screen.printAt(150, 45, "Pitch    %7.2f", inertialSensor.pitch());
  Brain.Screen.printAt(150, 60, "Yaw      %7.2f", inertialSensor.yaw());

  Brain.Screen.printAt(150, 90, "Heading  %7.2f", inertialSensor.heading());
  Brain.Screen.printAt(150, 105, "Rotation %7.2f", inertialSensor.rotation());

  Brain.Screen.render();
}

void opticalDebug()
{
  LCD.clearScreen();
  LCD.setFont(mono60);
  LCD.setCursor(1, 1);
  if(opticalSensor.isNearObject())
  {
    if(redMin < opticalSensor.hue() && opticalSensor.hue() < redMax)
    {
      LCD.clearScreen();
      LCD.print("RED 1");
    }
    else if(redMin1 < opticalSensor.hue() && opticalSensor.hue() < redMax1)
    {
      LCD.clearScreen();
      LCD.print("RED 2");
    }
    else if(blueMin < opticalSensor.hue() && opticalSensor.hue() < blueMax)
    {
      LCD.clearScreen();
      LCD.print("BLUE");
    }
    else
    {
      LCD.clearScreen();
      LCD.print("OTHER");
    }
  }
  else
  {
    LCD.clearScreen();
    LCD.print("OBJECT NOT FOUND");
  }
  LCD.render();
}

void f_forward(double rots, int speed, int timeout, bool wait)
{
  driveMotors.setTimeout(timeout, msec);
  driveMotors.spinFor(rots, deg, speed, velocityUnits::pct, wait);
  driveMotors.setTimeout(0, msec);
}

int P(int currentPos, int target, double kP)
{
  int error = target - currentPos;
  int pow = error * kP;
  return pow;
}

/*
_______________________________________________________________________________________________________________________________________________________
|                        |                        |                        |                        |                        |                        |
|       PARAMETER        |       RISE TIME        |       OVERSHOOT        |     SETTLING TIME      |   STEADY-STATE ERROR   |       STABILITY        |
|________________________|________________________|________________________|________________________|________________________|________________________|
|                        |                        |                        |                        |                        |                        |
|           kP           |        DECREASE        |        INCREASE        |          N/A           |        DECREASE        |        WORSENS         |
|________________________|________________________|________________________|________________________|________________________|________________________|
|                        |                        |                        |                        |                        |                        |
|           kI           |        DECREASE        |        INCREASE        |        INCREASE        |        DECREASE        |        WORSENS         |
|________________________|________________________|________________________|________________________|________________________|________________________|
|                        |                        |                        |                        |                        |                        |
|           kD           |          N/A           |        DECREASE        |        DECREASE        |          N/A           |        IMPROVES        |
|________________________|________________________|________________________|________________________|________________________|________________________|

*/

void PIDTurn(const double target, const int timeout,const double maxError, const double kP, const double kI, const double kD,  const int dT)
{
  timer t_timer;
  t_timer.reset();
  driveMotors.setTimeout(timeout, msec);

  double currentPos = inertialSensor.rotation(deg);

  double error = target - currentPos;
  double pow = 100;
  double integral = 0;
  double derivative;
  double prevError = error;

  while(std::abs(pow) > 2.5)
  {
    if(t_timer.time(msec) > timeout && timeout != 0) break;

    currentPos = inertialSensor.rotation(deg);
    bool dir = target < currentPos;

    error = target - currentPos;

    integral += error;
    if(dir) {if(error == 0 || currentPos < target) integral = 0;}
    else if(!dir) {if(error == 0 || currentPos > target) integral = 0;}
    if(std::abs(error) > maxError) integral = 0;

    derivative = error - prevError;
    prevError = error;

    pow = (error * kP) + (integral * kI) + (derivative * kD);

    ControllerLCD.clearScreen();
    ControllerLCD.setCursor(1, 1);
    ControllerLCD.print("%3.3f", currentPos);
    ControllerLCD.setCursor(2, 1);
    ControllerLCD.print("%3.3f", pow);

    leftMotors.spin(fwd, pow, pct);
    rightMotors.spin(fwd, -pow, pct);

    wait(dT, msec);
  }
  driveMotors.setTimeout(0, msec);
  driveMotors.stop();
}

void PIDForward(double target, const int timeout, const double maxError, const double kP, const double kI, const double kD,  const int dT)
{
  timer t_timer;
  t_timer.reset();
  driveMotors.setTimeout(timeout, msec);

  target += backRightMotor.rotation(deg);

  //double currentPosLeft = (frontLeftMotor.rotation(deg) + backLeftMotor.rotation(deg)) / 2;
  double currentPosRight = (frontRightMotor.rotation(deg) + backRightMotor.rotation(deg)) / 2;
  double currentPos = currentPosRight;

  double error = target - currentPos;
  double pow = 100;
  double integral = 0;
  double derivative;
  double prevError = error;

  while(std::abs(pow) > 2.5)
  {
    if(t_timer.time(msec) > timeout && timeout != 0) break;

    currentPos = (frontRightMotor.rotation(deg) + backRightMotor.rotation(deg)) / 2;
    bool dir = target < currentPos;

    error = target - currentPos;

    integral += error;
    if(dir) {if(error == 0 || currentPos < target) integral = 0;}
    else if(!dir) {if(error == 0 || currentPos > target) integral = 0;}
    if(std::abs(error) > maxError) integral = 0;

    derivative = error - prevError;
    prevError = error;

    pow = (error * kP) + (integral * kI) + (derivative * kD);

    ControllerLCD.clearScreen();
    ControllerLCD.setCursor(1, 1);
    ControllerLCD.print("%3.3f", currentPos);
    ControllerLCD.setCursor(2, 1);
    ControllerLCD.print("%3.3f", pow);

    driveMotors.spin(fwd, pow, pct);

    wait(dT, msec);
  }
  driveMotors.setTimeout(0, msec);
  driveMotors.stop();
}

void PDistanceForward(const double target, const double kP)
{
  double pow = 100;
  while(std::abs(pow) > 2.5)
  {
    double currentPos = distanceSensor.objectDistance(distanceUnits::in);
    double error = target - currentPos;
    pow = error * kP;
    driveMotors.spin(fwd, pow, pct);
  }
}

void PIDDistanceForward(const double target, const int timeout, const double maxError, const double kP, const double kI, const double kD,  const int dT)
{
  timer t_timer;
  t_timer.reset();
  driveMotors.setTimeout(timeout, msec);

  double currentPos = distanceSensor.objectDistance(distanceUnits::in);

  double error = target - currentPos;
  double pow = 100;
  double integral = 0;
  double derivative;
  double prevError = error;

  while(std::abs(pow) > 2.5)
  {
    if(t_timer.time(msec) > timeout && timeout != 0) break;

    currentPos = distanceSensor.objectDistance(distanceUnits::in);
    bool dir = target < currentPos;

    error = target - currentPos;

    integral += error;
    if(dir) {if(error == 0 || currentPos < target) integral = 0;}
    else if(!dir) {if(error == 0 || currentPos > target) integral = 0;}
    if(std::abs(error) > maxError) integral = 0;

    derivative = error - prevError;
    prevError = error;

    pow = (error * kP) + (integral * kI) + (derivative * kD);

    ControllerLCD.clearScreen();
    ControllerLCD.setCursor(1, 1);
    ControllerLCD.print("%3.3f", currentPos);
    ControllerLCD.setCursor(2, 1);
    ControllerLCD.print("%3.3f", pow);

    driveMotors.spin(fwd, -pow, pct);

    wait(dT, msec);
  }
  driveMotors.setTimeout(0, msec);
  driveMotors.stop();
}

/*int findTurnDir(int currentPos, int target)
{
  int error = target - currentPos;
  if(error < 0) error += 360;

  if(error > 180) return -1;
  else return 1;
}

int findTurnDir2(int currentPos, int target)
{
  if(target > currentPos) return 1;
  else return -1;
}

int findVTurnDir(int currentPos)
{
  if(currentPos < 158) return -1;
  else return 1;
}

void PIDTurn(int target, turnDirection turnDir, const double maxError, const double kP, const double kI, const double kD,  const int dT)
{
  double currentPos = inertialSensor.rotation(deg);

  double error = target - currentPos;
  double pow;
  double speed;
  double integral = 0;
  double derivative;
  double prevError = error;

  bool dir = target < currentPos;

  int kTurnDir;

  switch(turnDir)
  {
    case Left:
      kTurnDir = -1;
      break;
    case Right:
      kTurnDir = 1;
      break;
    case Auto:
      if(dir) kTurnDir = 1;
      else kTurnDir = -1;
      break;
    default:
      kTurnDir = 0;
      break;
  }

  while(std::abs(error) > 2.5)
  {
    currentPos = inertialSensor.rotation(deg);
    error = target - currentPos;

    integral += error;
    if(dir) {if(error == 0 || currentPos < target) integral = 0;}
    else if(!dir) {if(error == 0 || currentPos < target) integral = 0;}
    if(std::abs(error) > maxError) integral = 0;

    derivative = error - prevError;
    prevError = error;

    pow = (error * kP) + (integral * kI) + (derivative * kD);
    speed = std::abs(pow);

    leftMotors.spin(fwd, speed * kTurnDir, pct);
    rightMotors.spin(fwd, speed * -kTurnDir, pct);

    wait(dT, msec);
  }
  driveMotors.stop();
}

void pTurn(int target, turnDirection turnDir = Auto, double kP = 0.55f)
{
  bool done = false;
  bool x = true;
  while(!done)
  {
    int currentPos = inertialSensor.heading();

    int dir = 0;
    switch(turnDir)
    {
      case Left:
        dir = -1;
        break;
      case Right:
        dir = 1;
        break;
      case Auto:
        dir = findTurnDir(currentPos, target);
        break;
    }

    while(true)
    {
      currentPos = inertialSensor.heading();
      int speed = abs(P(currentPos, target, kP));

      leftMotors.spin(fwd, speed * dir, pct);
      rightMotors.spin(fwd, -speed * dir, pct);

      if(!x) done = !(abs((int)((frontLeftMotor.velocity(pct) + frontRightMotor.velocity(pct) + backLeftMotor.velocity(pct) + backRightMotor.velocity(pct)) / 4)) > 1);
      wait(1, msec);
      if(currentPos > target - 1.5 && currentPos < target + 1.5) break;
      x = !x;
      wait(1, msec);
    }
    driveMotors.stop();
  }
}

void pTurn2(int target, turnDirection turnDir = Auto, double kP = 0.55f)
{
  bool done = false;
  while(!done)
  {
    int currentPos = inertialSensor.rotation();

    int dir = 0;
    switch(turnDir)
    {
      case Left:
        dir = -1;
        break;
      case Right:
        dir = 1;
        break;
      case Auto:
        dir = findTurnDir2(currentPos, target);
        break;
    }

    while(true)
    {
      currentPos = inertialSensor.rotation();
      int speed = abs(P(currentPos, target, kP));

      leftMotors.spin(fwd, speed * dir, pct);
      rightMotors.spin(fwd, -speed * dir, pct);

      if(speed < 5) done = true;

      if(currentPos > target - 2.5 && currentPos < target + 2.5) break;
    }
    driveMotors.stop();
  }
}

void pVTurn(vision::signature *sig, turnDirection turnDir = Auto, double kP = 0.55f)
{
  const int minSize = 5;

  bool done = false;
  while(!done)
  {
    visionSensor.takeSnapshot(*sig);
    vision::object *t_obj = &visionSensor.largestObject;
    vision::object obj = *t_obj;

    int currentPos = obj.centerX;

    int dir = 0;
    switch(turnDir)
    {
      case Left:
        dir = -1;
        break;
      case Right:
        dir = 1;
        break;
      case Auto:
        dir = findVTurnDir(currentPos);
        break;
      default:
        dir = 1;
        break;
    }

    if((!obj.exists) || (obj.width < minSize || obj.height < minSize))
    {
      LCD.clearScreen();
      LCD.setCursor(1, 1);
      LCD.print("OBJECT NOT FOUND");
    }
    else
    {
      int speed = abs(P(currentPos));

      LCD.clearScreen();
      LCD.setCursor(1, 1);
      LCD.print("%d", currentPos);
      LCD.setCursor(2, 1);
      LCD.print("%d", speed);
      LCD.render();

      leftMotors.spin(fwd, speed * dir, pct);
      rightMotors.spin(fwd, -speed * dir, pct);

      wait(3, sec);

      done = !(((frontLeftMotor.velocity(pct) + frontRightMotor.velocity(pct) + backLeftMotor.velocity(pct) + backRightMotor.velocity(pct)) / 4) > 1);
      wait(1, msec);
      if(currentPos > 58 - 1.5 && currentPos < 58 + 1.5) break;
    }
  }
  driveMotors.stop();
}

void inertialTurn(int target, turnType turnDir, int speed, bool c)
{
  if(turnDir == right)
  {
    leftMotors.spin(forward, speed, percentUnits::pct);
    rightMotors.spin(reverse, speed, percentUnits::pct);

    if(c) while(inertialSensor.heading(degrees) <= target) wait(1, msec);
    if(!c) while(inertialSensor.heading(degrees) >= target) wait(1, msec);
  }
  else if(turnDir == left)
  {
    leftMotors.spin(reverse, speed, percentUnits::pct);
    rightMotors.spin(forward, speed, percentUnits::pct);

    if(c) while(inertialSensor.heading(degrees) <= target) wait(1, msec);
    if(!c) while(inertialSensor.heading(degrees) >= target) wait(1, msec);
  }
  
  driveMotors.stop(brake);
}

//void t_inertialTurn(int target = 90, turnType turnDir = right, int speed = 50)

void pInertialTurn(int target = 90, double kP = 0.55, int accuracy = 3)
{
  bool done = false;
  while(!done)
  {
    int currentPos = inertialSensor.heading();
    int speed = P(currentPos, target, kP);
    rightMotors.setVelocity(speed, pct);
    leftMotors.setVelocity(-speed, pct);
    if(currentPos < target - accuracy || currentPos > target + accuracy) driveMotors.spin(fwd);
    else done = true;
    Task.sleep(1);
  }
  driveMotors.stop();
}

void pVisionTurn(vision::signature sig, double kP = 0.55, int accuracy = 3)
{
  const int minSize = 15;

  visionSensor.takeSnapshot(sig);
  vision::object obj = visionSensor.largestObject;

  if((!obj.exists) || (obj.width < minSize || obj.height < minSize))
  {
    LCD.clearScreen();
    LCD.printAt(20, 20, "Object doesn't exist");
    LCD.render();
  }
  else
  {
    bool done = false;
    while(!done)
    {
      int speed = P(obj.centerX, 158, kP);
      rightMotors.setVelocity(speed, pct);
      leftMotors.setVelocity(-speed, pct);

      if(obj.centerX < 158 - accuracy || obj.centerX > 158 + accuracy)
      {
        driveMotors.spin(fwd);
        LCD.clearScreen();
        LCD.printAt(20, 20, "Turning");
        LCD.printAt(20, 60, "%d", obj.centerX);
        LCD.render();
      }
      else done = true;
      visionSensor.takeSnapshot(sig);
      obj = visionSensor.largestObject;
      Task.sleep(5);
    }
    LCD.clearScreen();
    LCD.printAt(20, 20, "Done");
    LCD.render();
    driveMotors.stop();
  }
}

void visionTurn(vision::signature sig, int accuracy = 3, int speed = 10)
{
  const int minSize = 15;

  accuracy = abs(accuracy);

  visionSensor.takeSnapshot(sig);
  vision::object obj = visionSensor.largestObject;

  if((!obj.exists) || (obj.width < minSize || obj.height < minSize))
  {
    LCD.clearScreen();
    LCD.printAt(20, 20, "Object doesn't exist");
    LCD.render();
  }
  else
  {
    bool done = false;
    while(!done)
    {
      visionSensor.takeSnapshot(sig, 1);
      vision::object obj = visionSensor.largestObject;
      ControllerLCD.clearLine(2);
      ControllerLCD.print("%d", obj.centerX);
      if(obj.centerX < 158 - accuracy)
      {
        leftMotors.spin(reverse, speed, percentUnits::pct);
        rightMotors.spin(forward, speed, percentUnits::pct);
      }
      else if(obj.centerX > 158 + accuracy)
      {
        leftMotors.spin(forward, speed, percentUnits::pct);
        rightMotors.spin(reverse, speed, percentUnits::pct);
      }
      else done = true;
    }
    driveMotors.stop(brake);
  }
}

bool charToBool(char str)
{
  if(str == '0') return false;
  else if(str == '1') return true;
  else return false;
}

int PIDTurn(motor_group motor1, motor_group motor2, int target, int range, int accuracy, double kP, double kI, double kD, inertial sensor, int dT = 15, bool reversed = false)
{
  int integral;
  int error;
  int prevError;
  int derivative;
  int pow;
  int reverse = 1;
  int sensorValue = sensor.heading(deg);

  if(reversed)
  {
    reverse = -1;
  }

  while(sensorValue > (target + accuracy) % 360 || sensorValue < (target - accuracy) % 360)
  {
    sensorValue = sensor.heading(deg);
    error = target - sensorValue;
    integral += error;

    if(error == 0 || error > range)
    {
      integral = 0;
    }

    derivative = error - prevError;
    prevError = error;
    pow = (error * kP) + (integral * kI) + (derivative * kD);
    motor1.setVelocity(pow * reverse, pct);
    motor2.setVelocity(-pow * reverse, pct);
    Task.sleep(dT);
  }

  return 1;
}

int PIDTurn(motor_group motor1, motor_group motor2, int target, int range, int accuracy, double kP, double kI, double kD, encoder sensor, int dT = 15, bool reversed = false)
{
  int integral;
  int error;
  int prevError;
  int derivative;
  int pow;
  int reverse = 1;
  int sensorValue = sensor.heading(deg);

  if(reversed)
  {
    reverse = -1;
  }

  while(sensorValue > (target + accuracy) % 360 || sensorValue < (target - accuracy) % 360)
  {
    sensorValue = sensor.heading(deg);
    error = target - sensorValue;
    integral += error;

    if(error == 0 || error > range)
    {
      integral = 0;
    }

    derivative = error - prevError;
    prevError = error;
    pow = (error * kP) + (integral * kI) + (derivative * kD);
    motor1.setVelocity(pow * reverse, pct);
    motor2.setVelocity(-pow * reverse, pct);
    Task.sleep(dT);
  }

  return 1;
}

int PID(motor_group motors, int target, int range, int accuracy, double kP, double kI, double kD, int sensorValue, int dT = 15, bool reversed = false)
{
  int integral;
  int error;
  int prevError;
  int derivative;
  int pow;
  int reverse = 1;

  if(reversed)
  {
    reverse = -1;
  }

  while(sensorValue > (target + accuracy) % 360 || sensorValue > (target - accuracy) % 360)
  {
    error = target - sensorValue;
    integral += error;

    if(error == 0 || error > range)
    {
      integral = 0;
    }

    derivative = error - prevError;
    prevError = error;
    pow = (error * kP) + (integral * kI) + (derivative * kD);
    motors.setVelocity(pow * reverse, pct);
    Task.sleep(dT);
  }

  return 1;
}
*/
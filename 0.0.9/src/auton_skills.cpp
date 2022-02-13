#include "vex.h"
#include "functions.h"
#include "configvalues.h"
#include <cmath>

using namespace vex;

void auton_Skills()
{
  //score 1
  liftMotors.spin(fwd, -100, pct);
  wait(500, msec);
  liftMotors.stop();

  //get 2
  intakeMotors.spin(fwd, 100, pct);
  PIDForward(400);
  liftMotors.spin(fwd, -100, pct);
  wait(0.35, sec);
  liftMotors.stop();
  intakeMotors.stop();
  PIDTurn(0);
  PIDForward(350);

  //score 2
  PIDTurn(-88.25);
  PIDForward(350, 750, 360, 0.3);

  liftMotors.spin(fwd, -100, pct);
  wait(0.75, sec);
  liftMotors.stop();
  f_forward(-50);

  //get 3
  PIDTurn(2.5);
  intakeMotors.spin(fwd, 100, pct);
  PIDForward(780);
  liftMotors.spin(fwd, -100, pct);
  wait(0.35, sec);
  liftMotors.stop();
  intakeMotors.stop();

  //score 3
  PIDTurn(-47.5);
  f_forward(650, 45, 1300);
  f_forward(-5);
  liftMotors.spin(fwd, -100, pct);
  wait(0.75, sec);
  liftMotors.stop();
  f_forward(-230);

  //get 4
  PIDTurn(87.5);
  f_forward(-300, 75, 1500);
  PIDTurn(90);

  intakeMotors.spin(fwd, 100, pct);
  /*driveMotors.spin(fwd, 50, pct);
  while(distanceSensor.objectDistance(distanceUnits::in) > 68.25) wait(1, msec);
  driveMotors.stop();*/
  PIDForward(1005);
  liftMotors.spin(fwd, -100, pct);
  wait(0.35, sec);
  liftMotors.stop();
  intakeMotors.stop();
  PIDTurn(0);

  //score 4
  f_forward(450, 65, 700);
  liftMotors.spin(fwd, -100, pct);
  wait(1, sec);
  liftMotors.stop();
  f_forward(-50);
}

void auton_Skills2()
{
  //get 5
  f_forward(-210);

  PIDTurn(89.5);
  intakeMotors.spin(fwd, 100, pct);
  PIDForward(900);
  f_forward(-50);
  liftMotors.spin(fwd, -100, pct);
  wait(0.25, sec);
  liftMotors.stop();
  intakeMotors.stop();

  //score 5
  PIDTurn(45);

  f_forward(1000, 65, 1700);
  f_forward(-35);
  liftMotors.spin(fwd, -100, pct);
  wait(0.75, sec);
  liftMotors.stop();
  f_forward(-800);
  wait(3, sec);

  //get 6
  PIDTurn(-90);
  PIDTurn(-140);
  intakeMotors.spin(fwd, 100, pct);
  PIDForward(500);
  liftMotors.spin(fwd, -100, pct);
  wait(0.25, sec);
  liftMotors.stop();
  intakeMotors.stop();

  //score 6
  PIDTurn(90);
  f_forward(50, 65, 1500);
  f_forward(-35);
  liftMotors.spin(fwd, -100, pct);
  wait(0.75, sec);
  liftMotors.stop();
  f_forward(-75);

  //get 7
  PIDTurn(250);
  intakeMotors.spin(fwd, 100, pct);
  PIDForward(500);
  liftMotors.spin(fwd, -100, pct);
  wait(0.25, sec);
  liftMotors.stop();
  intakeMotors.stop();
}

void auton_Skills2a()
{
  //get 5
  f_forward(-200);

  PIDTurn(89.85);
  intakeMotors.spin(fwd, 100, pct);
  PIDForward(1000);
  f_forward(-50);
  liftMotors.spin(fwd, -100, pct);
  wait(0.25, sec);
  liftMotors.stop();
  intakeMotors.stop();

  //score 5
  PIDTurn(32);

  f_forward(1000, 65, 1700);
  f_forward(-35);
  liftMotors.spin(fwd, -100, pct);
  wait(0.75, sec);
  liftMotors.stop();
  f_forward(-75);

  //get 6
  PIDTurn(-142.5);

  intakeMotors.spin(fwd, 100, pct);
  PIDForward(1150);
  liftMotors.spin(fwd, -100, pct);
  wait(0.35, sec);
  liftMotors.stop();
  intakeMotors.stop();

  //score 6
  PIDTurn(-270);
  f_forward(700, 65, 1750);
  liftMotors.spin(fwd, -100, pct);
  wait(0.75, sec);
  liftMotors.stop();
  f_forward(-75);
}

void auton_Skills3()
{
  //get 7
  PIDTurn(170.65, 0, 360, 0.35);
  intakeMotors.spin(fwd, 100, pct);
  PIDForward(580, 0, 360, 0.25);
  liftMotors.spin(fwd, -100, pct);
  wait(0.275, sec);
  liftMotors.stop();
  intakeMotors.stop();

  //score 7
  PIDTurn(134);
  f_forward(650, 65, 925);
  f_forward(-25);
  liftMotors.spin(fwd, -100, pct);
  wait(0.75, sec);
  liftMotors.stop();
  f_forward(-75);

  //get 8
  PIDTurn(264.5);

  intakeMotors.spin(fwd, 100, pct);
  PIDForward(800);
  liftMotors.spin(fwd, -100, pct);
  wait(0.2, sec);
  liftMotors.stop();
  intakeMotors.stop();
  PIDTurn(177.5);

  //score 8
  f_forward(450, 65, 700);
  liftMotors.spin(fwd, -100, pct);
  wait(1, sec);
  liftMotors.stop();
  f_forward(-50);

  //get 9
  PIDTurn(351.625);
  intakeMotors.spin(fwd, 100, pct);
  f_forward(350, 65);
  liftMotors.spin(fwd, -100, pct);
  wait(0.2, sec);
  liftMotors.stop();
  intakeMotors.stop();

  //score 9
  f_forward(350, 50, 1500);
  liftMotors.spin(fwd, -100, pct);
  intakeMotors.spin(fwd, 100, pct);
  wait(1.5, sec);
  liftMotors.stop();
  intakeMotors.stop();

  //descore 9
  f_forward(350, 50, 1500);
  f_forward(-200);
  f_forward(350, 50, 1500);
  f_forward(-200);
  f_forward(350, 50, 1500);
  f_forward(-100);
}

void PIDTest()
{
  PIDForward(720, 0, 360, 0.45, 0.0003829787235, 0.2449323333, 15);
  //PIDTurn(90, 0, 360, 0.35, 0.0002330097087, 0.09115200003, 15);
  //PIDTurn(90, 0, 360, kU, 0, 0, 15);
}

void distanceTest()
{
  double target = 10;
  double pow = 100;
  while(std::abs(pow) > 2.5)
  {
    double currentPos = distanceSensor.objectDistance(distanceUnits::in);
    double error = target - currentPos;
    pow = error * 4;
    driveMotors.spin(fwd, -pow, pct);
  }
}
#include "vex.h"
#include <math.h>
#include <cmath>
#include "enums.h"
#include "functions.h"
#include "odom.h"

using namespace vex;

namespace odom
{
  const double π = 3.1415926535897932;

  const double wheelRadius = 1.625;

  const double s_L = 5.0125;
  const double s_R = 5.0125;
  const double s_S = 17;

  double posX;
  double posY;
  double posθ;

  /*
      θ: Alt+03b8
      π: Alt227
      Δ: Alt+0394
  */

  bool running = true;

  odomType p_odomType = Inertial;

  int odometry()
  {
    switch(p_odomType)
    {
      case Inertial:
      {
        double encL_0 = 0;
        double encR_0 = 0;
        double encS_0 = 0;

        double θ_0 = 0;
        double d_0_x = 0;
        double d_0_y = 0;

        while(running)
        {
          double encL = leftRotationSensor.position(deg);
          double encR = rightRotationSensor.position(deg);
          double encS = backRotationSensor.position(deg);

          [[maybe_unused]]
          double ΔL = 2 * π * wheelRadius * (encL - encL_0) / 360;
          double ΔR = 2 * π * wheelRadius * (encR - encR_0) / 360;
          double ΔS = 2 * π * wheelRadius * (encS - encS_0) / 360;

          encL_0 = encL;
          encR_0 = encR;
          encS_0 = encS;

          double θ_1 = inertialSensor.rotation(deg) * π / 180;

          double Δθ = θ_1 - θ_0;

          double Δd_l_x = 0;
          double Δd_l_y = 0;
          if(Δθ == 0)
          {
            Δd_l_x = ΔS;
            Δd_l_y = ΔR;
          }
          else
          {
          /*****************************************************
          */Δd_l_x = 2 * std::sin(Δθ / 2) * ((ΔS / Δθ));      /*
          *****************************************************/
            Δd_l_y = 2 * std::sin(Δθ / 2) * ((ΔR / Δθ) + s_R);
          }

          double θ_m = θ_0 + (Δθ / 2);
          θ_0 = θ_1;

          double pl_r = std::sqrt(Δd_l_x * Δd_l_x + Δd_l_y * Δd_l_y);
          double pl_θ = std::atan2(Δd_l_y, Δd_l_x);

          pl_θ -= θ_m;

          double Δd_x = pl_r * std::cos(pl_θ);
          double Δd_y = pl_r * std::sin(pl_θ);

          double d_1_x = d_0_x + Δd_x;
          double d_1_y = d_0_y + Δd_y;

          d_0_x = d_1_x;
          d_0_y = d_1_y;

          posX = d_1_x;
          posY = d_1_y;
          posθ = θ_1;

          LCD.clearScreen();
          LCD.printAt(20 , 60, "Δθ:  %3.3f  ", Δθ);
          LCD.printAt(160, 60, "dlx: %3.3f  ", Δd_l_x);
          LCD.printAt(300, 60, "dly: %3.3f  ", Δd_l_y);
          LCD.printAt(20, 100, "rx:  %3.3f  ", (ΔS / Δθ));
          LCD.render();
        }
      } break;
      case Classic:
      {
        double encL_0 = 0;
        double encR_0 = 0;
        double encS_0 = 0;

        double θ_0 = 0;
        double d_0_x = 0;
        double d_0_y = 0;

        while(running)
        {
          double encL = leftRotationSensor.position(deg);
          double encR = rightRotationSensor.position(deg);
          double encS = backRotationSensor.position(deg);

          double ΔL = 2 * π * wheelRadius * (encL - encL_0) / 360;
          double ΔR = 2 * π * wheelRadius * (encR - encR_0) / 360;
          double ΔS = 2 * π * wheelRadius * (encS - encS_0) / 360;

          encL_0 = encL;
          encR_0 = encR;
          encS_0 = encS;

          double θ_1 = θ_0 + (ΔL - ΔR) / (s_L + s_R);

          double Δθ = θ_1 - θ_0;

          double Δd_l_x = 0;
          double Δd_l_y = 0;
          if(Δθ == 0)
          {
            Δd_l_x = ΔS;
            Δd_l_y = ΔR;
          }
          else
          {
            Δd_l_x = 2 * std::sin(Δθ / 2) * ((ΔS / Δθ) + s_S);
            Δd_l_y = 2 * std::sin(Δθ / 2) * ((ΔR / Δθ) + s_R);
          }

          double θ_m = θ_0 + (Δθ / 2);
          θ_0 = θ_1;

          double pl_r = std::sqrt(Δd_l_x * Δd_l_x + Δd_l_y * Δd_l_y);
          double pl_θ = std::atan2(Δd_l_y, Δd_l_x);

          pl_θ -= θ_m;

          double Δd_x = pl_r * std::cos(pl_θ);
          double Δd_y = pl_r * std::sin(pl_θ);

          double d_1_x = d_0_x + Δd_x;
          double d_1_y = d_0_y + Δd_y;

          d_0_x = d_1_x;
          d_0_y = d_1_y;

          posX = d_1_x;
          posY = d_1_y;
          posθ = θ_1;

          LCD.clearScreen();
          LCD.setCursor(1, 1);
          LCD.print("X: %3.3f  ", posX);
          LCD.print("Y: %3.3f  ", posY);
          LCD.print("θ: %3.3f  ", posθ);
          LCD.newLine();
          LCD.print("L: %3.3f  ", encL);
          LCD.print("R: %3.3f  ", encR);
          LCD.print("S: %3.3f  ", encS);
          LCD.render();
        }
      } break;
      default:
      {

      } break;
    }
    return 0;
  }

  double getCurrentPosX()
  {
    return posX;
  }

  double getCurrentPosY()
  {
    return posY;
  }

  double getCurrentPosθ(angleUnits u)
  {
    switch(u){
      case angleUnits::Rad:{
        return posθ;
      }break;
      case angleUnits::Deg:{
        return posθ * 180 / π;
      }break;
    }
    
  }

  void PIDTurnOdom(const double target, angleUnits u, const int timeout, const double maxError, const double kP, const double kI, const double kD,  const int dT)
  {
    timer t_timer;
    t_timer.reset();
    driveMotors.setTimeout(timeout, msec);

    double currentPos = getCurrentPosθ(u);

    double error = target - currentPos;
    double pow = 100;
    double integral = 0;
    double derivative;
    double prevError = error;

    while(true)
    {
      if(t_timer.time(msec) > timeout && timeout != 0) break;

      currentPos = getCurrentPosθ(angleUnits::Deg);
      bool dir = target < currentPos;

      if(dir) {if(std::abs(pow) < 2.5 && currentPos > target - 0.015) break;}
      else {if(std::abs(pow) < 2.5 && currentPos < target + 0.015) break;}

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

  int turnToAngle(double θ, angleUnits u)
  { 
    PIDTurnOdom(θ, u);
    return 0;
  }

  int turnToPoint(double x, double y)
  {
    double Δx = x - getCurrentPosX();
    double Δy = y - getCurrentPosY();

    double θ = std::atan2(Δy, Δx) * 180 / π;

    turnToAngle(θ);
    return 0;
  }

  int goToPointTurn(double x, double y)
  {
    turnToPoint(x, y);

    double leftPow, rightPow;
    
    while(true)
    {
      double Δx = x - getCurrentPosX();
      double Δy = y - getCurrentPosY();

      double θ = std::atan2(Δy, Δx);
      double Δθ = θ - getCurrentPosθ();

      if(std::abs(Δθ) > 0.0261799388)
      {
        if(Δθ > 0){

        }
      }
    }

    return 0;
  }
}
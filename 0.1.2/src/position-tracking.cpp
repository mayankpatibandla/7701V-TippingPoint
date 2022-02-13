#include "vex.h"

using namespace vex;

//Position Tracking (with inertial sensor)
namespace positionTracking{
//radius of tracking wheels (in inches)
const double WHEEL_RADIUS = 1.625;

//left-right distance between left or right tracking wheel and tracking center (in inches)
[[maybe_unused]]  //left tracking wheel is unused
const double s_L = 6.375;
const double s_R = 6.375;
//forward-backward distance between back tracking wheel and tracking center (in inches)
const double s_S = 6;

double pos_x;       //x position of robot (in inches)
double pos_y;       //y position of robot (in inches)
double pos_theta;   //angle of robot's heading (in radians)

//main position tracking function, will be used in its own thread
void positionTracking(){
  //previous position of encoders: L = left, R = right, S = back
  double encL_0 = 0, encR_0 = 0, encS_0 = 0;

  //previous positions of robot: theta = heading angle (in radians), x & y = position (in inches)
  double theta_0 = 0, d_0_x = 0, d_0_y = 0;

  while(true){
    //encoder sensor readings (in degrees)
    double encL = leftRotationSensor.position(deg);
    double encR = rightRotationSensor.position(deg);
    double encS = backRotationSensor.position(deg);

    //Change in position for each tracking wheel
    //Equation is circumfrence of wheel times section of circle where the encoder's angle changed:
    //delta = 2 * pi * radius * deltaEnc / 360
    [[maybe_unused]]  //left tracking wheel is unused
    double delta_L = 2 * M_PI * WHEEL_RADIUS * (encL - encL_0) / 360;
    double delta_R = 2 * M_PI * WHEEL_RADIUS * (encR - encR_0) / 360;
    double delta_S = 2 * M_PI * WHEEL_RADIUS * (encS - encS_0) / 360;

    //set previous encoder angles to current ones for use in next loop cycle
    encL_0 = encL; encR_0 = encR; encS_0 = encS;

    //get robot heading from inertial sensor and convert it from degrees to radians 
    double theta_1 = inertialSensor.rotation(deg) * M_PI / 180;
    //calculate change in heading angle (in radians)
    double delta_theta = theta_1 - theta_0;

    //change in local position
    double delta_d_l_x = 0, delta_d_l_y = 0;
    //if delta theta is 0, set change in local position to delta s and delta r; this avoids a divide by zero error
    if(delta_theta == 0){
      delta_d_l_x = delta_S;
      delta_d_l_y = delta_R;
    }
    else{ //otherwise set it to this:
      delta_d_l_x = 2 * std::sin(delta_theta / 2) * (delta_S / delta_theta + s_S);
      delta_d_l_y = 2 * std::sin(delta_theta / 2) * (delta_R / delta_theta + s_R);
    }

    //calculate average orientation
    double theta_m = theta_0 + delta_theta / 2;

    //convert change in local position to polar coords so we can rotate it
    double pl_r = std::sqrt(delta_d_l_x * delta_d_l_x + delta_d_l_y * delta_d_l_y);
    double pl_theta = std::atan2(delta_d_l_y, delta_d_l_x);

    //rotate the theta of the polar coord by -theta_m
    pl_theta -= theta_m;

    //convert back to rectangular coords to find change in position
    double delta_d_x = pl_r * std::cos(pl_theta);
    double delta_d_y = pl_r * std::sin(pl_theta);

    //set global position to previous pos + change in pos
    double d_1_x = d_0_x + delta_d_x;
    double d_1_y = d_0_y + delta_d_y;

    //set previous positions as current positions for use in next loop cycle
    d_0_x = d_1_x; d_0_y = d_1_y; theta_0 = theta_1;

    //assign the global positions to the vars located outside the function so they can be used elsewhere
    pos_x = d_1_x; pos_y = d_1_y; pos_theta = theta_1;

    //sleep this thread for 1 millisecond to conserve power
    this_thread::sleep_for(1);
  }
}

//functions that can be used externally to get the positions
double getX(){return pos_y;}
double getY(){return pos_x;}
double getTheta(){return pos_theta;}

//returns angle with wrap
double getThetaWrapped(bool range){
  //-pi to pi
  if(range){
    double temp_theta = fmod(getTheta() + M_PI, 2 * M_PI);
    if(temp_theta < 0) temp_theta += 2 * M_PI;
    return temp_theta - M_PI;
  }
  //0 to 2pi
  double temp_theta = fmod(getTheta(), 2 * M_PI);
  if(temp_theta < 0) temp_theta += 2 * M_PI;
  return temp_theta;
}
}
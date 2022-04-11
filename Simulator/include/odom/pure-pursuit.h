#pragma once
#include "odom/bot.h"
#include "odom/path-point.h"
//#include "odom/simulator.h"

namespace PurePursuit_ns{
  //Pursuit constants
  extern const double
    minVel, maxVel,
    maxAccel,
    turnK;
    
  extern double angleBetweenPoints(Vector target, Vector current);
  extern double angleToPoint(Vector target, Vector current, double heading);

  class PurePursuit{
  private:
    std::vector<PathPoint> path;
    double lookDistance, robotTrack;
    bool followBackward;

    Bot bot;

    int lastClosestIndex, lastLookIndex;
    double lastLookT;
    bool isFinished;

    Vector lastPos;
    double lastVelocity;
  
  public:
    PurePursuit(Vector &pos);

    void setPath(std::vector<PathPoint> &path);
    void setLookDistance(double lookDistance);
    void setRobotTrack(double robotTrack);

    void update();

    int findClosestIndex(Vector &currentPos);

    double findIntersectT(Vector &segmentStart, Vector &segmentEnd, Vector &currentPos);

    Vector findLookahead(Vector &currentPos);

    double findLookaheadCurvature(Vector &currentPos, double heading, Vector &lookPoint);

    double computeLeftVel(double targetVel, double curvature);
    double computeRightVel(double targetVel, double curvature);
  };
}
#pragma once
#include "odom/bot.h"
#include "odom/path-point.h"
#include "odom/simulator.h"

namespace PurePursuit{
  double angleBetweenPoints(Vector target, Vector current);
  double angleToPoint(Vector target, Vector current, double heading);

  class PurePursuit{
  private:
    std::vector<PathPoint> path;
    double lookDistance, robotTrack;
    bool followBackward;

    Bot bot;

    //int? maybe double
    int lastClosestIndex, lastLookIndex;
    int lastLookT; //unknown type
    bool isFinished;

    Vector lastPos;
    double lastVelocity;
  
  public:
    PurePursuit(Vector &pos);

    void setPath(std::vector<PathPoint> &path);
    void setlookDistance(double lookDistance);
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
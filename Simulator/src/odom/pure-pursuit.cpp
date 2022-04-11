#include "odom/pure-pursuit.h"

//values to tune
const double
  PurePursuit_ns::minVel = 2, PurePursuit_ns::maxVel = 8,
  PurePursuit_ns::maxAccel = 15,
  PurePursuit_ns::turnK = 20;

double PurePursuit_ns::angleBetweenPoints(Vector target, Vector current){
  return rollAngle180(std::atan2(target.y() - current.y(), target.x() - current.x()));
}

double PurePursuit_ns::angleToPoint(Vector target, Vector current, double heading){
  return rollAngle180(angleBetweenPoints(target, current) - heading);
}

PurePursuit_ns::PurePursuit::PurePursuit(Vector &pos):
  bot(localToCanvas(pos), 0),
  lastPos(bot.getLocalPos())
{
  followBackward = false;

  lastClosestIndex = 0; lastLookIndex = 0;
  isFinished = false;

  lastVelocity = minVel;
}

void PurePursuit_ns::PurePursuit::setPath(std::vector<PathPoint> &path){
  this->path = path;
}

void PurePursuit_ns::PurePursuit::setLookDistance(double lookDistance){
  this->lookDistance = lookDistance;
}

void PurePursuit_ns::PurePursuit::setRobotTrack(double robotTrack){
  this->robotTrack = robotTrack;
}

void PurePursuit_ns::PurePursuit::update(){
  Vector currentPos = bot.getLocalPos();
  double heading = bot.getHeading();

  int closestIndex = findClosestIndex(currentPos);
  PathPoint &closestPoint = path[closestIndex];
  Vector closestPointVector = closestPoint.vector();
  bool onPath = Vector::distance(currentPos, closestPointVector) <= lookDistance;

  Vector lookPoint = findLookahead(currentPos);
  Vector finalLookPoint = ((lookPoint - currentPos).normalized() * lookDistance) + currentPos;

  Vector endPointVector = path[path.size()-1].vector();
  bool endInLookahead = 
    Vector::distance(closestPointVector, endPointVector) < lookDistance &&
    Vector::distance(currentPos, endPointVector) < lookDistance;

  double curvature =
    endInLookahead ? 0 : findLookaheadCurvature(currentPos, heading, finalLookPoint);

  double angleToEnd = std::abs(angleToPoint(endPointVector, currentPos, heading));
  bool pastEnd = followBackward ? angleToEnd < M_PI_2 : angleToEnd > M_PI_2;

  bool followBackward_l = followBackward;
  if(endInLookahead) followBackward_l = angleToEnd > M_PI_2;

  isFinished = pastEnd && endInLookahead;

  double targetVel = 0;
  if(onPath){
    targetVel = std::min(closestPoint.velocity, turnK / std::abs(curvature));
  }
  else{
    targetVel = std::min(maxVel, turnK / std::abs(curvature));
  }

  //minimum velocity
  targetVel = std::max(targetVel, minVel);
  //get distance from last loop
  double distDt = Vector::distance(lastPos, currentPos);
  //get maximum allowable change in velocity
  double maxVelocity = std::sqrt(std::pow(lastVelocity, 2) + (2 * maxAccel * distDt));
  //limit the velocity
  if(targetVel > maxVelocity) targetVel = maxVelocity;

  lastPos = currentPos;
  lastVelocity = targetVel;

  double leftVel = computeLeftVel(targetVel, curvature);
  double rightVel = computeRightVel(targetVel, curvature);

  if(!isFinished){
    if(!followBackward_l){
      bot.tank(leftVel / maxVel, rightVel / maxVel);
    }
    else{
      curvature *= -1;
      bot.tank(-leftVel / maxVel, -rightVel / maxVel);
    }
  }
  else{
    bot.tank(0, 0);
  }

  bot.update();

  //draw functions not implemented yet; uncomment when they are
  Vector botCanvPos = bot.getCanvasPos();
  Vector botLocPos = bot.getLocalPos();

  drawLookahead(botCanvPos, lookPoint, lookDistance, finalLookPoint);
  drawClosest(botCanvPos, closestPointVector);
  drawCurvature(curvature, botLocPos, finalLookPoint);
  
  bot.draw();
};

int PurePursuit_ns::PurePursuit::findClosestIndex(Vector &currentPos){
  double closestDist = 1/0.;
  int closestIndex = lastClosestIndex;

  int lastI = lastLookIndex + 2;

  //if end of path is within lookahead, set closest point to end point
  Vector endPointVector = path[path.size()-1].vector();
  if(Vector::distance(currentPos, endPointVector) <= lookDistance)
    lastI = path.size();

  for(int i = closestIndex; i < lastI; i++){
    if(i >= path.size()) break;
    Vector pathIVector = path[i].vector();
    double distance = Vector::distance(currentPos, pathIVector);
    if(distance < closestDist){
      closestDist = distance;
      closestIndex = i;
    }
  }

  lastClosestIndex = closestIndex;
  return closestIndex;
}

double PurePursuit_ns::PurePursuit::findIntersectT(Vector &segmentStart, Vector &segmentEnd, Vector &currentPos){
  Vector d = segmentEnd - segmentStart;
  Vector f = segmentStart - currentPos;

  double a = d * d;
  double b = 2 * (f * d);
  double c = (f * f) - std::pow(lookDistance, 2);
  double discriminant = std::pow(b, 2) - 4 * a * c;

  if(discriminant >= 0){
    discriminant = std::sqrt(discriminant);
    double t1 = (-b - discriminant) / (2 * a);
    double t2 = (-b + discriminant) / (2 * a);

    //prioritize further down path
    if(t2 >= 0 && t2 <= 1)
      return t2;
    else if(t1 >= 0 && t1 <= 1)
      return t1;
  }

  //no intersection found; returns nan
  return 0/0.;
}

PurePursuit_ns::Vector PurePursuit_ns::PurePursuit::findLookahead(Vector &currentPos){
  //used for optimized search
  int lastIntersect = 0;

  Vector endPointVector = path[path.size()-1].vector();
  if(lastLookIndex == 0 && Vector::distance(currentPos, endPointVector) < lookDistance){
    lastLookIndex = path.size() - 2;
    lastLookT = 1;
  }

  //loop through every segment looking for intersection
  for(int i = std::max(lastLookIndex, lastClosestIndex); i < path.size() - 1; i++){
    Vector segmentStart = path[i].vector();
    Vector segmentEnd = path[i+1].vector();

    double intersectionT = findIntersectT(segmentStart, segmentEnd, currentPos);
    if(!std::isnan(intersectionT)){
      //if the seg is further along or the fractional index is greater, then this is the correct point
      if(i > lastLookIndex || intersectionT > lastLookT){
        lastLookIndex = i;
        lastLookT = intersectionT;
        //if this is the second intersection, then it's done
        if(lastIntersect > 0) break;
        //record the index of the first intersection
        lastIntersect = i;
      }
    }

    //Optimization: if an intersection is found and loop is checking distances further than lookahead, then it's done
    Vector pathIVector = path[i].vector();
    Vector lastIntersectVector = path[lastIntersect].vector();
    if(lastIntersect > 0 && Vector::distance(pathIVector, lastIntersectVector) >= lookDistance * 2)
      break;
  }

  Vector segmentStart = path[lastLookIndex].vector();
  Vector segmentEnd = path[lastLookIndex+1].vector();

  //lookpoint? seems unused so I omitted it

  return ((segmentEnd - segmentStart) * lastLookT) + segmentStart;
}

double PurePursuit_ns::PurePursuit::findLookaheadCurvature(Vector &currentPos, double heading, Vector &lookPoint){
  int side = sgn(std::sin(heading) * (lookPoint.x() - currentPos.x()) -
    std::cos(heading) * (lookPoint.y() - currentPos.y()));
  double a = -std::tan(heading);
  double c = std::tan(heading) * currentPos.x() - currentPos.y();
  double x = std::abs(a * lookPoint.x() + lookPoint.y() + c) / std::hypot(a, 1);
  return side * ((2 * x) / std::pow(Vector::distance(currentPos, lookPoint), 2));
}

double PurePursuit_ns::PurePursuit::computeLeftVel(double targetVel, double curvature){
  return targetVel * (2 + robotTrack * curvature) / 2;
}

double PurePursuit_ns::PurePursuit::computeRightVel(double targetVel, double curvature){
  return targetVel * (2 - robotTrack * curvature) / 2;
}
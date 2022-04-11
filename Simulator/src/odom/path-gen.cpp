#include "odom/path-gen.h"

double PurePursuit_ns::distPathPoint(PathPoint &a, PathPoint &b){
  Vector c = a.vector(); Vector d = b.vector();
  return Vector::distance(c, d);
}

std::vector<PurePursuit_ns::PathPoint> PurePursuit_ns::insertPoints(std::vector<Vector> &points, double resolution){
  std::vector<PathPoint> path;
  int numPoints = points.size();

  for(int i = 0; i < numPoints - 1; i++){
    Vector &start = points[i];
    Vector &end = points[i+1];

    Vector diff = end - start;
    int numInsert = std::ceil(diff.magnitude() / resolution);
    Vector step = diff * (1 / numInsert);

    for(int j = 0; j < numInsert; j++){
      double xNew = start.x() + step.x() * j;
      double yNew = start.y() + step.y() * j;
      PathPoint newPoint(xNew, yNew);
      newPoint.setSegmentIndex(i);
      path.push_back(newPoint);
    }
  }

  if(numPoints > 0)
    path.push_back(PathPoint(points[numPoints-1].x(), points[numPoints-1].y()));

  return path;
}

std::vector<PurePursuit_ns::PathPoint> PurePursuit_ns::smoothen(std::vector<PathPoint> &input, double dataWeight, double tolerance){
  std::vector<PathPoint> path(input);
  double smoothWeight = 1 - dataWeight;
  double change = tolerance;

  while(change >= tolerance){
    change = 0;
    for(int i = 1; i < input.size() - 1; i++){
      for(int j = 0; j < 2; j++){
        double aux = path[i].loc[j];
        double dataFac = dataWeight * (input[i].loc[j] - path[i].loc[j]);
        double smoothFac = smoothWeight * (path[i-1].loc[j] + path[i+1].loc[j] - (2 * path[i].loc[j]));
        path[i].loc[j] += (dataFac + smoothFac);
        change = std::abs(aux - path[i].loc[j]);
      }
    }
  }

  return path;
}

double PurePursuit_ns::computeSingleCurvature(PathPoint &prevPoint, PathPoint &point, PathPoint &nextPoint){
  double dist1 = distPathPoint(point, prevPoint);
  double dist2 = distPathPoint(point, nextPoint);
  double dist3 = distPathPoint(nextPoint, prevPoint);

  double productOfSides = dist1 * dist2 * dist3;
  double semiPerimeter = (dist1 + dist2 + dist3) / 2;
  double triangleArea = std::sqrt(semiPerimeter * (semiPerimeter - dist1) * (semiPerimeter - dist2) * (semiPerimeter - dist3));

  double r = (productOfSides) / (4 * triangleArea);
  double curvature = std::isnan(1/r) ? 0 : 1/r;

  return curvature;
}

std::vector<PurePursuit_ns::PathPoint> PurePursuit_ns::computeCurvatures(std::vector<PathPoint> &path){
  path[0].setCurvature(0);
  for(int i = 1; i < path.size() - 1; i++){
    double curvature = computeSingleCurvature(path[i-1], path[i], path[i+1]);
    path[i].setCurvature(curvature);
  }
  path[path.size()-1].setCurvature(0);
  return path;
}

std::vector<PurePursuit_ns::PathPoint> PurePursuit_ns::computeVelocity(std::vector<PathPoint> &path, double maxVel, double maxRate, double k){
  path[path.size()-1].setVelocity(0);
  for(int i = path.size() - 1; i > 0; i--){
    PathPoint &start = path[i];
    PathPoint &end = path[i-1];
    double wantedVel = std::min(maxVel, (k / path[i].curvature));
    double distance = distPathPoint(start, end);
    double newVel = std::min(wantedVel, std::sqrt(std::pow(start.velocity, 2) + (2 * maxRate * distance)));
    path[i-1].setVelocity(newVel);
  }
  return path;
}
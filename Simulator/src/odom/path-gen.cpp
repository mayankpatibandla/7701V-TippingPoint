#include "odom/path-gen.h"

namespace PurePursuit{
  double distPathPoint(PathPoint &a, PathPoint &b){
    Vector c = a.vector(); Vector d = b.vector();
    return Vector::distance(c, d);
  }

  std::vector<PathPoint> insertPoints(std::vector<Vector> &points, double resolution){
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

  std::vector<PathPoint> smoothen(std::vector<PathPoint> &input, double dataWeight, double tolerance){
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

  double computeSingleCurvature(PathPoint &prevPoint, PathPoint &point, PathPoint &nextPoint){
    double dist1 = distPathPoint(point, prevPoint);
    double dist2 = distPathPoint(point, nextPoint);
    double dist3 = 
  }
}
#include "odom/path-point.h"

namespace PurePursuit{
  extern double distPathPoint(PathPoint &a, PathPoint &b);

  extern std::vector<PathPoint> insertPoints(std::vector<Vector> &points, double resolution);
  extern std::vector<PathPoint> smoothen(std::vector<PathPoint> &input, double dataWeight, double tolerance);

  extern double computeSingleCurvature(PathPoint &prevPoint, PathPoint &point, PathPoint &nextPoint);
  extern std::vector<PathPoint> computeCurvatures(std::vector<PathPoint> &path);

  extern std::vector<PathPoint> computeVelocity(std::vector<PathPoint> &path, double maxVel, double maxRate, double k);
}
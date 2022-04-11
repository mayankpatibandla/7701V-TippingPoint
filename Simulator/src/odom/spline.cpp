#include "odom/spline.h"

namespace PurePursuit_ns{
  QuinticPolynomial::QuinticPolynomial(double xstart, double vstart, double xend, double vend){
    double u = xend - xstart - vstart;
    double v = vend - xstart;

    //idk what these are
    double a3 = 10 * u - 4 * v;
    double a4 = -15 * u + 7 * v;
    double a5 = 6 * u - 3 * v;

    coeffs[0] = xstart;
    coeffs[1] = vstart;
    coeffs[2] = 0;
    coeffs[3] = a3;
    coeffs[4] = a4;
    coeffs[5] = a5;
  }

  double QuinticPolynomial::calcPoint(double t){
    double xt = 0;
    for(int power = 0; power < 6; power++){
      xt += coeffs[power] * std::pow(t, power);
    }

    return xt;
  }

  QuinticSegmentPlanner::QuinticSegmentPlanner(WayPoint &s, WayPoint &g, int steps, bool end){
    double vxs = s.vel * std::sin(s.theta);
    double vys = s.vel * std::cos(s.theta);
    double vxg = g.vel * std::sin(g.theta);
    double vyg = g.vel * std::cos(g.theta);

    QuinticPolynomial xqp(s.x, vxs, g.x, vxg);
    QuinticPolynomial yqp(s.y, vys, g.y, vyg);

    for(int i = 0; i <= (end ? steps : steps - 1); i++){
      rx.push_back(xqp.calcPoint(i / steps));
      ry.push_back(yqp.calcPoint(i / steps));
    }
  }

  std::vector<PathPoint> QuinticSegmentPlanner::getPath(){
    std::vector<PathPoint> path;

    for(int i = 0; i < rx.size(); i++){
      PathPoint p(rx[i], ry[i]);
      path.push_back(p);
    }

    return path;
  }

  void QuinticPathPlanner::generateVelocities(){
    for(int i = 0; i < points.size() - 1; i++){
      WayPoint &p1 = points[i]; Vector p1Vec = p1.vector();
      WayPoint &p2 = points[i+1]; Vector p2Vec = p2.vector();

      double vel = slopeScalar * Vector::distance(p1Vec, p2Vec);
      p1.vel = vel;

      if(i == points.size() - 2){
        p2.vel = vel;
      }
    }
  }

  void QuinticPathPlanner::generatePath(){
    if(points.size() == 2){
      WayPoint &p1 = points[0];
      WayPoint &p2 = points[1];
      QuinticSegmentPlanner segment(p1, p2, steps, true);
      path = segment.getPath();
    }
    else{
      path.clear();
      for(int i = 0; i < points.size() - 1; i++){
        WayPoint &p1 = points[i];
        WayPoint &p2 = points[i+1];
        QuinticSegmentPlanner segment(p1, p2, steps, i >= points.size() - 2);
        std::vector<PathPoint> segmentPath = segment.getPath();

        for(int j = 0; j < segmentPath.size(); j++){
          segmentPath[j].setSegmentIndex(i);
        }
        path.insert(path.end(), segmentPath.begin(), segmentPath.end());
      }
    }
  }

  QuinticPathPlanner::QuinticPathPlanner(std::vector<WayPoint> &points, int steps, double slopeScalar):
    points(points), steps(steps), slopeScalar(slopeScalar)
  {
    generateVelocities();
    generatePath();
  }

  std::vector<PathPoint> QuinticPathPlanner::getPath(){
    return path;
  }
}
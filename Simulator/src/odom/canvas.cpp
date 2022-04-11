#include "odom/canvas.h"

double PurePursuit_ns::slider1Value = 30, PurePursuit_ns::slider2Value = 1, PurePursuit_ns::slider3Value = 0.5;
//canvas constants and globals
const int PurePursuit_ns::canvasWidth = 480, PurePursuit_ns::canvasHeight = 240;

const double PurePursuit_ns::canvasScale = 240 / 144;
const int PurePursuit_ns::marginOffset = 0;

const int PurePursuit_ns::wayPointWidth = 3;
const int PurePursuit_ns::pointWidth = 2;

PurePursuit_ns::sliders_ PurePursuit_ns::sliders;

//utility functions
void PurePursuit_ns::maintainCanvas(){
  sliders.resolution = slider1Value / 1;
  sliders.scalar = slider2Value / 500;
  sliders.lookahead = slider3Value / 1000;

  //maybe need to add rect
}

//turns percent to rgb from yellow to red
//perc: value between min and max
//returns vex::color
vex::color PurePursuit_ns::percToColor(double perc, double min, double max){
  double base = max - min;

  if(base == 0){
    perc = 0;
  }
  else{
    perc = (perc - min) / base * 100;
  }

  int r = 0, g = 0, b = 0;

  if(perc < 50){
    r = 255;
    g = std::round(5.1 * perc);
  }
  else{
    g = 255;
    r = std::round(510 - 5.1 * perc);
  }

  return vex::color(r, g, b);
}

//turns percent into rgb range rainbow
//perc: value between min and max
//returns vex::color
vex::color PurePursuit_ns::percToMultColor(double perc, double min, double max){
  double base = max - min;
  if(base == 0){
    perc = 0;
  }
  else{
    perc = (perc - min) / base * 100;
  }

  int r = 0, g = 0, b = 0;

  if(perc >= 0 && perc <= 20){
    r = 255;
    g = std::round(12.75 * perc);
    b = 0;
  }
  else if(perc > 20 && perc <= 40){
    r = std::round(-12.75 * perc + 510);
    g = 255;
    b = 0;
  }
  else if(perc > 40 && perc <= 60){
    r = 0;
    g = 255;
    b = std::round(12.75 * perc) - 510;
  }
  else if(perc > 60 && perc <= 80){
    r = 0;
    g = std::round(-12.75 * perc + 1020);
    b = 255;
  }
  else{
    r = std::round(12.75 * perc - 1020);
    g = 0;
    b = 255;
  }

  return vex::color(r, g, b);
}

//canvas functions

//scales sim coords to canvas coords
PurePursuit_ns::Vector PurePursuit_ns::localToCanvas(Vector &point){
  return Vector(point.x() * canvasScale, point.y() * canvasScale);
}

//scales canvas coords to sim coords
PurePursuit_ns::Vector PurePursuit_ns::canvasToLocal(Vector &point){
  return Vector(point.x() / canvasScale, (canvasHeight - point.y()) / canvasScale);
  //return Vector(point.x() / canvasScale, point.y() / canvasScale);
}

//draws a line from origin to point then draws a point
void PurePursuit_ns::drawLineToPoint(Vector &origin, Vector &point, int width){
  Brain.Screen.drawCircle(point.x(), point.y(), width);
  Brain.Screen.drawLine(origin.x(), origin.y(), point.x(), point.y());
}

//draws array of points
void PurePursuit_ns::drawWaypoints(std::vector<WayPoint> &points){
  Brain.Screen.setFillColor("#FF7F00");
  for(int i = 0; i < points.size(); i++){
    Vector iVec = points[i].vector();
    Vector cPoint = localToCanvas(iVec);
    Brain.Screen.drawCircle(cPoint.x(), canvasHeight - cPoint.y(), wayPointWidth);
  }
}

void PurePursuit_ns::drawPath(std::vector<PathPoint> &path, double min, double max){
  //curvature color calculations
  Brain.Screen.setPenWidth(2);
  for(int i = 0; i < path.size(); i++){
    double canvasX = path[i].x() * canvasScale;
    double canvasY = path[i].y() * canvasScale;
    vex::color style = percToMultColor(path[i].velocity, min, max);
    Brain.Screen.setPenColor(style);
    Brain.Screen.setFillColor(style);
    //draw points
    Brain.Screen.drawCircle(canvasX, canvasHeight - canvasY, pointWidth);
    //draw lines
    if(i < path.size() - 1){
      double lastX = path[i+1].x() * canvasScale;
      double lastY = path[i+1].y() * canvasScale;
      Brain.Screen.drawLine(
        canvasX, canvasHeight - canvasY,
        lastX, canvasHeight - lastY
      );
    }
  }
}

void PurePursuit_ns::drawLookahead(Vector &currPos, Vector &lookahead, double lookaheadDist, Vector &projectedLookahead){
  Brain.Screen.setPenColor("#FF0087");
  Brain.Screen.setFillColor("#FF0087");
  Brain.Screen.setPenWidth(3);
  Vector lookaheadVec = localToCanvas(lookahead);
  drawLineToPoint(currPos, lookaheadVec, 5);
  Brain.Screen.setPenColor("#000000");
  Brain.Screen.setFillColor("#000000");
  Brain.Screen.setPenWidth(1);
  Vector projLookVec = localToCanvas(projectedLookahead);
  drawLineToPoint(currPos, projLookVec, 4);
  Brain.Screen.setPenWidth(1);
  Brain.Screen.setFillColor(transparent);
  Brain.Screen.drawCircle(currPos.x(), currPos.y(), lookaheadDist * canvasScale);
}

void PurePursuit_ns::drawClosest(Vector &currPos, Vector &closest){
  Brain.Screen.setPenColor("#2B00BA");
  Brain.Screen.setFillColor("#2B00BA");
  Vector closVec = localToCanvas(closest);
  drawLineToPoint(currPos, closVec, 3);
}

void PurePursuit_ns::drawCurvature(double curvature, Vector &p1, Vector &p2){
  Brain.Screen.setPenColor("#000000");
  Brain.Screen.setFillColor(transparent);
  Brain.Screen.setPenWidth(1);

  if(std::abs(curvature) < 0.005)
    curvature = 0.005;

  double radius = std::abs(1 / curvature);

  double x3 = (p1.x() + p2.x()) / 2;
  double y3 = (p1.y() + p2.y()) / 2;
  double q = std::hypot(p1.x() - p2.x(), p1.y() - p2.y());

  double b = std::sqrt(std::pow(radius, 2) - std::pow(q / 2, 2));
  double x = x3 - b * (p1.y() - p2.y()) / q * sgn(curvature);
  double y = y3 - b * (p2.x() - p1.x()) / q * sgn(curvature);

  Vector localPoint(x, y);
  Vector canvasPoint = localToCanvas(localPoint);

  Brain.Screen.drawCircle(
    canvasPoint.x(), canvasPoint.y(),
    std::abs(1 / curvature * canvasScale)
  );
}

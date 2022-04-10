#pragma once
#include "odom/path-point.h"
#include "odom/general.h"

namespace PurePursuit{
  extern double slider1Value, slider2Value, slider3Value;

  //canvas constants and globals
  extern const int canvasWidth, canvasHeight;

  extern const double canvasScale;
  extern const int marginOffset;

  extern const int wayPointWidth, pointWidth;

  struct sliders_{
    double resolution, scalar, lookahead;
  };

  //utility functions
  extern void maintainCanvas();

  //turns percent to rgb from yellow to red
  //perc: value between min and max
  //returns vex::color
  extern vex::color percToColor(double perc, double min, double max);

  //turns percent into rgb range rainbow
  //perc: value between min and max
  //returns vex::color
  extern vex::color percToMultColor(double perc, double min, double max);

  //canvas functions

  //scales sim coords to canvas coords
  extern Vector localToCanvas(Vector &point);

  //scales canvas coords to sim coords
  extern Vector canvasToLocal(Vector &point);

  //draws line from origin to point then draws a point
  extern void drawLineToPoint(Vector &origin, Vector &point, int width);

  //draws array of points
  extern void drawWaypoints(std::vector<WayPoint> &points);

  extern void drawPath(std::vector<PathPoint> &path, double min, double max);

  extern void drawLookahead(Vector &currPos, Vector &lookahead, double lookaheadDist, Vector &projectedLookahead);

  extern void drawClosest(Vector &currPos, Vector &closest);

  extern void drawCurvature(double curvature, Vector &p1, Vector &p2);
}
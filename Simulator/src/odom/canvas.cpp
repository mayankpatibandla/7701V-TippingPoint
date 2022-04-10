#include "odom/canvas.h"

namespace PurePursuit{
  //canvas constants and globals
  const double canvasScale = 1;
  const int marginOffset = 0;

  const int wayPointWidth = 2;
  const int pointWidth = 1;

  sliders_ sliders{0, 0, 0};

  //utility functions
  void maintainCanvas(){
    sliders.resolution = slider1Value / 1;
    sliders.scalar = slider2Value / 500;
    sliders.lookahead = slider3Value / 1000;

    //maybe need to add rect
  }

  //turns percent to rgb from yellow to red
  //perc: value between min and max
  //returns vex::color
  vex::color percToColor(double perc, double min, double max){
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
  vex::color percToMultColor(double perc, double min, double max){
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
  Vector localToCanvas(Vector point){
    return Vector(point.x() * canvasScale, point.y() * canvasScale);
  }

  //scales canvas coords to sim coords
  Vector canvasToLocal(Vector point){
    return Vector(point.x() / canvasScale, (canvasHeight - point.y()) / canvasScale);
  }

  double fullMin = 1/0.;
  double fullMax = 0;

  //TODO: need to add draw functions here
}
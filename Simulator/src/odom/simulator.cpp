#include "odom/simulator.h"

std::vector<PurePursuit_ns::WayPoint> PurePursuit_ns::points;
std::vector<PurePursuit_ns::PurePursuit> PurePursuit_ns::bots;
std::vector<PurePursuit_ns::PathPoint> PurePursuit_ns::path;

void PurePursuit_ns::main(){
  maintainCanvas();

  points.push_back(WayPoint(20, 200, M_PI_2));
  points.push_back(WayPoint(55, 80, M_PI_2));
  points.push_back(WayPoint(100, 130, M_PI));

  Vector startPos(100, 100);

  bots.push_back(PurePursuit(startPos));

  animate();
}

void PurePursuit_ns::animate(){
  maintainCanvas();

  std::vector<WayPoint> ipoints = calculateAngles(points);
  QuinticPathPlanner test(ipoints, sliders.resolution, sliders.scalar);
  path = test.getPath();

  //Pure Pursuit Algorithm

  path = computeCurvatures(path);
  path = computeVelocity(path, maxVel, maxAccel, turnK);

  for(int i = 0; i < bots.size(); i++){
    bots[i].setPath(path);
    bots[i].setLookDistance(sliders.lookahead);
    bots[i].setRobotTrack(1 / 12.8);

    bots[i].update();
  }

  //Canvas Drawing
  drawWaypoints(points);
  drawPath(path, minVel, maxVel);
  Brain.Screen.render();

  this_thread::sleep_for(250);

  //update loop?
  while(true){
    Brain.Screen.clearScreen();
    Brain.Screen.drawRectangle(0, 0, 480, 240, "#FFFFFF");

    for(int i = 0; i < bots.size(); i++)
      bots[i].update();

    drawWaypoints(points);
    drawPath(path, minVel, maxVel);
    Brain.Screen.render();

    this_thread::sleep_for(50);
  }
}
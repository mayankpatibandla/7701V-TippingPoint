#include "vex.h"
#include "odom.h"
#include <vector>
#include <iostream>

namespace PurePursuit{
  class Vector{
  public:
    double x, y;
    
    Vector(double x, double y):
      x(x), y(y)
    {}

    double magnitude(){
      return std::hypot(x, y);
    }

    Vector normalized(){
      return Vector(x / magnitude(), y / magnitude());
    }

    Vector multiply(double s){
      return Vector(x*s, y*s);
    }

    double dot(Vector v){
      return x*v.x + y*v.y;
    }
  };

  class Point{
  public:
    double x, y;

    Point(double x, double y):
      x(x), y(y)
    {}

    Vector subtract(Point p){
      return Vector(x - p.x, y - p.y);
    }

    Point add(Vector v){
      return Point(x + v.x, y + v.y);
    }

    double distance(Point p){
      return std::hypot(p.x-x, p.y-y);
    }

    bool equals(Point p){
      return x == p.x && y == p.y;
    }
  };

  class Circle{
  public:
    Point center;
    double radius;

    Circle(Point center, double radius):
      center(center), radius(radius)
    {}

    //e = start point; l = end point
    double intersect(Point& e, Point& l){
      Vector d = l.subtract(e);
      Vector f = e.subtract(center);

      double a = d.dot(d);
      double b = 2 * f.dot(d);
      double c = f.dot(f) - radius*radius;

      double discriminant = b*b - 4*a*c;

      if(discriminant < 0){
        //no intersection
        return -1;
      }
      else{
        discriminant = std::sqrt(discriminant);
        //swapped + and -
        double t1 = (-b + discriminant) / (2*a);
        double t2 = (-b - discriminant) / (2*a);

        if(t1 >= 0 && t1 <= 1){
          //return t1 intersection
          return t1;
        }
        else if(t2 >= 0 && t2 <= 1){
          //return t2 intersection
          return t2;
        }

        //else no intersection
        return -1;
      }
    }
  };

  class Path{
  public:
    std::vector<Point> points;
    std::vector<double> velocities;
    double k, maxVelocity, maxAcceleration;

    Path(std::vector<Point>& points):
      points(points)
    {
      //init velocities with size points and fill with 0
    }

    double distanceAtPoint(int i){
      if(i <= 0){
        return 0;
      }
      else{
        return distanceAtPoint(i-1) + points[i].distance(points[i-1]);
      }
    }

    double curvatureAtPoint(int i){
      if(i <= 0 || i >= points.size()-1) return 0;

      if(points[i-1].x == points[i].x) points[i-1].x += 0.0001; //avoids divide by 0

      double k1 = 0.5 * (points[i-1].x*points[i-1].x + points[i-1].y*points[i-1].y - points[i].x*points[i].x - points[i].y*points[i].y) /
        (points[i-1].x - points[i].x);
      double k2 = (points[i-1].y - points[i].y) / (points[i-1].x - points[i].x);

      double b = 0.5 * (points[i].x*points[i].x - 2*points[i].x*k1 + points[i].y*points[i].y - points[i+1].x*points[i+1].x + 2*points[i+1].x*k1 - points[i+1].y*points[i+1].y) /
        (points[i+1].x*k2 - points[i+1].y + points[i].y - points[i].x*k2);
      double a = k1 - k2*b;

      double r = std::hypot(points[i-1].x - a, points[i-1].y - b);

      return 1/r;
    }

    double maxVelocityAtPoint(int i){
      return std::min(maxVelocity, k / curvatureAtPoint(i));
    }

    void generateVelocities(){
      velocities.reserve(points.size());
      for(int i = 0; i < points.size(); i++){
        velocities[i] = maxVelocityAtPoint(i);
      }

      for(int i = points.size()-2; i >= 0; i--){
        double vf = std::sqrt(velocities[i+1]*velocities[i+1] + 2*maxAcceleration*points[i+1].distance(points[i]));
        //std::cout << "vf: " << vf << "\t\t\t\t" << "vi[" << i << "]: " << velocities[i] << "\t\t\t\t";
        velocities[i] = std::min(velocities[i], vf);
        //std::cout << "vTarget[" << i << "]: " << velocities[i] << std::endl;
      }
    }
  };

  class Robot{
  public:
    Circle position;
    double theta;

    Robot(Circle position, double theta):
      position(position), theta(theta)
    {}
  };

  class Draw{
  public:
    static void drawPath(Path& path){
      //lines
      Brain.Screen.setPenWidth(3);
      Brain.Screen.setPenColor(green);
      Brain.Screen.setFillColor(green);
      for(int i = 1; i < path.points.size(); i++){
        Brain.Screen.drawLine(path.points[i-1].x, path.points[i-1].y, path.points[i].x, path.points[i].y);
      }

      //points
      Brain.Screen.setPenWidth(1);
      Brain.Screen.setPenColor(orange);
      Brain.Screen.setFillColor(orange);
      for(int i = 0; i < path.points.size(); i++){
        Brain.Screen.drawCircle(path.points[i].x, path.points[i].y, 3);
      }
    }

    static void drawRobot(Robot& robot){
      Brain.Screen.setPenWidth(2);

      //heading line
      Brain.Screen.setPenColor(yellow);
      Brain.Screen.setFillColor(yellow);
      Brain.Screen.drawLine(robot.position.center.x, robot.position.center.y,
        robot.position.center.x + robot.position.radius * std::cos(robot.theta),
        robot.position.center.y + robot.position.radius * std::sin(robot.theta)
      );

      //lookahead circle
      Brain.Screen.setPenColor(blue);
      Brain.Screen.setFillColor(transparent);
      Brain.Screen.drawCircle(robot.position.center.x, robot.position.center.y, robot.position.radius);

      //center dot
      Brain.Screen.setPenColor(purple);
      Brain.Screen.setFillColor(purple);
      Brain.Screen.drawCircle(robot.position.center.x, robot.position.center.y, 3);
    }

    static void drawArc(Point& center, double r, bool primary){
      Brain.Screen.setPenWidth(2);

      if(primary) Brain.Screen.setPenColor(cyan);
      else Brain.Screen.setPenColor(color(255, 192, 203));

      //outer circle
      Brain.Screen.setFillColor(transparent);
      Brain.Screen.drawCircle(center.x, center.y, r);

      if(primary){
        Brain.Screen.setPenColor(color(255, 192, 203));
        Brain.Screen.setFillColor(color(255, 192, 203));
      }
      else{
        Brain.Screen.setPenColor(cyan);
        Brain.Screen.setFillColor(cyan);
      }

      //center dot
      Brain.Screen.drawCircle(center.x, center.y, 3);
    }
  };

  class PathGenerator{
  public:
    //adds evenly spaced points in the path
    static Path injectPoints(Path& path, double spacing){
      std::vector<Point> emptyPtVector = {};
      Path newPath(emptyPtVector);

      for(int i = 1; i < path.points.size(); i++){
        Vector v = path.points[i].subtract(path.points[i-1]);
        int maxPoints = std::ceil(v.magnitude() / spacing);

        v = v.normalized().multiply(spacing);

        for(int j = 0; j < maxPoints; j++){
          newPath.points.push_back(path.points[i-1].add(v.multiply(j)));
        }
      }
      newPath.points.push_back(path.points.back());

      return newPath;
    }

    //smooths the path and curves it
    static Path smoothPath(Path& path, double weightData, double weightSmooth, double tolerance){
      Path newPath(path.points);

      double change = tolerance;
      while(change >= tolerance){
        change = 0;
        for(int i = 1; i < path.points.size()-1; i++){
          double aux = newPath.points[i].x;

          newPath.points[i].x += weightData * (path.points[i].x - newPath.points[i].x) +
            weightSmooth * (newPath.points[i-1].x + newPath.points[i+1].x - (2 * newPath.points[i].x));

          change += std::abs(aux - newPath.points[i].x);

          aux = newPath.points[i].y;

          newPath.points[i].y += weightData * (path.points[i].y - newPath.points[i].y) +
            weightSmooth * (newPath.points[i-1].y + newPath.points[i+1].y - (2 * newPath.points[i].y));

          change += std::abs(aux - newPath.points[i].y);
        }
      }

      return newPath;
    }

    static int signum(double n){
      if(n > 0) return 1;
      else if(n < 0) return -1;
      else return 0;
    }

    static Point circleCenter(Point& a, Point& b, double r, int sign){
      Point center(a.x/2 + b.x/2, a.y/2 + b.y/2);
      double halfDistance = center.distance(a);

      double root = std::hypot(r, halfDistance) / a.distance(b);

      Point ans1(center.x + root*(a.y-b.y), center.y + root*(b.x-a.x));
      Point ans2(center.x - root*(a.y-b.y), center.y - root*(b.x-a.x));

      //debug print to controller; very laggy; do not use
      /*
      Controller.Screen.clearLine(3);
      if(a.equals(b)){
        if(r == 0) Controller.Screen.print("One Coincident");
        else Controller.Screen.print("Infinite");
      }
      else if(halfDistance > r) Controller.Screen.print("None");
      else if(halfDistance - r == 0) Controller.Screen.print("One Diameter");
      else Controller.Screen.print("Two");
      */

      if(sign == signum(ans1.x)) return ans1;
      else return ans2;
    }

    static double signedCurvature(Robot& robot, Point& lookAhead, double lookAheadDistance){
      double a = -std::tan(robot.theta);
      double b = 1;
      double c = std::tan(robot.theta) * robot.position.center.x - robot.position.center.y;

      double x = std::abs(a*lookAhead.x + b*lookAhead.y + c) * std::hypot(a, b);

      double curvature = (2*x) / (lookAheadDistance*lookAheadDistance);

      double cross = std::sin(robot.theta) * (lookAhead.x - robot.position.center.x) - std::cos(robot.theta) * (lookAhead.y - robot.position.center.y);
      int sign = signum(cross);

      //draw the circles and center point
      double r = 1/curvature;
      Point center(circleCenter(robot.position.center, lookAhead, r, sign));
      //Draw::drawArc(center, r, true);
      center = circleCenter(robot.position.center, lookAhead, r, -sign);
      //Draw::drawArc(center, r, false);

      return sign * curvature;
    }
  };

  class RateLimiter{
  public:
    uint32_t timeStart, timeEnd;
    double maxRate;
    double lastOutput;

    RateLimiter(double maxRate):
      maxRate(maxRate)
    {
      timeStart = 0;
    }

    double constrain(double x, double a, double b){
      return x < a ? a : x > b ? b : x;
    }

    double limit(double x){
      if(timeStart == 0) timeStart = Brain.Timer.system();
      timeEnd = Brain.Timer.system();
      double deltaTime = timeEnd - timeStart;
      timeStart = Brain.Timer.system();
      double maxChange = deltaTime * maxRate;
      double output = x;
      output += constrain(x, -maxChange, maxChange);
      lastOutput = output;
      return output;
    }
  };


  class Motion{
  public:
    //plus and minus might need to be swapped; original from doc: left+, right-;
    static double leftVelocity(double targetVelocity, double curvature, double width){
      return targetVelocity * (2 - curvature*width) / 2;
    }
    static double rightVelocity(double targetVelocity, double curvature, double width){
      return targetVelocity * (2 + curvature*width) / 2;
    }
  };

  double leftVelocityOutput;
  double rightVelocityOutput;

  std::vector<Point> empty = {};
  Path currentPath(empty);

  void purePursuit(){
    //tuning parameters and constants
    double spacing = 2;
    double weightSmooth = 0.8, weightData = 1-weightSmooth,  tolerance = 0.001;
    double lookAheadDistance = 40;
    double trackWidth = 13.5;
    double k = 2, maxVelocity = 0.5679/*(in/15ms); 37.86(in/s)*/, maxAcceleration = 2.3679/*(in/15ms); 157.86(in/s/s)*/;
    double maxRate = maxAcceleration;
    double kV = 1/maxVelocity * 35, kA = 0.00, kP = 0.0;



    //path generation

    //Path waypointPath(waypoints);

    /*Brain.Screen.clearScreen();
    Brain.Screen.render();
    Draw::drawPath(waypointPath);
    Brain.Screen.render();
    waitUntil(Controller.ButtonX.pressing());*/

    //create and draw injected path
    Path injectedPath = PathGenerator::injectPoints(currentPath, spacing);
    /*Brain.Screen.clearScreen();
    Draw::drawPath(injectedPath);
    Brain.Screen.render();

    waitUntil(!Controller.ButtonX.pressing());
    waitUntil(Controller.ButtonX.pressing());*/

    //create and draw smooth path
    Path smoothedPath = PathGenerator::smoothPath(injectedPath, weightData, weightSmooth, tolerance);
    smoothedPath.k = k; smoothedPath.maxVelocity = maxVelocity; smoothedPath.maxAcceleration = maxAcceleration;

    /*Brain.Screen.clearScreen();
    Draw::drawPath(smoothedPath);
    Brain.Screen.render();

    //intersection
    waitUntil(!Controller.ButtonX.pressing());
    waitUntil(Controller.ButtonX.pressing());*/

    Robot robot(Circle(Point(0, 0), lookAheadDistance), 0);

    RateLimiter rateLimiter(maxRate);

    smoothedPath.generateVelocities();
    Controller.Screen.print(smoothedPath.points.size());

    double previousIndex = 0;
    Point previousLookAhead = smoothedPath.points[previousIndex];
    Point lookAhead = previousLookAhead;

    int searchStart = 1;

    double prevVelLeft, prevVelRight;

    //drivable simulation
    while(true){
      //time
      uint32_t timeStart = Brain.Timer.system();

      //input
      robot.position.center.x = pt::x();
      robot.position.center.y = pt::y();

      robot.theta = pt::thetaWrapped();

      //draw path
      //Draw::drawPath(smoothedPath);

      //find intersection points
      for(int i = searchStart; i < smoothedPath.points.size(); i++){
        double t = robot.position.intersect(smoothedPath.points[i-1], smoothedPath.points[i]);

        //no intersection
        if(t == -1) continue;

        double index = t + i-1;

        Vector d = smoothedPath.points[i].subtract(smoothedPath.points[i-1]);

        if(index > previousIndex){
          //new intersection point
          previousIndex = index;
          lookAhead = smoothedPath.points[i-1].add(d.multiply(t));
          previousLookAhead = lookAhead;
          searchStart = std::floor(previousIndex);
        }
        else{
          //intersection point is not the furthest on the path
          lookAhead = previousLookAhead;
        }
      }
      int roundedIndex = std::round(previousIndex);

      Controller.Screen.clearLine(3);
      Controller.Screen.print(smoothedPath.points.size());
      if(roundedIndex == smoothedPath.points.size()-1){
        leftVelocityOutput = 0; rightVelocityOutput = 0;
        Controller.Screen.clearLine(3);
        Controller.Screen.print("DONE");
        break;
      }

      //calculate and draw signed curvature
      double signedCurvature = PathGenerator::signedCurvature(robot, lookAhead, lookAheadDistance);

      //output velocities
      double targetVelLeft = Motion::leftVelocity(rateLimiter.limit(smoothedPath.velocities[roundedIndex]), signedCurvature, trackWidth);
      double targetAccelLeft = targetVelLeft - prevVelLeft;
      double ffL = kV * targetVelLeft + kA * targetAccelLeft;
      prevVelLeft = targetVelLeft;
      double actualVelLeft = targetVelLeft; //REPLACE WITH ACUTAL MEASURED VELOCITY FROM MOTOR
      double fbL = kP * (targetVelLeft - actualVelLeft);
      double leftSideFinalVel = ffL + fbL;

      double targetVelRight = Motion::rightVelocity(rateLimiter.limit(smoothedPath.velocities[roundedIndex]), signedCurvature, trackWidth);
      double targetAccelRight = targetVelRight - prevVelRight;
      double ffR = kV * targetVelRight + kA * targetAccelRight;
      prevVelRight = targetVelRight;
      double actualVelRight = targetVelRight; //REPLACE WITH ACUTAL MEASURED VELOCITY FROM MOTOR
      double fbR = kP * (targetVelRight - actualVelRight);
      double rightSideFinalVel = ffR + fbR;

      //set outputs
      leftVelocityOutput = leftSideFinalVel;
      rightVelocityOutput = rightSideFinalVel;

      //std::cout << "LEFT: " << leftVelocityOutput << "\t\t\t\t" << "RIGHT: " << rightVelocityOutput << std::endl;

      //draw robot
      //Draw::drawRobot(robot);

      //debug info
      /*Brain.Screen.setPenColor(white);
      Brain.Screen.setFillColor(transparent);
      Brain.Screen.printAt(0, 20, "X: %lf, Y: %lf, Theta: %lf", robot.position.center.x, robot.position.center.y, robot.theta);*/
      /*Brain.Screen.printAt(0, 40, "Signed Curvature: %lf", signedCurvature);
      Brain.Screen.printAt(0, 60, "Dist, Curv at %d: %lf, %lf",
        roundedIndex, smoothedPath.distanceAtPoint(roundedIndex), smoothedPath.curvatureAtPoint(roundedIndex)
      );*/
      //Brain.Screen.printAt(0, 40, "Left Vel: %lf, Right Vel: %lf", leftSideFinalVel, rightSideFinalVel);
      

      //draw intersection point
      /*Brain.Screen.setPenWidth(2);
      Brain.Screen.setPenColor(red);
      Brain.Screen.setFillColor(red);
      Brain.Screen.drawCircle(lookAhead.x, lookAhead.y, 4);*/

      //render
      //Brain.Screen.render();
      this_thread::sleep_until(timeStart + 15);
      //Brain.Screen.clearScreen();
    }
  }

  double leftVelocity(){
    return leftVelocityOutput;
  }
  double rightVelocity(){
    return rightVelocityOutput;
  }
}

//temporary put in other files later
void odomTestAuton(){
  using namespace PurePursuit;
  std::vector<Point> waypoints = {
    Point(0, 0),
    Point(24, 0),
    Point(48, 0)
  };
  Path waypointPath = Path(waypoints);
  currentPath = waypointPath;

  thread pathThread(purePursuit);

  while(true){
    leftMotors.spin(fwd, leftVelocity(), pct);
    rightMotors.spin(fwd, rightVelocity(), pct);
  }
}
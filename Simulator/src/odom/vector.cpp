#include "vex.h"
#include "odom/vector.h"
//{}
namespace PurePursuit_ns{
  Vector::Vector(double x, double y):
    ix(x), iy(y)
  {}

  double Vector::x(){
    return ix;
  }
  double Vector::y(){
    return iy;
  }

  //Magnitude: sqrt(v.x*v.x + v.y*v.y)
  double Vector::magnitude(){
    return std::hypot(x(), y());
  }
  double Vector::magnitude(Vector &v){
    return std::hypot(v.x(), v.y());
  }

  //Normalize: v.x / mag(), v.y / mag()
  Vector Vector::normalized(){
    return Vector(x() / magnitude(), y() / magnitude());
  }
  Vector Vector::normalized(Vector &v){
    return Vector(v.x() / v.magnitude(), v.y() / v.magnitude());
  }

  //Subtract: v1.x - v2.x, v1.y - v2.y
  Vector Vector::operator - (Vector &v){
    return Vector(x() - v.x(), y() - v.y());
  }
  Vector Vector::subtract(Vector &v){
    return Vector(x() - v.x(), y() - v.y());
  }
  Vector Vector::subtract(Vector &v1, Vector &v2){
    return Vector(v1.x() - v2.x(), v1.y() - v2.y());
  }

  //Add: v1.x + v2.x, v1.y + v2.y
  Vector Vector::operator + (Vector &v){
    return Vector(x() + v.x(), y() + v.y());
  }
  Vector Vector::add(Vector &v){
    return Vector(x() + v.x(), y() + v.y());
  }
  Vector Vector::add(Vector &v1, Vector &v2){
    return Vector(v1.x() + v2.x(), v1.y() + v2.y());
  }

  //Dot Product: v1.x * v2.x + v1.y * v2.y
  double Vector::operator * (Vector &v){
    return x() * v.x() + y() * v.y();
  }
  double Vector::dot(Vector &v){
    return x() * v.x() + y() * v.y();
  }
  double Vector::dot(Vector &v1, Vector &v2){
    return v1.x() * v2.x() + v1.y() * v2.y();
  }

  //Scalar Multiplication: v.x * z, v.y * z
  Vector Vector::operator * (double z){
    return Vector(x() * z, y() * z);
  }
  Vector Vector::multiply(double z){
    return Vector(x() * z, y() * z);
  }
  Vector Vector::multiply(Vector &v, double z){
    return Vector(v.x() * z, v.y() * z);
  }

  //Hadamard (dotMult) Product: v1.x * v2.x, v1.y * v2.y
  Vector Vector::hadamard(Vector &v){
    return Vector(x() * v.x(), y() * v.y());
  }
  Vector Vector::hadamard(Vector &v1, Vector &v2){
    return Vector(v1.x() * v2.x(), v1.y() * v2.y());
  }

  //Distance: sqrt((v1.x - v2.x) * (v1.x - v2.x) + (v1.y - v2.y) * (v1.y - v2.y))
  double Vector::distance(Vector &v){
    return std::hypot(x() - v.x(), y() - v.y());
  }
  double Vector::distance(Vector &v1, Vector &v2){
    return std::hypot(v1.x() - v2.x(), v1.y() - v2.y());
  }
}
#pragma once
#include "vex.h"
//{}
namespace PurePursuit{
  class Vector{
  private:
    double ix, iy;

  public:
    Vector(double x, double y);

    double x();
    double y();

    //Magnitude: sqrt(v.x*v.x + v.y*v.y)
    double magnitude();
    static double magnitude(Vector &v);

    //Normalize: v.x / mag(), v.y / mag()
    Vector normalized();
    static Vector normalized(Vector &v);

    //Subtract: v1.x - v2.x, v1.y - v2.y
    Vector operator - (Vector &v);
    Vector subtract(Vector &v);
    static Vector subtract(Vector &v1, Vector &v2);

    //Add: v1.x + v2.x, v1.y + v2.y
    Vector operator + (Vector &v);
    Vector add(Vector &v);
    static Vector add(Vector &v1, Vector &v2);

    //Dot Product: v1.x * v2.x + v1.y * v2.y
    double operator * (Vector &v);
    double dot(Vector &v);
    static double dot(Vector &v1, Vector &v2);

    //Scalar Multiplication: v.x * z, v.y * z
    Vector operator * (double z);
    Vector multiply(double z);
    static Vector multiply(Vector &v, double z);

    //Hadamard (dotMult) Product: v1.x * v2.x, v1.y * v2.y
    Vector hadamard(Vector &v);
    static Vector hadamard(Vector &v1, Vector &v2);

    //Distance: sqrt((v1.x - v2.x) * (v1.x - v2.x) + (v1.y - v2.y) * (v1.y - v2.y))
    double distance(Vector &v);
    static double distance(Vector &v1, Vector &v2);
  };
}
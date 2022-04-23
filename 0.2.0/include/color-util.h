#pragma once

class ColorUtil{
public:
  typedef struct rgb {
    float r, g, b;
  } RGB;

  typedef struct hsl {
    float h, s, l;
  } HSL;

protected:
  static float hue2rgb(float p, float q, float t);

public:
  static HSL rgb2hsl(float r, float g, float b);
  static RGB hsl2rgb(float h, float s, float l);
};
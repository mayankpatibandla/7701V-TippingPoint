#pragma once

enum teamColor{
  RED = 0, BLUE = 1, SKILLS = 2, TEST = 3, NONE = 4
};

enum teamSide{
  LEFT = 0, RIGHT = 1
};

enum autonVersion{
  AWP = 0, NEUTRAL = 1
};

enum autonType{
  MAIN = 0, OTHER = 1
};

extern teamColor tc;
extern teamSide ts;
extern autonVersion av;
extern autonType at;
#include "vex.h"
#include <fstream>

int main() {
  std::ifstream Auton("test.txt");

  std::string doot((std::istreambuf_iterator<char>(Auton)), std::istreambuf_iterator<char>());

  int size = doot.length() + 1;

  char shadow_auton[size];
  strcpy(shadow_auton, doot.c_str());

  int intArray[doot.length() + 1];

  for (int i=0; i < size; i++)
    intArray[i] = shadow_auton[i] - '0';
}
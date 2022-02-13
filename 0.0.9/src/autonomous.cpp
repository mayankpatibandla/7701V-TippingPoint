#include "vex.h"
#include "configvalues.h"
#include "functions.h"
#include "autons.h"

using namespace vex;

void f_autonomous()
{
  LCD.clearScreen();
  LCD.render();
  LCD.setCursor(1, 1);
  LCD.setFont(mono60);
  LCD.setPenColor(white);
  if(auton == 0) //skills auton
  {
    LCD.print("SKILLS");
    LCD.render();
    //PIDTest();
    auton_Skills();
    auton_Skills2a();
    //auton_Skills3();
    //PIDTest();
  }
  else if(teamColor) //blue autons
  {
    if(side) //right side
    {
      if(auton == 1) //catapult
      {
        LCD.print("BLUE RIGHT CATAPULT");
        LCD.render();

        auton_Catapult();
      }
      if(auton == 2)
      {
        LCD.print("BLUE RIGHT CYCLE TOWER");
        LCD.render();

        auton_CycleTower(Blue, sideRight);
      }
    }
    else //left side
    {
      if(auton == 1) //catapult
      {
        LCD.print("BLUE LEFT CATAPULT");
        LCD.render();

        auton_Catapult();
      }
      if(auton == 2)
      {
        LCD.print("BLUE LEFT CYCLE TOWER");
        LCD.render();

        auton_CycleTower(Blue, sideLeft);
      }
    }
  }
  else //red autons
  {
    if(side) //right side
    {
      if(auton == 1) //catapult
      {
        LCD.print("RED RIGHT CATAPULT");
        LCD.render();

        auton_Catapult();
      }
      if(auton == 2)
      {
        LCD.print("RED RIGHT CYCLE TOWER");
        LCD.render();

        auton_CycleTower(Red, sideRight);
      }
    }
    else //left side
    {
      if(auton == 1) //catapult
      {
        LCD.print("RED LEFT CATAPULT");
        LCD.render();

        auton_Catapult();
      }
      if(auton == 2)
      {
        LCD.print("RED LEFT CYCLE TOWER");
        LCD.render();

        auton_CycleTower(Red, sideLeft);
      }
    }
  }
}
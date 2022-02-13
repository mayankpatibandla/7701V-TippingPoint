#include "vex.h"

using namespace vex;
brain Brain;
controller Controller1;
competition Competition;
motor LeftLift(0);
motor RightLift(0);
motor MGTilterL(0);
motor MGTilterR(0);

digital_out Pneumatics(Brain.ThreeWirePort.A);

void usercontrol(){
 while (1) {
   //Drivetrain code
  /*LDrive.spin(directionType::fwd,Controller1.Axis3.position(percentUnits::pct)+Controller1.Axis4.position(percentUnits::pct)/2-Controller1.Axis2.position(percentUnits::pct), velocityUnits::pct);
  RDrive.spin(directionType::fwd,Controller1.Axis3.position(percentUnits::pct)-Controller1.Axis4.position(percentUnits::pct)/2-Controller1.Axis2.position(percentUnits::pct), velocityUnits::pct);
  LDrive2.spin(directionType::fwd,Controller1.Axis3.position(percentUnits::pct)+Controller1.Axis4.position(percentUnits::pct)/2-Controller1.Axis2.position(percentUnits::pct), velocityUnits::pct);
  RDrive2.spin(directionType::fwd,Controller1.Axis3.position(percentUnits::pct)-Controller1.Axis4.position(percentUnits::pct)/2-Controller1.Axis2.position(percentUnits::pct), velocityUnits::pct);
   //Control for four bar*/
  if(Controller1.ButtonL1.pressing()){
   LeftLift.spin(directionType::rev, 100, velocityUnits::pct);
   RightLift.spin(directionType::rev, 100, velocityUnits::pct);
  }
  else if(Controller1.ButtonL2.pressing()){
   RightLift.spin(directionType::fwd, 100, velocityUnits::pct);
   LeftLift.spin(directionType::fwd, 90,velocityUnits::pct);
  }
  else{
   RightLift.stop(brakeType::hold);
   LeftLift.stop(brakeType::hold);
  }
 
 //other mogo pickup

  if(Controller1.ButtonR1.pressing()){
   MGTilterL.spin(directionType::fwd, 100, velocityUnits::pct);
   MGTilterR.spin(directionType::fwd, 100, velocityUnits::pct);
  }
  else if(Controller1.ButtonR2.pressing()){
   MGTilterL.spin(directionType::rev, 100, velocityUnits::pct);
   MGTilterR.spin(directionType::rev, 100,velocityUnits::pct);
  }
  else{
   MGTilterL.stop(brakeType::hold);
   MGTilterR.stop(brakeType::hold);
  }

  if( Controller1.ButtonX.pressing() ) {
    Pneumatics.set( true );
  }
  //Otherwise don’t activate
  
  if( Controller1.ButtonY.pressing() ){
    Pneumatics.set( false );
  }
 
 wait(20,msec);
 }
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
 
 
  Competition.drivercontrol(usercontrol);

  while (true) {
    wait(100, msec);
  }
}
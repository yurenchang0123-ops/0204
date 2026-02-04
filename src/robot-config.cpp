#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen.
brain  Brain;

//The motor constructor takes motors as (port, ratio, reversed), so for example
//motor LeftFront = motor(PORT1, ratio6_1, false);
controller Controller1 = controller(primary);
motor LF = motor(PORT1, ratio6_1, true);
motor LB = motor(PORT2, ratio6_1, true);
motor LU = motor(PORT3, ratio6_1, false);
motor RF = motor(PORT4, ratio6_1, false);
motor RB = motor(PORT5, ratio6_1, false);
motor RU = motor(PORT6, ratio6_1, true);
motor Intake = motor(PORT7, ratio18_1, 0);
motor Outtake = motor(PORT8, ratio6_1, 1);
inertial Inertial_sensor = inertial(PORT11);
distance Front_Distance_sensor = distance(PORT19);
distance Back_Distance_sensor = distance(PORT20);
digital_out Loader = digital_out(Brain.ThreeWirePort.A);
digital_out lift = digital_out(Brain.ThreeWirePort.B);
digital_out goal_switch = digital_out(Brain.ThreeWirePort.C);
digital_out descore = digital_out(Brain.ThreeWirePort.D);

//Add your devices below, and don't forget to do the same in robot-config.h:


void vexcodeInit( void ) {
  // nothing to initialize
}
using namespace vex;

extern brain Brain;

//To set up a motor called LeftFront here, you'd use
//extern motor LeftFront;

extern controller Controller1;
extern motor LF;
extern motor LB;
extern motor LU;
extern motor RF;
extern motor RB;
extern motor RU;
extern motor Intake;
extern motor Outtake;
extern inertial Inertial_sensor;
extern digital_out Loader;
extern digital_out lift;
extern digital_out goal_switch;
extern digital_out descore;
extern distance Front_Distance_sensor;
extern distance Back_Distance_sensor;
void  vexcodeInit( void );
//Add your devices below, and don't forget to do the same in robot-config.cpp:



void  vexcodeInit( void );
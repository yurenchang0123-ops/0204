#include "vex.h"
// #include "autons.h"
void default_constants_skill(){
  // Eac  h constant set is in the form of (maxVoltage, kP, kI, kD, startI).
  chassis.set_drive_constants(10, 1, 0, 5, 0);
  chassis.set_heading_constants(6, .4, 0, 1, 0);
  chassis.set_turn_constants(12, .4, .03, 3, 15);
  chassis.set_swing_constants(12, .3, .001, 2, 15);

  // Each exit condition set is in the form of (settle_error, settle_time, timeout).
  chassis.set_drive_exit_conditions(1.5, 300, 2000);
  chassis.set_turn_exit_conditions(1, 300, 1500);
  chassis.set_swing_exit_conditions(1, 300, 2000);
}
double cm2inch(double Cm){
  return Cm * 0.393700787;
}
int coord_always(){
  while (1) {
    printf("X:%f",chassis.get_X_position());
    printf("  y:%f\n",chassis.get_Y_position());
    wait(20,msec);
   }
}

void skill_auton(){
  //前兩顆center
  task coord_1(coord_always);
  descore.set(1);
  Intake.spin(fwd,100,pct);
chassis.set_coordinates(55.18, 22.34, 0);
  chassis.drive_to_point(50, 45.5);
  wait(0.5,sec);
  chassis.drive_distance(5,-45);
 
  
  moveTime(-6,-6,500);
  goal_switch.set(1);
  Intake.spin(fwd,100,pct);
  wait(1,sec);
  goal_switch.set(0);
  chassis.turn_to_angle(-135);
  chassis.drive_distance(55);
  Loader.set(1);
  chassis.turn_to_angle(180);
  chassis.drive_distance(10);
  moveTime(4,4,1000);
  wait(0.8,sec);
  chassis.drive_distance(cm2inch(-14.8),180);
  wait(0.2,sec);
  Loader.set(0);
  chassis.turn_to_angle(270);
  chassis.drive_distance_front(29,270);
  Intake.stop();
  chassis.left_swing_to_angle(0);
  chassis.drive_distance(cm2inch(180),0);
  chassis.drive_distance_front(53,0);

//long goal 到 parking
// chassis.set_heading(0);
//   chassis.drive_distance_front(70,0);
//   Loader.set(0);
//   Intake.spin(fwd,100,pct);
//   chassis.turn_to_angle(25);
//   chassis.drive_distance(cm2inch(60),25);
//   chassis.left_swing_to_angle(85);
//   chassis.DriveL.spin(fwd,8,volt);
//   chassis.DriveR.spin(fwd,8,volt);


  // wait(0.25,sec);
  // chassis.DriveL.spin(fwd,11,volt);
  // chassis.DriveR.spin(fwd,11,volt);





  
// 70 point
  //   chassis.set_turn_exit_conditions(0.5, 300, 3000);
  //   chassis.set_turn_constants(12, 0.4, 0.03, 3.5, 15);  
  //   chassis.set_swing_exit_conditions(1, 300, 3000);
  //   chassis.drive_max_voltage = 8;
  //   chassis.set_drive_exit_conditions(1.5, 300, 2000);
  //   chassis.set_heading(90);
  //   chassis.drive_settle_error=.25;
  //   chassis.drive_settle_time=1000;
  //   chassis.set_drive_constants(7,0.58,0,2.5,0);


  //   chassis.drive_distance_front(41.5,90);
  //   descore.set(1);
  //   chassis.set_drive_exit_conditions(1.5, 300, 2000);
  //   Loader.set(1);

  //   Intake.spin(fwd,100,pct);
    
  //   chassis.turn_to_angle(180);
    
    
  //   chassis.drive_distance_front(16,180);
  //   chassis.drive_distance(cm2inch(4),180);
  //   moveTime(7,7,1000);
  //   wait(1.7,sec);
  //   chassis.drive_distance(cm2inch(-14.8),180);
  //   wait(0.2,sec);
    
  //   Loader.set(0);
    
  //   chassis.turn_to_angle(90);
  //   chassis.drive_distance_front(29,90);
  //   Intake.stop();
  //   chassis.right_swing_to_angle(0);

  //   chassis.drive_distance(cm2inch(180),0);
  
  //   chassis.drive_distance_front(53,0);


  //   chassis.drive_max_voltage = 8;
  //   chassis.turn_to_angle(90);
  //   chassis.set_drive_constants(7,0.58,0,2.5,0);
  //   chassis.drive_distance_front(40,90);
    
    
  //   chassis.turn_to_angle(0);
  //   chassis.drive_distance_front(83,0);
  
  //   wait(0.1,sec);
  // //1 long goal
  //   Intake.spin(fwd,100,pct);
  //   Outtake.spin(fwd,100,pct);
  //   moveTime(-6,-6,1000);
  //   Loader.set(1);
  //   wait(2,sec);
  //   Outtake.stop();
  //   chassis.drive_distance_front(17,0);
  //   chassis.drive_distance(cm2inch(4),0);
    
  //   wait(2,sec);
  //   chassis.turn_to_angle(0);
  //   chassis.drive_distance(cm2inch(-10),0);
  //   chassis.drive_distance_front(86.5,0);
  //   wait(0.1,sec);
  // //1 long goal
  //   Outtake.spin(fwd,100,pct);
  //   moveTime(-6,-6,1000);
  //   wait(2.2,sec);
  //   Outtake.stop();
  //   Intake.stop();
  //   chassis.drive_distance_front(70,0);
  //   chassis.turn_to_angle(270);
  //   chassis.drive_distance(cm2inch(215),270);
  //   chassis.set_drive_constants(7,0.58,0,2.5,0);
  //   chassis.drive_distance_front(43,270,7,1);
  //   chassis.turn_to_angle(0);
  //   Intake.spin(fwd,100,pct);
  //   chassis.drive_distance_front(16.8,0);
  //   // chassis.drive_distance(cm2inch(-0.2),0);
  //   wait(2,sec);
  //   chassis.turn_to_angle(0);
  //   chassis.drive_distance(cm2inch(-10),0);
  //   chassis.drive_distance_front(70,0);
  //   chassis.drive_distance(cm2inch(15),0);
  //   Loader.set(0);
  //   chassis.turn_to_angle(270);
  //   chassis.drive_distance_front(28,270);
  //   chassis.right_swing_to_angle(180);

  //   chassis.drive_distance(cm2inch(180),180);
  
  //   chassis.set_drive_exit_conditions(1.5, 300, 2000);
  //   chassis.drive_distance_front(53,180);
  //   chassis.turn_to_angle(270);
  //   chassis.drive_distance_front(40,270);
  //   chassis.turn_to_angle(180);
  //   //wait(0.2,sec);
  //   chassis.drive_distance_front(86,180);
  //   moveTime(-6,-6,1000);
  //   Loader.set(1);
  //   wait(0.2,sec);
  //   Intake.spin(fwd,100,pct);
  //   Outtake.spin(fwd,100,pct);
    
  //   wait(2,sec);
  //   Outtake.stop();
  //   chassis.drive_distance_front(16.8,180);
  //   //chassis.drive_distance(cm2inch(-0.1),180);
  //   wait(2.2,sec);
  //   chassis.drive_distance(cm2inch(-10),180);
  //   chassis.drive_distance_front(86,180);
  //   moveTime(-6,-6,1000);
  //   Outtake.spin(fwd,100,pct);
  //   wait(2.2,sec);
  //   Intake.stop();
  //   Outtake.stop();
  //   chassis.drive_distance_front(70,180);
  //   Loader.set(0);
  //   chassis.turn_to_angle(130);
  //   chassis.drive_distance(cm2inch(75),130);
  //   chassis.right_swing_to_angle(0);
  //   chassis.drive_distance(cm2inch(70),0);



    // chassis.right_swing_to_angle(90);
    // chassis.drive_distance(cm2inch(90),90);
    // Intake.spin(fwd);
    // wait(1.7,sec);
    // Intake2.stop(coast);
    // chassis.drive_distance(cm2inch(20));
    // chassis.turn_to_angle(270);
    // Loader.set(0);
    // chassis.drive_distance(cm2inch(190));
    // chassis.drive_distance_front(46);
    // Loader.set(1);
    // chassis.turn_to_angle(0);
    // chassis.drive_max_voltage = 3;
    // chassis.drive_distance(cm2inch(60));
    // moveTime(-5,-5, 100);
    // wait(0.3,sec);
    // moveTime(5,5, 200);
    // wait(0.7,sec);
    
    
    // chassis.drive_distance(cm2inch(-65));
    // printf("%lf\n",imu.heading());
    // wait(200,sec);
    
    // //
    // wait(1.7,sec);
    // Loader.set(0);
    // chassis.drive_max_voltage = 9;
    // chassis.drive_distance(cm2inch(30));
    // chassis.set_swing_exit_conditions(1, 300, 800);
    
    // chassis.swing_max_voltage = 8;
    // chassis.swing_max_voltage = 3;
    // chassis.right_swing_to_angle(270);
    // chassis.drive_distance_front(14);
    // chassis.turn_to_angle(180);
    // chassis.swing_max_voltage = 6;
    // chassis.drive_max_voltage = 10;
    // chassis.set_drive_exit_conditions(3,0,2000);
    // chassis.drive_distance(cm2inch(120));
    // chassis.set_drive_exit_conditions(1.5, 300, 2000);
    // chassis.drive_distance_front(80);
    


    // chassis.drive_max_voltage = 10;
    // chassis.right_swing_to_angle(100);
    // chassis.left_swing_to_angle(0);
    // Loader.set(1);
    // printf("%lf\n",imu.heading());
    // chassis.set_swing_exit_conditions(1, 300, 3000);
    // chassis.drive_distance(cm2inch(35));
    // moveTime(-5,-5, 70);
    // wait(0.3,sec);
    // moveTime(5,5, 200);
    // wait(0.7,sec);
    // moveTime(-5,-5, 200); 
    // chassis.drive_distance(cm2inch(-60));
    // Intake2.spin(fwd);
    // wait(1.7,sec);
    // wait(200,sec);
    // chassis.drive_distance(cm2inch(30));
}

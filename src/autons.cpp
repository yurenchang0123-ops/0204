#include "vex.h"

/**
 * Resets the constants for auton movement.
 * Modify these to change the default behavior of functions like
 * drive_distance(). For explanations of the difference between
 * drive, heading, turning, and swinging, as well as the PID and
 * exit conditions, check the docs.
 */

void default_constants(){
  // Each constant set is in the form of (maxVoltage, kP, kI, kD, startI).
  chassis.set_drive_constants(8, 0.9, 0, 4.8, 0);
  // chassis.set_drive_constants(10, .8, .0, .8, 0);
  chassis.set_heading_constants(6, .4, 0, 1, 0);
  chassis.set_turn_constants(10, .4, .03, 3, 15);
  chassis.set_swing_constants(10, .3, .001, 2, 15);

  // Each exit condition set is in the form of (settle_error, settle_time, timeout).
  chassis.set_drive_exit_conditions(1.5, 300, 5000);
  chassis.set_turn_exit_conditions(1, 200, 1250);
  chassis.set_swing_exit_conditions(3, 200, 3000);
}

/**
 * Sets constants to be more effective for odom movements.
 * For functions like drive_to_point(), it's often better to have
 * a slower max_voltage and greater settle_error than you would otherwise.
 */

void test(){
}

void moveTime(double LV,double RV,double Timemsec){
  chassis.drive_with_voltage(LV,RV);
  wait(Timemsec,msec);
  chassis.drive_with_voltage(0,0);
}


void print_coord(){
  printf("X:%f",chassis.get_X_position());
  printf("  y:%f\n",chassis.get_Y_position());
}

#include "vex.h" // 確保包含 VEX 核心庫
#include <cmath> // 為了使用 fabs

struct OuttakeParams {
    int time;
};

int outtake_task_fn(void* arg) {
    if (arg == nullptr) return 0;
    
    OuttakeParams* p = (OuttakeParams*)arg;
    int timeMsec = p->time;

    // 修正 Timer 未定義問題
    int startTime = (int)Brain.Timer.system(); 

    Intake.spin(forward, 100, percent);
    Outtake.spin(forward, 100, percent);
    
    while (((int)Brain.Timer.system() - startTime) < timeMsec) {
      int elapsedTime = (int)Brain.Timer.system() - startTime;
      Outtake.spin(forward, 100, percent);
        
        double outtakeVel = fabs(Outtake.velocity(rpm));

        if (elapsedTime > 500) {
            if (outtakeVel > 480) { // 假設 480 為卡住的門檻值
                if (elapsedTime < (timeMsec * 0.8)) {
                    Intake.spin(reverse, 100, percent);
                    wait(250, msec);
                    Intake.spin(forward, 100, percent);
                    wait(1000, msec);
                } else {
                    break; 
                }
            }
        }
        wait(20, msec);
    }
    
    Outtake.stop();
    delete p; 
    return 0;
}

void Outtaking(int timeMsec, bool blocking) {
    // 建立參數結構並分配記憶體
    OuttakeParams* p = new OuttakeParams{timeMsec};

    if (blocking) {
        // 直接執行函式邏輯
        outtake_task_fn((void*)p);
    } else {
        // 使用 vex::thread 開啟背景任務
        // 注意：在 VEXcode 中，建構子會自動啟動 thread
        vex::thread t(outtake_task_fn, (void*)p);
    }
}

void right_awp(){
  chassis.drive_max_voltage=10;
  chassis.set_coordinates(0, 0, 0);
  chassis.drive_max_voltage= 7;
  descore.set(1);
  chassis.drive_distance(14,10);
  Intake.spin(fwd,100,pct);  
  chassis.drive_distance(11,30,4,3);
  chassis.turn_to_angle(-45);
  chassis.drive_distance(5);
  Intake.spin(fwd,-100,pct);
  wait(0.8,sec);
  chassis.drive_distance(-5);
  Loader.set(1);
  chassis.turn_to_angle(135);
  Intake.spin(fwd,100,pct);
  chassis.drive_distance(32);
  chassis.turn_to_angle(180);
  chassis.drive_timeout=500;
  chassis.drive_distance(15,180);
  wait(1.4,sec);
  chassis.drive_timeout=1000;
  chassis.drive_distance(-33,180);
  // Outtake.spin(fwd,100,pct); 
  Outtaking(1500,1);
  chassis.drive_distance(13);
  chassis.turn_to_angle(-140);
  chassis.drive_distance(-18);
  chassis.turn_to_angle(180);
  descore.set(0);
  chassis.drive_distance(-22);
                  
}

void left_awp(){
  // chassis.set_coordinates(0,0,90);
  //   chassis.turn_max_voltage = 5.48;
  //   chassis.turn_settle_error = 0.58;
  //   chassis.turn_settle_time = 231;
  // chassis.turn_to_angle(75.131719, 5.48, 0.58, 231, 873);
  //   chassis.drive_max_voltage = 8.58;
  //   chassis.heading_max_voltage = 5.15;
  //   chassis.drive_settle_error = 1.36;
  //   chassis.drive_settle_time = 278;
  // chassis.drive_distance(28.05948, 75.131719, 8.58, 5.15, 1.36, 278, 1515);
  // task::sleep(50);
  //   chassis.turn_max_voltage = 11.0;
  //   chassis.turn_settle_error = 1.74;
  //   chassis.turn_settle_time = 248;
  // chassis.turn_to_angle(315.0, 11.0, 1.74, 248, 1024);
  //   chassis.drive_max_voltage = 7.95;
  //   chassis.heading_max_voltage = 4.77;
  //   chassis.drive_settle_error = 1.21;
  //   chassis.drive_settle_time = 254;
  // chassis.drive_distance(-19.346442, 315.0, 7.95, 4.77, 1.21, 254, 1337);
  // task::sleep(1000);
  //   chassis.drive_max_voltage = 12.0;
  //   chassis.heading_max_voltage = 7.8;
  //   chassis.drive_settle_error = 2.12;
  //   chassis.drive_settle_time = 273;
  // chassis.drive_distance(53.287567, 315.0, 12.0, 7.8, 2.12, 273, 1647);
  // task::sleep(50);
  //   chassis.turn_max_voltage = 7.9;
  //   chassis.turn_settle_error = 1.03;
  //   chassis.turn_settle_time = 222;
  // chassis.turn_to_angle(270.0, 7.9, 1.03, 222, 891);
  //   chassis.drive_max_voltage = 7.43;
  //   chassis.heading_max_voltage = 4.46;
  //   chassis.drive_settle_error = 1.09;
  //   chassis.drive_settle_time = 234;
  // chassis.drive_distance(12.0, 270.0, 7.43, 4.46, 1.09, 234, 1152);
  // task::sleep(50);
  //   chassis.drive_max_voltage = 8.71;
  //   chassis.heading_max_voltage = 5.23;
  //   chassis.drive_settle_error = 1.39;
  //   chassis.drive_settle_time = 284;
  // chassis.drive_distance(-30.0, 270.0, 8.71, 5.23, 1.39, 284, 1554);

  descore.set(1);
  Outtake.setVelocity(60,pct);
  chassis.drive_max_voltage= 7;
  chassis.drive_distance(14,-10);
  Intake.spin(fwd,100,pct);  
  chassis.drive_distance(15,-30,4,3);
  Loader.set(1);
  chassis.turn_to_angle(-135);
  chassis.drive_distance(-20);
  goal_switch.set(1);
  Intake.setVelocity(60,pct);
  Outtake.spinFor(fwd,0.5,sec);
  chassis.drive_distance(-3);
  chassis.turn_to_angle(-135);
  Intake.spin(fwd,100,pct);
  chassis.drive_distance(53);
  chassis.turn_to_angle(180);
  chassis.drive_timeout=500;
  chassis.drive_distance(15,180);
  wait(1,sec);
  chassis.drive_timeout=1000;
  chassis.drive_distance(-33,180);
  Outtaking(3000,1);
}

void solo_awp(){
  chassis.set_drive_constants(12, 1, 0, 5, 0);
  chassis.set_swing_constants(7, .3, .001, 2, 15);
  chassis.set_coordinates(91, 20, 90);

  chassis.drive_max_voltage=10;
  chassis.drive_timeout=500;
  chassis.drive_timeout=1500;
  Loader.set(1);
  chassis.drive_to_point(121.2, 23.5);
  chassis.turn_to_angle(180,8);
  Intake.spin(fwd,100,pct);

  moveTime(6,6,1000);
  wait(0.8,sec);
  chassis.drive_distance(-20,180);
  Outtake.spin(fwd,100,pct);
  moveTime(-6,-6,1300);
  Loader.set(0);
  Outtake.stop();
  chassis.turn_to_angle(-75,8,3,100,800);
  chassis.drive_to_point(107.5, 53);
  chassis.turn_to_angle(-90,8);
  chassis.drive_to_point(51,59);
  print_coord();
  chassis.turn_to_angle(-135);
  chassis.drive_distance(-15);
  goal_switch.set(1);
  Outtake.spin(fwd,100,pct);
  moveTime(-3,-3,600);
  wait(0.3,sec);
  goal_switch.set(0);
  Outtake.stop();
  chassis.drive_to_point(22, 35,8,10,7);
  Loader.set(1);
  chassis.turn_to_angle(180,8);
  moveTime(3,3,1000);
  wait(0.5,sec);
  chassis.drive_distance(-25);
  Outtake.spin(fwd,100,pct);
  moveTime(-5,-5,1500);
}

void right_9_block(){
  chassis.drive_max_voltage=10;
  chassis.set_coordinates(0, 0, 0);
  chassis.drive_max_voltage= 7;
  descore.set(1);
  chassis.drive_distance(15,10);
  Intake.spin(fwd,100,pct);  
  Loader.set(1);
  chassis.drive_distance(11,30,4,3);
  chassis.turn_to_angle(135);
  Intake.spin(fwd,100,pct);
  chassis.drive_distance(32);
  chassis.turn_to_angle(180);
  chassis.drive_timeout=500;
  chassis.drive_distance(15,180);
  moveTime(-3,-3,150);
  moveTime(4,4,250);
  wait(0.6,sec);
  chassis.drive_timeout=1000;
  chassis.drive_distance(-33,180);
  // Outtake.spin(fwd,100,pct); 
  Outtaking(3000,1);
  chassis.drive_timeout=1000;
  chassis.drive_distance(13);
  chassis.turn_to_angle(-140);
  chassis.drive_timeout=1000;
  chassis.drive_distance(-18);
  chassis.turn_to_angle(180);
  descore.set(0);
  chassis.drive_distance(-22);
                  
}

void left_9_block(){
  chassis.set_coordinates(0, 0, 0);
  chassis.drive_max_voltage= 7;
   descore.set(1);
  chassis.drive_distance(14,-10);
  Intake.spin(fwd,100,pct);  
  Loader.set(1);
  chassis.drive_distance(11,-30,4,3);
  chassis.turn_to_angle(-135);
  Intake.spin(fwd,100,pct);
  chassis.drive_distance(32);
  chassis.turn_to_angle(180);
//V2
  Loader.set(1);
  chassis.drive_timeout=500;
  chassis.drive_distance(20,180);
  moveTime(-3,-3,200);
  moveTime(4,4,400);
  wait(0.6,sec);
  chassis.drive_timeout=1500;
  chassis.drive_distance(-34,180);
  Outtaking(3000,1);
  chassis.drive_distance(13);
  chassis.turn_to_angle(-140);
  chassis.drive_distance(-16);
  chassis.turn_to_angle(180);
  descore.set(0);
  chassis.drive_distance(-15);
  chassis.drive_stop(hold);
//V1
  // chassis.drive_timeout=500;
  // chassis.drive_distance(-20,180);
  // Outtake.spin(fwd,100,pct);
  // wait(1.4,sec);
  // Outtake.stop();
  // chassis.drive_timeout=1000;
  // chassis.drive_distance(30);
  // wait(1,sec);
  // chassis.drive_distance(-34,180);
  // Outtake.spin(fwd,100,pct); 
  // wait(1.6,sec);
  // Outtake.stop();
  // chassis.drive_distance(13);
  // chassis.turn_to_angle(-140);
  // chassis.drive_distance(-16);
  // chassis.turn_to_angle(180);
  // descore.set(0);
  // chassis.drive_distance(-15);

}

void solo_13_block(){
 chassis.set_coordinates(90,20,90);
  chassis.drive_to_point(108,20);
  Loader.set(1);
  chassis.drive_to_point(120,8);
  chassis.turn_to_angle(180);
  chassis.drive_distance(6);
  //loader 1
  Intake.spin(fwd,100,pct);
  wait(2,sec);
  chassis.drive_distance(40);
  //long goal 1
  Outtake.spin(fwd,100,pct);
  wait(2,sec);
  Outtake.stop();
  Loader.set(0);
  chassis.left_swing_to_angle(270);
  chassis.drive_to_point(96,48);//3
  chassis.turn_to_angle(270);
  chassis.drive_to_point(48,48);//3
  chassis.turn_to_point(24,10);
  chassis.drive_to_point(24,10);
  chassis.turn_to_point(24,0);
  Loader.set(1);
  chassis.drive_distance(6);
  // loder 2
  wait(2,sec);
  chassis.drive_distance(40);
  // long goal 2
  Outtake.spin(fwd,100,pct);
  wait(2,sec);
  Outtake.stop();
  Loader.set(0);
}



//9 BLOCK(RIGHT)
  // chassis.set_coordinates(0, 0, 0);
  // chassis.drive_max_voltage= 7;
  // chassis.drive_to_point(1,12);
  // Intake.spin(fwd,100,pct);  
  // Loader.set(1);
  // wait(0.5,sec);
  // chassis.turn_to_point(8,30);
  // Loader.set(0);
  // chassis.drive_to_point(17,34);
  // chassis.left_swing_to_angle(90); 
  // chassis.drive_distance(7,90,7,4,1,200,2000);
  // Loader.set(1);
  // chassis.drive_distance(-3);
  // chassis.left_swing_to_angle(0);
  // chassis.drive_distance(-10);
  // chassis.left_swing_to_angle(-90);
  // chassis.drive_distance(-3);
  // chassis.left_swing_to_angle(180);
  // chassis.drive_timeout=300;
  // chassis.drive_distance(-10,180,10,4,1,200,500);
  // chassis.drive_timeout=1500;
  // Outtake.spin(fwd,100,pct);
  // wait(2,sec);
  // Outtake.stop();
  // chassis.drive_distance(28,180);
  // wait(1,sec);
  // chassis.drive_distance(-30,180);
  // chassis.drive_timeout=500;
  // Outtake.spin(fwd,100,pct);

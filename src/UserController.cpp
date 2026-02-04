#include"vex.h"


int Outtake_spin(){  
  Outtake.setVelocity(100, percent);
  while(1){
    if (Controller1.ButtonL1.pressing()) {
      Intake.spin(fwd,100,pct);
      Outtake.spin(fwd,100,pct);}
    else if (Controller1.ButtonR1.pressing()) Intake.spin(fwd,100,pct);
    else if (Controller1.ButtonR2.pressing()) Intake.spin(fwd,-100,pct);
    else {
      Intake.stop(); 
      Outtake.stop(); }
    wait(10,msec);
  }
}

int Loader_switch(){
  while(1){
    if (Controller1.ButtonDown.pressing()){
      Loader.set(!Loader.value());
      task::sleep(20); 
        // 統一：等待按鍵釋放
      while (Controller1.ButtonDown.pressing()) {
        task::sleep(5);
      }
    }
    wait(10,msec);
  }
}

// int Center_switch(){
//   while(1){
//     if (Controller1.ButtonY.pressing()){
//       goal_switch.set(1);
//       // 統一：等待按鍵釋放
//     }
//     else{
//       goal_switch.set(0);
//     }
//     wait(10,msec);
//   }
// }

int Descore_switch(){
  while(1){
    if (Controller1.ButtonB.pressing()){
      descore.set(!descore.value());
      task::sleep(20); 
        // 統一：等待按鍵釋放
      while (Controller1.ButtonB.pressing()) {
        task::sleep(5);
      }
    }
    wait(10,msec);
  } 
}
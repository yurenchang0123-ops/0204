#include "vex.h"
#include "icon.h"
#include "logo.h"
#include "UserControl.h"
#ifndef M_PI
// #define M_PI 3.14159265358979323846
#endif

// 角度轉弧度巨集
#define deg_to_rad(deg) ((deg) * M_PI / 180.0)
//github test
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int current_auton_selection = 0;//比賽調成"0"
bool reset_color=1;//紅色：1 藍色：0
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

using namespace vex;
competition Competition;

/*---------------------------------------------------------------------------*/
/*                             VEXcode Config                                */
/*                                                                           */
/*  Before you do anything else, start by configuring your motors and        */
/*  sensors. In VEXcode Pro V5, you can do this using the graphical          */
/*  configurer port icon at the top right. In the VSCode extension, you'll   */
/*  need to go to robot-config.cpp and robot-config.h and create the         */
/*  motors yourself by following the style shown. All motors must be         */
/*  properly reversed, meaning the drive should drive forward when all       */
/*  motors spin forward.                                                     */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                             JAR-Template Config                           */
/*                                                                           */
/*  Where all the magic happens. Follow the instructions below to input      */
/*  all the physical constants and values for your robot. You should         */
/*  already have configured your motors.                                     */
/*---------------------------------------------------------------------------*/

Drive chassis(

//Pick your drive setup from the list below:
//ZERO_TRACKER_NO_ODOM
//ZERO_TRACKER_ODOM
//TANK_ONE_FORWARD_ENCODER
//TANK_ONE_FORWARD_ROTATION
//TANK_ONE_SIDEWAYS_ENCODER
//TANK_ONE_SIDEWAYS_ROTATION
//TANK_TWO_ENCODER
//TANK_TWO_ROTATION
//HOLONOMIC_TWO_ENCODER
//HOLONOMIC_TWO_ROTATION

//Write it here:
TANK_ONE_SIDEWAYS_ROTATION,

//Add the names of your Drive motors into the motor groups below, separated by commas, i.e. motor_group(Motor1,Motor2,Motor3).
//You will input whatever motor names you chose when you configured your robot using the sidebar configurer, they don't have to be "Motor1" and "Motor2".

//Left Motors:
motor_group(LF,LB,LU),

//Right Motors:
motor_group(RF,RB,RU),

//Specify the PORT NUMBER of your inertial sensor, in PORT format (i.e. "PORT1", not simply "1"):
PORT11,

//Input your wheel diameter. (4" omnis are actually closer to 4.125"):
3.25,

//External ratio, must be in decimal, in the format of input teeth/output teeth.
//If your motor has an 84-tooth gear and your wheel has a 60-tooth gear, this value will be 1.4.
//If the motor drives the wheel directly, this value is 1:
0.75,

//Gyro scale, this is what your gyro reads when you spin the robot 360 degrees.
//For most cases 360 will do fine here, but this scale factor can be very helpful when precision is necessary.
360,

/*---------------------------------------------------------------------------*/
/*                                  PAUSE!                                   */
/*                                                                           */
/*  The rest of the drive constructor is for robots using POSITION TRACKING. */
/*  If you are not using position tracking, leave the rest of the values as  */
/*  they are.                                                                */
/*---------------------------------------------------------------------------*/

//If you are using ZERO_TRACKER_ODOM, you ONLY need to adjust the FORWARD TRACKER CENTER DISTANCE.

//FOR HOLONOMIC DRIVES ONLY: Input your drive motors by position. This is only necessary for holonomic drives, otherwise this section can be left alone.
//LF:      //RF:    
PORT1,     -PORT2,

//LB:      //RB: 
PORT3,     -PORT4,

//If you are using position tracking, this is the Forward Tracker port (the tracker which runs parallel to the direction of the chassis).
//If this is a rotation sensor, enter it in "PORT1" format, inputting the port below.
//If this is an encoder, enter the port as an integer. Triport A will be a "1", Triport B will be a "2", etc.
PORT13,

//Input the Forward Tracker diameter (reverse it to make the direction switch):
2,

//Input Forward Tracker center distance (a positive distance corresponds to a tracker on the right side of the robot, negative is left.)
//For a zero tracker tank drive with odom, put the positive distance from the center of the robot to the right side of the drive.
//This distance is in inches:
-1.25,

//Input the Sideways Tracker Port, following the same steps as the Forward Tracker Port:
PORT14,

//Sideways tracker diameter (reverse to make the direction switch):
2,

//Sideways tracker center distance (positive distance is behind the center of the robot, negative is in front):
2.875

);


bool auto_started = false;
/**
 * Function before autonomous. It prints the current auton number on the screen
 * and tapping the screen cycles the selected auton by 1. Add anything else you
 * may need, like resetting pneumatic components. You can rename these autons to
 * be more descriptive, if you like.
 */
int timer_1=105;
float speed,Chassis_t;
bool screen_mode=1;
bool pre_auton_break=0;
int brain_screen(){
	waitUntil(pre_auton_break);
	while(1){
		int LF_t = LF.temperature(percent)*0.7;
		int LB_t = LB.temperature(percent)*0.7;
		int LU_t = LU.temperature(percent)*0.7;
		int RF_t = RF.temperature(percent)*0.7;
		int RB_t = RB.temperature(percent)*0.7;
		int RU_t = RU.temperature(percent)*0.7;



		if (Brain.Screen.pressing()) {
			int touchX = Brain.Screen.xPosition();
			int touchY = Brain.Screen.yPosition();
			
			if (touchX >= 300 && touchX <= 480 && touchY >= 1 && touchY <= 41) {
				screen_mode = !screen_mode; 
			} 
			
			else {
				chassis.set_heading(0);      
				chassis.set_coordinates(0, 0, 0); 
			}
			
			waitUntil(!Brain.Screen.pressing());
		}

		if(screen_mode){
			Brain.Screen.setCursor(1,5);
			Brain.Screen.setPenColor(white);
			switch(current_auton_selection){ 
			case 1: 
				Brain.Screen.print("right_awp");
				break;
			case 2:
				Brain.Screen.print("left_awp");
				break;
			case 3:
				Brain.Screen.print("solo_awp");
				break;
			case 4:
				Brain.Screen.print("right_9 BLOCK");
				break;
			case 5:
				Brain.Screen.print("left_9 BLOCK");
				break;
			case 6:
				Brain.Screen.print("solo_13 BLOCK");
				break;
			case 7:
				Brain.Screen.print("skill");
				break;
			}
			if(current_auton_selection<7){
				Brain.Screen.setCursor(2,5); 
				if(reset_color) Brain.Screen.print("red");
				else Brain.Screen.print("blue");
			}
			Brain.Screen.drawImageFromBuffer(logo,70,30,sizeof(logo));
		}
		else {
      Brain.Screen.setPenColor(white);
			Brain.Screen.drawImageFromBuffer(icon,-10,20,sizeof(icon));
      
      Brain.Screen.printAt(50,25,"Intake");
			
			Brain.Screen.setPenColor(purple);
			Brain.Screen.setCursor(5,6);
			Brain.Screen.print(LF_t);
			Brain.Screen.setCursor(5,15);
			Brain.Screen.print(RF_t);
			Brain.Screen.setCursor(7,6);
			Brain.Screen.print(LB_t);
			Brain.Screen.setCursor(7,15);
			Brain.Screen.print(RB_t);
			Brain.Screen.setCursor(9,6);
			Brain.Screen.print(LU_t);
			Brain.Screen.setCursor(9,15);
			Brain.Screen.print(RU_t);

			Brain.Screen.setCursor(3,22);
			Brain.Screen.print("Intake: ");
			Brain.Screen.print(Intake.temperature(percent)*0.7);
			Brain.Screen.setCursor(4,22);
			Brain.Screen.print("Outtake :");
			Brain.Screen.print(Outtake.temperature(percent)*0.7);

			Brain.Screen.setPenColor(red);
			Brain.Screen.setCursor(18,5);
			Brain.Screen.print("Battery: ");
			Brain.Screen.print("%d", Brain.Battery.capacity());
		}
		Brain.Screen.drawRectangle(300, 1, 180, 40, green);
		Brain.Screen.setPenColor(black); 
		Brain.Screen.setFillColor(green);
		Brain.Screen.printAt(340, 25, "Switch Mode");
		Brain.Screen.setFillColor(black);
// --- 陀螺儀繪圖邏輯 ---
    double heading = chassis.get_absolute_heading();
    double angle_deg = fmod((450.0 - heading), 360.0);
    double angle_rad = deg_to_rad(angle_deg);
    
    // 指南針中心點和半徑
    const int CX = 400;
    const int CY = 175;
    const int R = 50;

    int EX = CX + R * cos(angle_rad);
    int EY = CY - R * sin(angle_rad); 

    // 繪製圓形外框
    Brain.Screen.setPenColor(white);
    Brain.Screen.drawCircle(CX, CY, R);
    
    // 繪製航向線
    Brain.Screen.setPenColor(red);
    Brain.Screen.drawLine(CX, CY, EX, EY);

    Brain.Screen.setPenColor(green);
    Brain.Screen.setCursor(4,38);
    Brain.Screen.print("X: ");
    Brain.Screen.print("%.3f",chassis.get_X_position());
    
    Brain.Screen.setCursor(5,38);
    Brain.Screen.print("Y: ");
    Brain.Screen.print("%.3f",chassis.get_Y_position());

    wait(0.2,sec);
    Brain.Screen.clearScreen();
    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1,0);
    Controller1.Screen.print(chassis.get_X_position());
    Controller1.Screen.setCursor(2,0);
    Controller1.Screen.print(chassis.get_Y_position());
	}			
	return 0;
}

int timer_30(){
  while(1){
    timer_1--;
    wait(1,sec);
    if(timer_1<=30&&timer_1>=29){
      Controller1.rumble(rumbleShort);
    }
  }
  return 0;
}





/****************************************************************************************************************************************************/
/****************************************************************************************************************************************************/
/****************************************************************************************************************************************************/
/****************************************************************************************************************************************************/

void pre_auton(void) {
  int autonCase = -1;         

  chassis.set_coordinates(0, 0, 0); 
  const int BUTTON_WIDTH = 160;
  const int BUTTON_HEIGHT = 90;
  const int FUNC_HEIGHT = 92;

  Brain.Screen.setPenColor(black); 
  if(current_auton_selection!=0){
    if(current_auton_selection<7){
      default_constants();
      chassis.set_coordinates(0, 0, 0);}
    else default_constants_skill();
    pre_auton_break=1;
  }
  // ------------------- B. 繪圖與邏輯主迴圈 -------------------
  
  while (current_auton_selection == 0) {
    Brain.Screen.clearScreen();
    
    // --- Case 1: R AWP (Cyan) --- 座標 (0, 0)
    Brain.Screen.setFillColor(autonCase == 1 ? green : cyan);
    Brain.Screen.drawRectangle(0, 0, BUTTON_WIDTH, BUTTON_HEIGHT);
    Brain.Screen.printAt(5, 35, "Case 1"); 
    Brain.Screen.printAt(5, 55, "R AWP"); 

    // --- Case 2: L AWP (Orange) --- 座標 (160, 0)
    Brain.Screen.setFillColor(autonCase == 2 ? green : orange);
    Brain.Screen.drawRectangle(BUTTON_WIDTH, 0, BUTTON_WIDTH, BUTTON_HEIGHT);
    Brain.Screen.printAt(BUTTON_WIDTH + 5, 35, "Case 2"); 
    Brain.Screen.printAt(BUTTON_WIDTH + 5, 55, "L AWP"); 

    // --- Case 3: SOLO AWP (Purple) --- 座標 (320, 0)
    Brain.Screen.setFillColor(autonCase == 3 ? green : purple);
    Brain.Screen.drawRectangle(BUTTON_WIDTH * 2, 0, BUTTON_WIDTH, BUTTON_HEIGHT);
    Brain.Screen.printAt(BUTTON_WIDTH * 2 + 5, 35, "Case 3"); 
    Brain.Screen.printAt(BUTTON_WIDTH * 2 + 5, 55, "SOLO AWP"); 

    // --- Case 4: R 9 BLK (Cyan) --- 座標 (0, 90)
    Brain.Screen.setFillColor(autonCase == 4 ? green : cyan);
    Brain.Screen.drawRectangle(0, BUTTON_HEIGHT, BUTTON_WIDTH, BUTTON_HEIGHT);
    Brain.Screen.printAt(5, BUTTON_HEIGHT + 35, "Case 4"); 
    Brain.Screen.printAt(5, BUTTON_HEIGHT + 55, "R 9_B"); 

    // --- Case 5: L 9 BLK (Orange) --- 座標 (160, 90)
    Brain.Screen.setFillColor(autonCase == 5 ? green : orange);
    Brain.Screen.drawRectangle(BUTTON_WIDTH, BUTTON_HEIGHT, BUTTON_WIDTH, BUTTON_HEIGHT);
    Brain.Screen.printAt(BUTTON_WIDTH + 5, BUTTON_HEIGHT + 35, "Case 5"); 
    Brain.Screen.printAt(BUTTON_WIDTH + 5, BUTTON_HEIGHT + 55, "L 9_B"); 

    // --- Case 6: SOLO 13 BLK (Purple) --- 座標 (320, 90)
    Brain.Screen.setFillColor(autonCase == 6 ? green : purple);
    Brain.Screen.drawRectangle(BUTTON_WIDTH * 2, BUTTON_HEIGHT, BUTTON_WIDTH, BUTTON_HEIGHT);
    Brain.Screen.printAt(BUTTON_WIDTH * 2 + 5, BUTTON_HEIGHT + 35, "Case 6"); 
    Brain.Screen.printAt(BUTTON_WIDTH * 2 + 5, BUTTON_HEIGHT + 55, "SOLO 13_B");
    
    // 左下方：確認鍵 (CONFIRM)
    Brain.Screen.setFillColor(green); 
    Brain.Screen.drawRectangle(0, 180, BUTTON_WIDTH, FUNC_HEIGHT);
    Brain.Screen.printAt(5, 220, "CONFIRM");

    // 中間下方：SKILL 鍵 (Case 7)
    Brain.Screen.setFillColor(autonCase == 7 ? green : white); 
    Brain.Screen.drawRectangle(BUTTON_WIDTH, 180, BUTTON_WIDTH, FUNC_HEIGHT);
    Brain.Screen.setPenColor(black);
    Brain.Screen.printAt(BUTTON_WIDTH + 5, 220, "SKILL (Case 7)");

    // 右下方：顏色切換 (Alliance Color)
    color alliance_bg = reset_color ? red : blue;
    Brain.Screen.setFillColor(alliance_bg); 
    Brain.Screen.drawRectangle(BUTTON_WIDTH * 2, 180, BUTTON_WIDTH, FUNC_HEIGHT);
    Brain.Screen.printAt(BUTTON_WIDTH * 2 + 55, 220, reset_color ? "RED" : "BLUE");   
    // ------------------- C. 偵測點擊事件----------------------
    waitUntil(Brain.Screen.pressing());
    int x = Brain.Screen.xPosition();
    int y = Brain.Screen.yPosition();
    waitUntil(!Brain.Screen.pressing());
    
    // 判斷 Auton 區 (Y < 180)
    if (y < BUTTON_HEIGHT) { // Y=0 行
      if (x < BUTTON_WIDTH) { autonCase = 1; } // Case 1
      else if (x < BUTTON_WIDTH * 2) { autonCase = 2; } // Case 2
      else { autonCase = 3; } // Case 3
    } 
    else if (y < 180) { // Y=90 行
      if (x < BUTTON_WIDTH) { autonCase = 4; } // Case 4
      else if (x < BUTTON_WIDTH * 2) { autonCase = 5; } // Case 5
      else { autonCase = 6; } // Case 6
    } 
    // 判斷功能區 (Y >= 180)
    else { 
      if (x < BUTTON_WIDTH) { // 左側：CONFIRM
        if (autonCase != -1) {current_auton_selection = autonCase;}
      } 
      else if (x < BUTTON_WIDTH * 2) autonCase = 7; 
      else  reset_color = !reset_color; 
    }
    if(current_auton_selection!=0){
      if(current_auton_selection<7)default_constants();
      else default_constants_skill();
      pre_auton_break=1;
      break;
    }
  }
  
  Brain.Screen.setPenColor(white);
  Brain.Screen.setFillColor(black);
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1,5);
  switch(current_auton_selection){ 
      case 1:         
        Brain.Screen.print("right_awp");
        break;
      case 2:
        Brain.Screen.print("left_awp");
        break;
      case 3:
        Brain.Screen.print("solo_awp");
        break;
      case 4:
          Brain.Screen.print("right_9 BLOCK");
        break;
      case 5:
        Brain.Screen.print("left_9 BLOCK");
        break;
      case 6:
        Brain.Screen.print("solo_13 BLOCK");
        break;
      case 7:
        Brain.Screen.print("skill");
        break;
  }
  if(current_auton_selection<7){
    Brain.Screen.setCursor(2,5); 
    if(reset_color) Brain.Screen.print("red");
    else Brain.Screen.print("blue");
  }
  wait(200,msec);
}


void autonomous(void) {
  auto_started = true;
  switch(current_auton_selection){   
    case 1:         
      right_awp();
      break;
    case 2:
      left_awp();
      break;
    case 3:
      solo_awp();
      break;
    case 4:
      right_9_block();
      break;
    case 5:
      left_9_block();
      break;
    case 6:
      solo_13_block();//暫時放 skill
      break;
    case 7:
      skill_auton();
      break;
  }
}


/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/
void usercontrol(void) {

  chassis.DriveL.setStopping(coast);
  chassis.DriveR.setStopping(coast);
  speed = 90; 
  
  task brain_screen_1(brain_screen); 
  task timer_2(timer_30); 
  // task user(user_control);
  // task control_1(Intake_spin);
  task control_2(Outtake_spin);
  task control_3(Loader_switch);
  task control_4(Descore_switch);
  // task control_5(Center_switch);
  while (1) {
    chassis.control_arcade( 4.5);
    wait(10,msec);
    
  }
}
//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}

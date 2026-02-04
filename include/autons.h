#pragma once
#include "JAR-Template/drive.h"

class Drive;

extern Drive chassis;

void default_constants();
void moveTime(double LV,double RV,double Timemsec);
void print_coord();
void test();
void right_awp();
void left_awp();
void solo_awp();
void right_9_block();
void left_9_block();
void solo_13_block();
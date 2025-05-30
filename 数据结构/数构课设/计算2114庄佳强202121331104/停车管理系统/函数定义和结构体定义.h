#pragma once
#include"函数定义和结构体定义.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h> 
#include <windows.h>		
#include <string.h>	
#include <cstring>
#include <time.h>
using namespace std;

//头文件部分

#define Price 0.1//每一秒的价格
#define	MAX_car 5//停车场最大容量
#define MAX_wait 4//候车场最大容量


typedef struct
{
	int in_time;//进场时间
	int out_time;//出场时间
	char ct[100];//停车时间信息
	char License_plate[30];//车牌号
}Car;


typedef struct node
{
	Car stop[MAX_car];
	int top;
}car_stop;//停车栈

typedef struct  //候车场
{
	Car wait[MAX_wait];
	int count;
	int front, rear;
}Waitting;//候车循环队列
void Car_Leave(car_stop& G, Waitting& P);//停车场出车
void Display(car_stop G);//显示停车场车辆信息
void Display_wait(Waitting P);//显示候车场车辆信息
void P_Leave(Waitting& P);//候车场出车
void car_P_come(Waitting& P, char C[]);//候车场进车
void car_come(car_stop& G, Waitting& P);//停车场进车
void search(car_stop G, Waitting P);//查找车辆
void welcome(car_stop& G, Waitting& P);//菜单界面
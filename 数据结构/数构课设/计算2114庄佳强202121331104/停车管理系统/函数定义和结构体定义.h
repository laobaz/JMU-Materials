#pragma once
#include"��������ͽṹ�嶨��.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h> 
#include <windows.h>		
#include <string.h>	
#include <cstring>
#include <time.h>
using namespace std;

//ͷ�ļ�����

#define Price 0.1//ÿһ��ļ۸�
#define	MAX_car 5//ͣ�����������
#define MAX_wait 4//�򳵳��������


typedef struct
{
	int in_time;//����ʱ��
	int out_time;//����ʱ��
	char ct[100];//ͣ��ʱ����Ϣ
	char License_plate[30];//���ƺ�
}Car;


typedef struct node
{
	Car stop[MAX_car];
	int top;
}car_stop;//ͣ��ջ

typedef struct  //�򳵳�
{
	Car wait[MAX_wait];
	int count;
	int front, rear;
}Waitting;//��ѭ������
void Car_Leave(car_stop& G, Waitting& P);//ͣ��������
void Display(car_stop G);//��ʾͣ����������Ϣ
void Display_wait(Waitting P);//��ʾ�򳵳�������Ϣ
void P_Leave(Waitting& P);//�򳵳�����
void car_P_come(Waitting& P, char C[]);//�򳵳�����
void car_come(car_stop& G, Waitting& P);//ͣ��������
void search(car_stop G, Waitting P);//���ҳ���
void welcome(car_stop& G, Waitting& P);//�˵�����
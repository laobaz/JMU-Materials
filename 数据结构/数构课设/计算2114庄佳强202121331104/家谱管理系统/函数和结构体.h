#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <stdlib.h> 
#include<string.h>
#include <time.h>
#include<stack>
using namespace std;




#define Maxx 30
typedef struct
{
	int num;//���Ӹ���
	char name[Maxx];///���� 
	int sex;//�Ա� 
	char spouse[Maxx];//��ż������

}DataType;//��������Ķ���


typedef struct Tnode
{
	DataType data;
	struct Tnode* nextstr[10];//���ӽ��	
	struct Tnode* parent;//˫�׽��
}Pedtree;//������

void welcome();//������
void welcome1();//����Ӵ��Ľ���
void Create_tree(Pedtree*& S, int& k);//��txt�ļ��е����ݹ��������
void Create_Newtree(Pedtree*& S, int& k);//txt�ļ��ĵڶ�������
void Create_tree_hand(Pedtree*& S);//ֱ��������ݹ��캯��
void Create_Newtree_hand(Pedtree*& ChildrenT);//ֱ�ӹ���ĵڶ�������
void Display(Pedtree* S);//���������
bool Search(Pedtree* S,char temp[],Pedtree *&temptree);//���������Ƿ���ҷ���
void Search1(Pedtree* S);//�ݹ��������
bool Search2(Pedtree* S, char temp[], Pedtree*& temptree);//���Ұ��µ������Ƿ���ҷ���
void Search3(Pedtree* S);//�ݹ���Һ��
void Search_result(Pedtree* S);//�ܵĲ��Һ���
void add_newpeople(Pedtree*& S);//���������
void add_newchildren(Pedtree*& S);//����º��Ӻ���
void add_newspouse(Pedtree*& S);//����°��º���
void Delete(Pedtree*& S);//ɾ��������
void Deleteall(Pedtree* &S);//ɾ�����Ӳ��ֺ���
void New_File(Pedtree* S);//�洢���ļ��ĺ���

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
	int num;//孩子个数
	char name[Maxx];///姓名 
	int sex;//性别 
	char spouse[Maxx];//配偶的姓名

}DataType;//树数据域的定义


typedef struct Tnode
{
	DataType data;
	struct Tnode* nextstr[10];//孩子结点	
	struct Tnode* parent;//双亲结点
}Pedtree;//家谱树

void welcome();//主界面
void welcome1();//在添加处的界面
void Create_tree(Pedtree*& S, int& k);//用txt文件中的数据构造家谱树
void Create_Newtree(Pedtree*& S, int& k);//txt文件的第二个函数
void Create_tree_hand(Pedtree*& S);//直接输出数据构造函数
void Create_Newtree_hand(Pedtree*& ChildrenT);//直接构造的第二个函数
void Display(Pedtree* S);//输出家谱树
bool Search(Pedtree* S,char temp[],Pedtree *&temptree);//查找姓名是否查找符合
void Search1(Pedtree* S);//递归查找祖先
bool Search2(Pedtree* S, char temp[], Pedtree*& temptree);//查找伴侣的姓名是否查找符合
void Search3(Pedtree* S);//递归查找后代
void Search_result(Pedtree* S);//总的查找函数
void add_newpeople(Pedtree*& S);//添加主函数
void add_newchildren(Pedtree*& S);//添加新孩子函数
void add_newspouse(Pedtree*& S);//添加新伴侣函数
void Delete(Pedtree*& S);//删除主函数
void Deleteall(Pedtree* &S);//删除孩子部分函数
void New_File(Pedtree* S);//存储到文件的函数

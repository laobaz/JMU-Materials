#include"函数和结构体.h"


char name[Maxx][Maxx], spouse[Maxx][Maxx];//定义全局变量，存储文件中的数据，方便建立家谱树和还原家谱树
int Num[Maxx], Sex[Maxx];
int flag = 0;//标记是否已经构建家谱表


void welcome()//主界面
{
	printf("\n\t\t------------------家谱管理-------------------\n\n"); 
	printf("\t\t———————————————————————\n");
	printf("\t\t*                                           *\n");
	printf("\t\t*         家谱信息管理菜单                  *\n");
	printf("\t\t*                                           *\n");
	printf("\t\t*          1:输入家谱信息                   *\n");
	printf("\t\t*          2:从文件中读取家谱               *\n");
	printf("\t\t*          3:查找并输出某人信息             *\n");
	printf("\t\t*          4:添加新的家庭成员               *\n");
	printf("\t\t*          5:输出整个家谱信息               *\n");
	printf("\t\t*          6:删除成员                       *\n");
	printf("\t\t*          7：存储到文件中                  *\n");
	printf("\t\t*          0:退出整个程序                   *\n");
	printf("\t\t*                                           *\n");
	printf("\t\t———————————————————————\n");
}
void welcome1()//添加时的见面
{
	printf("\n\n\t\t———————请选择你的操作————————\n\n");
	printf("\t      —————1.添加某个人的子女的信息——————\n");
	printf("\t   ——————2.添加某个人的配偶的信息——————\n");
	printf("\n\t  ——————————3.退出——————————— \n");
}
void Create_tree_hand(Pedtree*& S)//手动输出家谱树
{
	char a1[Maxx], a2[Maxx];
	int a3, a4;//临时存储文件中的数据
	fflush(stdin);//清除键盘缓冲区 
	system("cls");//清空控制台
	printf("请输入第一个人的姓名   伴侣（不存在为0）性别（男为1，女为 0），孩子个数   \n");
	scanf("%s %s %d %d", a1, a2, &a3, &a4);//读入
	strcpy(S->data.name, a1);//读入到家谱树的总祖先中，先建立总祖先
	strcpy(S->data.spouse, a2);
	S->data.sex = a3;
	S->data.num = a4;//读入到家谱树的总祖先中，先建立总祖先
	if (strcmp(S->data.spouse, "0") == 0 && S->data.num != 0)
	{
		printf("\t\t%s的配偶不存在，不能有孩子！\n", S->data.name);
		S->data.num = 0;
	}
	for (int i = 0; i < S->data.num; i++)//存储孩子部分
	{
		printf("\n");
		Pedtree* ChildrenT = (Pedtree*)malloc(sizeof(Pedtree));
		S->nextstr[i] = ChildrenT;
		printf("请输入%s的  第%d个孩子的 姓名 伴侣（不存在为0）性别（男为1，女为 0），孩子个数   \n",S->data.name,i+1);
		scanf("%s %s %d %d", a1, a2, &a3, &a4);//与上同理
		strcpy(ChildrenT->data.name, a1);
		strcpy(ChildrenT->data.spouse, a2);
		ChildrenT->data.sex = a3;
		ChildrenT->data.num = a4;	
		ChildrenT->parent = S;//
		if (ChildrenT->data.num != 0)//当孩子的孩子不为0，即有孩子时，先进行孩子的孩子部分输入
			Create_Newtree_hand(ChildrenT);
	}
	fflush(stdin);//清除键盘缓冲区 
	printf("\n\n\t\t- - - - 家谱建造成功- - - - - \n");
}
void Create_Newtree_hand(Pedtree*& S)//构建孩子的孩子，同理
{
	char a1[Maxx], a2[Maxx];
	int a3, a4;
	for (int i = 0; i < S->data.num; i++)
	{
		printf("\n");
		Pedtree* ChildrenT = (Pedtree*)malloc(sizeof(Pedtree));		
		S->nextstr[i] = ChildrenT;
		printf("请输入%s的  第%d个孩子的 姓名 伴侣（不存在为0）性别（男为1，女为 0），孩子个数  \n", S->data.name, i + 1);
		scanf("%s %s %d %d", a1, a2, &a3,&a4);
		strcpy(ChildrenT->data.name, a1);
		strcpy(ChildrenT->data.spouse, a2);
		ChildrenT->data.sex = a3;
		ChildrenT->data.num = a4;
		ChildrenT->parent = S;
		if (ChildrenT->data.num != 0)
			Create_Newtree_hand(ChildrenT);
	}

}
void Create_tree(Pedtree*& S,int &k)//利用文件中的数据构建家谱
{
	fflush(stdin);//清除键盘缓冲区 
	system("cls");
	strcpy(S->data.name, name[k]);
	strcpy(S->data.spouse, spouse[k]);
	S->data.sex = Sex[k];
	S->data.num = Num[k];
	k++;
	if (strcmp(S->data.spouse, "0") == 0 && S->data.num != 0)
	{
		printf("\t\t%s的配偶不存在，不能有孩子！\n", S->data.name);
		S->data.num = 0;
	}
	for (int i = 0; i < S->data.num; i++)
	{
		printf("\n");
		Pedtree *ChildrenT = (Pedtree*)malloc(sizeof(Pedtree));
		S->nextstr[i] = ChildrenT;
		strcpy(ChildrenT->data.name, name[k]);
		strcpy(ChildrenT->data.spouse, spouse[k]);
		ChildrenT->data.sex = Sex[k];
		ChildrenT->data.num = Num[k];
		k++;
		ChildrenT->parent = S;
		Create_Newtree(ChildrenT, k);
	}
	fflush(stdin);//清除键盘缓冲区 
	printf("\n\n\t\t- - - - 家谱建造成功- - - - - \n");
	
}
void Create_Newtree(Pedtree*& S, int& k)//同理上面
{
	for (int i = 0; i < S->data.num; i++)
	{
		printf("\n");
		Pedtree* ChildrenT = (Pedtree*)malloc(sizeof(Pedtree));
		S->nextstr[i] = ChildrenT;
		strcpy(ChildrenT->data.name, name[k]);
		strcpy(ChildrenT->data.spouse, spouse[k]);
		ChildrenT->data.sex = Sex[k];
		ChildrenT->data.num = Num[k];
		k++;
		ChildrenT->parent = S;
		Create_Newtree(ChildrenT, k);

	}
}
void Display(Pedtree* S)//输出家谱
{
	if (strcmp(S->data.name, "0") != 0)//存在这个人
		printf("\t\t姓名：%s  ", S->data.name);
	if (S->data.sex == 1)//男性
	{
		printf("性别：男\n");
		if (strcmp(S->data.spouse, "0") != 0)
			printf("\t\t老婆姓名：%s\n", S->data.spouse);
		else
			printf("\t\t没有老婆，未婚\n");
	}
	else if (S->data.sex == 0)//女性
	{
		printf("性别：女\n");
		if (strcmp(S->data.spouse, "0") != 0)//是否伴侣
			printf("\t\t老公姓名：%s\n", S->data.spouse);
		else
			printf("\t\t没有老公，未婚\n");
	}
	for (int i = 0; i < S->data.num; i++)
	{
		if (strcmp(S->nextstr[i]->data.name, "0") != 0)
			printf("\t\t第%d个子女的姓名：%s  ", i + 1, (S->nextstr[i])->data.name);
		if (((S->nextstr[i])->data.sex) == 1)
			printf("性别：男\n");
		else if (((S->nextstr[i])->data.sex) == 0)
			printf("性别：女\n");
	}
	cout << "\n";
	for (int j = 0; j < S->data.num; j++)//如果有孩子，遍历孩子部分
		Display(S->nextstr[j]);
	fflush(stdin);//清除键盘缓冲区

}
void Search_result(Pedtree* S)
{
	Pedtree* temptree = NULL;//记录找到的位置
	char temp[20];
	fflush(stdin);//清除键盘缓冲区 
	system("cls");
	printf("\t\t请输入你要查找的人的姓名：");
	scanf("%s", temp);
	if (Search(S, temp, temptree))//查找名字部分
	{
		printf("\n\n\t\t----*----*----*----*----*----*----*----*----*----*----\n");
		if (temptree->parent != NULL)//输出双亲
		{
			printf("\t\t姓名：%s\t", temptree->data.name);
			if (temptree->data.sex == 1)
				printf("\t\t性别：男\n");
			else if ((temptree->data.sex) == 0)
				printf("\t\t性别：女\n");
			if ((temptree->parent->data.sex) == 1)
			{
				printf("\t\t父亲姓名：%s \n", temptree->parent->data.name);
				printf("\t\t母亲姓名：%s \n", temptree->parent->data.spouse);
			}
			else if ((temptree->parent->data.sex) == 0)
			{
				printf("\t\t父亲姓名：%s \n", temptree->parent->data.spouse);
				printf("\t\t母亲姓名：%s \n", temptree->parent->data.name);
			}
			for (int i = 0; i < temptree->parent->data.num; i++)//输出兄弟部分
			{
				if (strcmp(temptree->parent->nextstr[i]->data.name, temp) != 0)
					printf("\t\t兄弟名称为：%s \n", temptree->parent->nextstr[i]->data.name);
			}
			if (temptree->parent->parent != NULL)
			{
				Search1(temptree->parent);//输出祖先部分
			}
		}
		else
		{
			printf("\t\t第1代\n");//没有双亲，第一代人，总祖先
			printf("\t\t姓名：%s  \n", temptree->data.name);
			if ((temptree->data.sex) == 1)
				printf("\t\t性别：男\n");
			else if ((temptree->data.sex) == 0)
				printf("\t\t性别：女\n");
			printf("\t\t无兄弟姐妹 \n");
		}
		//输出配偶信息 
		if ((temptree->data.sex) == 1)
		{
			if (strcmp(temptree->data.spouse, "0") != 0)
				printf("\t\t太太姓名：%s\n", temptree->data.spouse);
			else
				printf("\t\t没有太太，未婚\n");
		}
		else if ((temptree->data.sex) == 0)
		{
			if (strcmp(temptree->data.spouse, "0") != 0)
				printf("\t\t丈夫姓名：%s\n", temptree->data.spouse);
			else
				printf("\t\t没有丈夫，未婚\n");
		}
		if (temptree->data.num != 0)//孩子部分
		{
			printf("\t\t孩子信息：\n");
			for (int j = 0; j < temptree->data.num; j++)
			{
				if (strcmp(temptree->nextstr[j]->data.name, "0") == 0)
					continue;
				printf("\t\t\t第%d个孩子：姓名：%s  \n", j + 1, temptree->nextstr[j]->data.name);
				if ((temptree->nextstr[j]->data.sex) == 1)
					printf("\t\t\t\t\t性别：男\n");
				else if ((temptree->nextstr[j]->data.sex) == 0)
					printf("\t\t\t\t\t性别：女\n");

			}
			
		}
		for (int i = 0; i < temptree->data.num; i++)//输出后代部分
		{
			if (temptree->nextstr[i]->data.num != 0)
				Search3(temptree->nextstr[i]);
		}
		printf("\t\t----*----*----*----*----*----*----*----*----*----*----\n\n");
	}
	else if (Search2(S, temp, temptree))//如果在伴侣那边，下面同理
	{
		printf("\n\t\t你要找的人已找到，信息如下：\n");
		printf("\t\t姓名：%s  \n", temptree->data.spouse);
		if ((temptree->data.sex) == 1)
		{
			printf("\t\t性别：女\n");
			printf("\n\t\t无父母信息不存在家谱中,也无兄弟姐妹在家谱中\n");
			printf("\n\t\t丈夫姓名：%s\n", temptree->data.name);
		}
		else if ((temptree->data.sex) == 0)
		{
			printf("\t\t性别：男\n");
			printf("\n\t\t无父母信息不存在家谱中，也无兄弟姐妹在家谱中\n");
			printf("\n\t\t太太姓名：%s\n", temptree->data.name);
		}
		if (temptree->data.num != 0)
		{
			printf("\t\t孩子信息：\n");
			for (int j = 0; j < temptree->data.num; j++)
			{
				if (strcmp(temptree->nextstr[j]->data.name, "0") == 0)
					continue;
				printf("\t\t\t第%d个孩子：姓名：%s  \n", j + 1, temptree->nextstr[j]->data.name);
				if ((temptree->nextstr[j]->data.sex) == 1)
					printf("\t\t\t\t\t性别：男\n");
				else if ((temptree->nextstr[j]->data.sex) == 0)
					printf("\t\t\t\t\t性别：女\n");

			}

		}
		for (int i = 0; i < temptree->data.num; i++)
		{
			if (temptree->nextstr[i]->data.num != 0)
				Search3(temptree->nextstr[i]);
		}
		printf("\t\t----*----*----*----*----*----*----*----*----*----*----\n\n");
	}
	else
	{
		printf("\t\t***该家谱图中没有%s这个人的信息请确认是否输入正确***\n\n", temp);
	}
}
bool Search(Pedtree* S, char temp[], Pedtree*& temptree)//查找名字
{
	if (strcmp(S->data.name, temp) == 0)
	{
		temptree = S;
		return true;
	}
	else
	{
		for (int i = 0; i < S->data.num; i++)
		{
			if (Search(S->nextstr[i], temp, temptree))//递归
				return true;
		}
		return false;
	}
}
void Search1(Pedtree* S)//查找祖先
{
	if (S->parent != NULL)
	{

		if (S->parent->data.sex == 1)
			printf("\t\t祖先(除双亲外)为 男性 姓名为 %s 配偶为 %s  \n", S->parent->data.name, S->parent->data.spouse);
		else
			printf("\t\t祖先为(除双亲外) 女性 姓名为 %s 配偶为 %s  \n", S->parent->data.name, S->parent->data.spouse);
	}
	if (S->parent->parent != NULL)
		Search1(S->parent);
}
bool Search2(Pedtree* S, char temp[], Pedtree*& temptree)//查找伴侣部分
{
	if (strcmp(S->data.spouse, temp) == 0)
	{
		temptree = S;
		return true;
	}
	else
	{
		for (int i = 0; i < S->data.num; i++)
		{
			if (Search(S->nextstr[i], temp, temptree))
				return true;
		}
		return false;
	}
}
void Search3(Pedtree* S)//查找后代
{
	if (S->data.num != 0)
	{
		for (int i = 0; i < S->data.num;i++)
		{
			if (strcmp(S->nextstr[i]->data.spouse, "0") != 0)
				printf("\t\t后代有%s 配偶为%s\n", S->nextstr[i]->data.name,S->nextstr[i]->data.spouse);
			else
				printf("\t\t后代有%s 无配偶  \n", S->nextstr[i]->data.name);
		}
	}
	for (int i = 0; i < S->data.num; i++)
	{
		if (S->nextstr[i]->data.num != 0)
			Search3(S->nextstr[i]);
	}
}
void add_newpeople(Pedtree*& S)//添加新成员
{
	fflush(stdin);
	int choice;
	while (1)
	{
		fflush(stdin);
		system("cls");
		welcome1();
		cout << "\t  请你选择：";
		cin >> choice;
		switch (choice)
		{
		case 1:
		{
			add_newchildren(S);//新孩子
			int i;
			printf("\t\t输出0返回");
			scanf("%d", &i);
			break;
		}
		case 2:
		{
			add_newspouse(S);//新伴侣
			int i;
			printf("\t\t输出0返回");
			scanf("%d", &i);
			break;
		}
		case 3:
			return;

		}
	}
}
void add_newchildren(Pedtree*& S)
{
	fflush(stdin);
	system("cls");
	char children_name[Maxx];
	Pedtree* temptree = NULL;
	printf("\n\t\t请输入要添加子女的父母的名字：");//先找到双亲
	scanf("%s", children_name);
	if (Search(S, children_name, temptree) || Search2(S, children_name, temptree))
	{
		if (strcmp(temptree->data.spouse, "0") != 0)
		{
			Pedtree* Childtree;
			int num = temptree->data.num;
			Childtree = (Pedtree*)malloc(sizeof(Pedtree));//创建新的结点
			temptree->nextstr[num] = Childtree;


			printf("\n\t\t请输入要添加的子女的姓名：");
			scanf("%s", Childtree->data.name);
			printf("\n\t\t请输入添加子女的性别（1男，0女）：");
			fflush(stdin);//清除键盘缓冲区  
			scanf("%d", &(Childtree->data.sex));
			(temptree->data.num)++;
			Childtree->parent = temptree;
			strcpy(Childtree->data.spouse, "0");
			Childtree->data.num = 0;

			printf("\n\n\t\t- - - - 子女信息添加成功- - - - - \n");
		}
		else
			printf("\n\t\t配偶不存在，不能添加子女信息\n");
	}
	else
		printf("\n\n\t\t不存在该父母！\n");
	fflush(stdin);//清除键盘缓冲区 
}
void add_newspouse(Pedtree*& S)//与孩子部分同理
{
	fflush(stdin);
	system("cls");
	char pouse_name[Maxx];
	int f = 0;
	Pedtree *temptree=NULL;
	printf("\n\t\t请输入要添加人的配偶的名字：");
	scanf("%s", pouse_name);
	if (!Search(S, pouse_name, temptree))
	{
		printf("\n\n\t\t不存在该人！\n");
		f = 1;
	}
	else
	{
		if (strcmp(temptree->data.spouse, "0") == 0)
		{
			printf("\n\t\t请入人的姓名：");
			scanf("%s", temptree->data.spouse);

		}
		else
		{
			cout << "什么，找小三，我直接哒咩！\n";
			f = 1;
		}
	}
	fflush(stdin);
	if(f==0)
		printf("\n\n\t\t- - - - 配偶信息添加成功- - - - - \n");
}
void  Delete(Pedtree* &S)//删除部分
{
	fflush(stdin);//清除键盘缓冲区 
	system("cls");
	char DE_name[Maxx];
	cout << "\t\t请输入要删除的人：";
	cin >> DE_name;
	Pedtree* temptree = NULL;
	Pedtree* head = S;
	int i;
	if (Search(S, DE_name, temptree))
	{
		if (strcmp(temptree->data.name, head->data.name) == 0)
		{
			flag = 0;
			free(S);
		}
		Deleteall(temptree);
		//temptree->parent->data.num--;
		for (int i = 0; i < temptree->parent->data.num; i++)//将孩子结点前移，防止报错和反复读入
			if (strcmp(temptree->parent->nextstr[i]->data.name, "0") == 0)
			{
				for (int j = i; j <= temptree->parent->data.num; j++)
					temptree->parent->nextstr[j] = temptree->parent->nextstr[j + 1];
				temptree->parent->data.num--;//孩子减一
				break;
			}
		

		cout << "\t\t删除成功\n";
		return;
	}
	else if(Search2(S,DE_name,temptree))
	{
		for (i = 0; i < temptree->data.num; i++)
			Deleteall(temptree->nextstr[i]);
		strcpy(temptree->data.spouse, "0");
		temptree->data.num = 0;
		printf("\n\t\t删除成功");
	}
	else
	{
		printf("\n\n\t\t——————————————————————————\n\n");
		printf("\t\t***该家谱图中没有%s这个人的信息请确认是否输入正确***\n\n", DE_name);
		printf("\t\t——————————————————————————————\n\n");
	}
}
void Deleteall(Pedtree* &S)
{
	int i;
	if (S)
	{
		for (i = 0; i < S->data.num; i++)
			Deleteall(S->nextstr[i]);
		strcpy(S->data.name, "0");
		strcpy(S->data.spouse, "0");
		S->data.num = 0;
		S->data.sex = -1;
		//free(S);

	}
}
void New_File(Pedtree* S)//更新文件
{
	FILE* fp;
	stack<Pedtree*> st;//家谱结构栈，用来临时存储孩子
	stack<int> sp;//空格数量栈，为了和结构栈同步，赋给空格方便隔开
	Pedtree* p;
	int k = 0;
	fp = fopen("Myfamily104.txt", "w");
	fprintf(fp, "姓名\t伴侣\t性别\t孩子个数\n");
	st.push(S);
	sp.push(k);
	while (!st.empty())
	{
		p = st.top();
		st.pop();
		k = sp.top();
		sp.pop();
		if (strcmp(p->data.name, "0") != 0)
		{
			for (int i = 0; i < k; i++)
				fprintf(fp, "  ");
			fprintf(fp, "%s  %s  %d  %d  \n", p->data.name, p->data.spouse, p->data.sex, p->data.num);
			if (p->data.num != 0)
			{
				k = k + 2;//扩大空格
				for (int i = 0; i < p->data.num; i++)
				{

					st.push(p->nextstr[i]);//进栈
					sp.push(k);//同步进栈
				}
			}
		}

	}
	fclose(fp);
	
}

int main()
{
	Pedtree* S;
	char s1[Maxx], s2[Maxx], Garbage[Maxx];
	int a, b, s;
	FILE* fp;
	
	//i = 0;
	//while (name[i])
	//{
	//	printf("%s", name[i]);

	//	i++;
	//}
	//scanf("%d", &i);

	int choice, k = 0;

	while (1)
	{
		fflush(stdin);//清除键盘缓冲区 
		system("cls");
		welcome();
		printf("\n");
		printf("\t\t请您选择:");
		cin >> choice;
		switch (choice)
		{
		case 1:
		{
			if (flag == 0)
			{
				S = (Pedtree*)malloc(sizeof(Pedtree));
				S->parent = NULL;
				Create_tree_hand(S);
				printf("\t\t构建完成\n");
				flag = 1;
				int i;
				printf("\t\t输出0返回");
				scanf("%d", &i);
				break;
			}
			else
			{
				cout << "已经建立好了家谱，无需反复" << endl;
				int j;
				cout << "是否重新构构建  1.是  2.否：";
				cin >> j;
				switch (j)
				{
				case 1:
				{
					Deleteall(S);
					flag = 0;
					cout << "删除完成\n";
				}
				case 2:
				{
					break;
				}
				}
				int i;
				printf("\t\t输出0返回");
				scanf("%d", &i);
				break;
			}
		}
		case 2:
		{
			if (flag == 0)
			{
				k = 0;
				fp = fopen("MyFamily104.txt", "r");
				if (fp == NULL)
				{
					printf("can not open file\n");
					exit(0);
				}
				int i = 0;
				fscanf(fp, "%s %s %s %s", Garbage, Garbage, Garbage, Garbage);
				while (fscanf(fp, "%s %s %d %d\n", s1, s2, &s, &a) != EOF)
				{
					strcpy(name[i], s1);
					strcpy(spouse[i], s2);
					Num[i] = a;
					Sex[i] = s;
					i++;
				}
				fclose(fp);
				S = (Pedtree*)malloc(sizeof(Pedtree));
				S->parent = NULL;
				Create_tree(S, k);
				printf("\t\t构建完成\n");
				flag = 1;
				printf("\t\t输出0返回");
				scanf("%d", &i);
				break;
			}
			else
			{
				cout << "已经建立好了家谱，无需反复" << endl;
				int j;
				cout << "是否重新构构建  1.是  2.否：";
				cin >> j;
				switch (j)
				{
				case 1:
				{
					Deleteall(S);
					flag = 0;
					cout << "删除完成\n";
				}
				case 2:
				{
					break;
				}
				}
				int i;
				printf("\t\t输出0返回");
				scanf("%d", &i);
				break;
			}
		}

		case 3:
		{
			if (flag == 0)
			{
				cout << "请先建立族谱" << endl;
				int i;
				printf("\t\t输出0返回");
				scanf("%d", &i);
				break;

			}
			else
			{
				fflush(stdin);//清除键盘缓冲区 
				system("cls");
				Search_result(S);
				int i;
				printf("\t\t输出0返回");
				scanf("%d", &i);
				break;

			}
		}
		case 4:
		{
			if (flag == 0)
			{
				cout << "请先建立族谱" << endl;
				int i;
				printf("\t\t输出0返回");
				scanf("%d", &i);
				break;
			}
			else
			{
				fflush(stdin);//清除键盘缓冲区 
				system("cls");
				add_newpeople(S);
				int i;
				printf("\t\t输出0返回");
				scanf("%d", &i);
				break;
			}

		}
		case 5:
		{
			if (flag == 0)
			{
				cout << "请先建立族谱" << endl;
				int i;
				printf("\t\t输出0返回");
				scanf("%d", &i);
				break;
			}
			else
			{
				fflush(stdin);//清除键盘缓冲区 
				system("cls");
				printf("\n\n\t\t整个家谱主要的信息如下：\n");
				printf("\n\t\t---***---***---***---***---***---***---\n");
				Display(S);
				int i;
				printf("\t\t输出0返回");
				scanf("%d", &i);
				break;
			}
		}
		case 6:
		{
			if (flag == 0)
			{
				cout << "请先建立族谱" << endl;
				int i;
				printf("\t\t输出0返回");
				scanf("%d", &i);
				break;
			}
			else
			{
				Delete(S);
				int i;
				printf("\t\t输出0返回");
				scanf("%d", &i);
				break;
			}
		}

		case 7:
		{
			if (flag == 0)
			{
				cout << "请先建立族谱" << endl;
				int i;
				printf("\t\t输出0返回");
				scanf("%d", &i);
				break;
			}
			else
			{
				fflush(stdin);
				system("cls");
				New_File(S);
				cout << "存储完成\n";
				int i;
				printf("\t\t输出0返回");
				scanf("%d", &i);
				break;

			}

		}
		case 0:
		{
			cout << "\t\t感谢使用本小程序！" << endl;
			return 0;
		}
		default:
			cout << "\t\t输出不正确，再试试吧！" << endl;
			break;
		}
	}

}
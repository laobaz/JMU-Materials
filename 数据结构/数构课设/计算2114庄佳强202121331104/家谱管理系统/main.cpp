#include"�����ͽṹ��.h"


char name[Maxx][Maxx], spouse[Maxx][Maxx];//����ȫ�ֱ������洢�ļ��е����ݣ����㽨���������ͻ�ԭ������
int Num[Maxx], Sex[Maxx];
int flag = 0;//����Ƿ��Ѿ��������ױ�


void welcome()//������
{
	printf("\n\t\t------------------���׹���-------------------\n\n"); 
	printf("\t\t����������������������������������������������\n");
	printf("\t\t*                                           *\n");
	printf("\t\t*         ������Ϣ����˵�                  *\n");
	printf("\t\t*                                           *\n");
	printf("\t\t*          1:���������Ϣ                   *\n");
	printf("\t\t*          2:���ļ��ж�ȡ����               *\n");
	printf("\t\t*          3:���Ҳ����ĳ����Ϣ             *\n");
	printf("\t\t*          4:����µļ�ͥ��Ա               *\n");
	printf("\t\t*          5:�������������Ϣ               *\n");
	printf("\t\t*          6:ɾ����Ա                       *\n");
	printf("\t\t*          7���洢���ļ���                  *\n");
	printf("\t\t*          0:�˳���������                   *\n");
	printf("\t\t*                                           *\n");
	printf("\t\t����������������������������������������������\n");
}
void welcome1()//���ʱ�ļ���
{
	printf("\n\n\t\t����������������ѡ����Ĳ�������������������\n\n");
	printf("\t      ����������1.���ĳ���˵���Ů����Ϣ������������\n");
	printf("\t   ������������2.���ĳ���˵���ż����Ϣ������������\n");
	printf("\n\t  ��������������������3.�˳����������������������� \n");
}
void Create_tree_hand(Pedtree*& S)//�ֶ����������
{
	char a1[Maxx], a2[Maxx];
	int a3, a4;//��ʱ�洢�ļ��е�����
	fflush(stdin);//������̻����� 
	system("cls");//��տ���̨
	printf("�������һ���˵�����   ���£�������Ϊ0���Ա���Ϊ1��ŮΪ 0�������Ӹ���   \n");
	scanf("%s %s %d %d", a1, a2, &a3, &a4);//����
	strcpy(S->data.name, a1);//���뵽���������������У��Ƚ���������
	strcpy(S->data.spouse, a2);
	S->data.sex = a3;
	S->data.num = a4;//���뵽���������������У��Ƚ���������
	if (strcmp(S->data.spouse, "0") == 0 && S->data.num != 0)
	{
		printf("\t\t%s����ż�����ڣ������к��ӣ�\n", S->data.name);
		S->data.num = 0;
	}
	for (int i = 0; i < S->data.num; i++)//�洢���Ӳ���
	{
		printf("\n");
		Pedtree* ChildrenT = (Pedtree*)malloc(sizeof(Pedtree));
		S->nextstr[i] = ChildrenT;
		printf("������%s��  ��%d�����ӵ� ���� ���£�������Ϊ0���Ա���Ϊ1��ŮΪ 0�������Ӹ���   \n",S->data.name,i+1);
		scanf("%s %s %d %d", a1, a2, &a3, &a4);//����ͬ��
		strcpy(ChildrenT->data.name, a1);
		strcpy(ChildrenT->data.spouse, a2);
		ChildrenT->data.sex = a3;
		ChildrenT->data.num = a4;	
		ChildrenT->parent = S;//
		if (ChildrenT->data.num != 0)//�����ӵĺ��Ӳ�Ϊ0�����к���ʱ���Ƚ��к��ӵĺ��Ӳ�������
			Create_Newtree_hand(ChildrenT);
	}
	fflush(stdin);//������̻����� 
	printf("\n\n\t\t- - - - ���׽���ɹ�- - - - - \n");
}
void Create_Newtree_hand(Pedtree*& S)//�������ӵĺ��ӣ�ͬ��
{
	char a1[Maxx], a2[Maxx];
	int a3, a4;
	for (int i = 0; i < S->data.num; i++)
	{
		printf("\n");
		Pedtree* ChildrenT = (Pedtree*)malloc(sizeof(Pedtree));		
		S->nextstr[i] = ChildrenT;
		printf("������%s��  ��%d�����ӵ� ���� ���£�������Ϊ0���Ա���Ϊ1��ŮΪ 0�������Ӹ���  \n", S->data.name, i + 1);
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
void Create_tree(Pedtree*& S,int &k)//�����ļ��е����ݹ�������
{
	fflush(stdin);//������̻����� 
	system("cls");
	strcpy(S->data.name, name[k]);
	strcpy(S->data.spouse, spouse[k]);
	S->data.sex = Sex[k];
	S->data.num = Num[k];
	k++;
	if (strcmp(S->data.spouse, "0") == 0 && S->data.num != 0)
	{
		printf("\t\t%s����ż�����ڣ������к��ӣ�\n", S->data.name);
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
	fflush(stdin);//������̻����� 
	printf("\n\n\t\t- - - - ���׽���ɹ�- - - - - \n");
	
}
void Create_Newtree(Pedtree*& S, int& k)//ͬ������
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
void Display(Pedtree* S)//�������
{
	if (strcmp(S->data.name, "0") != 0)//���������
		printf("\t\t������%s  ", S->data.name);
	if (S->data.sex == 1)//����
	{
		printf("�Ա���\n");
		if (strcmp(S->data.spouse, "0") != 0)
			printf("\t\t����������%s\n", S->data.spouse);
		else
			printf("\t\tû�����ţ�δ��\n");
	}
	else if (S->data.sex == 0)//Ů��
	{
		printf("�Ա�Ů\n");
		if (strcmp(S->data.spouse, "0") != 0)//�Ƿ����
			printf("\t\t�Ϲ�������%s\n", S->data.spouse);
		else
			printf("\t\tû���Ϲ���δ��\n");
	}
	for (int i = 0; i < S->data.num; i++)
	{
		if (strcmp(S->nextstr[i]->data.name, "0") != 0)
			printf("\t\t��%d����Ů��������%s  ", i + 1, (S->nextstr[i])->data.name);
		if (((S->nextstr[i])->data.sex) == 1)
			printf("�Ա���\n");
		else if (((S->nextstr[i])->data.sex) == 0)
			printf("�Ա�Ů\n");
	}
	cout << "\n";
	for (int j = 0; j < S->data.num; j++)//����к��ӣ��������Ӳ���
		Display(S->nextstr[j]);
	fflush(stdin);//������̻�����

}
void Search_result(Pedtree* S)
{
	Pedtree* temptree = NULL;//��¼�ҵ���λ��
	char temp[20];
	fflush(stdin);//������̻����� 
	system("cls");
	printf("\t\t��������Ҫ���ҵ��˵�������");
	scanf("%s", temp);
	if (Search(S, temp, temptree))//�������ֲ���
	{
		printf("\n\n\t\t----*----*----*----*----*----*----*----*----*----*----\n");
		if (temptree->parent != NULL)//���˫��
		{
			printf("\t\t������%s\t", temptree->data.name);
			if (temptree->data.sex == 1)
				printf("\t\t�Ա���\n");
			else if ((temptree->data.sex) == 0)
				printf("\t\t�Ա�Ů\n");
			if ((temptree->parent->data.sex) == 1)
			{
				printf("\t\t����������%s \n", temptree->parent->data.name);
				printf("\t\tĸ��������%s \n", temptree->parent->data.spouse);
			}
			else if ((temptree->parent->data.sex) == 0)
			{
				printf("\t\t����������%s \n", temptree->parent->data.spouse);
				printf("\t\tĸ��������%s \n", temptree->parent->data.name);
			}
			for (int i = 0; i < temptree->parent->data.num; i++)//����ֵܲ���
			{
				if (strcmp(temptree->parent->nextstr[i]->data.name, temp) != 0)
					printf("\t\t�ֵ�����Ϊ��%s \n", temptree->parent->nextstr[i]->data.name);
			}
			if (temptree->parent->parent != NULL)
			{
				Search1(temptree->parent);//������Ȳ���
			}
		}
		else
		{
			printf("\t\t��1��\n");//û��˫�ף���һ���ˣ�������
			printf("\t\t������%s  \n", temptree->data.name);
			if ((temptree->data.sex) == 1)
				printf("\t\t�Ա���\n");
			else if ((temptree->data.sex) == 0)
				printf("\t\t�Ա�Ů\n");
			printf("\t\t���ֵܽ��� \n");
		}
		//�����ż��Ϣ 
		if ((temptree->data.sex) == 1)
		{
			if (strcmp(temptree->data.spouse, "0") != 0)
				printf("\t\t̫̫������%s\n", temptree->data.spouse);
			else
				printf("\t\tû��̫̫��δ��\n");
		}
		else if ((temptree->data.sex) == 0)
		{
			if (strcmp(temptree->data.spouse, "0") != 0)
				printf("\t\t�ɷ�������%s\n", temptree->data.spouse);
			else
				printf("\t\tû���ɷ�δ��\n");
		}
		if (temptree->data.num != 0)//���Ӳ���
		{
			printf("\t\t������Ϣ��\n");
			for (int j = 0; j < temptree->data.num; j++)
			{
				if (strcmp(temptree->nextstr[j]->data.name, "0") == 0)
					continue;
				printf("\t\t\t��%d�����ӣ�������%s  \n", j + 1, temptree->nextstr[j]->data.name);
				if ((temptree->nextstr[j]->data.sex) == 1)
					printf("\t\t\t\t\t�Ա���\n");
				else if ((temptree->nextstr[j]->data.sex) == 0)
					printf("\t\t\t\t\t�Ա�Ů\n");

			}
			
		}
		for (int i = 0; i < temptree->data.num; i++)//����������
		{
			if (temptree->nextstr[i]->data.num != 0)
				Search3(temptree->nextstr[i]);
		}
		printf("\t\t----*----*----*----*----*----*----*----*----*----*----\n\n");
	}
	else if (Search2(S, temp, temptree))//����ڰ����Ǳߣ�����ͬ��
	{
		printf("\n\t\t��Ҫ�ҵ������ҵ�����Ϣ���£�\n");
		printf("\t\t������%s  \n", temptree->data.spouse);
		if ((temptree->data.sex) == 1)
		{
			printf("\t\t�Ա�Ů\n");
			printf("\n\t\t�޸�ĸ��Ϣ�����ڼ�����,Ҳ���ֵܽ����ڼ�����\n");
			printf("\n\t\t�ɷ�������%s\n", temptree->data.name);
		}
		else if ((temptree->data.sex) == 0)
		{
			printf("\t\t�Ա���\n");
			printf("\n\t\t�޸�ĸ��Ϣ�����ڼ����У�Ҳ���ֵܽ����ڼ�����\n");
			printf("\n\t\t̫̫������%s\n", temptree->data.name);
		}
		if (temptree->data.num != 0)
		{
			printf("\t\t������Ϣ��\n");
			for (int j = 0; j < temptree->data.num; j++)
			{
				if (strcmp(temptree->nextstr[j]->data.name, "0") == 0)
					continue;
				printf("\t\t\t��%d�����ӣ�������%s  \n", j + 1, temptree->nextstr[j]->data.name);
				if ((temptree->nextstr[j]->data.sex) == 1)
					printf("\t\t\t\t\t�Ա���\n");
				else if ((temptree->nextstr[j]->data.sex) == 0)
					printf("\t\t\t\t\t�Ա�Ů\n");

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
		printf("\t\t***�ü���ͼ��û��%s����˵���Ϣ��ȷ���Ƿ�������ȷ***\n\n", temp);
	}
}
bool Search(Pedtree* S, char temp[], Pedtree*& temptree)//��������
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
			if (Search(S->nextstr[i], temp, temptree))//�ݹ�
				return true;
		}
		return false;
	}
}
void Search1(Pedtree* S)//��������
{
	if (S->parent != NULL)
	{

		if (S->parent->data.sex == 1)
			printf("\t\t����(��˫����)Ϊ ���� ����Ϊ %s ��żΪ %s  \n", S->parent->data.name, S->parent->data.spouse);
		else
			printf("\t\t����Ϊ(��˫����) Ů�� ����Ϊ %s ��żΪ %s  \n", S->parent->data.name, S->parent->data.spouse);
	}
	if (S->parent->parent != NULL)
		Search1(S->parent);
}
bool Search2(Pedtree* S, char temp[], Pedtree*& temptree)//���Ұ��²���
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
void Search3(Pedtree* S)//���Һ��
{
	if (S->data.num != 0)
	{
		for (int i = 0; i < S->data.num;i++)
		{
			if (strcmp(S->nextstr[i]->data.spouse, "0") != 0)
				printf("\t\t�����%s ��żΪ%s\n", S->nextstr[i]->data.name,S->nextstr[i]->data.spouse);
			else
				printf("\t\t�����%s ����ż  \n", S->nextstr[i]->data.name);
		}
	}
	for (int i = 0; i < S->data.num; i++)
	{
		if (S->nextstr[i]->data.num != 0)
			Search3(S->nextstr[i]);
	}
}
void add_newpeople(Pedtree*& S)//����³�Ա
{
	fflush(stdin);
	int choice;
	while (1)
	{
		fflush(stdin);
		system("cls");
		welcome1();
		cout << "\t  ����ѡ��";
		cin >> choice;
		switch (choice)
		{
		case 1:
		{
			add_newchildren(S);//�º���
			int i;
			printf("\t\t���0����");
			scanf("%d", &i);
			break;
		}
		case 2:
		{
			add_newspouse(S);//�°���
			int i;
			printf("\t\t���0����");
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
	printf("\n\t\t������Ҫ�����Ů�ĸ�ĸ�����֣�");//���ҵ�˫��
	scanf("%s", children_name);
	if (Search(S, children_name, temptree) || Search2(S, children_name, temptree))
	{
		if (strcmp(temptree->data.spouse, "0") != 0)
		{
			Pedtree* Childtree;
			int num = temptree->data.num;
			Childtree = (Pedtree*)malloc(sizeof(Pedtree));//�����µĽ��
			temptree->nextstr[num] = Childtree;


			printf("\n\t\t������Ҫ��ӵ���Ů��������");
			scanf("%s", Childtree->data.name);
			printf("\n\t\t�����������Ů���Ա�1�У�0Ů����");
			fflush(stdin);//������̻�����  
			scanf("%d", &(Childtree->data.sex));
			(temptree->data.num)++;
			Childtree->parent = temptree;
			strcpy(Childtree->data.spouse, "0");
			Childtree->data.num = 0;

			printf("\n\n\t\t- - - - ��Ů��Ϣ��ӳɹ�- - - - - \n");
		}
		else
			printf("\n\t\t��ż�����ڣ����������Ů��Ϣ\n");
	}
	else
		printf("\n\n\t\t�����ڸø�ĸ��\n");
	fflush(stdin);//������̻����� 
}
void add_newspouse(Pedtree*& S)//�뺢�Ӳ���ͬ��
{
	fflush(stdin);
	system("cls");
	char pouse_name[Maxx];
	int f = 0;
	Pedtree *temptree=NULL;
	printf("\n\t\t������Ҫ����˵���ż�����֣�");
	scanf("%s", pouse_name);
	if (!Search(S, pouse_name, temptree))
	{
		printf("\n\n\t\t�����ڸ��ˣ�\n");
		f = 1;
	}
	else
	{
		if (strcmp(temptree->data.spouse, "0") == 0)
		{
			printf("\n\t\t�����˵�������");
			scanf("%s", temptree->data.spouse);

		}
		else
		{
			cout << "ʲô����С������ֱ�����㣡\n";
			f = 1;
		}
	}
	fflush(stdin);
	if(f==0)
		printf("\n\n\t\t- - - - ��ż��Ϣ��ӳɹ�- - - - - \n");
}
void  Delete(Pedtree* &S)//ɾ������
{
	fflush(stdin);//������̻����� 
	system("cls");
	char DE_name[Maxx];
	cout << "\t\t������Ҫɾ�����ˣ�";
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
		for (int i = 0; i < temptree->parent->data.num; i++)//�����ӽ��ǰ�ƣ���ֹ����ͷ�������
			if (strcmp(temptree->parent->nextstr[i]->data.name, "0") == 0)
			{
				for (int j = i; j <= temptree->parent->data.num; j++)
					temptree->parent->nextstr[j] = temptree->parent->nextstr[j + 1];
				temptree->parent->data.num--;//���Ӽ�һ
				break;
			}
		

		cout << "\t\tɾ���ɹ�\n";
		return;
	}
	else if(Search2(S,DE_name,temptree))
	{
		for (i = 0; i < temptree->data.num; i++)
			Deleteall(temptree->nextstr[i]);
		strcpy(temptree->data.spouse, "0");
		temptree->data.num = 0;
		printf("\n\t\tɾ���ɹ�");
	}
	else
	{
		printf("\n\n\t\t����������������������������������������������������\n\n");
		printf("\t\t***�ü���ͼ��û��%s����˵���Ϣ��ȷ���Ƿ�������ȷ***\n\n", DE_name);
		printf("\t\t������������������������������������������������������������\n\n");
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
void New_File(Pedtree* S)//�����ļ�
{
	FILE* fp;
	stack<Pedtree*> st;//���׽ṹջ��������ʱ�洢����
	stack<int> sp;//�ո�����ջ��Ϊ�˺ͽṹջͬ���������ո񷽱����
	Pedtree* p;
	int k = 0;
	fp = fopen("Myfamily104.txt", "w");
	fprintf(fp, "����\t����\t�Ա�\t���Ӹ���\n");
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
				k = k + 2;//����ո�
				for (int i = 0; i < p->data.num; i++)
				{

					st.push(p->nextstr[i]);//��ջ
					sp.push(k);//ͬ����ջ
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
		fflush(stdin);//������̻����� 
		system("cls");
		welcome();
		printf("\n");
		printf("\t\t����ѡ��:");
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
				printf("\t\t�������\n");
				flag = 1;
				int i;
				printf("\t\t���0����");
				scanf("%d", &i);
				break;
			}
			else
			{
				cout << "�Ѿ��������˼��ף����跴��" << endl;
				int j;
				cout << "�Ƿ����¹�����  1.��  2.��";
				cin >> j;
				switch (j)
				{
				case 1:
				{
					Deleteall(S);
					flag = 0;
					cout << "ɾ�����\n";
				}
				case 2:
				{
					break;
				}
				}
				int i;
				printf("\t\t���0����");
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
				printf("\t\t�������\n");
				flag = 1;
				printf("\t\t���0����");
				scanf("%d", &i);
				break;
			}
			else
			{
				cout << "�Ѿ��������˼��ף����跴��" << endl;
				int j;
				cout << "�Ƿ����¹�����  1.��  2.��";
				cin >> j;
				switch (j)
				{
				case 1:
				{
					Deleteall(S);
					flag = 0;
					cout << "ɾ�����\n";
				}
				case 2:
				{
					break;
				}
				}
				int i;
				printf("\t\t���0����");
				scanf("%d", &i);
				break;
			}
		}

		case 3:
		{
			if (flag == 0)
			{
				cout << "���Ƚ�������" << endl;
				int i;
				printf("\t\t���0����");
				scanf("%d", &i);
				break;

			}
			else
			{
				fflush(stdin);//������̻����� 
				system("cls");
				Search_result(S);
				int i;
				printf("\t\t���0����");
				scanf("%d", &i);
				break;

			}
		}
		case 4:
		{
			if (flag == 0)
			{
				cout << "���Ƚ�������" << endl;
				int i;
				printf("\t\t���0����");
				scanf("%d", &i);
				break;
			}
			else
			{
				fflush(stdin);//������̻����� 
				system("cls");
				add_newpeople(S);
				int i;
				printf("\t\t���0����");
				scanf("%d", &i);
				break;
			}

		}
		case 5:
		{
			if (flag == 0)
			{
				cout << "���Ƚ�������" << endl;
				int i;
				printf("\t\t���0����");
				scanf("%d", &i);
				break;
			}
			else
			{
				fflush(stdin);//������̻����� 
				system("cls");
				printf("\n\n\t\t����������Ҫ����Ϣ���£�\n");
				printf("\n\t\t---***---***---***---***---***---***---\n");
				Display(S);
				int i;
				printf("\t\t���0����");
				scanf("%d", &i);
				break;
			}
		}
		case 6:
		{
			if (flag == 0)
			{
				cout << "���Ƚ�������" << endl;
				int i;
				printf("\t\t���0����");
				scanf("%d", &i);
				break;
			}
			else
			{
				Delete(S);
				int i;
				printf("\t\t���0����");
				scanf("%d", &i);
				break;
			}
		}

		case 7:
		{
			if (flag == 0)
			{
				cout << "���Ƚ�������" << endl;
				int i;
				printf("\t\t���0����");
				scanf("%d", &i);
				break;
			}
			else
			{
				fflush(stdin);
				system("cls");
				New_File(S);
				cout << "�洢���\n";
				int i;
				printf("\t\t���0����");
				scanf("%d", &i);
				break;

			}

		}
		case 0:
		{
			cout << "\t\t��лʹ�ñ�С����" << endl;
			return 0;
		}
		default:
			cout << "\t\t�������ȷ�������԰ɣ�" << endl;
			break;
		}
	}

}
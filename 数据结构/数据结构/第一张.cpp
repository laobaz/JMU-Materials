#include<stdio.h>
#include<stdlib.h>
//单链表
#define CRE (STU*)malloc(sizeof(STU))
typedef struct student 
{
	int num;
	char names[100];
	double sorce;
	student* next;
}STU;
//头插法   输入和输出是相反的
STU* creates(int x)
{
	STU *head,*node;
	head = CRE;
	head->next = NULL;
	int i = 0;
	while (i<x)
	{
		node = CRE;
		scanf("%d%s%lf", &node->num, node->names, &node->sorce);
		node->next = head->next;
		head->next = node;
		i++;
	}
	//node->next = NULL;不需要这个
	return head;
}
//尾插法   输入和输出是相同的
STU* createss(int x)
{
	STU* head, * node, * end;
	head = NULL;
	int i = 0;
	while (i < x)
	{
		node = CRE;
		scanf("%d%s%lf", &node->num, node->names, &node->sorce);
		node->next = NULL;
		if (head == NULL)head = node;
		else end->next = node;
		end = node;
	}
	return head;
}
//插入操作
void charu(STU* head, int i)
{
	STU* p = head;
	STU* pr;
	int j = 0;
	while (j < i-1 && p->next != NULL)
	{
		j++;
		p = p->next;
	}
	if (p == head)
	{
		pr = CRE;
		scanf("%d%s%lf", &pr->num, pr->names, &pr->sorce);
		pr->next = head;
		head = pr;
	}
	else if (p ->next!= NULL)
	{
		pr = CRE;
		scanf("%d%s%lf", &pr->num, pr->names, &pr->sorce);
		pr->next = p->next;
		p->next = pr;
	}
	else
	{
		pr = CRE;
		scanf("%d%s%lf", &pr->num, pr->names, &pr->sorce);
		p->next = pr;
		pr->next = NULL;
	}
}
//删除操作
void shanchu(STU* head, int i)
{
	STU* pr = head,*p;
	int j = 1;
	while (j<i&&pr!=NULL)
	{
		p = pr;
		pr = pr->next;
		j++;
	}
	if (pr == head)
	{
		head = head->next;
		free(pr);
	}
	else if (pr != NULL)
	{
		p->next = pr->next;
		free(pr);
	}
}
//双链表
#define CRES (STUS*)malloc(sizeof(STUS))
typedef struct students
{
	int num;
	students* prior;
	students* next;
}STUS;
//建立操作
STUS* CREATES(int x)
{
	STUS* head, * end, * node;
	int i = 1;//当设计头节点为空时，i=0
	while (i < x)
	{
		node = CRES;
		scanf("%d%s%lf", &node->num);
		node->next = NULL;
		if (head == NULL)head = node;
		else
		{
			end->next = node;
			node->prior = end;//node的前指针指向end，也就是node的上个循环的结构体
		}
		end = node;
	}
	return head;
}
//插入操作
void charu2(STUS* head, int i,STUS*s)
{
	STUS *p = head;
	int j = 0;
	while (j < i && p != NULL)
	{
		j++;
		p = p->next;
	}
	if (p != NULL)
	{
		s->next = p->next;
		p->next = s;
		p->next->prior = s;//下一位的前指针指向s
		s->prior = p;//s的前指针指向p
	}
}
//删除操作(删除p)
void shanchu2(STUS* head, int i)
{
	STUS* p = head, *pr;
	int j = 1;
	while (j < i && p != NULL)
	{
		pr = p;
		p = p->next;
		j++;
	}
	if (p != NULL)
	{
		pr->next = p->next;
		p->next->prior = pr;
		delete p;
	}
}
int main()
{
	return 0;
}
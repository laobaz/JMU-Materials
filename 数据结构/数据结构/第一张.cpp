#include<stdio.h>
#include<stdlib.h>
//������
#define CRE (STU*)malloc(sizeof(STU))
typedef struct student 
{
	int num;
	char names[100];
	double sorce;
	student* next;
}STU;
//ͷ�巨   �����������෴��
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
	//node->next = NULL;����Ҫ���
	return head;
}
//β�巨   ������������ͬ��
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
//�������
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
//ɾ������
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
//˫����
#define CRES (STUS*)malloc(sizeof(STUS))
typedef struct students
{
	int num;
	students* prior;
	students* next;
}STUS;
//��������
STUS* CREATES(int x)
{
	STUS* head, * end, * node;
	int i = 1;//�����ͷ�ڵ�Ϊ��ʱ��i=0
	while (i < x)
	{
		node = CRES;
		scanf("%d%s%lf", &node->num);
		node->next = NULL;
		if (head == NULL)head = node;
		else
		{
			end->next = node;
			node->prior = end;//node��ǰָ��ָ��end��Ҳ����node���ϸ�ѭ���Ľṹ��
		}
		end = node;
	}
	return head;
}
//�������
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
		p->next->prior = s;//��һλ��ǰָ��ָ��s
		s->prior = p;//s��ǰָ��ָ��p
	}
}
//ɾ������(ɾ��p)
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
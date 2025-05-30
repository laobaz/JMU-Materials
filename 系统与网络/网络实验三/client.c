#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>


//�����ڴ��ṹ��
typedef struct memory_Block {
	void* start;  //��ʼ��ַ
	void* end;    //������ַ
	size_t size;  //��С
	struct memory_Block* next;
	int num;     //���̺�
}memoryBlock;

//��������ڴ��ṹ��
typedef struct free_Block
{
	void* start;  //��ʼ��ַ
	void* end;    //������ַ
	size_t size;  //��С
	struct free_Block* next;  //��һ�����п�
}FreeBlock;

//����ҳ��,���ڰ��߼���ַת��Ϊ�����ַ
//һ������һ��ҳ��
typedef struct page_Table
{
	int num;
	void* page[10];
	struct page_Table* next;
}Page_Table;
size_t page_table_size;

//����ȫ�ֱ�������ʾ������ڴ�ռ�
void* memory_pool;
size_t memory_size;

//������ʹ���ڴ������ͷָ��Ϳ����ڴ������ͷָ��
memoryBlock* used_list;
FreeBlock* free_list;
Page_Table* page_table;


void dealloc(void* ptr);

//��ʼ���ڴ��
void init_memory_pool(size_t size) {
	memory_size = size;
	memory_pool = malloc(memory_size);//��ŷ���ռ��ʼ��ַ
	if (memory_pool == NULL) {
		printf("1.ʧ��");
		exit(EXIT_FAILURE);
	}
}
//��ʼ�������ڴ�����
void init_free_list() {
	free_list = malloc(sizeof(FreeBlock));
	if (free_list == NULL) {
		printf("2.ʧ��");
		exit(EXIT_FAILURE);
	}
	free_list->start = memory_pool;  //��ʼΪ�ڴ�ص�ͷ��ַ
	free_list->end = (int)memory_pool +memory_size;//��βΪ�ڴ�ص�β��ַ
	free_list->size = memory_size;
	free_list->next = NULL;//��ʱû�з���

}

//��ʼ��ʹ������
void init_used_list() {
	used_list = NULL;
}

//��ʼ��ҳ��
void init_page_table(size_t size) {
	page_table_size = size;
	page_table = NULL;
	
}

//�����ڴ�
void* alloc(size_t size, int num) {
	FreeBlock* pre = NULL;
	FreeBlock* cur = free_list;
	while (cur != NULL && cur->size < size) {//Ѱ�ҷ���Ҫ��Ŀ����ڴ��
		pre = cur;
		cur = cur->next;
	}
	if (cur != NULL) {
		//�ҵ����㹻�Ŀռ䡣ֱ�ӷ���
		memoryBlock* block = malloc(sizeof(memoryBlock));
		if (block == NULL) {
			printf("4.ʧ��");
			exit(EXIT_FAILURE);
		}
		block->start = cur->start;
		block->end = (int)cur->start + size;
		block->size = size;
		block->num = num;
		block->next = used_list;//ͷ�巨
		used_list = block;
		cur->start = block->end;
		cur->size = cur->size - size;
		printf("���%d�Ľ��̣���ʼ��ַ:%p,��β��ַ:%p ��С:%zu bytes�����ڴ�\n", block->num, block->start, block->end, block->size);
		if (cur->size == 0) {
			if (pre == NULL)
				free_list = cur->next;//ͷ��Ϊ��һ��
			else
				pre->next = cur->next;//����cur
			free(cur);
		}

		//����ҳ��
		//for (size_t i = 0; i < page_table_size; i++) {
		//	if (page_table[i] == NULL) {//���ҳΪ��
		//		page_table[i] = block->start;//���������ַ
		//		printf("�����ַ%p���ڴ��ĵ�ַ�洢�ڵ�%zuҳ��\n", block->start, i);
		//		break;
		//	}
		//}
		Page_Table* ppre = NULL;
		Page_Table* pcur = page_table;
		while (pcur != NULL && pcur->num != block->num) {
			ppre = pcur;
			pcur = pcur->next;
		}
		if (pcur != NULL) {
			for (size_t i = 0; i < page_table_size; i++) {
				if (pcur->page[i] == 0) {//���ҳΪ��
					pcur->page[i] = block->start;//���������ַ
					printf("�����ַ%p���ڴ��ĵ�ַ�洢�ڵ�%zuҳ��\n", block->start, i);
					break;
				}
			}
		}
		else {
			Page_Table* page_Table_new = malloc(sizeof(Page_Table));//�����ڴ�
			memset(page_Table_new->page, 0, sizeof(page_Table_new->page));//ҳ������Ϊ0
			page_Table_new->num = block->num;//д����
			page_Table_new->page[0] = block->start;//д�뿪ʼ��ַ
			page_Table_new->next = page_table;//ͷ��
			page_table = page_Table_new;
			printf("�����ַ%p���ڴ��ĵ�ַ�洢�ڵ�0ҳ��\n", block->start);
		}
		return block->start;//���ؿ�ʼ��ַ
	}
	else {
		printf("���%d�Ľ��� ��С:%zu bytes�����ڴ�\n",num,size);
		printf("û���㹻�Ŀռ䣬ʹ�����������㷨��ʹ�õ��������ͷ�һ�����������ڴ���ͷ�\n");
		//û���㹻�Ŀռ䣬ʹ�����������㷨��ʹ�õ��������ͷ�һ�����������ڴ���ͷ�
		memoryBlock* mprev = NULL;
		memoryBlock* mcur = used_list;
		//ͷ�巨��ͷ��β��
		while (mcur != NULL && mcur->size < size) {//�ҵ�ͷ��
			mprev = mcur;
			mcur = mcur->next;
		}
		if (mcur != NULL) {//����ɾ������
			dealloc(mcur->start);
			return alloc(size, num);//�ٴγ���
		}
		else {
			printf("����ʧ��\n");
		}
	}

}


//�ͷ��ڴ�

void dealloc(void* ptr) {
	memoryBlock* pre = NULL;
	memoryBlock* cur = used_list;
	while (cur!=NULL&&cur->start!=ptr)
	{
		pre = cur;
		cur = cur->next;
	}
	if (cur != NULL) {
		//�ҵ���Ҫ�ͷŵ��ڴ��
		if (pre == NULL)//����ͷ
			used_list = cur->next;
		else
			pre->next = cur->next;
		FreeBlock* freeblock = malloc(sizeof(FreeBlock));
		if (freeblock == NULL) {
			printf("6.ʧ��");
			exit(EXIT_FAILURE);
		}
		//���ջ������ڴ�Ϊ��Ƭ��
		printf("���%d�Ľ��̣���ʼ��ַ:%p,��β��ַ:%p ��С:%zu bytes��������\n", cur->num, cur->start, cur->end, cur->size);
		freeblock->start = (int)cur->start;
		freeblock->end = cur->end;
		freeblock->size = cur->size;
		freeblock->next = free_list;//ͷ�巨
		free_list = freeblock;
		//����ҳ��
		
		/*for (size_t i = 0; i < page_table_size; i++) {
			if (page_table[i] == cur->start) {
				page_table[i] = NULL;
				printf("���%d�Ľ���,�����ַ%p���ڴ��ĵ�ַ�ӵ�%zuҳ���ͷ�\n", cur->num,cur->start,i);
				break;
			}
		}*/
		Page_Table* ppre = NULL;
		Page_Table* pcur = page_table;
		while (pcur != NULL && pcur->num != cur->num) {
			ppre = pcur;
			pcur = pcur->next;
		}
		if (pcur != NULL) {
			for (size_t i = 0; i < page_table_size; i++)
			{
				if (pcur->page[i] == cur->start) {
					pcur->page[i] =0;
					printf("���%d�Ľ���,�����ַ%p���ڴ��ĵ�ַ�ӵ�%zuҳ���ͷ�\n", cur->num, cur->start, i);
					break;
				}
			}
			int flag = 0;
			for (size_t i = 0; i < page_table_size; i++) {
				if (pcur->page[i] != 0)
					flag = 1;
			}
			if (flag == 0) {
				if (ppre == NULL) {
					page_table = pcur->next;
				}
				else {
					ppre->next = pcur->next;
				}
				//free(pcur);
			}
		}
		//�ϲ����ڵĿ����ڴ��
		FreeBlock* pre = NULL;
		FreeBlock* cur = free_list;
		FreeBlock* temp = free_list;
		while (temp != NULL) {
			while (cur != NULL) {
				if (pre!=NULL&&temp->end == cur->start)//�ж��Ƿ�������һ��
				{
					temp->end = cur->end;
					temp->size = temp->size + cur->size;
					pre->next = cur->next;
					free(cur);
					cur = pre->next;
				}
				else
				{
					pre = cur;
					cur = cur->next;
				}
			}
			temp = temp->next;
			pre = NULL;
			cur = free_list;
		}
	
	}
	
	
}
//�������̺�����ڴ�
void dealloc_all(int num) {
	memoryBlock* cur = used_list;
	while (cur != NULL  && cur->num != num)
	{
		cur = cur->next;
	}
	if (cur != NULL) {
		dealloc(cur->start);
		dealloc_all(num);
	}

}
//��ӡ�ڴ���������ʹ�����
void print_memory_status() {
	printf("�ڴ����:\n");
	printf("�ܹ��ڴ�:%zu bytes\n",memory_size);
	size_t used=0, free=0;
	memoryBlock* memoryblock=used_list;
	FreeBlock* freeblock=free_list;
	while (memoryblock != NULL) {
		used = used + memoryblock->size;
		memoryblock = memoryblock->next;
	}
	while (freeblock != NULL) {
		free = free + freeblock->size;
		freeblock = freeblock->next;
	}
	printf("ʹ�õ��ڴ�:%zu bytes\n", used);
	printf("���е��ڴ�:%zu bytes\n", free);
	printf("ʹ�õ��ڴ��:\n");
	memoryblock = used_list;
	freeblock = free_list;
	while (memoryblock != NULL) {
		printf("���%d�Ľ��̣���ʼ��ַ:%p,��β��ַ:%p ��С:%zu bytes\n", memoryblock->num,memoryblock->start, memoryblock->end, memoryblock->size);
		memoryblock = memoryblock->next;
	}
	printf("���е��ڴ��:\n");
	while (freeblock != NULL) {
		printf("��ʼ��ַ:%p,��β��ַ:%p ��С:%zu bytes\n", freeblock->start, freeblock->end, freeblock->size);
		freeblock = freeblock->next;
	}
}

//��ӡҳ��
void print_page_table() {
	/*printf("page table:\n");*/
	//for (size_t i = 0; i < page_table_size; i++) {
	//	if (page_table[i] == NULL){}
	//		//printf("Page %zu free\n", i);
	//	else
	//		printf("Page %zu alloc (��ʼ��ַ��%p)\n", i,page_table[i]);
	//}

	Page_Table* pcur = page_table;
	while (pcur != NULL) {
		printf("%d��ҳ��\n", pcur->num);
		for (size_t i = 0; i < page_table_size; i++) {
			if (pcur->page[i] == 0) {}
			//printf("Page %zu free\n", i);
			else
				printf("Page %zu alloc (��ʼ��ַ��%p)\n", i, pcur->page[i]);
		}
		printf("\n");
		pcur = pcur->next;
	}
}

int main() {
	init_memory_pool(1024);//��ʼ���ڴ��
	init_free_list();//��ʼ�������б�
	init_used_list();//��ʼ��ʹ���б�
	init_page_table(10);//��ʼ��ҳ��
	void* ptr[4]; //ģ�����
	srand((unsigned int)time(NULL));
	int size,num;
	for (int i = 0; i < 10; i++) {
		size= rand() % 300 + 1;//����ڴ�
		num = rand() % 4;//������̺�
		ptr[num]=alloc(size, num);
		print_memory_status();
		printf("\n");
		printf("\n");
	}
	dealloc(ptr[0]);//���һ���ڴ��
	dealloc_all(1);//������������ڴ��
	print_memory_status();
	printf("\n");
	print_page_table();
	printf("ͨ��ҳ�����ڴ�飬ɾ�����е�ʹ���ڴ�\n");
	Page_Table* cur=page_table;
	while (cur!= NULL) {
		for (size_t i = 0; i < page_table_size; i++) {
			if (cur->page[i] == 0) {}
			else
				dealloc(cur->page[i]);
			
		}
		cur = cur->next;
	}
	print_memory_status();
	print_page_table();
	
}

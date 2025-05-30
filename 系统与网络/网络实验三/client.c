#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>


//定义内存块结构体
typedef struct memory_Block {
	void* start;  //初始地址
	void* end;    //结束地址
	size_t size;  //大小
	struct memory_Block* next;
	int num;     //进程号
}memoryBlock;

//定义空闲内存块结构体
typedef struct free_Block
{
	void* start;  //初始地址
	void* end;    //结束地址
	size_t size;  //大小
	struct free_Block* next;  //下一个空闲块
}FreeBlock;

//定义页表,用于把逻辑地址转化为物理地址
//一个进程一张页表
typedef struct page_Table
{
	int num;
	void* page[10];
	struct page_Table* next;
}Page_Table;
size_t page_table_size;

//定义全局变量，表示整体的内存空间
void* memory_pool;
size_t memory_size;

//定义已使用内存链表的头指针和空闲内存链表的头指针
memoryBlock* used_list;
FreeBlock* free_list;
Page_Table* page_table;


void dealloc(void* ptr);

//初始化内存池
void init_memory_pool(size_t size) {
	memory_size = size;
	memory_pool = malloc(memory_size);//存放分配空间初始地址
	if (memory_pool == NULL) {
		printf("1.失败");
		exit(EXIT_FAILURE);
	}
}
//初始化空闲内存链表
void init_free_list() {
	free_list = malloc(sizeof(FreeBlock));
	if (free_list == NULL) {
		printf("2.失败");
		exit(EXIT_FAILURE);
	}
	free_list->start = memory_pool;  //开始为内存池的头地址
	free_list->end = (int)memory_pool +memory_size;//结尾为内存池的尾地址
	free_list->size = memory_size;
	free_list->next = NULL;//暂时没有分配

}

//初始化使用链表
void init_used_list() {
	used_list = NULL;
}

//初始化页表
void init_page_table(size_t size) {
	page_table_size = size;
	page_table = NULL;
	
}

//分配内存
void* alloc(size_t size, int num) {
	FreeBlock* pre = NULL;
	FreeBlock* cur = free_list;
	while (cur != NULL && cur->size < size) {//寻找符合要求的空闲内存块
		pre = cur;
		cur = cur->next;
	}
	if (cur != NULL) {
		//找到了足够的空间。直接分配
		memoryBlock* block = malloc(sizeof(memoryBlock));
		if (block == NULL) {
			printf("4.失败");
			exit(EXIT_FAILURE);
		}
		block->start = cur->start;
		block->end = (int)cur->start + size;
		block->size = size;
		block->num = num;
		block->next = used_list;//头插法
		used_list = block;
		cur->start = block->end;
		cur->size = cur->size - size;
		printf("编号%d的进程，开始地址:%p,结尾地址:%p 大小:%zu bytes存入内存\n", block->num, block->start, block->end, block->size);
		if (cur->size == 0) {
			if (pre == NULL)
				free_list = cur->next;//头改为下一个
			else
				pre->next = cur->next;//跳过cur
			free(cur);
		}

		//更新页表
		//for (size_t i = 0; i < page_table_size; i++) {
		//	if (page_table[i] == NULL) {//如果页为空
		//		page_table[i] = block->start;//存入物理地址
		//		printf("物理地址%p的内存块的地址存储在第%zu页中\n", block->start, i);
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
				if (pcur->page[i] == 0) {//如果页为空
					pcur->page[i] = block->start;//存入物理地址
					printf("物理地址%p的内存块的地址存储在第%zu页中\n", block->start, i);
					break;
				}
			}
		}
		else {
			Page_Table* page_Table_new = malloc(sizeof(Page_Table));//分配内存
			memset(page_Table_new->page, 0, sizeof(page_Table_new->page));//页表设置为0
			page_Table_new->num = block->num;//写入编号
			page_Table_new->page[0] = block->start;//写入开始地址
			page_Table_new->next = page_table;//头插
			page_table = page_Table_new;
			printf("物理地址%p的内存块的地址存储在第0页中\n", block->start);
		}
		return block->start;//返回开始地址
	}
	else {
		printf("编号%d的进程 大小:%zu bytes存入内存\n",num,size);
		printf("没有足够的空间，使用最先适配算法从使用的链表中释放一个最早分配的内存块释放\n");
		//没有足够的空间，使用最先适配算法从使用的链表中释放一个最早分配的内存块释放
		memoryBlock* mprev = NULL;
		memoryBlock* mcur = used_list;
		//头插法的头在尾部
		while (mcur != NULL && mcur->size < size) {//找到头部
			mprev = mcur;
			mcur = mcur->next;
		}
		if (mcur != NULL) {//调用删除操作
			dealloc(mcur->start);
			return alloc(size, num);//再次尝试
		}
		else {
			printf("分配失败\n");
		}
	}

}


//释放内存

void dealloc(void* ptr) {
	memoryBlock* pre = NULL;
	memoryBlock* cur = used_list;
	while (cur!=NULL&&cur->start!=ptr)
	{
		pre = cur;
		cur = cur->next;
	}
	if (cur != NULL) {
		//找到了要释放的内存块
		if (pre == NULL)//链表头
			used_list = cur->next;
		else
			pre->next = cur->next;
		FreeBlock* freeblock = malloc(sizeof(FreeBlock));
		if (freeblock == NULL) {
			printf("6.失败");
			exit(EXIT_FAILURE);
		}
		//回收回来的内存为碎片的
		printf("编号%d的进程，开始地址:%p,结尾地址:%p 大小:%zu bytes结束进程\n", cur->num, cur->start, cur->end, cur->size);
		freeblock->start = (int)cur->start;
		freeblock->end = cur->end;
		freeblock->size = cur->size;
		freeblock->next = free_list;//头插法
		free_list = freeblock;
		//更新页表
		
		/*for (size_t i = 0; i < page_table_size; i++) {
			if (page_table[i] == cur->start) {
				page_table[i] = NULL;
				printf("编号%d的进程,物理地址%p的内存块的地址从第%zu页中释放\n", cur->num,cur->start,i);
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
					printf("编号%d的进程,物理地址%p的内存块的地址从第%zu页中释放\n", cur->num, cur->start, i);
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
		//合并相邻的空闲内存块
		FreeBlock* pre = NULL;
		FreeBlock* cur = free_list;
		FreeBlock* temp = free_list;
		while (temp != NULL) {
			while (cur != NULL) {
				if (pre!=NULL&&temp->end == cur->start)//判断是否相连在一起
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
//结束进程后，清空内存
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
//打印内存空闲情况和使用情况
void print_memory_status() {
	printf("内存情况:\n");
	printf("总共内存:%zu bytes\n",memory_size);
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
	printf("使用的内存:%zu bytes\n", used);
	printf("空闲的内存:%zu bytes\n", free);
	printf("使用的内存块:\n");
	memoryblock = used_list;
	freeblock = free_list;
	while (memoryblock != NULL) {
		printf("编号%d的进程，开始地址:%p,结尾地址:%p 大小:%zu bytes\n", memoryblock->num,memoryblock->start, memoryblock->end, memoryblock->size);
		memoryblock = memoryblock->next;
	}
	printf("空闲的内存块:\n");
	while (freeblock != NULL) {
		printf("开始地址:%p,结尾地址:%p 大小:%zu bytes\n", freeblock->start, freeblock->end, freeblock->size);
		freeblock = freeblock->next;
	}
}

//打印页表
void print_page_table() {
	/*printf("page table:\n");*/
	//for (size_t i = 0; i < page_table_size; i++) {
	//	if (page_table[i] == NULL){}
	//		//printf("Page %zu free\n", i);
	//	else
	//		printf("Page %zu alloc (开始地址：%p)\n", i,page_table[i]);
	//}

	Page_Table* pcur = page_table;
	while (pcur != NULL) {
		printf("%d的页表：\n", pcur->num);
		for (size_t i = 0; i < page_table_size; i++) {
			if (pcur->page[i] == 0) {}
			//printf("Page %zu free\n", i);
			else
				printf("Page %zu alloc (开始地址：%p)\n", i, pcur->page[i]);
		}
		printf("\n");
		pcur = pcur->next;
	}
}

int main() {
	init_memory_pool(1024);//初始化内存池
	init_free_list();//初始化空闲列表
	init_used_list();//初始化使用列表
	init_page_table(10);//初始化页表
	void* ptr[4]; //模拟进程
	srand((unsigned int)time(NULL));
	int size,num;
	for (int i = 0; i < 10; i++) {
		size= rand() % 300 + 1;//随机内存
		num = rand() % 4;//随机进程号
		ptr[num]=alloc(size, num);
		print_memory_status();
		printf("\n");
		printf("\n");
	}
	dealloc(ptr[0]);//清除一个内存块
	dealloc_all(1);//清除进程所有内存块
	print_memory_status();
	printf("\n");
	print_page_table();
	printf("通过页表找内存块，删除所有的使用内存\n");
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

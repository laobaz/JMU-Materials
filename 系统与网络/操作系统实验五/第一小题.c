#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>
#include <semaphore.h>
#include <unistd.h>
void* gone();
sem_t mutex;  //��ľ��ʵ�ֻ������
 int i=0;     //����ȫ�ּ���������۲졣 
int main() {
    sem_init(&mutex, 0, 1);
    int  pc;
    pthread_t p;
    for ( ;i < 15; i++) {
        pc = pthread_create(&p, NULL, gone, NULL);    
        if (pc != 0 ) 
            printf("Thread creation failure!\n");
        
    }
    sleep(2);
    return EXIT_SUCCESS;
}
int count=0;
void *gone(){	
		sem_wait(&mutex);
		count++;//ȫ�ֹ�������++
		printf("��%d�Ž�\n",count);
	   sleep(0.1);
		printf("��%d�ų�\n",count);
		sem_post(&mutex); 
	
}

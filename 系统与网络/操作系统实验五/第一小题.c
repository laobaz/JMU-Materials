#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>
#include <semaphore.h>
#include <unistd.h>
void* gone();
sem_t mutex;  //独木桥实现互斥访问
 int i=0;     //用于全局计数，方便观察。 
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
		count++;//全局过桥人数++
		printf("第%d号进\n",count);
	   sleep(0.1);
		printf("第%d号出\n",count);
		sem_post(&mutex); 
	
}

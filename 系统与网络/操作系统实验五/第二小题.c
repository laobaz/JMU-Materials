#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>

#include <time.h>
#include <semaphore.h>
#include <unistd.h>
void* east();
void* west();
sem_t mutex;       //独木桥实现互斥访问
sem_t temp;        //用于访问判断的互斥 
int eastCount = 0; //记录当前桥上东方向的人
int westCount = 0; //记录当前桥上西方向的人
int flag=0;
//int change=0; 
int main() {
    sem_init(&mutex, 0, 1);
    sem_init(&temp, 0, 1);
    int i, pc1, pc2;
    pthread_t p;
    for (i = 0; i < 7; i++) {
        
        pc2 = pthread_create(&p, NULL, east, NULL);
        pc1 = pthread_create(&p, NULL, west, NULL);
        if (pc1 != 0 || pc2 != 0) 
            printf("Thread creation failure!\n");
        
    }
    sleep(1);
    for (i = 0; i < 7; i++) {
        
        pc2 = pthread_create(&p, NULL, west, NULL);
        pc1 = pthread_create(&p, NULL, east, NULL);
        if (pc1 != 0 || pc2 != 0) 
            printf("Thread creation failure!\n");
        
    }
    
    sleep(50);
    return EXIT_SUCCESS;
}
void* east() {
      sem_wait(&temp);  //上锁防止多个线程同时访问桥的状态，导致死锁 
     if(flag==0){//桥未使用，可以进 
         flag=1;
         sem_wait(&mutex);
		 eastCount++;   
		 printf("东方进\n");
  	      printf("当前桥上东方人数为%d\n",eastCount);   
         sem_post(&temp);//判断完解开临时的锁 
     }
     else if(eastCount!=0){//桥上的自己的人，可以进 
	 	eastCount++;
	 	printf("东方进\n");
  	      printf("当前桥上东方人数为%d\n",eastCount);   
	 	sem_post(&temp);
	 } 
	 else{  //桥在被使用，而且没有自己的人，循环等待 
        sem_post(&temp); //临时上锁，防止同时访问，导致死锁 
        again1: 
	 	while(flag!=0&&eastCount==0){}
	    sem_wait(&temp);
	 	 if(flag==0) {
		 flag=1;//等待结束后，自己立刻上桥，上锁，防止对面又上人 
		 sem_wait(&mutex);	
     	}
     	else if(eastCount==0){//不是自己人在上面 
     		sem_post(&temp); //别人先上了 ，回去继续等待 
     		goto again1;
		}
		 
		 eastCount++;
	 	 printf("东方进\n");
         printf("当前桥上东方人数为%d\n",eastCount);   	
		 sem_post(&temp);  
	 } 
	 
     
	//过桥时间 
	sleep(0.1);
	
    sem_wait(&temp);
    eastCount--;
    printf("东方出\n");
     printf("当前桥上东方人数为%d\n",eastCount);
    if (eastCount == 0){
    	sem_post(&mutex);
    	flag=0;
	}   
     sem_post(&temp);
   
}

void* west() {
        sem_wait(&temp);  //上锁防止多个线程同时访问桥的状态，导致死锁 
     if(flag==0){//桥未使用，可以进 
        flag=1;
        sem_wait(&mutex);
		 westCount++;   
		 printf("西方进\n");
  	      printf("当前桥上西方人数为%d\n",westCount);   
         sem_post(&temp);//判断完解开临时的锁 
     }
     else if(westCount!=0){//桥上的自己的人，可以进 
	 	westCount++;   
		 printf("西方进\n");
  	      printf("当前桥上西方人数为%d\n",westCount);   
	 	sem_post(&temp);
	 } 
	 else{  //桥在被使用，而且没有自己的人，循环等待 
        sem_post(&temp); 
        again2:
	 	while(westCount==0&&flag!=0){} 
	 	sem_wait(&temp);
	 	 if(flag==0) {
		 flag=1;//等待结束后，自己立刻上桥，上锁，防止对面又上人 
		 sem_wait(&mutex);	
     	}    	
     	else if(westCount==0){//不是自己人在上面 
     	sem_post(&temp); //别人先上了 ，回去继续等待 
     		goto again2;
		 }
		 westCount++;   
		 printf("西方进\n");
  	      printf("当前桥上西方人数为%d\n",westCount); 	  
  	      sem_post(&temp);
     }



    sleep(0.1);

   
    sem_wait(&temp);
    westCount--;
     printf("西方出\n");
    printf("当前桥上西方人数为%d\n",westCount);
    if (westCount == 0){
    	sem_post(&mutex);
    	flag=0;
	}
    sem_post(&temp);
     
}

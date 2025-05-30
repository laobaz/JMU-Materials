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
sem_t mutex;  //��ľ��ʵ�ֻ������
sem_t temp;
int eastCount = 0; //��ǵ�ǰ���ϴӶ���������
int westCount = 0; //��ǵ�ǰ���ϴ����򶫵���
int flag=0;       

int main() {
    sem_init(&mutex, 0, 1);
    sem_init(&temp, 0, 1);
    int i, pc1, pc2;
    pthread_t p;
    for (i = 0; i < 3; i++) {
        
        pc2 = pthread_create(&p, NULL, west, NULL);
        pc1 = pthread_create(&p, NULL, east, NULL);
        if (pc1 != 0 || pc2 != 0) 
            printf("Thread creation failure!\n");
        
    }
    
    for (i = 0; i < 3; i++) {
        
        pc2 = pthread_create(&p, NULL, east, NULL);
        pc1 = pthread_create(&p, NULL, west, NULL);
        if (pc1 != 0 || pc2 != 0) 
            printf("Thread creation failure!\n");
        
    }
   
    sleep(5);
    return EXIT_SUCCESS;
}
void* east() {
     sem_wait(&temp);  //������ֹ����߳�ͬʱ�����ŵ�״̬���������� 
     if(flag==0){//��δʹ�ã����Խ� 
         flag=1;
         sem_wait(&mutex);
		 eastCount++;   
		 printf("������\n");
  	      printf("��ǰ���϶�������Ϊ%d\n",eastCount);   
         sem_post(&temp);//�ж���⿪��ʱ���� 
     }
     else if(eastCount!=0){//���ϵ��Լ����ˣ����Խ� 
	 	eastCount++;
	 	printf("������\n");
  	      printf("��ǰ���϶�������Ϊ%d\n",eastCount);   
	 	sem_post(&temp);
	 } 
	 else{  //���ڱ�ʹ�ã�����û���Լ����ˣ�ѭ���ȴ� 
        sem_post(&temp); 
        again1: 
	 	while(flag!=0&&eastCount==0){}
	    sem_wait(&temp);//��ʱ��������ֹͬʱ���ʣ��������� 
	 	 if(flag==0) {
		 flag=1;//�ȴ��������Լ��������ţ���������ֹ���������� 
		 sem_wait(&mutex);
     	}
     	else if(eastCount==0){//�����Լ��������� 
     		sem_post(&temp); //���������� ����ȥ�����ȴ� 
     		goto again1;
		 }
		 eastCount++;
	 	 printf("������\n");
         printf("��ǰ���϶�������Ϊ%d\n",eastCount);   	
		 sem_post(&temp);  
	 } 
		 
	//����ʱ�� 
	sleep(0.1);
    sem_wait(&temp);
    eastCount--;
    printf("������\n");
     printf("��ǰ���϶�������Ϊ%d\n",eastCount);
    if (eastCount == 0){
    	sem_post(&mutex);
    	flag=0;
	}   
    sem_post(&temp);
   
}

void* west() {
    sem_wait(&temp);
    if(flag==0){
    	sem_wait(&mutex);
    	flag=1;
    	westCount++;	
	 	 printf("������\n");
         printf("��ǰ������������Ϊ%d\n",westCount);  
		 sem_post(&temp); 	
	}
     else{
     sem_post(&temp);
     again2:
     while(flag==1){}
         sem_wait(&temp);
          if(flag==0&&westCount==0) {
		    flag=1;
		    sem_wait(&mutex);
     	}
     	else{
     		sem_post(&temp); //���������� ����ȥ�����ȴ� 
     		goto again2;
		 }
		 westCount++;
	 	 printf("������\n");
         printf("��ǰ������������Ϊ%d\n",westCount);   	
		 sem_post(&temp);  
     	
	}
  	 
    sleep(0.1);
    sem_wait(&temp);
    westCount--;
     printf("������\n");
    printf("��ǰ������������Ϊ%d\n",westCount);
   	sem_post(&mutex);
   	flag=0;
    sem_post(&temp);
     
}

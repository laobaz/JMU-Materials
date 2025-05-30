#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
//#include <sys/wait.h>

int count = 0;
int main() {

	//����һ���ӽ��� 
	pid_t p1 = fork();
	count++;
	if (p1 < 0) {//����ʧ�� 
		exit(-1);
	}
	else if (p1 == 0) {//������ӽ��� 
		printf("Child :pid=%d \t ppid =%d \t count=%d\n",getpid(),getppid(),count);
		sleep(5);
	}
	else {
		printf("Parent :pid=%d \t ppid =%d \t count=%d\n",getpid(),getppid(),count);
		//���������ֹ�ӽ����ٽ���һ���ӽ��� 
		pid_t p2 = fork();//�ڸ��������ڽ���һ���ӽ���
		count++; 
		if (p2 < 0) {//����ʧ�� 
			exit(-1);
		}
		else if (p2 == 0) {//������ӽ��� 
			printf("Child :pid=%d \t ppid =%d \t count=%d\n",getpid(),getppid(),count);
			sleep(5);
		}

		else {
			printf("Parent :pid=%d \t ppid =%d \t count=%d\n",getpid(),getppid(),count);
			sleep(5);
		}
		sleep(5);
	}
	//printf("In the end :count=%d\n",count);
	return 0;
}

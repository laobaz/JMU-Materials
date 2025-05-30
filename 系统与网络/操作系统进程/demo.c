#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
//#include <sys/wait.h>

int count = 0;
int main() {

	//常见一个子进程 
	pid_t p1 = fork();
	count++;
	if (p1 < 0) {//创建失败 
		exit(-1);
	}
	else if (p1 == 0) {//如果是子进程 
		printf("Child :pid=%d \t ppid =%d \t count=%d\n",getpid(),getppid(),count);
		sleep(5);
	}
	else {
		printf("Parent :pid=%d \t ppid =%d \t count=%d\n",getpid(),getppid(),count);
		//放在这里防止子进程再建立一个子进程 
		pid_t p2 = fork();//在父进程中在建立一个子进程
		count++; 
		if (p2 < 0) {//创建失败 
			exit(-1);
		}
		else if (p2 == 0) {//如果是子进程 
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

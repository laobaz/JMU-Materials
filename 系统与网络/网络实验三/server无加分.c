#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<pthread.h>
#include<errno.h> 
#include<netinet/in.h> 
//#include<time.h>
#define BUF_size 1024


typedef struct{
	int type;         //信息请求类型
	char username[20];//用户名
	char message[BUF_size];  //信息
}Packet;

char staticusername[20];

void* Send_Message(void *arg);
void* Recv_Message(void *arg);

void error_message(char* message) {
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

int sock;   //返回值
Packet packet;   //发的包
struct sockaddr_in serv_addr,recv_addr2;//定义套接字

int main(int argc,char *argv[]) {
	//socklen_t clnt_addr_size;
	pthread_t send_thread, recv_thread;//定义线程
    if(2 != argc)                                                                                  
     {                                                                                               
          printf("Usage:%s portnumber\n", argv[0]);                                                      
          return EXIT_FAILURE;                                                                     
     }         
	//create套接字
	sock = socket(PF_INET, SOCK_DGRAM, 0);
	if (sock == -1)
		error_message("UDP创建失败");
	//connect  服务
	memset(&serv_addr, 0, sizeof(serv_addr));
	int port = atoi(argv[1]);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(port);
	if (bind(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
		error_message("bind error");	
	printf("输入名称：");
	scanf("%s", packet.username);
	strcpy(staticusername, packet.username);//复制到全局中
	packet.type = 1;  //当前信息为登录信息
	if (sendto(sock, &packet, sizeof(packet), 0, (struct sockaddr*)&serv_addr,
		sizeof(serv_addr)) == -1)//发送
		error_message("发送失败");
		// int pt1, pt2;  
	//建立发送信息线程
	pthread_create(&send_thread, NULL, Send_Message, (void*)&sock);
	//建立收到信息线程
	pthread_create(&recv_thread, NULL, Recv_Message, (void*)&sock);
	//阻塞线程，让主进程等待    
	pthread_join(send_thread, NULL);
	//pthread_join(recv_thread, NULL);
	close(sock);
	return EXIT_SUCCESS;
}
void* Send_Message(void* arg) {

	while (1) {
		printf("输入信息(输入q退出)：");
		scanf("%s", packet.message);
		if (strcmp(packet.message, "q") == 0)
			break;
		strcpy(packet.username, staticusername);
		packet.type = 2;//发送请求
		if (sendto(sock, &packet, sizeof(packet), 0, (struct sockaddr*)&serv_addr,
		sizeof(serv_addr)) == -1)//发送
		error_message("发送失败");
	}
	packet.type = 2;//登出请求
	sprintf(packet.message, "%s 离开了聊天", packet.username);
		if (sendto(sock, &packet, sizeof(packet), 0, (struct sockaddr*)&serv_addr,
		sizeof(serv_addr)) == -1)//发送
		error_message("发送失败");
	pthread_exit(NULL);
}
void* Recv_Message(void* arg){
	socklen_t serv_addr_size;  //一种数据类型，它其实和int差不多，记录长度
	while (1) {
		serv_addr_size = sizeof(serv_addr);
		//接收
		if (recvfrom(sock, &packet, sizeof(packet), 0, (struct sockaddr*)&serv_addr,
			&serv_addr_size) == -1)
			error_message("recvfrom error");
		switch (packet.type)
		{
		case 1://登录请求
			printf("\n%s加入聊天\n", packet.username);//打到字符串中
			break;
		case 2://聊天信息
			printf("\n%s : %s\n", packet.username, packet.message);
			break;			
	}
}
	pthread_exit(NULL);//关闭线程
}



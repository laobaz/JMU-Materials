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
	int type;         //��Ϣ��������
	char username[20];//�û���
	char message[BUF_size];  //��Ϣ
}Packet;

char staticusername[20];

void* Send_Message(void *arg);
void* Recv_Message(void *arg);

void error_message(char* message) {
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

int sock;   //����ֵ
Packet packet;   //���İ�
struct sockaddr_in serv_addr,recv_addr2;//�����׽���

int main(int argc,char *argv[]) {
	//socklen_t clnt_addr_size;
	pthread_t send_thread, recv_thread;//�����߳�
    if(2 != argc)                                                                                  
     {                                                                                               
          printf("Usage:%s portnumber\n", argv[0]);                                                      
          return EXIT_FAILURE;                                                                     
     }         
	//create�׽���
	sock = socket(PF_INET, SOCK_DGRAM, 0);
	if (sock == -1)
		error_message("UDP����ʧ��");
	//connect  ����
	memset(&serv_addr, 0, sizeof(serv_addr));
	int port = atoi(argv[1]);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(port);
	if (bind(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
		error_message("bind error");	
	printf("�������ƣ�");
	scanf("%s", packet.username);
	strcpy(staticusername, packet.username);//���Ƶ�ȫ����
	packet.type = 1;  //��ǰ��ϢΪ��¼��Ϣ
	if (sendto(sock, &packet, sizeof(packet), 0, (struct sockaddr*)&serv_addr,
		sizeof(serv_addr)) == -1)//����
		error_message("����ʧ��");
		// int pt1, pt2;  
	//����������Ϣ�߳�
	pthread_create(&send_thread, NULL, Send_Message, (void*)&sock);
	//�����յ���Ϣ�߳�
	pthread_create(&recv_thread, NULL, Recv_Message, (void*)&sock);
	//�����̣߳��������̵ȴ�    
	pthread_join(send_thread, NULL);
	//pthread_join(recv_thread, NULL);
	close(sock);
	return EXIT_SUCCESS;
}
void* Send_Message(void* arg) {

	while (1) {
		printf("������Ϣ(����q�˳�)��");
		scanf("%s", packet.message);
		if (strcmp(packet.message, "q") == 0)
			break;
		strcpy(packet.username, staticusername);
		packet.type = 2;//��������
		if (sendto(sock, &packet, sizeof(packet), 0, (struct sockaddr*)&serv_addr,
		sizeof(serv_addr)) == -1)//����
		error_message("����ʧ��");
	}
	packet.type = 2;//�ǳ�����
	sprintf(packet.message, "%s �뿪������", packet.username);
		if (sendto(sock, &packet, sizeof(packet), 0, (struct sockaddr*)&serv_addr,
		sizeof(serv_addr)) == -1)//����
		error_message("����ʧ��");
	pthread_exit(NULL);
}
void* Recv_Message(void* arg){
	socklen_t serv_addr_size;  //һ���������ͣ�����ʵ��int��࣬��¼����
	while (1) {
		serv_addr_size = sizeof(serv_addr);
		//����
		if (recvfrom(sock, &packet, sizeof(packet), 0, (struct sockaddr*)&serv_addr,
			&serv_addr_size) == -1)
			error_message("recvfrom error");
		switch (packet.type)
		{
		case 1://��¼����
			printf("\n%s��������\n", packet.username);//���ַ�����
			break;
		case 2://������Ϣ
			printf("\n%s : %s\n", packet.username, packet.message);
			break;			
	}
}
	pthread_exit(NULL);//�ر��߳�
}



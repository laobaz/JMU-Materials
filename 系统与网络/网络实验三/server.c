#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<pthread.h>
#include <errno.h>
#include <netinet/in.h>
#define BUF_size 1024



typedef struct {
	int type;         //��Ϣ��������
	char username[20];//�û���
	char message[BUF_size];  //��Ϣ
}Packet;

typedef struct _NODE
{
    struct sockaddr_in c_addr;//������
    struct _NODE *next;//ָ����
} node_t;

void error_message(char* message) {
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
void creat_link(node_t **head); 
void do_register(int sock,Packet packet, struct sockaddr_in recv_addr, node_t *phead);
void do_group_chat(int sock,Packet packet, struct sockaddr_in recv_addr, node_t *phead);
void quit_group_chat(int sock,Packet packet, struct sockaddr_in recv_addr, node_t *phead);

int main(int argc, char* argv[]) {
	
	if(2 != argc)                                                                                  
  {                                                                                               
          printf("Usage:%s portnumber\n", argv[0]);                                                      
          return EXIT_FAILURE;                                                                     
     }           
	int serv_sock;   //����ֵ
	Packet packet;   //���İ�
	struct sockaddr_in serv_addr,recv_addr;//�����׽���
	socklen_t recv_addr_size;
	char buf[BUF_size];
	//create�׽���
	serv_sock = socket(PF_INET, SOCK_DGRAM, 0);
	if (serv_sock == -1)
		error_message("UDP����ʧ��");
	//connect  ����
	memset(&serv_addr, 0, sizeof(serv_addr));
	int listen_port = atoi(argv[1]);
	//�趨���ʹ��� 
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(listen_port);
	if (bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
		error_message("bind error");
		
	//��������ͷ�ڵ�
	node_t *phead = NULL;
     creat_link(&phead);
     phead->next = NULL;
		
	
	while (1)
	{
		
        memset(&recv_addr, 0, sizeof(recv_addr));//��ղ���
        recv_addr_size=sizeof(recv_addr);
		//�յ���Ϣ
		if (recvfrom(serv_sock, &packet, sizeof(packet), 0, (struct sockaddr*)&recv_addr,
			&recv_addr_size) == -1)
			error_message("recvfrom error");
		switch (packet.type)
		{
		case 1://��¼����
		printf("\n%s ��������\n", packet.username);
		  do_register(serv_sock,packet,recv_addr,phead); 
	      break;
		case 2://������Ϣ
		printf("\n%s : %s\n", packet.username, packet.message);
			do_group_chat(serv_sock,packet,recv_addr,phead);
			break;
		case 3:
			printf("\n%s�˳�����", packet.username);
			quit_group_chat(serv_sock,packet,recv_addr,phead);	
		default:
			break;
		}
		
	}
	close(serv_sock);
	return EXIT_SUCCESS;
}
void creat_link(node_t **head)
{
    *head = (node_t *)malloc(sizeof(node_t));
}
void do_register(int sock,Packet packet, struct sockaddr_in recv_addr, node_t *phead)
{
    //����������¼��Ϣ���͸�������
    node_t *p = phead;
    while (p->next != NULL)
    {
        p = p->next;
        if (sendto(sock, &packet, sizeof(packet),0, (struct sockaddr *)&(p->c_addr), sizeof(p->c_addr)) == -1)
        {
            error_message("recvfrom error");
        }
    }
    //����¼�Ŀͻ�����Ϣ���뱣��������
    //ͷ�巨 
    //����һ���µ�ָ�뱣��ͻ�����Ϣ
    node_t *newp = NULL;
    creat_link(&newp);
    newp->c_addr = recv_addr;
    newp->next = phead->next;
    phead->next = newp;
}
void do_group_chat(int sock,Packet packet, struct sockaddr_in recv_addr, node_t *phead)
{
    //������������Ϣ�������Լ�֮���������
    node_t *p = phead;
    while (p->next != NULL)
    {
        p = p->next;
        //�ж�����ͻ�����Ϣ�Ƿ����Լ�
        //���Լ��Ͳ�����
        if (memcmp(&(p->c_addr), &recv_addr, sizeof(recv_addr)))
        {
            if (sendto(sock, &packet, sizeof(packet), 0, (struct sockaddr *)&(p->c_addr), sizeof(p->c_addr)) == -1)
            {
                error_message("recvfrom error");
            }
        }
    }

}
void quit_group_chat(int sock,Packet packet, struct sockaddr_in recv_addr, node_t *phead)
{
    node_t *p = phead;

    while (p->next != NULL)
    {
        //�ж�����ͻ�����Ϣ�Ƿ����Լ�
        //���Լ��Ͳ����Ͳ��ҽ��Լ��Ŀͻ�����Ϣ��������ɾ��
        if (memcmp(&(p->next->c_addr), &recv_addr, sizeof(recv_addr)))
        {
            p = p->next;
            if (sendto(sock, &packet, sizeof(packet), 0, (struct sockaddr *)&(p->c_addr), sizeof(p->c_addr)) == -1)
            {
                error_message("recvfrom error");
            }
        }
        else
        {
            node_t *pnew;
            pnew = p->next;
            p->next = pnew->next;
            pnew->next = NULL;
            free(pnew);
            pnew = NULL;
        }
    }
}

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
	int type;         //信息请求类型
	char username[20];//用户名
	char message[BUF_size];  //信息
}Packet;

typedef struct _NODE
{
    struct sockaddr_in c_addr;//数据域
    struct _NODE *next;//指针域
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
	int serv_sock;   //返回值
	Packet packet;   //发的包
	struct sockaddr_in serv_addr,recv_addr;//定义套接字
	socklen_t recv_addr_size;
	char buf[BUF_size];
	//create套接字
	serv_sock = socket(PF_INET, SOCK_DGRAM, 0);
	if (serv_sock == -1)
		error_message("UDP创建失败");
	//connect  服务
	memset(&serv_addr, 0, sizeof(serv_addr));
	int listen_port = atoi(argv[1]);
	//设定发送窗口 
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(listen_port);
	if (bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
		error_message("bind error");
		
	//定义链表头节点
	node_t *phead = NULL;
     creat_link(&phead);
     phead->next = NULL;
		
	
	while (1)
	{
		
        memset(&recv_addr, 0, sizeof(recv_addr));//清空操作
        recv_addr_size=sizeof(recv_addr);
		//收到信息
		if (recvfrom(serv_sock, &packet, sizeof(packet), 0, (struct sockaddr*)&recv_addr,
			&recv_addr_size) == -1)
			error_message("recvfrom error");
		switch (packet.type)
		{
		case 1://登录请求
		printf("\n%s 加入聊天\n", packet.username);
		  do_register(serv_sock,packet,recv_addr,phead); 
	      break;
		case 2://聊天信息
		printf("\n%s : %s\n", packet.username, packet.message);
			do_group_chat(serv_sock,packet,recv_addr,phead);
			break;
		case 3:
			printf("\n%s退出聊天", packet.username);
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
    //遍历链表将登录信息发送给所以人
    node_t *p = phead;
    while (p->next != NULL)
    {
        p = p->next;
        if (sendto(sock, &packet, sizeof(packet),0, (struct sockaddr *)&(p->c_addr), sizeof(p->c_addr)) == -1)
        {
            error_message("recvfrom error");
        }
    }
    //将登录的客户端信息插入保存在链表
    //头插法 
    //定义一个新的指针保存客户端信息
    node_t *newp = NULL;
    creat_link(&newp);
    newp->c_addr = recv_addr;
    newp->next = phead->next;
    phead->next = newp;
}
void do_group_chat(int sock,Packet packet, struct sockaddr_in recv_addr, node_t *phead)
{
    //遍历链表，将消息发给除自己之外的所有人
    node_t *p = phead;
    while (p->next != NULL)
    {
        p = p->next;
        //判断链表客户端信息是否是自己
        //是自己就不发送
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
        //判断链表客户端信息是否是自己
        //是自己就不发送并且将自己的客户端信息在链表内删除
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

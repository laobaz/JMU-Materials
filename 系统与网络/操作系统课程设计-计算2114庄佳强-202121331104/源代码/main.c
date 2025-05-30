#include <stdio.h>
#include <string.h>

#include "disk.h"


#define VOL_NAME 'g' /* ��꣬�����Լ��ķ������е��� */

struct bios_pram_block bpb; /* ����ȫ��PBP */
static UDStrack *udstrack;
void print_bpb(struct bios_pram_block *bpb);

int main(int argc, char *argv[])
{
	disk_open_vol(VOL_NAME); /* �򿪷��� */
	disk_read_bpb(&bpb);	 /* ��ȡBIOS������ */
	print_bpb(&bpb);
    //printf("%ld\n",BPB_num); 
	const int SIZE = 1000;
	int opt;
	char cmd[SIZE];
	char arg[SIZE];
	//ʹ��ջ��¼Ŀ¼��ַ
	udstrack=malloc(sizeof(udstrack));
	udstrack->top = 0;
	udstrack->Used[udstrack->top] = BPB_num;
	//printf("%u",udstrack.Used[udstrack.top]) ;
	udstrack->Usedname[udstrack->top] = "G";
	//print_File_control_block(&bpb,udstrack);
	while (1)
	{
		cmd[0] = arg[0] = '\0';
		int i  ;
		//printf("%d",udstrack->top);
		for (i = 0; i <=udstrack->top; i++) {
			if(i==0){
				printf("%s:",udstrack->Usedname[i]);
			}
			else
			printf("%s\\", udstrack->Usedname[i]);
		}
		//printf("%s", udstrack->Usedname[udstrack->top]);
		printf(">");
		scanf("%s", cmd);
		if (getchar() != '\n')
			gets(arg);

		if (!strcmp(cmd, "ls")) /* ls ��ʾ�ļ��б� */
			ls(arg,&bpb,udstrack);
		else if (!strcmp(cmd, "cd")) /* cd �л�Ŀ¼ */
			cd(arg,&bpb, udstrack);
		else if (!strcmp(cmd, "fcb")) /* �鿴�ļ����ƿ�*/
			print_File_control_block(&bpb,udstrack);
		else if (!strcmp(cmd, "fat")) /* �鿴fat�� */
			fat(&bpb,udstrack);
		else if (!strcmp(cmd, "touch")) /* touch ����ļ� */
			touch(arg,&bpb,udstrack);
		else if (!strcmp(cmd, "mkdir")) /* mkdir ɾ���ļ� */
			mkdir(arg,&bpb,udstrack);
		else if (!strcmp(cmd, "cat")) /* �鿴�ļ�����*/
			cat(arg, &bpb, udstrack);
			else if (!strcmp(cmd, "rm")) /* ɾ���ļ�/Ŀ¼*/
			rm(arg, &bpb, udstrack);
		else if (!strcmp(cmd, "help")) /* help ��ʾ������Ϣ */
		{
			printf("������������: \n");
			printf("ls [Ŀ¼]: ��ʾĿ¼�µ��ļ��б�\n");
			printf("cd [Ŀ¼]: �л���ָ����Ŀ¼\n");
			//printf("mkdir [Ŀ¼]: ����һ���µ�Ŀ¼\n");
			printf("touch [�ļ�]: ����һ���µ��ļ�\n");
			printf("mkdir [�ļ���]: ����һ���µ��ļ��ļ���\n");
			printf("rm [�ļ�/Ŀ¼]:ɾ���ļ�����Ŀ¼"); 
			printf("fcb �鿴��ǰĿ¼���ļ����ƿ�\n");
			printf("fat �鿴��ǰĿ¼���ļ���\n");
			printf("touch:����ļ�\n");
			printf("cat:�鿴�ļ�����\n");
			printf("help:��ʾ������Ϣ\n");
		}
		else
		{
			printf((strlen(arg) ? "δ֪����\"%s %s\"" : "δ֪����\"%s\""), cmd, arg);
			puts("����help�鿴����");
		}
	}
	disk_close();
	return 0;
}

/* ���bios_pram_block�е����� */
void print_bpb(struct bios_pram_block *bpb)
{
	printf("�ļ�ϵͳ����: %s\n", bpb->fs_type);
	printf("���ID: %u\n", bpb->vol_id);
	printf("�����: %s\n\n", bpb->vol_lab);
	printf("ÿ���������ֽ���: %u\n", bpb->byte_per_sec);
	printf("ÿ���ص�������: %u\n", bpb->sec_per_clus);
	printf("������������: %u\n", bpb->rsvd_sec_cnt);
	printf("FAT����: %u\n", bpb->num_fats);
	printf("��Ŀ¼��Ŀ��������: %u\n", bpb->root_ent_cnt);
	printf("ÿ��FATռ��������: %u\n", bpb->sec_per_fat);
	printf("��������: %u\n", bpb->tot_sec);
}




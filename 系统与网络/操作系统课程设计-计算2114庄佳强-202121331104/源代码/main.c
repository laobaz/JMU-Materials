#include <stdio.h>
#include <string.h>

#include "disk.h"


#define VOL_NAME 'g' /* 卷标，根据自己的分区进行调整 */

struct bios_pram_block bpb; /* 定义全局PBP */
static UDStrack *udstrack;
void print_bpb(struct bios_pram_block *bpb);

int main(int argc, char *argv[])
{
	disk_open_vol(VOL_NAME); /* 打开分区 */
	disk_read_bpb(&bpb);	 /* 读取BIOS参数块 */
	print_bpb(&bpb);
    //printf("%ld\n",BPB_num); 
	const int SIZE = 1000;
	int opt;
	char cmd[SIZE];
	char arg[SIZE];
	//使用栈记录目录地址
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

		if (!strcmp(cmd, "ls")) /* ls 显示文件列表 */
			ls(arg,&bpb,udstrack);
		else if (!strcmp(cmd, "cd")) /* cd 切换目录 */
			cd(arg,&bpb, udstrack);
		else if (!strcmp(cmd, "fcb")) /* 查看文件控制块*/
			print_File_control_block(&bpb,udstrack);
		else if (!strcmp(cmd, "fat")) /* 查看fat表 */
			fat(&bpb,udstrack);
		else if (!strcmp(cmd, "touch")) /* touch 添加文件 */
			touch(arg,&bpb,udstrack);
		else if (!strcmp(cmd, "mkdir")) /* mkdir 删除文件 */
			mkdir(arg,&bpb,udstrack);
		else if (!strcmp(cmd, "cat")) /* 查看文件内容*/
			cat(arg, &bpb, udstrack);
			else if (!strcmp(cmd, "rm")) /* 删除文件/目录*/
			rm(arg, &bpb, udstrack);
		else if (!strcmp(cmd, "help")) /* help 显示帮助信息 */
		{
			printf("可用命令如下: \n");
			printf("ls [目录]: 显示目录下的文件列表\n");
			printf("cd [目录]: 切换到指定的目录\n");
			//printf("mkdir [目录]: 创建一个新的目录\n");
			printf("touch [文件]: 创建一个新的文件\n");
			printf("mkdir [文件夹]: 创建一个新的文件文件夹\n");
			printf("rm [文件/目录]:删除文件或者目录"); 
			printf("fcb 查看当前目录的文件控制块\n");
			printf("fat 查看当前目录的文件表\n");
			printf("touch:添加文件\n");
			printf("cat:查看文件内容\n");
			printf("help:显示帮助信息\n");
		}
		else
		{
			printf((strlen(arg) ? "未知命令\"%s %s\"" : "未知命令\"%s\""), cmd, arg);
			puts("输入help查看帮助");
		}
	}
	disk_close();
	return 0;
}

/* 输出bios_pram_block中的内容 */
void print_bpb(struct bios_pram_block *bpb)
{
	printf("文件系统类型: %s\n", bpb->fs_type);
	printf("卷标ID: %u\n", bpb->vol_id);
	printf("卷标名: %s\n\n", bpb->vol_lab);
	printf("每个扇区的字节数: %u\n", bpb->byte_per_sec);
	printf("每个簇的扇区数: %u\n", bpb->sec_per_clus);
	printf("保留扇区总数: %u\n", bpb->rsvd_sec_cnt);
	printf("FAT数量: %u\n", bpb->num_fats);
	printf("根目录条目数量上限: %u\n", bpb->root_ent_cnt);
	printf("每个FAT占用扇区数: %u\n", bpb->sec_per_fat);
	printf("扇区总数: %u\n", bpb->tot_sec);
}




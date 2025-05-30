#include <stdio.h>

#include "disk.h"

#define min(a, b) (((a) < (b)) ? (a) : (b))

static char _vol[7] = "\\\\.\\N:"; /* 卷标名 */
static HANDLE _handle = NULL;      /* 保存在内部的"文件指针" */

static const DWORD SEC_SIZE = 512; /* 预设定扇区大小 */

static void _lock_vol()
{
    DWORD dw;

    if (DeviceIoControl(_handle, FSCTL_LOCK_VOLUME, NULL, 0, NULL, 0, &dw, NULL) == 0)
    {
        printf("ERROR: disk::lock code[%lu]\n", GetLastError());
        exit(-1);
    }
}

static void _unlock_vol()
{
    DWORD dw;

    if (DeviceIoControl(_handle, FSCTL_UNLOCK_VOLUME, NULL, 0, NULL, 0, &dw, NULL) == 0)
    {
        printf("ERROR: disk::lock code[%lu]\n", GetLastError());
        exit(-1);
    }
}

static DWORD _row_read(void *buffer, DWORD offset, DWORD size)
{
    DWORD readsize = 0;
    OVERLAPPED over = {0};
    over.Offset = offset;

    if (size != 0 && ReadFile(_handle, buffer, size, &readsize, &over) == 0)
    {
        printf("ERROR: disk::write code[%lu] buffer[%p] offset[%lu] size[%lu] \n", GetLastError(), buffer, offset, size);
        disk_close();
        exit(-1);
    }
    return readsize;
}

static DWORD _row_write(void *buffer, DWORD offset, DWORD size)
{
    DWORD writeensize = 0;
    OVERLAPPED over = {0};
    over.Offset = offset;

    _lock_vol();
    if (size != 0 && WriteFile(_handle, buffer, size, &writeensize, &over) == 0)
    {
        printf("ERROR: disk::write code[%lu] buffer[%p] offset[%lu] size[%lu] \n", GetLastError(), buffer, offset, size);
        _unlock_vol();
        disk_close();
        exit(-1);
    }
    _unlock_vol();

    return writeensize;
}

/* ============================================================== */

/*
 * 打开分区
 * vol_name: 分区卷标
 */
void disk_open_vol(char vol_name)
{
    disk_close();

    _vol[4] = vol_name;
    _handle = CreateFile((LPCSTR)_vol, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
    if (_handle == INVALID_HANDLE_VALUE)
    {
        printf("ERROR: disk::open_vol can not open %s", _vol);
        disk_close();
        exit(-1);
    }
}

/*
 * 读取分区数据
 */
void disk_read(void *buffer, DWORD offset, DWORD size)
{
    u8 tmp_buff[SEC_SIZE]; /* 临时缓冲区 */
    DWORD buff_off = 0;    /* 当前读取的进度 */

    /*
     * 原版的API只能按照扇区读写
     * 也就是说offset和size都必须是512的整数倍，否则就会报错
     * 所以需要一些额外的操作来实现和Linux一样自由读写的效果
     * FK U Microsoft
     */

    /*
     * 起始地址未对齐扇区
     * 先读取属于该扇区内的数据
     */
    if (offset % SEC_SIZE != 0)
    {
        DWORD sec_off = offset % SEC_SIZE;               /* 扇区内偏移 */
        DWORD read_size = min(size, SEC_SIZE - sec_off); /* 该扇区内要读取的数据大小 */

        _row_read(tmp_buff, offset - sec_off, SEC_SIZE); /* 先读入临时缓冲区 */
        memcpy(buffer, tmp_buff + sec_off, read_size);

        buff_off += read_size;
    }
    /*
     * 读取中间包含的完整扇区
     */
    if (size - buff_off >= SEC_SIZE)
    {
        DWORD sec_cnt = (size - buff_off) / SEC_SIZE; /* 包含的扇区数 */
        DWORD read_size = SEC_SIZE * sec_cnt;

        _row_read((u8 *)buffer + buff_off, offset + buff_off, read_size);

        buff_off += read_size;
    }
    /*
     * 读取末尾地址未对其的扇区
     */
    if (buff_off < size)
    {
        DWORD read_size = size - buff_off;

        _row_read(tmp_buff, offset + buff_off, SEC_SIZE);
        memcpy((u8 *)buffer + buff_off, tmp_buff, read_size);
    }
}

/*
 * 数据写入分区
 */
void disk_write(void *buffer, DWORD offset, DWORD size)
{
    u8 tmp_buff[SEC_SIZE]; /* 临时缓冲区 */
    DWORD buff_off = 0;    /* 当前读取的进度 */

    /*
     * 进行非扇区对其的写入，原理与disk_read相似
     * 不过在写入非完整扇区数据时需要采取“读取、部分修改、写回”的策略
     * 使其不会破坏无关的数据
     */

    /*
     * 起始地址未对齐扇区
     * 进行部分写入
     */
    if (offset % SEC_SIZE != 0)
    {
        DWORD sec_off = offset % SEC_SIZE;               /* 扇区内偏移 */
        DWORD read_size = min(size, SEC_SIZE - sec_off); /* 该扇区内要读取的数据大小 */

        _row_read(tmp_buff, offset - sec_off, SEC_SIZE);  /* 先将原数据读入临时缓冲区 */
        memcpy(tmp_buff + sec_off, buffer, read_size);    /* 对缓冲区数据进行部分修改 */
        _row_write(tmp_buff, offset - sec_off, SEC_SIZE); /* 把被部分修改过的数据写回扇区 */

        buff_off += read_size;
    }
    /*
     * 写入中间包含的完整扇区
     */
    if (size - buff_off >= SEC_SIZE)
    {
        DWORD sec_cnt = (size - buff_off) / SEC_SIZE; /* 包含的扇区数 */
        DWORD read_size = SEC_SIZE * sec_cnt;

        _row_write((u8 *)buffer + buff_off, offset + buff_off, read_size);

        buff_off += read_size;
    }
    /*
     * 写入末尾地址未对其的扇区
     */
    if (buff_off < size)
    {
        DWORD read_size = size - buff_off;

        _row_read(tmp_buff, offset + buff_off, SEC_SIZE);
        memcpy(tmp_buff, (u8 *)buffer + buff_off, read_size);
        _row_write(tmp_buff, offset + buff_off, SEC_SIZE);
    }
}

/*
 * 读取引导扇区中的BIOS参数块
 */
void disk_read_bpb(struct bios_pram_block *bpb)
{
    struct fat_boot_sector bs;
    disk_read(&bs, 0, sizeof(bs));

    bpb->byte_per_sec = bs.BPB_BytesPerSec;
    bpb->sec_per_clus = bs.BPB_SecPerClus;
    bpb->rsvd_sec_cnt = bs.BPB_ResvdSecCnt;
    bpb->num_fats = bs.BPB_NumFATs;
    bpb->root_ent_cnt = bs.BPB_RootEntCnt;
    bpb->sec_per_fat = bs.BPB_FATSz16;
    bpb->tot_sec = bs.BPB_TotSec16 != 0 ? bs.BPB_TotSec16 : bs.BPB_TotSec32;
    bpb->vol_id = bs.BS_VollD;
    memcpy(bpb->vol_lab, bs.BS_VolLab, sizeof(bpb->vol_lab));
    memcpy(bpb->fs_type, bs.BS_FileSysType, sizeof(bpb->fs_type));
    
}

/*
 * 释放资源
 */
void disk_close()
{
    if (_handle != NULL)
        CloseHandle(_handle);
    _vol[4] = 'N';
    _handle = NULL;
}

 


//char tempbuf[1024];
int File_control_block_size = 32;
void ls(const char* dir, struct bios_pram_block* bpb, UDStrack* udstrack)
{
    
    //遍历目录区
    int i = 0;
    for (; i < 1024; i++) {
        FileDescriptor tempFp;
       	//printf("%ld\n",BPB_num); 
       	//printf("%u",udstrack->Used[udstrack->top]) ;
        disk_read(&tempFp,udstrack->Used[udstrack->top] + i * File_control_block_size,File_control_block_size);
        if(strlen(tempFp.DIR_Name)==0){
        	break;
		}
		if(tempFp.DIR_Name[0]==0x2E){
		continue;
		}
		//读出是目录 
		if(tempFp.DIR_Attr==0x10&&tempFp.DIR_Name[0]!=0xE5){
			printf(".");
			int j=0;
			for(;j<8;j++){
				if(tempFp.DIR_Name[j]==' ')
				break;
				printf("%c",tempFp.	DIR_Name[j]);
			}
			printf("\t");
	    }
	    //读出是文件 
	    else if(tempFp.DIR_Attr==0X20&&tempFp.DIR_Name[0]!=0xE5){
	    	int j=0;
	    	for(;j<8;j++){
	    		if(tempFp.DIR_Name[j]==' ')
				break; 
				printf("%c",tempFp.DIR_Name[j]);
			}
			printf(".");
			 j=0;
			for(;j<3;j++){
			if(tempFp.DIR_Name[j]==' ')
				break;  
				 
				printf("%c",tempFp.DIR_Type[j]);
			} 
			printf("\t");
		}
    }
    printf("\n");
}

void cd(const char* dir, struct bios_pram_block* bpb, UDStrack* udstrack) {
    //返回前目录 
    //printf("%s", dir);
    if (dir[0] == '.' && dir[1] == '.') {
        if (udstrack->top > 0) {
            udstrack->top--;
        }
    }
    else {
        //获得栈中最前面的目录地址
        DWORD BPB_temp = udstrack->Used[udstrack->top];
        char* character;
        //分割字符串
        character = strtok((char*)dir, "/");
        //printf("%s", character);
        FileDescriptor tempFp;
        char filename[14];
        while (character != NULL) {
            disk_read(&tempFp, BPB_temp, File_control_block_size);
            BPB_temp += 32;
            if (tempFp.DIR_Name[0] == 0xE5) {
                continue;
            }
            if (strlen(tempFp.DIR_Name) == 0) {
                break;
            }
            //找到是目录 
            if (tempFp.DIR_Attr == 0x10) {
                //提取文件名 
                memset(filename, 0, sizeof(filename));
                int index = 0;
                int j = 0;
                for (; j < 8; j++) {
                    if (tempFp.DIR_Name[j] == ' ') {
                        break;
                    }
                    filename[index++] = tempFp.DIR_Name[j];
                }
                //printf("%s", filename);
                if (strcmp(character, filename) == 0) {
                    u16 num = tempFp.DIR_FstClus;
                    //跳转到对应数据区
                    //bpb->sec_per_fat * num_fats + bpb->rsvd_sec_cnt ) *byte_per_sec到根目录区
                    //再加上32*  bpb->root_ent_cnt 到数据区
                    //(num - 2) * byte_per_sec * bpb->sec_per_clus到指定的蔟号中
                    BPB_temp = (bpb->sec_per_fat * bpb->num_fats + bpb->rsvd_sec_cnt) *
                    bpb->byte_per_sec + 32 * bpb->root_ent_cnt + (num - 2) * bpb->byte_per_sec * bpb->sec_per_clus;
                    //BPB_temp = (bpb->sec_per_fat * 2 + bpb->rsvd_sec_cnt + 32) *512 + (num - 2) * 512 * 4;
                  
                    udstrack->top++;
                    udstrack->Used[udstrack->top] = BPB_temp;
                    //记得分配空间
                    udstrack->Usedname[udstrack->top]=malloc(sizeof(character));
                    strcpy(udstrack->Usedname[udstrack->top], character);
                    character = strtok(NULL, "/");
                }
            }

        }
    }
}






void rm(const char* dir, struct bios_pram_block* bpb, UDStrack* udstrack) {
    DWORD BPB_temp = udstrack->Used[udstrack->top];
    FileDescriptor temp_File;
    while (1) {
        disk_read(&temp_File, BPB_temp, sizeof(temp_File));
        
        if (temp_File.DIR_Name[0] == '\0') {
            break;
        }
        if (temp_File.DIR_Name[0] == 0XE5 || temp_File.DIR_Name[0] == 0x2E || temp_File.DIR_Attr & 0b00000010) {
           BPB_temp += 32;
		    continue;
        }
        char filename[14];
        memset(filename, 0, sizeof(filename));
        int index = 0;
        int j = 0;
        for (; j < 8; j++) {
            if (temp_File.DIR_Name[j] == ' ') {
                break;
            }
            filename[index++] = temp_File.DIR_Name[j];
        }
        //printf("%s", filename);
        if (strcmp(dir, filename) == 0) {
            temp_File.DIR_Name[0] = 0xE5;
            disk_write(&temp_File, BPB_temp, 32);

            u16 Fat_after_convert[4096];
            convert_Fat(Fat_after_convert, bpb);
            
            u16 count = temp_File.DIR_FstClus;
            u16 count_temp;
            u8 old_buff[2], new_buff[2];
            while (count != 0xfff && count != 0) {
                u16 fat_count = count * 3 / 2;
                //修改fat表
                DWORD bpb_temp = bpb->byte_per_sec * bpb->rsvd_sec_cnt + (int)fat_count;
                disk_read(old_buff, bpb_temp, 2);
                if (count % 2 == 0) {
                    new_buff[1] = old_buff[1] & 0xf0;
                    new_buff[0] = 0x00;
                }
                else {
                    new_buff[1] = 0x00;
                    new_buff[0] = old_buff[0] & 0x0f;
                }
                //fat1
                disk_write(new_buff, bpb_temp, 2);
                //fat2
                disk_write(new_buff, bpb_temp + bpb->byte_per_sec * bpb->sec_per_fat, 2);
                count_temp = Fat_after_convert[count];
                count = count_temp;

            }
        }
        BPB_temp += 32;
    }
    
}

void mkdir(const char* dir, struct bios_pram_block* bpb, UDStrack* udstrack) {
    char temp_dir[20];
    //转大写
    int i = 0;
    while (dir[i] != '\0') {
        temp_dir[i] = toupper(dir[i]);
        i++;
    }
    temp_dir[i] = '\0';
    //当前目录地址
    DWORD cur_offset = udstrack->Used[udstrack->top];
    //写入字符
    u8 temp_buff[32];
    //FileDescriptor new_file;
    memset(temp_buff, 0, sizeof temp_buff);
    char* filename;
    filename = strtok((char*)temp_dir, ".");
    i = 0;
    //文件名
    while (filename[i] != '\0') {
        temp_buff[i] = filename[i];
        i++;
    }
    //补全空白
    for (; i < 8; i++)
        temp_buff[i] = ' ';

    int j = 0;
    //文件后缀
    for (j = 0; j < 3; j++) {
        temp_buff[i++] = ' ';
   }
    //文件类型
    temp_buff[i++] = 0x10;
    //保留区
    for (; i < 22; i++) {
        temp_buff[i] = 0x00;
    }
    time_t t = time(NULL);
    struct tm* tm = localtime(&t);
    //算时间
    int hour = tm->tm_hour;    // 小时
    int minute = tm->tm_min;   // 分钟
    int second = tm->tm_sec;   // 秒钟
    int fat_time = (hour << 11) | (minute << 5) | (second / 2);
    unsigned char time_high = (fat_time >> 8) & 0xFF;  // 高字节
    unsigned char time_low = fat_time & 0xFF;          // 低字节
    temp_buff[i++] = time_low;//时间
    temp_buff[i++] = time_high;
    //算日期
    int year = tm->tm_year + 1900;  // 年份偏移量
    int month = tm->tm_mon + 1;     // 月份
    int day = tm->tm_mday;          // 日期
    int fat_date = ((year - 1980) << 9) | (month << 5) | day;
    unsigned char date_high = (fat_date >> 8) & 0xFF;  // 高字节
    unsigned char date_low = fat_date & 0xFF;          // 低字节
    temp_buff[i++] = date_low;//日期
    temp_buff[i++] = date_high;
    //文件第一簇号
    u16 Fat_after_convert[4096];
    convert_Fat(Fat_after_convert, bpb);
    j = 0;
    u16 count = 0;
    for (; j < 4096; j++) {
        if (Fat_after_convert[j] == 0) {
            count = j;
            break;
        }
            
    }
    char a = (char)count;
    temp_buff[i++] = a;
    a=(char)count>>8; 
    temp_buff[i++] = a;
    u16 fat_count = count * 3 / 2;
    //修改fat表
    u8 old_buff[2],new_buff[2];
    DWORD bpb_temp = bpb->byte_per_sec * bpb->rsvd_sec_cnt + (int)fat_count;
    disk_read(old_buff, bpb_temp, 2);
    if (count % 2 == 0) {
        new_buff[1] = old_buff[1] | 0x0f;
        new_buff[0] = 0xff;
    }
    else {
        new_buff[1] = 0xff;
        new_buff[0] = old_buff[0] | 0xf0;
    }
    //fat1
    disk_write(new_buff, bpb_temp, 2);
    //fat2
    disk_write(new_buff, bpb_temp + bpb->byte_per_sec * bpb->sec_per_fat, 2);


    for (; i < 28; i++)
    {
        temp_buff[i] = 0x00;
    }
    //文件大小
    for (; i < 32; i++)
    {
        temp_buff[i] = 0x00;
    }
    FileDescriptor New_file;
    //查看第一个空白
    for (i = 0; i < 128; i++) {
        disk_read(&New_file, cur_offset + i * 32, 32);
        if (j < 0 && New_file.DIR_Name[0] == 0xE5 || New_file.DIR_Attr == 0) {
            j = i;
            break;
        }
        if (memcmp(New_file.DIR_Name, filename, min(sizeof(New_file.DIR_Name), sizeof(filename))) == 0) {
            printf("该文件夹已存在!\n");
            return;
        }
    }
    DWORD temp_offset = (cur_offset + j * 32);
    disk_write(temp_buff, temp_offset, sizeof temp_buff);
}

//void touch(const char* dir, struct bios_pram_block* bpb, UDStrack* udstrack) {
//    u8 New_name[8];
//    u8 New_type[3];
//    //当前偏移量
//    DWORD cur_offset = udstrack->Used[udstrack->top];
//    memset(New_name, 0, sizeof(New_name));
//    memset(New_type, 0, sizeof(New_type));
//    FileDescriptor New_file;
//    
//   
//    char temp[8];
//    int u = 0,count=0;
//    for (; u < 8; u++) {
//        if (dir[u] == '.')
//            break;
//        else {
//            New_name[u] = dir[u];
//            count++;
//        }
//   }
//    u = 0;
//    for (; u < 3; u++) {
//        New_type[u] = dir[count+1+ u];
//    }
//
//    DWORD temp_offset;
//    int j = -1,i=0;
//    //(bpb->root_ent_cnt*bpb->byte_per_sec/32
//    for (; i <128; i++) {
//        disk_read(&New_file, cur_offset + i * 32, 32);
//        if (j < 0 && New_file.DIR_Name[0] == 0xE5 || New_file.DIR_Attr == 0) {
//            j = i;
//            break;
//        }
//        if (memcmp(New_file.DIR_Name, New_name, min(sizeof(New_file.DIR_Name), sizeof(New_name))) == 0) {
//            printf("该文件已存在!\n");
//            return;
//        }
//    }
//        //计算出该文件要存储的地方
//        temp_offset = (cur_offset + j * 32);
//        memset(New_file.DIR_Name,0,sizeof(New_file.DIR_Name));
//        memset(New_file.DIR_Type,0,sizeof(New_file.DIR_Type));
//        memset(New_file.Reserved, 0, sizeof(New_file.Reserved));
//        memcpy(New_file.DIR_Name, New_name, sizeof(New_name));
//        memcpy(New_file.DIR_Type, New_type, sizeof(New_type));
//        New_file.DIR_Attr = 0x20;
//        New_file.DIR_FstClus = 0;
//        New_file.DIR_FileSize = 0;
//        //memset(New_file->Reserved, 0, sizeof(New_file->Reserved));
//        time_t t = time(NULL);
//        struct tm* tm = localtime(&t);
//        int year = tm->tm_year + 1900;  // 年份偏移量
//        int month = tm->tm_mon + 1;     // 月份
//        int day = tm->tm_mday;          // 日期
//        int fat_date = ((year - 1980) << 9) | (month << 5) | day;
//        New_file.WrtDate = fat_date;
//        int hour = tm->tm_hour;    // 小时
//        int minute = tm->tm_min;   // 分钟
//        int second = tm->tm_sec;   // 秒钟
//        int fat_time = (hour << 11) | (minute << 5) | (second / 2);
//        New_file.WrtTime = fat_time;
//        disk_write(&New_file, temp_offset,32);
//        //break;
//    
//
//}
void touch(const char* dir, struct bios_pram_block* bpb, UDStrack* udstrack) {
    char temp_dir[20];
    //转大写
    int i = 0;
    while (dir[i] != '\0') {
        temp_dir[i] = toupper(dir[i]);
        i++;
    }
    temp_dir[i] = '\0';
    //当前目录地址
    DWORD cur_offset = udstrack->Used[udstrack->top];
    //写入字符
    u8 temp_buff[32];
    //FileDescriptor new_file;
    memset(temp_buff, 0, sizeof temp_buff);
    char* filename;
    char* type;
    filename = strtok((char*)temp_dir, ".");
    type = strtok(NULL, ".");
    i = 0;
    //文件名
    while (filename[i] != '\0') {
        temp_buff[i] = filename[i];
        i++;
    }
    //补全空白
    for ( ; i < 8; i++)
        temp_buff[i] = ' ';
    
    int j = 0;
    //文件后缀
    while (type[j] != '\0')
       temp_buff[i++] =type[j++];
    //补全空白
    for (; i < 11; i++)
        temp_buff[i] = ' ';
    //文件类型
    temp_buff[i++] = 0x20;
    //保留区
    for ( ; i < 22; i++){
        temp_buff[i] = 0x00;
    }
    time_t t = time(NULL);
    struct tm* tm = localtime(&t);
    //算时间
    int hour = tm->tm_hour;    // 小时
    int minute = tm->tm_min;   // 分钟
    int second = tm->tm_sec;   // 秒钟
    int fat_time = (hour << 11) | (minute << 5) | (second / 2);
    unsigned char time_high = (fat_time >> 8) & 0xFF;  // 高字节
    unsigned char time_low = fat_time & 0xFF;          // 低字节
    temp_buff[i++] = time_low;//时间
    temp_buff[i++] = time_high;
    //算日期
    int year = tm->tm_year + 1900;  // 年份偏移量
    int month = tm->tm_mon + 1;     // 月份
    int day = tm->tm_mday;          // 日期
    int fat_date = ((year - 1980) << 9) | (month << 5) | day;
    unsigned char date_high = (fat_date >> 8) & 0xFF;  // 高字节
    unsigned char date_low = fat_date & 0xFF;          // 低字节
    temp_buff[i++] = date_low;//日期
    temp_buff[i++] = date_high;
    //文件第一簇号
    for (; i < 28; i++)
    {
        temp_buff[i] = 0x00;
    }
    //文件大小
    for (; i < 32; i++)
    {
        temp_buff[i] = 0x00;
    }
    FileDescriptor New_file;
   //查看第一个空白
    for ( i=0; i < 128; i++) {
        disk_read(&New_file, cur_offset + i * 32, 32);
        if (j < 0 && New_file.DIR_Name[0] == 0xE5 || New_file.DIR_Attr == 0) {
            j = i;
            break;
        }
        if (memcmp(New_file.DIR_Name, filename, min(sizeof(New_file.DIR_Name), sizeof(filename))) == 0) {
            printf("该文件已存在!\n");
            return;
        }
    }
    DWORD temp_offset = (cur_offset + j * 32);
    disk_write(temp_buff, temp_offset, sizeof temp_buff);
}


void print_File_control_block(struct bios_pram_block* bpb,UDStrack* udstrack) {
    int i = 0;
    FileDescriptor tempFp;
    printf("文件控制块为：\n");
    printf("文件名\t\t属性\t\t类型\t\t最后一次写入时间\t\t开始蔟\t\t文件大小\n");
    for (; i < 1024; i++) {
        //printf("%ld\n",BPB_num); 
        disk_read(&tempFp, udstrack->Used[udstrack->top] + i * File_control_block_size, File_control_block_size);
        if (strlen(tempFp.DIR_Name) == 0) {
            break;
        }
       	if(tempFp.DIR_Name[0]==0x2E){
			continue;
		}
        if (tempFp.DIR_Name[0] != 0xE5 && (tempFp.DIR_Attr == 0x10 || tempFp.DIR_Attr == 0X20)) {
            int j = 0;
            //printf("文件名为:");
            for (; j < 8; j++) {
                printf("%c", tempFp.DIR_Name[j]);
            }
            printf("\t");
            j = 0;
            for (; j < 3; j++) {
                if (tempFp.DIR_Name[j] == ' ')
                    break;
                printf("%c", tempFp.DIR_Type[j]);
            }
            printf("\t\t");
           // printf("文件为:");
           if(tempFp.DIR_Attr==16){
           	printf("目录\t\t");
		   }
		   else if(tempFp.DIR_Attr==32){
		   	printf("文件\t\t");
		   }
		   
           // printf("最后一次写入时间为:");
           //利用算法分析时间 
           int date_y=((tempFp.WrtDate>>9)&0x7f)+1980;
           int date_m=((tempFp.WrtDate>>5)&0x0f);
           int date_d=tempFp.WrtDate&0x1f; 
           printf("%04d/%02d/%02d  ",date_y,date_m,date_d);
           int time_h=(tempFp.WrtTime>>11)&0x1f;
           int time_m=(tempFp.WrtTime>>5)&0x3f;
           int time_s=(tempFp.WrtTime&0x1f)*2;
           printf("%02d:%02d:%02d\t\t",time_h,time_m,time_s);
           
           // printf("此条目对应的开始簇数为:");
            printf("%u\t\t", tempFp.DIR_FstClus);
           // printf("文件大小为:");
            printf("%u", tempFp.DIR_FileSize);
            printf("\n");
            //printf("文件名: %s文件类型: %s文件属性: %u保留位: %s最后一次写入时间: %u最后一次写入日期: %u此条目对应的开始簇数: %u文件大小: %u\n"
            //,tempFp.DIR_Name,tempFp.DIR_Type,tempFp.DIR_Attr,tempFp.DIR_Attr,tempFp.Reserved,tempFp.WrtTime,tempFp.WrtDate,tempFp.DIR_FstClus,tempFp.DIR_FileSize);
             //printf("\n");
        }

    }
}
// Num_Of_Fat=bpb->sec_per_fat * 512 * 2 / 3
int Num_Of_Fat = 4096;
void fat(struct bios_pram_block* bpb, UDStrack* udstrack) {
    DWORD BPB_temp = udstrack->Used[udstrack->top];
    u16 Fat_after_convert[Num_Of_Fat];
    memset(Fat_after_convert, 0, Num_Of_Fat);
    FileDescriptor temp_File;
    convert_Fat(Fat_after_convert, bpb);
    int i = 0;
   for (; i < 100; i++) {
      printf("%03x  ", Fat_after_convert[i]);
   }
   printf("\n"); 
    while (1) {
        disk_read(&temp_File, BPB_temp, sizeof(temp_File));
        BPB_temp += 32;
        if (temp_File.DIR_Name[0] == '\0') {
            break;
        }
        if (temp_File.DIR_Name[0] == 0XE5 || temp_File.DIR_Name[0] == 0x2E||temp_File.DIR_Attr & 0b00000010) {
            continue;
        }

        //读出是目录
        if (temp_File.DIR_FstClus != 0) {
            if (temp_File.DIR_Attr == 0x10) {
                printf(".");
                int j = 0;
                for (; j < 8; j++) {
                    if (temp_File.DIR_Name[j] == ' ')
                        break;
                    printf("%c", temp_File.DIR_Name[j]);
                }
            }
            //读出是文件 
            else if (temp_File.DIR_Attr == 0X20) {
                int j = 0;
                for (; j < 8; j++) {
                    if (temp_File.DIR_Name[j] == ' ')
                        break;
                    printf("%c", temp_File.DIR_Name[j]);
                }
                printf(".");
                j = 0;
                for (; j < 3; j++) {
                    if (temp_File.DIR_Name[j] == ' ')
                        break;

                    printf("%c", temp_File.DIR_Type[j]);
                }
            }
            printf(":"); 
            int num = temp_File.DIR_FstClus;
            int temp_num; 
            printf("%lu->", num);
            while (Fat_after_convert[num] != 0xff8&&Fat_after_convert[num] !=0xfff&&Fat_after_convert[num] !=0x0 ) {
            	temp_num = Fat_after_convert[num];
                printf("%lu->", temp_num);
                num=temp_num;
            }
            printf("EOF\n");
        }
    }
}

//转化8字节为12字节，并获取转化为的FAT_After_Convert表
void convert_Fat(u16* FAT_After_Convert, struct bios_pram_block* bpb) {
    u8 buff[3];
    DWORD OffSet = bpb->byte_per_sec * bpb->rsvd_sec_cnt;
    int i = 0;
    int size=3;
    int index=0;
    //bpb->sec_per_fat*bpb->byte_per_sec
    for (; i < bpb->sec_per_fat * bpb->byte_per_sec/3; i++, OffSet += 3) {
        //每3个项一组，合成2个fat表项，放在FAT_After_Convert中 
        disk_read(buff, OffSet, size);
        //取第二个低4位往前推8位+第一个
        FAT_After_Convert[index] = (u16)(buff[1] & 0b00001111) << 8 | buff[0];
        //取第个高4位+第三个往后推4位
        FAT_After_Convert[index + 1] = ((u16)buff[1] & 0b11110000 | (u16)(buff[2]) << 8) >> 4;
        index += 2;
    }
}
void cat(const char* dir, struct bios_pram_block* bpb, UDStrack* udstrack) {
    DWORD BPB_temp = udstrack->Used[udstrack->top];
     FileDescriptor temp_File;
    while (1) {
        disk_read(&temp_File, BPB_temp, sizeof(temp_File));
        BPB_temp += 32;
        if (temp_File.DIR_Name[0] == '\0') {
            break;
        }
        if (temp_File.DIR_Name[0] == 0XE5 || temp_File.DIR_Name[0] == 0x2E || temp_File.DIR_Attr & 0b00000010) {
            continue;
        }
        char filename[14];
        memset(filename, 0, sizeof(filename));
        int index = 0;
        int j = 0;
        for (; j < 8; j++) {
            if (temp_File.DIR_Name[j] == ' ') {
                break;
            }
            filename[index++] = temp_File.DIR_Name[j];
        }
        //printf("%s", filename);
        if (strcmp(dir, filename) == 0) {
            BPB_temp= (bpb->sec_per_fat * 2 + bpb->rsvd_sec_cnt + 32) * 512 + (temp_File.DIR_FstClus - 2) * 512 * 4;
                int file[2049];
                disk_read(file, BPB_temp, 2048);
                printf("%s", file);
                printf("\n");
        }
    }
}

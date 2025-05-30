#pragma once

#include <windows.h>

#include "types.h"
#include<time.h>
extern struct bios_pram_block bpb;  /* 声明可全局访问的BPB */

//计算根目录首地址//(bpb.sec_per_fat * 2 + bpb.rsvd_sec_cnt) * 512=16384

//记录跟目录地址偏移量
static DWORD BPB_num  = 16384;

//记录目录切换列表栈
typedef struct
{
    int top;  //栈顶
    DWORD Used[100];
    char *Usedname[100];
}UDStrack; 


/*
 * FAT12/16引导扇区信息
 * 关闭内存对齐优化，方便一次性读取赋值
 */
#pragma pack(1)
struct fat_boot_sector
{
    //一个跳转指令
    u8 BS_jmpBOOT[3];
    //厂商名
    u8 BS_OEMName[8];
    // 每个扇区字节数 512
    u16 BPB_BytesPerSec;
    // 每簇扇区数 1
    u8 BPB_SecPerClus;
    // boot引导占扇区数 1
    u16 BPB_ResvdSecCnt;
    //一共有几个FAT表 2
    u8 BPB_NumFATs;
    //根目录文件最大数  0xe0 = 224
    u16 BPB_RootEntCnt;
    //扇区总数  0xb40 = 2880
    u16 BPB_TotSec16;
    //介质描述符  0xf0
    u8 BPB_Media;
    //每个FAT表占扇区数 12
    u16 BPB_FATSz16;
    // 每个磁道占扇区数 0x12
    u16 BPB_SecPerTrk;
    // 磁头数   0x2
    u16 BPB_NumHeads;
    // 隐藏扇区数 0
    u32 BPB_HiddSec;
    // 如果BPB_TotSec16=0,则由这里给出扇区数 0
    u32 BPB_TotSec32;
    // INT 13H的驱动号 0
    u8 BS_DrvNum;
    //保留，未用    0
    u8 BS_Reserved1;
    //扩展引导标记  0x29
    u8 BS_BootSig;
    // 卷序列号 0
    u32 BS_VollD;
    // 卷标 'yxr620'
    u8 BS_VolLab[11];
    // 文件系统类型 'FAT12'
    u8 BS_FileSysType[8];

};
#pragma pack()

/*
 * BIOS参数块
 * 记录了FAT分区的基本参数
 * 已进行简化，仅保留计算需要的内容
 */
struct bios_pram_block
{
    u16 byte_per_sec;   /* 每个扇区的字节数 */
    u8 sec_per_clus;    /* 每个簇的扇区数 */
    u16 rsvd_sec_cnt;   /* 保留扇区总数(包括引导扇区) */
    u8 num_fats;        /* FAT数量 */
    u16 root_ent_cnt;   /* 根目录条目数量上限 */
    u16 sec_per_fat;    /* 每个FAT占用扇区数 */
    u32 tot_sec;        /* 扇区总数 */
    /* FAT12/16 EPBP */
    u32 vol_id;
    u8 vol_lab[11];
    u8 fs_type[8];
};

//文件描述符定义
typedef struct FileDescriptor
{
    u8 DIR_Name[8];   //文件名
    u8 DIR_Type[3];   //文件类型/扩展名
    u8 DIR_Attr;      //文件类型
    u8 Reserved[10];  //保留位
    u16 WrtTime;      //最后一次写入时间
    u16 WrtDate;      //最后一次写入日期
    u16 DIR_FstClus;  //此条目对应的开始簇数
    u32 DIR_FileSize; //文件大小
} __attribute__((packed)) FileDescriptor;

void disk_open_vol(char vol_name);
void disk_read(void *buffer, DWORD offset, DWORD size);
void disk_write(void *buffer, DWORD offset, DWORD size);
void disk_read_bpb(struct bios_pram_block *bpb);
void disk_close();
void ls(const char* dir,struct bios_pram_block* bpb,UDStrack *ud);
void cd(const char* dir, struct bios_pram_block* bpb,UDStrack *ud);
void touch(const char* dir, struct bios_pram_block* bpb,UDStrack* ud);
void rm(const char* dir, struct bios_pram_block* bpb,UDStrack* ud);
void print_File_control_block(struct bios_pram_block* bpb,UDStrack* udstrack);
void fat(struct bios_pram_block* bpb, UDStrack* udstrack);
void convert_Fat(u16* FAT_After_Convert, struct bios_pram_block* bpb);
void cat(const char* dir, struct bios_pram_block* bpb, UDStrack* udstrack);
void mkdir(const char* dir, struct bios_pram_block* bpb, UDStrack* udstrack);
#pragma once

#include <windows.h>

#include "types.h"
#include<time.h>
extern struct bios_pram_block bpb;  /* ������ȫ�ַ��ʵ�BPB */

//�����Ŀ¼�׵�ַ//(bpb.sec_per_fat * 2 + bpb.rsvd_sec_cnt) * 512=16384

//��¼��Ŀ¼��ַƫ����
static DWORD BPB_num  = 16384;

//��¼Ŀ¼�л��б�ջ
typedef struct
{
    int top;  //ջ��
    DWORD Used[100];
    char *Usedname[100];
}UDStrack; 


/*
 * FAT12/16����������Ϣ
 * �ر��ڴ�����Ż�������һ���Զ�ȡ��ֵ
 */
#pragma pack(1)
struct fat_boot_sector
{
    //һ����תָ��
    u8 BS_jmpBOOT[3];
    //������
    u8 BS_OEMName[8];
    // ÿ�������ֽ��� 512
    u16 BPB_BytesPerSec;
    // ÿ�������� 1
    u8 BPB_SecPerClus;
    // boot����ռ������ 1
    u16 BPB_ResvdSecCnt;
    //һ���м���FAT�� 2
    u8 BPB_NumFATs;
    //��Ŀ¼�ļ������  0xe0 = 224
    u16 BPB_RootEntCnt;
    //��������  0xb40 = 2880
    u16 BPB_TotSec16;
    //����������  0xf0
    u8 BPB_Media;
    //ÿ��FAT��ռ������ 12
    u16 BPB_FATSz16;
    // ÿ���ŵ�ռ������ 0x12
    u16 BPB_SecPerTrk;
    // ��ͷ��   0x2
    u16 BPB_NumHeads;
    // ���������� 0
    u32 BPB_HiddSec;
    // ���BPB_TotSec16=0,����������������� 0
    u32 BPB_TotSec32;
    // INT 13H�������� 0
    u8 BS_DrvNum;
    //������δ��    0
    u8 BS_Reserved1;
    //��չ�������  0x29
    u8 BS_BootSig;
    // �����к� 0
    u32 BS_VollD;
    // ��� 'yxr620'
    u8 BS_VolLab[11];
    // �ļ�ϵͳ���� 'FAT12'
    u8 BS_FileSysType[8];

};
#pragma pack()

/*
 * BIOS������
 * ��¼��FAT�����Ļ�������
 * �ѽ��м򻯣�������������Ҫ������
 */
struct bios_pram_block
{
    u16 byte_per_sec;   /* ÿ���������ֽ��� */
    u8 sec_per_clus;    /* ÿ���ص������� */
    u16 rsvd_sec_cnt;   /* ������������(������������) */
    u8 num_fats;        /* FAT���� */
    u16 root_ent_cnt;   /* ��Ŀ¼��Ŀ�������� */
    u16 sec_per_fat;    /* ÿ��FATռ�������� */
    u32 tot_sec;        /* �������� */
    /* FAT12/16 EPBP */
    u32 vol_id;
    u8 vol_lab[11];
    u8 fs_type[8];
};

//�ļ�����������
typedef struct FileDescriptor
{
    u8 DIR_Name[8];   //�ļ���
    u8 DIR_Type[3];   //�ļ�����/��չ��
    u8 DIR_Attr;      //�ļ�����
    u8 Reserved[10];  //����λ
    u16 WrtTime;      //���һ��д��ʱ��
    u16 WrtDate;      //���һ��д������
    u16 DIR_FstClus;  //����Ŀ��Ӧ�Ŀ�ʼ����
    u32 DIR_FileSize; //�ļ���С
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

   RS	EQU P2.6
   RW	EQU P2.5
   E	EQU P2.7
   LCD	EQU P0
   BF	EQU P0.7
   ORG  0000H
   MOV DPTR,#TABLE
   MOV R0,#0 		//����һ��ȫ���ۼӱ��������ڳ���ȡ��
   MOV 34H,#9		//��ʼ�����������
   MOV 33H,#1		//�ҵĴ洢λ�ã���ʼ��Ϊ1
   MOV 38H,#1		//��Ϸ��ʼ���洢�ֽڵ�ַ��Ϊ1ʱ��ʾ��Ϸδ��ʼ   AJMP MAIN		//
   AJMP MAIN
   ORG  0100H

MAIN:
	 ACALL MAIN1   //��Ϸ��ʼǰ����Һ��������ʾ
	 ACALL MAIN0   //���п�ʼ�����ѯ
START:
	 ACALL  Change	//��������ܸı����
	 JNB p3.0,AddCoinContinue
	 ACALL D125ms
	 JNB p3.1,Scores   
     JNB P3.3,EndContinue	 //����
     AJMP START


Scores:
	 ACALL D10ms
	 JNB p3.1,Scoress
	 AJMP START
Scoress:

	 MOV 28H,#0	   //��ǰ����λ��1
	 DEC 33H	   //������1
	 MOV A,34H
	 CLR C
	 SUBB A,35H  
	 JZ SUBB37 	 //��һ�����ֺ͵ڶ���������ͬʱ��ת
	 MOV A,34H
	 CLR C
	 SUBB A,36H
	 JZ SUBB36	 //��һ�����ֺ͵�����������ͬʱ��ת
	 MOV A,35H
	 CLR C		  //��λ����
	 SUBB A,36H
	 JZ SUBB35	 //�ڶ������ֺ͵�����������ͬʱ��ת
	 AJMP detect  //��û����ת������ӳ���

AddCoinContinue:	//��Ϊtarget out of range ����������ת������ת��ת 
     AJMP AddCoin
continue:			//��Ϊtarget out of range ����������ת������ת��ת 
	 AJMP START
EndContinue:	  	//��Ϊtarget out of range ����������ת������ת��ת
     AJMP END1

SUBB37:
     INC 28H		 //��ǰ��������1 	 
     INC 29H	     //�ܻ��ִ���1
	 MOV A,34H
	 CLR C
	 SUBB A,36H	   //�ж������Ƿ���ͬ
	 JZ  all			 //Ϊ���ת���ټ�һ���ӳ���
	 AJMP assignment	//������ת�������ӳ���
SUBB36:
     INC 28H
     INC 29H
	 MOV A,34H
	 CLR C
	 SUBB A,35H		 //�ж������Ƿ���ͬ
	 JZ  all
	 AJMP assignment
SUBB35:
     INC 28H
     INC 29H
	 MOV A,35H
	 CLR C
	 SUBB A,34H
	 JZ  all
	 AJMP assignment

all:   //�ټ�һ
    INC 28H		//��ǰ���ּ�1
    INC 29H		//�ܻ��ּ�1
assignment:	  //����
    MOV A,29H		
	MOV B,#100		//�����λ
	DIV AB
	MOV 30H,A
	MOV A,B
	MOV B,#10		//����ʮλ�͸�λ
	DIV AB
	MOV 31H,A
	MOV A,B
	MOV 32H,A
    

detect:
    ACALL DisPlay
    JNB p3.1,detect		//ѭ����ⰴ���Ƿ��ɿ������û�������������Լ��İ�������
	ACALL MAIN1     	//��ʾ���ε÷ֽ���
	MOV 28H,#0			//��ǰ�������
	MOV A,33H
	CJNE A,#0,continue	 //û�б�ֱ�ӽ���
    AJMP END2


	
AddCoin:
	 MOV 20H,#25
	 ACALL D10ms			//��ʱ�ӳ�����������
	 JNB P3.0,Addcoin0
	 AJMP START
AddCoin0:
     DEC 20H
	 JB P3.0, AddCoin1
	 ACALL D10ms
	 MOV R5,20H
	 DJNZ R5, AddCoin0
	 CJNE R5, #00H, AddCoin1
XUNHUAN:	
	 INC 33H
	 MOV A, 33H
	 CJNE A, #16, XUNHUAN1
	 DEC 33H
XUNHUAN1:
	 ACALL D10ms
	 ACALL D10ms
	 ACALL D10ms
	 JNB P3.0, XUNHUAN
	 
	 AJMP START
	 
AddCoin1:
	 INC 33H				  //������1
	 MOV A, 33H
	 CJNE A, #16, AddCoin2
	 DEC 33H
AddCoin2:
	 AJMP START
MAIN0:
		MOV p0,#0
		JNB P3.2, START1	//��ʼ
		AJMP MAIN0
		

START1:
		ACALL MAIN1			//��ʾ�÷�
		ACALL DD10ms		//��ʱ�ӳ�����������
		MOV R7, #08
		MOV P2, #0FEH
		JNB P3.2, START2	//K3���ƿ�ʼ
		AJMP MAIN0
START2:		
		MOV R6, #200
START3:				
		MOV R5, #200		//����ѭ����������Ƶ��ٶ�
START4:		
		DJNZ R5, START4
		DJNZ R6, START3	
		MOV A, P2
		RL A				//��λʵ�������
		MOV P2, A
		DJNZ R7, START2		
		ACALL MAIN1			
		AJMP START

END1:   MOV	33H,#0
		ACALL MAIN1
		LCALL DD10ms		//��ʱ�ӳ�����������
		JNB P3.3, END2		//�ٴ��ж�K4�Ƿ���
		AJMP START
END2:		
		MOV P2, #18H		
		MOV R7, #07			//����ֵ����ѭ���ĳ���
END3:		
		MOV P0, #00H
		MOV A, P2
		SUBB A, #04H
		MOV P2, A			
		DJNZ R7, END3		//ʹP2.5ʵ�ֵ�ƽ��ת
		AJMP END2			//ʹ���򲻶Ͻ�����ѭ��

  											

Change:		      //���ָı�
	PUSH PSW	  //�ֳ�����
	PUSH Acc
    MOV R2,#0	  //��ʼ��R2Ϊ0
Change1:
    MOV A,R2
	CLR C		  //�����λ����ֹSUBBʱ����  
    SUBB A,#0	  
	JZ NUM0		  //AΪ��ʱ��ʾ��ǰ�ڶ���P2��,��ת����Ӧ��
	CLR C
	SUBB A,#1
	JZ NUM1
	CLR C
	SUBB A,#1
	JZ NUM2
	INC R0
	POP Acc
	POP PSW
	RET     
NUM0:
	MOV A,R0	  //��ȫ�ֱ�����ֵ��A
	MOV B,#3	  //������ֵ��B
	DIV AB		  //���
	MOV A,B		  //��������ֵ��A
	JZ NUM00	  //�����3���� ��ת����һ�ӳ���
	AJMP NUM000	  //������ת����ת��һ�����ӳ���
NUM00: //��һ  
    INC 36H		  //�������������ʾ�����ּ�һ
	MOV A,36H
	CJNE A,#10,NUM000    //�������10����ת����ת��һ���ӳ���
	MOV 36H,#0			 //����
NUM000://��ת��һ��
    MOV A,R2
	ADD A,#1		  //ת�Ƶ���һ������������ֽ�
	MOV R2,A
	AJMP change1

NUM1:
 
	INC 35H	 			  //
	MOV A,35H
	CJNE A,#10,NUM111
	MOV 35H,#0
NUM111:

	MOV A,R2
	ADD A,#1
	MOV R2,A
	AJMP Change1      
NUM2:				 //ͬ��

	MOV A,R0
	MOV B,#2		 //��2Ϊ0ʱ��ת
	DIV AB
	MOV A,B
	JNZ NUM22
	AJMP NUM222

NUM22:
    DEC 34H
    MOV A,34H
	CJNE A,#-1,NUM222
	MOV 34H,#9
NUM222:
    MOV A,R2
	ADD A,#1
	MOV R2,A
	AJMP Change1




DELAY:				  //�������ʾ�ӳ�
      MOV R5,#20
DEL0: MOV R6,#1
DEL1: MOV R7,#10 
DEL2: DJNZ R7,DEL2   
	  DJNZ R6,DEL1
	  DJNZ R5,DEL0
	  RET



DisPlay:				  //��̬��ʾ������ӳ���

    PUSH PSW
	PUSH Acc
    MOV R2,#4	  //��ʼ��R2Ϊ0
	MOV R1,#36H	  //R1��ʼ���洢��ַ
	MOV R3,#07H
STARTS:
    MOV A,R2
	MOV P2,A
	ADD A,#4
	MOV R2,A  
	MOV A,@R1
	DEC R1
	MOVC A,@A+DPTR
	MOV p0,A
	LCALL DELAY
    DJNZ R3,STARTS
	POP Acc
	POP PSW
	RET     

D500ms:	 //��ʱ500ms ʹ��3��ѭ��
      PUSH PSW
	  PUSH Acc

      MOV 40H,#100 

D12:
	  MOV 41H,#5
D3:      
      MOV 42H,#100
D4:

	  DJNZ 42H,D4
	  DJNZ 41H,D3    //((100*2+4)*5+3500)*100Լ500`000ms=0.5s
	  ACAll Display	//���ӳ��з���ˢ����ʾ����ֹ����ܵ���ʾ��ʧ
	  DJNZ 40H,D12   
	 

	  POP Acc
	  POP PSW
	  RET

D125ms:	 //��ʱ125ms ʹ��3��ѭ��
      PUSH PSW
	  PUSH Acc

      MOV 40H,#25 

DD12:
	  MOV 41H,#5
DD3:      
      MOV 42H,#100
DD4:

	  DJNZ 42H,DD4
	  DJNZ 41H,DD3    //((100*2+4)*5+3500)*25Լ125000ms=0.125s
	  ACAll Display	//���ӳ��з���ˢ����ʾ����ֹ����ܵ���ʾ��ʧ
	  DJNZ 40H,DD12   
	 

	  POP Acc
	  POP PSW
	  RET
D10ms:	//��ʱ10ms
      PUSH PSW
	  PUSH Acc

      MOV 40H,#5
D0:   MOV 41H,#4
D2:
	  MOV 42H,#250   //250*2*4*5=10000����=10ms
D1:
	  DJNZ 42H,D1
	  DJNZ 41H,D2
	  LCALL DisPlay		//�����ڴ�ѭ��ʱ�ڽ�����Ϸ֮����Ҫ��ʾ���������
	  DJNZ 40H,D0
	  POP Acc
	  POP PSW
	  RET

DD10ms:	//��ʱ10ms
      PUSH PSW
	  PUSH Acc

      MOV 40H,#5
DD0:   MOV 41H,#4
DD2:
	  MOV 42H,#250   //250*2*4*5=10000����=10ms
DD1:
	  DJNZ 42H,DD1
	  DJNZ 41H,DD2
	  DJNZ 40H,DD0
	  POP Acc
	  POP PSW
	  RET




MAIN1:	PUSH PSW	//LEDҺ����ʾ��
		PUSH Acc
		PUSH DPH
		PUSH DPL
		MOV 00H,#0
		MOV	A,#01H	//O1HΪ������������(����1)
		ACALL W_CMD //��LCD1602д������01H

		MOV A,#38H	//38HΪ������������(����6)
		ACALL W_CMD	//��LCD1602д������38H

		MOV A,#0CH	//0CHΪ��ʾ����ָ��(����4)
		ACALL W_CMD	//��LCD1602д������0CH

		MOV A,#14H	//14HΪ�����λָ��(����5)
		ACALL W_CMD	//��LCD1602д������14H

		MOV A,#83H 	//83H(80H+03H)��ʾλ������(����8)����һ�д�03H��ʼ
		ACALL W_CMD	//��LCD1602д������83H

		MOV R0,0	//�Ĵ���R0Ϊ��ʾ�ַ������ļ�����
		
	//	MOV 34H,#1
		MOV A,38H
		CJNE A,#1,GG //
		MOV 38H,#0
		MOV DPTR,#TAB1
		SJMP LOOP1

GG:		MOV A,33H
		CJNE A,#0,W1
		MOV DPTR,#TAB2
		SJMP LOOP1 

W1:		//MOV 30H,#2
		MOV A,28H	//ȡ���μӵķ�
		CJNE A,#0,SORE1
		MOV DPTR,#TAB3
		SJMP LOOP1

SORE1:	CJNE A,#1,SORE2
		MOV	DPTR,#TAB4
		SJMP LOOP1	

SORE2:	MOV DPTR,#TAB5
		SJMP LOOP1	
			
LOOP1:	MOV A,R0
		MOVC A,@A+DPTR //��ʾ�ַ���ASCIIд��A
		ACALL W_DATA   //��ʾ�ַ���ASCIIд��LCD1602
		INC R0		   //�ַ�������
		CJNE R0,#10,LOOP1	//��һ����ʾ10���ַ��Ƿ������
		MOV A,#0C0H	   //C0H(80H+40H)��ʾɨ������(����8)����2�д�40H
		ACALL W_CMD

LOOP2:	MOV A,R0
		MOVC A,@A+DPTR //����ʾ�ַ���ASCII������LCD1602
		ACALL W_DATA
		INC R0
		CJNE R0,#27,LOOP2 //�жϵڶ���16���ַ��Ƿ������
LOOP:	POP DPL
		POP DPH
		POP Acc
		POP PSW
		RET

WAIT:	MOV LCD,#0FFH  //���1602�Ƿ���æ״̬
		CLR RS		//��RS��0
		SETB RW		//��RW��1
		CLR	E		//�����������źţ�ʹ������ָ����Ч
		NOP
		SETB E
		JB BF,WAIT	//���æ��־BF��BF=1��ѭ���ȴ�
		RET

W_CMD:	ACALL WAIT	//д�������ӳ���
		MOV LCD,A
		CLR RS	   	//��RS,RW��0
		CLR RW
		SETB E		//��E�β����½���,����д��LCD1602
		NOP
		CLR E
		RET

W_DATA:	ACALL WAIT  //д�������ӳ���
		MOV LCD,A
		SETB RS		//��RW��1
		CLR RW		//��RW��0
		SETB E		//��E�˲����½���,ʹ����д��LCD1602
		NOP
		CLR E						   
		RET





TAB1:	DB'Welcome to'
		DB'   Game starts  '   
TAB2:	DB' Game Over'
		DB'     You Win  '

TAB3:	DB'  Regret ' 
		DB'     No score     '
TAB4:	DB'  Congrats'
		DB'   Get 1 score  '
TAB5:	DB' Well done'
		DB'   Get 2 score  '
TABLE:

	DB	3FH,  06H,  5BH,  4FH,  66H,  6DH  //0 1 2 3 4 5
	DB	7DH,  07H,  7FH,  6FH  //6 7 8 9 A b
	DB  77H,  7cH,	39H,  5eH,  79H,  71H
	  END

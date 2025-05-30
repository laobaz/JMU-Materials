    

    .data
          
Button: .word 0        #用于存储Button状态
A: .word 0             #用于存储第一个数码管t1
B: .word 0             #用于存储第二个数码管t2
C: .word 0             #用于存储第三个数码管t3
D: .word 0            #用于标记数码管后一个地址位置


    .text
     la $a0,Button
     la $a1,A         #把A的地址载入到a1中
     la $a2,B         #把B的地址载入到a2中
     la,$a3,C         #把C的地址载入到a3中
     la,$t5,D         #载入D地址到t5
     addi $s0 ,$s0,1  #设置s0为1 用于比较Button态和币数是否为0
     addi $s1,$s1,9  #设置s1为10，用于判断数码管是否到10，归零 
Main:  
     
     #lw $t1,0($a1)    #先从存储中读取三个数码管当前的状态
     #lw $t2,0($a2)    
     #lw $t3,0($a3)   
     addi $t1,$t1,1   #给赋予新的值  值可以随时变化
     addi $t3,$t3,1
     nop
     nop
     sw $t1,0($a1)    #写回到存储中，同时同步到数码管外设中
     sw $t3,0($a3) 
     nop	
     nop              #写入两个Bubble给用户判断时间

     addi $t2,$t2,1   #再写入数据 给予随机性
     addi $t3,$t3,1
     nop
     nop
     sw $t2,0($a2)    #
     sw $t3,0($a3)
     nop
     nop              #写入两个Bubble给用户判断时间

     addi $t2,$t2,1
     addi $t3,$t3,1
     nop
     nop
     sw $t3,0($a3) 
     sw $t2,0($a2)
     nop
     nop              #写入两个Bubble给用户判断时间 

     
re1:       
     bge $t1,$s1,ret1   #判断数字是否超出范围
re2:     
     bge $t2,$s1,ret2    
re3:
     bge $t3,$s1,ret3 
     j Main
                    
start:
     
     sw $0,0($a0)     #先把键盘状态归零
     lw $t8,4($t5)    #再从内存中取出币的数量
     bge $t8,$s0,x    #不为0时跳转到判断相同的子程序 
     j re1            #否则返回
x:
     addi $t8,$t8 -1  #每次游玩币都要减1
     sw $t8,4($t5)    #存入
     lw $t1,0($a1)    #先从存储中读取三个数码管当前的状态
     lw $t2,0($a2)    
     lw $t3,0($a3)
     beq $t1,$t2,xx   #先判断是否有两个相同
     beq $t2,$t3,xx 
     beq $t1,$t3,xx
     
     j re1
xx: 
     lw $t6,8($t5)    #先在分数上加1 
     addi $t6,$t6,1   
     sw $t6 8($t5)   
     beq $t2,$t3,xxx   #再判断是否有三个相同的情况 
     j re1
     
xxx:
    beq $t2,$t1,xxxx
    J re1             #没有返回
xxxx:
    lw $t6,8($t5)     #有再加1
    addi $t6,$t6,1
    sw $t6 8($t5)
    J re1
    
    
ret1:
    addi $t1,$0,0     #重置数码管数字  
    sw $t1,0($a1)    
    j re2
     
ret2:
    addi $t2,$0,0     
    sw $t2,0($a2)
    j re3          
ret3:
    addi $t3,$0,0
    sw $t3,0($a3)
    j Main 
    
                                
     lw $t4,0($a0)
     nop                           #读取键盘状态  为1时 跳转到判断子程序   用于中断部分跳转
     beq $t4,$s0,start       
     j re1
     
     
     
     
     
     
     

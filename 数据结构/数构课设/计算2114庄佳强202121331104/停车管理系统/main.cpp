#include"函数定义和结构体定义.h"
void Display(car_stop G)
{
    int i = G.top;
    if (i == -1)
        cout << "目前停车站为空" << endl;//当停车场为空时
    else
    {
        time_t t1;
        long int t = time(&t1);
        printf("\t车牌号\t\t停放时间\t当前所需支付金额\t停放位序\n");
        while (i != -1)
        {
            printf("\t%s\t\t%d时%d分\t\t%d元\t\t\t第%d个车位\n",
                G.stop[i].License_plate, (t - G.stop[i].in_time) / 360, (t - G.stop[i].in_time) / 60, (((int )(t - G.stop[i].in_time)/60+1)*(6)), i + 1);
            //停车时间 为当前时间-进车时间
            i--;
        }
    }
}
void Display_wait(Waitting P)
{
    int i = P.front;
    int k = 1;
    if(P.count==0)
        printf("便道目前为空\n");
    else
        printf("\t车牌号\t\t停放位序\n");
    while (i != P.rear && k <= P.count) //用读取的数量来作为判断的标准
    {
        printf("\t%s\t\t第%d个\n", P.wait[i].License_plate, k);
        i = (i + 1) % MAX_wait;
        k++;
    }
}
void car_P_come(Waitting& P,char C[])//当停车场满后会进行这个操作
{
    int i = P.front,c=0;
    if(P.count>0&&(P.front==P.rear+1)%MAX_wait)
        printf("便道已满，请下次再来！\n");
    else
    {
        while (c < P.count)//判断候车场是否有该车
        {
            if (strcmp(P.wait[i].License_plate, C) == 0)
            {
                printf("输入有误，此汽车已存在！\n");
                return;
            }
            i--;
            c++;
        }
        strcpy(P.wait[P.rear].License_plate, C);//进队操作
        P.rear = (P.rear + 1) % MAX_wait;
        P.count++;
        printf("牌照为%s的汽车停入便道上\n", C);
    }
}
void car_come(car_stop& G, Waitting& P)
{
    char C[20];
    printf("请输入即将停车的车牌号：");
    getchar();
    gets_s(C);      //vs特性
    int k;
    k = strlen("闽D 12345");
    if (strlen(C) != k)
    {
        printf("输入错误！！！\n");
    }
    else
    {
        int i = G.top;
        while (i != -1) {
            if (strcmp(G.stop[i].License_plate, C) == 0) {     //判断停车场是否存在当前车辆
                printf("输入有误，此汽车已存在！\n");
                return;
            }
            i--;
        }
        if (G.top >= MAX_car - 1)
        {
            printf("停车场已满\n请转到候车场\n");
            car_P_come(P, C);
        }
        else
        {
            time_t t1;
            long int t = time(&t1);                 //时间
            char* t2;
            t2 = ctime(&t1);                        //当前时间
            G.stop[++G.top].in_time = t;
            strcpy(G.stop[G.top].ct, t2);//复制信息到G中
            strcpy(G.stop[G.top].License_plate, C);
            printf("牌照为%s的汽车停入停车位的第%d车位，当前时间：%s\n", C, G.top + 1, t2);
        }
    }
    printf("\n\t\t\t是否继续进行进车？是：1，否：2\n");//判断是否进行进车
    int c;
    cin >> c;
    if (c == 1)
        car_come(G, P);
    else if (c == 2)
        return;
    else
        printf("输入不对，再试试吧！\n");

}
void Car_Leave(car_stop& G,Waitting &P)
{
    char C[20];
    printf("请输入即将离开的车牌号：");
    getchar();//清除输出的回车，防止被gets读取(以下同理）
    gets_s(C);//VS特定识别符
    int i,flag=1;
    if (G.top >= 0)
    {
        for (i = G.top; i >= 0; i--)
        {
            if (strcmp(G.stop[i].License_plate, C) == 0)//寻找要出的车辆
            {
                flag = 0;//标记位
                break;
            }
                
        }
    }
    if (flag == 0)//找到
    {
        Car temp;
        int j = i;
        temp = G.stop[i];
        while (j <= G.top&&j>-1)
        {
            G.stop[j] = G.stop[j + 1];//将车辆前移
            j++;
        }
        G.top--;
        time_t t1;//利用系统自带的时间函数计算出入时间
        long int t = time(&t1);//
        temp.out_time = t;
        char* t2;
        t2 = ctime(&t1);//获得当前时间
        printf("离开时间%s\n需付费%d元\n", t2, (((int)(t - G.stop[i].in_time) / 60 + 1) *6) );

        while (G.top < MAX_car - 1)//如果候车场不为空时，进入停车场
        {
            if (P.count == 0)
                break;
            else
            {
                
                strcpy(G.stop[++G.top].License_plate, P.wait[P.front].License_plate);
                printf("牌照为%s的汽车从便道中进入停车位的%d车位\n", P.wait[P.front].License_plate, G.top + 1);
                time_t t1;
                long int t = time(&t1);
                char* t2;
                G.stop[G.top].in_time = t;
                P.front = (P.front + 1) % MAX_wait;//循环队列
                P.count--;
            }

        
        }
    }
    else
        printf("停车场内没有该汽车的信息！\n");
}

void P_Leave( Waitting& P)//
{
    int i,flag=1;
    char C[20];
    printf("请输入即将离开的车牌号：");
    getchar();
    gets_s(C);
    if (P.count <= 0)
    {
        printf("便道上不存在汽车!\n");
        return;
    }
    i = P.front;
    int c = 0;
    while (c<P.count)
    {
        if (strcmp(P.wait[i].License_plate, C) == 0)//寻找相同的车牌号
        {
            flag = 0;
            break;
        }
        i++;
        c++;
    }
    if (flag == 0)
    {
        printf("\n牌照为%s的汽车离开候车场，不收取任何费用！\n", P.wait[i].License_plate);
        
        c = 0;
        int j = i;
        int temp = (P.rear - i + MAX_wait) % MAX_wait;//计算出从i(找到的队列下标)到最后一个队列有几个元素，作为判断标准
        while (c<temp)
        {
            P.wait[j] = P.wait[((j + 1) % MAX_wait)];//候车站队列前移
            j++;
            c++;
        }
        P.count--;
    }
}

void search(car_stop G, Waitting P)
{
    char C[20];
    printf("请输入要搜索的车牌号：\n");
    getchar();
    gets_s(C);
    int i,flag=0,k,j;
    time_t t1;
    long int t = time(&t1);
    if(G.top>=0)
        for (i = G.top; i >=0; i--)
        {
            if (strcmp(G.stop[i].License_plate, C) == 0)
            {
                printf("此汽车在停车场内，信息如下：\n");
                printf("\t车牌号\t\t停车位序\t当前所需支付金额\t进入时间\t\n");
                printf("\t%s\t\t第%d个\t\t%d元\t\t\t%s", G.stop[i].License_plate, i + 1, (((int)(t - G.stop[i].in_time) / 60 + 1) * 6), G.stop[i].ct);
                flag = 1;
                break;
            }
        }
    if (flag == 0 && P.count > 0)//停车场没有，候车场不为空时
    {
        i = P.front, k = 1, j = P.rear;
        while (i != j)
        {
            if (strcmp(P.wait[i].License_plate, C) == 0)
            {
                printf("此汽车在停便道上\n");
                printf("\t车牌号\t\t停车位序\n");
                printf("\t%s\t第%d个", P.wait[i].License_plate, k);
                flag = 1;
                break;
            }
            i++;
            k++;

        }
    }
    if (flag==0)
        printf("停车场内外不存在该汽车信息！\n");

}





void welcome(car_stop &G,Waitting &P)
{

    printf("\t————————————目前停车场状况—————————————\n");
    printf("\t停车场共有%d个车位,当前停车场共有%d辆车,等候区共有%d辆车\n", MAX_car, G.top + 1, (P.rear - P.front + MAX_wait) % MAX_wait);
    printf("\t——————————————————————————————\n");
    printf("\t|                   1.停车场停车信息                        |\n");
    printf("\t|                   2.便道上停车信息                        |\n");
    printf("\t|                   3.汽车到达停车场                        |\n");
    printf("\t|                   4.汽车离去停车场                        |\n");
    printf("\t|                   5.汽车离去候车场                        |\n");
    printf("\t|                   6.查找汽车功能　                        |\n");
    printf("\t|                   7.退出管理系统                          |\n");
    printf("\t|收费标准：本停车场按照%.0f元/分钟计费，望周知(时间向上取整)|\n", 60 * Price);
    printf("\t|                                                           |\n");
    printf("\t————————————————————————————————\n");


}

int main()
{
    int flag=1;
    car_stop G;//
    G.top = -1;//初始化栈
    Waitting P;
    P.rear = P.front = 0;//初始化队列
    P.count = 0;
    while (flag)
    {
        system("cls");//清空当前界面
        welcome(G, P);
        int i;
        cin >> i;
        switch (i)
        {
        case 1:
        {
            Display(G);
            break;
        }
        case 2:
        {
            Display_wait(P);
            break;
        }
        case 3:
        {
            car_come(G, P);
            break;
        }
        case 4:
        {
            Car_Leave(G, P);
            break;
        }
        case 5:
        {
            P_Leave(P);
            break;
        }
        case 6:
        {
            search(G, P);
            break;
        }
        case 7:
        {
            printf("\n欢迎您再次使用本系统呦 \n\n");
            flag = 0;
            return 0;
        break;

        }
        default:
            break;
        }
        while (1)
        {
            printf("\n输出0返回\n");
            cin >> i;
            if (i == 0)
                break;
            else
                printf("您的输入有误，请重新输入\n");
        }
    }
}

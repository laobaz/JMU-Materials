#include"��������ͽṹ�嶨��.h"
void Display(car_stop G)
{
    int i = G.top;
    if (i == -1)
        cout << "Ŀǰͣ��վΪ��" << endl;//��ͣ����Ϊ��ʱ
    else
    {
        time_t t1;
        long int t = time(&t1);
        printf("\t���ƺ�\t\tͣ��ʱ��\t��ǰ����֧�����\tͣ��λ��\n");
        while (i != -1)
        {
            printf("\t%s\t\t%dʱ%d��\t\t%dԪ\t\t\t��%d����λ\n",
                G.stop[i].License_plate, (t - G.stop[i].in_time) / 360, (t - G.stop[i].in_time) / 60, (((int )(t - G.stop[i].in_time)/60+1)*(6)), i + 1);
            //ͣ��ʱ�� Ϊ��ǰʱ��-����ʱ��
            i--;
        }
    }
}
void Display_wait(Waitting P)
{
    int i = P.front;
    int k = 1;
    if(P.count==0)
        printf("���ĿǰΪ��\n");
    else
        printf("\t���ƺ�\t\tͣ��λ��\n");
    while (i != P.rear && k <= P.count) //�ö�ȡ����������Ϊ�жϵı�׼
    {
        printf("\t%s\t\t��%d��\n", P.wait[i].License_plate, k);
        i = (i + 1) % MAX_wait;
        k++;
    }
}
void car_P_come(Waitting& P,char C[])//��ͣ�������������������
{
    int i = P.front,c=0;
    if(P.count>0&&(P.front==P.rear+1)%MAX_wait)
        printf("������������´�������\n");
    else
    {
        while (c < P.count)//�жϺ򳵳��Ƿ��иó�
        {
            if (strcmp(P.wait[i].License_plate, C) == 0)
            {
                printf("�������󣬴������Ѵ��ڣ�\n");
                return;
            }
            i--;
            c++;
        }
        strcpy(P.wait[P.rear].License_plate, C);//���Ӳ���
        P.rear = (P.rear + 1) % MAX_wait;
        P.count++;
        printf("����Ϊ%s������ͣ������\n", C);
    }
}
void car_come(car_stop& G, Waitting& P)
{
    char C[20];
    printf("�����뼴��ͣ���ĳ��ƺţ�");
    getchar();
    gets_s(C);      //vs����
    int k;
    k = strlen("��D 12345");
    if (strlen(C) != k)
    {
        printf("������󣡣���\n");
    }
    else
    {
        int i = G.top;
        while (i != -1) {
            if (strcmp(G.stop[i].License_plate, C) == 0) {     //�ж�ͣ�����Ƿ���ڵ�ǰ����
                printf("�������󣬴������Ѵ��ڣ�\n");
                return;
            }
            i--;
        }
        if (G.top >= MAX_car - 1)
        {
            printf("ͣ��������\n��ת���򳵳�\n");
            car_P_come(P, C);
        }
        else
        {
            time_t t1;
            long int t = time(&t1);                 //ʱ��
            char* t2;
            t2 = ctime(&t1);                        //��ǰʱ��
            G.stop[++G.top].in_time = t;
            strcpy(G.stop[G.top].ct, t2);//������Ϣ��G��
            strcpy(G.stop[G.top].License_plate, C);
            printf("����Ϊ%s������ͣ��ͣ��λ�ĵ�%d��λ����ǰʱ�䣺%s\n", C, G.top + 1, t2);
        }
    }
    printf("\n\t\t\t�Ƿ�������н������ǣ�1����2\n");//�ж��Ƿ���н���
    int c;
    cin >> c;
    if (c == 1)
        car_come(G, P);
    else if (c == 2)
        return;
    else
        printf("���벻�ԣ������԰ɣ�\n");

}
void Car_Leave(car_stop& G,Waitting &P)
{
    char C[20];
    printf("�����뼴���뿪�ĳ��ƺţ�");
    getchar();//�������Ļس�����ֹ��gets��ȡ(����ͬ��
    gets_s(C);//VS�ض�ʶ���
    int i,flag=1;
    if (G.top >= 0)
    {
        for (i = G.top; i >= 0; i--)
        {
            if (strcmp(G.stop[i].License_plate, C) == 0)//Ѱ��Ҫ���ĳ���
            {
                flag = 0;//���λ
                break;
            }
                
        }
    }
    if (flag == 0)//�ҵ�
    {
        Car temp;
        int j = i;
        temp = G.stop[i];
        while (j <= G.top&&j>-1)
        {
            G.stop[j] = G.stop[j + 1];//������ǰ��
            j++;
        }
        G.top--;
        time_t t1;//����ϵͳ�Դ���ʱ�亯���������ʱ��
        long int t = time(&t1);//
        temp.out_time = t;
        char* t2;
        t2 = ctime(&t1);//��õ�ǰʱ��
        printf("�뿪ʱ��%s\n�踶��%dԪ\n", t2, (((int)(t - G.stop[i].in_time) / 60 + 1) *6) );

        while (G.top < MAX_car - 1)//����򳵳���Ϊ��ʱ������ͣ����
        {
            if (P.count == 0)
                break;
            else
            {
                
                strcpy(G.stop[++G.top].License_plate, P.wait[P.front].License_plate);
                printf("����Ϊ%s�������ӱ���н���ͣ��λ��%d��λ\n", P.wait[P.front].License_plate, G.top + 1);
                time_t t1;
                long int t = time(&t1);
                char* t2;
                G.stop[G.top].in_time = t;
                P.front = (P.front + 1) % MAX_wait;//ѭ������
                P.count--;
            }

        
        }
    }
    else
        printf("ͣ������û�и���������Ϣ��\n");
}

void P_Leave( Waitting& P)//
{
    int i,flag=1;
    char C[20];
    printf("�����뼴���뿪�ĳ��ƺţ�");
    getchar();
    gets_s(C);
    if (P.count <= 0)
    {
        printf("����ϲ���������!\n");
        return;
    }
    i = P.front;
    int c = 0;
    while (c<P.count)
    {
        if (strcmp(P.wait[i].License_plate, C) == 0)//Ѱ����ͬ�ĳ��ƺ�
        {
            flag = 0;
            break;
        }
        i++;
        c++;
    }
    if (flag == 0)
    {
        printf("\n����Ϊ%s�������뿪�򳵳�������ȡ�κη��ã�\n", P.wait[i].License_plate);
        
        c = 0;
        int j = i;
        int temp = (P.rear - i + MAX_wait) % MAX_wait;//�������i(�ҵ��Ķ����±�)�����һ�������м���Ԫ�أ���Ϊ�жϱ�׼
        while (c<temp)
        {
            P.wait[j] = P.wait[((j + 1) % MAX_wait)];//��վ����ǰ��
            j++;
            c++;
        }
        P.count--;
    }
}

void search(car_stop G, Waitting P)
{
    char C[20];
    printf("������Ҫ�����ĳ��ƺţ�\n");
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
                printf("��������ͣ�����ڣ���Ϣ���£�\n");
                printf("\t���ƺ�\t\tͣ��λ��\t��ǰ����֧�����\t����ʱ��\t\n");
                printf("\t%s\t\t��%d��\t\t%dԪ\t\t\t%s", G.stop[i].License_plate, i + 1, (((int)(t - G.stop[i].in_time) / 60 + 1) * 6), G.stop[i].ct);
                flag = 1;
                break;
            }
        }
    if (flag == 0 && P.count > 0)//ͣ����û�У��򳵳���Ϊ��ʱ
    {
        i = P.front, k = 1, j = P.rear;
        while (i != j)
        {
            if (strcmp(P.wait[i].License_plate, C) == 0)
            {
                printf("��������ͣ�����\n");
                printf("\t���ƺ�\t\tͣ��λ��\n");
                printf("\t%s\t��%d��", P.wait[i].License_plate, k);
                flag = 1;
                break;
            }
            i++;
            k++;

        }
    }
    if (flag==0)
        printf("ͣ�������ⲻ���ڸ�������Ϣ��\n");

}





void welcome(car_stop &G,Waitting &P)
{

    printf("\t������������������������Ŀǰͣ����״����������������������������\n");
    printf("\tͣ��������%d����λ,��ǰͣ��������%d����,�Ⱥ�������%d����\n", MAX_car, G.top + 1, (P.rear - P.front + MAX_wait) % MAX_wait);
    printf("\t������������������������������������������������������������\n");
    printf("\t|                   1.ͣ����ͣ����Ϣ                        |\n");
    printf("\t|                   2.�����ͣ����Ϣ                        |\n");
    printf("\t|                   3.��������ͣ����                        |\n");
    printf("\t|                   4.������ȥͣ����                        |\n");
    printf("\t|                   5.������ȥ�򳵳�                        |\n");
    printf("\t|                   6.�����������ܡ�                        |\n");
    printf("\t|                   7.�˳�����ϵͳ                          |\n");
    printf("\t|�շѱ�׼����ͣ��������%.0fԪ/���ӼƷѣ�����֪(ʱ������ȡ��)|\n", 60 * Price);
    printf("\t|                                                           |\n");
    printf("\t����������������������������������������������������������������\n");


}

int main()
{
    int flag=1;
    car_stop G;//
    G.top = -1;//��ʼ��ջ
    Waitting P;
    P.rear = P.front = 0;//��ʼ������
    P.count = 0;
    while (flag)
    {
        system("cls");//��յ�ǰ����
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
            printf("\n��ӭ���ٴ�ʹ�ñ�ϵͳ�� \n\n");
            flag = 0;
            return 0;
        break;

        }
        default:
            break;
        }
        while (1)
        {
            printf("\n���0����\n");
            cin >> i;
            if (i == 0)
                break;
            else
                printf("����������������������\n");
        }
    }
}

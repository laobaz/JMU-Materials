#include"init.h"
#include"function.h"

int main()
{
    cout << "������Ҫ�������﷨:" << endl;
    input();   //�ķ����봦��
    Augmented_grammar();        // ���������ķ�
    printProductions();         // ��ӡ�洢�Ĳ���ʽ����
    calVN();                    // ��¼���з��ս��
    calVT();                    // ��¼�����ս�� ������
    printVNT();                 // ��ӡ���еķ��ս�����ս��
    Initialize_Project();       //��ʼ����Ŀ��
    initFcollections();         // ��ʼ������ʽ���ϣ������з��ս�������ȥ��
    calFIRST();                 // ����FIRST����
    calFOLLOW();                // ����FOLLOW����
    printFirstFollow();         // ��ӡFIRST FOLLOW����
    Project_Set_Specification_Family(); //�����﷨������Ŀ�弯
    ActionTable();               //����Action��
    print_Project();             //��ӡ��Ŀ��
    print_family_table();       //��ӡ�淶��
    printGototable();            //��ӡgoto��
    printActiontables();         //��ӡSLR��

    if (judgeG())                // ���и��ķ�
    {
       analysis_SLR();        // �﷨����������ַ���
    }
    return 0;
}
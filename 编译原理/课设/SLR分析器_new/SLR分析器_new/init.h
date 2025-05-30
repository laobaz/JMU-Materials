#pragma once
#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <map>
#include <set>
#include <iomanip>
#include <algorithm>
using namespace std;


//MOVEIN  // �ƽ���Ŀ
//REDUCE   // ��Լ��Ŀ
//TOBEREDUCE    // ��Լ��Ŀ
//ACCEPTION      // ������Ŀ
//MRCONFLICT     // �ƽ�-��Լ��ͻ
//RRCONFLICT     // ��Լ��Լ��ͻ
//NONECONFLICT   // �޳�ͻ


//ȫ�ֱ�������
//�������뷽������
set<string> nonterminal;  //���ս������
set<string> Finalization;  //�ս������
string  wait_ananly;    //����Ĵ��������ִ�
string G_start; //�ķ���ʼ��


class production {
public:
    string left;            //����ʽ��
    vector<string> right;   //����ʽ�Ҳ�
    int index;              //����ʽ���
    production(const string& str) {
        left = str;
        right.clear();
        index = -1;
    }
    production() {
        left.clear();
        right.clear();
        index = -1;
    }
    void push(const string& str) {
        right.push_back(str);
    }
    void print() {
        cout << left << "::=";
        //vector<string>::iterator it = right.begin();
        //for (; it != right.end(); it++) {
        //    cout << (*it) << " ";
        //}
        for (auto obj : right) {
            cout << obj << " ";
        }
        cout << endl;
    }
    production& operator=(const production& p) {
        this->index = p.index;
        this->left = p.left;
        this->right = p.right;
        return *this;
    }
};

// һ�����ս����FIRST & FOLLOW����
class first_follow {
public:
    string vn;      //���ս��
    set<string> vfirst; //FIRST����
    set<string> vfollow; //FOLLOW����
    first_follow(const string& str) {   // ���캯��
        vn = str;
        vfirst.clear();
        vfollow.clear();
    }
    void insert_first(string t) {     // FIRST���ϲ���
        if (vfirst.empty() == true || vfirst.count(t) < 1) {
            vfirst.insert(t);
        }
    }
    void insert_follow(string t) {     // FOLLOW���ϲ���
        if (vfollow.empty() == true || vfollow.count(t) < 1) {
            vfollow.insert(t);
        }

    }
    void print() {   // ���FIRST��FOLLOW����
        if (vfirst.empty()) {
            cout << "FIRST:NULL" << endl;
        }
        else {
            cout << "FIRST[" << vn << "] = { ";
            set<string>::iterator it1 = vfirst.begin();
            cout << (*it1);
            it1++;
            for (; it1 != vfirst.end(); it1++) {
                cout << ", " << (*it1);
            }
            cout << " }\t\t\t";
        }

        if (vfollow.empty()) {
            cout << "FOLLOW:NULL" << endl;
        }
        else {
            cout << "FOLLOW[" << vn << "] = {  ";
            set<string>::iterator it2 = vfollow.begin();
            cout << (*it2);
            it2++;
            for (; it2 != vfollow.end(); it2++) {
                cout << ",  " << (*it2);
            }
            cout << "}" << endl;
        }

    }
    bool operator==(const first_follow& ff) {
        if (ff.vn == this->vn)
            return true;
        else
            return false;
    }
};

//һ�����ʽ�Ĺ���
class Project {
public:
    int index;   // ��Ŀ��Ŷ�Ӧ����ʽ�ı��
    int index_point; // ����ʽ�Ҳ�����λ��
    int number = 0; // ��Ŀ���
    string type;      // ���ʽ����
    string leftstr;     // ����ʽ�󲿷��ս��
    string rightstr;      // ���ұߵĵ�һ������

    Project(int pro_index, int project_num) {
        index = pro_index;
        index_point = 0;
        number = project_num;
        type.clear();
        leftstr.clear();
        rightstr.clear();
    }
    Project() {
        number = -1;
        index = -1;
        index_point = -1;
        type.clear();
        leftstr.clear();
        rightstr.clear();
    }
    // ��ӡ��ǰ��Ŀ
    void print();
};


//���ڴ洢��Ŀ���淶��
class Family {

public:
    //�洢����Ŀ
    vector <int> project_num;
    //״̬
    int family_num;
    Family(int num) {
        family_num = num;
    }
    bool operator==(const Family& a) {
        for (int i = 0; i < a.project_num.size(); i++) {
            
            if (find(project_num.begin(), project_num.end(), a.project_num.at(i)) == project_num.end()) {
                return false;
            }
        }
        return true;
    }
};

class Goto {
public:
    string nonterminal;  //���ս��
    int  state; //״̬ I0....
    int FN;      //ָ�����
    Goto(const string str, int state, int Family_num) {
        nonterminal = str;
        this->state = state;
        FN = Family_num;
    }


};
class Action {
public:
    string Finalization;//�ս��
    int state; //״̬
    string F2S; //<�ս��,״̬>
    Action(string F, int state, string Fn = "error") {
        this->state = state;
        Finalization = F;
        F2S = Fn;
    }
    Action() {
        this->F2S.clear();
        this->Finalization.clear();
        this->state = 0;
    }
    Action operator=(Action& a) {
        this->F2S = a.F2S;
        this->Finalization = a.Finalization;
        this->state = a.state;
        return *this;
    }
};


vector<production> productions;             //����ʽ����
vector<first_follow> fcollections;          //���ս����FIRST���Ϻ�FOLLOW����
vector<Family> Family_table;                //��Ŀ��
stack<string> GAnalasis;                    //�﷨����ջ
vector<Project>projects;                     //��Ŀ����
vector<Goto> gototables;
vector<Action> Actiontables;
stack<string>Family_stack;


void input();                       // �ķ����봦����
void Augmented_grammar();           // ���������ķ�
void printProductions();            // ���ԣ���ӡ�洢�Ĳ���ʽ����
void printVNT();                    // ���ԣ���ӡ���еķ��ս�����ս��
void calVN();                       // ��¼���з��ս��
void calVT();                       // ��¼�����ս��
void initFcollections();            // ��ʼ������ʽ���ϣ������з��ս�������ȥ��
void calFIRST();                    // ����FIRST����
void calFOLLOW();                   // ����FOLLOW����
void printFirstFollow();            // ��ӡFIRST FOLLOW����
void initAnalysisTable();           // ��ʼ��SLRԤ�������
bool isVN(string str);              // �ж��Ƿ�Ϊ���ս��
string getpro(int j);               // �õ�productions[j]�Ĳ���ʽ�ַ���
bool SLR_parse();                   // �ж��Ƿ�ΪSLR�ķ�
bool judgeG();                      // ���и��ķ�
void inputIstr();                   // ������������ַ���
string getStackStr(const stack<string> &stack);               // ����﷨����ջ�е���������
void analysisIstr();                // �﷨����������ַ���
void Initialize_Project();          // ��ʼ����Ŀ��
void Project_Set_Specification_Family();       // ����Ŀ���淶��
void ActionTable();
void print_family_table();          //��ӡfamilytable��

production find_production(int index);
void print_production(int i, const production& prod);
void print_family_table();
void printGototable();
void printActiontables();

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


//MOVEIN  // 移进项目
//REDUCE   // 归约项目
//TOBEREDUCE    // 待约项目
//ACCEPTION      // 接受项目
//MRCONFLICT     // 移进-归约冲突
//RRCONFLICT     // 归约归约冲突
//NONECONFLICT   // 无冲突


//全局变量定义
//对象定义与方法声明
set<string> nonterminal;  //非终结符集合
set<string> Finalization;  //终结符集合
string  wait_ananly;    //输入的待分析的字串
string G_start; //文法开始符


class production {
public:
    string left;            //产生式左部
    vector<string> right;   //产生式右部
    int index;              //产生式编号
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

// 一个非终结符的FIRST & FOLLOW集合
class first_follow {
public:
    string vn;      //非终结符
    set<string> vfirst; //FIRST集合
    set<string> vfollow; //FOLLOW集合
    first_follow(const string& str) {   // 构造函数
        vn = str;
        vfirst.clear();
        vfollow.clear();
    }
    void insert_first(string t) {     // FIRST集合插入
        if (vfirst.empty() == true || vfirst.count(t) < 1) {
            vfirst.insert(t);
        }
    }
    void insert_follow(string t) {     // FOLLOW集合插入
        if (vfollow.empty() == true || vfollow.count(t) < 1) {
            vfollow.insert(t);
        }

    }
    void print() {   // 输出FIRST、FOLLOW集合
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

//一个表达式的过程
class Project {
public:
    int index;   // 项目编号对应产生式的标号
    int index_point; // 产生式右部·的位置
    int number = 0; // 项目编号
    string type;      // 表达式类型
    string leftstr;     // 产生式左部非终结符
    string rightstr;      // ·右边的第一个符号

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
    // 打印当前项目
    void print();
};


//用于存储项目集规范族
class Family {

public:
    //存储的项目
    vector <int> project_num;
    //状态
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
    string nonterminal;  //非终结符
    int  state; //状态 I0....
    int FN;      //指向的蔟
    Goto(const string str, int state, int Family_num) {
        nonterminal = str;
        this->state = state;
        FN = Family_num;
    }


};
class Action {
public:
    string Finalization;//终结符
    int state; //状态
    string F2S; //<终结符,状态>
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


vector<production> productions;             //产生式集合
vector<first_follow> fcollections;          //非终结符的FIRST集合和FOLLOW集合
vector<Family> Family_table;                //项目蔟
stack<string> GAnalasis;                    //语法分析栈
vector<Project>projects;                     //项目集合
vector<Goto> gototables;
vector<Action> Actiontables;
stack<string>Family_stack;


void input();                       // 文法输入处理函数
void Augmented_grammar();           // 构造增广文法
void printProductions();            // 测试，打印存储的产生式集合
void printVNT();                    // 测试，打印所有的非终结符，终结符
void calVN();                       // 记录所有非终结符
void calVT();                       // 记录所有终结符
void initFcollections();            // 初始化产生式集合（将所有非终结符加入进去）
void calFIRST();                    // 计算FIRST集合
void calFOLLOW();                   // 计算FOLLOW集合
void printFirstFollow();            // 打印FIRST FOLLOW集合
void initAnalysisTable();           // 初始化SLR预测分析表
bool isVN(string str);              // 判断是否为非终结符
string getpro(int j);               // 得到productions[j]的产生式字符串
bool SLR_parse();                   // 判断是否为SLR文法
bool judgeG();                      // 评判该文法
void inputIstr();                   // 输入待分析的字符串
string getStackStr(const stack<string> &stack);               // 获得语法分析栈中的所有内容
void analysisIstr();                // 语法分析输入的字符串
void Initialize_Project();          // 初始化项目集
void Project_Set_Specification_Family();       // 求项目集规范族
void ActionTable();
void print_family_table();          //打印familytable表

production find_production(int index);
void print_production(int i, const production& prod);
void print_family_table();
void printGototable();
void printActiontables();

#include"init.h"
#include"function.h"

int main()
{
    cout << "请输入要分析的语法:" << endl;
    input();   //文法输入处理
    Augmented_grammar();        // 构造增广文法
    printProductions();         // 打印存储的产生式集合
    calVN();                    // 记录所有非终结符
    calVT();                    // 记录所有终结符 包括ε
    printVNT();                 // 打印所有的非终结符，终结符
    Initialize_Project();       //初始化项目集
    initFcollections();         // 初始化产生式集合（将所有非终结符加入进去）
    calFIRST();                 // 计算FIRST集合
    calFOLLOW();                // 计算FOLLOW集合
    printFirstFollow();         // 打印FIRST FOLLOW集合
    Project_Set_Specification_Family(); //分析语法建造项目族集
    ActionTable();               //建造Action表
    print_Project();             //打印项目表
    print_family_table();       //打印规范蔟
    printGototable();            //打印goto表
    printActiontables();         //打印SLR表

    if (judgeG())                // 评判该文法
    {
       analysis_SLR();        // 语法分析输入的字符串
    }
    return 0;
}
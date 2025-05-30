
#include <iostream>
#include <string>
#include <unordered_map>
#include<map>
#include <algorithm>
#include<vector>
#include <fstream>
using namespace std;




//用于识别是基本字或标识符 = { "int", "main", "void", "if", "char", "return", "short", "long", "short", "signed", "ensigned",
vector<string> Reserved = { "restrict", "struct", "union", "enum", "typedef", "sizeof", "auto", "static", "register", "extern", "const",
        "volatitle", "break", "goto", "else", "switch", "case", "default", "continue", "do", "double", "float","int"};// 保留字表
vector<string> Operator = { "+", "-", "*", "/", "%", ".", "++", "--", ">", "<", "=",  "?", "'",
      "\"", "==", ">=", "<=", "!=", "&", "|", "~", "^", "<<", ">>", "!", "&&", "||", "+=", "-=", "*=", "/=",
      "%=", "&=", "|=", "^=", ">>=", "<==", "*", "&" , ":" ,"<>"};//符号表
vector<string> decollator = { "(", ")", "{", "}", ";", "[", "]" ,","};//分割符

  unordered_map<string,int> Reserved_word;//保留字哈希
  unordered_map<string, int> Operator_word;//符号表哈希
  unordered_map<string, int> decollator_word;////分隔符哈希
  int constant=0;//常数
  int identifier = 0;//标志符
  



  void init_vector(vector<string> &ve, string str[]) {
      int i = 0;
      while (!str[i].empty()) {
          ve.push_back(str[i]);
          i++;
      }
  }


  void init() {

     // init_vector(Reserved, Reserved_t);
     // init_vector(Operator, Operator_t);
     // init_vector(decollator, decollator_t);
      int j = 1;
       constant = j;//常数
      j++;
       identifier = j;//标志符
      j++;
      for (int i = 1; i <= Reserved.size(); i++) {

          Reserved_word.insert({ Reserved.at(i-1) ,i + j});
      }
      j = j + Reserved.size();
      for (int i = 1; i <= Operator.size() ; i++) {
          Operator_word.insert({Operator.at(i-1) ,i + j});
      }
      j = j + Operator.size();
      for (int i = 1; i <= decollator.size(); i++) {
          decollator_word.insert({ decollator.at(i-1),i + j });
      }
      j = j + decollator.size();

  }

  void save_file(const vector <string> &result) {
      ofstream ofs;
      ofs.open("../result.txt", ios::out);
      for (int i = 0; i < result.size(); i++) {
          ofs << result[i] << endl;
      }
      ofs << "常数码 ：1" << endl;
      ofs << "标识符码 ：2" << endl;
      ofs << "关键字码：" << endl;
      for (auto it : Reserved_word) 
          ofs << "(  " << it.first << " , " << it.second <<"  )" << endl;
      
      ofs << "符号码" << endl;
      for (auto it : Operator_word)
          ofs << "(  " << it.first << " , " << it.second << "  )" << endl;
      ofs << "分隔符码" << endl;
      for (auto it : decollator_word)
          ofs << "(  " << it.first << " , " << it.second << "  )" << endl;
      
      ofs.close();
  }
 
int main()
{
     
    init();
    
   
    vector <string> result;//记录结果

    string str1, str;
    while (cin >> str1)
    {
        if (str1 == "end") {
            break;
        }
        //读入代码（字符串形式）
        str = str + ' ' + str1;
    }
    //开始处理读入的代码
    int length_str = str.length();
    string result_temp;
    int key=0;
    string word;
    for (int i = 0; i < length_str; i++)
    {
        //当遇到空格或换行时，跳过继续执行
        if (str[i] == ' ' || str[i] == '\n') continue;
        //识别常数
        else if (isdigit(str[i]))
        {

            //以字符串形式表示这个常数
            while (isdigit(str[i]))
            {
                word += str[i];
                i++;
            }
            i--;
            key = 1;
        }
        //识别基本字或标识符
        else if (isalpha(str[i]))
        {
            
            //以字符串形式表示这个基本字或者标识符
            while (isdigit(str[i]) || isalpha(str[i]))
            {
                word += str[i];
                i++;
            }
            i--;
            result_temp;
            vector<string>::iterator it= find(Reserved.begin(), Reserved.end(), word);
            if (it == Reserved.end()) {
                 key = 2;
            }
            else {
                key = Reserved_word.at(word);
            }

        }
        //识别运算符
        else
        {

            switch (str[i])
            {
               
            case '+': 
            {
                key = Operator_word.at("+");
                word = "+";
                break;
            }
            case '-':
            {
                key = Operator_word.at("-");
                word = "-";
                break;
            }
            case '*':
            {
                key = Operator_word.at("*");
                word = "*";
                break;
            }
            case '/': {
                key = Operator_word.at("/");
                word = "/";
                break;
            }
            case '=': {
                key = Operator_word.at("=");
                word = "=";
                break;
            }
            case '<': {
                i++;
                if (str[i] == '>')
                {
                    key = Operator_word.at("<>");
                    word = "<>";

                }
                else if (str[i] == '=')
                {
                    key = Operator_word.at("<=");
                    word = "<=";

                }
                else if (str[i] == '<')
                {
                    key = Operator_word.at("<<");
                    word = "<<";
                }
                else
                {
                    i--;
                    key = Operator_word.at("<");
                    word = "<";
                }
                break;
            }
            case '>': {
                i++;
                if (str[i] == '=')
                {
                    key = Operator_word.at(">=");
                    word = ">=";
                }
                else if (str[i] == '>') {
                    key = Operator_word.at(">>");
                    word = ">>";
                }
                else

                {
                    i--;
                    key = Operator_word.at(">");
                    word = ">";
                }
                break;
            }
            case ':':
            {
                key = Operator_word.at(":");
                word = ":";
                break;
            }
                //分割界符
            case '(':
            {
                key = decollator_word.at("(");
                word = "(";
                break;
            }
            case ')':
            {
                key = decollator_word.at(")");
                word = ")";
                break;
            }
            case ',':
            {
                key = decollator_word.at(",");
                word = ",";
                break;
            }
            case ';':
            {
                key = decollator_word.at(";");
                word = ";";
                break;
            }
            case '{':
            {
                key = decollator_word.at("{");
                word = "{";
                break;
            }
            case '}':
            {
                key = decollator_word.at("}");
                word = "}";
                break;
            }
            case '[':
            {
                key = decollator_word.at("[");
                word = "[";
                break;
            }
            case ']':
            {
                key = decollator_word.at("]");
                word = "]";
                break;
            }
                //错误处理
            default:
               
                break;

            }
            
        }
        if (key != 0 && word != "") {
            result_temp = "(" + to_string(key) + "," + word + ")";
            result.push_back(result_temp);
            key = 0;
            word = "";
        }
        
    }
    save_file(result);

    cout << "Yes,it is correct." << endl;
    return 0;
}



#include <iostream>
#include <string>
#include <unordered_map>
#include<map>
#include <algorithm>
#include<vector>
#include <fstream>
using namespace std;




//����ʶ���ǻ����ֻ��ʶ�� = { "int", "main", "void", "if", "char", "return", "short", "long", "short", "signed", "ensigned",
vector<string> Reserved = { "restrict", "struct", "union", "enum", "typedef", "sizeof", "auto", "static", "register", "extern", "const",
        "volatitle", "break", "goto", "else", "switch", "case", "default", "continue", "do", "double", "float","int"};// �����ֱ�
vector<string> Operator = { "+", "-", "*", "/", "%", ".", "++", "--", ">", "<", "=",  "?", "'",
      "\"", "==", ">=", "<=", "!=", "&", "|", "~", "^", "<<", ">>", "!", "&&", "||", "+=", "-=", "*=", "/=",
      "%=", "&=", "|=", "^=", ">>=", "<==", "*", "&" , ":" ,"<>"};//���ű�
vector<string> decollator = { "(", ")", "{", "}", ";", "[", "]" ,","};//�ָ��

  unordered_map<string,int> Reserved_word;//�����ֹ�ϣ
  unordered_map<string, int> Operator_word;//���ű��ϣ
  unordered_map<string, int> decollator_word;////�ָ�����ϣ
  int constant=0;//����
  int identifier = 0;//��־��
  



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
       constant = j;//����
      j++;
       identifier = j;//��־��
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
      ofs << "������ ��1" << endl;
      ofs << "��ʶ���� ��2" << endl;
      ofs << "�ؼ����룺" << endl;
      for (auto it : Reserved_word) 
          ofs << "(  " << it.first << " , " << it.second <<"  )" << endl;
      
      ofs << "������" << endl;
      for (auto it : Operator_word)
          ofs << "(  " << it.first << " , " << it.second << "  )" << endl;
      ofs << "�ָ�����" << endl;
      for (auto it : decollator_word)
          ofs << "(  " << it.first << " , " << it.second << "  )" << endl;
      
      ofs.close();
  }
 
int main()
{
     
    init();
    
   
    vector <string> result;//��¼���

    string str1, str;
    while (cin >> str1)
    {
        if (str1 == "end") {
            break;
        }
        //������루�ַ�����ʽ��
        str = str + ' ' + str1;
    }
    //��ʼ�������Ĵ���
    int length_str = str.length();
    string result_temp;
    int key=0;
    string word;
    for (int i = 0; i < length_str; i++)
    {
        //�������ո����ʱ����������ִ��
        if (str[i] == ' ' || str[i] == '\n') continue;
        //ʶ����
        else if (isdigit(str[i]))
        {

            //���ַ�����ʽ��ʾ�������
            while (isdigit(str[i]))
            {
                word += str[i];
                i++;
            }
            i--;
            key = 1;
        }
        //ʶ������ֻ��ʶ��
        else if (isalpha(str[i]))
        {
            
            //���ַ�����ʽ��ʾ��������ֻ��߱�ʶ��
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
        //ʶ�������
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
                //�ָ���
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
                //������
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


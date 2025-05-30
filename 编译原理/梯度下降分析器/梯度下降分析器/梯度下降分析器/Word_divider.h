#pragma once

#include<iostream>
#include<vector>
#include<string>
using namespace std;


vector<string> Reserved = { "restrict", "struct", "union", "enum", "typedef", "sizeof", "auto", "static", "register", "extern", "const",
        "volatitle", "break", "goto", "else", "switch", "case", "default", "continue", "do", "double", "float","int" };// 保留字表


void Word_divier(const string str,vector<string> &result)
{

    //init();


    //vector <string> result;//记录结果

    //开始处理读入的代码
    int length_str = str.length();
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
                word ="num";
                i++;
            }
            i--;
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
            vector<string>::iterator it = find(Reserved.begin(), Reserved.end(), word);
            if (it == Reserved.end()) {
                word = "id";
            }

        }
        //识别运算符
        else
        {

            switch (str[i])
            {

            case '+':
            {
                
                word = "+";
                break;
            }
            case '-':
            {
                
                word = "-";
                break;
            }
            case '*':
            {
               
                word = "*";
                break;
            }
            case '/': {

                word = "/";
                break;
            }
            case '=': {

                word = "=";
                break;
            }
            case '<': {
                i++;
                if (str[i] == '>')
                {

                    word = "<>";

                }
                else if (str[i] == '=')
                {

                    word = "<=";

                }
                else if (str[i] == '<')
                {
            
                    word = "<<";
                }
                else
                {
                    i--;
                  
                    word = "<";
                }
                break;
            }
            case '>': {
                i++;
                if (str[i] == '=')
                {
                
                    word = ">=";
                }
                else if (str[i] == '>') {
                  
                    word = ">>";
                }
                else

                {
                    i--;
                    
                    word = ">";
                }
                break;
            }
            case ':':
            {
       
                word = ":";
                break;
            }
            //分割界符
            case '(':
            {
             
                word = "(";
                break;
            }
            case ')':
            {
             
                word = ")";
                break;
            }
            case ',':
            {
             
                word = ",";
                break;
            }
            case ';':
            {
            
                word = ";";
                break;
            }
            case '{':
            {
             
                word = "{";
                break;
            }
            case '}':
            {
             
                word = "}";
                break;
            }
            case '[':
            {
            
                word = "[";
                break;
            }
            case ']':
            {
            
                word = "]";
                break;
            }
           
            
            //错误处理
            default:

                break;
            }
 
        }
        if (word != "") {

            result.push_back(word);

            word = "";
        }

    }

}